/****************************************************************************
**
****************************************************************************/

#ifndef __CHECKGATEWAYCOMMANDTHREAD_H__
#define __CHECKGATEWAYCOMMANDTHREAD_H__

#include <QMutex>
#include <QThread>
#include <QWaitCondition>


class CheckGatewayCommandThread : public QThread
{
    Q_OBJECT

public:
    explicit CheckGatewayCommandThread(QObject *parent = nullptr);
    ~CheckGatewayCommandThread();

    void startCheckGatewayCommandThreadInterface(int waitTimeout, const bool logging);
    void stopCheckGatewayCommandThreadOperation( void );
	void setCheckGatewayCommaondThreadLogging( bool logging );

signals:
    void checkGatewayCommandThreadError(const QString &s);
    void checkGatewayCommandThreadExit();

public slots:
  void handleCheckingAGatewayCommand(const QString & type, const QString & command);

private:
    void run() override;

    bool m_operational;
    QStringList m_gatewayCommandsToValidateList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logData;
};
#endif 
