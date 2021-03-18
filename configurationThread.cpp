/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>

#include "configurationThread.h"
#include "amptgui_x_status.h"

static const QString formatIt("yyyy/MM/dd hh:mm:ss");

static QDateTime CurrentDateTimeOfLastWrite = QDateTime::currentDateTime();

ConfigurationThread::ConfigurationThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true;
    m_configurationFile = nullptr;
    m_errorString = "";
    m_configurationPathAndFileName = "";
}

ConfigurationThread::~ConfigurationThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void ConfigurationThread::stopConfigurationThreadOperation( void )
{
    m_operational = false;
}

void ConfigurationThread::receiveConfigurationToSave(const QString & configuration)
{
    qDebug() << Q_FUNC_INFO << " configuration is " << configuration << Qt::endl;

    const QMutexLocker locker(&m_mutex);
    m_configurationList.append(configuration);
    // qDebug() << Q_FUNC_INFO << " # of elements is " << m_dataToLogList.size() << " after adding " << data << Qt::endl;
}

void ConfigurationThread::startConfigurationThreadInterface(int waitTimeout, QString & directoryPath)
{
    const QMutexLocker locker(&m_mutex);
    AmptGUI_X_Status success = NO_ERROR;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString configurationFile(directoryPath);

    // qDebug() << Q_FUNC_INFO << " directoryPath for configuration file " << directoryPath;

    m_waitTimeout = waitTimeout;
	m_operational = true;

    if (! QDir(directoryPath).exists())
    {
        if (QDir().mkdir(directoryPath))
        {
          // qDebug() << Q_FUNC_INFO << " successfully created configuration directory " << directoryPath;
          m_errorString = QString(Q_FUNC_INFO) + " INFO: " + CurrentDateTime + " created configuration directory:" + directoryPath;
          emit sendConfigurationThreadInfo(m_errorString);

        }
        else
        {
		  qDebug() << Q_FUNC_INFO << " failed to create configuration directory " << directoryPath;
          m_errorString = QString(Q_FUNC_INFO) + " ERROR: " + CurrentDateTime + " failed to create configuration directory:" + directoryPath;
          emit sendConfigurationThreadError(m_errorString);
          success = ERROR_CREATING_DIRECTORY;
        }
    }
    else
	{
      // qDebug() << Q_FUNC_INFO << " configuration directory " << directoryPath << " already exists, proceeding ...";
      m_errorString = QString(Q_FUNC_INFO) + " INFO: " + CurrentDateTime + " cconfiguration directory:" + directoryPath + " already exists, proceeding ...";
      emit sendConfigurationThreadInfo(m_errorString);
    }

    // qDebug() << Q_FUNC_INFO << " documents dir:" << QStandardPaths::locate(QStandardPaths::DocumentsLocation,"Documents");
    // qDebug() << Q_FUNC_INFO << " standardlocations:" << QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    // QString docsPath = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0);

    configurationFile = "/AmptGUI_X_configuration.txt";
    // qDebug() << Q_FUNC_INFO << " Configuration file => " << configurationFile;


    if (success == NO_ERROR)
    {
        // QString configurationPathAndFileName(directoryPath);
        m_configurationPathAndFileName += directoryPath + configurationFile;

        m_configurationFile = new QFile(m_configurationPathAndFileName);

        // qDebug() << Q_FUNC_INFO << " size of config file:" << m_configurationFile->size();

        if (!m_configurationFile->open(QIODevice::ReadOnly | QIODevice::Truncate | QIODevice::Text))
        {
          qDebug() << " failed to open configuration file " << m_configurationPathAndFileName;
          m_errorString = QString(Q_FUNC_INFO) + " ERROR: " + CurrentDateTime + " failed to open configuration file:" + m_configurationPathAndFileName;
          emit sendConfigurationThreadError(m_errorString);
          success = ERROR_OPENING_CONFIGURATIONFILE;
          // Create default configuration file

        }
        else
        {
          // qDebug() << " success opening configuration file " << m_configurationPathAndFileName;
          // Read configuration file line by line, determine what is being configured, emit appropriate signal (including error(s)
          m_errorString = QString(Q_FUNC_INFO) + " INFO: " + CurrentDateTime + " opened configuration file:" + m_configurationPathAndFileName + " for read.";
          emit sendConfigurationThreadInfo(m_errorString);

          char buf[1024];
          memset(static_cast<void *>(buf),0,sizeof(buf));
          qint64 lineLength = -1;
          qint64 numberOfLinesRead = 0;
          QStringList configurationData;

          while ((lineLength = m_configurationFile->readLine(buf, sizeof(buf))) != -1)
          {
              // qDebug() << Q_FUNC_INFO << " INFO: configuration line : " << buf;
              configurationData.append(QString(buf));
              memset(static_cast<void *>(buf),0,sizeof(buf));
              numberOfLinesRead++;
          }
          // qDebug() << Q_FUNC_INFO << " INFO: number of configuration lines read: " << numberOfLinesRead;
          CurrentDateTimeOfLastWrite = CurrentDateTimeOfLastWrite.addYears(10);
          if (numberOfLinesRead > 0)
          {
              emit publishSavedConfiguration(configurationData);
          }
        }
        m_configurationFile->close();
        delete m_configurationFile;
        m_configurationFile = nullptr;
    }

    if ((success == NO_ERROR) || (success == ERROR_OPENING_CONFIGURATIONFILE)) // No errors or no default configuration info
    {
        if (!isRunning())
            start();
        else
            m_cond.wakeOne();
    }
    else
    {
        qDebug() << Qt::endl << Q_FUNC_INFO << " ERROR: " + CurrentDateTime + " Failed to create Configuration Thread: " << success << Qt::endl;
        emit sendConfigurationThreadError(m_errorString);
        m_operational = false;
    }
}


void ConfigurationThread::run()
{

  // qDebug() << Q_FUNC_INFO << " running ...";

  m_errorString = QString(Q_FUNC_INFO) + " INFO: read configuration file:" + m_configurationPathAndFileName + ", configuration thread operational.";
  emit sendConfigurationThreadInfo(m_errorString);
  while (m_operational) 
	{
      if (m_configurationList.isEmpty() == false)
        {
          QString configurationData = m_configurationList.takeFirst();
          m_mutex.lock();
          m_configurationFile = new QFile(m_configurationPathAndFileName);
          QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
          // qDebug() << Q_FUNC_INFO << " size of config file:" << m_configurationFile->size();

          if (!m_configurationFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
          {
            qDebug() << " failed to open configuration file " << m_configurationPathAndFileName;
            m_errorString = QString(Q_FUNC_INFO) + " ERROR: " + CurrentDateTime + " failed to open configuration file:" + m_configurationPathAndFileName + " for write.";
            emit sendConfigurationThreadError(m_errorString);
          }
          else
          {
              QTextStream loggin(m_configurationFile);
              m_errorString = QString(Q_FUNC_INFO) + " INFO: " + CurrentDateTime + " opened configuration file:" + m_configurationPathAndFileName + " for write.";
              emit sendConfigurationThreadInfo(m_errorString);

              qDebug() << Q_FUNC_INFO << " configuration data to save " << configurationData;
              loggin.reset();
              loggin.seek(0);
              loggin << configurationData << Qt::endl;
              // m_configurationFile->write(configurationData.toLocal8Bit());
              // m_configurationFile->flush();
              CurrentDateTimeOfLastWrite = QDateTime::currentDateTime();
              qDebug() << Q_FUNC_INFO << " INFO: CurrentDateTimeOfLastWrite:" << CurrentDateTimeOfLastWrite;
              m_errorString = QString(Q_FUNC_INFO) + " INFO: saved configuration file:" + m_configurationPathAndFileName;
              emit sendConfigurationThreadInfo(m_errorString);
          }
          m_mutex.unlock();
		}
	  else
		{
          QThread::msleep(500);
         // qDebug() << Q_FUNC_INFO << " no data " << Qt::endl;

		}
	}
  
}


void ConfigurationThread::handleTerminate( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: begin ...";

    QDateTime terminateDateTime(QDateTime::currentDateTime());

    while (m_operational == true)
    {
        QDateTime terminateDateTime(QDateTime::currentDateTime());
        qDebug() << Q_FUNC_INFO << " INFO : " << terminateDateTime;

        qDebug() << Q_FUNC_INFO << " INFO: waiting on mutex ...";
        m_mutex.lock();
        m_configurationList.clear();
        m_configurationFile->close();
        m_operational = false;
        m_mutex.unlock();

    }
    qDebug() << Q_FUNC_INFO << " INFO: ending ...";
}
