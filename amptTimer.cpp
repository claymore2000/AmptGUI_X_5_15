#include <QDebug>
#include <QString>

#include "amptTimer.h"

static const int defaultTimerDuration = 10000;

amptTimer::amptTimer( void )
{
  timer = new QTimer(this);
  m_duration = defaultTimerDuration;
  timer->setSingleShot(false);
  timer->setInterval(m_duration);
  timer->stop();
  m_timerID = -1;

  connect(timer, SIGNAL(timeout()), this, SLOT(amptTimerSlot()));

  // qDebug() << Q_FUNC_INFO << " Timer: single shot:" << false << " and duration:" << m_duration << " not running.";

}

amptTimer::amptTimer(bool singleShot)
{
  timer = new QTimer(this);
  timer->setSingleShot(singleShot);
  m_duration = defaultTimerDuration;
  timer->setInterval(m_duration);
  timer->stop();
  m_timerID = -1;

  connect(timer, SIGNAL(timeout()), this, SLOT(amptTimerSlot()));

  // qDebug() << Q_FUNC_INFO << " Timer: single shot:" << singleShot << " and duration:" << m_duration << " not running.";

}

amptTimer::amptTimer(bool singleShot, int durationInMS)
{
  timer = new QTimer(this);
  timer->setSingleShot(singleShot);
  m_duration = durationInMS;
  timer->setInterval(m_duration);
  timer->stop();
  m_timerID = -1;

  connect(timer, SIGNAL(timeout()), this, SLOT(amptTimerSlot()));

  // qDebug() << Q_FUNC_INFO << " Timer: single shot:" << singleShot << " and duration:" << m_duration << " not running.";

}


void amptTimer::setInterval(int durationInMS)
{
  if (durationInMS > 0)
  {
      m_duration = durationInMS;
      timer->setInterval(m_duration);
  }
  else
  {
      qDebug() << Q_FUNC_INFO << " requested duration less than 0, using " << defaultTimerDuration << " milliseconds.";
      m_duration = defaultTimerDuration;
      timer->setInterval(m_duration);
  }
}
void amptTimer::setSingleShot(bool singleShot)
{
    timer->setSingleShot(singleShot);
}

void amptTimer::setIntervalAndStart(int durationInMS)
{
    if (durationInMS > 0)
      timer->setInterval(durationInMS);
    else
    {
        qDebug() << Q_FUNC_INFO << " requested duration less than 0, using 10000 milliseconds.";
        timer->setInterval(10000);
    }
    timer->start();
    m_timerID = timer->timerId();

}

void amptTimer::amptTimerSlot( void )
{
    QString ErrorStr(Q_FUNC_INFO);
    ErrorStr += "!!!! WARNING: amptTimer timeout signal received for timerID:" + QString::number(m_timerID);
    qDebug() << ErrorStr;

    emit amptTimerExpired(m_timerID);
}

