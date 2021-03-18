/****************************************************************************
**
****************************************************************************/

#ifndef AMPTENDDEVICEPARAMETERBLOCKINFOTHREAD_H
#define AMPTENDDEVICEPARAMETERBLOCKINFOTHREAD_H


#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QStringList>
#include <QHash>

#include "amptTimer.h"

class EndDeviceParameterBlockInfoThread : public QThread
{
    Q_OBJECT

public:
    explicit EndDeviceParameterBlockInfoThread(QObject *parent = nullptr);
    ~EndDeviceParameterBlockInfoThread() override;

    void startEndDeviceParameterBlockInfoThreadInterface(int waitTimeout, const bool logging, QString docsDirectoryPath);
    void stopEndDeviceParameterBlockInfoThreadOperation( void );
	void setEndDeviceParameterBlockInfoThreadLogging( bool logging );
    void setCurrentOptimizerFamily(QString s);
    void setParameterBlockReadFrom(const bool s);

signals:
    void publishEndDeviceNewPBs(const QString & mac);
    void publishEndDeviceLinearKandOffs(const QString & mac, const QString & family, const QString & linearKandOffs);
    void publishEndDeviceCommunicationSettings(const QString &mac ,const QString & edComms);
    void publishEndDeviceSettings(const QString &mac, const QString & edSettings);
    void publishEndDevicePowerCntrlSettings(const QString &mac, const QString & ctrlVolts);
    void publishEndDeviceTempCntrlSettings(const QString & mac, const QString & tempCntrl);
    void publishEndDeviceFineTuningSettings(const QString & mac, const QString & fineTuning);
    void publishEndDeviceRadioSettings(const QString & mac, const QString & family, const QString & radio);
    void publishEndDeviceVersionSettings(const QString & mac, const QString family, const QString & versionInfo);
    void publishEndDeviceProtectionSettings(const QString & mac, const QString & family, const QString & protectionInfo);
    void publishEndDeviceKeySettings(const QString & mac, const QString & keyInfo);
    void publishEndDeviceOptimizerFamily(const QString & mac, const int & familyShunt);
    void publishEndDeviceOnMainImage(QString mac, bool s);
    void publishEndDeviceParametersSavedToFile(QString pbFileName);

    void publishEndDeviceParameterBlockInfoThreadError(const QString &s);
    void publishEndDeviceParameterBlockInfoThreadFamilyError(const QString &s);
    void publishEndDeviceParameterBlockInfoThreadFlashError(const QString &s);
    void publishEndDeviceParameterBlockInfoThreadExit();
    void publishOptimizerFamilyShunt(int s);
    void publishEndDeviceReceivedCoeffLineData( void );
    void publishEndDeviceValidCoeffLineData(const QString macAndCoeffsData);



public slots:
  void handleCompleteEndDeviceParameterBlockInfoAvailable(const QString & key, const QString & data240);
  void handleEndDeviceCoeffLineAvailable(const QString & mac, const QString & coeffLine);
  void handleSelectedMACChange(const QString & theMAC);
  void handleOptimizerFamilyChanged( const QString & s);
  void handleParametersReadFromChange( const bool s);
  void handleOnMainImage(const QString & mac, const bool s);
  void handleFindStoredPBInfo(const QString s, const QString t);
  void handleEndDeviceSaveParameterBlockInfoSignal(const bool s);
  void handleTerminate( void );

private:
    void run() override;
    bool validateAndPlaceParameterBlockValues(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool validateCorrectFamilyBasedOnShunt(QStringList & optimizerKey, const int & shunt);
    bool endDeviceParameterBlockInfo1500V_2nd(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceParameterBlockInfo1500V(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceParameterBlockInfo1500V_30(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceParameterBlockInfo1300V(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceParameterBlockInfo1300V_2nd(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceParameterBlockInfo1000V(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceParameterBlockInfo600V_V2(QStringList &macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceParameterBlockInfo600V_V2_2nd(QStringList & macFlashFamily, QString & justTheData, const int tShunt);
    bool endDeviceSaveParameterBlockInfo(const QString & s );
    bool endDeviceWriteParameterBlockInfoAsCharacterDataToFile(const QString &s,const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite600V_V2ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite600V_V2_2ndParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite1000VParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite1300VParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite1300V_2nd_ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite1500VParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite1500V_2nd_ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool endDeviceWrite1500V_30ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo);
    bool validateCoeffLineData(const QString mac, const QString coeffLine);


    bool m_operational;
    QStringList m_parsedParameterBlockDataList;
    QStringList m_parsedCoeffLineDataList;
    QString m_pbKeyAndData;
    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
	bool m_logData;
    QString m_currentOptimizerFamily;
	QString m_currentMAC;
    QHash<int, QString> m_optimizerFamilies;
    bool m_parametersReadFromFlash;
    bool m_saveParameterBlockInfo;
    QString m_saveParameterBlockPathBase;
    // LBC bool m_newReadOfParameterBlock;
};
#endif 
