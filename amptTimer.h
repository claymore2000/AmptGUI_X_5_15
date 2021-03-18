#ifndef __AMPTTIMER_H__
#define __AMPTTIMER_H__

#include <QTimer>

class amptTimer : public QObject
{
  Q_OBJECT

signals:
    void amptTimerExpired( const int timerID );

 public:
  amptTimer();
  amptTimer(bool singleShot);
  amptTimer(bool singleShot, int durationInMS);
  void setSingleShot(bool singleShot);
  void setInterval(int durationInMS);
  void setIntervalAndStart(int durationInMS);

  QTimer *timer;

  public slots:
	void amptTimerSlot( void );

private:
    int m_duration;
    int m_timerID;

};

#endif
