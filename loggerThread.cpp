/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QDebug>

#include "loggerThread.h"
#include "amptgui_x_status.h"

LoggerThread::LoggerThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true;
    m_loggerFile = nullptr;
}

LoggerThread::~LoggerThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void LoggerThread::stopLoggerThreadOperation( void )
{
    m_operational = false;
}

void LoggerThread::receiveDataToLog(const QString data)
{
    const QMutexLocker locker(&m_mutex);
    m_dataToLogList.append(data);
}

void LoggerThread::startLoggerThreadInterface(int waitTimeout, QString & directoryPath)
{
    const QMutexLocker locker(&m_mutex);
    AmptGUI_X_Status success = NO_ERROR;
    QString formatIt("yyyy_MM_dd_HH_mm_ss");
    QString logFileDateTime(QDateTime::currentDateTime().toString(formatIt));
    QString ErrorStr(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    // qDebug() << Q_FUNC_INFO << " starting logger thread interface ...";

    m_waitTimeout = waitTimeout;
	m_operational = true;

    if (! QDir(directoryPath).exists())
    {
        if (! QDir().mkdir(directoryPath))
        {
            success = ERROR_CREATING_DIRECTORY;
            ErrorStr += " ERROR: " + CurrentDateTime + " failed to create directory " + directoryPath + " for logging.";
            qDebug() << ErrorStr;
            emit publishLoggerThreadError(ErrorStr);
        }
        else {
            {
                qDebug() << Q_FUNC_INFO << " created directory " << directoryPath;
            }
        }
    }

    if (success == NO_ERROR)
    {
        // Construct Log File
        QString logPathAndFileName(directoryPath);


        logPathAndFileName += "/AmptGUI_X_";
        logPathAndFileName += logFileDateTime;
        m_loggerFile = new QFile(logPathAndFileName);

        if (!m_loggerFile->open(QIODevice::Append | QIODevice::Text))
        {
            success = ERROR_OPENING_LOGFILE;
            ErrorStr += " ERROR: " + CurrentDateTime + " failed to open log file " + logPathAndFileName + ", logging will not occur.";
            qDebug() << ErrorStr;
            emit publishLoggerThreadError(ErrorStr);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " INFO: opened log file " << logPathAndFileName;
        }
    }

    if (success == NO_ERROR)
    {
        if (!isRunning())
            start();
        else
            m_cond.wakeOne();
    }
    else
    {
        // qDebug() << Qt::endl << Q_FUNC_INFO << " ERROR: " + CurrentDateTime + " Failed to create Logger Thread: " << success << Qt::endl;
        ErrorStr = "";
        ErrorStr += Q_FUNC_INFO;
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create Logger Thread, it is non operational...";
        qDebug() << ErrorStr;
        emit publishLoggerThreadError(ErrorStr);

        m_operational = false;
    }
}


void LoggerThread::run()
{
    QTextStream loggin(m_loggerFile);

    // qDebug() << Q_FUNC_INFO << " running ...";

  while (m_operational) 
	{
      if (m_dataToLogList.isEmpty() == false)
        {
          QString logData = m_dataToLogList.takeFirst();
          loggin << logData << Qt::endl;
		}
	  else
		{
          QThread::msleep(80);
         // qDebug() << Q_FUNC_INFO << " no data " << Qt::endl;

		}
	}
  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";
}

