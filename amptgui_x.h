#ifndef AMPTGUI_X_H
#define AMPTGUI_X_H

#include <QWidget>
#include <QMessageBox>
#include <QMap>
#include "amptTimer.h"


#include "loggerThread.h"
#include "outputloggerthread.h"
#include "configurationThread.h"
#include "gatewayThread.h"
#include "receiveOTADataThread.h"
#include "parseOTADataThread.h"
#include "parseParameterBlockThread.h"
#include "parseGatewayParameterBlockThread.h"
#include "endDeviceParameterBlockInfoThread.h"
#include "checkGatewayCommandThread.h"
#include "gatewayValuesChangesTracked.h"
#include "endDeviceValuesChangesTracked.h"
#include "edSettingsValuesChangesTracked.h"
#include "protections1300VValueChangesTracked.h"

#include "powerCntrlValuesChangesTracked.h"
#include "linearCoeffsValueChangesTracked.h"
#include "tempCntrlValueChangesTracked.h"
#include "fineCntrlValuesChangesTracked.h"
#include "radioValueChangesTracked.h"

#include "screenshot.h"
#include "amptutilitiesdialog.h"
#include "batchCommandsThread.h"


namespace Ui {
class AmptGUI_X;
}

class AmptGUI_X : public QWidget
{
    Q_OBJECT


signals:
    void startSignal( void );
    void newMACDiscovered( const QString mac);
    void requestingAllEndDeviceParameterBlocks( const QString s );
    void requestingMACParameterBlock(const QString & s);
    void publishReadParameterBlockTimerStarted( void );
    void publishReadParameterBlockTimeout( void );
    void publishParametersAutoRead(bool);
    void publishClearCurrentEndDevicePBsAndLoadNewEDPBs( void );
    void publishFindStoredPBInfo(const QString s, const QString t);
    void publishEndDeviceSaveParameterBlockInfo(const bool);
    void publishError(const QString &s);
    void publishConfirmGatewayCommand(const QString &type, const QString &command);
    void publishValidateOnlyEndDeviceCommandToSend(const QString & commandToSend);
    void publishStartOutputRawFile(const QString &rawFilePathAndName);
    void publishStartOutputCSVFile(const QString &csvFilePathAndName);
    void publishStopOutputFiles(void);
    void publishUtilitiesBatchCommandsFile(const QString fileName);
    void publishCurrentActiveMAC(const QString currentActiveMAC);
    void publishLogCommandsToOutput(bool);
    void publishTerminate( void );

    void publishAllKnownMACs(QStringList s);

    void publishOneMACOTAData(QStringList s);

public:
    explicit AmptGUI_X(QWidget *parent = nullptr);
    ~AmptGUI_X();

public slots:
    void startLoggerSlot();
    void startConfigurationSlot();
    void startOutputLoggerSlot();
    bool startGatewaySlot();
    void startReceiveOTADataSlot();
    void startParseOTADataSlot();
    void startParseParameterBlockSlot();
    void startEndDeviceParameterBlockInfoSlot();
    void startParseGatewayParameterBlockSlot();
    void startCheckGatewayCommandSlot();
    void startBatchCommandsSlot();
    void startUpCommands();
    void configurationAtStart();
    void initializeGUI();
    void showGatewayResponse(const QString s);

    void showRawData(const QString& s);
    void showParsedOTAData(const QString& s, const QString& r);
    void enableCommandLinePushButton( const QString s );
    void sendGatewayCommandToGateway(const QString commandToSend);
    void sendCommandToGateway(const QString commandToSend );
    void sendCommandToGatewayFromCommandLine( void );
    void sendConfigurationCommandToGateway(const QString &command);
    void sendValidatedCommandToGateway(const QString &type, const QString & command);

    void handleClearCurrentEndDevicePBsAndLoadNewEDPBs( void );

    void handleGatewayIsOperational( void );
    void handleGatewayIsNotOperational( void );

    void handleCommandLineReturnPressed( void );

    void handleRadioButtonMACClicked(const bool s);
    void handleMACComboBoxChange(const QString & s);
    void handleRadioButtonBroadcastClicked(const bool s);
    void handleRadioButtonGroupClicked(const bool s);
    void handleRadioButtonNetworkClicked(const bool s);
    void handleRadioButtonGatewayClicked(const bool s);

    void handleCommandGroupBox(bool s);
    void handleAllRequestedParameterBlocksRead( void );

    void handleSaveSmallF( void );
    void handleSaveBigF(void );

    void handleScreenShotPushButton( void );
    void handleScreenShotQuitPushButton( void );

    void handleResetLinearCoeffs( void );
    void handleResetTempCntrl( void );
    void handleResetFineTuning( void );
    void handleResetRadio( void );
    void handleResetEDComms( void );
    void handleResetEDSettings( void );
    void handleResetKeys( void );
    void handleResetVersionInfo( void );
    void handleResetProtections( void );
    void handleResetOutput( void );
    void handleResetCoeffsLine( void );
    void handleResetGatewayWidgets( void );
    void handleResetGateway( void );
    void handleClearHistoryPushButton( void );

    void handleParametersReadReleased( void );
    void handleParametersWritePushButtonReleased( void );
    void handleParametersAutoRead( const QString & mac );
    void handleParametersAutoReadCheckBox(int state);

    void handleResendParameterBlockCommand(const QString & mac, const bool flash , const quint8 num);
    void handleGatewayParameterBlockData( const QString &s);


    void handleEndDeviceNewPBs(const QString & mac);
    void handleEndDeviceLinearKAndOffs(const QString & mac, const QString & family, const QString & linearKandOffs);
    void handleEndDeviceCommunicationsSettings(const QString & mac, const QString & edComms);
    void handleEndDeviceSettings(const QString & mac, const QString & edSettings);
    void handleEndDevicePowerCntrlSettings(const QString & mac, const QString & powerCntrl);
    void handleEndDeviceTempCntrlSettings(const QString & mac, const QString & tempCntrls);
    void handleEndDeviceFineTuningSettings(const QString & mac, const QString & fineTuning);
    void handleEndDeviceRadioSettings(const QString & mac, const QString & family, const QString & radio);
    void handleEndDeviceProtectionSettings(const QString & mac, const QString & family, const QString & pretectionsInfo);
    void handleEndDeviceVersionSettings(const QString & mac, const QString family, const QString & versionInfo);
    void handleEndDeviceKeySettings(const QString & mac, const QString & keyInfo);
    void handleEndDeviceParametersSavedToFile(const QString pbSaveToFile);

    void handleOTADataFormatSettings(const bool s);
    void handleConfigurationLongFormatOTAData(const int s);
    void handleConfigurationSuperCyclesInOutput(const int s);
    void handleConfigurationSaveParameterBlockCheckBox(int s);
    void handleNewMACDiscovered(const QString & mac);
    void handleConfigurationSave(const bool s);
    void handlePublishSavedConfiguration(const QStringList &config);

    void handleOTATableClicked(int row, int column);
    void handlePublishOtherGateways(const bool s);
    void handlePublishedErrors(const QString s);
    void handlePublishedInfo(const QString s);

    void handleGatewayChannelValueChanged(int channel);
    void handleGatewayGatewayAddressValueChanged(int gwAddr);
    void handleGatewayEndDeviceAddressValueChanged(int edAddr);
    void handleGatewayBunchSizeValueChanged(int bunchSize);
    void handleGatewayNetworkSizeValueChanged(int networkSize);
    void handleGatewayHoppingValueChanged(int hopping);
    void handleGatewayPowerValueChanged(QString power);
    void handleGatewaySyncwordValueChanged(int syncword);
    void handleGatewayModeValueChanged(int mode);
    void handleGatewayRepeatCommandValueChanged(int zCount);
    void handleGatewaySendPushButtonReleased( void );
    void handleGatewaySavePushButtonReleased( void );

    void handleEDCommsChannelValueChanged(int channel);
    void handleEDCommsGatewayAddressValueChanged(int s);
    void handleEDCommsEndDeviceAddressValueChanged(int s);
    void handleEDCommsBunchValueChanged(int s);
    void handleEDCommsNetIDValueChanged(int s);
    void handleEDCommsGroupValueChanged(int s);
    void handleEDCommsGBunchValueChanged(int s);
    void handleEDCommsRBunchValueChanged(int s);
    void handleEDCommsHoppingValueChanged(int s);
    void handleEDCommsRadioPowerValueChanged(int s);
    void handleEDCommsGWChannelFlagValueChanged(int s);
    void handleEDCommsSyncWordValueChanged(int s);
    void handleEDComms12KbodValueChanged(int s);
    void handleEDCommsStayInRXValueChanged(int s);
    void handleEDCommsStayInCWValueChanged(int s);
    void handleEDComms2RepeaterValueChanged(int s);
    void handleEDComms2RepeaterPowerValueChanged(int s);
    void handleEDComms2RepeaterChannelValueChanged(int s);
    void handleEDComms2SearchEnabledValueChanged(int s);
    void handleEDComms2CriticalLevel10ValueChanged(int s);
    void handleEDComms2SlaveValueChanged(int s);
    void handleEDComms2SlaveChannelValueChanged(int s);
    void handleEDComms2250KbodValueChanged(int s);
    void handleEDComms2CriticalLevel500ValueChanged(int s);
    void handleEDCommsSendPushButtonReleased( void );

    void handleEDSettingsSyncPhaseValueChanged(int s);
    void handleEDSettingsSyncFrequencyValueChanged(int s);
    void handleEDSettingsSendPushButtonReleased( void );
    void handleEDSettingsOVSetToSpinBoxChanged(int ovValue);
    void handleEDSettingsOCSetToSpinBoxChanged(int ocValue);

    void handleResetTextEditControls( void );

    void handleOVValueChangeFromSpinBox(int value);
    void handleOVValueChangeFromDial(int value);
    void handleOVSendPushButton( void );

    void handleOCValueChangeFromSpinBox(int value);
    void handleOCValueChangeFromDial(int value);
    void handleOCSendPushButton( void );

    void handleMPPValueChangeFromComboBox(int value);
    void handleMPPValueChangeFromDial(int value);
    void handleMPPSendPushButton( void );


    void handleModuleValueChangeFromComboBox(int value);
    void handleModuleValueChangeFromDial(int value);
    void handleModuleSendPushButton( void );

    void handleReadCoeffsPushButton( void );
    void handleEndDeviceReceivedCoeffLineData( void );
    void handleEndDeviceValidCoeffLineData(const QString macAndCoeffsData);

    void handleLinearCoeffsVOutCoefficientDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsVOutOffsetDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsVIn1CoefficientDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsVIn1OffsetDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsVIn2CoefficientDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsVIn2OffsetDoubleSpinBoxChange(const double value);

    void handleLinearCoeffsIOutCoefficientDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsIOutOffsetDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsIIn1CoefficientDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsIIn1OffsetDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsIIn2CoefficientDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsIIn2OffsetDoubleSpinBoxChange(const double value);

    void handleLinearCoeffsTextCoefficientDoubleSpinBoxChange(const double value);
    void handleLinearCoeffsTextOffsetDoubleSpinBoxChange(const double value);

    void handleLinearCoeffsSendPushButton( void );

    void handleTempCntrlOCProtectionSpinBoxChange(const int value);
    void handleTempCntrlTColdSpinBoxChange(const int value);
    void handleTempCntrlTHotSpinBoxChange(const int value);
    void handleTempCntrlTSuperHotSpinBoxChange(const int value);
    void handleTempCntrlFallbackTimeSpinBoxChange(const int value);
    void handleTempCntrlSendPushButton( void );


    void handlePowerCntrlVinTurnOnSpinBoxChange(const int value);
    void handlePowerCntrlVinStopRadioSpinBoxChange(const int value);
    void handlePowerCntrlVinLimit255SpinBoxChange(const int value);
    void handlePowerCntrlOVSpinBoxChange(const int value);
    void handlePowerCntrlOCSpinBoxChange(const int value);
    void handlePowerCntrlOVStartupSpinBoxChange(const int value);
    void handlePowerCntrlCurrentNoiseSpinBoxChange(const int value);
    void handlePowerCntrlOVStepSpinBoxChange(const int value);
    void handlePowerCntrlOCStepSpinBoxChange(const int value);
    void handlePowerCntrlModuleComboBoxChange(const QString & s);
    void handlePowerCntrlMPPComboBoxChange(const QString & s);

    void handlePowerCntrlSendPushButton( void );
    void handleSaveAllPushButton( void );
    void handleResetPowerCntrlWidgets( void );

    void handleFineTuningVRef0DoubleSpinBoxChange(const double value);
    void handleFineTuningKVRefDoubleSpinBoxChange(const double value);
    void handleFineTuningT0DoubleSpinBoxChange(const double value);
    void handleFineTuningTempCoeffCurrentDoubleSpinBoxChange(const double value);
    void handleFineTuningTempCoeffPowerDoubleSpinBoxChange(const double value);
    void handleFineTuningShortCircuitLevelSpinBoxChange(const int value);
    void handleFineTuningSendPushButton( void );


    void handleRadioDFK0DoubleSpinBoxChange(const double value);
    void handleRadioDFK1DoubleSpinBoxChange(const double value);
    void handleRadioDFK2DoubleSpinBoxChange(const double value);
    void handleRadioDFK3DoubleSpinBoxChange(const double value);
    void handleRadioPureOffsetSpinBoxChange(const int value);
    void handleRadioLowCurrentLimitTo255SpinBoxChange(const int value);
    void handleRadioSendPushButton( void );

    void handleNetworkDisbandNetworkPushButton( void );
    void handleNetworkEndOfTestPushButton( void );
    void handleNetworkEnableJoinPushButton( void );
    void handleNetworkDisableJoinPushButton( void );
    void handleNetworkNCommandArguments( QString text);
    void handleNetworkNCommandPushButton( void );

    void handleProtectionsFETFailureCountSpinBoxChange(const int );
    void handleProtectionsFETFailureThresholdSpinBoxChange( const int );
    void handleProtectionsFETFailureDeltaCurrentSpinBoxChange( const int );
    void handleProtectionsProtection1SpinBoxChange( const int );
    void handleProtectionsProtection2SpinBoxChange( const int );
    void handleProtectionsProtection3SpinBoxChange( const int );
    void handleProtectionsProtection4SpinBoxChange( const int );
    void handleProtections1300VAMFTimer1SpinBoxChange( const int );
    void handleProtections1300VAMFTimer2SpinBoxChange( const int );
    void handleProtections1300VAMFV_OVSpinBoxChange( const int );
    void handleProtections1300VAMFI_OCSpinBoxChange( const int );
    void handleProtectionsAMF_MPPCyclesOffSpinBoxChange(const int);
    void handleProtectionsAMF_MPPTimesOffSpinBoxChange(const int);

    void handleProtectionsEF_InputCurrentThresholdSpinBoxChange(const int);
    void handleProtectionsEF_OccurrenceThresholdSpinBoxChange(const int);
    void handleProtectionsEF_CountDownTimerSpinBoxChange(const int);
    void handleProtectionsEF_AlphaNumeratorSpinBoxChange(const int);

    void handleProtectionsIinLimitSpinBoxChange(const int);
    void handleProtectionsIinLimitOCStepsSpinBoxChange(const int);
    void handleProtectionsIinLimitOCDelaySpinBoxChange(const int);
    void handleProtectionsIinLimitTempAmbientAdjustSpinBoxChange( const int);

    void handleProtectionsAMF_DebugSpinBoxChange(const int);
    void handleProtectionsSendPushButton( void );

    void handleOptimizerFamilyChanged( const QString & mac, const int & familyShunt);
    void handleOptimizerFamilyChanged( const QString & family);

    void handleValidateCommandToCheck(const QString prompt, const QString command);

    void handleBeginReadingEndDeviceParameterBlock(const QString what);
    void handleReadingEndDeviceParameterBlockTimeout( const int timerID );
    void handleEndDeviceParameterBlockReadSuccessful( void );
    void handleEndDeviceOnMainImage(QString mac, bool s);

    void handleStartOutputPushButton( void );
    void handleStopOutputPushButton( void );
    void handleOutputReady( void );
    void handleCSVFileOpenFailed( const QString s);
    void handleRawFileOpenFailed( const QString s);

    void handleOutputSortOTATableRadioButtonNoneClicked( const bool s);
    void handleOutputSortOTATableRadioButtonSerialNumberClicked( const bool s);
    void handleOutputSortOTATableRadioButtonMACClicked( const bool s);
    void handleOutputSortOTATableRadioButtonNetworkClicked( const bool s);
    void handleOutputSortOTATableAscendingCheckBoxClicked(int s);


    void handleFilterOTADataByBunch( int state );
    void handleFilterOTADataByNetIDRange( int state );
    void handleFilterOTADataUnitsWithOVValue( int state );
    void handleFilterOTADataUnitsWithOCValue( int state );

    void handleResetAllTabTitles( void );

    void handleSimple();
    void handleOptimizerFamilyShunt(int s);

    void handleConfigurationSaveAmptGUI_XPushButton( void );

    void handleUtilitiesSelectSNOrMACValueChangedFromDial(int s);
    void handleUtilitiesSelectSNOrMACLineEdit(QString s);

    void handleUtilitiesUtilitiesDialogPushButton( void );
    void handleUtilitiesUtilitiesDialogClose( void );
    void handleUtilitiesGatewaySetupPushButton( void );

    void handleUtilitiesBatchCommandsSelectPushButton( void );
    void handlePublishBatchCommandsFileValidated( bool value);
    void handlePublishBatchCommandsFileOperationBegun( void );
    void handlePublishBatchCommandsFileOperationEnded( void );
    void handlePublishBatchCommandStatus(const QString status);


    void handleRequestAllKnownMACs( void );

    void handleBeginPublishOneMACOTAData(QString theMAC);
    void handleEndPublishOneMACOTAData( void );

    void closeEvent(QCloseEvent *event);


    // void receiveRawData(const QString& s);

private:
    Ui::AmptGUI_X *ui;
    LoggerThread m_loggerThread;
    outputLoggerThread m_outputLoggerThread;
    ConfigurationThread m_configurationThread;
    GatewayThread m_gatewayThread;
    ReceiveOTADataThread m_receiveOTADataThread;
    ParseOTADataThread m_parseOTADataThread;
    ParseParameterBlockThread m_parseParameterBlockThread;
    EndDeviceParameterBlockInfoThread m_endDeviceParameterBlockInfoThread;
    ParseGatewayParameterBlockThread m_parseGatewayParameterBlockThread;
    CheckGatewayCommandThread m_checkGatewayCommandThread;
    BatchCommandsThread m_batchCommandsThread;


    gatewayValuesChangesTracked * m_gatewayChangesTracked;
    edCommsValueChangesTracked * m_edCommsChangesTracked;
    edSettingsValueChangesTracked * m_edSettingsChangesTracked;
    powerCntrlValuesChangesTracked * m_powerCntrlChangesTracked;
    linearCoeffsValueChangesTracked * m_linearCoeffsChangesTracked;
    tempCntrlValueChangesTracked * m_tempCntrlValueChangesTracked;
    fineCntrlValueChangesTracked * m_fineTuningValueChangesTracked;
    radioValueChangesTracked * m_radioValueChangesTracked;
    protectionsValueChangesTracked * m_protectionsChangesTracked;

    QString m_currentActiveMAC;
    QString m_oneMACOTAData;

    int m_OTAClickedRow;
    bool saveAllParameters;
    QMessageBox * msgBox;
    amptTimer * m_parameterBlockThreadTimer;
    int m_parameterBlockThreadTimerID;
    int m_filteringOnBunch;
    bool m_filteringOnNetIDRange;
    int m_filteringNetIDStart;
    int m_filteringNetIDEnd;
    int m_filteringOutByOV;
    int m_filteringOutByOC;
    bool m_displayPowerDissapation;
    bool m_outputSortOTATableAscending;
    int  m_outputSortOTATableBy;

    Screenshot * m_ScreenShot;
    AmptUtilitiesDialog * m_utilitiesDialog;

    bool m_showGatewayResponseEnabled;

    bool validateAndSetConfigurationValue(const QString & configurationKey, int configurationValueType, QString & value);
    void initializeOTATableWidget( void );
    bool validSerialNumberSoFar(const QString s);
    bool validMACAddressSoFar(const QString s);
    void visibleEFFeatures( const bool visible );
    void visibleIinLimitFeatures( const bool visible);

};

#endif // AMPTGUI_X_H
