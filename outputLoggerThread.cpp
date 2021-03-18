/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

#include "outputLoggerThread.h"
#include "amptgui_x_status.h"

static const QString formatIt("yyyy_MM_dd_HH_mm_ss");


outputLoggerThread::outputLoggerThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true;
    m_readyForRawData = false;
    m_rawLoggerFile = nullptr;
    m_rawLoggerStream = nullptr;

    m_readyForCSVData = false;
    m_writtenCSVHeaderLine = false;
    m_csvLoggerFile = nullptr;
    m_csvLoggerStream = nullptr;

}

outputLoggerThread::~outputLoggerThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void outputLoggerThread::stopLoggerThreadOperation( void )
{
    // grab mutex
    // stop allowing data to be queued.
    // Empty string lists
    // close streams and files
    m_operational = false;
}

void outputLoggerThread::handleRawDataToLog(const QString data)
{
    if (m_readyForRawData == true)
    {
        const QMutexLocker locker(&m_rawMutex);
        m_rawDataToLogList.append(data);
    }
}
void outputLoggerThread::handleOTADataForCSV(const QString sn, const QString data)
{
    // qDebug() << Q_FUNC_INFO << " got some CSV for " << sn;
    if (m_readyForCSVData == true)
    {

        const QMutexLocker locker(&m_csvMutex);
        QString csvData(sn);
        csvData += "," + data;
        qDebug() << Q_FUNC_INFO << " INFO: queuing CSV data " << csvData << " size of queue = " << m_csvDataToLogList.size();
        m_csvDataToLogList.append(csvData);
    }
}



void outputLoggerThread::startLoggerThreadInterface(int waitTimeout)
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

    if (success == NO_ERROR)
    {
        if (!isRunning())
            start();
        else
            m_cond.wakeOne();
    }
    else
    {
        // qDebug() << Qt::endl << Q_FUNC_INFO << " ERROR: " + CurrentDateTime + " Failed to create output Logger Thread: " << success << Qt::endl;
        ErrorStr = "";
        ErrorStr += Q_FUNC_INFO;
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create Logger Thread, it is non operational...";
        qDebug() << ErrorStr;
        emit publishOutputLoggerThreadError(ErrorStr);

        m_operational = false;
    }
}


void outputLoggerThread::run()
{
    // qDebug() << Q_FUNC_INFO << " running ...";
    QString csvData;
    bool loggedSomething = false;


  while (m_operational)
    {
      loggedSomething = false;

      if (m_rawDataToLogList.isEmpty() == false)
        {
          m_rawMutex.lock();
          QString logData = m_rawDataToLogList.takeFirst();
          m_rawMutex.unlock();

          if (m_rawLoggerFile != nullptr)
          {
              *m_rawLoggerStream << logData << Qt::endl;
              loggedSomething = true;
          }
      }

      if (m_csvDataToLogList.isEmpty() == false)
      {
          qDebug() << Q_FUNC_INFO << " some CSV data";

          if (m_csvLoggerFile != nullptr)
          {
              if (m_writtenCSVHeaderLine == false)
              {
                  *m_csvLoggerStream << "SN,MAC,Time,Vin1,Vin2,Vout,Iin1,Iin2,Iout,PwrDis,Text,NetStatus,OV,OC,Module,MPP,Channel,Bunch,TimeSlot,GwOff,GwRSSI,EdOff,EdRSSI\r\n";
                  m_writtenCSVHeaderLine = true;
              }
              m_csvMutex.lock();
              csvData = m_csvDataToLogList.takeFirst();
              m_csvMutex.unlock();
              // Create CSV line for data, ignore SC lines
              *m_csvLoggerStream << csvData << "\n";
              qDebug() << Q_FUNC_INFO << " logged some CSV data " << csvData;

          }
      }

      if (loggedSomething == false)
      {
          QThread::msleep(80);
          // qDebug() << Q_FUNC_INFO << " no data " << Qt::endl;
      }
    }
  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";
}

void outputLoggerThread::handleStartOutputRawFile(const QString data)
{
    QString ErrorStr(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    qDebug() << Q_FUNC_INFO << " INFO: entering ...";

    if (m_rawLoggerFile == nullptr)
    {
        // QFileDevice::FileError err = QFileDevice::NoError;
        m_rawLoggerFile = new QFile(data);
        QString logFileDateTime(QDateTime::currentDateTime().toString(formatIt));


        if (!m_rawLoggerFile->open(QIODevice::Append | QIODevice::Text))
        {
            ErrorStr += " ERROR: " + CurrentDateTime + " failed to open raw log file " + data + ", error => " + m_rawLoggerFile->errorString() + ", logging of raw data will not occur.";
            qDebug() << ErrorStr;
            emit publishOutputLoggerThreadError(ErrorStr);
            handleStopOutputFiles();
            emit publishRawFileOpenFailed(ErrorStr);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: opened raw log file " << data;

            if (m_rawLoggerStream == nullptr)
            {
                    m_rawLoggerStream = new QTextStream(m_rawLoggerFile);
                    m_readyForRawData = true;
                    qDebug() << Q_FUNC_INFO << " INFO: ready to log raw data";
                    emit publishOutputLoggerReady();
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " request to log raw data but already logging (stream not nullptr), stopping logging...";
                qDebug() << ErrorStr;
                emit publishOutputLoggerThreadError(ErrorStr);
                handleStopOutputFiles();
                emit publishRawFileOpenFailed(ErrorStr);
            }
        }
    }
    else
    {
        ErrorStr += " ERROR: request to log raw data but already logging (file not nullptr), stopping logging...";
        qDebug() << ErrorStr;
        emit publishOutputLoggerThreadError(ErrorStr);
        handleStopOutputFiles();
        emit publishRawFileOpenFailed(ErrorStr);
    }
   qDebug() << Q_FUNC_INFO << " INFO: exiting ...";
}

void outputLoggerThread::handleStartOutputCSVFile(const QString data)
{
    qDebug() << Q_FUNC_INFO << " INFO: entering ...";
    QString logFileDateTime(QDateTime::currentDateTime().toString(formatIt));
    QString ErrorStr(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    if (m_csvLoggerFile == nullptr)
    {

        // QFileDevice::FileError err = QFileDevice::NoError;
        QString fileToOpen(data);
        int index = fileToOpen.indexOf(".csv");
        if (index == -1)
        {
            fileToOpen += ".csv";
        }
        m_csvLoggerFile = new QFile(fileToOpen);

        if (!m_csvLoggerFile->open(QIODevice::Append | QIODevice::Text))
        {
            ErrorStr += " ERROR: " + CurrentDateTime + " failed to open csv log file " + fileToOpen + ", error => " + m_csvLoggerFile->errorString() + ", logging of csv data will not occur.";
            qDebug() << ErrorStr;
            emit publishOutputLoggerThreadError(ErrorStr);
            handleStopOutputFiles();
            emit publishCSVFileOpenFailed(ErrorStr);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: opened csv log file " << fileToOpen;

            if (m_csvLoggerStream == nullptr)
            {
                m_csvLoggerStream = new QTextStream(m_csvLoggerFile);
                m_readyForCSVData = true;
                qDebug() << Q_FUNC_INFO << " INFO: ready to log csv data";
                emit publishOutputLoggerReady();
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " request to log csv data but already logging (stream not nullptr), stopping logging...";
                qDebug() << ErrorStr;
                emit publishOutputLoggerThreadError(ErrorStr);
                handleStopOutputFiles();
                emit publishCSVFileOpenFailed(ErrorStr);
            }
        }
    }
    else
    {
        ErrorStr += " ERROR: " + CurrentDateTime + " request to log csv data but already logging (file not nullptr), stopping logging...";
        qDebug() << ErrorStr;
        emit publishOutputLoggerThreadError(ErrorStr);
        handleStopOutputFiles();
        emit publishCSVFileOpenFailed(ErrorStr);
    }
   qDebug() << Q_FUNC_INFO << " INFO: exiting ...";

}

void outputLoggerThread::handleStopOutputFiles(void)
{
    qDebug() << Q_FUNC_INFO << " INFO: stopping output logging ...";

    m_readyForCSVData = false;
    m_writtenCSVHeaderLine = false;
    m_readyForRawData = false;

    if (m_rawLoggerStream != nullptr)
    {
        m_rawLoggerStream->flush();
        m_rawLoggerStream = nullptr;
    }

    if (m_rawLoggerFile != nullptr)
    {
        m_rawDataToLogList.clear();
        m_rawLoggerFile->flush();
        m_rawLoggerFile->close();
        delete(m_rawLoggerFile);
        m_rawLoggerFile = nullptr;
    }
    m_rawDataToLogList.clear();

    if (m_csvLoggerStream != nullptr)
    {
        m_csvLoggerStream->flush();
        m_csvLoggerStream = nullptr;
    }

    if (m_csvLoggerFile != nullptr)
    {
        m_csvDataToLogList.clear();
        m_csvLoggerFile->flush();
        m_csvLoggerFile->close();
        delete(m_csvLoggerFile);
        m_csvLoggerFile = nullptr;
    }
    m_csvDataToLogList.clear();

    qDebug() << Q_FUNC_INFO << " INFO: stopped output logging ...";
}

void outputLoggerThread::handleTerminate( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: begin ...";
    m_mutex.lock();
    handleStopOutputFiles();
    m_operational = false;
    m_mutex.unlock();
    qDebug() << Q_FUNC_INFO << " INFO: end ...";
}
