/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>

#include "receiveOTADataThread.h"

static const QString formatIt("yyyy_MM_dd_HH_mm_ss");

ReceiveOTADataThread::ReceiveOTADataThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true;
}

ReceiveOTADataThread::~ReceiveOTADataThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void ReceiveOTADataThread::stopReceiveOTADataThreadOperation( void )
{
    m_operational = false;
}


void ReceiveOTADataThread::receiveOTAData(const QString data)
{
    // qDebug() << " data is " << data << Qt::endl;

    const QMutexLocker locker(&m_mutex);
    m_otaDataReceivedList.append(data);
    // qDebug() << " number of elements: " << m_otaDataReceivedList.size() << Qt::endl;
}

void ReceiveOTADataThread::startReceiveOTADataThreadInterface(int waitTimeout, const bool logging)
{
    const QMutexLocker locker(&m_mutex);
    m_waitTimeout = waitTimeout;
    m_logData = logging;
	m_operational = true;

	if (m_logData)
	  {
		// Create name, try to open for write,
	  }

    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}


void ReceiveOTADataThread::run()
{
    // qDebug() << Q_FUNC_INFO << " running...";

    static const QRegularExpression OGW_RE("^\\d+\\s*$");
    static QRegularExpressionMatch otherGWMatch;
    int timeElapsedSinceLastOtherGWNotification = 0;
    QString CurrentDateTime("");

    while (m_operational)
	{
        if (timeElapsedSinceLastOtherGWNotification > 0)
        {
            if (timeElapsedSinceLastOtherGWNotification == 1)
            {
                emit publishOtherGatewayObserved(false);
            }
            timeElapsedSinceLastOtherGWNotification--;
        }


      if (m_otaDataReceivedList.isEmpty() == false)
		{

          QString otaData = m_otaDataReceivedList.takeFirst();

          // qDebug() << Q_FUNC_INFO << " INFO: otaData:" << otaData << " length is " << otaData.length();

          if ((otaData.length() == 72) && (otaData.at(0) == '|'))
          {
              if ( otaData.at(7) == '|' )
              {
                  emit receivedOTADataThreadMessage(otaData);
              }
              else
              {
                  QString ErrorStr(Q_FUNC_INFO);
                  QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                  ErrorStr += " ERROR: " + CurrentDateTime + " received unknown or poorly formed data message: " + otaData;
                  emit publishReceivedOTADataThreadUnknownMessage(ErrorStr);
                  // qDebug() << ErrorStr;
              }
          }
          else if (otaData.mid(0,5) == "\r\nL1:")
          {
              emit receivedOTADataThreadMessage(otaData);
          }
          else if ((otaData.length() > 62) && (otaData.at(0) == 'S'))
          {
              if (otaData.at(2) == '4')
              {
                  // qDebug() << Q_FUNC_INFO << " INFO: otaData:" << otaData;
                  emit receivedOTADataThreadCoeffsMessage(otaData);
              }
              else
              {
                  emit receivedOTADataThreadParameterBlockMessage(otaData);
              }
          }
          else if ((otaData.at(2) == '=') && (otaData.at(3) == '>'))
          {
              emit receivedSuperCyclesMessage(otaData);
          }
          else if ((otaData.at(0) == 'G') && (otaData.at(1) == 'W') && (otaData.at(2) == '\t'))
          {
              emit publishOtherGatewayInformation(otaData);
          }
          else if ((otaData.at(0) == 'I') && (otaData.at(1) == '\r') && (otaData.at(3) == '\r') && (otaData.at(5) == 'B'))
          {
              //I\r\n\r\nBOU\r\n response to I command, sent to ensure comms are alive. Nothing to do.
              qDebug() << Q_FUNC_INFO << " INFO: got response to I command.";
          }
          else
          {
              // qDebug() << Q_FUNC_INFO << " oTA data => " << otaData;
              if (otaData.contains("AMPT BOU"))
              {
                  // qDebug() << Q_FUNC_INFO << " got a GW PB message.";
                  emit receivedOTADataThreadGatewayParameterBlockMessage( otaData );
              }
              else if (otaData.contains("Auxilary GW information."))
              {
                  // qDebug() << Q_FUNC_INFO << " got a GW ? PB message.";
                  emit receivedOTADataThreadGatewayParameterBlockMessage(otaData);
              }
              else if (otaData.mid( (otaData.length()) - 4) == "\r\n\r\n")
              {
                  // qDebug() << Q_FUNC_INFO << " echoed command " << otaData;
              }
              else
              {
                  QString ErrorStr(Q_FUNC_INFO);

                  otherGWMatch = OGW_RE.match(otaData);
                  if ( otherGWMatch.hasMatch() )
                  {
                      if (timeElapsedSinceLastOtherGWNotification <= 0 ) /* Control how many messages and signals are published */
                      {
                          CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                          ErrorStr += " ERROR: " + CurrentDateTime + " other gateway observed, data => " + otaData + " length:" + QString::number(otaData.length());
                          timeElapsedSinceLastOtherGWNotification = 180;
                          emit publishReceivedOTADataThreadError(ErrorStr);
                          qDebug() << ErrorStr;
                          emit publishOtherGatewayObserved(true);
                      }
                      else
                      {
                          ErrorStr += " ERROR: " + CurrentDateTime + " other gateway observed BUT already in countdown, data => " + otaData + " length:" + QString::number(otaData.length());
                          emit publishReceivedOTADataThreadError(ErrorStr);
                          qDebug() << ErrorStr;
                      }
                  }
                  else
                  {
                      CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                      if (otaData.length() > 100)
                      {
                          ErrorStr += " ERROR: " + CurrentDateTime + " received unknown or poorly formed too long non raw data message";
                      }
                      else
                      {
                          ErrorStr += " ERROR: " + CurrentDateTime + " received unknown or poorly formed non raw data message: " + otaData;
                      }
                      emit publishReceivedOTADataThreadUnknownMessage(ErrorStr);
                      qDebug() << ErrorStr;
                  }
              }
          }
		}
	  else
		{
          QThread::msleep(80);
         // qDebug() << Qt::endl << "no data " << Qt::endl;

		}
	}

  emit this->receiveOTADataThreadExit();
  
}

void ReceiveOTADataThread::receiveOTADataThreadLogging( bool logging )
{
    qDebug() << Q_FUNC_INFO << " logging: " << QString::number(logging);
    m_logData = logging;
}

void ReceiveOTADataThread::handleTerminate( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: begin ...";
    m_mutex.lock();
    m_otaDataReceivedList.clear();
    m_operational = false;
    m_mutex.unlock();
    qDebug() << Q_FUNC_INFO << " INFO: end ...";
}
