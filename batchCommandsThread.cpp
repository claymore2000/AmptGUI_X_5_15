/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


#include "batchCommandsThread.h"
#include "amptgui_x_status.h"

const QString formatIt("yyyy_MM_dd_HH_mm_ss");

BatchCommandsThread::BatchCommandsThread(QObject *parent) :
    QThread(parent), m_operational{true}, m_running{false}, m_validated{false},
    m_currentActiveMAC{""}, m_batchCommandsFileName{""},
    m_batchCommandsFile{nullptr}, m_batchCommandsStream{nullptr},
    m_numberOfBatchCommandLoopsToDo{0}, m_numberOfBatchCommandLoopsSoFar{0},
    m_currentIndexIntoBatchCommandsVector{0}
{
    m_batchCommands.clear();
}

BatchCommandsThread::~BatchCommandsThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void BatchCommandsThread::stopBatchCommandsThreadOperation( void )
{
    m_operational = false;
}

bool BatchCommandsThread::validateBatchFile(const QString fileName)
{
    bool retValue = false;
    qDebug() << Q_FUNC_INFO << " enter ..." << fileName;

    QString currentActiveMAC = m_currentActiveMAC;

    // First Open file, is readable?
    QString ErrorStr(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    qDebug() << Q_FUNC_INFO << " INFO: entering ...";

    if (m_batchCommandsFile == nullptr)
    {
        // QFileDevice::FileError err = QFileDevice::NoError;
        m_batchCommandsFile = new QFile(fileName);
        QString logFileDateTime(QDateTime::currentDateTime().toString(formatIt));

        if (!m_batchCommandsFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ErrorStr += " ERROR: " + CurrentDateTime + " failed to open raw log file " + fileName + ", error => " + m_batchCommandsFile->errorString() + ", batch commands setup failed.";
            qDebug() << ErrorStr;
            emit publishBatchCommandsThreadError(ErrorStr);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " INFO: opened batch commands file " << fileName;

            if (m_batchCommandsStream == nullptr)
            {
                m_batchCommandsStream = new QTextStream(m_batchCommandsFile);

                QString line;
                bool firstLine = true;
                bool noErrors = true;
                static const QString REQUIREDFIRSTLINE_STR{"^REPEAT_NUMBER="};
                static const QRegularExpression REQUIREDFIRSTLINE_RE(REQUIREDFIRSTLINE_STR);

                static const QString DELAY_STR{"^DELAY="};
                static const QRegularExpression DELAY_RE(DELAY_STR);

                static const QString REGISTER_STR{"^REG="};
                static const QRegularExpression REGISTER_RE(REGISTER_STR);

                static const QString VALUE_STR{"VALUE="};
                static const QRegularExpression VALUE_RE(VALUE_STR);

                static const QRegularExpression AMPT_VALUE_RE{"^[H|h|b|i|f][0|1-9][0-9]*"};

                static const QString SPECIFIED_MAC_STR{"^s[ ]+m[1-9|a-f|A-F][0-9|a-f|A-F]{11}[ ]+[1-9][0-9]*[ ]+[H|h|b|i|f][0|1-9][0-9]*"};
                static const QRegularExpression SPECIFIED_MAC_RE(SPECIFIED_MAC_STR);

                static const QString GATEWAY_COMMAND_STR{"^GATEWAY="};
                static const QRegularExpression GATEWAY_COMMAND_RE(GATEWAY_COMMAND_STR);

                static QRegularExpressionMatch match;
                QString optimizerCommandToAdd{""};

                m_numberOfBatchCommandLoopsToDo = 0;
                m_batchCommands.clear();

                while (m_batchCommandsStream->readLineInto(&line) && (noErrors == true))
                {
                  line = line.trimmed();
                  //qDebug() << Q_FUNC_INFO << " INFO: trimmed line is " << line << " first line is " << firstLine << " noErrors is " << noErrors;
                  if (line.length() == 0)
                  {
                      continue; // skip empty line
                  }

                  if (firstLine)
                  {
                      match = REQUIREDFIRSTLINE_RE.match(line);
                      if (match.hasMatch())
                      {
                          // qDebug() << Q_FUNC_INFO << " INFO: first line hasMatch";
                          if (line.length() > REQUIREDFIRSTLINE_STR.length() - 1)
                          {
                              line = line.mid(REQUIREDFIRSTLINE_STR.length() - 1);
                              line = line.trimmed();
                              // qDebug() << Q_FUNC_INFO << " first line value " << line;
                              m_numberOfBatchCommandLoopsToDo = line.toInt();
                          }
                          else
                          {
                              ErrorStr += " ERROR: " + CurrentDateTime + " failed parsing line length(" + QString::number(line.length()) + ") of first line " + line + " versus reference length" + QString::number(REQUIREDFIRSTLINE_STR.length() - 1);
                              qDebug() << ErrorStr;
                              emit publishBatchCommandsThreadError(ErrorStr);
                              noErrors = false;
                          }
                      }
                      else
                      {
                          ErrorStr += " ERROR: " + CurrentDateTime + " Required First Line of batch commands file missing... ";
                          qDebug() << ErrorStr;
                          emit publishBatchCommandsThreadError(ErrorStr);
                          noErrors = false;
                      }
                      firstLine = false;
                  }
                  else
                  {
                      match = DELAY_RE.match(line);
                      if (match.hasMatch())
                      {
                          if (line.length() > DELAY_STR.length() - 1)
                          {
                              line = line.mid(DELAY_STR.length() - 1);
                              line = line.trimmed();
                              // qDebug() << Q_FUNC_INFO << " INFO: would add delay " << line << " to batch commands.";
                              m_batchCommands.push_back(line);
                          }
                          else
                          {
                              ErrorStr += " ERROR: " + CurrentDateTime + " failed parsing (length) of delay line " + line;
                              qDebug() << ErrorStr;
                              emit publishBatchCommandsThreadError(ErrorStr);
                              noErrors = false;
                          }
                      }
                      else
                      {
                          match = REGISTER_RE.match(line);
                          if (match.hasMatch())
                          {
                              match = VALUE_RE.match(line);
                              if (match.hasMatch())
                              {
                                  //qDebug() << Q_FUNC_INFO << " INFO: REG line " << line;

                                  int blankIndex = line.indexOf(' ');
                                  if (blankIndex > 0)
                                  {
                                      QString amptRegister = line.mid(REGISTER_STR.length() -1, blankIndex - REGISTER_STR.length() + 1);
                                      // qDebug() << Q_FUNC_INFO << " INFO: register value is " << amptRegister <<  " registerStrLength " + QString::number(REGISTER_STR.length() - 1) +" blankIndex " << QString::number(blankIndex) + "::" + QString::number(blankIndex - REGISTER_STR.length() + 1);
                                      line = line.mid(blankIndex);
                                      line = line.trimmed();
                                      // qDebug() << Q_FUNC_INFO << "INFO: line now " << line;
                                      if (line.length() > VALUE_STR.length() -2) // At least one char{Hbih...} and at least one number
                                      {
                                          QString amptValue = line.mid(VALUE_STR.length());
                                          // qDebug() << Q_FUNC_INFO << "INFO: ampt value is " << amptValue;
                                          match = AMPT_VALUE_RE.match(amptValue);
                                          if (match.hasMatch())
                                          {
                                              // qDebug() << Q_FUNC_INFO << " INFO: valid value " << amptValue;

                                              if (m_currentActiveMAC.length() == 12)
                                              {
                                                  optimizerCommandToAdd = "s m"+ m_currentActiveMAC + " " + amptRegister + " " + amptValue;
                                              }
                                              else
                                              {
                                                  optimizerCommandToAdd = "s * " + amptRegister + " " + amptValue;
                                              }
                                              // qDebug() << Q_FUNC_INFO << " INFO: would add command " << optimizerCommandToAdd << " to batchCommands.";
                                              m_batchCommands.push_back(optimizerCommandToAdd);
                                          }
                                          else
                                          {
                                              ErrorStr += " ERROR: " + CurrentDateTime + " Invalid register value setting  " + amptValue;
                                              qDebug() << ErrorStr;
                                              emit publishBatchCommandsThreadError(ErrorStr);
                                              noErrors = false;
                                          }
                                      }
                                      else
                                      {
                                          ErrorStr += " ERROR: " + CurrentDateTime + " Invalid length of value portion  " + line;
                                          qDebug() << ErrorStr;
                                          emit publishBatchCommandsThreadError(ErrorStr);
                                          noErrors = false;
                                      }
                                  }
                                  else
                                  {
                                      ErrorStr += " ERROR: " + CurrentDateTime + " Incorrect format of (REG/VALUE) line " + line;
                                      qDebug() << ErrorStr;
                                      emit publishBatchCommandsThreadError(ErrorStr);
                                      noErrors = false;
                                  }
                              }
                              else
                              {
                                  ErrorStr += " ERROR: " + CurrentDateTime + " Required Keyword " + VALUE_STR + " missing from line " + line;
                                  qDebug() << ErrorStr;
                                  emit publishBatchCommandsThreadError(ErrorStr);
                                  noErrors = false;
                              }
                          }
                          else
                          {
                              match = SPECIFIED_MAC_RE.match(line);
                              if (match.hasMatch())
                              {
                                 // qDebug() << Q_FUNC_INFO << " INFO: would add full command " << line << " to batch commands.";
                                 m_batchCommands.push_back(line);
                              }
                              else
                              {
                                  match = GATEWAY_COMMAND_RE.match(line);
                                  if (match.hasMatch())
                                  {
                                      line = line.mid(GATEWAY_COMMAND_STR.length() - 1);
                                      line = line.trimmed();
                                      qDebug() << Q_FUNC_INFO << " INFO: would add gateway command " << line << " to batch commands.";
                                      m_batchCommands.push_back(line);
                                  }
                                  else
                                  {
                                      ErrorStr += " ERROR: " + CurrentDateTime + " Unmatched batch command line " + line;
                                      qDebug() << ErrorStr;
                                      emit publishBatchCommandsThreadError(ErrorStr);
                                      noErrors = false;
                                  }
                              }
                          }
                      }
                  }

                }

                if (noErrors)
                {
                    if (m_batchCommands.size() == 0)
                    {
                        ErrorStr += " ERROR: " + CurrentDateTime + " batch file has not commands in it. ";
                        qDebug() << ErrorStr;
                        emit publishBatchCommandsThreadError(ErrorStr);
                        m_numberOfBatchCommandLoopsToDo = 0;
                        m_batchCommands.clear();
                    }
                    else
                    {
                        for (QString aBatchCommand : m_batchCommands)
                        {
                            qDebug() << Q_FUNC_INFO << " a batch command: " << aBatchCommand;
                        }
                        // publish good to go
                        retValue = true;
                    }
                }
                else
                {
                    m_numberOfBatchCommandLoopsToDo = 0;
                    m_batchCommands.clear();
                }

                m_batchCommandsStream->flush();
                delete m_batchCommandsStream;
                m_batchCommandsStream = nullptr;

                m_batchCommandsFile->flush();
                m_batchCommandsFile->close();
                delete(m_batchCommandsFile);
                m_batchCommandsFile = nullptr;
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " request to log raw data but already logging (stream not nullptr), stopping logging...";
                qDebug() << ErrorStr;
                emit publishBatchCommandsThreadError(ErrorStr);
            }
        }
    }
    else
    {
        ErrorStr += " ERROR: request to setup batch command but already setup (file not nullptr), cleaning up and exiting";
        qDebug() << ErrorStr;
        emit publishBatchCommandsThreadError(ErrorStr);
     }
     qDebug() << Q_FUNC_INFO << " INFO: exiting ...";

    return retValue;
}

void BatchCommandsThread::handlePublishCurrentActiveMAC(const QString currentActiveMAC)
{
      qDebug() << Q_FUNC_INFO << " enter ..." << currentActiveMAC;
      m_currentActiveMAC = currentActiveMAC;
}

void BatchCommandsThread::handlePublishBatchFileToValidate(const QString fileName)
{
  qDebug() << Q_FUNC_INFO << " enter ..." << fileName;

  QString errString(Q_FUNC_INFO);
  QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
  bool goodToGo = validateBatchFile(fileName);

  if (goodToGo)
  {
      emit publishBatchCommandsFileValidated(true);
  }
  else
  {
      errString += " ERROR: " + CurrentDateTime + " batchCommands file " + fileName + " failed validation.";
      emit publishBatchCommandsThreadError(errString);
      emit publishBatchCommandsFileValidated(false);
  }

}

void BatchCommandsThread::handlePublishBatchFileStartStop( void )
{
  // qDebug() << Q_FUNC_INFO << " enter ... m_running is " << m_running;

  const QMutexLocker locker(&m_mutex);
  m_running = !m_running;

  // qDebug() << Q_FUNC_INFO << " flipped? ... m_running is " << m_running;

  if (m_running)
  {
      m_running = true;
      m_numberOfBatchCommandLoopsSoFar = 0;
      m_currentIndexIntoBatchCommandsVector = 0;
      emit publishBatchCommandsFileOperationBegun();
  }
  else
  {
      m_running = false;
      m_numberOfBatchCommandLoopsSoFar = 0;
      m_currentIndexIntoBatchCommandsVector = 0;
      emit publishBatchCommandsFileOperationEnded();

      QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
      QString infoString(Q_FUNC_INFO);
      QString statusString = CurrentDateTime + " terminated by user.";
      infoString += " INFO: Batch operation " + statusString;
      emit publishBatchCommandStatus(statusString);
      emit publishBatchCommandsThreadError(infoString);
  }
}

void BatchCommandsThread::handlePublishTerminate( void )
{
  qDebug() << Q_FUNC_INFO << " enter ...";
  if (m_running)
  {
     emit publishBatchCommandsFileOperationEnded();
  }
  const QMutexLocker locker(&m_mutex);
  m_running = false;
  m_numberOfBatchCommandLoopsSoFar = 0;
  m_currentIndexIntoBatchCommandsVector = 0;
  m_operational = false;
  m_batchCommands.clear();
    qDebug() << Q_FUNC_INFO << " exit ...";
}

void BatchCommandsThread::startBatchCommandsThreadInterface(int waitTimeout)
{
    const QMutexLocker locker(&m_mutex);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    qDebug() << Q_FUNC_INFO << CurrentDateTime << " starting thread interface ...";

    m_waitTimeout = waitTimeout;
    m_operational = true;

    if (!isRunning())
      start();
    else
      m_cond.wakeOne();

    qDebug() << Q_FUNC_INFO << " exiting ...";
}

void BatchCommandsThread::run()
{
  qDebug() << Q_FUNC_INFO << " running ...";
  static const QString SPECIFIED_OPTIMIZER_COMMAND_START_STR{"^s[ ]"};
  static const QRegularExpression SPECIFIED_OPTIMIZER_COMMAND_START_RE(SPECIFIED_OPTIMIZER_COMMAND_START_STR);
  static const QString SPECIFIED_DELAY_TIME_STR{"^[1-9][0-9]*"}; // if all digits, a delay time and not a gateway command
  static const QRegularExpression SPECIFIED_DELAY_TIME_RE(SPECIFIED_DELAY_TIME_STR);

  static QRegularExpressionMatch match;

  while (m_operational) 
  {
    QThread::msleep(720);
    m_mutex.lock(); // acquire mutex before checking m_running, if running hold mutex til end, if not running let it go ASAP
                    // NOTE: m_operational can change from other methods in this thread but means thread is exiting ...

    if (m_running)
    {
        if (m_numberOfBatchCommandLoopsSoFar < m_numberOfBatchCommandLoopsToDo)
        {
            if (m_currentIndexIntoBatchCommandsVector < static_cast<unsigned int>(m_batchCommands.size()))
            {
                QString status = "Loop:" + QString::number(m_numberOfBatchCommandLoopsSoFar + 1) + " command# " + QString::number(m_currentIndexIntoBatchCommandsVector + 1) + " => ";
                QString currentCommand = m_batchCommands.at(m_currentIndexIntoBatchCommandsVector++);
                match = SPECIFIED_OPTIMIZER_COMMAND_START_RE.match(currentCommand);
                if (match.hasMatch())
                {
                    // qDebug() << Q_FUNC_INFO << " sending command " << currentCommand << "to gateway.";
                    emit publishBatchCommandToGateway(currentCommand);
                    status += currentCommand;
                    emit publishBatchCommandStatus(status);
                }
                else
                {
                    match = SPECIFIED_DELAY_TIME_RE.match(currentCommand);
                    if (match.hasMatch())
                    {
                        // A delay command
                        // qDebug() << Q_FUNC_INFO << " sleep for " << currentCommand << " microseconds";
                        status += "DELAY=" + currentCommand;
                        emit publishBatchCommandStatus(status);
                        QThread::msleep(currentCommand.toInt());
                    }
                    else // 3rd option is a gateway command, send it on up
                    {
                        emit publishBatchCommandToGateway(currentCommand);
                        status += currentCommand;
                        emit publishBatchCommandStatus(status);
                    }
                }
            }
            else
            {
                m_currentIndexIntoBatchCommandsVector = 0;
                m_numberOfBatchCommandLoopsSoFar++;
                // qDebug() << Q_FUNC_INFO << " INFO: currentIndex:" << m_currentIndexIntoBatchCommandsVector << " Loops so far:" << m_numberOfBatchCommandLoopsSoFar << " To Do:" << m_numberOfBatchCommandLoopsToDo;
            }
        }
        else
        {
            QString endStatus = " Completed " + QString::number(m_numberOfBatchCommandLoopsToDo) + " cycles of commands";
            emit publishBatchCommandStatus(endStatus);
            m_running = false;
            m_numberOfBatchCommandLoopsSoFar = 0;
            m_currentIndexIntoBatchCommandsVector = 0;
            emit publishBatchCommandsFileOperationEnded();
            // qDebug() << Q_FUNC_INFO << " INFO: finished batch commands";
        }
        m_mutex.unlock();
    }
    else
    {
      m_mutex.unlock();
      QThread::msleep(1000);
      // qDebug() << Q_FUNC_INFO << " no data " << Qt::endl;
    }
  }
  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";
}

