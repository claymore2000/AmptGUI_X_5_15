#ifndef __AMPTPREUSBSETUPTHREAD_H__
#define __AMPTPREUSBSETUPTHREAD_H__

#include <QThread>
#include <QProcess>
#include <QMutex>
#include <QWaitCondition>
#include <QString>
#include <QStringList>

class AmptPreUSBSetupThread : public QThread
{
  Q_OBJECT

 public:
    explicit AmptPreUSBSetupThread(QObject *parent = nullptr);
    ~AmptPreUSBSetupThread();
	void preSetupForUSBGateway( void );
    void startPreUSBThread(int waitTimeout, const bool logging);
    void success( bool good );
	void logging( bool logging );

signals:
    void preUSBSetupFailed( const QString &);
    void stopOperation( void );
    void error(const QString &s);
    void timeout(const QString &s);
    void outcome(const bool s);
	void processClosed( void );

private:
    void run() override;

    QProcess m_setupUSB;
    bool m_operational;
    QString m_scriptToRun;
    QStringList m_argumentList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_logging;

};

#endif
