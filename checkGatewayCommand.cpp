/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QDebug>

#include "checkGatewayCommandThread.h"

CheckGatewayCommandThread::CheckGatewayCommandThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true;
}

CheckGatewayCommandThread::~CheckGatewayCommandThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void CheckGatewayCommandThread::stopCheckGatewayCommandThreadOperation( void )
{
    m_operational = false;
}


void CheckGatewayCommandThread::startCheckGatewayCommandThreadInterface(int waitTimeout, const bool logging)
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

void CheckGatewayCommandThread::handleCheckingAGatewayCommand(const QString & type, const QString & command)
{
  qDebug() << Q_FUNC_INFO << " queuing command type " << type << " and command " << command;
  QString toCheck = type + "," + command;

  m_gatewayCommandsToValidateList.append(toCheck);
  qDebug() << Q_FUNC_INFO << " queued " << toCheck;
}


void CheckGatewayCommandThread::run()
{

  while (m_operational) 
	{

	}

  emit this->checkGatewayThreadExit();
  
}

void CheckGatewayCommandThread::setCheckGatewayCommandThreadLogging( bool logging )
{
}
