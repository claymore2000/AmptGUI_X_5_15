/****************************************************************************
**
****************************************************************************/

#ifndef LOGGERTHREAD_H
#define LOGGERTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QFile>


class LoggerThread : public QThread
{
    Q_OBJECT

public:
    explicit LoggerThread(QObject *parent = nullptr);
    ~LoggerThread() override;

    void startLoggerThreadInterface(int waitTimeout, QString & directoryPath);
    void stopLoggerThreadOperation( void );
	void LoggerThreadLogging( bool logging );

signals:
    void publishLoggerThreadError(const QString s);
    void receiveLoggerThreadError(const QString s);
    void receiveLoggerThreadExit();

public slots:
    void receiveDataToLog(const QString data);
private:
    void run() override;

    bool m_operational;
    QStringList m_dataToLogList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    QFile *m_loggerFile;
};

#endif 
