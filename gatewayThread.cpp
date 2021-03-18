/****************************************************************************
**
**
****************************************************************************/

#include "gatewayThread.h"

#include <QSerialPort>
#include <QTime>
#include <QDateTime>
#include <QDebug>

static const QString formatIt("yyyy/MM/dd hh:mm:ss");
static  const QString rn("\r\n");
static const QString gatewayResetCommand("R\r\n");

GatewayThread::GatewayThread(QObject *parent) :
    QThread(parent)
{
    m_attemptToBeOperational = true;
    m_operational = true;
    m_includeCommandsInLog = false;
}

GatewayThread::~GatewayThread()
{
    m_mutex.lock();
    m_attemptToBeOperational = false;
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void GatewayThread::stopOperation()
{
    m_mutex.lock();
    m_operational = false;
    m_mutex.unlock();
}

void GatewayThread::commandToSend(const QString command)
{
    // qDebug() << Q_FUNC_INFO << " got command " << command;

    QString commandWithFeedReturn(command);

    if (commandWithFeedReturn.contains('\r'))
    {
        if (! commandWithFeedReturn.contains('\n'))
        {
            commandWithFeedReturn.append('\n');
            // qDebug() << Q_FUNC_INFO << " appended line feed to command.";
        }
    }
    else
    {
        commandWithFeedReturn += rn;
        // qDebug() << Q_FUNC_INFO << " appended line feed carriage return to command.";
    }

    const QMutexLocker locker(&m_mutex);
    m_commandsToGatewayList.append(commandWithFeedReturn);
    // qDebug() << Q_FUNC_INFO << " appended " << commandWithFeedReturn << " to GatewayList.";
}

void GatewayThread::handleOutputIncludeCommandsInLog(bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: received bool value of " << s;
    m_includeCommandsInLog = s;
    //qDebug() << Q_FUNC_INFO << " INFO: m_includeCommandsInLog " << m_includeCommandsInLog;
}

void GatewayThread::handleGatewayCommandToSend(const QString command)
{
    qDebug() << Q_FUNC_INFO << " got command " << command;
    QString commandWithFeedReturn(command);

    if (commandWithFeedReturn.contains('\r'))
    {
        if (! commandWithFeedReturn.contains('\n'))
        {
            // qDebug() << Q_FUNC_INFO << " command already has line feed carriage return in command.";
            commandWithFeedReturn.append('\n');
            // qDebug() << Q_FUNC_INFO << " appended line feed to command.";
        }
    }
    else
    {
        commandWithFeedReturn += rn;
        // qDebug() << Q_FUNC_INFO << " appended line feed carriage return to command.";
    }

    const QMutexLocker locker(&m_mutex);
    m_commandsToGatewayList.append(commandWithFeedReturn);
    // qDebug() << Q_FUNC_INFO << " appended " << commandWithFeedReturn << " to GatewayList.";
}

void GatewayThread::startGatewayInterface(const QString portName, int waitTimeout, const bool logging)
{
    const QMutexLocker locker(&m_mutex);
    m_portName = portName;
    m_waitTimeout = waitTimeout;
	m_logTraffic = logging;
	m_operational = true;

    // qDebug() << Q_FUNC_INFO << " INFO: attempt to start ...";

	if (m_logTraffic)
	  {
        // LBC, TBD, Create name, try to open for write,
	  }

    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

bool GatewayThread::isOperational( void )
{
    return m_operational;
}

void GatewayThread::resetGateway( void )
{
    const QMutexLocker locker(&m_mutex);
    m_commandsToGatewayList.append(gatewayResetCommand);
}

void GatewayThread::run()
{


  QString response;
  int indexRN = 0;
  QByteArray gatewayData;
  bool shortOC = false;
  const int delayInCyclesBetweenSendingCommandsToGateway = 3;
  int loopsBetweenSendingCommandsToGateway = delayInCyclesBetweenSendingCommandsToGateway;
  int countdownToNextPublishNotOperational = 0;
  bool commsHappened = false;
  int operationalCyclesSinceComms = 0;
  const int operationalCyclesNoCommsSendTestCommand = 10;
  const int operationalCyclesNoCommsSendTestCommandWarn = operationalCyclesNoCommsSendTestCommand - 3;
  const int maxOperationalCyclesSinceComms = 15;

  // qDebug() << Q_FUNC_INFO << " begin of run()..." << Qt::endl;

  QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
  if (m_portName.isEmpty())
  {
      QString portErrString(Q_FUNC_INFO);
      portErrString += " ERROR: " + CurrentDateTime + " Gateway port name is unspecified, gateway is not operational.";

      qDebug() << portErrString;
      emit publishGatewayError(portErrString);
	  emit gatewayClosed();
      m_operational = false;
      m_attemptToBeOperational = false;
  }
  else
  {
      while (m_attemptToBeOperational)
      {
          QSerialPort gateway;
          gateway.setPortName(m_portName);
          operationalCyclesSinceComms = 0;

          if (!gateway.open(QIODevice::ReadWrite))
          {
              if (countdownToNextPublishNotOperational <= 0)
              {
                  QString errString(Q_FUNC_INFO);
                  errString += " ERROR: " + CurrentDateTime + " Failed to open gateway port " + m_portName + " , error code:" + gateway.error() + ":" + gateway.errorString();
                  qDebug() << errString;
                  emit publishGatewayError(errString);

                  gateway.clearError();
                  emit gatewayClosed();
                  m_operational = false;
                  countdownToNextPublishNotOperational = 10;
              }
              else
              {
                  QThread::msleep(3000);
                  countdownToNextPublishNotOperational--;
              }
          }
          else
          {
              m_operational = true;
              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

              // qDebug() << Q_FUNC_INFO << " INFO: Gateway is operational " << CurrentDateTime;
              // qDebug() << Q_FUNC_INFO << " #### #### Initialial Gateway baudrate is " << QString::number(gateway.baudRate());

              gateway.setBaudRate(QSerialPort::Baud115200);
              // qDebug() << Q_FUNC_INFO << " #### #### NOW, Gateway baudrate is " << gateway.baudRate();
              response.clear();
              indexRN = 0;
              gatewayData.clear();
              shortOC = false;
              loopsBetweenSendingCommandsToGateway = delayInCyclesBetweenSendingCommandsToGateway;
              emit publishGatewayIsOperational();

              while (m_operational)
              {
                  commsHappened = false;

                  if (gateway.waitForReadyRead(m_waitTimeout))
                  {
                      gatewayData = gateway.readAll();
                      while (gateway.waitForReadyRead(10))
                      {
                        gatewayData += gateway.readAll();
                      }

                      if (shortOC == true)
                      {
                          response += QString::fromUtf8(gatewayData);
                      }
                      else
                      {
                          response = QString::fromUtf8(gatewayData);
                      }
                      // qDebug() << Q_FUNC_INFO << "gatewayData as QString:" << response << " length of response:" << response.length();

                      indexRN = response.lastIndexOf(rn);

                      if (indexRN == 0)
                      {
                          if (response.length() > 2)
                          {
                              // BUG: read from gateway sometimes does not include the data associated with the SC line and MAC, comes in next read.
                              if ((response.lastIndexOf("SC") == 2) && (response.length() == 20))
                              {
                                  // qDebug() << Q_FUNC_INFO << " a short SC";
                                  shortOC = true;
                              }
                              else
                              {
                                  shortOC = false;
                                  response.remove(0,2);
                                  emit this->gatewayOutput(response);
                              }
                          } /* END if (response.length() > 2) */
                      } /* END if (indexRN == 0) */
                      else if (indexRN > 0)
                      {
                        shortOC = false;
                        QString x = response.left(indexRN);
                        // qDebug() << Q_FUNC_INFO << " INFO: raw INPUT from gateway: " << x;
                        emit this->gatewayOutput(response);
                      }
                      else
                      {
                          shortOC = false;
                          QString ErrorStr(Q_FUNC_INFO);
                          ErrorStr += " ERROR: " + CurrentDateTime + " indexRN is < 1 for string received at gateway:";
                          ErrorStr += response;
                          qDebug() << ErrorStr;
                          emit publishGatewayError(ErrorStr);
                      }
                      commsHappened = true;
                  } /* END if (gateway.waitForReadyRead(m_waitTimeout)) */
                  else
                  {
                      emit timeout(tr("Wait read response timeout %1") .arg(QTime::currentTime().toString()));
                  }

                  if (loopsBetweenSendingCommandsToGateway > 0)
                  {
                      loopsBetweenSendingCommandsToGateway--;
                  }

                  // qDebug() << Q_FUNC_INFO << " loopsBetweenSendingCommandsToGateway: " << loopsBetweenSendingCommandsToGateway;

                  if ((m_commandsToGatewayList.empty() == false) && (loopsBetweenSendingCommandsToGateway == 0))
                  {
                      const QByteArray commandData = (m_commandsToGatewayList.takeFirst()).toUtf8();

                      qDebug() << Q_FUNC_INFO << " writing command " << commandData << " to gateway." << Qt::endl;

                      qint64 bWritten = gateway.write(commandData);

                      if (gateway.waitForBytesWritten(500) == false)
                      {

                          emit timeout(tr("Wait gateway write failed, timeout occurred at %1")
                                       .arg(QTime::currentTime().toString()));
                          if (gateway.error() != QSerialPort::NoError)
                          {
                              QString GErrorStr(Q_FUNC_INFO);
                              GErrorStr += " ERROR: " + CurrentDateTime + " " + (tr("Error: gateway write error, %1  code: %2  %3 bytes written: %4")
                                                                                 .arg(QTime::currentTime().toString()).arg(gateway.error()).arg(gateway.errorString()).arg(bWritten));
                              emit publishGatewayError(GErrorStr);
                              qDebug() << GErrorStr;
                              gateway.clearError();
                              operationalCyclesSinceComms++;
                          }
                          else if (commandData == gatewayResetCommand)
                          {
                              m_operational = false;
                              emit publishGatewayIsNotOperational();
                          }
                      }
                      else
                      {
                          qDebug() << Q_FUNC_INFO << " Bytes Successfully Written to gateway " << bWritten;
                          if (m_includeCommandsInLog == true)
                          {
                              QString command(commandData);
                              command.remove("\r\n");
                              emit publishCommandToLog(command);
                          }
                          commsHappened = true;
                      }
                      loopsBetweenSendingCommandsToGateway = delayInCyclesBetweenSendingCommandsToGateway;
                  } /* END if ((m_commandsToGatewayList.empty() == false) && (loopsBetweenSendingCommandsToGateway == 0)) */

                  if (commsHappened == true)
                  {
                      operationalCyclesSinceComms = 0;
                  }
                  else
                  {
                      CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                      if (++operationalCyclesSinceComms == operationalCyclesNoCommsSendTestCommand)
                      {
                          commandToSend("I\r\n");
                          CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                          QString gatewayCheckStr(Q_FUNC_INFO);
                          gatewayCheckStr += " INFO: " + CurrentDateTime + " sending check command 'I' to gateway";
                          emit publishGatewayError(gatewayCheckStr);
                          qDebug() << gatewayCheckStr;

                      }
                      else if (operationalCyclesSinceComms >= maxOperationalCyclesSinceComms)
                      {
                          m_operational = false;
                          const QByteArray commandData = "R\r\n";
                          // qDebug() << Q_FUNC_INFO << " writing command " << commandData << " to gateway." << Qt::endl;
                          qint64 bWritten = gateway.write(commandData);

                          if (gateway.waitForBytesWritten(1000) == false)
                          {
                              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                              QString resetWaitError(Q_FUNC_INFO);
                              resetWaitError += " ERROR: " + CurrentDateTime + " gateway returned false when waiting to Reset to be written, bWritten=" + QString::number(bWritten);
                              emit publishGatewayError(resetWaitError);
                              qDebug() << resetWaitError;
                          }
                          CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                          QString gatewayNonOpStr(Q_FUNC_INFO);
                          gatewayNonOpStr += " ERROR: " + CurrentDateTime + " gateway is not operational.";
                          emit publishGatewayError(gatewayNonOpStr);
                          qDebug() << gatewayNonOpStr;
                          emit publishGatewayIsNotOperational();
                          operationalCyclesSinceComms = 0;
                      }
                      else if (operationalCyclesSinceComms > operationalCyclesNoCommsSendTestCommandWarn)
                      {
                          QString cyclesSinceCommsStr(Q_FUNC_INFO);
                          cyclesSinceCommsStr += " WARNING: " + CurrentDateTime + " operationalCyclesSinceComms=" + QString::number(operationalCyclesSinceComms);
                          emit publishGatewayError(cyclesSinceCommsStr);
                          qDebug() << cyclesSinceCommsStr;
                      }
                  }
               } /* END  while (m_operational) */
              if (gateway.isOpen())
              {
                gateway.close();
              }
          } /* END if (m_operational) */
      } /* END while (m_attemptToBeOperational) */
  }  // END else m_portName is not empty

  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";

  emit this->gatewayOutput(response);
  emit this->gatewayClosed(); 
}

void GatewayThread::handleTerminate( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: begin ...";

    m_mutex.lock();
    m_attemptToBeOperational = false;
    m_commandsToGatewayList.clear();
    m_operational = false;
    m_mutex.unlock();

    qDebug() << Q_FUNC_INFO << " INFO: end ...";
}
