/****************************************************************************
**
****************************************************************************/

#ifndef PARSEPARAMETERBLOCKTHREAD_H
#define PARSEPARAMETERBLOCKTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QMap>

class ParseParameterBlockThread : public QThread
{
    Q_OBJECT

public:
    explicit ParseParameterBlockThread(QObject *parent = nullptr);
    ~ParseParameterBlockThread() override;

    void startParseParameterBlockThreadInterface(int waitTimeout, const bool logging);
    void stopParseParameterBlockThreadOperation( void );
	void setParseParameterBlockThreadLogging( bool logging );
    void setCurrentOptimizerFamily(QString s);
    void setParameterBlockReadFrom(const bool s);

signals:
    // void parsedOTAParameterBlockDataMessage(const QString &s);
    void publishEndDeviceParameterBlockReadSuccessful( void );
    void publishAllRequestedParameterBlocksRead( void );

    void publishPossibleAutoReadOfPB(const QString &s);

    void parsedCompleteParameterBlockDataFor(const QString &key, const QString &data240);
    void parsedCoeffLineFor(const QString & mac, const QString &coeffLineLine);
    void resendParameterBlockCommand(const QString &mac, const bool , const quint8);
	void parsedGatewayParameterBlockInformation( void ); // Should all data just be sent out?
    void parseParameterBlockThreadUnknownMessage( const QString s);
    void enableReadParameterBlocks( const bool );
    void validParameterBlockSCXLine(const QString s);
    void publishParseParameterBlockThreadError(const QString s);
    void publishParseParameterBlockThreadParseSCXError(const QString s);
    void publishParseParameterBlockThreadParseMACError(const QString s);
    void publishParseParameterBlockThreadParseDataError(const QString s);
    void publishRequestRunningImageForMAC(const QString &mac);
    void parseParameterBlockThreadExit();

public slots:
  void parseOTAParameterBlockData(const QString & data);
  void handleOTADataThreadCoeffsMessage( const QString s);

  void handleParseParameterBlockTimerStarted( void );
  void handleParseParameterBlockTimerExpired( void );

  void handleOptimizerFamilyChanged( const QString & s);
  void handleParametersReadFromChange( const bool s);
  void handleStartParameterBlockRead( void );
  void handleNewMACDiscovered(const QString & s);
  void handleRequestAllEndDeviceParameterBlocks( const QString s );
  void handleRequestMACParameterBlock(const QString & s);
  void handleParametersAutoRead(bool s);

private:
    void run() override;

    bool m_operational;
    QStringList m_otaParameterBlockDataToParseList;
    QStringList m_otaParameterBlockCoeffLineToParseList;

    int m_waitTimeout = 0;
    bool m_parameterBlockReadTimerRunning;

    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logData;
    QString m_currentOptimizerFamily;
    bool m_parametersReadFromFlash;
    bool m_newReadOfParameterBlock;
    int m_disableReadingParameterBlocksDuration;

    bool m_currentlyReadingParameterBlocks;
    bool m_parametersAutoRead;

    QMap < QString, int > m_macs;
    QMap < QString, int> m_expectedPBInformationForMAC;
    QMap < QString, bool > m_macsPBReadComplete;
    QMap<QString, QVector<QString> > m_pbData; // <MAC_FROM_TYPE, <SCX, data> >
};
#endif 
