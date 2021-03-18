/****************************************************************************
**
****************************************************************************/

#ifndef GATEWAYTHREAD_H
#define GATEWAYTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>


class GatewayThread : public QThread
{
    Q_OBJECT

public:
    explicit GatewayThread(QObject *parent = nullptr);
    ~GatewayThread() override;

    void commandToSend(const QString command);
	void setupGateway( void );
    void startGatewayInterface(const QString portName, int waitTimeout, const bool logging);
    void stopOperation( void );
	void logging( bool logging );
    bool isOperational( void );
    void resetGateway( void );

signals:
    void publishGatewayIsOperational( void );
    void publishGatewayIsNotOperational( void );
    void gatewayOutput(const QString s);
    void publishCommandToLog(const QString commandData);
    void publishGatewayError(const QString s);
    void timeout(const QString s);
	void gatewayClosed();

public slots:
    void handleGatewayCommandToSend(const QString command);
    void handleOutputIncludeCommandsInLog(bool);
    void handleTerminate( void );

private:
    void run() override;

    bool m_operational;
    bool m_attemptToBeOperational;
    QStringList m_commandsToGatewayList;

    QString m_portName;
    QString m_request;
    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logTraffic;
    bool m_includeCommandsInLog;

};
#endif 
