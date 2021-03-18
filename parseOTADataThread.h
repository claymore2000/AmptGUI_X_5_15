/****************************************************************************
**
****************************************************************************/

#ifndef PARSEOTADATATHREAD_H
#define PARSEOTADATATHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>


class ParseOTADataThread : public QThread
{
    Q_OBJECT

public:
    explicit ParseOTADataThread(QObject *parent = nullptr);
    ~ParseOTADataThread() override;

    void startParseOTADataThreadInterface(int waitTimeout, const bool logging);
    void stopParseOTADataThreadOperation( void );
	void parseOTADataThreadLogging( bool logging );
    void setCurrentOptimizerFamily(QString s);
    void setParameterBlockReadFrom(const bool s);

signals:
    void parsedOTADataThreadRawMessage(const QString s, const QString r);
    void publishOnMainImage(const QString mac, const bool s);
    void publishReceivedOTADataThreadUnknownMessage( const QString s);
    void publishParseOTADataThreadError(const QString  s);
    void parseOTADataThreadExit();

public slots:
    void parseOTAData(const QString data);
    void handleOptimizerFamilyChanged( const QString s);
    void handleMemoryToFromLocationChanged( const bool s);
    void handleRequestRunningImageForMAC(const QString mac);
    void handlePublishedEndDeviceOptimizerFamily(const QString mac, const int familyShunt);
    void handleTerminate( void );
private:
    void run() override;
    void setVoltageMultiplier(const QString s);

    bool m_operational;
    QStringList m_otaDataToParseList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logData;
    QString m_currentOptimizerFamily;
    bool m_parametersReadFrom;
    int m_voltageMultiplier;
};
#endif 
