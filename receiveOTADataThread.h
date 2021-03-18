/****************************************************************************
**
****************************************************************************/

#ifndef RECEIVEOTADATATHREAD_H
#define RECEIVEOTADATATHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>


class ReceiveOTADataThread : public QThread
{
    Q_OBJECT

public:
    explicit ReceiveOTADataThread(QObject *parent = nullptr);
    ~ReceiveOTADataThread() override;

    void startReceiveOTADataThreadInterface(int waitTimeout, const bool logging);
    void stopReceiveOTADataThreadOperation( void );
    void receiveOTADataThreadLogging( bool logging );

signals:
    void receivedOTADataThreadMessage(const QString s);
    void receivedOTADataThreadCoeffsMessage(const QString s);
    void receivedOTADataThreadParameterBlockMessage( const QString s);
    void receivedOTADataThreadGatewayParameterBlockMessage( const QString s);
    void receivedSuperCyclesMessage(const QString s);
    void publishReceivedOTADataThreadUnknownMessage( const QString s);
    void publishReceivedOTADataThreadError(const QString s);
    void publishOtherGatewayInformation(const QString s);
    void publishOtherGatewayObserved(const bool s);
    void receiveOTADataThreadExit();

public slots:
    void receiveOTAData(const QString data);
    void handleTerminate( void );
private:
    void run() override;

    bool m_operational;
    QStringList m_otaDataReceivedList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logData;
};
#endif 
