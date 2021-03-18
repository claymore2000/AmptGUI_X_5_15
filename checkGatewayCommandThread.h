/****************************************************************************
**
****************************************************************************/

#ifndef CHECKGATEWAYCOMMANDTHREAD_H
#define CHECKGATEWAYCOMMANDTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>


class CheckGatewayCommandThread : public QThread
{
    Q_OBJECT

public:
    explicit CheckGatewayCommandThread(QObject *parent = nullptr);
    ~CheckGatewayCommandThread() override;

    void startCheckGatewayCommandThreadInterface(int waitTimeout, const bool logging);
    void stopCheckGatewayCommandThreadOperation( void );
    void setCheckGatewayCommandThreadLogging( bool logging );

signals:
    void publishValidateCommandToUser(const QString prompt, const QString command);
    void validatedCommand(const QString s);
    void checkGatewayCommandThreadError(const QString &s);
    void checkGatewayCommandThreadExit();

public slots:
  void handleCheckingAGatewayCommand(const QString & type, const QString & command);
  void handleValidatingFormatOfEndDeviceCommand(const QString & command);
  void handleTerminate( void );

private:
    void run() override;

    bool confirmByteRegisterNumberAndValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & s);
    bool confirmShortIntegerRegisterNumberAndValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & s);
    bool confirmFloatRegisterNumberAndValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & s);
    bool validateCommandTypeAndRegisterAndRegisterValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & s);
    void validateCommandToGateway(QString s);
    bool validateRegisterType(const QString registerType);
    bool validateRegisterNumberForType(int indexIntoCommand, QString s, QString & properlyFormedCommandString, QString & amptRegisterNumber, QString & amptRegisterType, QString & amptRegisterValue);
    bool validateCommandFormatToEndDevice(QString s, QString & properlyFormedCommandString, QString & amptAddressType, QString & amptRegisterNumber, QString & amptRegisterType, QString & amptRegisterTypeValue);
    void confirmCommandToEndDevice(QString s);

    bool m_operational;
    QStringList m_gatewayCommandsToValidateList;
    QStringList m_endDeviceCommandsToValidateList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logData;
};
#endif 
