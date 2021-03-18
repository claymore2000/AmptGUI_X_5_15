/****************************************************************************
**
****************************************************************************/

#ifndef PARSEGATEWAYPARAMETERBLOCKTHREAD_H
#define PARSEGATEWAYPARAMETERBLOCKTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QMap>

class ParseGatewayParameterBlockThread : public QThread
{
    Q_OBJECT

public:
    explicit ParseGatewayParameterBlockThread(QObject *parent = nullptr);
    ~ParseGatewayParameterBlockThread() override;

    void startParseGatewayParameterBlockThreadInterface(int waitTimeout, const bool logging);
    void stopParseGatewayParameterBlockThreadOperation( void );
	void setParseGatewayParameterBlockThreadLogging( bool logging );


signals:
    void parsedGatewayParameterBlockInformation( const QString & );
    void publishParseGatewayParameterBlockThreadError(const QString &s);
    void parseGatewayParameterBlockThreadExit();

public slots:
  void parseGatewayParameterBlockData(const QString & data);
  void handleTerminate( void );

  //void requestToParseGatewayParameterBlockData(const QStringList & s); // MACor*,From, Type
private:
    void run() override;
    bool obtainZCountLineData(const QString & s);
    bool obtainVersionLineData(const QString & s);
    bool obtainDataRateLineData(const QString &s);
    bool obtainUTCLineData(const QString &s);
    bool obtainMACLineData(const QString &s);
    bool obtainSyncwordLineData(const QString &s);
    void constructAndPublishGatewayPBList(void);


    bool m_operational;
    QStringList m_gatewayParameterBlockDataToParseList;

    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logData;
    QMap<QString, QString> m_gatewayPBData; // <GatewayPBName, Value>
};
#endif 
