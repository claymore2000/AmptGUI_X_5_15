/****************************************************************************
**
**
****************************************************************************/

#include <QDebug>

#include "amptPreUSBSetupThread.h"


AmptPreUSBSetupThread::AmptPreUSBSetupThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true;
    m_scriptToRun = "sudo ./bringUpGateway";
    m_argumentList.clear();
}

AmptPreUSBSetupThread::~AmptPreUSBSetupThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void AmptPreUSBSetupThread::preSetupForUSBGateway( void )
{
}

void AmptPreUSBSetupThread::success( bool good )
{
}

void AmptPreUSBSetupThread::logging( bool logging )
{
  m_logging = logging;
}

void AmptPreUSBSetupThread::startPreUSBThread(int waitTimeout, const bool logging)
{
    const QMutexLocker locker(&m_mutex);
    m_waitTimeout = waitTimeout;
	m_logging = logging;
	m_operational = true;

	if (m_logging)
	  {
		// Create name, try to open for write,
	  }

    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}


void AmptPreUSBSetupThread::run()
{
  m_mutex.lock();

  m_mutex.unlock();

  qDebug() << Q_FUNC_INFO << " starting run()";

  if (m_scriptToRun.isEmpty())
	{
      qDebug() << Q_FUNC_INFO << " ERROR: Process to setup USB Gateway failed, script not specified.";
	  emit error(tr("ERROR: Process to setup USB Gateway failed, script not specified."));
      emit preUSBSetupFailed("ERROR: Process to setup USB Gateway failed, script not specified.");
	  m_operational = false;
	}
  else
	{
      qDebug() << Q_FUNC_INFO << " else ...";

      m_setupUSB.start(m_scriptToRun,m_argumentList);

      qDebug() << Q_FUNC_INFO << " after start ...";

      bool notDone = false;
  
      if (!m_setupUSB.waitForStarted())
      {
          qDebug() << Q_FUNC_INFO << " ERROR: Process to setup USB Gateway failed, waitForStart Failure.";
          emit error(tr("ERROR: Process to setup USB Gateway failed, waitForStart failure."));
          emit preUSBSetupFailed("ERROR: Process to setup USB Gateway failed, waitForStart failure.");
          m_operational = false;
      }
      else
		{ 
          qDebug() << Q_FUNC_INFO << " before while loop 1.";
          char scriptOutput[512];
		  m_setupUSB.waitForFinished(); // sets current thread to sleep and waits for m_setupUSB to end.
          m_setupUSB.setReadChannel(QProcess::StandardOutput);
          qDebug() << Q_FUNC_INFO << " before while loop 2.";

             while ((m_operational) && (notDone == false))
			   {
                 if (m_setupUSB.waitForReadyRead(m_waitTimeout))
                   {
                     QByteArray scriptData = m_setupUSB.readAll();
                     while (m_setupUSB.waitForReadyRead(10))
                       scriptData += m_setupUSB.readAll();

                     QString response = QString::fromUtf8(scriptData);
                     qDebug() << Q_FUNC_INFO << " " << response;
                 }
                 else
                 {
                     QThread::msleep(1000);
                     qDebug() << Q_FUNC_INFO << " no data, sleeping ...";
                 }
             }
      }
  }

  QString response("");
  emit this->processClosed();

}
