#include <QSysInfo>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <QStringRef>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QStandardItem>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTextEdit>

#include <QApplication>
#include <QDesktopWidget>


#include "amptgui_x.h"
#include "amptgui_x_utilities.h"
#include "amptNamedIndexes.h"
#include "amptNamedLimits.h"
#include "amptRegisterConstants.h"
#include "ui_amptgui_x.h"
#include "amptparameterblockconstants.h"
#include "gatewayParameterBlockKeyNames.h"
#include "amptConfigurationKeys.h"
#include "screenshot.h"


static const QString formatIt("yyyy/MM/dd hh:mm:ss");
static QMap<QString, QString> mainImage;

static const int SerialNumIndex = 0;
static const int MACIndex = 1 + OTA_MAC_INDEX;
static const int TimeIndex = 1 + OTA_Time_INDEX ;
static const int Vin1Index = 1 + OTA_VIn1_INDEX;
static const int Vin2Index = 1 + OTA_VIn2_INDEX;
static const int VoutIndex = 1 + OTA_VOut_INDEX;
static const int Iin1Index = 1 + OTA_IIn1_INDEX;
static const int Iin2Index = 1 + OTA_IIn2_INDEX;
static const int IoutIndex = 1 + OTA_IOut_INDEX;
static const int PowerDissIndex = 1 + OTA_PowerDiss_INDEX;
static const int TempIndex = 1 + OTA_Text_INDEX;
static const int StatusIndex = 1 + OTA_Status_INDEX;
static const int OVIndex = 1 + OTA_OV_INDEX;
static const int OCIndex = 1 + OTA_OC_INDEX;
static const int ModuleIndex = 1 + OTA_Module_INDEX;
static const int MPPIndex = 1  + OTA_MPP_INDEX;
static const int ChannelIndex = 1 + OTA_Channel_INDEX;
static const int BunchIndex = 1 + OTA_Bunch_INDEX;
static const int SlotIndex = 1 + OTA_TimeSlot_INDEX;
static const int GWOffsetIndex = 1 + OTA_GWOffset_INDEX;
static const int GWRSSIIndex = 1 + OTA_GWORSSI_INDEX;
static const int EDOffsetIndex = 1 + OTA_EDOffset_INDEX;
static const int EDRSSIIndex = 1 + OTA_EDORSSI_INDEX;


static const int GatewayTabIndex = 0;
static const int EDCommsTabIndex = 1;
static const int EDComms2TabIndex = 2;
static const int EDSettingsTabIndex = 3;
static const int LinearCoeffsTabIndex = 4;
static const int PowerCntrlTabIndex = 5;
static const int TempCntrlTabIndex = 6;
static const int FineTuningTabIndex = 7;
static const int ProtectionTabIndex = 8;
static const int RadioTabIndex = 9;
static const int VersionTabIndex = 10;
static const int KeysTabIndex = 11;
static const int CCsTabIndex = 12;
static const int NetworkTabIndex = 13;
static const int ErrorsTabIndex = 14;
static const int OutputTabIndex = 15;
static const int ConfigurationTabIndex = 16;


static const QString Blank("");

static const QString endFont("</font>");
static const QString redFont("<font color='red'>");
static const QString blueFont("<font color='blue'>");
static const QString blackFont("<font color='black'>");
static const QString greyFont("<font color='grey'>");

static const QString otherGatewaysStr("Other GW(s)");
static const QString noOtherGatewaysStr("No Other GW(s)");

static const QString gatewayChannelStr("Channel:");
static const QString gatewayGatewayEndDeviceAddressStr("Gateway/ED Address:");
static const QString gatewayBunchSizeStr("Bunch Size:");
static const QString gatewayNetworkSizeStr("Network Size:");
static const QString gatewayHoppingStr("Hopping:");
static const QString gatewayPowerStr("Power:");
static const QString gatewaySyncwordStr("Sync Word:");
static const QString gatewayModeStr("Mode:");
static const QString gatewayRepeatCommandStr("Repeat Cmd:");

static const QString ocStepStr("OC Step:");
static const QString ovStepStr("OV Step:");
static const QString currentNoiseStr("Current Noise:");
static const QString ovStartupStr("OV Startup:");
static const QString ocStr("OC:");
static const QString ovStr("OV:");
static const QString vinLimit255Str("Vin Limit 255:");
static const QString vinStopRadioStr("Vin Stop Radio:");
static const QString vinTurnOnStr("Vin Turn On:");
static const QString vinTurnOffStr("Vin Turn Off:");
static const QString moduleStr("Module:");
static const QString mppStr("MPP:");

static const QString amptOffStr("Off");
static const QString amptOnStr("On");

static const QString linearCoeffsCoefficientsRowLabelStr("Coefficients:");
static const QString linearCoeffsOffsetRowLabelStr("Offsets:");
static const QString linearCoeffsVOutColumnStr("Vout");
static const QString linearCoeffsVIn1ColumnStr("Vin1");
static const QString linearCoeffsVIn2ColumnStr("Vin2");
static const QString linearCoeffsIOutColumnStr("Iout");
static const QString linearCoeffsIIn1ColumnStr("Iin1");
static const QString linearCoeffsIIn2ColumnStr("Iin2");
static const QString linearCoeffsTextColumnStr("Text");

static const QString tempCntrlOCProtectionStr("OC Protection:");
static const QString tempCntrlTColdStr("T.Cold:");
static const QString tempCntrlTHotStr("T.Hot:");
static const QString tempCntrlTSuperHotStr("T.Super Hot:");
static const QString tempCntrlFallbackTimeStr("Fallback Time:");

static const QString fineTuningVRef0Str("V Ref 0:");
static const QString fineTuningKVRefStr("K V Ref:");
static const QString fineTuningT0Str("T 0:");
static const QString fineTuningTempCoeffCurrentStr("Temp. Coeff. Current:");
static const QString fineTuningTempCoeffPowerStr("Temp. Coeff. Power:");
static const QString fineTuningShortCircuitLevelStr("Short Circuit Level:");

static const QString radioDFK0Str("DFK0:");
static const QString radioDFK1Str("DFK1:");
static const QString radioDFK2Str("DFK2:");
static const QString radioDFK3Str("DFK3:");
static const QString radioPureOffsetStr("Pure Offset:");
static const QString radioLowCurrentLimitTo255Str("Low Iin1 Switch 255:");
static const QString radioVin2To255Str("Vin2 Switch to 255:");
static const QString radioVin2From255Str("Vin2 Switch from 255:");

static const QString powerCntrlVinTurnOnStr("Vin Turn On:");
static const QString powerCntrlVinTurnOffStr("Vin Turn Off:");
static const QString powerCntrlVinStopRadioStr("Vin Stop Radio:");
static const QString powerCntrlVinLimit255Str("Vin Limit 255:");
static const QString powerCntrlOVStr("OV:");
static const QString powerCntrlOCStr("OC");
static const QString powerCntrlOVStartupStr("OV Startup:");
static const QString powerCntrlCurrentNoiseStr("Current Noise:");
static const QString powerCntrlOVStepStr("OV Step:");
static const QString powerCntrlOCStepStr("OC Step:");
static const QString powerCntrlModuleStr("Module:");
static const QString powerCntrlMPPStr("MPP:");

static const QString edCommsNetIDStr("NetID:");
static const QString edCommsBunchStr("Bunch:");
static const QString edCommsGroupStr("Group:");
static const QString edCommsChannelStr("Channel:");
static const QString edCommsGatewayEDAddressStr("Gateway/ED Address:");
static const QString edCommsGBunchStr("GBunch:");
static const QString edCommsRBunchStr("RBunch");
static const QString edCommsHoppingStr("Hop:");
static const QString edCommsRadioPowerStr("Radio Power:");
static const QString edCommsGatewayChannelFlagStr("GW Channel flag:");
static const QString edCommsSyncWordStr("Sync Word:");
static const QString edComms12KbodStr("12Kbod:");
static const QString edCommsStayInRXStr("Stay In RX:");
static const QString edCommsStayInCWStr("Stay In CW:");
static const QString edComms2RepeaterStr("Repeater:");
static const QString edComms2RepeaterPowerStr("Repeater Power:");
static const QString edComms2RepeaterChannelStr("Repeater Channel:");
static const QString edComms2SearchEnabledStr("Searach Enabled:");
static const QString edComms2CriticalLevel10Str("CriticalLevel10:");
static const QString edComms2SlaveStr("Slave:");
static const QString edComms2SlaveChannelStr("Slave Channel:");
static const QString edComms2250KbodStr("250Kbod:");
static const QString edComms2CriticalLevel500Str("CriticalLevel500:");

static const QString edSettingsSyncFrequencyStr("Sync Frequency:");
static const QString edSettingsSyncPhaseStr("Sync Phase:");
static const QString edSettingsFuseCommunicationsStr("Fuse Communications:");
static const QString edSettingsFuseElectricalStr("Fuse Electrical:");
static const QString edSettingsOptimizerFamilyStr("Optimizer Family:");

static const QString versionVersionHighStr("version High:");
static const QString versionVersionLowStr("version Low:");
static const QString versionSKUHighStr("sku High:");
static const QString versionSKULowStr("sku Low:");
static const QString versionVersionSuffix1Str("version Suffix1:");
static const QString versionVersionSuffix2Str("version Suffix2:");
static const QString versionVersionSuffix3Str("version Suffix3:");
static const QString versionShuntStr("Shunt:");
static const QString versionCommissionedStr("Commissioned:");


static const QString protectionFETFailureCountStr("FET Count:");
static const QString protectionFETFailureThresholdStr("FET Threshold:");
static const QString protectionFETFailureDeltaCurrentStr("FET Delta I:");

static const QString protection1_1300VStr("VhvVoutLimit:");
static const QString protection2_1300VStr("IhvVoutLimit:");
static const QString protection3_1300VStr("VhvVinsLimit:");
static const QString protection4_1300VStr("IhvVinsLimit:");

static const QString protection_AMF_Timer1Str("AMF Timer1:");
static const QString protection_AMF_Timer2Str("AMF Timer2:");
static const QString protection_AMF_V_OV_Str("AMF V_OV:");
static const QString protection_AMF_I_OC_Str("AMF I_OC:");
static const QString protection_AMF_MPP_Cycles_Off_Str("AMF MPP Cycles Off:");
static const QString protection_AMF_MPP_Number_Of_Off_Cycles("AMF MPP # of Off Cycles:");
static const QString protection_Debug_Monitoring_Str("Monitoring:");

static const QString protection1_1500VStr("VoutLimitCount:");
static const QString protection2_1500VStr("VoutLimit:");
static const QString protection3_1500VStr("IoutLimitCount:");
static const QString protection4_1500VStr("IoutLimit:");

static const QString protection_1500V_EFInputCurrentThresholdStr("EF Iin Threshold:");
static const QString protection_1500V_EFOccurrenceThresholdStr("EF Occurrence Threshold:");
static const QString protection_1500V_EFCountDownTimerStr("EF CountDown Timer:");
static const QString protection_1500V_EFAlphaNumeratorStr("EF Alpha Numerator:");
static const QString protection_1500V_EFModuleOffStr("EF ModuleOff:");

static const QString protection_1500V_30_IinLimitStr("Iin Limit:");
static const QString protection_1500V_30_IinLimitOCStepsStr("Iin OC Steps:");
static const QString protection_1500V_30_IinLimitOCDelayStr("Iin OC Delay:");
static const QString protection_1500V_30_IinLimitTempAmbientAdjustStr("IinLimit Ambient Adj:");


static const QString utilitiesSelectSNtoMACStr("SN => MAC:");
static const QString utilitiesSelectMACToSNStr("MAC => SN:");

static const QString networkEnableJoinStr("Enable Join");

static const QString MACCommandTypeToConfirm("MAC");
static const QString GatewayCommandTypeToConfirm("Gateway");

static double zeroAsDouble(0.000);
static int zero(0);

static bool ResetParameterBlockValues = true;

static const int TwoValueCheckBox = 1;
static const int TwoHundredFiftySixValueSpinBox = 2;
static const int NetIDSpinBox = 3;
static const int PositiveIntegerSpinBox = 4;
static const int OptimizerFamilyComboBox = 5;
static const int BooleanRadioButton = 6;

static QMap <QString,int> configurationMap;
static QMap<QString, QCheckBox *> configurationKeyToCheckBox;
static QMap<QString, QCheckBox *>::iterator configurationKeyToCheckBoxIter;

static QMap<QString, QSpinBox *> configurationKeyToSpinBox;
static QMap<QString, QSpinBox *>::iterator configurationKeyToSpinBoxIter;

static QMap<QString, QComboBox *> configurationKeyToComboBox;
static QMap<QString, QComboBox *>::iterator configurationKeyToComboBoxIter;

static QMap<QString, QRadioButton *> configurationKeyToRadioButton;
static QMap<QString, QRadioButton *>::iterator configurationKeyToRadioButtonIter;

static QMap<int, int> optimizerFamilyComboBoxShuntToIndexMap;
static QMap<int, int>::iterator optimizerFamilyComboBoxShuntToIndexMapIter;

static const int OutputSortOTATableByNone = 0;
static const int OutputSortOTATableBySerialNumber = 1;
static const int OutputSortOTATableByMAC = 2;
static const int OutputSortOTATableByNetwork = 3;

AmptGUI_X::AmptGUI_X(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AmptGUI_X)
{

    msgBox = nullptr;
    m_parameterBlockThreadTimer = nullptr;
    m_ScreenShot = nullptr;
    m_utilitiesDialog = nullptr;

    m_currentActiveMAC = "";
    emit publishCurrentActiveMAC(m_currentActiveMAC);
    m_oneMACOTAData = "";

    m_showGatewayResponseEnabled = true;

    m_filteringOnBunch = -1; /* Set to non valid bunch number */
    m_filteringOutByOV = -1; /* Set to non valid OV value */
    m_filteringOutByOC = -1; /* Set to non valid OC value */
    m_filteringOnNetIDRange = false;
    m_filteringNetIDStart = 0;
    m_filteringNetIDEnd = 15;
    m_displayPowerDissapation = false;
    m_outputSortOTATableAscending = true; // Initialize to true

    m_gatewayChangesTracked = new gatewayValuesChangesTracked;
    m_edCommsChangesTracked = new edCommsValueChangesTracked;
    m_edSettingsChangesTracked = new edSettingsValueChangesTracked;
    m_powerCntrlChangesTracked = new powerCntrlValuesChangesTracked;
    m_linearCoeffsChangesTracked = new linearCoeffsValueChangesTracked;
    m_tempCntrlValueChangesTracked = new tempCntrlValueChangesTracked;
    m_fineTuningValueChangesTracked = new fineCntrlValueChangesTracked;
    m_radioValueChangesTracked = new radioValueChangesTracked;
    m_protectionsChangesTracked = new protectionsValueChangesTracked;

    ui->setupUi(this);

    setStyleSheet("QPushButton { font: bold 14x; background-color: darkGray; border-color: black; border-width: 3px;  }" );
   // ui->OTATableWidget->setStyleSheet("QTableView::item:selected { color:white; background:#000000; font-weight:900; }"
   //                            "QTableCornerButton::section { background-color:#232326; }"
   //                            "QHeaderView::section { color:white; background-color:#232326; }");

    // setStyleSheet("QTableView { selection-background-color: red; }" );
    //setStyleSheet("QTableView::item:selected{background-color: palette(red); color: palette(highlightedText)}");
    // setStyleSheet( "QTableView { selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5,stop: 0 #FF92BB, stop: 1 white)}");
    // setStyleSheet("QTableWidget {  background-color: blue; selection-background-color: red; }" );

    /* Have not learned how to reorder the QTabWidget tabs via QtCreator was in placed, improving the "order" */
    ui->AllTabs->tabBar()->moveTab(7,2); /* ED Comms 2 to 3rd from left tab */
    ui->AllTabs->tabBar()->moveTab(11,8); /* move protection tab next to fine tuning */
    ui->AllTabs->tabBar()->moveTab(14,10); /* move radio tab left of protection tab */
    ui->AllTabs->tabBar()->moveTab(12,11); /* Move Keys tab left adjacent to version */


    // void QTabWidget::setTabToolTip(int index, const QString & tip)
    ui->AllTabs->setTabToolTip(GatewayTabIndex,"Commands related to the Ampt Gateway device.");
    ui->AllTabs->setTabToolTip(EDCommsTabIndex,"First of 2 tabs related to End Device network or communications settings.");
    ui->AllTabs->setTabToolTip(EDComms2TabIndex,"Second of 2 tabs related to End Device network or communications settings.");
    ui->AllTabs->setTabToolTip(EDSettingsTabIndex,"Odds and ends End Device settings.");
    ui->AllTabs->setTabToolTip(LinearCoeffsTabIndex,"The Linear Coefficients and Offsets for an End Device.");
    ui->AllTabs->setTabToolTip(PowerCntrlTabIndex,"Settings related to power and power control for an End Device.");
    ui->AllTabs->setTabToolTip(TempCntrlTabIndex,"Settings related to temperature protections for an End Device.");
    ui->AllTabs->setTabToolTip(FineTuningTabIndex,"Settings related to temperature calculations and short circuit protection of an End Device.");
    ui->AllTabs->setTabToolTip(ProtectionTabIndex,"Settings related to non temperature protections of an End Device.");
    ui->AllTabs->setTabToolTip(RadioTabIndex,"Settings related to the radio for an End Device.");
    ui->AllTabs->setTabToolTip(VersionTabIndex,"Settings related to the firmware versioning information of an End Device.");
    ui->AllTabs->setTabToolTip(KeysTabIndex,"Settings related to encryption/decryption of an End Device.");
    ui->AllTabs->setTabToolTip(CCsTabIndex,"Complex commands");
    ui->AllTabs->setTabToolTip(NetworkTabIndex,"Commands for creating, growing, and ending an Ampt network.");
    ui->AllTabs->setTabToolTip(ErrorsTabIndex,"Info/Warnings/Errors encountered during the lifetime of AmptGUI_X.");
    ui->AllTabs->setTabToolTip(OutputTabIndex,"Available ways to control and log data received by the AmptGUI_X.");
    ui->AllTabs->setTabToolTip(ConfigurationTabIndex,"Configurable behavior of the AmptGUI_X.");



    initializeOTATableWidget();

    /*
    ui->OTATableWidget->clear();
    ui->OTATableWidget->setRowCount(0);

    ui->OTATableWidget->setHorizontalHeaderItem(SerialNumIndex, new QTableWidgetItem(QString("SerialNum")));
    ui->OTATableWidget->setHorizontalHeaderItem(MACIndex, new QTableWidgetItem(QString("MAC")));
    ui->OTATableWidget->setHorizontalHeaderItem(TimeIndex, new QTableWidgetItem(QString("Time")));
    ui->OTATableWidget->setHorizontalHeaderItem(Vin1Index, new QTableWidgetItem(QString("V in1")));
    ui->OTATableWidget->setHorizontalHeaderItem(Vin2Index, new QTableWidgetItem(QString("V in2")));
    ui->OTATableWidget->setHorizontalHeaderItem(VoutIndex, new QTableWidgetItem(QString("V out")));
    ui->OTATableWidget->setHorizontalHeaderItem(Iin1Index, new QTableWidgetItem(QString("I in1")));
    ui->OTATableWidget->setHorizontalHeaderItem(Iin2Index, new QTableWidgetItem(QString("I in2")));
    ui->OTATableWidget->setHorizontalHeaderItem(IoutIndex, new QTableWidgetItem(QString("I out")));
    ui->OTATableWidget->setHorizontalHeaderItem(PowerDissIndex, new QTableWidgetItem(QString("Pwr Diss")));
    ui->OTATableWidget->setHorizontalHeaderItem(TempIndex, new QTableWidgetItem(QString("Temp")));
    ui->OTATableWidget->setHorizontalHeaderItem(StatusIndex, new QTableWidgetItem(QString("Status")));
    ui->OTATableWidget->setHorizontalHeaderItem(OVIndex, new QTableWidgetItem(QString("OV")));
    ui->OTATableWidget->setHorizontalHeaderItem(OCIndex, new QTableWidgetItem(QString("OC")));
    ui->OTATableWidget->setHorizontalHeaderItem(ModuleIndex, new QTableWidgetItem(QString("Mod")));
    ui->OTATableWidget->setHorizontalHeaderItem(MPPIndex, new QTableWidgetItem(QString("MPP")));
    ui->OTATableWidget->setHorizontalHeaderItem(ChannelIndex, new QTableWidgetItem(QString("Chnl")));
    ui->OTATableWidget->setHorizontalHeaderItem(BunchIndex, new QTableWidgetItem(QString("Bnch")));
    ui->OTATableWidget->setHorizontalHeaderItem(SlotIndex, new QTableWidgetItem(QString("Id")));

    ui->OTATableWidget->setHorizontalHeaderItem(GWOffsetIndex, new QTableWidgetItem(QString("GwOff")));
    ui->OTATableWidget->setHorizontalHeaderItem(GWRSSIIndex, new QTableWidgetItem(QString("GwRSSI")));
    ui->OTATableWidget->setHorizontalHeaderItem(EDOffsetIndex, new QTableWidgetItem(QString("EdOff")));
    ui->OTATableWidget->setHorizontalHeaderItem(EDRSSIIndex, new QTableWidgetItem(QString("EdRSSI")));


    //ui->OTATableWidget->horizontalHeader()->setDefaultSectionSize(80);
    ui->OTATableWidget->setColumnWidth(SerialNumIndex,78);
    ui->OTATableWidget->setColumnWidth(MACIndex,86);
    ui->OTATableWidget->setColumnWidth(TimeIndex,116);
    ui->OTATableWidget->setColumnWidth(Vin1Index,66);

    ui->OTATableWidget->setColumnWidth(Vin2Index,66);
    ui->OTATableWidget->setColumnWidth(VoutIndex,66);
    ui->OTATableWidget->setColumnWidth(Iin1Index,50);
    ui->OTATableWidget->setColumnWidth(Iin2Index,50);
    ui->OTATableWidget->setColumnWidth(IoutIndex,50);
    ui->OTATableWidget->setColumnWidth(PowerDissIndex,66);
    ui->OTATableWidget->setColumnWidth(TempIndex,46);
    ui->OTATableWidget->setColumnWidth(StatusIndex,48);
    ui->OTATableWidget->setColumnWidth(GWOffsetIndex,52);
    ui->OTATableWidget->setColumnWidth(GWRSSIIndex,58);
    ui->OTATableWidget->setColumnWidth(EDOffsetIndex,52);
    ui->OTATableWidget->setColumnWidth(EDRSSIIndex,58);

    ui->OTATableWidget->setColumnWidth(OVIndex,32);
    ui->OTATableWidget->setColumnWidth(OCIndex,32);
    ui->OTATableWidget->setColumnWidth(ChannelIndex,46);
    ui->OTATableWidget->setColumnWidth(BunchIndex,44);
    ui->OTATableWidget->setColumnWidth(SlotIndex,22);
    ui->OTATableWidget->setColumnWidth(ModuleIndex,40);
    ui->OTATableWidget->setColumnWidth(MPPIndex,40);

   ui->OTATableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

   */

    handleResetTextEditControls();

    ui->edSettingsOptimizerFamilyComboBox->addItem(Family600V);
    optimizerFamilyComboBoxShuntToIndexMap[Family600V_Shunt] = 0;

    ui->edSettingsOptimizerFamilyComboBox->addItem(Family1000V);
    optimizerFamilyComboBoxShuntToIndexMap[Family1000V_Shunt] = 1;

    ui->edSettingsOptimizerFamilyComboBox->addItem(Family1300V);
    optimizerFamilyComboBoxShuntToIndexMap[Family1300V_Shunt] = 2;

    ui->edSettingsOptimizerFamilyComboBox->addItem(Family1500V);
    optimizerFamilyComboBoxShuntToIndexMap[Family1500V_Shunt] = 3;

    ui->edSettingsOptimizerFamilyComboBox->addItem(Family600V_V2);
    optimizerFamilyComboBoxShuntToIndexMap[Family600V_V2_Shunt] = 4;

    ui->edSettingsOptimizerFamilyComboBox->addItem(Family1500V_30);
    optimizerFamilyComboBoxShuntToIndexMap[Family1500V_30_Shunt] = 5;

    ui->edSettingsOptimizerFamilyComboBox->addItem(Family1500V_2nd);
    optimizerFamilyComboBoxShuntToIndexMap[Family1500V_2nd_Shunt] = 6;


    ui->edSettingsOptimizerFamilyComboBox->setCurrentIndex(2);

    ui->gatewayHoppingComboBox->addItem(amptOffStr);
    ui->gatewayHoppingComboBox->addItem(amptOnStr);

    ui->gatewayPowerComboBox->addItem("1");
    ui->gatewayPowerComboBox->addItem("0");
    ui->gatewayPowerComboBox->addItem("-1");
    ui->gatewayPowerComboBox->addItem("-2");
    ui->gatewayPowerComboBox->addItem("-4");
    ui->gatewayPowerComboBox->addItem("-6");
    ui->gatewayPowerComboBox->addItem("-8");
    ui->gatewayPowerComboBox->addItem("-10");
    ui->gatewayPowerComboBox->addItem("-15");
    ui->gatewayPowerComboBox->addItem("-20");
    ui->gatewayPowerComboBox->addItem("-25");
    ui->gatewayPowerComboBox->addItem("-35");
    ui->gatewayPowerComboBox->addItem("-65");

    ui->gatewaySendPushButton->setEnabled(false);
    ui->gatewaySavePushButton->setEnabled(false);
    ui->gatewayResetGatewayPushButton->setEnabled(false);


    handleResetPowerCntrlWidgets();

    handleResetLinearCoeffs();
    handleResetTempCntrl();
    handleResetProtections();
    handleResetFineTuning();
    handleResetRadio();
    handleResetEDComms();
    handleResetEDSettings();

    handleResetKeys();
    handleResetVersionInfo();
    handleResetOutput();
    handleResetCoeffsLine();


   connect(ui->ovSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleOVValueChangeFromSpinBox(int)));
   connect(ui->ovDial, SIGNAL(valueChanged(int)), this, SLOT(handleOVValueChangeFromDial(int)));
   connect(ui->ovSendPushButton, SIGNAL(released( void )), this, SLOT(handleOVSendPushButton( void )));

   connect(ui->ocSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleOCValueChangeFromSpinBox(int)));
   connect(ui->ocDial, SIGNAL(valueChanged(int)), this, SLOT(handleOCValueChangeFromDial(int)));
   connect(ui->ocSendPushButton, SIGNAL(released( void )), this, SLOT(handleOCSendPushButton( void )));

   connect(ui->mppComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleMPPValueChangeFromComboBox(int)));
   connect(ui->mppDial, SIGNAL(valueChanged(int)), this, SLOT(handleMPPValueChangeFromDial(int)));
   connect(ui->mppSendPushButton, SIGNAL(released( void )), this, SLOT(handleMPPSendPushButton( void )));

   connect(ui->moduleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleModuleValueChangeFromComboBox(int)));
   connect(ui->moduleDial, SIGNAL(valueChanged(int)), this, SLOT(handleModuleValueChangeFromDial(int)));
   connect(ui->moduleSendPushButton, SIGNAL(released( void )), this, SLOT(handleModuleSendPushButton( void )));

   connect(ui->readCoefficientsPushButton, SIGNAL(released( void )), this, SLOT(handleReadCoeffsPushButton( void )));
   connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceReceivedCoeffLineData( void )), this, SLOT(handleEndDeviceReceivedCoeffLineData( void )));
   connect(&m_endDeviceParameterBlockInfoThread,SIGNAL(publishEndDeviceValidCoeffLineData(const QString)), this, SLOT(handleEndDeviceValidCoeffLineData(const QString)));

    /* All slots associcated with the start signal */
    connect(this, SIGNAL(startSignal()), this, SLOT(startConfigurationSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startLoggerSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startOutputLoggerSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startGatewaySlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startParseOTADataSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startReceiveOTADataSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startParseParameterBlockSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startParseGatewayParameterBlockSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startEndDeviceParameterBlockInfoSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startCheckGatewayCommandSlot()));
    connect(this, SIGNAL(startSignal()), this, SLOT(startBatchCommandsSlot()));

    /* Any "extra" GUI initialization */
    connect(this, SIGNAL(startSignal()), this, SLOT(configurationAtStart()));
    connect(this, SIGNAL(startSignal()), this, SLOT(initializeGUI()));

    //connect(this, SIGNAL(startSignal()), this, SLOT(startUpCommands()));

    connect(&m_gatewayThread, SIGNAL(publishGatewayIsOperational( void )), this, SLOT(handleGatewayIsOperational( void )));
    connect(&m_gatewayThread, SIGNAL(publishGatewayIsNotOperational( void )), this, SLOT(handleGatewayIsNotOperational( void )));

    connect(&m_gatewayThread,SIGNAL(gatewayOutput( const QString )),this,SLOT(showGatewayResponse( const QString )));
    connect(&m_gatewayThread,SIGNAL(gatewayOutput( const QString )),&m_receiveOTADataThread,SLOT(receiveOTAData(const QString)));
    // connect(&m_gatewayThread,SIGNAL(gatewayOutput( const QString )), this,SLOT(showRawData( const QString ))); /* DEBUG */
    // connect(&m_gatewayThread,SIGNAL(gatewayOutput( const QString )), &m_parseOTADataThread, SLOT(parseOTAData( const QString )));
    connect(&m_gatewayThread,SIGNAL(gatewayOutput( const QString )), &m_loggerThread, SLOT(receiveDataToLog( const QString )));
    connect(&m_gatewayThread, SIGNAL(publishGatewayError(const QString)), this, SLOT(handlePublishedErrors(const QString)));

    connect(&m_checkGatewayCommandThread, SIGNAL(checkGatewayCommandThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)) );
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceParameterBlockInfoThreadFamilyError(QString)), this, SLOT(handlePublishedErrors(QString)));

    connect(&m_parseOTADataThread,SIGNAL(parsedOTADataThreadRawMessage( const QString, const QString )), this, SLOT(showParsedOTAData( const QString, const QString )) );
    connect(&m_parseOTADataThread,SIGNAL(parsedOTADataThreadRawMessage( const QString, const QString )), &m_outputLoggerThread, SLOT(handleOTADataForCSV(const QString, const QString)));
    connect(&m_parseOTADataThread, SIGNAL(publishOnMainImage(const QString, const bool)), &m_endDeviceParameterBlockInfoThread, SLOT(handleOnMainImage(const QString,const bool)));
    connect(&m_parseOTADataThread, SIGNAL(publishParseOTADataThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)));

    // connect(this,SIGNAL(parse( const QString)), &m_parseOTADataThread, SLOT(parseOTAData(const QString )));

    // connect(&m_receiveOTADataThread,SIGNAL(receivedOTADataThreadRawMessage(const QString)), this, SLOT(receiveRawData(const QString)));
    connect(&m_receiveOTADataThread,SIGNAL(receivedOTADataThreadMessage(const QString)), &m_parseOTADataThread,SLOT(parseOTAData( const QString )));
    connect(&m_receiveOTADataThread,SIGNAL(receivedOTADataThreadParameterBlockMessage( const QString )), &m_parseParameterBlockThread, SLOT(parseOTAParameterBlockData( const QString )));


    connect(&m_receiveOTADataThread, SIGNAL(receivedOTADataThreadCoeffsMessage( const QString )), &m_parseParameterBlockThread, SLOT(handleOTADataThreadCoeffsMessage( const QString )));

    connect(&m_receiveOTADataThread,SIGNAL(receivedOTADataThreadGatewayParameterBlockMessage( const QString)), &m_parseGatewayParameterBlockThread, SLOT(parseGatewayParameterBlockData(const QString)));
    connect(&m_receiveOTADataThread,SIGNAL(publishReceivedOTADataThreadUnknownMessage(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_receiveOTADataThread,SIGNAL(publishReceivedOTADataThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_receiveOTADataThread,SIGNAL(publishOtherGatewayObserved(const bool)), this, SLOT(handlePublishOtherGateways(const bool)));

    connect(ui->OTATableWidget, SIGNAL(cellClicked(int,int)),this, SLOT(handleOTATableClicked(int, int)));

    connect(ui->commandLineEdit, SIGNAL(textChanged(const QString)), this, SLOT(enableCommandLinePushButton(const QString)));

    connect(ui->commandLineEdit, SIGNAL(returnPressed(void)), ui->commandLineEditPushButton, SIGNAL(clicked(void)));
    connect(ui->commandLineEditPushButton, SIGNAL(clicked()), this, SLOT(sendCommandToGatewayFromCommandLine()));

    connect(m_powerCntrlChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));
    connect(m_radioValueChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));
    connect(m_tempCntrlValueChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));
    connect(m_fineTuningValueChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));
    connect(m_linearCoeffsChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));
    connect(m_edCommsChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));
    connect(m_edSettingsChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));
    connect(m_protectionsChangesTracked, SIGNAL(publishCommand(const QString)), this, SLOT(sendCommandToGateway(const QString)));


    connect(ui->commandRadioButtonMAC,SIGNAL(clicked( const bool)), this, SLOT(handleRadioButtonMACClicked( const bool)));
    connect(ui->commandRadioButtonBroadcast,SIGNAL(clicked( const bool)), this, SLOT(handleRadioButtonBroadcastClicked( const bool)));
    connect(ui->commandRadioButtonGroup,SIGNAL(clicked( const bool)), this, SLOT(handleRadioButtonGroupClicked( const bool)));
    connect(ui->commandRadioButtonNetwork,SIGNAL(clicked( const bool)), this, SLOT(handleRadioButtonNetworkClicked( const bool)));
    connect(ui->commandRadioButtonGateway,SIGNAL(clicked( const bool)), this, SLOT(handleRadioButtonGatewayClicked( const bool)));

    connect(ui->commandMACComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(handleMACComboBoxChange(const QString)));
    connect(this, SIGNAL(newMACDiscovered(const QString)), this, SLOT(handleNewMACDiscovered(const QString)));
    connect(this, SIGNAL(newMACDiscovered(const QString)), &m_parseParameterBlockThread,SLOT(handleNewMACDiscovered( const QString)));

    /* SIGNALS to be handled from the Linear Coeffs Tab */
    connect(ui->linearCoeffsVOutCoefficientDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsVOutCoefficientDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsVOutOffsetDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsVOutOffsetDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsVIn1CoefficientDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsVIn1CoefficientDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsVIn1OffsetDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsVIn1OffsetDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsVIn2CoefficientDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsVIn2CoefficientDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsVIn2OffsetDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsVIn2OffsetDoubleSpinBoxChange(double)));

    connect(ui->linearCoeffsIOutCoefficientDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsIOutCoefficientDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsIOutOffsetDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsIOutOffsetDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsIIn1CoefficientDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsIIn1CoefficientDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsIIn1OffsetDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsIIn1OffsetDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsIIn2CoefficientDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsIIn2CoefficientDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsIIn2OffsetDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsIIn2OffsetDoubleSpinBoxChange(double)));

    connect(ui->linearCoeffsTextCoefficientDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsTextCoefficientDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsTextOffsetDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleLinearCoeffsTextOffsetDoubleSpinBoxChange(double)));
    connect(ui->linearCoeffsSendPushButton, SIGNAL(released( void )), this, SLOT(handleLinearCoeffsSendPushButton( void )));
    connect(ui->linearCoeffsSavePushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));

    connect(ui->saveSmallFPushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));
    connect(ui->saveBigFPushButton, SIGNAL(released( void )), this, SLOT(handleSaveBigF( void )));
    connect(ui->screenShotPushButton, SIGNAL(released( void )), this, SLOT(handleScreenShotPushButton( void )));



    /* SIGNALS to be handled from the ED Comms or ED Comms(2) Tab */
    connect(ui->edCommsChannelSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsChannelValueChanged(int)));
    connect(ui->edCommsBunchSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsBunchValueChanged(int)));
    connect(ui->edCommsNetIDSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsNetIDValueChanged(int)));
    connect(ui->edCommsGatewayAddressSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsGatewayAddressValueChanged(int)));
    connect(ui->edCommsEndDeviceAddressSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsEndDeviceAddressValueChanged(int)));
    connect(ui->edCommsGroupSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsGroupValueChanged(int)));
    connect(ui->edCommsGBunchSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsGBunchValueChanged(int)));
    connect(ui->edCommsRBunchSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsRBunchValueChanged(int)));
    connect(ui->edCommsHoppingAllowedSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsHoppingValueChanged(int)));
    connect(ui->edCommsRadioPowerSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsRadioPowerValueChanged(int)));
    connect(ui->edCommsGatewayChannelFlagSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsGWChannelFlagValueChanged(int)));
    connect(ui->edCommsSyncWordSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsSyncWordValueChanged(int)));
    connect(ui->edComms12KbodSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms12KbodValueChanged(int)));
    connect(ui->edCommsStayInRXSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsStayInRXValueChanged(int)));
    connect(ui->edCommsStayInCWSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDCommsStayInCWValueChanged(int)));

    connect(ui->edCommsSendPushButton, SIGNAL(released( void )), this, SLOT(handleEDCommsSendPushButtonReleased( void )));
    connect(ui->edComms2SendPushButton, SIGNAL(released( void )), this, SLOT(handleEDCommsSendPushButtonReleased( void )));

    connect(ui->edCommsSavePushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));
    connect(ui->edComms2SavePushButton,SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));

    connect(ui->edComms2RepeaterSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2RepeaterValueChanged(int)));
    connect(ui->edComms2RepeaterPowerSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2RepeaterPowerValueChanged(int)));
    connect(ui->edComms2RepeaterChannelSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2RepeaterChannelValueChanged(int)));
    connect(ui->edComms2SearchSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2SearchEnabledValueChanged(int)));
    connect(ui->edComms2SlaveSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2SlaveValueChanged(int)));
    connect(ui->edComms2SlaveChannelSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2SlaveChannelValueChanged(int)));
    connect(ui->edComms2250KbodSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2250KbodValueChanged(int)));
    connect(ui->edComms2CriticalLevel10SpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2CriticalLevel10ValueChanged(int)));
    connect(ui->edComms2CriticalLevel500SpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDComms2CriticalLevel500ValueChanged(int)));

    connect(ui->edSettingsSyncPhaseSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDSettingsSyncPhaseValueChanged( int )));
    connect(ui->edSettingsSyncFrequencySpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleEDSettingsSyncFrequencyValueChanged( int )));
    connect(ui->edSettingsSendPushButton, SIGNAL(released( void )), this, SLOT(handleEDSettingsSendPushButtonReleased( void )));
    connect(ui->edSettingsOVSetToSpinBox , SIGNAL(valueChanged(int)), this, SLOT(handleEDSettingsOVSetToSpinBoxChanged(int)));
    connect(ui->edSettingsOCSetToSpinBox , SIGNAL(valueChanged(int)), this, SLOT(handleEDSettingsOCSetToSpinBoxChanged(int)));

    /* SIGNALS to be handled from the Power Cntrl Tab */
    connect(ui->powerCntrlVinTurnOnSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlVinTurnOnSpinBoxChange(const int)));
    connect(ui->powerCntrlVinStopRadioSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlVinStopRadioSpinBoxChange(const int)));
    connect(ui->powerCntrlVinLimit255SpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlVinLimit255SpinBoxChange(const int)));
    connect(ui->powerCntrlOVSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlOVSpinBoxChange(const int)));
    connect(ui->powerCntrlOCSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlOCSpinBoxChange(const int)));
    connect(ui->powerCntrlOVStartupSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlOVStartupSpinBoxChange(const int)));
    connect(ui->powerCntrlCurrentNoiseSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlCurrentNoiseSpinBoxChange(const int)));
    connect(ui->powerCntrlOVStepSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlOVStepSpinBoxChange(const int)));
    connect(ui->powerCntrlOCStepSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handlePowerCntrlOCStepSpinBoxChange(const int)));
    connect(ui->powerCntrlModuleComboBox,SIGNAL(currentIndexChanged(QString)), this, SLOT(handlePowerCntrlModuleComboBoxChange(const QString)));
    connect(ui->powerCntrlMPPComboBox,SIGNAL(currentIndexChanged(QString)), this, SLOT(handlePowerCntrlMPPComboBoxChange(const QString)));
    connect(ui->powerCntrlSendPushButton, SIGNAL(released( void )), this, SLOT(handlePowerCntrlSendPushButton( void )));

    connect(ui->powerCntrlSavePushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));
    connect(ui->powerCntrlSaveAllPushButton, SIGNAL(released( void )), this, SLOT(handleSaveAllPushButton( void)));

    /* SIGNALS to be handled from the Temp. Cntrl Tab */
    connect(ui->tempCntrlOCProtectionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleTempCntrlOCProtectionSpinBoxChange(int)));
    connect(ui->tempCntrlTColdSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleTempCntrlTColdSpinBoxChange(int)));
    connect(ui->tempCntrlTHotSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleTempCntrlTHotSpinBoxChange(int)));
    connect(ui->tempCntrlTSuperHotSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleTempCntrlTSuperHotSpinBoxChange(int)));
    connect(ui->tempCntrlFallbackTimeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleTempCntrlFallbackTimeSpinBoxChange(int)));
    connect(ui->tempCntrlSendPushButton, SIGNAL(released( void )), this, SLOT(handleTempCntrlSendPushButton( void )));
    connect(ui->tempCntrlSavePushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));


    /* SIGNALS to be handled from the Fine Tuning Tab */
    connect(ui->fineTuningVRef0DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleFineTuningVRef0DoubleSpinBoxChange(double)));
    connect(ui->fineTuningKVRefDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleFineTuningKVRefDoubleSpinBoxChange(double)));
    connect(ui->fineTuningT0DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleFineTuningT0DoubleSpinBoxChange(double)));
    connect(ui->fineTuningTempCoeffCurrentDoubleSpingBox, SIGNAL(valueChanged(double)), this, SLOT(handleFineTuningTempCoeffCurrentDoubleSpinBoxChange(double)));
    connect(ui->fineTuningTempCoeffPowerDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleFineTuningTempCoeffPowerDoubleSpinBoxChange(double)));
    connect(ui->fineTuningShortCircuitLevelSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleFineTuningShortCircuitLevelSpinBoxChange(int)));
    connect(ui->fineTuningSendPushButton, SIGNAL(released( void )), this, SLOT(handleFineTuningSendPushButton( void )));
    connect(ui->fineTuningSavePushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void)) );

    /*SIGNALS to be handled from the Radio Tab */
    connect(ui->radioDFK0DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleRadioDFK0DoubleSpinBoxChange(double)));
    connect(ui->radioDFK1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleRadioDFK1DoubleSpinBoxChange(double)));
    connect(ui->radioDFK2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleRadioDFK2DoubleSpinBoxChange(double)));
    connect(ui->radioDFK3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleRadioDFK3DoubleSpinBoxChange(double)));
    connect(ui->radioPureOffsetSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleRadioPureOffsetSpinBoxChange(int)));
    connect(ui->radioLowCurrentLimitTo255SpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleRadioLowCurrentLimitTo255SpinBoxChange(int)));
    connect(ui->radioSendPushButton, SIGNAL(released( void )), this, SLOT(handleRadioSendPushButton( void )));
    connect(ui->radioSavePushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));

    /* SIGNALS/SLOTS related to Network Tab */
    connect(ui->networkDisbandNetworkPushButton, SIGNAL(released( void )), this, SLOT(handleNetworkDisbandNetworkPushButton( void )));
    connect(ui->networkEnableJoinPushButton, SIGNAL(released( void )), this, SLOT(handleNetworkEnableJoinPushButton( void )));
    connect(ui->networkDisableJoinPushButton, SIGNAL(released( void )), this, SLOT(handleNetworkDisableJoinPushButton( void )));
    connect(ui->networkEndOfTestPushButton, SIGNAL(released( void )), this, SLOT(handleNetworkEndOfTestPushButton( void )));
    connect(ui->networkNCommandMACLineEdit, SIGNAL(textChanged(QString)), this, SLOT(handleNetworkNCommandArguments( QString)));
    connect(ui->networkNCommandArgumentLineEdit, SIGNAL(textChanged(QString)), this, SLOT(handleNetworkNCommandArguments( QString)));
    connect(ui->networkNCommandPushButton, SIGNAL(released( void)), this, SLOT(handleNetworkNCommandPushButton( void )));

    /* Signals to be handled from the Protections Tab */
    connect(ui->protectionsFETFailureCountSpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsFETFailureCountSpinBoxChange(int)));
    connect(ui->protectionsFETThresholdSpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsFETFailureThresholdSpinBoxChange(int)));
    connect(ui->protectionsFETDeltaCurrentSpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsFETFailureDeltaCurrentSpinBoxChange(int)));
    connect(ui->protectionsProtection1SpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsProtection1SpinBoxChange(int)));
    connect(ui->protectionsProtection2SpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsProtection2SpinBoxChange(int)));
    connect(ui->protectionsProtection3SpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsProtection3SpinBoxChange(int)));
    connect(ui->protectionsProtection4SpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsProtection4SpinBoxChange(int)));
    connect(ui->protectionsAMF_Timer1Spinbox,SIGNAL(valueChanged(int)), this, SLOT(handleProtections1300VAMFTimer1SpinBoxChange(int)));
    connect(ui->protectionsAMF_Timer2Spinbox,SIGNAL(valueChanged(int)), this, SLOT(handleProtections1300VAMFTimer2SpinBoxChange(int)));
    connect(ui->protectionsAMF_V_OVSpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtections1300VAMFV_OVSpinBoxChange(int)));
    connect(ui->protectionsAMF_I_OCSpinBox,SIGNAL(valueChanged(int)), this, SLOT(handleProtections1300VAMFI_OCSpinBoxChange(int)));
    connect(ui->protectionsAMF_MPP_Off_CyclesSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsAMF_MPPCyclesOffSpinBoxChange(int)));
    connect(ui->protectionsAMF_MPP_TimesOffSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsAMF_MPPTimesOffSpinBoxChange(int)));
    connect(ui->protectionsAMF_DebugSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsAMF_DebugSpinBoxChange(int)));

    connect(ui->protectionsEFInputCurrentThresholdSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsEF_InputCurrentThresholdSpinBoxChange(int)));
    connect(ui->protectionsEFOccurrenceThresholdSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsEF_OccurrenceThresholdSpinBoxChange(int)));
    connect(ui->protectionsEFCountDownTimerSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsEF_CountDownTimerSpinBoxChange(int)));
    connect(ui->protectionsEFAlphaNumeratorSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsEF_AlphaNumeratorSpinBoxChange(int)));

    connect(ui->protectionsIinLimitSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsIinLimitSpinBoxChange(int)));
    connect(ui->protectionsIinLimitOCStepsSpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsIinLimitOCStepsSpinBoxChange(int)));
    connect(ui->protectionsIinLimitOCDelaySpinbox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsIinLimitOCDelaySpinBoxChange(int)));
    connect(ui->protectionsIinLimitTempAmbientAdjustSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleProtectionsIinLimitTempAmbientAdjustSpinBoxChange(int)));

    connect(ui->protectionsSendPushButton, SIGNAL(released( void )), this, SLOT(handleProtectionsSendPushButton( void )));
    connect(ui->protectionsSavePushButton, SIGNAL(released( void )), this, SLOT(handleSaveSmallF( void )));

    /* possibly new parameter block values to load */
    connect(this,SIGNAL(publishClearCurrentEndDevicePBsAndLoadNewEDPBs(void)), this, SLOT(handleClearCurrentEndDevicePBsAndLoadNewEDPBs(void)));
    connect(this, SIGNAL(publishFindStoredPBInfo(const QString, const QString)), &m_endDeviceParameterBlockInfoThread, SLOT(handleFindStoredPBInfo(const QString, const QString)));

    /* Configuration Signals */
    /*                                                   not using tristate, so use this signal */
    connect(ui->outputSuperCycleInOutputCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleConfigurationSuperCyclesInOutput(int)));
    connect(ui->outputOutputLongFormatOTADataCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleConfigurationLongFormatOTAData(int)));
    connect(ui->configurationSaveParameterBlockCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleConfigurationSaveParameterBlockCheckBox(int)));
    connect(this, SIGNAL(publishEndDeviceSaveParameterBlockInfo(bool)), &m_endDeviceParameterBlockInfoThread, SLOT(handleEndDeviceSaveParameterBlockInfoSignal(bool)));

    connect(ui->configurationSaveAmptGUI_XPushButton, SIGNAL(released(void )), this, SLOT(handleConfigurationSaveAmptGUI_XPushButton( void )));
    connect(&m_configurationThread,SIGNAL(publishSavedConfiguration(const QStringList &)), this, SLOT(handlePublishSavedConfiguration(const QStringList &)));
    connect(&m_configurationThread,SIGNAL(sendConfigurationThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_configurationThread,SIGNAL(sendConfigurationThreadInfo(const QString)), this, SLOT(handlePublishedInfo(const QString)));


    /* Parameters ReadWrite Group Box Signals */
    connect(ui->parametersReadPushButton, SIGNAL(released( void )), this, SLOT(handleParametersReadReleased( void )));
    connect(ui->parametersWritePushButton, SIGNAL(released( void )), this, SLOT(handleParametersWritePushButtonReleased( void )));

    /* Signals/Slots specifically related to end device reading parameter blocks */
    connect(this,SIGNAL(publishReadParameterBlockTimerStarted()), &m_parseParameterBlockThread, SLOT(handleParseParameterBlockTimerStarted()));
    connect(&m_parseParameterBlockThread, SIGNAL(publishEndDeviceParameterBlockReadSuccessful( void )), this, SLOT( handleEndDeviceParameterBlockReadSuccessful( void )));
    connect(this, SIGNAL(publishReadParameterBlockTimeout()), &m_parseParameterBlockThread, SLOT(handleParseParameterBlockTimerExpired()));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceOnMainImage(QString, bool)), this, SLOT(handleEndDeviceOnMainImage(QString, bool )));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceParametersSavedToFile(QString )), this, SLOT(handleEndDeviceParametersSavedToFile(QString)) );

    connect(ui->edSettingsOptimizerFamilyComboBox, SIGNAL(currentIndexChanged(QString)), &m_parseOTADataThread, SLOT(handleOptimizerFamilyChanged(const QString)));
    connect(ui->edSettingsOptimizerFamilyComboBox, SIGNAL(currentIndexChanged(QString)), &m_parseParameterBlockThread, SLOT(handleOptimizerFamilyChanged(const QString)));
    connect(ui->edSettingsOptimizerFamilyComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(handleOptimizerFamilyChanged(const QString)));

    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceOptimizerFamily(const QString ,const int )), this, SLOT(handleOptimizerFamilyChanged(const QString , const int )));

    connect(ui->parametersFlashCheckBox, SIGNAL(clicked( const bool)),&m_parseOTADataThread,SLOT(handleMemoryToFromLocationChanged( const bool)));
    connect(ui->parametersFlashCheckBox, SIGNAL(clicked( const bool)),&m_parseParameterBlockThread,SLOT(handleParametersReadFromChange( const bool)));

    connect(ui->gatewayResetGatewayPushButton, SIGNAL(released( void )), this, SLOT(handleResetGateway( void )));
    connect(ui->gatewaySendPushButton, SIGNAL(released( void )), this, SLOT(handleGatewaySendPushButtonReleased( void )));
    connect(ui->gatewaySavePushButton, SIGNAL(released( void)), this, SLOT(handleGatewaySavePushButtonReleased( void )));
    connect(ui->gatewayChannelSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewayChannelValueChanged(int)));
    connect(ui->gatewayGatewaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewayGatewayAddressValueChanged(int)));
    connect(ui->gatewayEndDeviceSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewayEndDeviceAddressValueChanged(int)));
    connect(ui->gatewayBunchSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewayBunchSizeValueChanged(int)));
    connect(ui->gatewayNetworkSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewayNetworkSizeValueChanged(int)));
    connect(ui->gatewayHoppingComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleGatewayHoppingValueChanged(int)));
    connect(ui->gatewayPowerComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(handleGatewayPowerValueChanged(QString)));
    connect(ui->gatewaySyncwordSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewaySyncwordValueChanged(int)));
    connect(ui->gatewayModeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewayModeValueChanged(int)));
    connect(ui->gatewayRepeatCommandSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleGatewayRepeatCommandValueChanged(int)));

    connect(ui->outputStartOutputPushButton, SIGNAL(released(void)), this, SLOT(handleStartOutputPushButton( void )));
    connect(ui->outputStopOutputPushButton, SIGNAL(released(void)), this, SLOT(handleStopOutputPushButton( void )));
    connect(this, SIGNAL(publishLogCommandsToOutput(bool)), &m_gatewayThread, SLOT(handleOutputIncludeCommandsInLog(bool)));
    connect(this, SIGNAL(publishStartOutputRawFile(QString)), &m_outputLoggerThread, SLOT(handleStartOutputRawFile(QString)));
    connect(this, SIGNAL(publishStartOutputCSVFile(QString)), &m_outputLoggerThread, SLOT(handleStartOutputCSVFile(QString)));
    connect(this, SIGNAL(publishStopOutputFiles(void)), &m_outputLoggerThread, SLOT(handleStopOutputFiles(void)));
    connect(&m_gatewayThread, SIGNAL(gatewayOutput(QString)),&m_outputLoggerThread, SLOT(handleRawDataToLog(QString)));
    connect(&m_gatewayThread, SIGNAL(publishCommandToLog(QString)), &m_outputLoggerThread, SLOT(handleRawDataToLog(QString)));

    connect(ui->outputSortOTATableRadioButtonNone, SIGNAL(clicked(const bool)), this, SLOT(handleOutputSortOTATableRadioButtonNoneClicked( const bool )));
    connect(ui->outputSortOTATableRadioButtonSerialNumber, SIGNAL(clicked(const bool)), this, SLOT(handleOutputSortOTATableRadioButtonSerialNumberClicked( const bool )));
    connect(ui->outputSortOTATableRadioButtonMAC, SIGNAL(clicked(const bool)), this, SLOT(handleOutputSortOTATableRadioButtonMACClicked( const bool )));
    connect(ui->outputSortOTATableRadioButtonNetwork, SIGNAL(clicked(const bool)), this, SLOT(handleOutputSortOTATableRadioButtonNetworkClicked( const bool )));
    connect(ui->outputSortOTATableAscendingCheckBox, SIGNAL(stateChanged(int )), this, SLOT(handleOutputSortOTATableAscendingCheckBoxClicked(int )));


    connect(&m_outputLoggerThread, SIGNAL(publishOutputLoggerReady(void)), this, SLOT(handleOutputReady(void)));
    connect(&m_outputLoggerThread, SIGNAL(publishCSVFileOpenFailed(const QString)), this, SLOT(handleCSVFileOpenFailed( const QString)));
    connect(&m_outputLoggerThread, SIGNAL(publishRawFileOpenFailed(const QString)), this, SLOT(handleRawFileOpenFailed( const QString)));

    connect(ui->outputFilterOutputByBunchCheckBox,SIGNAL(stateChanged(int)), this, SLOT(handleFilterOTADataByBunch(int)));
    connect(ui->outputFilterOutputByNetIDRangeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleFilterOTADataByNetIDRange(int)));
    connect(ui->outputFilterOutUnitsWithOVCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleFilterOTADataUnitsWithOVValue(int)));
    connect(ui->outputFilterOutUnitsWithOCCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleFilterOTADataUnitsWithOCValue(int)));

    connect(m_gatewayChangesTracked, SIGNAL(publishCommand(const QString)), &m_gatewayThread, SLOT(handleGatewayCommandToSend(const QString)));
    // LBC 07/02/2019 : no such slot, signal not connected to anything else. connect(m_gatewayChangesTracked, SIGNAL(publishNewEndDeviceChannel(int)), this, SLOT(handleNewEndDeviceChannel(int)));

    connect(&m_checkGatewayCommandThread, SIGNAL(publishValidateCommandToUser(const QString, const QString)), this, SLOT(handleValidateCommandToCheck(const QString, const QString)));
    connect(&m_checkGatewayCommandThread, SIGNAL(validatedCommand(const QString)), &m_gatewayThread, SLOT(handleGatewayCommandToSend(const QString)));

    connect(&m_parseParameterBlockThread, SIGNAL(enableReadParameterBlocks(bool)), ui->parametersReadPushButton,SLOT(setEnabled(bool)));
    connect(&m_parseParameterBlockThread, SIGNAL(enableReadParameterBlocks(bool)), ui->parametersWritePushButton,SLOT(setEnabled(bool)));
    // LBC connect(&m_parseParameterBlockThread, SIGNAL(enableReadParameterBlocks(bool)), ui->commandGroupBox, SLOT(setEnabled(bool)));
    connect(&m_parseParameterBlockThread, SIGNAL(enableReadParameterBlocks(bool)), this, SLOT(handleCommandGroupBox(bool)));
    connect(&m_parseParameterBlockThread, SIGNAL(publishAllRequestedParameterBlocksRead( void )), this, SLOT(handleAllRequestedParameterBlocksRead( void )));

    connect(&m_parseParameterBlockThread, SIGNAL(publishParseParameterBlockThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_parseParameterBlockThread, SIGNAL(publishParseParameterBlockThreadParseDataError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_parseParameterBlockThread, SIGNAL(publishParseParameterBlockThreadParseSCXError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_parseParameterBlockThread, SIGNAL(publishParseParameterBlockThreadParseMACError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_parseParameterBlockThread,SIGNAL(resendParameterBlockCommand(const QString, const bool, const quint8)),this,SLOT(handleResendParameterBlockCommand(const QString,const bool, const quint8)));
    connect(&m_parseParameterBlockThread,SIGNAL(parsedCompleteParameterBlockDataFor(const QString, const QString)),&m_endDeviceParameterBlockInfoThread, SLOT(handleCompleteEndDeviceParameterBlockInfoAvailable(const QString, const QString)));
    connect(&m_parseParameterBlockThread,SIGNAL(parsedCoeffLineFor(const QString, const QString)),&m_endDeviceParameterBlockInfoThread, SLOT(handleEndDeviceCoeffLineAvailable(const QString, const QString)));

    connect(&m_parseParameterBlockThread,SIGNAL(publishRequestRunningImageForMAC(const QString)), &m_parseOTADataThread, SLOT(handleRequestRunningImageForMAC(const QString)));
    connect(&m_parseParameterBlockThread,SIGNAL(publishPossibleAutoReadOfPB(const QString)),this,SLOT(handleParametersAutoRead(const QString)));
    connect(this, SIGNAL(publishParametersAutoRead(bool)), &m_parseParameterBlockThread, SLOT(handleParametersAutoRead(bool)));
    connect(ui->parametersAutoReadCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleParametersAutoReadCheckBox(int)));

    connect(&m_parseGatewayParameterBlockThread, SIGNAL(parsedGatewayParameterBlockInformation(const QString)), this, SLOT(handleGatewayParameterBlockData(const QString)));
    connect(&m_parseGatewayParameterBlockThread, SIGNAL(publishParseGatewayParameterBlockThreadError(const QString)), this, SLOT(handlePublishedErrors(QString)));


    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceNewPBs(const QString)), this, SLOT(handleEndDeviceNewPBs(const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceLinearKandOffs(const QString, const QString, const QString)), this, SLOT(handleEndDeviceLinearKAndOffs(const QString, const QString, const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceCommunicationSettings(const QString, const QString)), this,SLOT(handleEndDeviceCommunicationsSettings(const QString,const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceSettings(const QString,const QString)), this, SLOT(handleEndDeviceSettings(const QString,const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceProtectionSettings(const QString, const QString, const QString)),this, SLOT(handleEndDeviceProtectionSettings(const QString, const QString, const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDevicePowerCntrlSettings(const QString, const QString)), this, SLOT(handleEndDevicePowerCntrlSettings(const QString,const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceTempCntrlSettings(const QString, const QString)), this, SLOT(handleEndDeviceTempCntrlSettings(const QString, const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceFineTuningSettings(const QString, const QString)), this, SLOT(handleEndDeviceFineTuningSettings(const QString, const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceRadioSettings(const QString,const QString, const QString)), this,SLOT(handleEndDeviceRadioSettings(const QString, const QString,const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceVersionSettings(const QString, const QString, const QString)), this, SLOT(handleEndDeviceVersionSettings(const QString, const QString, const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceKeySettings(const QString,const QString)), this, SLOT(handleEndDeviceKeySettings(const QString,const QString)));

    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceOptimizerFamily(const QString,const int)), &m_parseOTADataThread, SLOT(handlePublishedEndDeviceOptimizerFamily(const QString,const int)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceParameterBlockInfoThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceParameterBlockInfoThreadFamilyError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishEndDeviceParameterBlockInfoThreadFlashError(const QString)), this, SLOT(handlePublishedErrors(const QString)));
    connect(&m_endDeviceParameterBlockInfoThread, SIGNAL(publishOptimizerFamilyShunt(int)), this,SLOT(handleOptimizerFamilyShunt(int)));

    connect(&m_loggerThread, SIGNAL(publishLoggerThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)));


    connect(this,SIGNAL(requestingAllEndDeviceParameterBlocks( const QString )), &m_parseParameterBlockThread, SLOT(handleRequestAllEndDeviceParameterBlocks( const QString  )));
    connect(this,SIGNAL(requestingMACParameterBlock(const QString)), &m_parseParameterBlockThread, SLOT(handleRequestMACParameterBlock(const QString)));
    connect(this,SIGNAL(publishConfirmGatewayCommand(const QString, const QString)),&m_checkGatewayCommandThread,SLOT(handleCheckingAGatewayCommand(const QString, const QString)));
    connect(this, SIGNAL(publishValidateOnlyEndDeviceCommandToSend(const QString)),&m_checkGatewayCommandThread,SLOT(handleValidatingFormatOfEndDeviceCommand(const QString)));

    connect(this,SIGNAL(publishError(const QString)), this, SLOT(handlePublishedErrors(const QString)));

    connect(ui->commandLineEdit, SIGNAL(returnPressed( void )), this, SLOT(handleCommandLineReturnPressed( void )));

    connect(ui->clearHistoryPushButton, SIGNAL(released( void )), this, SLOT(handleClearHistoryPushButton( void )));

    connect(this, SIGNAL(publishTerminate( void )), &m_receiveOTADataThread, SLOT(handleTerminate( void )));
    connect(this, SIGNAL(publishTerminate( void )), &m_endDeviceParameterBlockInfoThread, SLOT(handleTerminate( void )));
    connect(this, SIGNAL(publishTerminate( void )), &m_configurationThread, SLOT(handleTerminate( void )));
    connect(this, SIGNAL(publishTerminate( void )), &m_gatewayThread, SLOT(handleTerminate( void )));
    connect(this, SIGNAL(publishTerminate( void )), &m_parseOTADataThread, SLOT(handleTerminate( void )));
    connect(this, SIGNAL(publishTerminate( void )), &m_parseGatewayParameterBlockThread, SLOT(handleTerminate( void )));
    connect(this, SIGNAL(publishTerminate( void )), &m_outputLoggerThread, SLOT(handleTerminate( void )));
    connect(this, SIGNAL(publishTerminate( void )), &m_batchCommandsThread, SLOT(handlePublishTerminate( void )));

    // connect(this, SIGNAL(publishTerminate( void )), this, SLOT(handleUtilitiesUtilitiesDialogClose( void )));

    connect(ui->utilitiesSelectSNOrMACDial, SIGNAL(valueChanged( int )), this, SLOT(handleUtilitiesSelectSNOrMACValueChangedFromDial(int)));

    // SIGNAL textEdited chosen because signal not set IF string changed programatically (SIGNAL textChanged also set if programmatically changed).
    connect(ui->utilitiesSelectSNOrMACLineEdit, SIGNAL(textEdited(const QString & )), this, SLOT(handleUtilitiesSelectSNOrMACLineEdit(const QString &)));

    connect(ui->utilitiesUtilitiesDialogPushButton, SIGNAL(released(void)), this, SLOT(handleUtilitiesUtilitiesDialogPushButton( void )));

    connect(ui->utilitiesGatewaySetupPushButton, SIGNAL(released(void)), this, SLOT(handleUtilitiesGatewaySetupPushButton( void )));


    connect(ui->utilitiesBatchCommandsSelectPushButton, SIGNAL(released(void)), this, SLOT(handleUtilitiesBatchCommandsSelectPushButton(void)));
    connect(this, SIGNAL(publishUtilitiesBatchCommandsFile(const QString)), &m_batchCommandsThread, SLOT(handlePublishBatchFileToValidate(const QString)));
    connect(&m_batchCommandsThread, SIGNAL(publishBatchCommandsFileValidated(bool)), this, SLOT(handlePublishBatchCommandsFileValidated(bool)));
    connect(ui->utilitiesBatchCommandsStartStopPushButton, SIGNAL(released(void)), &m_batchCommandsThread, SLOT(handlePublishBatchFileStartStop( void )));
    connect(&m_batchCommandsThread, SIGNAL(publishBatchCommandsFileOperationBegun( void )), this, SLOT(handlePublishBatchCommandsFileOperationBegun( void )));
    connect(&m_batchCommandsThread, SIGNAL(publishBatchCommandsFileOperationEnded( void )), this, SLOT(handlePublishBatchCommandsFileOperationEnded( void )));
    connect(&m_batchCommandsThread, SIGNAL(publishBatchCommandToGateway(const QString)), &m_gatewayThread, SLOT(handleGatewayCommandToSend(const QString)));
    connect(&m_batchCommandsThread, SIGNAL(publishBatchCommandStatus(const QString )), this, SLOT(handlePublishBatchCommandStatus(const QString)));
    connect(&m_batchCommandsThread, SIGNAL(publishBatchCommandsThreadError(const QString)), this, SLOT(handlePublishedErrors(const QString)));



    connect(this, SIGNAL(publishCurrentActiveMAC(const QString)), &m_batchCommandsThread, SLOT(handlePublishCurrentActiveMAC(const QString)));


    saveAllParameters = false;
    m_OTAClickedRow = -1;

    configurationKeyToCheckBox[RequireStructureFile] = ui->configurationRequireStructureFileCheckBox;
    configurationKeyToCheckBox[IncludeCommandsInLogs] = ui->outputIncludeCommandsInLogCheckBox;
    configurationKeyToCheckBox[SaveParameterBlockData] = ui->configurationSaveParameterBlockCheckBox;
    configurationKeyToCheckBox[OutputLongFormatOTAData] = ui->outputOutputLongFormatOTADataCheckBox;
    configurationKeyToCheckBox[SuperCycleInOutput] = ui->outputSuperCycleInOutputCheckBox;
    configurationKeyToCheckBox[PerCentCommunication] = ui->configurationPerCentCommunicationCheckBox;
    configurationKeyToCheckBox[MACParameterBlockPopUp] = ui->configurationMACParameterBlockPopUpCheckBox;
    configurationKeyToCheckBox[SaveAmptGUI_X_Config] = ui->configurationSaveAmptGUI_XCheckBox;
    configurationKeyToCheckBox[ReadParametersFromFlash] = ui->parametersFlashCheckBox;
    configurationKeyToCheckBox[AutoReadParameters] = ui->parametersAutoReadCheckBox;
    configurationKeyToCheckBox[CheckCommands] = ui->confirmCommandCheckBox;
    configurationKeyToCheckBox[FilterOutUnitsWithOV] = ui->outputFilterOutUnitsWithOVCheckBox;
    configurationKeyToCheckBox[FilterOutputByBunch] = ui->outputFilterOutputByBunchCheckBox;
    configurationKeyToCheckBox[FilterOutputByNetIDRange] = ui->outputFilterOutputByNetIDRangeCheckBox;
    configurationKeyToCheckBox[FilterOutUnitsWithOC] = ui->outputFilterOutUnitsWithOCCheckBox;
    configurationKeyToCheckBox[OutputSortOTATableAscending] = ui->outputSortOTATableAscendingCheckBox;

    configurationKeyToSpinBox[FilterOutUnitsWithOVFilter] = ui->outputFilterOutUnitsWithOVSpinBox;
    configurationKeyToSpinBox[FilterOutputByBunchFilter] = ui->outputFilterOutputByBunchSpinBox;
    configurationKeyToSpinBox[FilterOutputByNetIDRangeFromFilter] = ui->outputFilterOutputNetIDStartToUseSpinBox;
    configurationKeyToSpinBox[FilterOutputByNetIDRangeToFilter] = ui->outputFilterOutputNetIDEndToUseSpinBox;
    configurationKeyToSpinBox[FilterOutUnitsWithOCFilter] = ui->outputFilterOutUnitsWithOCSpinBox;

    configurationKeyToComboBox[OptimerFamily] = ui->edSettingsOptimizerFamilyComboBox;

    configurationKeyToRadioButton[OutputSortOTATableNone] = ui->outputSortOTATableRadioButtonNone;
    configurationKeyToRadioButton[OutputSortOTATableSerialNumber] = ui->outputSortOTATableRadioButtonSerialNumber;
    configurationKeyToRadioButton[OutputSortOTATableMAC] = ui->outputSortOTATableRadioButtonMAC;
    configurationKeyToRadioButton[OutputSortOTATableNetwork] = ui->outputSortOTATableRadioButtonNetwork;

    configurationMap[RequireStructureFile] = TwoValueCheckBox;
    configurationMap[IncludeCommandsInLogs] = TwoValueCheckBox;
    configurationMap[SaveParameterBlockData] = TwoValueCheckBox;
    configurationMap[OutputLongFormatOTAData] = TwoValueCheckBox;
    configurationMap[SuperCycleInOutput] = TwoValueCheckBox;
    configurationMap[MACParameterBlockPopUp] = TwoValueCheckBox;
    configurationMap[PerCentCommunication] = TwoValueCheckBox;
    configurationMap[SaveAmptGUI_X_Config] = TwoValueCheckBox;
    configurationMap[ReadParametersFromFlash] = TwoValueCheckBox;
    configurationMap[AutoReadParameters] = TwoValueCheckBox;
    configurationMap[CheckCommands] = TwoValueCheckBox;
    configurationMap[FilterOutUnitsWithOV] = TwoValueCheckBox;
    configurationMap[FilterOutUnitsWithOVFilter] = TwoHundredFiftySixValueSpinBox;
    configurationMap[FilterOutputByBunch] = TwoValueCheckBox;
    configurationMap[FilterOutputByBunchFilter] = PositiveIntegerSpinBox;
    configurationMap[FilterOutputByNetIDRange] = TwoValueCheckBox;
    configurationMap[FilterOutputByNetIDRangeFromFilter] = NetIDSpinBox;
    configurationMap[FilterOutputByNetIDRangeToFilter] = NetIDSpinBox;
    configurationMap[FilterOutUnitsWithOC] = TwoValueCheckBox;
    configurationMap[FilterOutUnitsWithOCFilter] = TwoHundredFiftySixValueSpinBox;
    configurationMap[OutputSortOTATableAscending] = TwoValueCheckBox;
    configurationMap[OutputSortOTATableNone] = BooleanRadioButton;
    configurationMap[OutputSortOTATableSerialNumber] = BooleanRadioButton;
    configurationMap[OutputSortOTATableMAC] = BooleanRadioButton;
    configurationMap[OutputSortOTATableNetwork] = BooleanRadioButton;
    configurationMap[OptimerFamily] = OptimizerFamilyComboBox;


    emit(startSignal());

    ui->parametersWritePushButton->setEnabled(false);

    if (ui->parametersAutoReadCheckBox->isChecked() == true)
    {
        emit publishParametersAutoRead(true);
    }
    else
    {
        publishParametersAutoRead(false);
    }
}


AmptGUI_X::~AmptGUI_X()
{
    delete ui;
}

void AmptGUI_X::handleConfigurationLongFormatOTAData(const int s)
{
    const QString LongFormatCommand("L 1");
    const QString ShortFormatCommand("L 0");

    if (s == 2)
    {
        // qDebug() << Q_FUNC_INFO << " sending " << LongFormatCommand;
        sendConfigurationCommandToGateway(LongFormatCommand);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " sending " << ShortFormatCommand;
        sendConfigurationCommandToGateway(ShortFormatCommand);
    }
}

void AmptGUI_X::handleConfigurationSaveParameterBlockCheckBox(int s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: s=" << QString::number(s);
    if (s == 2)
    {
        emit publishEndDeviceSaveParameterBlockInfo(true);
    }
    else
    {
        emit publishEndDeviceSaveParameterBlockInfo(false);
    }
}

void AmptGUI_X::handleConfigurationSuperCyclesInOutput(const int s)
{
    const QString SuperCyclesInOutput("K 9 1");
    const QString SuperCyclesNotInOutput("K 9 0");

    // qDebug() << Q_FUNC_INFO << " integer arg. is " << s;

    if (s == 2)
    {
        // qDebug() << Q_FUNC_INFO << " sending " << SuperCyclesInOutput;
        sendConfigurationCommandToGateway(SuperCyclesInOutput);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " sending " << SuperCyclesNotInOutput;
        sendConfigurationCommandToGateway(SuperCyclesNotInOutput);
    }
}

void AmptGUI_X::configurationAtStart()
{
    // check if configuration file exists, if so, try to access it and obtain settings ...
    // else just check state of 'things' to determine start up actions.

    // qDebug() << Q_FUNC_INFO << " startup configuration begin.";
    if (ui->outputOutputLongFormatOTADataCheckBox->isChecked() == true)
    {
        handleConfigurationLongFormatOTAData(2);
    }
    else
    {
         handleConfigurationLongFormatOTAData(0);
    }

    if (ui->outputSuperCycleInOutputCheckBox->isChecked() == true)
    {
        handleConfigurationSuperCyclesInOutput(2);
    }
    else
    {
        handleConfigurationSuperCyclesInOutput(0);
    }

    // qDebug() << Q_FUNC_INFO << " startup configuration end.";
}

void AmptGUI_X::initializeGUI()
{
    // qDebug() << Q_FUNC_INFO << " begin.";
    m_parseOTADataThread.setCurrentOptimizerFamily(ui->edSettingsOptimizerFamilyComboBox->currentText());

    if ( ui->commandRadioButtonGateway->isChecked())
    {
        ui->networkEnableJoinPushButton->setEnabled(true);
        ui->networkDisableJoinPushButton->setEnabled(true);
        ui->networkDisbandNetworkPushButton->setEnabled(true);
        ui->saveSmallFPushButton->setEnabled(false);
        ui->saveBigFPushButton->setEnabled(false);
    }
    else
    {
        ui->networkEnableJoinPushButton->setEnabled(false);
        ui->networkDisableJoinPushButton->setEnabled(false);
        ui->networkDisbandNetworkPushButton->setEnabled(false);
        ui->saveSmallFPushButton->setEnabled(true);
        ui->saveBigFPushButton->setEnabled(true);
    }

    ui->networkNCommandPushButton->setEnabled(false);



    ui->networkNCommandMACLineEdit->setCursorPosition(0);
    ui->networkNCommandMACLineEdit->clear();
    ui->networkNCommandMACLineEdit->setEnabled(true);
    ui->networkNCommandMACLineEdit->setClearButtonEnabled(true);

    ui->networkNCommandArgumentLineEdit->setCursorPosition(0);
    ui->networkNCommandArgumentLineEdit->clear();
    ui->networkNCommandArgumentLineEdit->setEnabled(true);
    ui->networkNCommandArgumentLineEdit->setClearButtonEnabled(true);

    if ((ui->commandRadioButtonMAC->isChecked()) || (ui->commandRadioButtonBroadcast->isChecked()))
    {
        ui->networkEndOfTestPushButton->setEnabled(true);
    }
    else
    {
        ui->networkEndOfTestPushButton->setEnabled(false);
    }

    ui->utilitiesBatchCommandsGroupBox->setEnabled(true);
    ui->utilitiesBatchCommandsSelectLineEdit->setEnabled(false);
    ui->utilitiesBatchCommandsSelectPushButton->setEnabled(true);
    ui->utilitiesBatchCommandsStartStopLineEdit->setEnabled(false);
    ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);

    /*
    ui->outputSortOTATableRadioButtonNone->setChecked(true);
    ui->outputSortOTATableRadioButtonSerialNumber->setChecked(false);
    ui->outputSortOTATableRadioButtonMAC->setChecked(false);
    ui->outputSortOTATableRadioButtonNetwork->setChecked(false);
    ui->outputSortOTATableAscendingCheckBox->setChecked(true);
    */

    // qDebug() << Q_FUNC_INFO << " complete.";
}

void AmptGUI_X::startConfigurationSlot()
{
    // qDebug() << Q_FUNC_INFO << " begin ...";
    // qDebug() << Q_FUNC_INFO << " standardlocations:" << QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString docsDirectory = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0);
    QString AmptGUI_X_BaseDir = docsDirectory + "/AmptGUI_X";

    m_configurationThread.startConfigurationThreadInterface(1000,AmptGUI_X_BaseDir);
    // qDebug() << Q_FUNC_INFO << " Configuration thread running : " << m_configurationThread.isRunning();
}

void AmptGUI_X::startLoggerSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting LoggerThread ...";
    QString directory("./");

    m_loggerThread.startLoggerThreadInterface(1000, directory);
    // qDebug() << Q_FUNC_INFO << " LoggerThread running : " << m_loggerThread.isRunning();
}

void AmptGUI_X::startOutputLoggerSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting outputLoggerThread ...";

    m_outputLoggerThread.startLoggerThreadInterface(1000);
    // qDebug() << Q_FUNC_INFO << " outputLoggerThread running : " << m_outputLoggerThread.isRunning();
}

void AmptGUI_X::startReceiveOTADataSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting ReceiveOTADataThread ...";
    m_receiveOTADataThread.startReceiveOTADataThreadInterface(1000,false);
    // qDebug() << Q_FUNC_INFO << " ReceiveOTADataThread running: " << m_receiveOTADataThread.isRunning();
}

void AmptGUI_X::startParseOTADataSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting ParseOTADataThread ...";
    m_parseOTADataThread.startParseOTADataThreadInterface(1000,false);
    // qDebug() << Q_FUNC_INFO << " ParseOTADataThread running: " << m_parseOTADataThread.isRunning();
}

void AmptGUI_X::startParseParameterBlockSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting ParseParameterBlockThread ...";
    m_parseParameterBlockThread.startParseParameterBlockThreadInterface(1000,false);

    // qDebug() << Q_FUNC_INFO << " ParseParameterBlockThread running: " << m_parseParameterBlockThread.isRunning();

    QString currentOptimizerFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();
    bool     readFromFlash = ui->parametersFlashCheckBox->isChecked();
    m_parseParameterBlockThread.setCurrentOptimizerFamily(currentOptimizerFamily);
    if (readFromFlash)
    {
        m_parseParameterBlockThread.setParameterBlockReadFrom(1);
    }
    else
    {
        m_parseParameterBlockThread.setParameterBlockReadFrom(0);
    }
}

void AmptGUI_X::startEndDeviceParameterBlockInfoSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting EndDeviceParameterBlockInfoThread ...";
    QString docsDirectory = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0);

    // m_configurationThread.startConfigurationThreadInterface(1000,docsDirectory);
    m_endDeviceParameterBlockInfoThread.startEndDeviceParameterBlockInfoThreadInterface(1000,false, docsDirectory);
    // qDebug() << Q_FUNC_INFO << " EndDeviceParameterBlockInfoThread running: " << m_endDeviceParameterBlockInfoThread.isRunning();
    QString currentOptimizerFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();
    bool     readFromFlash = ui->parametersFlashCheckBox->isChecked();
    m_endDeviceParameterBlockInfoThread.setCurrentOptimizerFamily(currentOptimizerFamily);
    if (readFromFlash)
    {
        m_endDeviceParameterBlockInfoThread.setParameterBlockReadFrom(1);
    }
    else
    {
        m_endDeviceParameterBlockInfoThread.setParameterBlockReadFrom(0);
    }
}

void AmptGUI_X::startParseGatewayParameterBlockSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting ParseGatewayParameterBlockThread ...";
    m_parseGatewayParameterBlockThread.startParseGatewayParameterBlockThreadInterface(1000,false);
    //qDebug() << Q_FUNC_INFO << " ParseGatewayParameterBlockThread running: " << m_parseGatewayParameterBlockThread.isRunning();
}

void AmptGUI_X::startCheckGatewayCommandSlot()
{
    // qDebug() << Q_FUNC_INFO << " starting CheckGatewayCommandThread ...";
    m_checkGatewayCommandThread.startCheckGatewayCommandThreadInterface(1000,false);
    //qDebug() << Q_FUNC_INFO << " CheckGatewayCommandThread running: " << m_checkGatewayCommandThread.isRunning();
}

void AmptGUI_X::startBatchCommandsSlot()
{
    m_batchCommandsThread.startBatchCommandsThreadInterface(1000);
}



void AmptGUI_X::handleGatewayIsNotOperational( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Received.";
    ui->gatewayResetGatewayPushButton->setEnabled(false);
}

void AmptGUI_X::handleGatewayIsOperational( void )
{
    // qDebug() << Q_FUNC_INFO << " INFO: Received.";
    ui->gatewayResetGatewayPushButton->setEnabled(false);
    startUpCommands();
    ui->gatewayResetGatewayPushButton->setEnabled(true);
}


bool AmptGUI_X::startGatewaySlot()
{
    bool retValue = false;
    // qDebug() << Q_FUNC_INFO << " starting gatewayThread ...";
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    // qDebug() << Q_FUNC_INFO << "Looking for Gateway Device";
    // qDebug() << Q_FUNC_INFO << "Total number of possible ports Gateway could be using: " << serialPortInfos.count();

    const QString blankString = "N/A";
    QString description;
    QString manufacturer;
    const QString amptSolar("AMPTSOLAR");
    const QString amptGWSerialNumber("2011090201");
    bool foundGateway = false;
    QString serialNumber;
    QString gatewayPortName("");
    bool gatewayPortBusy = true;

    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);


    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();

        // qDebug() << Q_FUNC_INFO << "manufacturer:" << manufacturer << " description:" << description << " serialNumber:" << serialNumber;

        // LBC 07/28/2018 - switch to serialNumber until windows gateway issue figured out. if (manufacturer == amptSolar)
        if (serialNumber == amptGWSerialNumber) // "2011090201")
        {
            /*
            qDebug() << Qt::endl;

            qDebug() << Q_FUNC_INFO << "\tGateway Port: " << serialPortInfo.portName() << Qt::endl
            << "\tGateway Location: " << serialPortInfo.systemLocation() << Qt::endl
            << "\tGateway Description: " << (!description.isEmpty() ? description : blankString) << Qt::endl
            << "\tGateway Manufacturer: " << (!manufacturer.isEmpty() ? manufacturer : blankString) << Qt::endl
            << "\tGateway Serial number: " << (!serialNumber.isEmpty() ? serialNumber : blankString) << Qt::endl
            << "\tGateway Vendor Identifier: " << (serialPortInfo.hasVendorIdentifier()
                                         ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16)
                                         : blankString) << Qt::endl
            << "\tGateway Product Identifier: " << (serialPortInfo.hasProductIdentifier()
                                          ? QByteArray::number(serialPortInfo.productIdentifier(), 16)
                                          : blankString) << Qt::endl
            << "\tGateway Busy: " << (serialPortInfo.isBusy() ? "Yes" : "No");
            */

            foundGateway = true;
            gatewayPortBusy  = serialPortInfo.isBusy();
            gatewayPortName = serialPortInfo.portName();
            break;
        }
    }
    CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    if (foundGateway == true)
    {
        if (gatewayPortBusy == false)
        {
            // qDebug() << Q_FUNC_INFO << " Gateway Port Selected: " << gatewayPortName << " attemping to configure...";
            m_gatewayThread.startGatewayInterface(gatewayPortName,1000,false);
            retValue = true;
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " Status: Error, your Gateway is not running, gateway port busy.";

            QString InfoStr(Q_FUNC_INFO);
            InfoStr += " ERROR: " + CurrentDateTime + " USB Gateway is not running, gateway port is busy/already in use, exiting...";
            emit publishError(InfoStr);

            QMessageBox * probConfirmDialog = new QMessageBox(this);
            probConfirmDialog->setText(InfoStr);

            /*QAbstractButton* pButtonOk = */  probConfirmDialog->addButton(tr("QUIT"), QMessageBox::YesRole);
            /* QAbstractButton *pButtonNo = */ // probConfirmDialog->addButton(tr("NO"), QMessageBox::NoRole);
            int nMode = probConfirmDialog->exec();
            delete probConfirmDialog;
            qDebug() << Q_FUNC_INFO << " INFO nMode=" << nMode << " => " << ((nMode == 0) ? " Quitting" : " Would stay");

        }
    }
    else
    {
        QString InfoStr(Q_FUNC_INFO);
        InfoStr += " ERROR: " + CurrentDateTime + " USB Gateway is not running, active Ampt Gateway not found, plug in USB Gateway before trying again...";
        emit publishError(InfoStr);

        QMessageBox * prob2ConfirmDialog = new QMessageBox(this);
        prob2ConfirmDialog->setText(InfoStr);
        /*QAbstractButton* pButtonOk = */  prob2ConfirmDialog->addButton(tr("QUIT"), QMessageBox::YesRole);
        /* QAbstractButton *pButtonNo = */ // prob2ConfirmDialog->addButton(tr("NO"), QMessageBox::NoRole);
        prob2ConfirmDialog->exec();
        delete prob2ConfirmDialog;
        // qDebug() << Q_FUNC_INFO << " INFO nMode=" << nMode << " => " << ((nMode == 0) ? " Quitting" : " Would stay");
        emit publishTerminate();
    }
    return retValue;
}

void AmptGUI_X::startUpCommands()
{
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    bool sentStartUpCommands = false;
    quint8 attemptsToSendCommands = 0;
    const quint8 maxAttemptsToSendCommands = 3;
    // qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " begin ...";

    while ((sentStartUpCommands == false) && (attemptsToSendCommands <= maxAttemptsToSendCommands))
    {
        if (m_gatewayThread.isRunning() == true)
        {
            m_gatewayThread.commandToSend("?\r\n");
            // qDebug() << Q_FUNC_INFO << " number of seconds since Epoch: " << QDateTime::currentSecsSinceEpoch();
            m_gatewayThread.commandToSend("T " + QString::number( QDateTime::currentSecsSinceEpoch() ) + "\r\n");

            sentStartUpCommands = true;
        }
        else
        {
            QThread::msleep(200);
            attemptsToSendCommands++;
        }
    }

    if (sentStartUpCommands == false)
    {
        QString ErrorStr(Q_FUNC_INFO);
        CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to send startUpCommands..., gateway connected? ";
        qDebug() << ErrorStr;
        emit publishError(ErrorStr);
        // LBC should send signal to exit out of program?
    }

    if (sentStartUpCommands == true)
    {
        if (ui->outputSuperCycleInOutputCheckBox->isChecked() == true)
        {
            m_gatewayThread.commandToSend("K 9 1");
        }
        else
        {
            m_gatewayThread.commandToSend("K 9 0");
        }
    }
    /*
    CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " end ...";
    */
}

void AmptGUI_X::handleFilterOTADataByBunch( int state )
{
    bool ok = false;
    qDebug() << Q_FUNC_INFO << " INFO: signal received: " << state;

    if (state == 2)
    {
        m_filteringOnBunch = (ui->outputFilterOutputByBunchSpinBox->text()).toInt(&ok,10);
    }
    else
    {
        m_filteringOnBunch = -1;
    }
    qDebug() << Q_FUNC_INFO << " INFO: m_filteringOnBunch set to " << m_filteringOnBunch;
}

void AmptGUI_X::handleFilterOTADataByNetIDRange(int state)
{
    bool ok = false;
    qDebug() << Q_FUNC_INFO << " INFO: signal received: " << state;

    if (state == 2)
    {
        m_filteringOnNetIDRange = true;
        m_filteringNetIDStart = (ui->outputFilterOutputNetIDStartToUseSpinBox->text()).toInt(&ok);
        m_filteringNetIDEnd = (ui->outputFilterOutputNetIDEndToUseSpinBox->text().toInt(&ok));
    }
    else
    {
        m_filteringOnNetIDRange = false;
        m_filteringNetIDStart = 0;
        m_filteringNetIDEnd = 15;
    }
    qDebug() << Q_FUNC_INFO << " INFO: m_filteringOnNetIDRange set to " << m_filteringOnNetIDRange << " :" << m_filteringNetIDStart << "  :" << m_filteringNetIDEnd;
}

void AmptGUI_X::handleFilterOTADataUnitsWithOVValue( int state )
{
    bool ok = false;
    qDebug() << Q_FUNC_INFO << " INFO: signal received: " << state;

    if (state == 2)
    {
        m_filteringOutByOV = (ui->outputFilterOutUnitsWithOVSpinBox->text()).toInt(&ok,10);
    }
    else
    {
        m_filteringOutByOV = -1;
    }
    qDebug() << Q_FUNC_INFO << " INFO: m_filteringOutByOV set to " << m_filteringOutByOV;
}

void AmptGUI_X::handleFilterOTADataUnitsWithOCValue( int state )
{
    bool ok = false;
    qDebug() << Q_FUNC_INFO << " INFO: signal received: " << state;

    if (state == 2)
    {
        m_filteringOutByOC = (ui->outputFilterOutUnitsWithOCSpinBox->text()).toInt(&ok,10);
    }
    else
    {
        m_filteringOutByOC = -1;
    }
    qDebug() << Q_FUNC_INFO << " INFO: m_filteringOutByOC set to " << m_filteringOutByOC;
}

void AmptGUI_X::showParsedOTAData(const QString &s, const QString &r)
{
    bool ok = false;
    // qDebug() << Q_FUNC_INFO << " INFO: s:" << s << " r.at(0):" << r.at(0);

    /* The next four lines speeds up the 'un-highlighting' of the previous selected mac line */
    QPalette p = palette();
    p.setColor(QPalette::Inactive, QPalette::Highlight, Qt::white ); //p.color(QPalette::Active, QPalette::Highlight));
    p.setColor(QPalette::Active, QPalette::Highlight, Qt::white ); //p.color(QPalette::Active, QPalette::Highlight));
    ui->OTATableWidget->setPalette(p);

    ui->commandLineEdit->setEnabled(true);
    ui->commandLineEditPushButton->setEnabled(true);
    QString macInPullDown = ui->commandMACComboBox->currentText();

    QStringList restOfData = r.split(",");

    if (restOfData.at(0) == m_oneMACOTAData)
    {
        emit publishOneMACOTAData(restOfData);
    }

    // qDebug() << Q_FUNC_INFO << " INFO: s:" << s << " restOfData.at(0):" << restOfData.at(0);

    ui->OTATableWidget->setAlternatingRowColors(true);
    // ui->OTATableWidget->setStyleSheet("alternate-background-color: lightGray;background-color: white;");
    // ui->OTATableWidget->setStyleSheet("alternate-background-color: white;background-color: lightGray;");
    ui->OTATableWidget->setStyleSheet("alternate-background-color: white;background-color: white;");

    // qDebug() << Q_FUNC_INFO << " restOfData size: " << restOfData.size() << " elements: " << restOfData.at(0) << " bunch: " << restOfData.at(17) << Qt::endl;

   // qDebug() << Q_FUNC_INFO << " INFO: m_filteringOnBunch: " << m_filteringOnBunch << " BunchIndex:" << BunchIndex << " restOfData.at(BunchIndex - 1):" << restOfData.at(BunchIndex -1 ).toInt(&ok,10);
    if ((m_filteringOnBunch > -1) && ((restOfData.at(BunchIndex -1)).toInt(&ok,10) != m_filteringOnBunch))
    {
        // LBC Should a QStringList of SNs be kept of Optimizers already filtered?
        QTableWidgetItem *snExists = nullptr;
        for(int i = 0; i < ui->OTATableWidget->rowCount();i++)
        {
            snExists = ui->OTATableWidget->item(i,0);
            if ((snExists !=nullptr) && (snExists->text() == s))
            {
                ui->OTATableWidget->removeRow(i);
                // Check if activeMAC is set, if so, need to unset and broadcast this
                break;
            }
        }
        return; // LBC Is this correct behavior?
    }

    // qDebug() << Q_FUNC_INFO << " INFO: m_filteringOutByOV: " << m_filteringOutByOV << " OVIndex:" << OVIndex << " restOfData.at(OVIndex - 1):" << restOfData.at(OVIndex -1 ).toInt(&ok,10);

    if ((m_filteringOutByOV > -1) && ((restOfData.at(OVIndex - 1)).toInt(&ok,10) == m_filteringOutByOV))
    {
        // LBC Should a QStringList of SNs be kept of Optimizers already filtered?
        QTableWidgetItem *snExists = nullptr;
        for(int i = 0; i < ui->OTATableWidget->rowCount();i++)
        {
            snExists = ui->OTATableWidget->item(i,0);
            if ((snExists !=nullptr) && (snExists->text() == s))
            {
                ui->OTATableWidget->removeRow(i);
                // Check if activeMAC is set, if so, need to unset and broadcast this
                break;
            }
        }
        return; // LBC Is this correct behavior?
    }

    //qDebug() << Q_FUNC_INFO << " INFO: m_filteringOutByOC: " << m_filteringOutByOC << " OCIndex:" << OCIndex << " restOfData.at(OCIndex - 1):" << restOfData.at(OCIndex -1 ).toInt(&ok,10);

    if ((m_filteringOutByOC > -1) && ((restOfData.at(OCIndex - 1)).toInt(&ok,10) == m_filteringOutByOC))
    {
        // LBC Should a QStringList of SNs be kept of Optimizers already filtered?
        QTableWidgetItem *snExists = nullptr;
        for(int i = 0; i < ui->OTATableWidget->rowCount();i++)
        {
            snExists = ui->OTATableWidget->item(i,0);
            if ((snExists !=nullptr) && (snExists->text() == s))
            {
                ui->OTATableWidget->removeRow(i);
                // Check if activeMAC is set, if so, need to unset and broadcast this
                break;
            }
        }
        return; // LBC Is this correct behavior?
    }

    //qDebug() << Q_FUNC_INFO << " INFO: m_filteringOnNetIDRange: " << m_filteringOnNetIDRange << " SlotIndex:" << SlotIndex << " restOfData.at(SlotIndex - 1):" << restOfData.at(SlotIndex -1 ).toInt(&ok,10);

    if ((m_filteringOnNetIDRange == true) && (((restOfData.at(SlotIndex - 1)).toInt(&ok,10) < m_filteringNetIDStart) || ((restOfData.at(SlotIndex - 1)).toInt(&ok,10) > m_filteringNetIDEnd)))
    {
        // qDebug() << Q_FUNC_INFO << " INFO: filtering on netID range ...";
        // LBC Should a QStringList of SNs be kept of Optimizers already filtered?
        QTableWidgetItem *snExists = nullptr;
        for(int i = 0; i < ui->OTATableWidget->rowCount();i++)
        {
            snExists = ui->OTATableWidget->item(i,0);
            if ((snExists !=nullptr) && (snExists->text() == s))
            {
                ui->OTATableWidget->removeRow(i);
                // Check if activeMAC is set, if so, need to unset and broadcast this
                break;
            }
        }
        return; // LBC Is this correct behavior?
    }

    if (ui->OTATableWidget->rowCount() == 0)
    {
        // qDebug() << Q_FUNC_INFO << " INFO: first row being added, serial number of " << s <<" would sort by m_outputSortOTATableBy = " << QString::number(m_outputSortOTATableBy);
        // ui->OTATableWidget->clear();
        ui->OTATableWidget->setRowCount(1);
        // ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
        QTableWidgetItem * g = new QTableWidgetItem(s);

        g->setBackgroundColor(Qt::white);
        ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,g);

        for (int i = 0; i < restOfData.size(); i++)
        {
            g = new QTableWidgetItem(restOfData.at(i));
            g->setBackgroundColor(Qt::white);
            ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,i+1,g);
        }
        if ((ui->commandMACComboBox->findText(restOfData.at(0))) == -1)
        {
            ui->commandMACComboBox->addItem(restOfData.at(0));
            emit newMACDiscovered(restOfData.at(0));
        }
        ui->readCoefficientsPushButton->setEnabled(true);
    }
    else
    {
        bool foundSN = false;
        QTableWidgetItem *snExists = nullptr;
        int foundRow = -1;

        for (int i = 0; i < ui->OTATableWidget->rowCount(); i++)
        {
            snExists = ui->OTATableWidget->item(i,0);

            if ((snExists != nullptr) && (snExists->text() == s))
            {
                foundSN = true;
                foundRow = i;
                break;
            }
        }
        if (foundSN == true)
        {
            bool protectionOn = false;
            bool repeaterOrSlave = false;
            int netStatusAsInt = (restOfData.at(OTA_Status_INDEX)).toInt();

            if ((netStatusAsInt < AmptLowestGoodStatusValue ) || (netStatusAsInt > AmptHighestGoodStatusValue))
            {
                if ((netStatusAsInt > AmptHighestGoodStatusValue) && (netStatusAsInt < 436))
                {
                     protectionOn = true;
                }
                else if ((netStatusAsInt % 50) <= 10)
                {
                    repeaterOrSlave = true;
                }
            }

            bool activeMac = (macInPullDown == restOfData.at(0));
            QTableWidgetItem * g = new QTableWidgetItem(s);
            g->setBackgroundColor(Qt::white);
            ui->OTATableWidget->setItem(foundRow,0,g);
            if (activeMac)
            {
                ui->OTATableWidget->item(foundRow,0)->setData(Qt::BackgroundRole, QColor (224,224,224));
                ui->OTATableWidget->item(foundRow,0)->setSelected(false);
            }
            else
            {
                ui->OTATableWidget->item(foundRow,0)->setData(Qt::BackgroundRole, QColor (255,255,255));
            }

            if (protectionOn == true)
                ui->OTATableWidget->item(foundRow,0)->setBackground(Qt::red);
            else if (repeaterOrSlave == true)
                ui->OTATableWidget->item(foundRow,0)->setBackgroundColor(Qt::cyan);
            for (int i = 0; i < restOfData.size(); i++)
            {
                g = new QTableWidgetItem(restOfData.at(i));
                g->setBackgroundColor(Qt::white);

                ui->OTATableWidget->setItem(foundRow,i+1,g);

                // ui->OTATableWidget->setItem(foundRow,i+1,new QTableWidgetItem(restOfData.at(i)));
                if (i == OTA_Status_INDEX)
                {
                    if (protectionOn == true)
                        ui->OTATableWidget->item(foundRow, i + 1)->setBackground(Qt::red);
                    else if (repeaterOrSlave == true)
                        ui->OTATableWidget->item(foundRow, i + 1)->setBackgroundColor(Qt::cyan);
                    else if (activeMac)
                    {
                        ui->OTATableWidget->item(foundRow,i+1)->setData(Qt::BackgroundRole, QColor (224,224,224));
                        ui->OTATableWidget->item(foundRow,i+1)->setSelected(false);
                    }
                    else
                    {
                        ui->OTATableWidget->item(foundRow,i+1)->setData(Qt::BackgroundRole, QColor (255,255,255));
                    }
                }
                else if (activeMac)
                {
                    ui->OTATableWidget->item(foundRow,i+1)->setData(Qt::BackgroundRole, QColor (224,224,224));
                    ui->OTATableWidget->item(foundRow,i+1)->setSelected(false);
                    // ensure module, MPP stuff set correctly
                    // qDebug() << Q_FUNC_INFO << " INFO: Module:" << restOfData.at(ModuleIndex - 1) << " ModuleIndex - 1:" << ModuleIndex -1 << " MPP:" << restOfData.at(14);
                    // if ((ui->moduleSendPushButton->isEnabled() == false) &&  (restOfData.at(ModuleIndex - 1) != ui->moduleComboBox->currentText()))
                    if ( (restOfData.at(ModuleIndex - 1) != ui->moduleComboBox->currentText()) && (ui->moduleSendPushButton->isEnabled() == false))
                    {
                        ui->moduleDial->setEnabled(false);
                        ui->moduleComboBox->setEnabled(false);
                        if (restOfData.at(ModuleIndex - 1) == "Off")
                            ui->moduleComboBox->setCurrentIndex(zero);
                        else
                            ui->moduleComboBox->setCurrentIndex(1);

                        ui->moduleSendPushButton->setEnabled(false);
                        ui->moduleComboBox->setEnabled(true);
                        ui->moduleDial->setEnabled(true);
                    }
                    if ( (restOfData.at(MPPIndex - 1) != ui->mppComboBox->currentText()) && (ui->mppSendPushButton->isEnabled() == false))
                    //if ((ui->mppSendPushButton->isEnabled() == false) && (restOfData.at(MPPIndex - 1) != ui->mppComboBox->currentText()))
                    {
                        ui->mppDial->setEnabled(false);
                        ui->mppComboBox->setEnabled(false);
                        if (restOfData.at(MPPIndex - 1) == "Off")
                            ui->mppComboBox->setCurrentIndex(zero);
                        else
                            ui->mppComboBox->setCurrentIndex(1);
                        ui->mppSendPushButton->setEnabled(false);
                        ui->mppComboBox->setEnabled(true);
                        ui->mppDial->setEnabled(true);
                    }
                    if ( (restOfData.at(OVIndex - 1) != ui->ovSpinBox->text()) && (ui->ovSendPushButton->isEnabled() == false))
                    {
                        ui->ovDial->setEnabled(false);
                        ui->ovSpinBox->setEnabled(false);
                        ui->ovSpinBox->setValue(restOfData.at(OVIndex - 1).toInt());
                        ui->ovDial->setEnabled(true);
                        ui->ovSpinBox->setEnabled(true);
                        ui->ovSendPushButton->setEnabled(false);
                    }
                    if ( (restOfData.at(OCIndex - 1) != ui->ocSpinBox->text()) && (ui->ocSendPushButton->isEnabled() == false))
                    {
                        ui->ocDial->setEnabled(false);
                        ui->ocSpinBox->setEnabled(false);
                        ui->ocSpinBox->setValue(restOfData.at(OCIndex - 1).toInt());
                        ui->ocDial->setEnabled(true);
                        ui->ocSpinBox->setEnabled(true);
                        ui->ocSendPushButton->setEnabled(false);
                    }
                }
                else
                {
                   // ui->OTATableWidget->item(foundRow,i+1)->setData(Qt::BackgroundRole, QColor (255,255,255));
                }
            }
            // LBC uncomment this to see QModelIndex info qDebug() << Q_FUNC_INFO << " currentSelectedRow:" << ui->OTATableWidget->currentIndex();
            // ui->OTATableWidget->setItem(foundRow,1,new QTableWidgetItem(r));
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " INFO:UUUUIIIUUUYYY  PPPPPP got an unmatched non first table entry, serial number " << s << " sort by " << m_outputSortOTATableBy;
            // qDebug() << Q_FUNC_INFO << " INFO: rowCount currently " << QString::number(ui->OTATableWidget->rowCount());

            ui->OTATableWidget->setSortingEnabled(false);
            ui->OTATableWidget->setRowCount(ui->OTATableWidget->rowCount() + 1);
            //ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
            ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
            for (int i = 0; i < restOfData.size(); i++)
            {
                ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,i+1,new QTableWidgetItem(restOfData.at(i)));
                //ui->OTATableWidget->item(ui->OTATableWidget->rowCount()-1,i+1) ->setData(Qt::BackgroundRole, QColor (128,128,128));
            }
            // ui->OTATableWidget->setSortingEnabled(true);

            if (m_outputSortOTATableBy == OutputSortOTATableByNone)
            {
                /*
                ui->OTATableWidget->setRowCount(ui->OTATableWidget->rowCount() + 1);
                //ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
                ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
                for (int i = 0; i < restOfData.size(); i++)
                {
                    ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,i+1,new QTableWidgetItem(restOfData.at(i)));
                    //ui->OTATableWidget->item(ui->OTATableWidget->rowCount()-1,i+1) ->setData(Qt::BackgroundRole, QColor (128,128,128));
                }
                */
            }
            else if (m_outputSortOTATableBy == OutputSortOTATableBySerialNumber)
            {
                /*
                int i = 0;
                ui->OTATableWidget->setRowCount(ui->OTATableWidget->rowCount() + 1);
                //ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
                ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
                for (i = 0; i < restOfData.size(); i++)
                {
                    ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,i+1,new QTableWidgetItem(restOfData.at(i)));
                    //ui->OTATableWidget->item(ui->OTATableWidget->rowCount()-1,i+1) ->setData(Qt::BackgroundRole, QColor (128,128,128));
                }
                */
                ui->OTATableWidget->setSortingEnabled(true);
                if (m_outputSortOTATableAscending == true)
                {
                    ui->OTATableWidget->sortItems(SerialNumIndex,Qt::AscendingOrder);
                }
                else
                {
                    ui->OTATableWidget->sortItems(SerialNumIndex,Qt::DescendingOrder);
                }
            }
            else if (m_outputSortOTATableBy == OutputSortOTATableByMAC)
            {
                /*
                int i = 0;
                ui->OTATableWidget->setRowCount(ui->OTATableWidget->rowCount() + 1);
                //ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
                ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,0,new QTableWidgetItem(s));
                for (i = 0; i < restOfData.size(); i++)
                {
                    ui->OTATableWidget->setItem(ui->OTATableWidget->rowCount()-1,i+1,new QTableWidgetItem(restOfData.at(i)));
                    //ui->OTATableWidget->item(ui->OTATableWidget->rowCount()-1,i+1) ->setData(Qt::BackgroundRole, QColor (128,128,128));
                }
                */
                ui->OTATableWidget->setSortingEnabled(true);
                if (m_outputSortOTATableAscending == true)
                {
                    ui->OTATableWidget->sortItems(MACIndex,Qt::AscendingOrder);
                }
                else
                {
                    ui->OTATableWidget->sortItems(MACIndex,Qt::DescendingOrder);
                }

            }
            else if (m_outputSortOTATableBy == OutputSortOTATableByNetwork)
            {
                ui->OTATableWidget->setSortingEnabled(true);
                if (m_outputSortOTATableAscending == true)
                {
                    ui->OTATableWidget->sortItems(SlotIndex,Qt::AscendingOrder);
                }
                else
                {
                    ui->OTATableWidget->sortItems(SlotIndex,Qt::DescendingOrder);
                }

            }
            else
            {
                QString errString(Q_FUNC_INFO);
                QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                errString += " ERROR: " + CurrentDateTime + " unknown SortOTATableBy value of " + QString::number(m_outputSortOTATableBy) + " for serial number " + s;
                emit publishError(errString);
                qDebug() << errString;
            }

            // qDebug() << Q_FUNC_INFO << " INFO:UUUUIIIUUUYYY  FFFFFFFF finished == got an unmatched non first table entry, serial number " << s << " sort by " << m_outputSortOTATableBy;
            // qDebug() << Q_FUNC_INFO << " INFO: rowCount NOW " << QString::number(ui->OTATableWidget->rowCount());
            /* mac could have been known and then filtered out and now adding back in, check to only add once */
            if ((ui->commandMACComboBox->findText(restOfData.at(0))) == -1)
            {
                ui->commandMACComboBox->addItem(restOfData.at(0));
            }
        }
    }

}

void AmptGUI_X::showGatewayResponse(const QString s)
{
    //emit parse(s);
    if (m_showGatewayResponseEnabled)
    {
         ui->gatewayResponseTextEdit->appendPlainText(s);
    }
}

void AmptGUI_X::showRawData(const QString &s)
{
    qDebug() << Q_FUNC_INFO<< " got Raw Data signal " << s;

    // ui->InputCommandGroupBox->setTitle(s);
}

void AmptGUI_X::enableCommandLinePushButton( const QString s)
{
    if (s.length() == 0)
    {
        ui->commandLineEditPushButton->setEnabled(false);
    }
    else
    {
        ui->commandLineEditPushButton->setEnabled(true);
    }
}

void AmptGUI_X::sendValidatedCommandToGateway(const QString &type, const QString & command)
{
    qDebug() << Q_FUNC_INFO << " will send type " << type << " command: " << command;

    if (type == GatewayCommandTypeToConfirm)
    {
        QString commandToSend(command);
        commandToSend += "\r\n";
        m_gatewayThread.commandToSend(commandToSend);
    }
    else
    {
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        QString ErrorStr = "ERROR: " + CurrentDateTime + " Unknown validated command type: " + type + " command: " + command + " not sent.";
        qDebug() << Q_FUNC_INFO << ErrorStr;
        emit(publishError(ErrorStr));
    }
}

void AmptGUI_X::sendConfigurationCommandToGateway(const QString &command)
{
    QString commandToSend = command + " \r\n";
    // qDebug() << Q_FUNC_INFO << " trying to send command " << commandToSend << " to gateway";
    m_gatewayThread.commandToSend(commandToSend);

}


void AmptGUI_X::handleOVSendPushButton( void )
{
   qDebug() << Q_FUNC_INFO;
   QString toSend = ui->ovSpinBox->text();
   QString commandToSend = "s m" + m_currentActiveMAC + ByteRegister_OverVoltageLimit + ByteRegisterCommand + toSend;
   sendCommandToGateway(commandToSend);
   ui->ovSendPushButton->setEnabled(false);
}


void AmptGUI_X::handleOCSendPushButton( void )
{
   qDebug() << Q_FUNC_INFO;
   QString toSend = ui->ocSpinBox->text();
   QString commandToSend = "s m" + m_currentActiveMAC + ByteRegister_OverCurrentLimit + ByteRegisterCommand + toSend;
   sendCommandToGateway(commandToSend);
   ui->ocSendPushButton->setEnabled(false);
}


void AmptGUI_X::handleMPPSendPushButton( void )
{
   qDebug() << Q_FUNC_INFO;
   QString toSend = "1";

   if (ui->mppComboBox->currentText() == "Off")
   {
       toSend = "0";
   }
   QString commandToSend = "s m" + m_currentActiveMAC + ByteRegister_MPPTracking + ByteRegisterCommand + toSend;
   sendCommandToGateway(commandToSend);

   ui->mppSendPushButton->setEnabled(false);  
}


void AmptGUI_X::handleModuleSendPushButton( void )
{
   qDebug() << Q_FUNC_INFO;
   QString toSend = "1";

   if (ui->moduleComboBox->currentText() == "Off")
   {
       toSend = "0";
   }
   QString commandToSend = "s m" + m_currentActiveMAC + ByteRegister_ModuleOutput + ByteRegisterCommand + toSend;
   sendCommandToGateway(commandToSend);
   ui->moduleSendPushButton->setEnabled(false);

}

void AmptGUI_X::sendGatewayCommandToGateway(const QString commandToSend)
{
    qDebug() << Q_FUNC_INFO << " sending gateway command straight on through ...";
    m_gatewayThread.commandToSend(commandToSend);
}

void AmptGUI_X::sendCommandToGateway(const QString commandToSend)
{
    qDebug() << Q_FUNC_INFO << " validate command  before sending to gateway";
    emit publishValidateOnlyEndDeviceCommandToSend(commandToSend);
}

void AmptGUI_X::sendCommandToGatewayFromCommandLine( void )
{
    QString commandToSend(ui->commandLineEdit->text());
    ui->commandLineEdit->clear();

    qDebug() << Q_FUNC_INFO << " Entering, command is " << commandToSend << " cleared command line";


    if (ui->confirmCommandCheckBox->checkState() == Qt::Checked)
    {
        qDebug() << Q_FUNC_INFO << " sendCommandToGateway:  command check " << commandToSend << Qt::endl;
        // LBC 07/26/2018 bool okToSend = false;

        if (ui->commandRadioButtonGateway->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " sendCommandToGateway:  command check for Gateway cmd" << commandToSend;
            emit publishConfirmGatewayCommand(GatewayCommandTypeToConfirm,commandToSend);

            // need to add \r\n to command if valid

        }
        else if (ui->commandRadioButtonBroadcast->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " sendCommandToGateway:  need to command check for Broadcast cmd" << commandToSend;
            emit publishConfirmGatewayCommand("Broadcast", commandToSend);
            handleRadioButtonBroadcastClicked(true);
        }
        else if (ui->commandRadioButtonMAC->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " sendCommandToGateway:  need to command check for MAC cmd" << commandToSend;
            emit publishConfirmGatewayCommand(MACCommandTypeToConfirm, commandToSend);
            handleRadioButtonMACClicked(true);

        }
        else if (ui->commandRadioButtonNetwork->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " sendCommandToGateway:  need to command check for Network cmd" << commandToSend;
            emit publishConfirmGatewayCommand("Network", commandToSend);
            handleRadioButtonNetworkClicked(true);
        }
        else if (ui->commandRadioButtonGroup->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " sendCommandToGateway:  need to command check for Group cmd" << commandToSend;
            emit publishConfirmGatewayCommand("Group", commandToSend);
            handleRadioButtonGroupClicked(true);
        }
    }
    else
    {
        if (ui->commandRadioButtonGateway->isChecked())
        {
            commandToSend += " \r\n";
            qDebug() << Q_FUNC_INFO << " trying to send command " << commandToSend << " to gateway";
            m_gatewayThread.commandToSend(commandToSend);
            qDebug() << Q_FUNC_INFO << " after call m_gatewayThread.commandToSend " << commandToSend;
        }
        else if (ui->commandRadioButtonMAC->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " validate MAC command before sending to gateway";
            emit publishValidateOnlyEndDeviceCommandToSend(commandToSend);

            handleRadioButtonMACClicked(true); // repopulate command line with s mXXXXX....
        }
        else if (ui->commandRadioButtonBroadcast->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " validate Broadcast command before sending to gateway: " << commandToSend;
            emit publishValidateOnlyEndDeviceCommandToSend(commandToSend);

            handleRadioButtonBroadcastClicked(true); // repopulate command line with s *
        }
        else if (ui->commandRadioButtonGroup->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " validate Group command before sending to gateway: " << commandToSend;
            emit publishValidateOnlyEndDeviceCommandToSend(commandToSend);

            handleRadioButtonGroupClicked(true); // repopulate command line with s s
        }
        else if (ui->commandRadioButtonNetwork->isChecked())
        {
            qDebug() << Q_FUNC_INFO << " validate Network command before sending to gateway: " << commandToSend;
            emit publishValidateOnlyEndDeviceCommandToSend(commandToSend);

            handleRadioButtonNetworkClicked(true); // repopulate command line with s #
        }
        else
        {
            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
            QString ErrorStr(Q_FUNC_INFO);
            ErrorStr += " ERROR: " + CurrentDateTime + " unknown command button received, no command will be sent to gateway.";
            qDebug() << ErrorStr;
            emit publishError(ErrorStr);
        }
    }

    qDebug() << Q_FUNC_INFO << " Exiting, command was " << commandToSend;

}

void AmptGUI_X::handleRadioButtonBroadcastClicked(const bool s)
{
    qDebug() << Q_FUNC_INFO << ": " << s << Qt::endl;

    if (s == true)
    {
        ui->commandMACComboBox->setEnabled(false);
        ui->parametersReadPushButton->setEnabled(true);
        ui->parametersWritePushButton->setEnabled(false);
        ui->saveSmallFPushButton->setEnabled(true);
        ui->saveBigFPushButton->setEnabled(true);

        // qDebug() << Q_FUNC_INFO << ": true" << s << Qt::endl;
        QString broadcastCommand("s * ");
        ui->commandLineEdit->setText(broadcastCommand);
        m_currentActiveMAC = "";
        emit publishCurrentActiveMAC(m_currentActiveMAC);

        ui->moduleComboBox->setEnabled(true);
        ui->moduleDial->setEnabled(true);
        ui->moduleSendPushButton->setEnabled(true);

        ui->mppComboBox->setEnabled(true);
        ui->mppDial->setEnabled(true);
        ui->mppSendPushButton->setEnabled(true);

        ui->ovSpinBox->setEnabled(true);
        ui->ovDial->setEnabled(true);
        ui->ovSendPushButton->setEnabled(true);

        ui->ocSpinBox->setEnabled(true);
        ui->ocDial->setEnabled(true);
        ui->ocSendPushButton->setEnabled(true);

        ui->networkEnableJoinPushButton->setEnabled(false);
        ui->networkDisableJoinPushButton->setEnabled(false);
        ui->networkDisbandNetworkPushButton->setEnabled(false);
        ui->networkEndOfTestPushButton->setEnabled(true);

        ui->utilitiesBatchCommandsSelectPushButton->setEnabled(true);
        ui->utilitiesBatchCommandsSelectLineEdit->clear();
        ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsStartStopLineEdit->clear();
    }
}

void AmptGUI_X::handleRadioButtonGatewayClicked(const bool s)
{
    qDebug() << Q_FUNC_INFO << ": " << s << Qt::endl;

    if (s == true)
    {
        // qDebug() << Q_FUNC_INFO << ": set true " << Qt::endl;
        QString gatewayCommand("");
        ui->commandLineEdit->setText(gatewayCommand);
        m_currentActiveMAC = "";
        emit publishCurrentActiveMAC(m_currentActiveMAC);
        ui->saveSmallFPushButton->setEnabled(false);
        ui->saveBigFPushButton->setEnabled(false);

        handleResetTextEditControls();
        ui->commandMACComboBox->setEnabled(false);
        ui->parametersReadPushButton->setEnabled(true);
        ui->parametersWritePushButton->setEnabled(false);
        ui->readCoefficientsPushButton->setEnabled(false);

        ui->networkEnableJoinPushButton->setEnabled(true);
        ui->networkDisableJoinPushButton->setEnabled(true);
        ui->networkDisbandNetworkPushButton->setEnabled(true);
        ui->networkEndOfTestPushButton->setEnabled(false);

        ui->utilitiesBatchCommandsSelectPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsSelectLineEdit->clear();
        ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsStartStopLineEdit->clear();
    }
}

void AmptGUI_X::handleRadioButtonGroupClicked(const bool s)
{
    qDebug() << Q_FUNC_INFO << ": " << s << Qt::endl;

    if (s == true)
    {
        QString groupCommand("s s");
        groupCommand += (QString("%1").arg(ui->configurationGroupToUseSpinBox->value(), 4, 16, QChar('0'))).toUpper();

        //qDebug() << Q_FUNC_INFO << ": set true using group command prefix:" << groupCommand << Qt::endl;

        ui->commandLineEdit->setText(groupCommand);

        m_currentActiveMAC = "";
        emit publishCurrentActiveMAC(m_currentActiveMAC);
        publishCurrentActiveMAC(m_currentActiveMAC);

        ui->commandMACComboBox->setEnabled(false);
        ui->parametersReadPushButton->setEnabled(false);
        ui->parametersWritePushButton->setEnabled(false);
        ui->readCoefficientsPushButton->setEnabled(false);

        ui->networkEnableJoinPushButton->setEnabled(false);
        ui->networkDisableJoinPushButton->setEnabled(false);
        ui->networkDisbandNetworkPushButton->setEnabled(false);
        ui->networkEndOfTestPushButton->setEnabled(false);

        ui->saveSmallFPushButton->setEnabled(true);
        ui->saveBigFPushButton->setEnabled(true);

        ui->utilitiesBatchCommandsSelectPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsSelectLineEdit->clear();
        ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsStartStopLineEdit->clear();
    }
}

void AmptGUI_X::handleRadioButtonNetworkClicked(const bool s)
{
    qDebug() << Q_FUNC_INFO << ": " << s << Qt::endl;

    if (s == true)
    {
        QString netIDCommand("s #");
        netIDCommand += (QString("%1").arg(ui->configurationNetIDToUseSpinBox->value(), 3, 16, QChar('0'))).toUpper();

        //qDebug() << Q_FUNC_INFO << ": set true using netID command prefix:" << netIDCommand << Qt::endl;

        ui->commandLineEdit->setText(netIDCommand);

        m_currentActiveMAC = "";
        emit publishCurrentActiveMAC(m_currentActiveMAC);
        publishCurrentActiveMAC(m_currentActiveMAC);

        ui->saveSmallFPushButton->setEnabled(true);
        ui->saveBigFPushButton->setEnabled(true);

        ui->commandMACComboBox->setEnabled(false);
        ui->parametersReadPushButton->setEnabled(false);
        ui->parametersWritePushButton->setEnabled(false);
        ui->readCoefficientsPushButton->setEnabled(false);

        ui->networkEnableJoinPushButton->setEnabled(false);
        ui->networkDisableJoinPushButton->setEnabled(false);
        ui->networkDisbandNetworkPushButton->setEnabled(false);
        ui->networkEndOfTestPushButton->setEnabled(false);

        ui->utilitiesBatchCommandsSelectPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsSelectLineEdit->clear();
        ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsStartStopLineEdit->clear();
    }
}

void AmptGUI_X::handleRadioButtonMACClicked(const bool s)
{
    qDebug() << Q_FUNC_INFO << ": " << s << Qt::endl;

    if (s == true)
    {
        qDebug() << Q_FUNC_INFO << ": set true" << Qt::endl;

        QString mac(ui->commandMACComboBox->currentText());
        ui->readCoefficientsPushButton->setEnabled(true);
        ui->saveSmallFPushButton->setEnabled(true);
        ui->saveBigFPushButton->setEnabled(true);

        qDebug() << Q_FUNC_INFO << ": mac " << mac << " length: " << mac.length() << Qt::endl;


        if (mac.length() == 12)
        {
            QString macCommand("s m");
            macCommand += mac;
            macCommand += " ";
            ui->commandLineEdit->setText(macCommand);
            m_currentActiveMAC = mac;
            emit publishCurrentActiveMAC(m_currentActiveMAC);
            handleResetCoeffsLine();
            ui->commandMACComboBox->setEnabled(true);
            ui->parametersReadPushButton->setEnabled(true);
            ui->parametersWritePushButton->setEnabled(false);
            // LBC send signal to select existing PBs for this mac
            emit publishClearCurrentEndDevicePBsAndLoadNewEDPBs();

            if ((ui->OTATableWidget->rowCount() > -1) && (m_OTAClickedRow >= 0))
            {
                int indexOfMAC = 0;
                qDebug() << Q_FUNC_INFO << " INFO: OTAClickedRow:" << m_OTAClickedRow;

                // ui->commandMACComboBox->setEnabled(true);

                if ((indexOfMAC = ui->commandMACComboBox->findText(m_currentActiveMAC)) != -1)
                {
                   // LBC trying to highligh row ui->OTATableWidget->selectRow(m_OTAClickedRow);
                    ui->OTATableWidget->cellClicked(indexOfMAC,OVIndex);
                    ui->OTATableWidget->setFocus();

                    ui->commandMACComboBox->setCurrentIndex(indexOfMAC);
                    ui->ovSpinBox->setValue((ui->OTATableWidget->item(indexOfMAC,OVIndex)->text()).toInt());
                    ui->ovSpinBox->setEnabled(true);
                    ui->ovDial->setEnabled(true);

                    ui->ovSendPushButton->setEnabled(false);

                    ui->ocSpinBox->setValue((ui->OTATableWidget->item(indexOfMAC,OCIndex)->text()).toInt());
                    ui->ocSpinBox->setEnabled(true);
                    ui->ocDial->setEnabled(true);

                    ui->ocSendPushButton->setEnabled(false);

                    if (ui->OTATableWidget->item(indexOfMAC,ModuleIndex)->text() == "On")
                        ui->moduleComboBox->setCurrentIndex(1);
                    else
                        ui->moduleComboBox->setCurrentIndex(zero);

                    ui->moduleComboBox->setEnabled(true);
                    ui->moduleDial->setEnabled(true);


                    ui->moduleSendPushButton->setEnabled(false);

                    if (ui->OTATableWidget->item(indexOfMAC,MPPIndex)->text() == "On")
                        ui->mppComboBox->setCurrentIndex(1);
                    else
                        ui->mppComboBox->setCurrentIndex(zero);

                    ui->mppComboBox->setEnabled(true);
                    ui->mppDial->setEnabled(true);

                    ui->mppSendPushButton->setEnabled(false);

                    ui->networkEnableJoinPushButton->setEnabled(false);
                    ui->networkDisableJoinPushButton->setEnabled(false);
                    ui->networkDisbandNetworkPushButton->setEnabled(false);
                    ui->networkEndOfTestPushButton->setEnabled(true);

                    ui->utilitiesBatchCommandsSelectPushButton->setEnabled(true);
                    ui->utilitiesBatchCommandsSelectLineEdit->clear();
                    ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
                    ui->utilitiesBatchCommandsStartStopLineEdit->clear();
                }
                else
                {
                    QString ErrorStr(Q_FUNC_INFO);
                    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                    ErrorStr += " ERROR: " + CurrentDateTime + " invalid MAC:" + m_currentActiveMAC + " not found via Index is OTATableWidget.";
                    emit publishError(ErrorStr);
                    qDebug() << ErrorStr;
                    handleResetTextEditControls();
                }
            }
            else
            {
                QString ErrorStr(Q_FUNC_INFO);
                QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                ErrorStr += " ERROR: " + CurrentDateTime + " text controls not set, no prior active OTA table row";
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
                handleResetTextEditControls();
            }

            ui->readCoefficientsPushButton->setEnabled(true);
        }
        else
        {
            QString ErrorStr(Q_FUNC_INFO);
            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
            ErrorStr += " ERROR: " + CurrentDateTime + " MAC:" + mac + " in commandMACComboBox not of correct length.";
            emit publishError(ErrorStr);
            qDebug() << ErrorStr;
            m_currentActiveMAC = "";
            emit publishCurrentActiveMAC(m_currentActiveMAC);
            ui->commandLineEdit->setText("");
        }
    }
}
void AmptGUI_X::handleMACComboBoxChange(const QString & s)
{
    qDebug() << Q_FUNC_INFO << " INFO: " << s;

    QString errString(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    if ((ui->commandRadioButtonMAC->isChecked()) && (s.length() == 12))
    {
        QString macCommand("s m");
        macCommand += s;
        macCommand += " ";
        ui->commandLineEdit->setText(macCommand);

        // emit signal to reset/clear/ ed parameters and possibly load new ed parameters if they exist if s != m_currentActiveMAC
        if (s != m_currentActiveMAC)
        {
            qDebug() << Q_FUNC_INFO << " INFO: emiting signal to clear and possibly load new ed PBs for MAC:" << s;
            m_currentActiveMAC = s;
            emit publishCurrentActiveMAC(m_currentActiveMAC);
            handleResetCoeffsLine();
            emit publishClearCurrentEndDevicePBsAndLoadNewEDPBs();
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: Not clearing current PBs because s:" << " == m_currentActiveMAC (" << m_currentActiveMAC << ")";
        }

        int indexOfMAC = 0;

        if ((indexOfMAC = ui->commandMACComboBox->findText(m_currentActiveMAC)) != -1)
        {
            ui->commandMACComboBox->setCurrentIndex(indexOfMAC);

            // Need to find MAC in OTATableWidget
            bool found = false;
            int i = 0;

            for (i = 0; i < ui->OTATableWidget->rowCount() && found == false; i++)
            {
                if (ui->OTATableWidget->item(i,MACIndex)->text() == m_currentActiveMAC)
                {
                    // qDebug() << Q_FUNC_INFO << " m_OTAClickedRow: " << m_OTAClickedRow;

                    ui->ovSpinBox->setValue((ui->OTATableWidget->item(i,OVIndex)->text()).toInt());
                    ui->ovSpinBox->setEnabled(true);
                    ui->ovDial->setEnabled(true);

                    ui->ovSendPushButton->setEnabled(false);

                    ui->ocSpinBox->setValue((ui->OTATableWidget->item(i,OCIndex)->text()).toInt());
                    ui->ocSpinBox->setEnabled(true);
                    ui->ocDial->setEnabled(true);

                    ui->ocSendPushButton->setEnabled(false);

                    if (ui->OTATableWidget->item(i,ModuleIndex)->text() == "On")
                        ui->moduleComboBox->setCurrentIndex(1);
                    else
                        ui->moduleComboBox->setCurrentIndex(zero);

                    ui->moduleComboBox->setEnabled(true);
                    ui->moduleDial->setEnabled(true);


                    ui->moduleSendPushButton->setEnabled(false);

                    if (ui->OTATableWidget->item(i,MPPIndex)->text() == "On")
                        ui->mppComboBox->setCurrentIndex(1);
                    else
                        ui->mppComboBox->setCurrentIndex(zero);

                    ui->mppComboBox->setEnabled(true);
                    ui->mppDial->setEnabled(true);

                    ui->mppSendPushButton->setEnabled(false);

                    // qDebug() << Q_FUNC_INFO << "IndexOfMAC: " << indexOfMAC << " OVIndex:" << OVIndex;

                    ui->OTATableWidget->cellClicked(i,OVIndex);
                    found = true;
                }
            }
            if (found == false)
            {
                errString += " INFO: " + CurrentDateTime + " MAC:" + m_currentActiveMAC + " not located in OTATableWidget."; // INFO cause could be filtered out
                emit publishError(errString);
                qDebug() << errString;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " received MAC:" << m_currentActiveMAC << ", not found via Index in commandMACComboBox.";
            handleResetTextEditControls();
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " Ignoring MACComboBox change, not selected or MAC not of proper length.";
        handleResetTextEditControls();

        m_currentActiveMAC = "";
        emit publishCurrentActiveMAC(m_currentActiveMAC);

        ui->readCoefficientsPushButton->setEnabled(false);
        // QString ErrorStr(Q_FUNC_INFO);
        //QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " MAC:" + s + " in commandMACComboBox not of correct length or MAC radio button not selected, m_currentActiveMAC set blank.";
        emit publishError(errString);
        qDebug() << errString;
    }

}

void AmptGUI_X::handleParametersAutoReadCheckBox(int state)
{
    if (state == 2)
    {
        emit publishParametersAutoRead(true);
    }
    else
    {
        emit publishParametersAutoRead(false);
    }
}

void AmptGUI_X::handleCommandGroupBox(bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: BEGIN argument is " << s;

    if (s == true)
    {
        ui->parametersReadPushButton->setEnabled(true);
        ui->parametersWritePushButton->setEnabled(false);
        ui->commandGroupBox->setEnabled(true);

        if (ui->commandRadioButtonMAC->isChecked())
        {
            ui->commandMACComboBox->setEnabled(true);
        }
        else
        {
            ui->commandMACComboBox->setEnabled(false);
        }
    }
    else
    {
        ui->commandGroupBox->setEnabled(false);
    }
    // qDebug() << Q_FUNC_INFO << " INFO: END argument is " << s;
}

void AmptGUI_X::handleAllRequestedParameterBlocksRead( void )
{
    // qDebug() << Q_FUNC_INFO << " INFO: BEGIN...";
    QMessageBox * pbsConfirmDialog = new QMessageBox(this);
    pbsConfirmDialog->setText("Received all requested parameter block information");
    pbsConfirmDialog->addButton(tr("OK"), QMessageBox::YesRole);
    pbsConfirmDialog->exec();
    delete pbsConfirmDialog;

    // qDebug() << Q_FUNC_INFO << " INFO: END...";
}

void AmptGUI_X::handleParametersAutoRead(const QString & mac)
{
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    qDebug()<< Q_FUNC_INFO << " INFO: possible auto read for MAC:" << mac;

    QString command("");

    if (ui->parametersAutoReadCheckBox->isChecked())
    {
        ui->parametersReadPushButton->setEnabled(false);
        ui->parametersWritePushButton->setEnabled(false);
        ui->commandGroupBox->setEnabled(false);

        m_parseOTADataThread.setParameterBlockReadFrom(ParametersReadFromFlash);
        if (mac.length() == 12)
        {
            command = "s m";
            command += mac;
            command += " 57 b1\r\n";

            qDebug() << Q_FUNC_INFO << " Auto reading PB for mac " << mac << " : sending command " << command;
            m_gatewayThread.commandToSend(command);
            emit requestingMACParameterBlock(mac);
            ResetParameterBlockValues = false; // Want to keep values UNTIL ... // LBC
            handleBeginReadingEndDeviceParameterBlock(mac);
        }
        else
        {
            QString ErrorStr(Q_FUNC_INFO);

            ErrorStr += " ERROR: " + CurrentDateTime + " invalid (length) for MAC address -> " + mac;
            qDebug() << ErrorStr;
            emit publishError(ErrorStr);

            m_parseOTADataThread.setParameterBlockReadFrom(ParametersReadFromUnknown);
            ui->parametersReadPushButton->setEnabled(true);
            ui->parametersWritePushButton->setEnabled(true);
            ui->commandGroupBox->setEnabled(true);
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Auto Read not checked ...";
        qDebug() << ErrorStr;
        emit publishError(ErrorStr);
    }

}

void AmptGUI_X::handleParametersWritePushButtonReleased( void )
{
    qDebug()<< Q_FUNC_INFO << " INFO: received ...";
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString msgString(Q_FUNC_INFO);

    QMessageBox *parametersWriteConfirmDialog = new QMessageBox(this);
    parametersWriteConfirmDialog->addButton(tr("Yes"),QMessageBox::YesRole);
    parametersWriteConfirmDialog->addButton(tr("No"),QMessageBox::NoRole);
    QString InfoStr = " Do you wish to write parameter block info for ";
    int nMode = 0;

    QString command("");
    if (ui->commandRadioButtonMAC->isChecked())
    {
        InfoStr += " mac " + m_currentActiveMAC + "?";
        parametersWriteConfirmDialog->setText(InfoStr);
        nMode = parametersWriteConfirmDialog->exec();
        if (nMode == 0)
        {
            command = "f m" + m_currentActiveMAC + "\r\n";
            qDebug() << " INFO: " << CurrentDateTime << " sending " << command << " to gateway...";
            sendCommandToGateway(command);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " writing parameter block cancelled.";
        }
    }
    else     if (ui->commandRadioButtonBroadcast->isChecked())
    {
        InfoStr += " all macs (broadcast)?";
        parametersWriteConfirmDialog->setText(InfoStr);
        nMode = parametersWriteConfirmDialog->exec();
        if (nMode == 0)
        {
            command = "f *\r\n";
            qDebug() << " INFO: " << CurrentDateTime << " sending " << command << " to gateway...";
            sendCommandToGateway(command);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " writing parameter block cancelled.";
        }
    }
    else     if (ui->commandRadioButtonGateway->isChecked())
    {
        InfoStr += " the Gateway?";
        parametersWriteConfirmDialog->setText(InfoStr);
        nMode = parametersWriteConfirmDialog->exec();
        if (nMode == 0)
        {
            command = "G\r\n";
            qDebug() << " INFO: " << CurrentDateTime << " sending " << command << " to gateway...";
            sendGatewayCommandToGateway(command);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " writing parameter block cancelled.";
        }
    }
    else
    {
        msgString += " ERROR: " + CurrentDateTime + " write parameters to flash not implemented for the current commandRadioButton selection...";
        emit publishError(msgString);
        qDebug() << msgString;
    }
}

void AmptGUI_X::handleParametersReadReleased()
{
    //qDebug()<< Q_FUNC_INFO;

    bool readFlash = false;
    QString command("");

    ui->parametersReadPushButton->setEnabled(false);
    ui->parametersWritePushButton->setEnabled(false);
    ui->commandGroupBox->setEnabled(false);
    ui->commandLineEdit->setEnabled(false);
    ui->commandLineEditPushButton->setEnabled(false);

    if (ui->parametersFlashCheckBox->isChecked())
    {
        readFlash = true;
        m_parseOTADataThread.setParameterBlockReadFrom(ParametersReadFromFlash);
    }
    else
    {
        m_parseOTADataThread.setParameterBlockReadFrom(ParametersReadFromMemory);
    }

    if (ui->commandRadioButtonBroadcast->isChecked())
    {
        command = "s * 58 b2\r\n";
        // qDebug() << Q_FUNC_INFO << " INFO: sending command to gateway: " << command;
        m_gatewayThread.commandToSend(command);

        // qDebug() << Q_FUNC_INFO << " commandRadioButtonBroadcast->isChecked()";
        if (readFlash == true)
        {
            command = "s * 57 b1\r\n";
        }
        else
        {
            command = "s * 32 b1\r\n";
        }

        int numberOfKnownMACs = ui->commandMACComboBox->count();
        QString knownMACs("");

        for (int i = 0; i < numberOfKnownMACs; i++)
        {
            knownMACs += ui->commandMACComboBox->itemText(i);
            if (i < (numberOfKnownMACs - 1))
            {
               knownMACs += ",";
            }
        }

        qDebug() << Q_FUNC_INFO << " INFO: list of MACs that will respond to broadcast: " << knownMACs;
        emit requestingAllEndDeviceParameterBlocks(knownMACs);

        // qDebug() << Q_FUNC_INFO << " INFO: sending command to gateway: " << command;
        m_gatewayThread.commandToSend(command);
        // Get all MACs for combo box, construct QStringList.
        // Modify requestingAllEndDeviceParameterBlocks to take QStringListArgument
        // As well as handleAllEndDeviceParameterBlocks
        // What does handleBeginReadingEndDeviceParameterBlock do?

        handleBeginReadingEndDeviceParameterBlock("*");
        ResetParameterBlockValues = false;

    }
    else if (ui->commandRadioButtonMAC->isChecked())
    {
        QString mac(ui->commandMACComboBox->currentText());
        // qDebug() << Q_FUNC_INFO << " commandRadioButtonMAC->isChecked()";
        // qDebug() << Q_FUNC_INFO << " : mac " << mac << " length: " << mac.length();

        if (mac.length() == 12)
        {
            command = "s * 58 b2\r\n";
            // qDebug() << Q_FUNC_INFO << " INFO: sending command to gateway: " << command;
            m_gatewayThread.commandToSend(command);

            command = "s m";
            command += mac;
            if (readFlash == true)
            {
                command += " 57 b1\r\n";
            }
            else
            {
                command += " 32 b1\r\n";
            }

            // qDebug() << Q_FUNC_INFO << " : sending command " << command;
            m_gatewayThread.commandToSend(command);
            emit requestingMACParameterBlock(mac);
            ResetParameterBlockValues = false; // Want to keep values UNTIL ... // LBC
            handleBeginReadingEndDeviceParameterBlock(mac);
            ResetParameterBlockValues = false;
        }
        else
        {
            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
            QString errString(Q_FUNC_INFO);
            errString += " : ERROR: " + CurrentDateTime +  " invalid MAC address:" + mac;
            qDebug() << errString;
            emit publishError(errString);

            m_parseOTADataThread.setParameterBlockReadFrom(ParametersReadFromUnknown);
            ui->parametersReadPushButton->setEnabled(true);
            // ui->parametersWritePushButton->setEnabled(true);
            ui->commandGroupBox->setEnabled(true);
            ui->commandLineEdit->setEnabled(true);
            ui->commandLineEditPushButton->setEnabled(true);
        }
    }
    else if (ui->commandRadioButtonGateway->isChecked())
    {
        qDebug() << Q_FUNC_INFO << " commandRadioButtonGateway->isChecked()";
        command = "i\r\n";
        qDebug() << Q_FUNC_INFO << " : sending command " << command;
        m_parseOTADataThread.setParameterBlockReadFrom(ParametersReadFromGateway);
        m_gatewayThread.commandToSend(command);
        ui->parametersReadPushButton->setEnabled(true);
        ui->parametersWritePushButton->setEnabled(true);
        ui->commandGroupBox->setEnabled(true);
        ui->commandLineEdit->setEnabled(true);
        ui->commandLineEditPushButton->setEnabled(true);
    }
}

void AmptGUI_X::handleOTADataFormatSettings(const bool s)
{
    if (s == true)
    {
    }
    else
    {

    }
}

void AmptGUI_X::handleResetGatewayWidgets( void )
{
    m_gatewayChangesTracked->setIgnoreSignalsToChangeGatewayValues(true);
    m_gatewayChangesTracked->resetAllTrackedGatewayValues();

    QTabBar* bar=ui->AllTabs->tabBar();
    bar->setTabTextColor(GatewayTabIndex,Qt::black);

    ui->gatewayVersionLineEdit->setEnabled(false);
    ui->gatewayVersionLineEdit->setText("");

    ui->gatewayDataRateLineEdit->setEnabled(false);
    ui->gatewayDataRateLineEdit->setText("");

    ui->gatewayFrequencyLineEdit->setEnabled(false);
    ui->gatewayFrequencyLineEdit->setText("");

    ui->gatewayMicroSecondsInTickLineEdit->setEnabled(false);
    ui->gatewayMicroSecondsInTickLineEdit->setText("");

    ui->gatewayChannelSpinBox->setEnabled(false);
    ui->gatewayChannelLabel->setText(blackFont + gatewayChannelStr + endFont);

    ui->gatewayNetworkSizeSpinBox->setEnabled(false);
    ui->gatewayNetworkSizeLabel->setText(blackFont + gatewayNetworkSizeStr + endFont);

    ui->gatewayBunchSizeSpinBox->setEnabled(false);
    ui->gatewayBunchSizeLabel->setText(blackFont + gatewayBunchSizeStr + endFont);

    ui->gatewayLongPacketsLineEdit->setEnabled(false);
    ui->gatewayLongPacketsLineEdit->setText("");

    ui->gatewayShiftLineEdit->setEnabled(false);
    ui->gatewayShiftLineEdit->setText("");

    ui->gatewayMACDataLabel->setEnabled(false);
    ui->gatewayMACDataLabel->setText("");

    ui->gatewayGatewaySpinBox->setEnabled(false);
    ui->gatewayEndDeviceSpinBox->setEnabled(false);
    ui->gatewayGatewayEDAddressLabel->setText(blackFont + gatewayGatewayEndDeviceAddressStr + endFont);

    ui->gatewaySyncwordSpinBox->setEnabled(false);
    ui->gatewaySyncWordLabel->setText(blackFont + gatewaySyncwordStr + endFont);

    ui->gatewayRepeatCommandSpinBox->setEnabled(false);
    ui->gatewayRepeatCommandsLabel->setText(blackFont + gatewayRepeatCommandStr + endFont);

    // ui->gatewayModeLabel->setEnabled(false);
    ui->gatewayModeSpinBox->setEnabled(false);
    ui->gatewayModeLabel->setText(blackFont + gatewayModeStr + endFont);

    ui->gatewayHoppingComboBox->setEnabled(false);
    ui->gatewayHoppingLabel->setText(blackFont + gatewayHoppingStr + endFont);

    ui->gatewayPowerComboBox->setEnabled(false);
    ui->gatewayPowerLabel->setText(blackFont + gatewayPowerStr + endFont);

    ui->gatewayFWVersionLineEdit->setText("");

    m_gatewayChangesTracked->setIgnoreSignalsToChangeGatewayValues(false);

}

void AmptGUI_X::handleGatewayParameterBlockData( const QString &s)
{
    // qDebug() << Q_FUNC_INFO << " got gateway Parameter Block data " << s;
 /*
  *  "i\r\n\r\n\r\nAMPT BOU Radio Gateway ver. F\r\nDatarate:12001 Freq2410001 Tick (mks) 500 Chan 2 # SPTs 8 bunch size 16\r\nUTC:0 963 Normal   long packets  temp 3033\t shift -30 ADCs  TRUE  Power ED\r\nMAC 884A800006EA no hop  FEC=0GwAddr 1\tEdAddr 2\r\nSync Word: F0F0\r\n"
*/
    // ui->parametersReadPushButton->setEnabled(true);
    // ui->parametersWritePushButton->setEnabled(true);

    // LBC here check to see if there is actual gateway data versus an empty string (indicates parsing gateway data failed.)


    handleResetGatewayWidgets();



    if (s.length() > 200)
    {
        m_gatewayChangesTracked->setIgnoreSignalsToChangeGatewayValues(true);

        QStringList gatewayPairs = s.split(' ');
        int numberOfGatewayPairs = gatewayPairs.size();
        // qDebug() << Q_FUNC_INFO << " elements in gatewayPairs: " << numberOfGatewayPairs;
        int index = -1;

        if ((numberOfGatewayPairs == 16) || (numberOfGatewayPairs == 20)) // From either "i" or "?" command
        {
            for (int i = 0; i < numberOfGatewayPairs; i++)
            {
                // qDebug() << Q_FUNC_INFO << " element pair at " << i << " is " << gatewayPairs.at(i);
                QStringList onePair = (gatewayPairs.at(i)).split(gatewayKeyValueSeparator.at(0));
                if (onePair.size() == 2)
                {
                    // qDebug() << Q_FUNC_INFO << " the current key: " << onePair.at(0) << " gatewayVersionKey " << gatewayVersionKey;

                    QString theKey = onePair.at(0);
                    if ( theKey == gatewayVersionKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read version of " << onePair.at(1);
                        ui->gatewayVersionLineEdit->setEnabled(true);
                        ui->gatewayVersionLineEdit->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayDataRateKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " read data rate of " << onePair.at(1);
                        ui->gatewayDataRateLineEdit->setEnabled(true);
                        ui->gatewayDataRateLineEdit->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayFrequencyKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " read frequency of " << onePair.at(1);
                        ui->gatewayFrequencyLineEdit->setEnabled(true);
                        ui->gatewayFrequencyLineEdit->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayMicroSecondsInTickKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " read mks in Tick of " << onePair.at(1);
                        ui->gatewayMicroSecondsInTickLineEdit->setEnabled(true);
                        ui->gatewayMicroSecondsInTickLineEdit->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayChannelKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " read channel of " << onePair.at(1);
                        ui->gatewayChannelSpinBox->setEnabled(true);
                        ui->gatewayChannelSpinBox->setValue((onePair.at(1)).toInt());
                    }
                    else if (theKey == gatewayNetworkSizeKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " read network size  of " << onePair.at(1);
                        ui->gatewayNetworkSizeSpinBox->setEnabled(true);
                        ui->gatewayNetworkSizeSpinBox->setValue((onePair.at(1)).toInt());
                    }
                    else if (theKey == gatewayRadioModeKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " radio mode is " << onePair.at(1);
                        ui->gatewayModeSpinBox->setEnabled(true);
                        if (onePair.at(1) == "Normal")
                        {
                            ui->gatewayModeSpinBox->setValue(1);
                        }
                        else
                        {
                            ui->gatewayModeSpinBox->setValue(0);
                        }
                    }
                    else if (theKey == gatewayBunchSizeKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " read bunch size of " << onePair.at(1);
                        ui->gatewayBunchSizeSpinBox->setEnabled(true);
                        ui->gatewayBunchSizeSpinBox->setValue((onePair.at(1)).toInt());
                    }
                    else if (theKey == gatewayUTCKey)
                    {
                        // qDebug() << Q_FUNC_INFO << " read UTC of " << onePair.at(1);
                        // NO such entry for UTC ui->gateway ->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayLongPacketsKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read long packet of " << onePair.at(1);
                        ui->gatewayLongPacketsLineEdit->setEnabled(true);
                        ui->gatewayLongPacketsLineEdit->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayShiftKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read shift of " << onePair.at(1);
                        ui->gatewayShiftLineEdit->setEnabled(true);
                        ui->gatewayShiftLineEdit->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayPowerKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read power of " << onePair.at(1);
                        ui->gatewayPowerComboBox->setEnabled(true);
                        if (ui->gatewayPowerComboBox->findText(onePair.at(1)) == -1)
                        {
                            ui->gatewayPowerComboBox->addItem(onePair.at(1));
                        }
                        else
                        {
                            int index = ui->gatewayPowerComboBox->findText(onePair.at(1));
                            ui->gatewayPowerComboBox->setCurrentIndex(index);
                        }
                    }
                    else if (theKey == gatewayMACKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read MAC of " << onePair.at(1);
                        ui->gatewayMACDataLabel->setEnabled(true);
                        ui->gatewayMACDataLabel->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayHopKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read hop of " << onePair.at(1);
                        index = (onePair.at(1)).toInt();

                        if ((index >= 0) && (index <= 1))
                        {
                            ui->gatewayHoppingComboBox->setEnabled(true);
                            ui->gatewayHoppingComboBox->setCurrentIndex(index);
                        }
                        else
                        {
                            QString errString(Q_FUNC_INFO);
                            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                            errString += " ERROR: " + CurrentDateTime + " valid index for gateway hopping not found, mapping unexpected value of " + onePair.at(1) + ", failed to set.";
                            emit publishError(errString);
                            qDebug() << errString;
                        }
                    }
                    else if (theKey == gatewayGWAddrKey )
                    {
                        //qDebug() << Q_FUNC_INFO << " read GW Addr of " << onePair.at(1);
                        ui->gatewayGatewaySpinBox->setEnabled(true);
                        ui->gatewayGatewaySpinBox->setValue((onePair.at(1)).toInt());
                    }
                    else if (theKey == gatewayEDAddrKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read ED Addr of " << onePair.at(1);
                        ui->gatewayEndDeviceSpinBox->setEnabled(true);
                        ui->gatewayEndDeviceSpinBox->setValue((onePair.at(1)).toInt());
                    }
                    else if (theKey == gatewaySyncwordKey )
                    {
                        bool ok = true;
                        // qDebug() << Q_FUNC_INFO << " read sync word of " << onePair.at(1);
                        ui->gatewaySyncwordSpinBox->setEnabled(true);
                        ui->gatewaySyncwordSpinBox->setValue((onePair.at(1)).toInt(&ok,16));
                    }
                    else if (theKey == gatewayZCountKey )
                    {
                        bool ok = true;
                        // qDebug() << Q_FUNC_INFO << " read zcount of " << onePair.at(1);
                        ui->gatewayRepeatCommandSpinBox->setEnabled(true);
                        ui->gatewayRepeatCommandSpinBox->setValue((onePair.at(1)).toInt(&ok,16));
                    }
                    else if (theKey == gatewayFWVersionKey )
                    {
                        // qDebug() << Q_FUNC_INFO << " read fwversion of " << onePair.at(1);
                        ui->gatewayFWVersionLineEdit->setText(onePair.at(1));
                    }
                    else if (theKey == gatewayModeStr)
                    {
                        ui->gatewayModeLabel->setEnabled(true);
                        ui->gatewayModeSpinBox->setEnabled(true);
                        ui->gatewayModeSpinBox->setValue((onePair.at(1)).toInt());
                    }

                }
                else
                {
                    QString errString(Q_FUNC_INFO);
                    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                    errString += " ERROR: " + CurrentDateTime + " expected size of pair(2) not found, instead found " + QString::number(onePair.size()) + ", failed to set for index:" + QString::number(i);
                    emit publishError(errString);
                    qDebug() << errString;
                }
            }
        }
        else
        {
            QString errString(Q_FUNC_INFO);
            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
            errString += " ERROR: " + CurrentDateTime + " gateway parameter input variable has incorrect number of keys, received:" + QString::number(numberOfGatewayPairs) + " expected (17 or 19), failed to read.";
            emit publishError(errString);
            qDebug() << errString;
        }
        m_gatewayChangesTracked->setIgnoreSignalsToChangeGatewayValues(false);
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " gateway parameter input variable not of the correct size., failed to read.";
        emit publishError(errString);
        qDebug() << errString;
    }
    ui->gatewaySendPushButton->setEnabled(false);
    ui->gatewaySavePushButton->setEnabled(false);
}

void AmptGUI_X::handleResendParameterBlockCommand(const QString & mac, const bool flash, const quint8 num)
{
    QString resendCommand("s m");

    resendCommand += mac;

    if (flash)
    {
        resendCommand += " 57 b";
    }
    else
    {
        resendCommand += " 32 b";
    }

    if ((num >= 1) && (num <= 10))
    {
        resendCommand += QString::number(num) + "\r\n";
        qDebug() << Q_FUNC_INFO << " will 'resend' command " << resendCommand;
        m_gatewayThread.commandToSend(resendCommand);
    }
    else
    {
        QString ErrorStr = " received an invalid command argument num:" + QString::number(num);
        qDebug() << Q_FUNC_INFO << ErrorStr;
        emit publishError(ErrorStr);
    }

}

void AmptGUI_X::handleEndDeviceNewPBs(const QString & mac)
{
    if (mac == m_currentActiveMAC)
    {
        qDebug() << Q_FUNC_INFO << " mac:" << mac << " is the current active mac:" << m_currentActiveMAC;

        QTabBar* bar=ui->AllTabs->tabBar();
        // bar->setTabTextColor(currentIndex, Qt::red);
        int numTabs = ui->AllTabs->count();

        for (int i = 0; i < numTabs; i++)
        {
            if (i != GatewayTabIndex)
            {
                bar->setTabTextColor(i,Qt::black);
            }
        }
        ui->parametersWritePushButton->setEnabled(true);

    }
    else
    {
        qDebug() << Q_FUNC_INFO << " mac: " << mac << " is not the current active mac:" << m_currentActiveMAC;
    }
}

   void AmptGUI_X::handleEndDeviceLinearKAndOffs(const QString & mac, const QString & family, const QString & linearKandOffs)
   {
       // qDebug() << Q_FUNC_INFO << " received linearKandOffs for mac: " << mac << " family " << family << " linearKandOffs " << linearKandOffs;

       /*
       if (family == Family600V_V2)
       {
           qDebug() << Q_FUNC_INFO << " yes, a 600V_V2 optimizer!!!!!!";
       }
       */
       if (mac == m_currentActiveMAC)
       {
           QStringList linearKandOffsElements = linearKandOffs.split(",");
           if (linearKandOffsElements.size() != 14)
           {
               QString ErrorStr(Q_FUNC_INFO);
               QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
               ErrorStr += " Error: " + CurrentDateTime + " number of expected linear coefficients and offsets(14) not received:" + QString::number(linearKandOffsElements.size()) + " for family " + family;

               qDebug() << Q_FUNC_INFO << ErrorStr;
               emit publishError(ErrorStr);
           }
           else
           {
               /*
               for (int i = 0; i <linearKandOffsElements.size(); i++)
               {
                   qDebug() << Q_FUNC_INFO << linearKandOffsElements.at(i) << " as double " << (linearKandOffsElements.at(i)).toDouble();
               }
               */

               m_linearCoeffsChangesTracked->setIgnoreSignals(true);

               ui->linearCoeffsLinearCoefficientsRowLabel->setEnabled(true);
               ui->linearCoeffsLinearCoefficientsRowLabel->setText(blackFont + linearCoeffsCoefficientsRowLabelStr + endFont );

               ui->linearCoeffsLinearOffsetsRowLabel->setEnabled(true);
               ui->linearCoeffsLinearOffsetsRowLabel->setText( blackFont + linearCoeffsOffsetRowLabelStr + endFont );


               // qDebug() << Q_FUNC_INFO << "LinearCoeffsRowLabel should have black Font: enabled:" << ui->linearCoeffsLinearCoefficientsRowLabel->isEnabled();  // LBC

               ui->linearCoeffsVOutColumnLabel->setEnabled(true);
               ui->linearCoeffsVOutColumnLabel->setText(blackFont  + linearCoeffsVOutColumnStr + endFont );

               ui->linearCoeffsVIn1ColumnLabel->setEnabled(true);
               ui->linearCoeffsVIn1ColumnLabel->setText(blackFont + linearCoeffsVIn1ColumnStr + endFont );

               ui->linearCoeffsVIn2ColumnLabel->setEnabled(true);
               ui->linearCoeffsVIn2ColumnLabel->setText(blackFont + linearCoeffsVIn2ColumnStr + endFont );

               ui->linearCoeffsIOutColumnLabel->setEnabled(true);
               ui->linearCoeffsIOutColumnLabel->setText(blackFont + linearCoeffsIOutColumnStr + endFont );

               ui->linearCoeffsIIn1ColumnLabel->setEnabled(true);
               ui->linearCoeffsIIn1ColumnLabel->setText(blackFont + linearCoeffsIIn1ColumnStr + endFont );

               ui->linearCoeffsIIn2ColumnLabel->setEnabled(true);
               ui->linearCoeffsIIn2ColumnLabel->setText(blackFont + linearCoeffsIIn2ColumnStr + endFont );

               ui->linearCoeffsTextColumnLabel->setEnabled(true);
               ui->linearCoeffsTextColumnLabel->setText(blackFont + linearCoeffsTextColumnStr + endFont );

               ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsVOutCoefficientDoubleSpinBox->setValue( (linearKandOffsElements.at(0)).toDouble());

               ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsVOutOffsetDoubleSpinBox->setValue( (linearKandOffsElements.at(1)).toDouble());
               ui->linearCoeffsVIn1CoefficientDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsVIn1CoefficientDoubleSpinBox->setValue( (linearKandOffsElements.at(2)).toDouble());
               ui->linearCoeffsVIn1OffsetDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsVIn1OffsetDoubleSpinBox->setValue( (linearKandOffsElements.at(3)).toDouble());
               ui->linearCoeffsIOutCoefficientDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsIOutCoefficientDoubleSpinBox->setValue( (linearKandOffsElements.at(4)).toDouble());
               ui->linearCoeffsIOutOffsetDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsIOutOffsetDoubleSpinBox->setValue( (linearKandOffsElements.at(5)).toDouble());
               ui->linearCoeffsVIn2CoefficientDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsVIn2CoefficientDoubleSpinBox->setValue( (linearKandOffsElements.at(6)).toDouble());
               ui->linearCoeffsVIn2OffsetDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsVIn2OffsetDoubleSpinBox->setValue( (linearKandOffsElements.at(7)).toDouble());
               ui->linearCoeffsTextCoefficientDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsTextCoefficientDoubleSpinBox->setValue( (linearKandOffsElements.at(8)).toDouble());
               ui->linearCoeffsTextOffsetDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsTextOffsetDoubleSpinBox->setValue( (linearKandOffsElements.at(9)).toDouble());
               ui->linearCoeffsIIn1CoefficientDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsIIn1CoefficientDoubleSpinBox->setValue( (linearKandOffsElements.at(12)).toDouble());
               ui->linearCoeffsIIn1OffsetDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsIIn1OffsetDoubleSpinBox->setValue( (linearKandOffsElements.at(13)).toDouble());
               ui->linearCoeffsIIn2CoefficientDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsIIn2CoefficientDoubleSpinBox->setValue( (linearKandOffsElements.at(10)).toDouble());
               ui->linearCoeffsIIn2OffsetDoubleSpinBox->setEnabled(true);
               ui->linearCoeffsIIn2OffsetDoubleSpinBox->setValue( (linearKandOffsElements.at(11)).toDouble());

               // qDebug() << Q_FUNC_INFO << " XXX CCC XXX ignore linear Coeffs signal " << QString::number(m_linearCoeffsChangesTracked->getIgnoreSignals());
               m_linearCoeffsChangesTracked->setIgnoreSignals(false);

               // qDebug() << Q_FUNC_INFO << " XXX CCC XXX ignore linear Coeffs signal " << QString::number(m_linearCoeffsChangesTracked->getIgnoreSignals());


           }
       }
       else
       {
           // LBC emit error?
           handleResetLinearCoeffs();
       }

       // What is the current active mac?
       // If mac argument matches the active mac, then display
       // else do nothing.
   }


void AmptGUI_X::handleEndDeviceSettings(const QString & mac, const QString & edSettings)
{
    // qDebug() << Q_FUNC_INFO << " received edSettings for mac: " << mac << " edSettings " << edSettings;

    if (mac == m_currentActiveMAC)
    {
        QStringList edSettingsElements = edSettings.split(",");
        if (edSettingsElements.size() != 2) // The "fuse" settings are currently ignored as they are not active in firmware.
        {
            QString ErrorStr(Q_FUNC_INFO);
            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
            ErrorStr += " Error: " + CurrentDateTime + " number of expected edSettings(2)) not received:" + QString::number(edSettingsElements.size());

            qDebug() << Q_FUNC_INFO << ErrorStr;
            emit publishError(ErrorStr);
        }
        else
        {

            // for (int i = 0; i < edSettingsElements.size(); i++)
            //{
            //    qDebug() << Q_FUNC_INFO << " %%%%%%%%%%%%%%%%%%%%  " << i << " => " << edSettingsElements.at(i);
            //}

            m_edSettingsChangesTracked->setIgnoreSignals( true );

            ui->edSettingsSyncFrequencyLabel->setText(blackFont + edSettingsSyncFrequencyStr + endFont);
            ui->edSettingsSyncFrequencySpinBox->setEnabled(true);
            ui->edSettingsSyncFrequencySpinBox->setValue((edSettingsElements.at(0)).toInt());

            ui->edSettingsSyncPhaseLabel->setText(blackFont + edSettingsSyncPhaseStr + endFont);
            ui->edSettingsSyncPhaseSpinBox->setEnabled(true);
            ui->edSettingsSyncPhaseSpinBox->setValue((edSettingsElements.at(1)).toInt());

            ui->edSettingsOptimizerFamilyLabel->setText(blackFont + edSettingsOptimizerFamilyStr + endFont);

            m_edSettingsChangesTracked->setIgnoreSignals( false);

        }
    }
    else
    {
        handleResetEDSettings();
    }
}

   void AmptGUI_X::handleEndDeviceCommunicationsSettings(const QString & mac, const QString & edComms)
   {
       // qDebug() << Q_FUNC_INFO << " received edComms for mac: " << mac << " edComms " << edComms;

       if (mac == m_currentActiveMAC)
       {
           QStringList edCommsElements = edComms.split(",");
           if (edCommsElements.size() != 18)
           {
               QString ErrorStr(Q_FUNC_INFO);
               QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
               ErrorStr += " Error: " + CurrentDateTime + " number of expected edComms(18) not received:" + QString::number(edCommsElements.size());

               qDebug() << Q_FUNC_INFO << ErrorStr;
               emit publishError(ErrorStr);
           }
           else
           {
               /*
               for (int i = 0; i < edCommsElements.size(); i++)
               {
                   qDebug() << Q_FUNC_INFO << edCommsElements.at(i);
               }
               */

               m_edCommsChangesTracked->setIgnoreSignals(true);

               quint8 byte1 = static_cast<quint8>((edCommsElements.at(EDComms_boolByte1_INDEX)).toUInt());
               quint8 byte2 = static_cast<quint8>((edCommsElements.at(EDComms_boolByte2_INDEX)).toUInt());

               ui->edCommsNetIDSpinBox->setEnabled(true);
               ui->edCommsNetIDSpinBox->setValue((edCommsElements.at(0)).toInt() );
               ui->edCommsNetIDLabel->setText(blackFont + edCommsNetIDStr + endFont);

               ui->edCommsBunchSpinBox->setEnabled(true);
               ui->edCommsBunchSpinBox->setValue((edCommsElements.at(1)).toInt());
               ui->edCommsBunchLabel->setText(blackFont + edCommsBunchStr + endFont);

               ui->edCommsGroupSpinBox->setEnabled(true);
               ui->edCommsGroupSpinBox->setValue((edCommsElements.at(2)).toInt());
               ui->edCommsGroupLabel->setText(blackFont + edCommsGroupStr + endFont);

               ui->edCommsSyncWordSpinBox->setEnabled(true);
               ui->edCommsSyncWordSpinBox->setValue((edCommsElements.at(3)).toInt());
               ui->edCommsSyncWordLabel->setText(blackFont + edCommsSyncWordStr + endFont);

               ui->edCommsRBunchSpinBox->setEnabled(true);
               ui->edCommsRBunchSpinBox->setValue((edCommsElements.at(4)).toInt());
               ui->edCommsRBunchLabel->setText(blackFont + edCommsRBunchStr + endFont);

               ui->edCommsGBunchSpinBox->setEnabled(true);
               ui->edCommsGBunchSpinBox->setValue((edCommsElements.at(5)).toInt());
               ui->edCommsGBunchLabel->setText(blackFont + edCommsGBunchStr + endFont);

               ui->edCommsChannelSpinBox->setEnabled(true);
               // qDebug() << Q_FUNC_INFO << edCommsElements.at(6);
               ui->edCommsChannelSpinBox->setValue((edCommsElements.at(6)).toInt());
               ui->edCommsChannelLabel->setText(blackFont + edCommsChannelStr + endFont);

               ui->edCommsRadioPowerSpinBox->setEnabled(true);
               ui->edCommsRadioPowerSpinBox->setValue((edCommsElements.at(7)).toInt());
               ui->edCommsRadioPowerLabel->setText(blackFont + edCommsRadioPowerStr + endFont);

               ui->edCommsEndDeviceAddressSpinBox->setEnabled(true);
               ui->edCommsEndDeviceAddressSpinBox->setValue((edCommsElements.at(8)).toInt());
               ui->edCommsGatewayAddressSpinBox->setEnabled(true);
               ui->edCommsGatewayAddressSpinBox->setValue((edCommsElements.at(9)).toInt());
               ui->edCommsGatewayEdAddressLabel->setText(blackFont + edCommsGatewayEDAddressStr + endFont);

               ui->edComms2RepeaterChannelSpinBox->setEnabled(true);
               ui->edComms2RepeaterChannelSpinBox->setValue((edCommsElements.at(10)).toInt());
               ui->edComms2RepeaterChannelLabel->setText(blackFont + edComms2RepeaterChannelStr + endFont);

               ui->edComms2RepeaterPowerSpinBox->setEnabled(true);
               ui->edComms2RepeaterPowerSpinBox->setValue((edCommsElements.at(11)).toInt());
               ui->edComms2RepeaterPowerLabel->setText(blackFont + edComms2RepeaterPowerStr + endFont);

               // 12 is byte1, 13 is Starting500Channel, 16 is showState
               ui->edComms2CriticalLevel10SpinBox->setEnabled(true);
               ui->edComms2CriticalLevel10SpinBox->setValue((edCommsElements.at(14)).toInt());
               ui->edComms2CriticalLevel10Label->setText(blackFont + edComms2CriticalLevel10Str + endFont);

               // qDebug( ) << "\n\n\n\n" << Q_FUNC_INFO << " #########################  " << edCommsElements.at(14) << "\n\n\n\n";

               ui->edComms2CriticalLevel500SpinBox->setEnabled(true);
               ui->edComms2CriticalLevel500SpinBox->setValue((edCommsElements.at(15)).toInt());
               ui->edComms2CriticalLevel500Label->setText(blackFont + edComms2CriticalLevel500Str + endFont);

               // 15 is show state
               // 16 is byte2

               ui->edComms2RepeaterSpinBox->setEnabled(true);
               if ((byte1 & 0x20) == 0x20) // isRelay
               {
                   ui->edComms2RepeaterSpinBox->setValue(1);
               }
               else
               {
                   ui->edComms2RepeaterSpinBox->setValue(0);
               }
               ui->edComms2RepeaterLabel->setText(blackFont + edComms2RepeaterStr + endFont);

               ui->edComms2SlaveSpinBox->setEnabled(true);
               if ((byte1 & 0x40) == 0x40) // is500
               {
                   ui->edComms2SlaveSpinBox->setValue(1);
               }
               else
               {
                   ui->edComms2SlaveSpinBox->setValue(0);
               }
               ui->edComms2SlaveLabel->setText(blackFont + edComms2SlaveStr + endFont);

               ui->edCommsHoppingAllowedSpinBox->setEnabled(true);
               if ((byte1 & 0x10) == 0x10) // Hopping Allowed
               {
                   ui->edCommsHoppingAllowedSpinBox->setValue(1);
               }
               else
               {
                   ui->edCommsHoppingAllowedSpinBox ->setValue(0);
               }
               ui->edCommsHoppingAllowedLabel->setText(blackFont + edCommsHoppingStr + endFont);

               ui->edCommsGatewayChannelFlagSpinBox->setEnabled(true);
               if ((byte1 & 0x08) == 0x08)
               {
                   ui->edCommsGatewayChannelFlagSpinBox->setValue(1);
               }
               else
               {
                   ui->edCommsGatewayChannelFlagSpinBox->setValue(0);
               }
               ui->edCommsGatewayChannelFlagLabel->setText(blackFont + edCommsGatewayChannelFlagStr + endFont);

               ui->edComms12KbodSpinBox->setEnabled(true);
               if ((byte1 & 0x04) == 0x04)
               {
                   ui->edComms12KbodSpinBox->setValue(1);
               }
               else
               {
                   ui->edComms12KbodSpinBox->setValue(0);
               }
               ui->edComms12KbodLabel->setText(blackFont + edComms12KbodStr + endFont);

               ui->edComms2SearchSpinBox->setEnabled(true);
               if ((byte1 & 0x80) == 0x80)
               {
                   ui->edComms2SearchSpinBox->setValue(1);
               }
               else
               {
                   ui->edComms2SearchSpinBox->setValue(0);
               }
               ui->edComms2SeachLabel->setText(blackFont + edComms2SearchEnabledStr + endFont);

               ui->edComms2SlaveChannelSpinBox->setEnabled(true);
               ui->edComms2SlaveChannelSpinBox->setValue((edCommsElements.at(13)).toInt());
               ui->edComms2SlaveChannelLabel->setText(blackFont + edComms2SlaveChannelStr + endFont);

               ui->edCommsStayInRXSpinBox->setEnabled(true);
               if ((byte2 & 0x08) == 0x08)
               {
                   ui->edCommsStayInRXSpinBox->setValue(1);
               }
               else
               {
                   ui->edCommsStayInRXSpinBox->setValue(0);
               }
               ui->edCommsStayInRXLabel->setText(blackFont + edCommsStayInRXStr + endFont);

               ui->edComms2250KbodSpinBox->setEnabled(true);
               if ((byte2 & 0x02) == 0x02)
               {
                   ui->edComms2250KbodSpinBox->setValue(1);
               }
               else
               {
                   ui->edComms2250KbodSpinBox->setValue(0);
               }
               ui->edComms2250KbodLabel->setText(blackFont + edComms2250KbodStr + endFont);
               // qDebug() << Q_FUNC_INFO << " byte2:" << byte2;

               ui->edCommsSendPushButton->setEnabled(false);
               ui->edCommsSavePushButton->setEnabled(false);
               ui->edComms2SendPushButton->setEnabled(false);
               ui->edComms2SavePushButton->setEnabled(false);

               m_edCommsChangesTracked->setIgnoreSignals(false);
           }
       }
       else
       {
           // handleResetEDComms();
       }
       /* In either disable pushbuttons, either unknown mac OR it right MAC, then values have not changed (just read in) */

   }

   void AmptGUI_X::handleEndDeviceVersionSettings(const QString &mac, const QString family, const QString & versionInfo)
   {
       // qDebug() << Q_FUNC_INFO << " received versionInfo for mac: " << mac << " family: " << family <<" versionInfo: " << versionInfo;
       QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

       if (mac == m_currentActiveMAC)
       {
           QStringList versionInfoElements = versionInfo.split(",");
           // qDebug() << Q_FUNC_INFO << " ################################################  size of versionInfoElements " << versionInfoElements.size();

           if (((family == Family1300V) || (family == Family1500V) || (family == Family1500V_30) || (family == Family600V_V2) || (family == Family600V_V2_2nd)) && versionInfoElements.size() != 7)
           {
               QString ErrorStr(Q_FUNC_INFO);

               ErrorStr += " Error: " + CurrentDateTime +" number of expected versionInfo(7) for family:" + family + " not received: " + QString::number(versionInfoElements.size());
               qDebug() << Q_FUNC_INFO << ErrorStr;
               emit publishError(ErrorStr);
               return;
           }
           else if ((family == Family1000V) && (versionInfoElements.size() != 6))
           {
               QString ErrorStr(Q_FUNC_INFO);
               ErrorStr += " Error: " + CurrentDateTime + " number of expected versionInfo(6)  for family:" + family + " not received: " + QString::number(versionInfoElements.size());
               qDebug() << Q_FUNC_INFO << ErrorStr;
               emit publishError(ErrorStr);
               return;
           }
           else
           {

               ui->versionVersionHighLabel->setText(blackFont + versionVersionHighStr + endFont);
               ui->versionVersionHighDataLabel->setEnabled(true);
               ui->versionVersionHighDataLabel->setText(versionInfoElements.at(0));

               ui->versionVersionLowLabel->setText(blackFont + versionVersionLowStr + endFont);
               ui->versionVersionLowDataLabel->setEnabled(true);
               ui->versionVersionLowDataLabel->setText(versionInfoElements.at(1));

               ui->versionSKUHighLabel->setText(blackFont + versionSKUHighStr + endFont);
               ui->versionSKUHighDataLabel->setEnabled(true);
               ui->versionSKUHighDataLabel->setText(versionInfoElements.at(2));

               ui->versionSKULowLabel->setText(blackFont + versionSKULowStr + endFont);
               ui->versionSKULowDataLabel->setEnabled(true);
               ui->versionSKULowDataLabel->setText(versionInfoElements.at(3));

               if (family != Family1000V)
               {
                   QString versionSuffixInfo = versionInfoElements.at(6);

                   ui->versionVersionSuffix1Label->setText(blackFont + versionVersionSuffix1Str + endFont);
                   ui->versionVersionSuffix1DataLabel->setEnabled(true);
                   ui->versionVersionSuffix1DataLabel->setText(versionSuffixInfo.at(0));

                   ui->versionVersionSuffix2Label->setText(blackFont + versionVersionSuffix2Str + endFont);
                   ui->versionVersionSuffix2DataLabel->setEnabled(true);
                   ui->versionVersionSuffix2DataLabel->setText(versionSuffixInfo.at(1));

                   ui->versionVersionSuffix3Label->setText(blackFont + versionVersionSuffix3Str + endFont);
                   ui->versionVersionSuffix3DataLabel->setEnabled(true);
                   ui->versionVersionSuffix3DataLabel->setText(versionSuffixInfo.at(2));
               }

               ui->versionShuntLabel->setText(blackFont + versionShuntStr + endFont);
               ui->versionShuntDataLabel->setEnabled(true);
               ui->versionShuntDataLabel->setText(versionInfoElements.at(4));

               ui->versionCommissionedLabel->setText(blackFont + versionCommissionedStr + endFont);
               ui->versionCommissionedDateTimeEdit->setEnabled(true);
              // LBC ui->versionCommissionedDateTimeEdit->setDateTime(versionInfoElements.at(5));

           }
       }

   }

void AmptGUI_X::visibleEFFeatures( const bool visible )
{
    ui->protectionsEFInputCurrentThresholdLabel->setVisible(visible);
    ui->protectionsEFInputCurrentThresholdSpinBox->setEnabled(visible);
    ui->protectionsEFInputCurrentThresholdSpinBox->setVisible(visible);

    ui->protectionsEFOccurrenceThresholdLabel->setVisible(visible);
    ui->protectionsEFOccurrenceThresholdSpinbox->setEnabled(visible);
    ui->protectionsEFOccurrenceThresholdSpinbox->setVisible(visible);

    ui->protectionsEFCountDownTimerLabel->setVisible(visible);
    ui->protectionsEFCountDownTimerSpinbox->setEnabled(visible);
    ui->protectionsEFCountDownTimerSpinbox->setVisible(visible);

    ui->protectionsEFAlphaNumeratorLabel->setVisible(visible);
    ui->protectionsEFAlphaNumeratorSpinbox->setEnabled(visible);
    ui->protectionsEFAlphaNumeratorSpinbox->setVisible(visible);

    ui->protectionsEFModuleOffLabel->setVisible(visible);
    ui->protectionsEFModuleOffSpinbox->setEnabled(visible);
    ui->protectionsEFModuleOffSpinbox->setVisible(visible);

    ui->protectionsAMF_DebugLabel->setVisible(visible);
    ui->protectionsAMF_DebugSpinbox->setEnabled(visible);
    ui->protectionsAMF_DebugSpinbox->setVisible(visible);

    if (visible == true)
    {
        ui->protectionsEFInputCurrentThresholdLabel->setText(blackFont + protection_1500V_EFInputCurrentThresholdStr + endFont);
        ui->protectionsEFOccurrenceThresholdLabel->setText(blackFont + protection_1500V_EFOccurrenceThresholdStr + endFont);
        ui->protectionsEFCountDownTimerLabel->setText(blackFont + protection_1500V_EFCountDownTimerStr + endFont);
        ui->protectionsEFAlphaNumeratorLabel->setText(blackFont + protection_1500V_EFAlphaNumeratorStr + endFont);
        ui->protectionsEFModuleOffLabel->setText(blackFont + protection_1500V_EFModuleOffStr + endFont);
        ui->protectionsAMF_DebugLabel->setText(blackFont + protection_Debug_Monitoring_Str + endFont);
    }
    else
    {
        ui->protectionsEFInputCurrentThresholdLabel->setText("");
        ui->protectionsEFOccurrenceThresholdLabel->setText("");
        ui->protectionsEFCountDownTimerLabel->setText("");
        ui->protectionsEFAlphaNumeratorLabel->setText("");
        ui->protectionsEFModuleOffLabel->setText("");
        ui->protectionsAMF_DebugLabel->setText("");
    }

}

void AmptGUI_X::visibleIinLimitFeatures( const bool visible)
{
    ui->protectionsIinLimitLabel->setVisible(visible);
    ui->protectionsIinLimitSpinbox->setEnabled(visible);
    ui->protectionsIinLimitSpinbox->setVisible(visible);

    ui->protectionsIinLimitOCStepsLabel->setVisible(visible);
    ui->protectionsIinLimitOCStepsSpinbox->setEnabled(visible);
    ui->protectionsIinLimitOCStepsSpinbox->setVisible(visible);

    ui->protectionsIinLimitOCDelayLabel->setVisible(visible);
    ui->protectionsIinLimitOCDelaySpinbox->setEnabled(visible);
    ui->protectionsIinLimitOCDelaySpinbox->setVisible(visible);

    ui->protectionsIinLimitTempAmbientAdjustLabel->setVisible(visible);
    ui->protectionsIinLimitTempAmbientAdjustSpinBox->setEnabled(visible);
    ui->protectionsIinLimitTempAmbientAdjustSpinBox->setVisible((visible));

    if (visible == true)
    {
        ui->protectionsIinLimitLabel->setText(blackFont + protection_1500V_30_IinLimitStr + endFont);
        ui->protectionsIinLimitOCStepsLabel->setText(blackFont + protection_1500V_30_IinLimitOCStepsStr + endFont);
        ui->protectionsIinLimitOCDelayLabel->setText(blackFont + protection_1500V_30_IinLimitOCDelayStr + endFont);
        ui->protectionsIinLimitTempAmbientAdjustLabel->setText(blackFont + protection_1500V_30_IinLimitTempAmbientAdjustStr + endFont);
    }
    else
    {
        ui->protectionsIinLimitLabel->setText("");
        ui->protectionsIinLimitOCStepsLabel->setText("");
        ui->protectionsIinLimitOCDelayLabel->setText("");
        ui->protectionsIinLimitTempAmbientAdjustLabel->setText("");
    }
}

   void AmptGUI_X::handleEndDeviceProtectionSettings(const QString & mac, const QString & family, const QString & protectionsInfo)
   {
      qDebug() << Q_FUNC_INFO << " setting up protections for mac: " << mac << " family:" << family << " with protections:" << protectionsInfo;

      /* QSignalBlocker(ui->protectionsFETFailureCountSpinBox);
       QSignalBlocker(ui->protectionsFETThresholdSpinBox);
       QSignalBlocker(ui->protectionsFETDeltaCurrentSpinBox );
       QSignalBlocker(ui->protectionsProtection1SpinBox);
       QSignalBlocker(ui->protectionsProtection2SpinBox);
       QSignalBlocker(ui->protectionsProtection3SpinBox);
       QSignalBlocker(ui->protectionsProtection4SpinBox); */


       if (mac == m_currentActiveMAC)
       {
           // qDebug() << Q_FUNC_INFO << "good mac" << mac;
           QStringList protectionElements = protectionsInfo.split(",");
           if (family == Family1300V)
           {
               m_protectionsChangesTracked->setIgnoreSignals(true);
               if ((protectionElements.size() == 9) || (protectionElements.size() == 13) ||
                       (protectionElements.size() == 16))
               {
                   // qDebug() << Q_FUNC_INFO << " good family:" << family;

                   ui->protectionsFETFailureCountLabel->setEnabled(true);
                   ui->protectionsFETFailureCountLabel->setText(blackFont + protectionFETFailureCountStr + endFont);

                   ui->protectionsFETFailureCountSpinBox->setEnabled(true);
                   ui->protectionsFETFailureCountSpinBox->setVisible(true);
                   ui->protectionsFETFailureCountSpinBox->setValue((protectionElements.at(1)).toInt());

                   ui->protectionsFETThresholdLabel->setEnabled(true);
                   ui->protectionsFETThresholdLabel->setText(blackFont + protectionFETFailureThresholdStr + endFont);

                   ui->protectionsFETThresholdSpinBox->setEnabled(true);
                   ui->protectionsFETThresholdSpinBox->setVisible(true);
                   ui->protectionsFETThresholdSpinBox->setValue((protectionElements.at(2)).toInt());

                   ui->protectionsFETDeltaCurrentLabel->setEnabled(true);
                   ui->protectionsFETDeltaCurrentLabel->setText(blackFont + protectionFETFailureDeltaCurrentStr + endFont);

                   ui->protectionsFETDeltaCurrentSpinBox->setEnabled(true);
                   ui->protectionsFETDeltaCurrentSpinBox->setVisible(true);
                   ui->protectionsFETDeltaCurrentSpinBox->setValue((protectionElements.at(3)).toInt());

                   // skip current to go to 255

                   ui->protectionsProtection1SpinBox->setEnabled(true);
                   ui->protectionsProtection1Label->setText(blackFont + protection1_1300VStr + endFont);

                   ui->protectionsProtection1SpinBox->setEnabled(true);
                   ui->protectionsProtection1SpinBox->setMinimum(0);
                   ui->protectionsProtection1SpinBox->setMaximum(65535);
                   ui->protectionsProtection1SpinBox->setToolTip("s * 20 i<XXX>, where XXX when divided by 33.33 sets the VhsVoutLimit control of OC");
                   ui->protectionsProtection1SpinBox->setValue((protectionElements.at(5)).toInt());

                   ui->protectionsProtection2Label->setEnabled(true);
                   ui->protectionsProtection2Label->setText(blackFont + protection2_1300VStr + endFont);

                   ui->protectionsProtection2SpinBox->setEnabled(true);
                   ui->protectionsProtection2SpinBox->setMinimum(0);
                   ui->protectionsProtection2SpinBox->setMaximum(255);
                   ui->protectionsProtection2SpinBox->setToolTip("s * 21 i<XXX>, where XXX is the settng for OC when VhsVoutLimit exceeded.");
                   ui->protectionsProtection2SpinBox->setValue((protectionElements.at(6)).toInt());

                   ui->protectionsProtection3Label->setEnabled(true);
                   ui->protectionsProtection3Label->setText(blackFont + protection3_1300VStr + endFont);

                   ui->protectionsProtection3SpinBox->setEnabled(true);
                   ui->protectionsProtection3SpinBox->setMinimum(0);
                   ui->protectionsProtection3SpinBox->setMaximum(65535);
                   ui->protectionsProtection3SpinBox->setToolTip("s * 22 i<XXX>, where XXX when divided by 33.33 sets the VhsVinsLimit control of OC");
                   ui->protectionsProtection3SpinBox->setValue((protectionElements.at(7)).toInt());

                   ui->protectionsProtection4Label->setEnabled(true);
                   ui->protectionsProtection4Label->setText(blackFont + protection4_1300VStr + endFont);

                   ui->protectionsProtection4SpinBox->setEnabled(true);
                   ui->protectionsProtection4SpinBox->setMinimum(0);
                   ui->protectionsProtection4SpinBox->setMaximum(255);
                   ui->protectionsProtection4SpinBox->setToolTip("s * 23 i<XXX>, where XXX is the settng for OC when VhsVinsLimit exceeded.");
                   ui->protectionsProtection4SpinBox->setValue((protectionElements.at(8)).toInt());

                   visibleEFFeatures(false);
                   visibleIinLimitFeatures(false);

                   if (protectionElements.at(0) == "1_D")
                   {
                       if (protectionElements.size() != 16)
                       {
                           QString ErrorStr(Q_FUNC_INFO);
                           ErrorStr += " Error: number of expected 1300V protections(13) for version 1_D not received: " + QString::number(protectionElements.size());
                           qDebug() << Q_FUNC_INFO << ErrorStr;
                           emit publishError(ErrorStr);
                       }
                       else
                       {
                           ui->protectionsAMF_Timer1Label->setVisible(true);
                           ui->protectionsAMF_Timer1Label->setEnabled(true);
                           ui->protectionsAMF_Timer1Label->setText(blackFont + protection_AMF_Timer1Str + endFont);

                           ui->protectionsAMF_Timer1Spinbox->setVisible(true);
                           ui->protectionsAMF_Timer1Spinbox->setEnabled(true);
                           ui->protectionsAMF_Timer1Spinbox->setValue((protectionElements.at(9)).toInt());

                           ui->protectionsAMF_Timer2Label->setVisible(true);
                           ui->protectionsAMF_Timer2Label->setEnabled(true);
                           ui->protectionsAMF_Timer2Label->setText(blackFont + protection_AMF_Timer2Str + endFont);

                           ui->protectionsAMF_Timer2Spinbox->setVisible(true);
                           ui->protectionsAMF_Timer2Spinbox->setEnabled(true);
                           ui->protectionsAMF_Timer2Spinbox->setValue((protectionElements.at(10)).toInt());

                           ui->protectionsAMF_V_OVLabel->setVisible(true);
                           ui->protectionsAMF_V_OVLabel->setEnabled(true);
                           ui->protectionsAMF_V_OVLabel->setText(blackFont + protection_AMF_V_OV_Str + endFont);

                           ui->protectionsAMF_V_OVSpinBox->setVisible(true);
                           ui->protectionsAMF_V_OVSpinBox->setEnabled(true);
                           ui->protectionsAMF_V_OVSpinBox->setValue((protectionElements.at(11)).toInt());

                           ui->protectionsAMF_I_OCLabel->setVisible(true);
                           ui->protectionsAMF_I_OCLabel->setEnabled(true);
                           ui->protectionsAMF_I_OCLabel->setText(blackFont + protection_AMF_I_OC_Str + endFont);

                           ui->protectionsAMF_I_OCSpinBox->setVisible(true);
                           ui->protectionsAMF_I_OCSpinBox->setEnabled(true);
                           ui->protectionsAMF_I_OCSpinBox->setValue((protectionElements.at(12)).toInt());

                           ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(true);
                           ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(true);
                           ui->protectionsAMF_MPP_Off_CyclesLabel->setText(blackFont + protection_AMF_MPP_Cycles_Off_Str + endFont);

                           ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(true);
                           ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(true);
                           ui->protectionsAMF_MPP_Off_CyclesSpinbox->setValue((protectionElements.at(13)).toInt());

                           ui->protectionsAMF_MPP_TimesOffLabel->setVisible(true);
                           ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(true);
                           ui->protectionsAMF_MPP_TimesOffLabel->setText(blackFont + protection_AMF_MPP_Number_Of_Off_Cycles + endFont);

                           ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(true);
                           ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(true);
                           ui->protectionsAMF_MPP_TimesOffSpinbox->setValue((protectionElements.at(14)).toInt());

                           ui->protectionsAMF_DebugLabel->setVisible(true);
                           ui->protectionsAMF_DebugLabel->setVisible(true);
                           ui->protectionsAMF_DebugLabel->setText(blackFont + protection_Debug_Monitoring_Str + endFont);

                           ui->protectionsAMF_DebugSpinbox->setVisible(true);
                           ui->protectionsAMF_DebugSpinbox->setEnabled(true);
                           ui->protectionsAMF_DebugSpinbox->setValue((protectionElements.at(15)).toInt());


                       }
                   } /* END if (protectionElements.at(0) == "1_D") */
                   else
                   {
                       ui->protectionsAMF_Timer1Label->setVisible(false);
                       ui->protectionsAMF_Timer1Label->setEnabled(false);

                       ui->protectionsAMF_Timer1Spinbox->setVisible(false);
                       ui->protectionsAMF_Timer1Spinbox->setEnabled(false);

                       ui->protectionsAMF_Timer2Label->setVisible(false);
                       ui->protectionsAMF_Timer2Label->setEnabled(false);

                       ui->protectionsAMF_Timer2Spinbox->setVisible(false);
                       ui->protectionsAMF_Timer2Spinbox->setEnabled(false);

                       ui->protectionsAMF_V_OVLabel->setVisible(false);
                       ui->protectionsAMF_V_OVLabel->setEnabled(false);

                       ui->protectionsAMF_V_OVSpinBox->setVisible(false);
                       ui->protectionsAMF_V_OVSpinBox->setEnabled(false);

                       ui->protectionsAMF_I_OCLabel->setVisible(false);
                       ui->protectionsAMF_I_OCLabel->setEnabled(false);

                       ui->protectionsAMF_I_OCSpinBox->setVisible(false);
                       ui->protectionsAMF_I_OCSpinBox->setEnabled(false);

                       ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(false);
                       ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(false);

                       ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(false);
                       ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(false);

                       ui->protectionsAMF_MPP_TimesOffLabel->setVisible(false);
                       ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(false);

                       ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(false);
                       ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(false);

                       ui->protectionsAMF_DebugLabel->setVisible(false);
                       ui->protectionsAMF_DebugLabel->setEnabled(false);

                       ui->protectionsAMF_DebugSpinbox->setVisible(false);
                       ui->protectionsAMF_DebugSpinbox->setEnabled(false);
                   }
               } /* END if ((protectionElements.size() == 9) || (protectionElements.size() == 13)) */
               else
               {
                   QString ErrorStr(Q_FUNC_INFO);
                   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                   ErrorStr += " Error: " + CurrentDateTime + " number of expected 1300V protections(9 or 13) not received: " + QString::number(protectionElements.size());
                   qDebug() << Q_FUNC_INFO << ErrorStr;
                   emit publishError(ErrorStr);
               }
               m_protectionsChangesTracked->setIgnoreSignals(false);
           } /* END if (family == Family1300V) */
           else if (family == Family1500V_2nd)
           {
               m_protectionsChangesTracked->setIgnoreSignals(true);
               if (protectionElements.size() == 10)
               {
                   qDebug() << Q_FUNC_INFO << " good family:" << family;
                   ui->protectionsFETFailureCountLabel->setEnabled(false);
                   ui->protectionsFETFailureCountLabel->setText(blackFont + "" + endFont);

                   ui->protectionsFETFailureCountSpinBox->setEnabled(false);
                   ui->protectionsFETFailureCountSpinBox->setValue(0);
                   ui->protectionsFETFailureCountSpinBox->setVisible(false);

                   ui->protectionsFETThresholdLabel->setEnabled(false);
                   ui->protectionsFETThresholdLabel->setText(blackFont + "" + endFont);

                   ui->protectionsFETThresholdSpinBox->setEnabled(false);
                   ui->protectionsFETThresholdSpinBox->setValue(0);
                   ui->protectionsFETThresholdSpinBox->setVisible(false);

                   ui->protectionsFETDeltaCurrentLabel->setEnabled(false);
                   ui->protectionsFETDeltaCurrentLabel->setText(blackFont + ""  + endFont);

                   ui->protectionsFETDeltaCurrentSpinBox->setEnabled(false);
                   ui->protectionsFETDeltaCurrentSpinBox->setValue(0);
                   ui->protectionsFETDeltaCurrentSpinBox->setVisible(false);

                   ui->protectionsProtection1Label->setText(blackFont + protection1_1500VStr + endFont);

                   ui->protectionsProtection1SpinBox->setEnabled(true);
                   ui->protectionsProtection1SpinBox->setMinimum(0);
                   ui->protectionsProtection1SpinBox->setMaximum(65535);
                   ui->protectionsProtection1SpinBox->setToolTip("s * 33 i<XXX>, where XXX is the time in milliseconds Vout must be a safe value before leaving protection.");
                   ui->protectionsProtection1SpinBox->setValue((protectionElements.at(0)).toInt());

                   ui->protectionsProtection2Label->setText(blackFont + protection2_1500VStr + endFont);

                   ui->protectionsProtection2SpinBox->setEnabled(true);
                   ui->protectionsProtection2SpinBox->setMinimum(0);
                   ui->protectionsProtection2SpinBox->setMaximum(65535);
                   ui->protectionsProtection2SpinBox->setToolTip("s * 34 i<XXX>, where XXX is the Lower Limit for Vout Protection (Volts * 33.33) .");
                   ui->protectionsProtection2SpinBox->setValue((protectionElements.at(1)).toInt());

                   ui->protectionsProtection3Label->setText(blackFont + protection3_1500VStr + endFont);

                   ui->protectionsProtection3SpinBox->setEnabled(true);
                   ui->protectionsProtection3SpinBox->setMinimum(0);
                   ui->protectionsProtection3SpinBox->setMaximum(65535);
                   ui->protectionsProtection3SpinBox->setToolTip("s * 35 i<XXX>, where XXX is the time in milliseconds Iout must be a safe value before leaving protection.");
                   ui->protectionsProtection3SpinBox->setValue((protectionElements.at(2)).toInt());

                   ui->protectionsProtection4Label->setText(blackFont + protection4_1500VStr + endFont);

                   ui->protectionsProtection4SpinBox->setEnabled(true);
                   ui->protectionsProtection4SpinBox->setMinimum(-100);
                   ui->protectionsProtection4SpinBox->setMaximum(32767);
                   ui->protectionsProtection4SpinBox->setToolTip("s * 36 i<XXX>, where XXX is the Lower Limit for Iout Protection (milliAmps) .");
                   ui->protectionsProtection4SpinBox->setValue((protectionElements.at(3)).toInt());

                   ui->protectionsEFInputCurrentThresholdLabel->setVisible(true);
                   ui->protectionsEFInputCurrentThresholdLabel->setText(blackFont + protection_1500V_EFInputCurrentThresholdStr + endFont);

                   ui->protectionsEFInputCurrentThresholdSpinBox->setEnabled(true);
                   ui->protectionsEFInputCurrentThresholdSpinBox->setVisible(true);
                   ui->protectionsEFInputCurrentThresholdSpinBox->setValue((protectionElements.at(4)).toInt());

                   ui->protectionsEFOccurrenceThresholdLabel->setVisible(true);
                   ui->protectionsEFOccurrenceThresholdLabel->setText(blackFont + protection_1500V_EFOccurrenceThresholdStr + endFont);

                   ui->protectionsEFOccurrenceThresholdSpinbox->setEnabled(true);
                   ui->protectionsEFOccurrenceThresholdSpinbox->setVisible(true);
                   ui->protectionsEFOccurrenceThresholdSpinbox->setValue((protectionElements.at(5)).toInt());

                   ui->protectionsEFCountDownTimerLabel->setVisible(true);
                   ui->protectionsEFCountDownTimerLabel->setText(blackFont + protection_1500V_EFCountDownTimerStr + endFont);

                   ui->protectionsEFCountDownTimerSpinbox->setEnabled(true);
                   ui->protectionsEFCountDownTimerSpinbox->setVisible(true);
                   ui->protectionsEFCountDownTimerSpinbox->setValue((protectionElements.at(6)).toInt());

                   ui->protectionsEFAlphaNumeratorLabel->setVisible(true);
                   ui->protectionsEFAlphaNumeratorLabel->setText(blackFont + protection_1500V_EFAlphaNumeratorStr + endFont);

                   ui->protectionsEFAlphaNumeratorSpinbox->setEnabled(true);
                   ui->protectionsEFAlphaNumeratorSpinbox->setVisible(true);
                   ui->protectionsEFAlphaNumeratorSpinbox->setValue((protectionElements.at(7)).toInt());

                   ui->protectionsEFModuleOffLabel->setVisible(true);
                   ui->protectionsEFModuleOffLabel->setText(blackFont + protection_1500V_EFModuleOffStr + endFont);

                   ui->protectionsEFModuleOffSpinbox->setEnabled(false);
                   ui->protectionsEFModuleOffSpinbox->setVisible(true);
                   qDebug() << Q_FUNC_INFO << " INFO: value at 8 is " << protectionElements.at(8);
                   ui->protectionsEFModuleOffSpinbox->setValue((protectionElements.at(8)).toInt());

                   visibleIinLimitFeatures(false);

                   ui->protectionsAMF_Timer1Label->setVisible(false);
                   ui->protectionsAMF_Timer1Label->setEnabled(false);

                   ui->protectionsAMF_Timer1Spinbox->setVisible(false);
                   ui->protectionsAMF_Timer1Spinbox->setEnabled(false);

                   ui->protectionsAMF_Timer2Label->setVisible(false);
                   ui->protectionsAMF_Timer2Label->setEnabled(false);

                   ui->protectionsAMF_Timer2Spinbox->setVisible(false);
                   ui->protectionsAMF_Timer2Spinbox->setEnabled(false);

                   ui->protectionsAMF_V_OVLabel->setVisible(false);
                   ui->protectionsAMF_V_OVLabel->setEnabled(false);

                   ui->protectionsAMF_V_OVSpinBox->setVisible(false);
                   ui->protectionsAMF_V_OVSpinBox->setEnabled(false);

                   ui->protectionsAMF_I_OCLabel->setVisible(false);
                   ui->protectionsAMF_I_OCLabel->setEnabled(false);

                   ui->protectionsAMF_I_OCSpinBox->setVisible(false);
                   ui->protectionsAMF_I_OCSpinBox->setEnabled(false);

                   ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(false);
                   ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(false);

                   ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(false);
                   ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(false);

                   ui->protectionsAMF_MPP_TimesOffLabel->setVisible(false);
                   ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(false);

                   ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(false);
                   ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(false);

                   ui->protectionsAMF_DebugLabel->setText(blackFont + protection_Debug_Monitoring_Str + endFont);
                   ui->protectionsAMF_DebugLabel->setVisible(true);
                   ui->protectionsAMF_DebugLabel->setEnabled(true);

                   ui->protectionsAMF_DebugSpinbox->setVisible(true);
                   ui->protectionsAMF_DebugSpinbox->setEnabled(true);
                   qDebug() << Q_FUNC_INFO << " INFO: value at 9 is " << protectionElements.at(9);
                   ui->protectionsAMF_DebugSpinbox->setValue((protectionElements.at(9)).toInt());
               }
               else
               {
                   QString ErrorStr(Q_FUNC_INFO);
                   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                   ErrorStr += " Error: " + CurrentDateTime + " number of expected 1500V_2nd protections(9) not received: " + QString::number(protectionElements.size());
                   qDebug() << Q_FUNC_INFO << ErrorStr;
                   emit publishError(ErrorStr);
               }

               m_protectionsChangesTracked->setIgnoreSignals(false);
           }
           else if ((family == Family1500V) || (family == Family1500V_30))
           {
               m_protectionsChangesTracked->setIgnoreSignals(true);
               if (protectionElements.size() >= 4)
               {
                   qDebug() << Q_FUNC_INFO << " good family:" << family << " numberOfElements: " << QString::number(protectionElements.size());
                   ui->protectionsFETFailureCountLabel->setEnabled(false);
                   ui->protectionsFETFailureCountLabel->setText(blackFont + "" + endFont);

                   ui->protectionsFETFailureCountSpinBox->setEnabled(false);
                   ui->protectionsFETFailureCountSpinBox->setValue(0);
                   ui->protectionsFETFailureCountSpinBox->setVisible(false);

                   ui->protectionsFETThresholdLabel->setEnabled(false);
                   ui->protectionsFETThresholdLabel->setText(blackFont + "" + endFont);

                   ui->protectionsFETThresholdSpinBox->setEnabled(false);
                   ui->protectionsFETThresholdSpinBox->setValue(0);
                   ui->protectionsFETThresholdSpinBox->setVisible(false);

                   ui->protectionsFETDeltaCurrentLabel->setEnabled(false);
                   ui->protectionsFETDeltaCurrentLabel->setText(blackFont + ""  + endFont);

                   ui->protectionsFETDeltaCurrentSpinBox->setEnabled(false);
                   ui->protectionsFETDeltaCurrentSpinBox->setValue(0);
                   ui->protectionsFETDeltaCurrentSpinBox->setVisible(false);

                   ui->protectionsProtection1Label->setText(blackFont + protection1_1500VStr + endFont);

                   ui->protectionsProtection1SpinBox->setEnabled(true);
                   ui->protectionsProtection1SpinBox->setMinimum(0);
                   ui->protectionsProtection1SpinBox->setMaximum(65535);
                   ui->protectionsProtection1SpinBox->setToolTip("s * 33 i<XXX>, where XXX is the time in milliseconds Vout must be a safe value before leaving protection.");
                   ui->protectionsProtection1SpinBox->setValue((protectionElements.at(0)).toInt());

                   ui->protectionsProtection2Label->setText(blackFont + protection2_1500VStr + endFont);

                   ui->protectionsProtection2SpinBox->setEnabled(true);
                   ui->protectionsProtection2SpinBox->setMinimum(0);
                   ui->protectionsProtection2SpinBox->setMaximum(65535);
                   ui->protectionsProtection2SpinBox->setToolTip("s * 34 i<XXX>, where XXX is the Lower Limit for Vout Protection (Volts * 33.33) .");
                   ui->protectionsProtection2SpinBox->setValue((protectionElements.at(1)).toInt());

                   ui->protectionsProtection3Label->setText(blackFont + protection3_1500VStr + endFont);

                   ui->protectionsProtection3SpinBox->setEnabled(true);
                   ui->protectionsProtection3SpinBox->setMinimum(0);
                   ui->protectionsProtection3SpinBox->setMaximum(65535);
                   ui->protectionsProtection3SpinBox->setToolTip("s * 35 i<XXX>, where XXX is the time in milliseconds Iout must be a safe value before leaving protection.");
                   ui->protectionsProtection3SpinBox->setValue((protectionElements.at(2)).toInt());

                   ui->protectionsProtection4Label->setText(blackFont + protection4_1500VStr + endFont);

                   ui->protectionsProtection4SpinBox->setEnabled(true);
                   ui->protectionsProtection4SpinBox->setMinimum(-100);
                   ui->protectionsProtection4SpinBox->setMaximum(32767);
                   ui->protectionsProtection4SpinBox->setToolTip("s * 36 i<XXX>, where XXX is the Lower Limit for Iout Protection (milliAmps) .");
                   ui->protectionsProtection4SpinBox->setValue((protectionElements.at(3)).toInt());

                   ui->protectionsAMF_Timer1Label->setVisible(false);
                   ui->protectionsAMF_Timer1Label->setEnabled(false);

                   ui->protectionsAMF_Timer1Spinbox->setVisible(false);
                   ui->protectionsAMF_Timer1Spinbox->setEnabled(false);

                   ui->protectionsAMF_Timer2Label->setVisible(false);
                   ui->protectionsAMF_Timer2Label->setEnabled(false);

                   ui->protectionsAMF_Timer2Spinbox->setVisible(false);
                   ui->protectionsAMF_Timer2Spinbox->setEnabled(false);

                   ui->protectionsAMF_V_OVLabel->setVisible(false);
                   ui->protectionsAMF_V_OVLabel->setEnabled(false);

                   ui->protectionsAMF_V_OVSpinBox->setVisible(false);
                   ui->protectionsAMF_V_OVSpinBox->setEnabled(false);

                   ui->protectionsAMF_I_OCLabel->setVisible(false);
                   ui->protectionsAMF_I_OCLabel->setEnabled(false);

                   ui->protectionsAMF_I_OCSpinBox->setVisible(false);
                   ui->protectionsAMF_I_OCSpinBox->setEnabled(false);

                   ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(false);
                   ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(false);

                   ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(false);
                   ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(false);

                   ui->protectionsAMF_MPP_TimesOffLabel->setVisible(false);
                   ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(false);

                   ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(false);
                   ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(false);

                   ui->protectionsAMF_DebugLabel->setVisible(false);
                   ui->protectionsAMF_DebugLabel->setEnabled(false);

                   ui->protectionsAMF_DebugSpinbox->setVisible(false);
                   ui->protectionsAMF_DebugSpinbox->setEnabled(false);


                   if (protectionElements.size() >= 9)
                   {

                       for (int i = 0; i < 10; i++)
                       {
                           qDebug() << Q_FUNC_INFO << " 1500V EF protection element:" << QString::number(i) << " valueAsStr:" << protectionElements.at(i);
                       }
                       ui->protectionsEFInputCurrentThresholdLabel->setEnabled(true);
                       ui->protectionsEFInputCurrentThresholdLabel->setText(blackFont + protection_1500V_EFInputCurrentThresholdStr + endFont);
                       ui->protectionsEFInputCurrentThresholdLabel->setVisible(true);
                       ui->protectionsEFInputCurrentThresholdSpinBox->setValue((protectionElements.at(4)).toInt());
                       ui->protectionsEFInputCurrentThresholdSpinBox->setEnabled(true);
                       ui->protectionsEFInputCurrentThresholdSpinBox->setVisible(true);

                       ui->protectionsEFOccurrenceThresholdLabel->setEnabled(true);
                       ui->protectionsEFOccurrenceThresholdLabel->setText(blackFont + protection_1500V_EFOccurrenceThresholdStr + endFont);
                       ui->protectionsEFOccurrenceThresholdLabel->setVisible(true);
                       ui->protectionsEFOccurrenceThresholdSpinbox->setValue((protectionElements.at(5)).toInt());
                       ui->protectionsEFOccurrenceThresholdSpinbox->setEnabled(true);
                       ui->protectionsEFOccurrenceThresholdSpinbox->setVisible(true);

                       ui->protectionsEFCountDownTimerLabel->setEnabled(true);
                       ui->protectionsEFCountDownTimerLabel->setVisible(true);
                       ui->protectionsEFCountDownTimerLabel->setText(blackFont + protection_1500V_EFCountDownTimerStr + endFont);
                       ui->protectionsEFCountDownTimerSpinbox->setValue((protectionElements.at(6)).toInt());
                       ui->protectionsEFCountDownTimerSpinbox->setEnabled(true);
                       ui->protectionsEFCountDownTimerSpinbox->setVisible(true);

                       ui->protectionsEFAlphaNumeratorLabel->setEnabled(true);
                       ui->protectionsEFAlphaNumeratorLabel->setVisible(true);
                       ui->protectionsEFAlphaNumeratorLabel->setText(blackFont + protection_1500V_EFAlphaNumeratorStr + endFont);
                       ui->protectionsEFAlphaNumeratorSpinbox->setValue((protectionElements.at(7)).toInt());
                       ui->protectionsEFAlphaNumeratorSpinbox->setEnabled(true);
                       ui->protectionsEFAlphaNumeratorSpinbox->setVisible(true);

                       ui->protectionsEFModuleOffLabel->setEnabled(true);
                       ui->protectionsEFModuleOffLabel->setVisible(true);
                       ui->protectionsEFModuleOffLabel->setText(blackFont + protection_1500V_EFModuleOffStr + endFont);
                       ui->protectionsEFModuleOffSpinbox->setValue((protectionElements.at(8)).toInt());
                       ui->protectionsEFModuleOffSpinbox->setEnabled(false);
                       ui->protectionsEFModuleOffSpinbox->setVisible(true);

                       ui->protectionsAMF_DebugLabel->setEnabled(true);
                       ui->protectionsAMF_DebugLabel->setVisible(true);
                       ui->protectionsAMF_DebugLabel->setText(blackFont + protection_Debug_Monitoring_Str + endFont);
                       ui->protectionsAMF_DebugSpinbox->setValue((protectionElements.at(9)).toInt());
                       ui->protectionsAMF_DebugSpinbox->setEnabled(true);
                       ui->protectionsAMF_DebugSpinbox->setVisible(true);
                       visibleIinLimitFeatures(false);
                   }
                   else if (protectionElements.size() == 8) // 1500V_30 at the moment
                   {
                       for (int i = 0; i < 8; i++)
                       {
                           qDebug() << Q_FUNC_INFO << " 1500V_30 protection element:" << QString::number(i) << " valueAsStr:" << protectionElements.at(i);
                       }

                       visibleEFFeatures(false);
                       ui->protectionsIinLimitLabel->setEnabled(true);
                       ui->protectionsIinLimitLabel->setText(blackFont + protection_1500V_30_IinLimitStr + endFont);
                       ui->protectionsIinLimitLabel->setVisible(true);
                       ui->protectionsIinLimitSpinbox->setValue((protectionElements.at(4)).toInt());
                       ui->protectionsIinLimitSpinbox->setEnabled(true);
                       ui->protectionsIinLimitSpinbox->setVisible(true);

                       unsigned char IinOCStepsAndDelayRegister = (protectionElements.at(5)).toUInt();

                       ui->protectionsIinLimitOCStepsLabel->setEnabled(true);
                       ui->protectionsIinLimitOCStepsLabel->setText(blackFont + protection_1500V_30_IinLimitOCStepsStr + endFont);
                       ui->protectionsIinLimitOCStepsLabel->setVisible(true);
                       ui->protectionsIinLimitOCStepsSpinbox->setValue((IinOCStepsAndDelayRegister >> 4));
                       ui->protectionsIinLimitOCStepsSpinbox->setEnabled(true);
                       ui->protectionsIinLimitOCStepsSpinbox->setVisible(true);

                       ui->protectionsIinLimitOCDelayLabel->setEnabled(true);
                       ui->protectionsIinLimitOCDelayLabel->setText(blackFont + protection_1500V_30_IinLimitOCDelayStr + endFont);
                       ui->protectionsIinLimitOCDelayLabel->setVisible(true);
                       ui->protectionsIinLimitOCDelaySpinbox->setValue((IinOCStepsAndDelayRegister & 0x0F));
                       ui->protectionsIinLimitOCDelaySpinbox->setEnabled(true);
                       ui->protectionsIinLimitOCDelaySpinbox->setVisible(true);

                       ui->protectionsIinLimitTempAmbientAdjustLabel->setEnabled(true);
                       ui->protectionsIinLimitTempAmbientAdjustLabel->setText(blackFont + protection_1500V_30_IinLimitTempAmbientAdjustStr + endFont);
                       ui->protectionsIinLimitTempAmbientAdjustLabel->setVisible(true);
                       ui->protectionsIinLimitTempAmbientAdjustSpinBox->setValue((protectionElements.at(7)).toInt());
                       ui->protectionsIinLimitTempAmbientAdjustSpinBox->setEnabled(true);
                       ui->protectionsIinLimitTempAmbientAdjustSpinBox ->setVisible(true);

                       ui->protectionsAMF_DebugLabel->setEnabled(true);
                       ui->protectionsAMF_DebugLabel->setVisible(true);
                       ui->protectionsAMF_DebugLabel->setText(blackFont + protection_Debug_Monitoring_Str + endFont);
                       ui->protectionsAMF_DebugSpinbox->setValue((protectionElements.at(6)).toInt());
                       ui->protectionsAMF_DebugSpinbox->setEnabled(true);
                       ui->protectionsAMF_DebugSpinbox->setVisible(true);




                   }
                   else
                   {
                       QString ErrorStr(Q_FUNC_INFO);
                       QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                       ErrorStr += " Error: " + CurrentDateTime + " number of expected 1500V or 1500V_30 protections(>=9 or 7) not received: " + QString::number(protectionElements.size());
                       qDebug() << Q_FUNC_INFO << ErrorStr;
                       emit publishError(ErrorStr);
                   }

               }
               else
               {
                   QString ErrorStr(Q_FUNC_INFO);
                   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                   ErrorStr += " Error: " + CurrentDateTime + " number of expected 1500V protections(> 4) not received: " + QString::number(protectionElements.size());
                   qDebug() << Q_FUNC_INFO << ErrorStr;
                   emit publishError(ErrorStr);
               }

               m_protectionsChangesTracked->setIgnoreSignals(false);
           }
           else if (family == Family1000V)
           {
               m_protectionsChangesTracked->setIgnoreSignals(true);
               if (protectionElements.size() == 8)
               {

                   // qDebug() << Q_FUNC_INFO << " good family:" << family;
                   ui->protectionsFETFailureCountLabel->setEnabled(true);
                   ui->protectionsFETFailureCountLabel->setText(blackFont + protectionFETFailureCountStr + endFont);

                   ui->protectionsFETFailureCountSpinBox->setEnabled(true);
                   ui->protectionsFETFailureCountSpinBox->setVisible(true);
                   ui->protectionsFETFailureCountSpinBox->setValue((protectionElements.at(0)).toInt());

                   ui->protectionsFETThresholdLabel->setEnabled(true);
                   ui->protectionsFETThresholdLabel->setText(blackFont + protectionFETFailureThresholdStr + endFont);

                   ui->protectionsFETThresholdSpinBox->setEnabled(true);
                   ui->protectionsFETThresholdSpinBox->setVisible(true);
                   ui->protectionsFETThresholdSpinBox->setValue((protectionElements.at(1)).toInt());

                   ui->protectionsFETDeltaCurrentLabel->setEnabled(true);
                   ui->protectionsFETDeltaCurrentLabel->setText(blackFont + protectionFETFailureDeltaCurrentStr + endFont);

                   ui->protectionsFETDeltaCurrentSpinBox->setEnabled(true);
                   ui->protectionsFETDeltaCurrentSpinBox->setVisible(true);
                   ui->protectionsFETDeltaCurrentSpinBox->setValue((protectionElements.at(2)).toInt());

                   ui->protectionsProtection1Label->setVisible(false);
                   ui->protectionsProtection1SpinBox->setEnabled(false);
                   ui->protectionsProtection1SpinBox->setVisible(false);

                   ui->protectionsProtection2Label->setVisible(false);
                   ui->protectionsProtection2SpinBox->setEnabled(false);
                   ui->protectionsProtection2SpinBox->setVisible(false);

                   ui->protectionsProtection3Label->setVisible(false);
                   ui->protectionsProtection3SpinBox->setEnabled(false);
                   ui->protectionsProtection3SpinBox->setVisible(false);

                   ui->protectionsProtection4Label->setVisible(false);
                   ui->protectionsProtection4SpinBox->setEnabled(false);
                   ui->protectionsProtection4SpinBox->setVisible(false);

                   visibleEFFeatures(false);
                   visibleIinLimitFeatures(false);

                   ui->protectionsAMF_Timer1Label->setVisible(false);
                   ui->protectionsAMF_Timer1Label->setEnabled(false);

                   ui->protectionsAMF_Timer1Spinbox->setVisible(false);
                   ui->protectionsAMF_Timer1Spinbox->setEnabled(false);

                   ui->protectionsAMF_Timer2Label->setVisible(false);
                   ui->protectionsAMF_Timer2Label->setEnabled(false);

                   ui->protectionsAMF_Timer2Spinbox->setVisible(false);
                   ui->protectionsAMF_Timer2Spinbox->setEnabled(false);

                   ui->protectionsAMF_V_OVLabel->setVisible(false);
                   ui->protectionsAMF_V_OVLabel->setEnabled(false);

                   ui->protectionsAMF_V_OVSpinBox->setVisible(false);
                   ui->protectionsAMF_V_OVSpinBox->setEnabled(false);

                   ui->protectionsAMF_I_OCLabel->setVisible(false);
                   ui->protectionsAMF_I_OCLabel->setEnabled(false);

                   ui->protectionsAMF_I_OCSpinBox->setVisible(false);
                   ui->protectionsAMF_I_OCSpinBox->setEnabled(false);

                   ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(false);
                   ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(false);

                   ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(false);
                   ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(false);

                   ui->protectionsAMF_MPP_TimesOffLabel->setVisible(false);
                   ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(false);

                   ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(false);
                   ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(false);

                   ui->protectionsAMF_DebugLabel->setVisible(false);
                   ui->protectionsAMF_DebugLabel->setEnabled(false);

                   ui->protectionsAMF_DebugSpinbox->setVisible(false);
                   ui->protectionsAMF_DebugSpinbox->setEnabled(false);


               }
               else
               {
                   QString ErrorStr(Q_FUNC_INFO);
                   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                   ErrorStr += " Error: " + CurrentDateTime + " number of expected 1000V protections(8) not received: " + QString::number(protectionElements.size());
                   qDebug() << Q_FUNC_INFO << ErrorStr;
                   emit publishError(ErrorStr);
               }

           }
           else if (family == Family600V_V2)
           {
               m_protectionsChangesTracked->setIgnoreSignals(true);

               // qDebug() << Q_FUNC_INFO << " good family:" << family;


               ui->protectionsFETFailureCountLabel->setEnabled(true);
               ui->protectionsFETFailureCountLabel->setText(blackFont + protectionFETFailureCountStr + endFont);

               ui->protectionsFETFailureCountSpinBox->setEnabled(true);
               ui->protectionsFETFailureCountSpinBox->setVisible(true);
               ui->protectionsFETFailureCountSpinBox->setValue((protectionElements.at(1)).toInt());

               ui->protectionsFETThresholdLabel->setEnabled(true);
               ui->protectionsFETThresholdLabel->setText(blackFont + protectionFETFailureThresholdStr + endFont);

               ui->protectionsFETThresholdSpinBox->setEnabled(true);
               ui->protectionsFETThresholdSpinBox->setVisible(true);
               ui->protectionsFETThresholdSpinBox->setValue((protectionElements.at(2)).toInt());

               ui->protectionsFETDeltaCurrentLabel->setEnabled(true);
               ui->protectionsFETDeltaCurrentLabel->setText(blackFont + protectionFETFailureDeltaCurrentStr + endFont);

               ui->protectionsFETDeltaCurrentSpinBox->setEnabled(true);
               ui->protectionsFETDeltaCurrentSpinBox->setVisible(true);
               ui->protectionsFETDeltaCurrentSpinBox->setValue((protectionElements.at(3)).toInt());

               ui->protectionsProtection1SpinBox->setEnabled(true);
               ui->protectionsProtection1Label->setText(blackFont + "oscLowCurrentL:" + endFont);
               ui->protectionsProtection1SpinBox->setEnabled(true);
               ui->protectionsProtection1SpinBox->setMinimum(-32765);
               ui->protectionsProtection1SpinBox->setMaximum(32767);
               ui->protectionsProtection1SpinBox->setToolTip("s * 19 i<XXX>, 0 disables");
               ui->protectionsProtection1SpinBox->setValue((protectionElements.at(4)).toInt());

               //ui->protectionsProtection1Label->setVisible(false);
               //ui->protectionsProtection1SpinBox->setEnabled(false);
               //ui->protectionsProtection1SpinBox->setVisible(false);

               ui->protectionsProtection2Label->setVisible(false);
               ui->protectionsProtection2SpinBox->setEnabled(false);
               ui->protectionsProtection2SpinBox->setVisible(false);

               ui->protectionsProtection3Label->setVisible(false);
               ui->protectionsProtection3SpinBox->setEnabled(false);
               ui->protectionsProtection3SpinBox->setVisible(false);

               ui->protectionsProtection4Label->setVisible(false);
               ui->protectionsProtection4SpinBox->setEnabled(false);
               ui->protectionsProtection4SpinBox->setVisible(false);

               visibleEFFeatures(false);
               visibleIinLimitFeatures(false);

               ui->protectionsAMF_Timer1Label->setVisible(false);
               ui->protectionsAMF_Timer1Label->setEnabled(false);

               ui->protectionsAMF_Timer1Spinbox->setVisible(false);
               ui->protectionsAMF_Timer1Spinbox->setEnabled(false);

               ui->protectionsAMF_Timer2Label->setVisible(false);
               ui->protectionsAMF_Timer2Label->setEnabled(false);

               ui->protectionsAMF_Timer2Spinbox->setVisible(false);
               ui->protectionsAMF_Timer2Spinbox->setEnabled(false);

               ui->protectionsAMF_V_OVLabel->setVisible(false);
               ui->protectionsAMF_V_OVLabel->setEnabled(false);

               ui->protectionsAMF_V_OVSpinBox->setVisible(false);
               ui->protectionsAMF_V_OVSpinBox->setEnabled(false);

               ui->protectionsAMF_I_OCLabel->setVisible(false);
               ui->protectionsAMF_I_OCLabel->setEnabled(false);

               ui->protectionsAMF_I_OCSpinBox->setVisible(false);
               ui->protectionsAMF_I_OCSpinBox->setEnabled(false);

               ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(false);
               ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(false);

               ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(false);
               ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(false);

               ui->protectionsAMF_MPP_TimesOffLabel->setVisible(false);
               ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(false);

               ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(false);
               ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(false);

               ui->protectionsAMF_DebugLabel->setVisible(false);
               ui->protectionsAMF_DebugLabel->setEnabled(false);

               ui->protectionsAMF_DebugSpinbox->setVisible(false);
               ui->protectionsAMF_DebugSpinbox->setEnabled(false);

           }
           else if (family == Family600V_V2_2nd)
           {
               m_protectionsChangesTracked->setIgnoreSignals(true);

               qDebug() << Q_FUNC_INFO << " good family:" << family;
               if ((protectionElements.size() == 9) || (protectionElements.size() == 16))
               {


                   // LBC .at(0) is Version skip


                   ui->protectionsFETFailureCountLabel->setEnabled(true);
                   ui->protectionsFETFailureCountLabel->setText(blackFont + protectionFETFailureCountStr + endFont);

                   ui->protectionsFETFailureCountSpinBox->setEnabled(true);
                   ui->protectionsFETFailureCountSpinBox->setVisible(true);
                   ui->protectionsFETFailureCountSpinBox->setValue((protectionElements.at(1)).toInt());

                   ui->protectionsFETThresholdLabel->setEnabled(true);
                   ui->protectionsFETThresholdLabel->setText(blackFont + protectionFETFailureThresholdStr + endFont);

                   ui->protectionsFETThresholdSpinBox->setEnabled(true);
                   ui->protectionsFETThresholdSpinBox->setVisible(true);
                   ui->protectionsFETThresholdSpinBox->setValue((protectionElements.at(2)).toInt());

                   ui->protectionsFETDeltaCurrentLabel->setEnabled(true);
                   ui->protectionsFETDeltaCurrentLabel->setText(blackFont + protectionFETFailureDeltaCurrentStr + endFont);

                   ui->protectionsFETDeltaCurrentSpinBox->setEnabled(true);
                   ui->protectionsFETDeltaCurrentSpinBox->setVisible(true);
                   ui->protectionsFETDeltaCurrentSpinBox->setValue((protectionElements.at(3)).toInt());

                   // at(4) is Low current setting to go to channel 255

                   ui->protectionsProtection1SpinBox->setEnabled(true);
                   ui->protectionsProtection1Label->setText(blackFont + protection1_1300VStr + endFont);

                   ui->protectionsProtection1SpinBox->setEnabled(true);
                   ui->protectionsProtection1SpinBox->setMinimum(0);
                   ui->protectionsProtection1SpinBox->setMaximum(65535);
                   ui->protectionsProtection1SpinBox->setToolTip("s * 20 i<XXX>, where XXX when divided by 33.33 sets the VhsVoutLimit control of OC");
                   ui->protectionsProtection1SpinBox->setValue((protectionElements.at(5)).toInt());

                   ui->protectionsProtection2Label->setEnabled(true);
                   ui->protectionsProtection2Label->setText(blackFont + protection2_1300VStr + endFont);

                   ui->protectionsProtection2SpinBox->setEnabled(true);
                   ui->protectionsProtection2SpinBox->setMinimum(0);
                   ui->protectionsProtection2SpinBox->setMaximum(255);
                   ui->protectionsProtection2SpinBox->setToolTip("s * 21 i<XXX>, where XXX is the settng for OC when VhsVoutLimit exceeded.");
                   ui->protectionsProtection2SpinBox->setValue((protectionElements.at(6)).toInt());

                   ui->protectionsProtection3Label->setEnabled(true);
                   ui->protectionsProtection3Label->setText(blackFont + protection3_1300VStr + endFont);

                   ui->protectionsProtection3SpinBox->setEnabled(true);
                   ui->protectionsProtection3SpinBox->setMinimum(0);
                   ui->protectionsProtection3SpinBox->setMaximum(65535);
                   ui->protectionsProtection3SpinBox->setToolTip("s * 22 i<XXX>, where XXX when divided by 33.33 sets the VhsVinsLimit control of OC");
                   ui->protectionsProtection3SpinBox->setValue((protectionElements.at(7)).toInt());

                   ui->protectionsProtection4Label->setEnabled(true);
                   ui->protectionsProtection4Label->setText(blackFont + protection4_1300VStr + endFont);

                   ui->protectionsProtection4SpinBox->setEnabled(true);
                   ui->protectionsProtection4SpinBox->setMinimum(0);
                   ui->protectionsProtection4SpinBox->setMaximum(255);
                   ui->protectionsProtection4SpinBox->setToolTip("s * 23 i<XXX>, where XXX is the settng for OC when VhsVinsLimit exceeded.");
                   ui->protectionsProtection4SpinBox->setValue((protectionElements.at(8)).toInt());
                   // skip current to go to 255

                   visibleEFFeatures(false);
                   visibleIinLimitFeatures(false);

                   // qDebug() << Q_FUNC_INFO << " INFO: versionHexStr: " << protectionElements.at(0);

                   if ((protectionElements.at(0) == "1F ") || (protectionElements.at(0) == "1G "))
                   {
                       if (protectionElements.size() != 16)
                       {
                           QString ErrorStr(Q_FUNC_INFO);
                           ErrorStr += " Error: number of expected 600V V2 protections(16) for version " + protectionElements.at(0) + " not received: " + QString::number(protectionElements.size());
                           qDebug() << Q_FUNC_INFO << ErrorStr;
                           emit publishError(ErrorStr);
                       }
                       else
                       {
                           ui->protectionsAMF_Timer1Label->setVisible(true);
                           ui->protectionsAMF_Timer1Label->setEnabled(true);
                           ui->protectionsAMF_Timer1Label->setText(blackFont + protection_AMF_Timer1Str + endFont);

                           ui->protectionsAMF_Timer1Spinbox->setVisible(true);
                           ui->protectionsAMF_Timer1Spinbox->setEnabled(true);
                           ui->protectionsAMF_Timer1Spinbox->setValue((protectionElements.at(9)).toInt());

                           ui->protectionsAMF_Timer2Label->setVisible(true);
                           ui->protectionsAMF_Timer2Label->setEnabled(true);
                           ui->protectionsAMF_Timer2Label->setText(blackFont + protection_AMF_Timer2Str + endFont);

                           ui->protectionsAMF_Timer2Spinbox->setVisible(true);
                           ui->protectionsAMF_Timer2Spinbox->setEnabled(true);
                           ui->protectionsAMF_Timer2Spinbox->setValue((protectionElements.at(10)).toInt());

                           ui->protectionsAMF_V_OVLabel->setVisible(true);
                           ui->protectionsAMF_V_OVLabel->setEnabled(true);
                           ui->protectionsAMF_V_OVLabel->setText(blackFont + protection_AMF_V_OV_Str + endFont);

                           ui->protectionsAMF_V_OVSpinBox->setVisible(true);
                           ui->protectionsAMF_V_OVSpinBox->setEnabled(true);
                           ui->protectionsAMF_V_OVSpinBox->setValue((protectionElements.at(11)).toInt());

                           ui->protectionsAMF_I_OCLabel->setVisible(true);
                           ui->protectionsAMF_I_OCLabel->setEnabled(true);
                           ui->protectionsAMF_I_OCLabel->setText(blackFont + protection_AMF_I_OC_Str + endFont);

                           ui->protectionsAMF_I_OCSpinBox->setVisible(true);
                           ui->protectionsAMF_I_OCSpinBox->setEnabled(true);
                           ui->protectionsAMF_I_OCSpinBox->setValue((protectionElements.at(12)).toInt());

                           ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(true);
                           ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(true);
                           ui->protectionsAMF_MPP_Off_CyclesLabel->setText(blackFont + protection_AMF_MPP_Cycles_Off_Str + endFont);

                           ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(true);
                           ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(true);
                           ui->protectionsAMF_MPP_Off_CyclesSpinbox->setValue((protectionElements.at(13)).toInt());

                           ui->protectionsAMF_MPP_TimesOffLabel->setVisible(true);
                           ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(true);
                           ui->protectionsAMF_MPP_TimesOffLabel->setText(blackFont + protection_AMF_MPP_Number_Of_Off_Cycles + endFont);

                           ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(true);
                           ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(true);
                           ui->protectionsAMF_MPP_TimesOffSpinbox->setValue((protectionElements.at(14)).toInt());

                           ui->protectionsAMF_DebugLabel->setVisible(true);
                           ui->protectionsAMF_DebugLabel->setVisible(true);
                           ui->protectionsAMF_DebugLabel->setText(blackFont + protection_Debug_Monitoring_Str + endFont);

                           ui->protectionsAMF_DebugSpinbox->setVisible(true);
                           ui->protectionsAMF_DebugSpinbox->setEnabled(true);
                           ui->protectionsAMF_DebugSpinbox->setValue((protectionElements.at(15)).toInt());

                           /* LBC Need to add labels and spin boxes for CyclesOff, TimesToCycle, and Debug */
                       }
                   } /* END if ((protectionElements.at(0) == "1_F") || (protectionElements.at(0) == "1G "))*/
                   else
                   {
                       ui->protectionsAMF_Timer1Label->setVisible(false);
                       ui->protectionsAMF_Timer1Label->setEnabled(false);

                       ui->protectionsAMF_Timer1Spinbox->setVisible(false);
                       ui->protectionsAMF_Timer1Spinbox->setEnabled(false);

                       ui->protectionsAMF_Timer2Label->setVisible(false);
                       ui->protectionsAMF_Timer2Label->setEnabled(false);

                       ui->protectionsAMF_Timer2Spinbox->setVisible(false);
                       ui->protectionsAMF_Timer2Spinbox->setEnabled(false);

                       ui->protectionsAMF_V_OVLabel->setVisible(false);
                       ui->protectionsAMF_V_OVLabel->setEnabled(false);

                       ui->protectionsAMF_V_OVSpinBox->setVisible(false);
                       ui->protectionsAMF_V_OVSpinBox->setEnabled(false);

                       ui->protectionsAMF_I_OCLabel->setVisible(false);
                       ui->protectionsAMF_I_OCLabel->setEnabled(false);

                       ui->protectionsAMF_I_OCSpinBox->setVisible(false);
                       ui->protectionsAMF_I_OCSpinBox->setEnabled(false);

                       ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(false);
                       ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(false);

                       ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(false);
                       ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(false);

                       ui->protectionsAMF_MPP_TimesOffLabel->setVisible(false);
                       ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(false);

                       ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(false);
                       ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(false);

                       ui->protectionsAMF_DebugLabel->setVisible(false);
                       ui->protectionsAMF_DebugLabel->setEnabled(false);

                       ui->protectionsAMF_DebugSpinbox->setVisible(false);
                       ui->protectionsAMF_DebugSpinbox->setEnabled(false);


                   }
               } /* END if ((protectionElements.size() == 9) || (protectionElements.size() == 13)) */
               else
               {
                   QString ErrorStr(Q_FUNC_INFO);
                   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                   ErrorStr += " Error: " + CurrentDateTime + " number of expected 600V2 protections(9 or 13) not received: " + QString::number(protectionElements.size());
                   qDebug() << Q_FUNC_INFO << ErrorStr;
                   emit publishError(ErrorStr);
               }
               m_protectionsChangesTracked->setIgnoreSignals(false);
           }

       } /* END if (mac == m_currentActiveMAC) */

       qDebug() << Q_FUNC_INFO << " INFO: Exiting ... ";
   }

void AmptGUI_X::handleResetProtections( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: ResetParameterBlockValues:" << QString::number(ResetParameterBlockValues);

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();
    QString tFontColor = blackFont;

    if ((theFamily == Family1300V) || (theFamily == Family1300V_2nd) || (theFamily == Family600V_V2))
    {
        m_protectionsChangesTracked->setIgnoreSignals(true);

        visibleEFFeatures(false);
        visibleIinLimitFeatures(false);

        if (ResetParameterBlockValues == true)
        {
            tFontColor = greyFont;

            ui->protectionsIinLimitLabel->setVisible(false);
            ui->protectionsIinLimitLabel->setEnabled(false);
            ui->protectionsIinLimitSpinbox->setEnabled(false);
            ui->protectionsIinLimitSpinbox->setVisible(false);
            ui->protectionsIinLimitLabel->setText("");

            ui->protectionsIinLimitOCDelaySpinbox->setVisible(false);
            ui->protectionsIinLimitOCDelayLabel->setEnabled(false);
            ui->protectionsIinLimitOCDelaySpinbox->setEnabled(false);
            ui->protectionsIinLimitOCDelaySpinbox->setVisible(false);
            ui->protectionsIinLimitOCDelayLabel->setText("");

            ui->protectionsIinLimitOCStepsLabel->setVisible(false);
            ui->protectionsIinLimitOCStepsLabel->setEnabled(false);
            ui->protectionsIinLimitOCStepsSpinbox->setEnabled(false);
            ui->protectionsIinLimitOCStepsSpinbox->setVisible(false);
            ui->protectionsIinLimitOCStepsLabel->setText("");

            ui->protectionsIinLimitTempAmbientAdjustLabel->setVisible(false);
            ui->protectionsIinLimitTempAmbientAdjustLabel->setEnabled(false);
            ui->protectionsIinLimitTempAmbientAdjustSpinBox->setEnabled(false);
            ui->protectionsIinLimitTempAmbientAdjustSpinBox->setVisible(false);
            ui->protectionsIinLimitTempAmbientAdjustLabel->setText("");

            ui->protectionsEFInputCurrentThresholdLabel->setVisible(false);
            ui->protectionsEFInputCurrentThresholdLabel->setEnabled(false);
            ui->protectionsEFInputCurrentThresholdSpinBox->setEnabled(false);
            ui->protectionsEFInputCurrentThresholdSpinBox->setVisible(false);

            ui->protectionsEFOccurrenceThresholdLabel->setVisible(false);
            ui->protectionsEFOccurrenceThresholdLabel->setEnabled(false);
            ui->protectionsEFOccurrenceThresholdSpinbox->setEnabled(false);
            ui->protectionsEFOccurrenceThresholdSpinbox->setVisible(false);

            ui->protectionsEFCountDownTimerLabel->setVisible(false);
            ui->protectionsEFCountDownTimerLabel->setEnabled(false);
            ui->protectionsEFCountDownTimerSpinbox->setEnabled(false);
            ui->protectionsEFCountDownTimerSpinbox->setVisible(false);

            ui->protectionsEFAlphaNumeratorLabel->setVisible(false);
            ui->protectionsEFAlphaNumeratorLabel->setEnabled(false);
            ui->protectionsEFAlphaNumeratorSpinbox->setEnabled(false);
            ui->protectionsEFAlphaNumeratorSpinbox->setVisible(false);

            ui->protectionsFETFailureCountLabel->setEnabled(false);
            ui->protectionsFETFailureCountSpinBox->setEnabled(false);
            ui->protectionsFETFailureCountLabel->setVisible(true);
            ui->protectionsFETFailureCountSpinBox->setVisible(true);

            ui->protectionsFETThresholdLabel->setEnabled(false);
            ui->protectionsFETThresholdSpinBox->setEnabled(false);
            ui->protectionsFETThresholdLabel->setVisible(true);
            ui->protectionsFETThresholdSpinBox->setVisible(true);

            ui->protectionsFETDeltaCurrentLabel->setEnabled(false);
            ui->protectionsFETDeltaCurrentSpinBox->setEnabled(false);
            ui->protectionsFETDeltaCurrentLabel->setVisible(true);
            ui->protectionsFETDeltaCurrentSpinBox->setVisible(true);

            // skip current to go to 255

            ui->protectionsProtection1Label->setEnabled(false);
            ui->protectionsProtection1SpinBox->setEnabled(false);

            ui->protectionsProtection2Label->setEnabled(false);
            ui->protectionsProtection2SpinBox->setEnabled(false);

            ui->protectionsProtection3Label->setEnabled(false);
            ui->protectionsProtection3SpinBox->setEnabled(false);

            ui->protectionsProtection4Label->setEnabled(false);
            ui->protectionsProtection4SpinBox->setEnabled(false);

            ui->protectionsAMF_Timer1Label->setVisible(false);
            ui->protectionsAMF_Timer1Spinbox->setVisible(false);

            ui->protectionsAMF_Timer2Label->setVisible(false);
            ui->protectionsAMF_Timer2Spinbox->setVisible(false);

            ui->protectionsAMF_V_OVLabel->setVisible(false);
            ui->protectionsAMF_V_OVSpinBox->setVisible(false);

            ui->protectionsAMF_I_OCLabel->setVisible(false);
            ui->protectionsAMF_I_OCSpinBox->setVisible(false);

            ui->protectionsAMF_MPP_Off_CyclesLabel->setVisible(false);
            ui->protectionsAMF_MPP_Off_CyclesLabel->setEnabled(false);

            ui->protectionsAMF_MPP_Off_CyclesSpinbox->setVisible(false);
            ui->protectionsAMF_MPP_Off_CyclesSpinbox->setEnabled(false);

            ui->protectionsAMF_MPP_TimesOffLabel->setVisible(false);
            ui->protectionsAMF_MPP_TimesOffLabel->setEnabled(false);

            ui->protectionsAMF_MPP_TimesOffSpinbox->setVisible(false);
            ui->protectionsAMF_MPP_TimesOffSpinbox->setEnabled(false);

            ui->protectionsAMF_DebugLabel->setVisible(false);
            ui->protectionsAMF_DebugLabel->setEnabled(false);

            ui->protectionsAMF_DebugSpinbox->setVisible(false);
            ui->protectionsAMF_DebugSpinbox->setEnabled(false);
        }

        ui->protectionsSendPushButton->setEnabled(false);
        ui->protectionsSavePushButton->setEnabled(false);

        ui->protectionsFETFailureCountLabel->setText(tFontColor + protectionFETFailureCountStr + endFont);
        ui->protectionsFETThresholdLabel->setText(tFontColor + protectionFETFailureThresholdStr + endFont);
        ui->protectionsFETDeltaCurrentLabel->setText(tFontColor + protectionFETFailureDeltaCurrentStr + endFont);
        ui->protectionsProtection1Label->setText(tFontColor + protection1_1300VStr + endFont);
        ui->protectionsProtection2Label->setText(tFontColor + protection2_1300VStr + endFont);
        ui->protectionsProtection3Label->setText(tFontColor + protection3_1300VStr + endFont);
        ui->protectionsProtection4Label->setText(tFontColor + protection4_1300VStr + endFont);
        ui->protectionsAMF_Timer1Label->setText(tFontColor + protection_AMF_Timer1Str + endFont);
        ui->protectionsAMF_Timer2Label->setText(tFontColor + protection_AMF_Timer2Str + endFont);
        ui->protectionsAMF_V_OVLabel->setText(tFontColor + protection_AMF_V_OV_Str + endFont);
        ui->protectionsAMF_I_OCLabel->setText(tFontColor + protection_AMF_I_OC_Str + endFont);
        ui->protectionsAMF_MPP_Off_CyclesLabel->setText(tFontColor + protection_AMF_MPP_Cycles_Off_Str + endFont);
        ui->protectionsAMF_MPP_TimesOffLabel->setText(blackFont + protection_AMF_MPP_Number_Of_Off_Cycles + endFont);
        ui->protectionsAMF_DebugLabel->setText(blackFont + protection_Debug_Monitoring_Str + endFont);

        m_protectionsChangesTracked->setIgnoreSignals(false);
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_2nd) || (theFamily == Family1500V_30))
    {
        tFontColor = blackFont;
        bool setValue = !ResetParameterBlockValues;

        m_protectionsChangesTracked->setIgnoreSignals(true);

        qDebug() << Q_FUNC_INFO << " INFO 1500V setValue:" << QString::number(setValue);

        ui->protectionsFETFailureCountLabel->setEnabled(false);
        ui->protectionsFETFailureCountSpinBox->setEnabled(false);
        ui->protectionsFETFailureCountLabel->setVisible(false);
        ui->protectionsFETFailureCountSpinBox->setVisible(false);

        ui->protectionsFETThresholdLabel->setEnabled(false);
        ui->protectionsFETThresholdSpinBox->setEnabled(false);
        ui->protectionsFETThresholdLabel->setVisible(false);
        ui->protectionsFETThresholdSpinBox->setVisible(false);

        ui->protectionsFETDeltaCurrentLabel->setEnabled(false);
        ui->protectionsFETDeltaCurrentSpinBox->setEnabled(false);
        ui->protectionsFETDeltaCurrentLabel->setVisible(false);
        ui->protectionsFETDeltaCurrentSpinBox->setVisible(false);

        ui->protectionsAMF_DebugLabel->setVisible(false);
        ui->protectionsAMF_DebugLabel->setEnabled(false);
        ui->protectionsAMF_DebugSpinbox->setEnabled(setValue);
        ui->protectionsAMF_DebugSpinbox->setVisible(false);
        ui->protectionsAMF_DebugLabel->setText("");

        ui->protectionsProtection1Label->setEnabled(true);
        ui->protectionsProtection1SpinBox->setEnabled(true);

        ui->protectionsProtection2Label->setEnabled(true);
        ui->protectionsProtection2SpinBox->setEnabled(true);

        ui->protectionsProtection3Label->setEnabled(true);
        ui->protectionsProtection3SpinBox->setEnabled(true);

        ui->protectionsProtection4Label->setEnabled(true);
        ui->protectionsProtection4SpinBox->setEnabled(true);

        ui->protectionsProtection1Label->setText(tFontColor + protection1_1500VStr + endFont);
        ui->protectionsProtection2Label->setText(tFontColor + protection2_1500VStr + endFont);
        ui->protectionsProtection3Label->setText(tFontColor + protection3_1500VStr + endFont);
        ui->protectionsProtection4Label->setText(tFontColor + protection4_1500VStr + endFont);

        ui->protectionsSendPushButton->setEnabled(false);
        ui->protectionsSavePushButton->setEnabled(false);

        if (theFamily == Family1500V_30)
        {
            ui->protectionsIinLimitLabel->setVisible(true);
            ui->protectionsIinLimitLabel->setEnabled(true);
            ui->protectionsIinLimitSpinbox->setEnabled(true);
            ui->protectionsIinLimitSpinbox->setVisible(true);

            ui->protectionsIinLimitOCDelayLabel->setVisible(true);
            ui->protectionsIinLimitOCDelayLabel->setEnabled(true);
            ui->protectionsIinLimitOCDelaySpinbox->setEnabled(true);
            ui->protectionsIinLimitOCDelaySpinbox->setVisible(true);

            ui->protectionsIinLimitOCStepsLabel->setVisible(true);
            ui->protectionsIinLimitOCStepsLabel->setEnabled(true);
            ui->protectionsIinLimitOCStepsSpinbox->setEnabled(true);
            ui->protectionsIinLimitOCStepsSpinbox->setVisible(true);

            ui->protectionsIinLimitTempAmbientAdjustLabel->setVisible(true);
            ui->protectionsIinLimitTempAmbientAdjustLabel->setEnabled(true);
            ui->protectionsIinLimitTempAmbientAdjustSpinBox->setEnabled(true);
            ui->protectionsIinLimitTempAmbientAdjustSpinBox->setVisible(true);


            ui->protectionsAMF_DebugLabel->setVisible(true);
            ui->protectionsAMF_DebugLabel->setEnabled(true);
            ui->protectionsAMF_DebugSpinbox->setEnabled(true);
            ui->protectionsAMF_DebugSpinbox->setVisible(true);

            ui->protectionsIinLimitLabel->setText(tFontColor + protection_1500V_30_IinLimitStr + endFont);
            ui->protectionsIinLimitOCDelayLabel->setText(tFontColor + protection_1500V_30_IinLimitOCDelayStr + endFont);
            ui->protectionsIinLimitOCStepsLabel->setText(tFontColor + protection_1500V_30_IinLimitOCStepsStr + endFont);
            ui->protectionsIinLimitTempAmbientAdjustLabel->setText(tFontColor + protection_1500V_30_IinLimitTempAmbientAdjustStr + endFont);
            ui->protectionsAMF_DebugLabel->setText(tFontColor + protection_Debug_Monitoring_Str + endFont);
        }
        else
        {
            ui->protectionsIinLimitLabel->setVisible(false);
            ui->protectionsIinLimitLabel->setEnabled(false);
            ui->protectionsIinLimitSpinbox->setEnabled(false);
            ui->protectionsIinLimitSpinbox->setVisible(false);
            ui->protectionsIinLimitLabel->setText("");

            ui->protectionsIinLimitOCDelaySpinbox->setVisible(false);
            ui->protectionsIinLimitOCDelayLabel->setEnabled(false);
            ui->protectionsIinLimitOCDelaySpinbox->setEnabled(false);
            ui->protectionsIinLimitOCDelaySpinbox->setVisible(false);
            ui->protectionsIinLimitOCDelayLabel->setText("");

            ui->protectionsIinLimitOCStepsLabel->setVisible(false);
            ui->protectionsIinLimitOCStepsLabel->setEnabled(false);
            ui->protectionsIinLimitOCStepsSpinbox->setEnabled(false);
            ui->protectionsIinLimitOCStepsSpinbox->setVisible(false);
            ui->protectionsIinLimitOCStepsLabel->setText("");

            ui->protectionsIinLimitTempAmbientAdjustLabel->setVisible(false);
            ui->protectionsIinLimitTempAmbientAdjustLabel->setEnabled(false);
            ui->protectionsIinLimitTempAmbientAdjustSpinBox->setEnabled(false);
            ui->protectionsIinLimitTempAmbientAdjustSpinBox->setVisible(false);
            ui->protectionsIinLimitTempAmbientAdjustLabel->setText("");

        }

        if (theFamily == Family1500V_2nd)
        {
            ui->protectionsEFInputCurrentThresholdLabel->setVisible(true);
            ui->protectionsEFInputCurrentThresholdLabel->setEnabled(true);
            ui->protectionsEFInputCurrentThresholdSpinBox->setEnabled(true);
            ui->protectionsEFInputCurrentThresholdSpinBox->setVisible(true);

            ui->protectionsEFOccurrenceThresholdLabel->setVisible(true);
            ui->protectionsEFOccurrenceThresholdLabel->setEnabled(true);
            ui->protectionsEFOccurrenceThresholdSpinbox->setEnabled(true);
            ui->protectionsEFOccurrenceThresholdSpinbox->setVisible(true);

            ui->protectionsEFCountDownTimerLabel->setVisible(true);
            ui->protectionsEFCountDownTimerLabel->setEnabled(true);
            ui->protectionsEFCountDownTimerSpinbox->setEnabled(true);
            ui->protectionsEFCountDownTimerSpinbox->setVisible(true);

            ui->protectionsEFAlphaNumeratorLabel->setVisible(true);
            ui->protectionsEFAlphaNumeratorLabel->setEnabled(true);
            ui->protectionsEFAlphaNumeratorSpinbox->setEnabled(true);
            //ui->protectionsEFAlphaNumeratorSpinbox->setValue(setValue);
            ui->protectionsEFAlphaNumeratorSpinbox->setVisible(true);

            ui->protectionsEFModuleOffLabel->setVisible(true);
            ui->protectionsEFModuleOffLabel->setEnabled(true);
            ui->protectionsEFModuleOffSpinbox->setEnabled(false); // Always false, read only
            ui->protectionsEFModuleOffSpinbox->setVisible(true);
            // ui->protectionsEFModuleOffSpinbox->setValue(setValue);

            ui->protectionsAMF_DebugLabel->setVisible(true);
            ui->protectionsAMF_DebugLabel->setEnabled(true);
            ui->protectionsAMF_DebugSpinbox->setEnabled(true);
            ui->protectionsAMF_DebugSpinbox->setVisible(true);

            ui->protectionsEFInputCurrentThresholdLabel->setText(tFontColor + protection_1500V_EFInputCurrentThresholdStr + endFont);
            ui->protectionsEFOccurrenceThresholdLabel->setText(tFontColor + protection_1500V_EFOccurrenceThresholdStr + endFont);
            ui->protectionsEFCountDownTimerLabel->setText(tFontColor + protection_1500V_EFCountDownTimerStr + endFont);
            ui->protectionsEFAlphaNumeratorLabel->setText(tFontColor + protection_1500V_EFAlphaNumeratorStr + endFont);
            ui->protectionsEFModuleOffLabel->setText(tFontColor + protection_1500V_EFModuleOffStr + endFont);
            ui->protectionsAMF_DebugLabel->setText(tFontColor + protection_Debug_Monitoring_Str + endFont);
        }
        else
        {
            ui->protectionsEFInputCurrentThresholdLabel->setVisible(false);
            ui->protectionsEFInputCurrentThresholdLabel->setEnabled(false);
            ui->protectionsEFInputCurrentThresholdSpinBox->setEnabled(false);
            ui->protectionsEFInputCurrentThresholdSpinBox->setVisible(false);

            ui->protectionsEFOccurrenceThresholdLabel->setVisible(false);
            ui->protectionsEFOccurrenceThresholdLabel->setEnabled(false);
            ui->protectionsEFOccurrenceThresholdSpinbox->setEnabled(false);
            ui->protectionsEFOccurrenceThresholdSpinbox->setVisible(false);

            ui->protectionsEFCountDownTimerLabel->setVisible(false);
            ui->protectionsEFCountDownTimerLabel->setEnabled(false);
            ui->protectionsEFCountDownTimerSpinbox->setEnabled(false);
            ui->protectionsEFCountDownTimerSpinbox->setVisible(false);

            ui->protectionsEFAlphaNumeratorLabel->setVisible(false);
            ui->protectionsEFAlphaNumeratorLabel->setEnabled(false);
            ui->protectionsEFAlphaNumeratorSpinbox->setEnabled(false);
            ui->protectionsEFAlphaNumeratorSpinbox->setVisible(false);

            ui->protectionsEFModuleOffLabel->setVisible(false);
            ui->protectionsEFModuleOffLabel->setEnabled(false);
            ui->protectionsEFModuleOffSpinbox->setEnabled(false); // Always false, read only
            ui->protectionsEFModuleOffSpinbox->setVisible(false);

            ui->protectionsEFInputCurrentThresholdLabel->setText("");
            ui->protectionsEFOccurrenceThresholdLabel->setText("");
            ui->protectionsEFCountDownTimerLabel->setText("");
            ui->protectionsEFAlphaNumeratorLabel->setText("");
            ui->protectionsEFModuleOffLabel->setText("");
            // ui->protectionsAMF_DebugLabel->setText("");
        }
        m_protectionsChangesTracked->setIgnoreSignals(false);
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        ErrorStr += " ERROR: " + CurrentDateTime + " reset code for family " + theFamily + " not yet implemented.";
        qDebug() << ErrorStr;
        publishError(ErrorStr);
    }

}
void AmptGUI_X::handleEndDeviceParametersSavedToFile(const QString pbSaveToFile)
{
    // if mac and should pop up pb window, do so
    if (ui->commandRadioButtonMAC->isChecked() && ui->configurationMACParameterBlockPopUpCheckBox->isChecked())
    {
        // qDebug() << Q_FUNC_INFO << " Would pop up PB window for MAC " << m_currentActiveMAC <<
                    //" using file " << pbSaveToFile;
        QFile pbFile(pbSaveToFile);
        if (pbFile.open(QFile::ReadOnly | QFile::Text))
        {
           QTextStream in(&pbFile);
           QString pbStr = in.readAll();
           QMessageBox *txt = new QMessageBox;

           txt->setText(pbStr);
           //txt->setReadOnly(true);
           txt->setMinimumWidth(920);
           txt->setMinimumHeight(600);
           txt->setWindowState(Qt::WindowActive);
           txt->setWindowFlags(Qt::Window |  Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint |  Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
           txt->setWindowTitle(pbSaveToFile);
           txt->show();

        }

        // Have access to all pb data for active MAC (flash/mem, 8K/Main, ...)
        // Show data
    }
}
   void AmptGUI_X::handleEndDeviceKeySettings(const QString &mac, const QString & keyInfo)
   {
       // qDebug() << Q_FUNC_INFO << " received keyInfo for mac: " << mac << " keyInfo: " << keyInfo;
       if (mac == m_currentActiveMAC)
       {
           QStringList keyInfoElements = keyInfo.split(",");
           if (keyInfoElements.size() != 2)
           {
               QString ErrorStr(Q_FUNC_INFO);
               QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
               ErrorStr += " Error: " + CurrentDateTime + " number of expected keyInfo(1) not received: " + QString::number(keyInfoElements.size());
               qDebug() << Q_FUNC_INFO << ErrorStr;
               emit publishError(ErrorStr);
           }
           else
           {
               ui->keysEDPrivateKeyAndIVLabel ->setEnabled(true);

               ui->keysEDPrivateKeyLineEdit->setEnabled(true);
               // qDebug() << Q_FUNC_INFO << " HHHHHEEEEEHHHHEEEE ::::" << keyInfoElements.at(0);
               ui->keysEDPrivateKeyLineEdit->setText(keyInfoElements.at(0));
               ui->keysEDPrivateIVLineEdit->setEnabled(true);
               ui->keysEDPrivateIVLineEdit->setText(keyInfoElements.at(1));
           }
       }
   }

   void AmptGUI_X::handleEndDevicePowerCntrlSettings(const QString & mac, const QString & powerCntrl)
    {
        qDebug() << Q_FUNC_INFO << " received powerCntrl for mac: " << mac << " powerCntrl " << powerCntrl;

        if (mac == m_currentActiveMAC)
        {
            QStringList cntrlVoltElements = powerCntrl.split(",");
            if (cntrlVoltElements.size() != 12)
            {
                QString ErrorStr(Q_FUNC_INFO);
                QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                ErrorStr += " Error: " + CurrentDateTime + " number of expected powerCntrl(12) not received:" + QString::number(cntrlVoltElements.size());

                qDebug() << Q_FUNC_INFO << ErrorStr;
                emit publishError(ErrorStr);

                for (int i = 0; i < cntrlVoltElements.size(); i++)
                {
                    qDebug() << Q_FUNC_INFO << cntrlVoltElements.at(i);
                }

                //LBC need to do same thing as "outer else case", so write private function?
                // LBC would include setIgnoreSignals ...
            }
            else
            {

                for (int i = 0; i < cntrlVoltElements.size(); i++)
                {
                    qDebug() << Q_FUNC_INFO << cntrlVoltElements.at(i);
                }

                m_powerCntrlChangesTracked->setIgnoreSignals(true);

                ui->powerCntrlVinStopRadioSpinBox->setEnabled(true);
                ui->powerCntrlVinStopRadioSpinBox->setValue((cntrlVoltElements.at(0)).toInt());
                ui->powerCntrlVinStopRadioLabel->setEnabled(true);
                ui->powerCntrlVinStopRadioLabel->setText(blackFont + powerCntrlVinStopRadioStr + endFont );

                ui->powerCntrlOVSpinBox->setEnabled(true);
                ui->powerCntrlOVSpinBox->setValue((cntrlVoltElements.at(1)).toInt());
                ui->powerCntrlOVLabel->setEnabled(true);
                ui->powerCntrlOVLabel->setText(blackFont + powerCntrlOVStr + endFont );

                ui->powerCntrlOCSpinBox->setEnabled(true);
                ui->powerCntrlOCSpinBox->setValue((cntrlVoltElements.at(2)).toInt());
                ui->powerCntrlOCLabel->setEnabled(true);
                ui->powerCntrlOCLabel->setText(blackFont + powerCntrlOCStr + endFont );

                ui->powerCntrlOVStartupSpinBox->setEnabled(true);
                ui->powerCntrlOVStartupSpinBox->setValue((cntrlVoltElements.at(3)).toInt());
                ui->powerCntrlOVStartupLabel->setEnabled(true);
                ui->powerCntrlOVStartupLabel->setText(blackFont + powerCntrlOVStartupStr + endFont );

                ui->powerCntrlOCStepSpinBox->setEnabled(true);
                ui->powerCntrlOCStepSpinBox->setValue((cntrlVoltElements.at(4)).toInt());
                ui->powerCntrlOCStepLabel->setEnabled(true);
                ui->powerCntrlOCStepLabel->setText(blackFont + powerCntrlOCStepStr + endFont );

                QString tFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

                if ((tFamily == Family600V) || (tFamily == Family1000V) || (tFamily == Family1500V) || (tFamily == Family1500V_30))
                {
                    ui->powerCntrlCurrentNoiseSpinBox->setEnabled(true);
                    ui->powerCntrlCurrentNoiseSpinBox->setValue((cntrlVoltElements.at(5)).toInt());
                    ui->powerCntrlCurrentNoiseLabel->setEnabled(true);
                    ui->powerCntrlCurrentNoiseLabel->setText(blackFont + powerCntrlCurrentNoiseStr + endFont );
                }
                else
                {
                    ui->powerCntrlCurrentNoiseSpinBox->setEnabled(false);
                    ui->powerCntrlCurrentNoiseSpinBox->setValue((cntrlVoltElements.at(5)).toInt());
                    ui->powerCntrlCurrentNoiseLabel->setEnabled(false);
                    ui->powerCntrlCurrentNoiseLabel->setText(greyFont + powerCntrlCurrentNoiseStr + endFont );
                }

                ui->powerCntrlOVStepSpinBox->setEnabled(true);
                ui->powerCntrlOVStepSpinBox->setValue((cntrlVoltElements.at(6)).toInt());
                ui->powerCntrlOVStepLabel->setEnabled(true);
                ui->powerCntrlOVStepLabel->setText(blackFont + powerCntrlOVStepStr + endFont );

                ui->powerCntrlVinLimit255SpinBox->setEnabled(true);
                ui->powerCntrlVinLimit255SpinBox->setValue((cntrlVoltElements.at(7)).toInt());
                ui->powerCntrlVinLimit255Label->setEnabled(true);
                ui->powerCntrlVinLimit255Label->setText(blackFont + powerCntrlVinLimit255Str + endFont );

                ui->powerCntrlVinTurnOnSpinBox->setEnabled(true);
                ui->powerCntrlVinTurnOnSpinBox->setValue((cntrlVoltElements.at(8)).toInt());
                ui->powerCntrlVinTurnOnLabel->setEnabled(true);
                ui->powerCntrlVinTurnOnLabel->setText(blackFont + powerCntrlVinTurnOnStr + endFont );

                ui->powerCntrlModuleComboBox->setEnabled(true);
                ui->powerCntrlModuleComboBox->setCurrentIndex((cntrlVoltElements.at(10)).toInt());
                ui->powerCntrlModuleLabel->setEnabled(true);
                ui->powerCntrlModuleLabel->setText(blackFont + powerCntrlModuleStr + endFont );

                ui->powerCntrlMPPComboBox->setEnabled(true);
                ui->powerCntrlMPPComboBox->setCurrentIndex((cntrlVoltElements.at(11)).toInt());
                ui->powerCntrlMPPLabel->setEnabled(true);
                ui->powerCntrlMPPLabel->setText(blackFont + powerCntrlMPPStr + endFont );

                ui->powerCntrlSendPushButton->setEnabled(false);
                ui->powerCntrlSavePushButton->setEnabled(false);
                ui->powerCntrlSaveAllPushButton->setEnabled(false);
                saveAllParameters = false;

                m_powerCntrlChangesTracked->setIgnoreSignals(false);
            }
        }
        else
        {
            ui->powerCntrlVinStopRadioSpinBox->setEnabled(false);
            ui->powerCntrlOVSpinBox->setEnabled(false);
            ui->powerCntrlOCSpinBox->setEnabled(false);
            ui->powerCntrlOVStartupSpinBox->setEnabled(false);
            ui->powerCntrlOCStepSpinBox->setEnabled(false);
            ui->powerCntrlCurrentNoiseSpinBox->setEnabled(false);
            ui->powerCntrlOVStepSpinBox->setEnabled(false);
            ui->powerCntrlVinLimit255SpinBox->setEnabled(false);
            ui->powerCntrlVinTurnOnLabel->setEnabled(false);
            ui->powerCntrlSendPushButton->setEnabled(false);
            ui->powerCntrlSavePushButton->setEnabled(false);
            ui->powerCntrlSaveAllPushButton->setEnabled(false);
            m_powerCntrlChangesTracked->setIgnoreSignals(true);
        }
        qDebug() << Q_FUNC_INFO << " Exiting ...";
    }

    void AmptGUI_X::handleEndDeviceTempCntrlSettings(const QString & mac, const QString & tempCntrls)
    {
        // qDebug() << Q_FUNC_INFO << " received tempCntrls for mac: " << mac << " tempCntrls " << tempCntrls;

        if (mac == m_currentActiveMAC)
        {
            m_tempCntrlValueChangesTracked->setIgnoreSignals(true);
            QStringList tempCntrlElements = tempCntrls.split(",");
            if (tempCntrlElements.size() != 5)
            {
                QString ErrorStr(Q_FUNC_INFO);
                QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                ErrorStr += " Error: " + CurrentDateTime + " number of expected tempCntrl(5) not received:" + QString::number(tempCntrlElements.size());

                qDebug() << Q_FUNC_INFO << ErrorStr;
                emit publishError(ErrorStr);
            }
            else
            {
                /*
                for (int i = 0; i < tempCntrlElements.size(); i++)
                {
                    qDebug() << Q_FUNC_INFO << tempCntrlElements.at(i);
                }
                */

                ui->tempCntrlTSuperHotLabel->setText(blackFont + tempCntrlTSuperHotStr + endFont);
                ui->tempCntrlTSuperHotSpinBox->setEnabled(true);
                ui->tempCntrlTSuperHotSpinBox->setValue((tempCntrlElements.at(0)).toInt());

                ui->tempCntrlTHotLabel->setText(blackFont + tempCntrlTHotStr + endFont);
                ui->tempCntrlTHotSpinBox->setEnabled(true);
                ui->tempCntrlTHotSpinBox->setValue((tempCntrlElements.at(1)).toInt());

                ui->tempCntrlTColdLabel->setText(blackFont + tempCntrlTColdStr + endFont);
                ui->tempCntrlTColdSpinBox->setEnabled(true);
                ui->tempCntrlTColdSpinBox->setValue((tempCntrlElements.at(2)).toInt());

                ui->tempCntrlFallbackTimeLabel->setText(blackFont + tempCntrlFallbackTimeStr + endFont );
                ui->tempCntrlFallbackTimeSpinBox->setEnabled(true);
                ui->tempCntrlFallbackTimeSpinBox->setValue((tempCntrlElements.at(3)).toInt());

                ui->tempCntrlOCProtectionLabel->setText(blackFont + tempCntrlOCProtectionStr + endFont);
                ui->tempCntrlOCProtectionSpinBox->setEnabled(true);
                ui->tempCntrlOCProtectionSpinBox->setValue((tempCntrlElements.at(4)).toInt());

                m_tempCntrlValueChangesTracked->setIgnoreSignals(false);
            }
        }
        else
        {
            handleResetTempCntrl();
        }
    }
    void AmptGUI_X::handleEndDeviceFineTuningSettings(const QString & mac, const QString & fineTuning)
    {
            // qDebug() << Q_FUNC_INFO << " received fineTuning for mac: " << mac << " fineTuning " << fineTuning;

            if (mac == m_currentActiveMAC)
            {
                m_fineTuningValueChangesTracked->setIgnoreSignals(true);

                QStringList fineTuningElements = fineTuning.split(",");
                if (fineTuningElements.size() != 6)
                {
                    QString ErrorStr(Q_FUNC_INFO);
                    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                    ErrorStr += " Error: " + CurrentDateTime + " number of expected fineTuning(6) not received:" + QString::number(fineTuningElements.size());

                    qDebug() << Q_FUNC_INFO << ErrorStr;
                    emit publishError(ErrorStr);
                }
                else
                {
                    /*
                    for (int i = 0; i < fineTuningElements.size(); i++)
                    {
                        qDebug() << Q_FUNC_INFO << fineTuningElements.at(i);
                    }
                    */
                    ui->fineTuningVRef0Label->setText(blackFont + fineTuningVRef0Str + endFont);
                    ui->fineTuningVRef0DoubleSpinBox->setEnabled(true);
                    ui->fineTuningVRef0DoubleSpinBox->setValue((fineTuningElements.at(0)).toDouble());

                    ui->fineTuningKVRefLabel->setText(blackFont + fineTuningKVRefStr + endFont);
                    ui->fineTuningKVRefDoubleSpinBox->setEnabled(true);
                    ui->fineTuningKVRefDoubleSpinBox->setValue((fineTuningElements.at(1)).toDouble());

                    ui->fineTuningT0Label->setText(blackFont + fineTuningT0Str +endFont);
                    ui->fineTuningT0DoubleSpinBox->setEnabled(true);
                    ui->fineTuningT0DoubleSpinBox->setValue((fineTuningElements.at(2)).toDouble());

                    ui->fineTuningTempCoeffCurrentLabel->setText(blackFont + fineTuningTempCoeffCurrentStr + endFont);
                    ui->fineTuningTempCoeffCurrentDoubleSpingBox->setEnabled(true);
                    ui->fineTuningTempCoeffCurrentDoubleSpingBox->setValue((fineTuningElements.at(3)).toDouble());

                    ui->fineTuningTempCoeffPowerLabel->setText(blackFont + fineTuningTempCoeffPowerStr + endFont);
                    ui->fineTuningTempCoeffPowerDoubleSpinBox->setEnabled(true);
                    ui->fineTuningTempCoeffPowerDoubleSpinBox->setValue((fineTuningElements.at(4)).toDouble());

                    ui->fineTuningShortCircuitLevelLabel->setText(blackFont + fineTuningShortCircuitLevelStr + endFont);
                    ui->fineTuningShortCircuitLevelSpinBox->setEnabled(true);
                    ui->fineTuningShortCircuitLevelSpinBox->setValue((fineTuningElements.at(5)).toInt());

                    m_fineTuningValueChangesTracked->setIgnoreSignals(false);
                }
            }
            else
            {
                handleResetFineTuning();
            }

    }

void AmptGUI_X::handleEndDeviceRadioSettings(const QString & mac, const QString & family, const QString & radio)
{
 // qDebug() << Q_FUNC_INFO << " received radio for mac: " << mac << " fineTuning " << radio;
 QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
 bool goodToGo = true;
 QStringList radioElements = radio.split(",");

 if (mac == m_currentActiveMAC)
 {
     int expectedNumberOfArguments = 5;

     if ((family == Family1300V) || (family == Family1500V) || (family == Family1500V_30))
     {
         expectedNumberOfArguments = 6;

         if (radioElements.size() != expectedNumberOfArguments)
         {
             QString ErrorStr(Q_FUNC_INFO);
             ErrorStr += " Error: " + CurrentDateTime + " number of expected radio(" + QString::number(expectedNumberOfArguments) + ") not received:" + QString::number(radioElements.size()) + " for family " + family;

             qDebug() << Q_FUNC_INFO << ErrorStr;
             emit publishError(ErrorStr);
             goodToGo = false;
         }
     }
     else if (family == Family600V_V2)
     {
         if ((radioElements.size() > 6) || (radioElements.size() < 5))
         {
             {
                 QString ErrorStr(Q_FUNC_INFO);
                 ErrorStr += " Error: " + CurrentDateTime + " number of expected radio( 5 or 6 ) not received:" + QString::number(radioElements.size()) + " for family " + family;

                 qDebug() << Q_FUNC_INFO << ErrorStr;
                 emit publishError(ErrorStr);
                 goodToGo = false;
             }
         }
     }

     if (goodToGo == true)
     {

         /*
         for (int i = 0; i < radioElements.size(); i++)
         {
             qDebug() << Q_FUNC_INFO << radioElements.at(i);
         }
         */


         m_radioValueChangesTracked->setIgnoreSignals(true);

         ui->radioDFK0DoubleSpinBox->setEnabled(true);
         ui->radioDFK0DoubleSpinBox->setValue((radioElements.at(0)).toDouble());
         ui->radioDFK0Label->setText(blackFont + radioDFK0Str + endFont);

         ui->radioDFK1DoubleSpinBox->setEnabled(true);
         ui->radioDFK1DoubleSpinBox->setValue((radioElements.at(1)).toDouble());
         ui->radioDFK1Label->setText(blackFont + radioDFK1Str + endFont);

         ui->radioDFK2DoubleSpinBox->setEnabled(true);
         ui->radioDFK2DoubleSpinBox->setValue((radioElements.at(2)).toDouble());
         ui->radioDFK2Label->setText(blackFont + radioDFK2Str + endFont);

         ui->radioDFK3DoubleSpinBox->setEnabled(true);
         ui->radioDFK3DoubleSpinBox->setValue((radioElements.at(3)).toDouble());
         ui->radioDFK3Label->setText(blackFont + radioDFK3Str + endFont);

         ui->radioPureOffsetSpinBox->setEnabled(true);
         ui->radioPureOffsetSpinBox->setValue((radioElements.at(4)).toInt());
         ui->radioPureOffsetLabel->setText(blackFont + radioPureOffsetStr + endFont);

         if (family == Family1300V)
         {
             ui->radioLowCurrentLimitTo255SpinBox->setEnabled(true);
             ui->radioLowCurrentLimitTo255SpinBox->setValue((radioElements.at(5)).toInt());
             ui->radioLowCurrentLimitTo255Label->setText(blackFont + radioLowCurrentLimitTo255Str + endFont);
             ui->radioVin2To255ValueLabel->setText("1335V");
             ui->radioVin2From255ValueLabel->setText("1260V");
         }
         else if ((family == Family1500V) || (family == Family1500V_30))
         {
             ui->radioLowCurrentLimitTo255SpinBox->setEnabled(true);
             ui->radioLowCurrentLimitTo255SpinBox->setValue((radioElements.at(5)).toInt());
             ui->radioLowCurrentLimitTo255Label->setText(blackFont + radioLowCurrentLimitTo255Str + endFont);
             ui->radioVin2To255ValueLabel->setText("1500V");
             ui->radioVin2From255ValueLabel->setText("1440V");
         }
         else if ((family == Family600V_V2) && (radioElements.size() == 6))
         {
             ui->radioLowCurrentLimitTo255SpinBox->setEnabled(true);
             ui->radioLowCurrentLimitTo255SpinBox->setValue((radioElements.at(5)).toInt());
             ui->radioLowCurrentLimitTo255Label->setText(blackFont + radioLowCurrentLimitTo255Str + endFont);
             ui->radioVin2To255ValueLabel->setText("650V");
             ui->radioVin2From255ValueLabel->setText("620V");
         }
         else
         {
             QString ErrorStr(Q_FUNC_INFO);
             ErrorStr += "ERROR: " + CurrentDateTime + " mac:" + m_currentActiveMAC + " is missing the Iin1 to and from 255 channel levels, family " + family;
             emit publishError(ErrorStr);
             qDebug() << ErrorStr;
         }

         m_radioValueChangesTracked->setIgnoreSignals(false);
     }
 }
 else
 {
     handleResetRadio();
 }
}

     void AmptGUI_X::handleNewMACDiscovered(const QString &mac)
     {
         // qDebug() << Q_FUNC_INFO << " mac:" << mac;

         if (ui->parametersAutoReadCheckBox->isChecked())
         {
             // build command to read mac's parameter block from flash and send to gateway
             QString macCommand = ("s m");
             macCommand += mac + " 57 b1\r\n";
             qDebug() << Q_FUNC_INFO << " sending command " << macCommand << " to gateway (AutoRead).";
             m_gatewayThread.commandToSend(macCommand);
         }
     }

     void AmptGUI_X::handleConfigurationSave(const bool s)
     {
         qDebug() << Q_FUNC_INFO << " Entering ... arg is " << s;
         if ((s == true) || (s == false))
         {
             QString configurationData(RequireStructureFile);
             qDebug() << Q_FUNC_INFO << " request to save configuration from button.";
             if (ui->configurationRequireStructureFileCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + IncludeCommandsInLogs;
             if (ui->outputIncludeCommandsInLogCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }
             configurationData += "\n" + SaveParameterBlockData;
             if (ui->configurationSaveParameterBlockCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                configurationData += "0";
             }
             configurationData += "\n" + OutputLongFormatOTAData;
             if (ui->outputOutputLongFormatOTADataCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + SuperCycleInOutput;
             if (ui->outputSuperCycleInOutputCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + PerCentCommunication;
             if (ui->configurationPerCentCommunicationCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + MACParameterBlockPopUp;
             if (ui->configurationMACParameterBlockPopUpCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + SaveAmptGUI_X_Config;
             if (ui->configurationSaveAmptGUI_XCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + ReadParametersFromFlash;
             if (ui->parametersFlashCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + AutoReadParameters;
             if (ui->parametersAutoReadCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + CheckCommands;
             if (ui->confirmCommandCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                 configurationData += "0";
             }

             configurationData += "\n" + FilterOutUnitsWithOV;
             if (ui->outputFilterOutUnitsWithOVCheckBox->isChecked())
             {
                 configurationData += "2";
                 configurationData += "\n" + FilterOutUnitsWithOV;
                 configurationData += QString::number(ui->outputFilterOutUnitsWithOVSpinBox->value());
             }
             else
             {
                 configurationData += "0";
                 configurationData += "\n" + FilterOutUnitsWithOVFilter;
                 configurationData += QString::number(ui->outputFilterOutUnitsWithOVSpinBox->value());
             }

             configurationData += "\n" + FilterOutputByBunch;
             if (ui->outputFilterOutputByBunchCheckBox->isChecked())
             {
                 configurationData += "2";
                 configurationData += "\n" + FilterOutputByBunchFilter;
                 configurationData += QString::number(ui->outputFilterOutputByBunchSpinBox->value());
             }
             else
             {
                 configurationData += "0";
                 configurationData += "\n" + FilterOutputByBunchFilter;
                 configurationData += QString::number(ui->outputFilterOutputByBunchSpinBox->value());
             }

             configurationData += "\n" + FilterOutputByNetIDRange;
             if (ui->outputFilterOutputByNetIDRangeCheckBox->isChecked())
             {
                 configurationData += "2";
                 configurationData += "\n" + FilterOutputByNetIDRangeFromFilter;
                 configurationData += QString::number(ui->outputFilterOutputNetIDStartToUseSpinBox->value());
                 configurationData += "\n" + FilterOutputByNetIDRangeToFilter;
                 configurationData += QString::number(ui->outputFilterOutputNetIDEndToUseSpinBox->value());
             }
             else
             {
                 configurationData += "0";
                 configurationData += "\n" + FilterOutputByNetIDRangeFromFilter;
                 configurationData += QString::number(ui->outputFilterOutputNetIDStartToUseSpinBox->value());
                 configurationData += "\n" + FilterOutputByNetIDRangeToFilter;
                 configurationData += QString::number(ui->outputFilterOutputNetIDEndToUseSpinBox->value());
             }

             configurationData += "\n" + FilterOutUnitsWithOC;
             if (ui->outputFilterOutUnitsWithOCCheckBox->isChecked())
             {
                 configurationData += "2";
                 configurationData += "\n" + FilterOutUnitsWithOCFilter;
                 configurationData += QString::number(ui->outputFilterOutUnitsWithOCSpinBox->value());
             }
             else
             {
                 configurationData += "0";
                 configurationData += "\n" + FilterOutUnitsWithOCFilter;
                 configurationData += QString::number(ui->outputFilterOutUnitsWithOCSpinBox->value());
             }
             configurationData += "\n" + OptimerFamily;
             configurationData += ui->edSettingsOptimizerFamilyComboBox->currentText();

             configurationData += "\n" + OutputSortOTATableAscending;
             if (ui->outputSortOTATableAscendingCheckBox->isChecked())
             {
                 configurationData += "2";
             }
             else
             {
                configurationData += "0";
             }
             configurationData += "\n" + OutputSortOTATableNone;
             if (ui->outputSortOTATableRadioButtonNone->isChecked())
             {
                 configurationData += "1";
             }
             else
             {
                 configurationData += "0";
             }
             configurationData += "\n" + OutputSortOTATableSerialNumber;
             if (ui->outputSortOTATableRadioButtonSerialNumber->isChecked())
             {
                 configurationData += "1";
             }
             else
             {
                 configurationData += "0";
             }
             configurationData += "\n" + OutputSortOTATableMAC;
             if (ui->outputSortOTATableRadioButtonMAC->isChecked())
             {
                 configurationData += "1";
             }
             else
             {
                 configurationData += "0";
             }
             configurationData += "\n" + OutputSortOTATableNetwork;
             if (ui->outputSortOTATableRadioButtonNetwork->isChecked())
             {
                 configurationData += "1";
             }
             else
             {
                 configurationData += "0";
             }

             m_configurationThread.receiveConfigurationToSave(configurationData);
         }
     }

void AmptGUI_X::handleResetGateway( void )
{
     qDebug() << Q_FUNC_INFO << " INFO: attempt to reset.";
     QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
     QString infoString(Q_FUNC_INFO);

     handleResetGatewayWidgets();

     if (m_gatewayThread.isRunning() == true)
     {
         if (m_gatewayThread.isOperational())
         {
             m_gatewayThread.resetGateway();
             infoString += " INFO: " + CurrentDateTime + " gateway operational, reset issued.";
             emit publishError(infoString);
             ui->gatewayResetGatewayPushButton->setEnabled(false);
             qDebug() << infoString;
         }
         else
         {
             m_gatewayThread.resetGateway();
             infoString += " INFO: " + CurrentDateTime + " gateway not operational, reset issued.";
             emit publishError(infoString);
             qDebug() << infoString;
             ui->gatewayResetGatewayPushButton->setEnabled(false);
         }
         // m_gatewayThread.commandToSend("R\r\n");
     }
     else
     {
         infoString += " ERROR: " + CurrentDateTime + " gateway thread not running, Failed to send Reset Gateway command ... ";
         qDebug() << infoString;
         emit publishError(infoString);
     }
}

void AmptGUI_X::handleOTATableClicked(int row, int column)
{
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    // qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " got click on row:" << row << " column:" << column;
    //QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    if (row < ui->OTATableWidget->rowCount())
    {
        QString selectedMAC = ui->OTATableWidget->item(row,1)->text();
        //qDebug() << Q_FUNC_INFO << " mac on row:" << row << " is " << selectedMAC;
        // this was for debug ui->OTATableWidget->item(row, column) ->setData(Qt::BackgroundRole, QColor (255,128,128));

        if (selectedMAC.length() == 12)
        {
            int indexOfMAC = 0;
            if ((indexOfMAC = ui->commandMACComboBox->findText(selectedMAC)) != -1)
            {
                // qDebug() << Q_FUNC_INFO << " indexOfSelectedMAC:" << selectedMAC << " is " << indexOfMAC;

                /* LBC trying to see if Enter could be used to choose row of OTA table widget
                if (ui->OTATableWidget->isActiveWindow())
                {
                    qDebug() << Q_FUNC_INFO << " INFO: OTATableWidget is active window.";
                    ui->OTATableWidget->setFocus();
                }
                */
                m_OTAClickedRow = row;
                ui->commandMACComboBox->setCurrentIndex(indexOfMAC);

                // qDebug() << Q_FUNC_INFO << " <1>m_OTAClickedRow:" << m_OTAClickedRow;

                ui->ovSpinBox->setValue((ui->OTATableWidget->item(row,OVIndex)->text()).toInt());
                ui->ovSpinBox->setEnabled(true);
                ui->ovDial->setEnabled(true);

                ui->ovSendPushButton->setEnabled(false);

                ui->ocSpinBox->setValue((ui->OTATableWidget->item(row,OCIndex)->text()).toInt());
                ui->ocSpinBox->setEnabled(true);
                ui->ocDial->setEnabled(true);

                ui->ocSendPushButton->setEnabled(false);

                if (ui->OTATableWidget->item(row,ModuleIndex)->text() == "On")
                    ui->moduleComboBox->setCurrentIndex(1);
                else
                    ui->moduleComboBox->setCurrentIndex(zero);
                ui->moduleComboBox->setEnabled(true);
                ui->moduleDial->setEnabled(true);


                ui->moduleSendPushButton->setEnabled(false);

                if (ui->OTATableWidget->item(row,MPPIndex)->text() == "On")
                    ui->mppComboBox->setCurrentIndex(1);
                else
                    ui->mppComboBox->setCurrentIndex(zero);
                ui->mppComboBox->setEnabled(true);
                ui->mppDial->setEnabled(true);

                ui->mppSendPushButton->setEnabled(false);

                //ui->channelSpinBox->setValue((ui->OTATableWidget->item(row,ChannelIndex)->text()).toInt()); LBC

            }
            else
            {
                QString ErrorStr(Q_FUNC_INFO);
                ErrorStr += "ERROR: " + CurrentDateTime + " mac:" + selectedMAC + " from OTATable row:" + QString::number(row) + " column:" + QString::number(column) + " not found in commandMACComboBox.";
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
            }
            // Change active MAC in PullDown and if MAC command type selected, in commandLineEdit
        }
        else
        {
            QString ErrorStr(Q_FUNC_INFO);
            ErrorStr += "ERROR: " + CurrentDateTime + " received invalid mac:" + selectedMAC + " from row:" + QString::number(row) + " column:" + QString::number(column);
            emit publishError(ErrorStr);
            qDebug() << ErrorStr;
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " received row index:" + QString::number(row) + " out of range";
        emit publishError(ErrorStr);
        qDebug() << ErrorStr;
    }
}

void AmptGUI_X::handleSaveSmallF( void )
{
    qDebug() << Q_FUNC_INFO << " received ...";
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    m_edCommsChangesTracked->setIgnoreSignals(true);
    m_edSettingsChangesTracked->setIgnoreSignals(true);
    m_powerCntrlChangesTracked->setIgnoreSignals(true);
    m_linearCoeffsChangesTracked->setIgnoreSignals(true);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(true);
    m_fineTuningValueChangesTracked->setIgnoreSignals(true);
    m_radioValueChangesTracked->setIgnoreSignals(true);
    m_protectionsChangesTracked->setIgnoreSignals(true);

    // OK, see what type of save (mac, broadcast, group, network) to do.
    if (ui->commandRadioButtonMAC->isChecked())
    {
        qDebug() << Q_FUNC_INFO << " set up small f MAC save.";
        if (m_currentActiveMAC.length() == 12)
        {
            QString saveCommandToSend("f m");
            saveCommandToSend += m_currentActiveMAC;
            qDebug() << Q_FUNC_INFO << " will send " << saveCommandToSend << " to gateway.";
            m_gatewayThread.commandToSend(saveCommandToSend);
            handleResetPowerCntrlWidgets();
            m_powerCntrlChangesTracked->resetAllTrackedValues(true);

            handleResetFineTuning();
            m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

            handleResetRadio();
            m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

            handleResetLinearCoeffs();
            m_linearCoeffsChangesTracked->resetAllTrackedValues();

            handleResetTempCntrl();
            m_tempCntrlValueChangesTracked->resetAllTrackedValues(true);

            handleResetEDComms();
            m_edCommsChangesTracked->resetAllTrackedValues();

            handleResetEDSettings();
            m_edSettingsChangesTracked->resetAllTrackedValues(true);

            handleResetProtections();
            m_protectionsChangesTracked->resetAllTrackedValues(true);

            handleResetAllTabTitles();
        }
        else
        {
            QString ErrorStr(Q_FUNC_INFO);

            ErrorStr += " ERROR: " + CurrentDateTime + " cannot send small f mac save command, currentActiveMAC length is " + QString::number( m_currentActiveMAC.length() );
            emit publishError(ErrorStr);
            qDebug() << ErrorStr;
        }
    }
    else if (ui->commandRadioButtonBroadcast->isChecked())
    {
        QString saveCommandToSend("f *");
        qDebug() << Q_FUNC_INFO << " will send " << saveCommandToSend << " to gateway.";
        m_gatewayThread.commandToSend(saveCommandToSend);

        handleResetPowerCntrlWidgets();
        m_powerCntrlChangesTracked->resetAllTrackedValues(true);

        handleResetFineTuning();
        m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

        handleResetRadio();
        m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

        handleResetLinearCoeffs();
        m_linearCoeffsChangesTracked->resetAllTrackedValues();

        handleResetTempCntrl();
        m_tempCntrlValueChangesTracked->resetAllTrackedValues(true);

        handleResetEDComms();
        m_edCommsChangesTracked->resetAllTrackedValues();

        handleResetEDSettings();
        m_edSettingsChangesTracked->resetAllTrackedValues(true);

        handleResetProtections();
        m_protectionsChangesTracked->resetAllTrackedValues(true);

        handleResetAllTabTitles();
    }
    else if (ui->commandRadioButtonGroup->isChecked())
    {
        QString ErrorStr(Q_FUNC_INFO);

        ErrorStr += " ERROR: " + CurrentDateTime + " cannot send small f mac save command, GROUP save not implemented yet.";
        emit publishError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else if (ui->commandRadioButtonNetwork->isChecked())
    {
        QString ErrorStr(Q_FUNC_INFO);

        ErrorStr += " ERROR: " + CurrentDateTime + " cannot send small f mac save command, NETWORK save not implemented yet.";
        emit publishError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " received small f save command when Gateway command button is set.";
        emit publishError(ErrorStr);
        qDebug() << ErrorStr;
    }

    m_edCommsChangesTracked->setIgnoreSignals(false);
    m_edSettingsChangesTracked->setIgnoreSignals(false);
    m_powerCntrlChangesTracked->setIgnoreSignals(false);
    m_linearCoeffsChangesTracked->setIgnoreSignals(false);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(false);
    m_fineTuningValueChangesTracked->setIgnoreSignals(false);
    m_radioValueChangesTracked->setIgnoreSignals(false);
    m_protectionsChangesTracked->setIgnoreSignals(false);
}

void AmptGUI_X::handleSaveBigF( void )
{
    qDebug() << Q_FUNC_INFO << " received ...";
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    // OK, see what type of save (mac, broadcast, group, network) to do.

    m_edCommsChangesTracked->setIgnoreSignals(true);
    m_edSettingsChangesTracked->setIgnoreSignals(true);
    m_powerCntrlChangesTracked->setIgnoreSignals(true);
    m_linearCoeffsChangesTracked->setIgnoreSignals(true);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(true);
    m_fineTuningValueChangesTracked->setIgnoreSignals(true);
    m_radioValueChangesTracked->setIgnoreSignals(true);
    m_protectionsChangesTracked->setIgnoreSignals(true);

    if (ui->commandRadioButtonMAC->isChecked())
    {
        qDebug() << Q_FUNC_INFO << " set up big F MAC save.";
        if (m_currentActiveMAC.length() == 12)
        {
            QString saveCommandToSend("F m");
            saveCommandToSend += m_currentActiveMAC;
            qDebug() << Q_FUNC_INFO << " will send " << saveCommandToSend << " to gateway.";
            m_gatewayThread.commandToSend(saveCommandToSend);
            handleResetPowerCntrlWidgets();
            m_powerCntrlChangesTracked->resetAllTrackedValues(true);

            handleResetFineTuning();
            m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

            handleResetRadio();
            m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

            handleResetLinearCoeffs();
            m_linearCoeffsChangesTracked->resetAllTrackedValues();

            handleResetTempCntrl();
            m_tempCntrlValueChangesTracked->resetAllTrackedValues(true);

            handleResetEDComms();
            m_edCommsChangesTracked->resetAllTrackedValues();

            handleResetEDSettings();
            m_edSettingsChangesTracked->resetAllTrackedValues(true);

            handleResetProtections();
            m_protectionsChangesTracked->resetAllTrackedValues(true);
            handleResetAllTabTitles();
        }
        else
        {
            QString ErrorStr(Q_FUNC_INFO);
            ErrorStr += " ERROR: " + CurrentDateTime + " cannot send Big F mac save command, currentActiveMAC length is " + QString::number( m_currentActiveMAC.length() );
            emit publishError(ErrorStr);
            qDebug() << ErrorStr;
        }
    }
    else if (ui->commandRadioButtonBroadcast->isChecked())
    {
        QString saveCommandToSend("F *");
        qDebug() << Q_FUNC_INFO << " will send " << saveCommandToSend << " to gateway.";
        m_gatewayThread.commandToSend(saveCommandToSend);
        handleResetPowerCntrlWidgets();
        m_powerCntrlChangesTracked->resetAllTrackedValues(true);

        handleResetFineTuning();
        m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

        handleResetRadio();
        m_fineTuningValueChangesTracked->resetAllTrackedValues(true);

        handleResetLinearCoeffs();
        m_linearCoeffsChangesTracked->resetAllTrackedValues();

        handleResetTempCntrl();
        m_tempCntrlValueChangesTracked->resetAllTrackedValues(true);

        handleResetEDComms();
        m_edCommsChangesTracked->resetAllTrackedValues();

        handleResetEDSettings();
        m_edSettingsChangesTracked->resetAllTrackedValues(true);

        handleResetProtections();
        m_protectionsChangesTracked->resetAllTrackedValues(true);

        handleResetAllTabTitles();
    }
    else if (ui->commandRadioButtonGroup->isChecked())
    {
        QString ErrorStr(Q_FUNC_INFO);

        ErrorStr += " ERROR: " + CurrentDateTime + " cannot send small f mac save command, GROUP save not implemented yet.";
        emit publishError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else if (ui->commandRadioButtonNetwork->isChecked())
    {
        QString ErrorStr(Q_FUNC_INFO);

        ErrorStr += " ERROR: " + CurrentDateTime + " cannot send small f mac save command, NETWORK save not implemented yet.";
        emit publishError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " received Big F save command when Gateway command button is set.";
        emit publishError(ErrorStr);
        qDebug() << ErrorStr;
    }

    m_edCommsChangesTracked->setIgnoreSignals(false);
    m_edSettingsChangesTracked->setIgnoreSignals(false);
    m_powerCntrlChangesTracked->setIgnoreSignals(false);
    m_linearCoeffsChangesTracked->setIgnoreSignals(false);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(false);
    m_fineTuningValueChangesTracked->setIgnoreSignals(false);
    m_radioValueChangesTracked->setIgnoreSignals(false);
    m_protectionsChangesTracked->setIgnoreSignals(false);

}

void AmptGUI_X::handleScreenShotQuitPushButton( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: received ...";

    if (m_ScreenShot != nullptr)
    {
        delete m_ScreenShot;
        m_ScreenShot = nullptr;
    }
    ui->screenShotPushButton->setEnabled(true);
}

void AmptGUI_X::handleScreenShotPushButton( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: received ...";

    ui->screenShotPushButton->setEnabled(false);


    if (m_ScreenShot != nullptr)
    {
        delete m_ScreenShot;
        m_ScreenShot = nullptr;
    }

    m_ScreenShot = new Screenshot;
    connect(m_ScreenShot,SIGNAL(publishQuitPushButton( void )), this, SLOT(handleScreenShotQuitPushButton( void )));
    m_ScreenShot->show();
}

void AmptGUI_X::handlePublishedErrors(const QString s)
{
    qDebug() << Q_FUNC_INFO << " received info/error: " << s;
    ui->errorsPlainTextEdit->appendPlainText(s);
    ui->commandLineEdit->setEnabled(true);
    ui->commandLineEditPushButton->setEnabled(true);
}

void AmptGUI_X::handlePublishedInfo(const QString s)
{
    // qDebug() << Q_FUNC_INFO << " received info: " << s;
    ui->errorsPlainTextEdit->appendPlainText(s);
}

void AmptGUI_X::handlePublishOtherGateways(const bool s)
{
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    qDebug() << Q_FUNC_INFO << " " << CurrentDateTime << " other gateway(s):" << QString::number(s);
    if (s == true)
    {
        ui->gatewayOtherGatewaysLabel->setText("<font color='red'>Other GW(s)</font>");
    }
    else
    {
        ui->gatewayOtherGatewaysLabel->setText("<font color='black'>No Other GW(s)</font>");
    }
}

void AmptGUI_X::handleGatewayChannelValueChanged(int channel)
{
    // qDebug() << Q_FUNC_INFO << " channel:" << QString::number(channel);

    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        // int currentIndex = 0;
        m_gatewayChangesTracked->gatewayChannelValueChanged(channel);
        ui->gatewaySendPushButton->setEnabled(true);
        //ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayChannelLabel->setText(redFont + gatewayChannelStr + endFont);
        // currentIndex = ui->AllTabs->currentIndex();

        bool endDevicesAlso = ui->gatewayChangeEndDevicesAlsoCheckBox->isChecked();
        if ((endDevicesAlso == true) && (ui->edCommsChannelSpinBox->isEnabled() == true))
        {
           ui->edCommsChannelSpinBox->setValue(channel);
           qDebug() << Q_FUNC_INFO << " told edCommsChannelToChange ";
        }
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(GatewayTabIndex, Qt::red);

    }
}

void AmptGUI_X::handleGatewayGatewayAddressValueChanged(int gwAddr)
{
    // qDebug() << Q_FUNC_INFO << " gwAddr:" << QString::number(gwAddr);

    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        //int currentIndex = 0;
        m_gatewayChangesTracked->gatewayGatewayAddressValueChanged(gwAddr);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayGatewayEDAddressLabel->setText(redFont + gatewayGatewayEndDeviceAddressStr + endFont);

        bool endDevicesAlso = ui->gatewayChangeEndDevicesAlsoCheckBox->isChecked();
        if ((endDevicesAlso == true) && (ui->edCommsGatewayAddressSpinBox->isEnabled() == true))
        {
           ui->edCommsGatewayAddressSpinBox->setValue(gwAddr);
           qDebug() << Q_FUNC_INFO << " told edCommsGatewayAddress to change ";
        }

        // currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(GatewayTabIndex, Qt::red);
    }
}

void AmptGUI_X::handleGatewayEndDeviceAddressValueChanged(int edAddr)
{
    // qDebug() << Q_FUNC_INFO << " edAddr:" << QString::number(edAddr);

    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        // int currentIndex = 0;
        m_gatewayChangesTracked->gatewayEndDeviceAddressValueChanged(edAddr);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayGatewayEDAddressLabel->setText(redFont + gatewayGatewayEndDeviceAddressStr + endFont);

        bool endDevicesAlso = ui->gatewayChangeEndDevicesAlsoCheckBox->isChecked();
        if ((endDevicesAlso == true) && (ui->edCommsEndDeviceAddressSpinBox->isEnabled() == true))
        {
           ui->edCommsEndDeviceAddressSpinBox->setValue(edAddr);
           qDebug() << Q_FUNC_INFO << " told edCommsEndDeviceAddress to change ";
        }
        // currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(GatewayTabIndex, Qt::red);
    }
}

void AmptGUI_X::handleGatewayBunchSizeValueChanged(int bunchSize)
{
    // qDebug() << Q_FUNC_INFO << " bunchSize:" << QString::number(bunchSize);

    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        int currentIndex = 0;
        m_gatewayChangesTracked->gatewayBunchSizeValueChanged(bunchSize);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayBunchSizeLabel->setText(redFont + gatewayBunchSizeStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

    }

}

void AmptGUI_X::handleGatewayNetworkSizeValueChanged(int networkSize)
{
    // qDebug() << Q_FUNC_INFO << " networkSize:" << QString::number(networkSize);

    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        int currentIndex = 0;
        m_gatewayChangesTracked->gatewayNetworkSizeValueChanged(networkSize);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayNetworkSizeLabel->setText(redFont + gatewayNetworkSizeStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

    }

}


void AmptGUI_X::handleGatewayHoppingValueChanged(int hopping)
{
    // qDebug() << Q_FUNC_INFO << " hopping:" << hopping;

    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        int currentIndex = 0;
        m_gatewayChangesTracked->gatewayHoppingValueChanged(hopping);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayHoppingLabel->setText(redFont + gatewayHoppingStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
    }

}

void AmptGUI_X::handleGatewayPowerValueChanged(QString power)
{
    // qDebug() << Q_FUNC_INFO << " power index :" << power;

    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        int currentIndex = 0;
        m_gatewayChangesTracked->gatewayPowerValueChanged(power);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayPowerLabel->setText(redFont + gatewayPowerStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
    }
}

void AmptGUI_X::handleGatewaySyncwordValueChanged(int syncword)
{
    // qDebug() << Q_FUNC_INFO << " syncword:" << syncword;
    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        int currentIndex = 0;
        m_gatewayChangesTracked->gatewaySyncWordValueChanged(syncword);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewaySyncWordLabel->setText(redFont + gatewaySyncwordStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
    }
}

void AmptGUI_X::handleGatewayModeValueChanged(int mode)
{
    // qDebug() << Q_FUNC_INFO << " mode:" << mode;
    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        int currentIndex = 0;
        m_gatewayChangesTracked->gatewayModeValueChanged(mode);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayModeLabel->setText(redFont + gatewayModeStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
    }
}

void AmptGUI_X::handleGatewayRepeatCommandValueChanged(int zCount)
{
    // qDebug() << Q_FUNC_INFO << " ZCount:" << zCount;
    if (m_gatewayChangesTracked->getIgnoreGatewaySignals() == false)
    {
        int currentIndex = 0;
        m_gatewayChangesTracked->gatewayModeValueChanged(zCount);
        ui->gatewaySendPushButton->setEnabled(true);
        // ui->gatewaySavePushButton->setEnabled(true);
        ui->gatewayRepeatCommandsLabel->setText(redFont + gatewayRepeatCommandStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
    }
}

void AmptGUI_X::handleEDSettingsSyncPhaseValueChanged(int s)
{
    // qDebug() << Q_FUNC_INFO << " value:" << s;

    if (m_edSettingsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_edSettingsChangesTracked->changeSyncPhase(s);
        // qDebug() << Q_FUNC_INFO << " changed to " << s;
        ui->edSettingsSendPushButton->setEnabled(true);
        ui->edSettingsSyncPhaseLabel->setText(redFont + edSettingsSyncPhaseStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleEDSettingsSyncFrequencyValueChanged(int s)
{

    // qDebug() << Q_FUNC_INFO << " value:" << s;

    if (m_edSettingsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;

        m_edSettingsChangesTracked->changeSyncFrequency(s);
        // qDebug() << Q_FUNC_INFO << " changed to " << s;
        ui->edSettingsSendPushButton->setEnabled(true);
        ui->edSettingsSyncFrequencyLabel->setText(redFont + edSettingsSyncFrequencyStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleEDSettingsOVSetToSpinBoxChanged( int ovValue)
{
    // qDebug() << Q_FUNC_INFO << " Entering with ovValue of " << QString::number(ovValue);
    int ovToOutputVoltage = 0;
    QString ovSettingToMaxOutputVoltageStr("allows maximum output voltage of ");

    QString family = ui->edSettingsOptimizerFamilyComboBox->currentText();
    if ((family == Family1500V) || (family == Family1500V_30) || (family == Family1500V_2nd))
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((6.175 * ovValue) - 35.053);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @1250V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);
    }
    else if (family == Family1300V)
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((5.5393 * ovValue) - 6.5825);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @770V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);
    }
    else if (family == Family1000V)
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((2.6826 * ovValue) + 516.33);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @900V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);
    }
    else if ((family == Family600V_V2) || (family == Family600V_V2_2nd))
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((2.4401 * ovValue) + 6.9774);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @376V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);
    }
    else
    {
        ui->edSettingsOVSetToLabel->setEnabled(false);
        ui->edSettingsOVSetToSpinBox->setValue(0);
        ui->edSettingsOVSetToSpinBox->setEnabled(false);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText("");
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(false);
        QString errString(Q_FUNC_INFO);
        errString += " ERROR: code not implemented for optimizer family " + family + " ovValue of " + QString::number(ovValue);
        publishError(errString);
        qDebug() << errString;
    }
}

void AmptGUI_X::handleEDSettingsOCSetToSpinBoxChanged( int ocValue)
{
    // qDebug() << Q_FUNC_INFO << " Entering with ocValue of " << QString::number(ocValue);
    double ocToOutputCurrent = 0.0;
    QString ocSettingToMaxOutputCurrentStr("allows maximum output current of ");

    QString family = ui->edSettingsOptimizerFamilyComboBox->currentText();
    if ((family == Family1500V) || (family == Family1500V_30) || (family == Family1500V_2nd))
    {
        ui->edSettingsOCSetToLabel->setEnabled(true);
        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOCSetToSpinBox->setEnabled(true);
        ocToOutputCurrent = (0.0821 * ocValue) - 0.0743;
        ocSettingToMaxOutputCurrentStr += QString::number(ocToOutputCurrent) + "A (VDC @1100V)";
        ui->edSettingsOCSettingMaxCurrentOutputLabel ->setText(ocSettingToMaxOutputCurrentStr);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(true);
    }
    else if (family == Family1300V)
    {
        ui->edSettingsOCSetToLabel->setEnabled(true);
        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOCSetToSpinBox->setEnabled(true);
        ocToOutputCurrent = (0.0578 * ocValue) - 0.222;
        ocSettingToMaxOutputCurrentStr += QString::number(ocToOutputCurrent) + "A (Vin @766V)";
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setText(ocSettingToMaxOutputCurrentStr);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(true);
    }
    else if ((family == Family600V_V2) || (family == Family600V_V2_2nd))
    {
        ui->edSettingsOCSetToLabel->setEnabled(true);
        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOCSetToSpinBox->setEnabled(true);
        ocToOutputCurrent = (0.0574 * ocValue) + 0.242;
        ocSettingToMaxOutputCurrentStr += QString::number(ocToOutputCurrent) + "";
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setText(ocSettingToMaxOutputCurrentStr);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(true);
    }
    else
    {
        ui->edSettingsOCSetToLabel->setEnabled(false);
        ui->edSettingsOCSetToSpinBox->setValue(0);
        ui->edSettingsOCSetToSpinBox->setEnabled(false);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setText("");
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(false);
        QString errString(Q_FUNC_INFO);
        errString += " ERROR: code not implemented for optimizer family " + family + " ocValue of " + QString::number(ocValue);
        publishError(errString);
        qDebug() << errString;
    }
}


void AmptGUI_X::handleEDSettingsSendPushButtonReleased( void )
{
    // qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";

    if (m_currentActiveMAC != "")
    {
        bool saveButtonState = false;
        m_edSettingsChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC);

        int currentIndex = ui->AllTabs->currentIndex();
        // QString aCommand;
        QTabBar* bar=ui->AllTabs->tabBar();


        bar->setTabTextColor(currentIndex,Qt::blue);

        if (m_edSettingsChangesTracked->getSyncPhaseChanged())
        {
            ui->edSettingsSyncPhaseLabel->setText( blueFont + edSettingsSyncPhaseStr + endFont );
            saveButtonState = true;
        }
        if (m_edSettingsChangesTracked->getSyncFrequencyChanged())
        {
            ui->edSettingsSyncFrequencyLabel->setText( blueFont + edSettingsSyncFrequencyStr + endFont );
            saveButtonState = true;
        }

        ui->edSettingsSendPushButton->setEnabled(false);
        ui->edSettingsSavePushButton->setEnabled(saveButtonState);
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

        errString += " ERROR: " + CurrentDateTime + " no current active MAC";
        emit publishError(errString);
        qDebug() << errString;
    }
}

void AmptGUI_X::handleEDCommsSendPushButtonReleased( void )
{
   qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";

   if (m_currentActiveMAC != "")
   {
       int oldGWAddr = ui->edCommsGatewayAddressSpinBox->value();
       int oldEDAddr = ui->edCommsEndDeviceAddressSpinBox->value();
       int oldBunch = ui->edCommsBunchSpinBox->value();
       int oldNetID = ui->edCommsNetIDSpinBox->value();

       m_edCommsChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC, oldGWAddr, oldEDAddr, oldBunch, oldNetID);

       int currentIndex = ui->AllTabs->currentIndex();
       // QString aCommand;
       QTabBar* bar=ui->AllTabs->tabBar();
       bool saveButtonState = false;
       bool save2ButtonState = false;

       bar->setTabTextColor(currentIndex,Qt::blue);

       if (m_edCommsChangesTracked->getChannelChanged())
       {
           ui->edCommsChannelLabel->setText( blueFont + edCommsChannelStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getGatewayAddressChanged() || (m_edCommsChangesTracked->getEndDeviceAddressChanged()))
       {
           ui->edCommsGatewayEdAddressLabel->setText( blueFont + edCommsGatewayEDAddressStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getBunchChanged())
       {
           ui->edCommsBunchLabel->setText( blueFont + edCommsBunchStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getNetIDChanged())
       {
           ui->edCommsNetIDLabel->setText( blueFont + edCommsNetIDStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getGBunchChanged())
       {
           qDebug() << Q_FUNC_INFO << " YUP! " << edCommsGBunchStr;

           ui->edCommsGBunchLabel->setText( blueFont + edCommsGBunchStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getRBunchChanged())
       {
           ui->edCommsRBunchLabel->setText( blueFont + edCommsRBunchStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getHoppingChanged())
       {
           ui->edCommsHoppingAllowedLabel->setText( blueFont + edCommsHoppingStr + endFont );
           saveButtonState = true;
       }

       if (m_edCommsChangesTracked->getGWChannelFlagChanged())
       {
           ui->edCommsGatewayChannelFlagLabel->setText(blueFont + edCommsGatewayChannelFlagStr + endFont);
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getSyncWordChanged())
       {
           ui->edCommsSyncWordLabel->setText(blueFont +  edCommsSyncWordStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->get12KbodChanged())
       {
           ui->edComms12KbodLabel->setText(blueFont +  edComms12KbodStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getStayInRXChanged())
       {
           ui->edCommsStayInRXLabel->setText(blueFont +  edCommsStayInRXStr + endFont ); // No parameter to save
       }
       if (m_edCommsChangesTracked->getStayInCWChanged())
       {
           ui->edCommsStayInCWLabel->setText(blueFont +  edCommsStayInCWStr + endFont ); // No parameter to save
       }
       if (m_edCommsChangesTracked->getRadioPowerChanged())
       {
           ui->edCommsRadioPowerLabel->setText(blueFont +  edCommsRadioPowerStr + endFont );
           saveButtonState = true;
       }
       if (m_edCommsChangesTracked->getRepeaterChanged())
       {
           ui->edComms2RepeaterLabel->setText(blueFont +  edComms2RepeaterStr + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->getRepeaterPowerChanged())
       {
           ui->edComms2RepeaterPowerLabel->setText(blueFont +  edComms2RepeaterPowerStr + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->getRepeaterChannelChanged())
       {
           ui->edComms2RepeaterChannelLabel->setText(blueFont +  edComms2RepeaterChannelStr + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->getSearchEnabledChanged())
       {
           ui->edComms2SeachLabel->setText(blueFont +  edComms2SearchEnabledStr + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->getCriticalLevel10Changed())
       {
           ui->edComms2CriticalLevel10Label->setText(blueFont +  edComms2CriticalLevel10Str + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->getSlaveChanged())
       {
           ui->edComms2SlaveLabel->setText(blueFont +  edComms2SlaveStr + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->getSlaveChannelChanged())
       {
           ui->edComms2SlaveChannelLabel->setText(blueFont +  edComms2SlaveChannelStr + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->get250KbodChanged())
       {
           ui->edComms2250KbodLabel->setText(blueFont +  edComms2250KbodStr + endFont );
           save2ButtonState = true;
       }
       if (m_edCommsChangesTracked->getCriticalLevel500Changed())
       {
           ui->edComms2CriticalLevel500Label->setText(blueFont +  edComms2CriticalLevel500Str + endFont );
           save2ButtonState = true;
       }

       ui->edCommsSendPushButton->setEnabled(false);
       ui->edComms2SendPushButton->setEnabled(false);
       ui->edCommsSavePushButton->setEnabled(saveButtonState);
       ui->edComms2SavePushButton->setEnabled(save2ButtonState);
   }
   else
   {
       QString errString(Q_FUNC_INFO);
       QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
       errString += " ERROR: " + CurrentDateTime + " no current active MAC";
       emit publishError(errString);
       qDebug() << errString;
   }

}

void AmptGUI_X::handleGatewaySavePushButtonReleased( void )
{
    qDebug() << Q_FUNC_INFO << " received a save gateway request...";

    // Issue 'G' command to gateway
    QString commandToSend("G\r\n");
    m_gatewayThread.commandToSend(commandToSend);
    // Need all gateway parameters to be black
    ui->gatewayChannelLabel->setText(blackFont + gatewayChannelStr + endFont);
    ui->gatewayGatewayEDAddressLabel->setText(blackFont + gatewayGatewayEndDeviceAddressStr + endFont);
    ui->gatewayPowerLabel->setText(blackFont + gatewayPowerStr + endFont);
    ui->gatewaySyncWordLabel->setText(blackFont + gatewaySyncwordStr + endFont);
    ui->gatewayBunchSizeLabel->setText(blackFont + gatewayBunchSizeStr + endFont);
    ui->gatewayNetworkSizeLabel->setText(blackFont + gatewayNetworkSizeStr + endFont);
    ui->gatewayHoppingLabel->setText(blackFont + gatewayHoppingStr + endFont);
    ui->gatewayPowerLabel->setText(blackFont + gatewayPowerStr + endFont);
    ui->gatewayModeLabel->setText(blackFont + gatewayModeStr + endFont);
    ui->gatewayRepeatCommandsLabel->setText(blackFont + gatewayRepeatCommandStr + endFont);
    ui->gatewaySendPushButton->setEnabled(false);
    ui->gatewaySavePushButton->setEnabled(false);
    QTabBar* bar=ui->AllTabs->tabBar();
    bar->setTabTextColor(GatewayTabIndex, Qt::black);
}

void AmptGUI_X::handleGatewaySendPushButtonReleased( void )
{
    qDebug() << Q_FUNC_INFO << " Time to send changed gateway parameters to gateway ...";

    int currentIndex = 0;

    bool endDevicesAlso = ui->gatewayChangeEndDevicesAlsoCheckBox->isChecked();

    m_gatewayChangesTracked->writeAllChangedValuesToMemory(endDevicesAlso);

    currentIndex = ui->AllTabs->currentIndex();
    QTabBar* bar=ui->AllTabs->tabBar();
    bar->setTabTextColor(currentIndex,Qt::blue);


    if (m_gatewayChangesTracked->getGatewayChannelValueChanged())
    {
        ui->gatewayChannelLabel->setText(blueFont + gatewayChannelStr + endFont);
        if (endDevicesAlso)
        {
            m_edCommsChangesTracked->changeChannel(ui->gatewayChannelSpinBox->value());
            ui->edCommsChannelLabel->setText(blueFont + edCommsChannelStr + endFont);
            ui->edCommsChannelSpinBox->setValue( ui->gatewayChannelSpinBox->value() );
            bar->setTabTextColor(1,Qt::blue);
            ui->edCommsSavePushButton->setEnabled(true);
            ui->edCommsSendPushButton->setEnabled(false);

            // LBC333 Need to enable write button on ED tab.
        }
    }

    if (m_gatewayChangesTracked->getGatewayEndDeviceOrGatewayValueChanged())
    {
        ui->gatewayGatewayEDAddressLabel->setText(blueFont + gatewayGatewayEndDeviceAddressStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewayPowerValueChanged())
    {
        ui->gatewayPowerLabel->setText(blueFont + gatewayPowerStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewaySyncWordValueChanged())
    {
        ui->gatewaySyncWordLabel->setText(blueFont + gatewaySyncwordStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewayBunchSizeValueChanged())
    {
        ui->gatewayBunchSizeLabel->setText(blueFont + gatewayBunchSizeStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewayNetworkSizeValueChanged())
    {
        ui->gatewayNetworkSizeLabel->setText(blueFont + gatewayNetworkSizeStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewayHoppingValueChanged())
    {
        ui->gatewayHoppingLabel->setText(blueFont + gatewayHoppingStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewayPowerValueChanged())
    {
        ui->gatewayPowerLabel->setText(blueFont + gatewayPowerStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewayModeValueChanged())
    {
        ui->gatewayModeLabel->setText(blueFont + gatewayModeStr + endFont);
    }

    if (m_gatewayChangesTracked->getGatewayZCountValueChanged())
    {
        ui->gatewayRepeatCommandsLabel->setText(blueFont + gatewayRepeatCommandStr + endFont);
    }

    ui->gatewaySendPushButton->setEnabled(false);
    ui->gatewaySavePushButton->setEnabled(true);
}

void AmptGUI_X::handleOVValueChangeFromSpinBox(int value)
{
    // qDebug() << Q_FUNC_INFO << "value of " << value;
    if (value != ui->ovDial->value())
    {
        //qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->ovDial->setValue(value);
        ui->ovSendPushButton->setEnabled( true );
    }
}

void AmptGUI_X::handleOVValueChangeFromDial(int value)
{
    // qDebug() << Q_FUNC_INFO << "value of " << value;
    if (value != ui->ovSpinBox->value())
    {
        //qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->ovSpinBox->setValue(value);
        ui->ovSendPushButton->setEnabled( true );
    }
}

void AmptGUI_X::handleOCValueChangeFromSpinBox(int value)
{
    // qDebug() << Q_FUNC_INFO << " value of " << value;
    if (value != ui->ocDial->value())
    {
        // qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->ocDial->setValue(value);
        ui->ocSendPushButton->setEnabled( true );
    }
}

void AmptGUI_X::handleOCValueChangeFromDial(int value)
{
    // qDebug() << Q_FUNC_INFO << "value of " << value;
    if (value != ui->ocSpinBox->value())
    {
        // qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->ocSpinBox->setValue(value);
        ui->ocSendPushButton->setEnabled( true );
    }
}


void AmptGUI_X::handleMPPValueChangeFromComboBox(int value)
{
    // qDebug() << Q_FUNC_INFO << "value of " << value;
    if (value != ui->mppDial->value())
    {
        // qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->mppDial->setValue(value);
        ui->mppSendPushButton->setEnabled(true);
    }
}

void AmptGUI_X::handleMPPValueChangeFromDial(int value)
{
    // qDebug() << Q_FUNC_INFO << "value of " << value;
    if (value != ui->mppComboBox->currentIndex())
    {
        qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->mppComboBox->setCurrentIndex(value);
        ui->mppSendPushButton->setEnabled(true);
    }
}

void AmptGUI_X::handleModuleValueChangeFromComboBox(int value)
{
    // qDebug() << Q_FUNC_INFO << "value of " << value;
    if (value != ui->moduleDial->value())
    {
        //qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->moduleDial->setValue(value);
        ui->moduleSendPushButton->setEnabled( true );
    }
}

void AmptGUI_X::handleModuleValueChangeFromDial(int value)
{
    // qDebug() << Q_FUNC_INFO << "value of " << value;
    if (value != ui->moduleComboBox->currentIndex())
    {
        //qDebug() << Q_FUNC_INFO << " new value of " << value;
        ui->moduleComboBox->setCurrentIndex(value);
        ui->moduleSendPushButton->setEnabled( true );
    }
}


void AmptGUI_X::handleReadCoeffsPushButton( void )
{
   qDebug() << Q_FUNC_INFO << " INFO: got click";
   QString msgString(Q_FUNC_INFO);
   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

   if ((m_currentActiveMAC != "") && (ui->commandRadioButtonMAC->isChecked()))
   {
     ui->readCoefficientsPushButton->setEnabled(false);
     ui->parametersReadPushButton->setEnabled(false);
     ui->parametersWritePushButton->setEnabled(false);
     ui->commandLineEditPushButton->setEnabled(false);

     QString commandToSend = "s m" +  m_currentActiveMAC + ByteRegister_ReadCoefficientsSomeOffsetsDFK3AndOC + ByteRegisterCommand + "2";
     sendCommandToGateway(commandToSend);
     msgString += " INFO: " + CurrentDateTime + " command:" + commandToSend + " sent to gateway.";
     qDebug() << msgString;
   }
   else
   {
     msgString += " ERROR: " + CurrentDateTime + " unable to request coefficients";
     emit publishError(msgString);
     qDebug() << msgString;
   }
}

void AmptGUI_X::handleEndDeviceReceivedCoeffLineData( void )
{

    QString msgString(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    if ((m_currentActiveMAC != "") && (ui->commandRadioButtonMAC->isChecked()))
    {
      msgString += " INFO:" + CurrentDateTime + " current active mac:" + m_currentActiveMAC;
      ui->readCoefficientsPushButton->setEnabled(true);
      ui->parametersReadPushButton->setEnabled(true);
      ui->parametersWritePushButton->setEnabled(false);
      ui->commandLineEditPushButton->setEnabled(true);

      qDebug() << msgString;
    }
    else
    {
        msgString += " ERROR:" + CurrentDateTime + " no current active mac or commandRadioButtonMAC is not checked.";
        publishError(msgString);
        qDebug() << msgString;
    }
}

void AmptGUI_X::handleEndDeviceValidCoeffLineData(const QString macAndCoeffsData)
{
    QString msgString(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QStringList macAndData = macAndCoeffsData.split(",");

    if (macAndData.at(0) == m_currentActiveMAC)
    {
        if (macAndData.size() == 14)
        {
            msgString += " INFO: " + CurrentDateTime + " correct number and mac:" + macAndCoeffsData;
            qDebug() << msgString;
            ui->macReadCoeffsVoutCoeff->setEnabled(true);
            ui->macReadCoeffsVoutCoeff->setText(macAndData.at(1));
            ui->macReadCoeffsVin1Coeff->setEnabled(true);
            ui->macReadCoeffsVin1Coeff->setText(macAndData.at(2));
            ui->macReadCoeffsIoutCoeff->setEnabled(true);
            ui->macReadCoeffsIoutCoeff->setText(macAndData.at(3));
            ui->macReadCoeffsVin2Coeff->setEnabled(true);
            ui->macReadCoeffsVin2Coeff->setText(macAndData.at(4));
            ui->macReadCoeffsIin2Coeff->setEnabled(true);
            ui->macReadCoeffsIin2Coeff->setText(macAndData.at(5));
            ui->macReadCoeffsIin1Coeff->setEnabled(true);
            ui->macReadCoeffsIin1Coeff->setText(macAndData.at(6));
            ui->macReadCOeffsVoutOffset->setEnabled(true);
            ui->macReadCOeffsVoutOffset->setText(macAndData.at(7));
            ui->macReadCOeffsIoutOffset->setEnabled(true);
            ui->macReadCOeffsIoutOffset->setText(macAndData.at(8));
            ui->macReadCOeffsIin2Offset->setEnabled(true);
            ui->macReadCOeffsIin2Offset->setText(macAndData.at(9));
            ui->macReadCOeffsIin1Offset->setEnabled(true);
            ui->macReadCOeffsIin1Offset->setText(macAndData.at(10));
            ui->macReadCoeffsDFK3->setEnabled(true);
            ui->macReadCoeffsDFK3->setText(macAndData.at(11));
            ui->macReadCoeffsOV->setEnabled(true);
            ui->macReadCoeffsOV->setText(macAndData.at(12));
            ui->macReadCoeffsOC->setEnabled(true);
            ui->macReadCoeffsOC->setText(macAndData.at(13));
        }
        else
        {
            msgString += " ERROR: " + CurrentDateTime + " wrong number of elements in macAndCoeffsData, expected 13, got " + QString::number(macAndData.size());
            qDebug() << msgString;
            emit publishError(msgString);
        }
    }
    else
    {
        msgString += " ERROR: " + CurrentDateTime + " mac for coefficient data, " + macAndData.at(0) + " is not the current active mac, " + m_currentActiveMAC;
        qDebug() << msgString;
        emit publishError(msgString);
    }

}

void AmptGUI_X::handlePowerCntrlVinTurnOnSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeVinTurnOn(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlVinTurnOnLabel->setText(redFont + vinTurnOnStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}



void AmptGUI_X::handlePowerCntrlVinStopRadioSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeVinStopRadio(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlVinStopRadioLabel->setText(redFont + vinStopRadioStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

void AmptGUI_X::handlePowerCntrlVinLimit255SpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeVinLimit255(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlVinLimit255Label->setText(redFont + vinLimit255Str + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

void AmptGUI_X::handlePowerCntrlOVSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;
     //LBC need to remember big F versus small f

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeOV(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlOVLabel->setText(redFont + ovStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

void AmptGUI_X::handlePowerCntrlOCSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;
     // LBC need to remember big F versus small f

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeOC(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlOCLabel->setText(redFont + ocStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

void AmptGUI_X::handlePowerCntrlOVStartupSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeOVStartup(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlOVStartupLabel->setText(redFont + ovStartupStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

void AmptGUI_X::handlePowerCntrlCurrentNoiseSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeCurrentNoise(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlCurrentNoiseLabel->setText(redFont + currentNoiseStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

void AmptGUI_X::handlePowerCntrlOVStepSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;

     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeOVStep(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlOVStepLabel->setText(redFont + ovStepStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
         saveAllParameters = true;
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }

}

void AmptGUI_X::handlePowerCntrlOCStepSpinBoxChange(const int value)
{
     // qDebug() << Q_FUNC_INFO << " value:" << value;
     if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_powerCntrlChangesTracked->changeOCStep(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;
         ui->powerCntrlSendPushButton->setEnabled(true);
         //ui->gatewaySavePushButton->setEnabled(true);
         ui->powerCntrlOCStepLabel->setText(redFont + ocStepStr + endFont);
         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);
         saveAllParameters = true;
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

void AmptGUI_X::handlePowerCntrlModuleComboBoxChange(const QString & s)
{
    // qDebug() << Q_FUNC_INFO << " value:" << s;

    if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_powerCntrlChangesTracked->changeModule(s);
        // qDebug() << Q_FUNC_INFO << " changed to " << s;
        ui->powerCntrlSendPushButton->setEnabled(true);
        //ui->gatewaySavePushButton->setEnabled(true);
        ui->powerCntrlModuleLabel->setText(redFont + moduleStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        saveAllParameters = true;
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handlePowerCntrlMPPComboBoxChange(const QString & s)
{
    // qDebug() << Q_FUNC_INFO << " value:" << s;

    if (m_powerCntrlChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_powerCntrlChangesTracked->changeMPP(s);
        // qDebug() << Q_FUNC_INFO << " changed to " << s;
        ui->powerCntrlSendPushButton->setEnabled(true);
        //ui->gatewaySavePushButton->setEnabled(true);
        ui->powerCntrlMPPLabel->setText(redFont + mppStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        saveAllParameters = true;
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}


void AmptGUI_X::handleSaveAllPushButton( void )
{
    qDebug() << Q_FUNC_INFO << " mac specific, group, network, or broadcast little f command.";

    ui->powerCntrlSendPushButton->setEnabled(false);
    ui->powerCntrlSavePushButton->setEnabled(false);
    ui->powerCntrlSaveAllPushButton->setEnabled(false);

    ui->powerCntrlCurrentNoiseLabel->setText(blackFont + currentNoiseStr + endFont);
    ui->powerCntrlVinTurnOnLabel->setText(blackFont + vinTurnOnStr + endFont);
    ui->powerCntrlVinStopRadioLabel->setText(blackFont + vinStopRadioStr + endFont);
    ui->powerCntrlVinLimit255Label->setText(blackFont + vinLimit255Str + endFont);
    ui->powerCntrlOVStepLabel->setText(blackFont + ovStepStr + endFont);
    ui->powerCntrlOCStepLabel->setText(blackFont + ocStepStr + endFont);
    ui->powerCntrlOVStartupLabel->setText(blackFont + ovStartupStr + endFont);
    ui->powerCntrlOVLabel->setText(blackFont + ovStr + endFont);
    ui->powerCntrlOCLabel->setText(blackFont + ocStr + endFont);
    ui->powerCntrlModuleLabel->setText(blackFont + moduleStr + endFont);
    ui->powerCntrlMPPLabel->setText(blackFont + mppStr + endFont);


    int currentIndex = ui->AllTabs->currentIndex();
    QTabBar* bar=ui->AllTabs->tabBar();
    bar->setTabTextColor(currentIndex,Qt::black);
    saveAllParameters = false;
    m_powerCntrlChangesTracked->resetAllTrackedValues(true);
}

void AmptGUI_X::handlePowerCntrlSendPushButton( void )
{

    // qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";

    if (m_currentActiveMAC != "")
    {

        m_powerCntrlChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC);

        int currentIndex = ui->AllTabs->currentIndex();
        QString aCommand;
        QTabBar* bar=ui->AllTabs->tabBar();
        bool saveButtonState = false;
        bool saveAllButtonState = false;

        bar->setTabTextColor(currentIndex,Qt::blue);

        if (m_powerCntrlChangesTracked->getCurrentNoiseChanged())
        {
            ui->powerCntrlCurrentNoiseLabel->setText(blueFont + currentNoiseStr + endFont);
            saveButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getVinTurnOnChanged())
        {
            ui->powerCntrlVinTurnOnLabel->setText(blueFont + vinTurnOnStr + endFont);
            saveButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getVinStopRadioChanged())
        {
            ui->powerCntrlVinStopRadioLabel->setText(blueFont + vinStopRadioStr + endFont);
            saveButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getVinLimit255Changed())
        {
            ui->powerCntrlVinLimit255Label->setText(blueFont + vinLimit255Str + endFont);
            saveButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getOVStepChanged())
        {
            ui->powerCntrlOVStepLabel->setText(blueFont + ovStepStr + endFont);
            saveButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getOCStepChanged())
        {
            ui->powerCntrlOCStepLabel->setText(blueFont + ocStepStr + endFont);
            saveButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getOVStartupChanged())
        {
            ui->powerCntrlOVStartupLabel->setText(blueFont + ovStartupStr + endFont);
            saveButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getOVChanged())
        {
            ui->powerCntrlOVLabel->setText(blueFont + ovStr + endFont);
            saveAllButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getOCChanged())
        {
            ui->powerCntrlOCLabel->setText(blueFont + ocStr + endFont);
            saveAllButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getModuleChanged())
        {
            ui->powerCntrlModuleLabel->setText(blueFont + moduleStr + endFont);
            saveAllButtonState = true;
        }
        if (m_powerCntrlChangesTracked->getMPPChanged())
        {
            ui->powerCntrlMPPLabel->setText(blueFont + mppStr + endFont);
            saveAllButtonState = true;
        }

        ui->powerCntrlSendPushButton->setEnabled(false);
        ui->powerCntrlSavePushButton->setEnabled(saveButtonState);
        ui->powerCntrlSaveAllPushButton->setEnabled(saveAllButtonState);

    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " no current active MAC";
        emit publishError(errString);
        qDebug() << errString;
    }
}

void AmptGUI_X::handleResetTextEditControls( void )
{

    ui->ovSendPushButton->setEnabled(false);
    ui->ocSendPushButton->setEnabled(false);
    ui->moduleSendPushButton->setEnabled(false);
    ui->mppSendPushButton->setEnabled(false);

    ui->ovSpinBox->setEnabled(false);
    ui->ovDial->setEnabled(false);
    ui->ovDial->setValue(0);

    ui->ocSpinBox->setEnabled(false);
    ui->ocDial->setEnabled(false);
    ui->ocDial->setValue(0);

    //ui->moduleSpinBox->setEnabled(true); LBC
    //ui->moduleDial->setEnabled(true);

    ui->moduleComboBox->clear();
    ui->moduleComboBox->addItem(amptOffStr);
    ui->moduleComboBox->addItem(amptOnStr);
    ui->moduleComboBox->setEnabled(false);
    ui->moduleDial->setValue(zero);
    ui->moduleDial->setEnabled(false);
    ui->moduleSendPushButton->setEnabled(false);

    ui->mppComboBox->clear();
    ui->mppComboBox->addItem(amptOffStr);
    ui->mppComboBox->addItem(amptOnStr);
    ui->mppComboBox->setEnabled(false);
    ui->mppDial->setEnabled(false);
    ui->mppDial->setValue(zero);
    ui->mppSendPushButton->setEnabled(false);

}

void AmptGUI_X::handleResetPowerCntrlWidgets( void )
{
    // qDebug() << Q_FUNC_INFO;

    m_powerCntrlChangesTracked->setIgnoreSignals(true);

    QString tFontColor = blackFont;

    if ( ResetParameterBlockValues == true )
    {
        tFontColor = greyFont;

        ui->powerCntrlVinStopRadioSpinBox->setEnabled(false);
        ui->powerCntrlVinStopRadioSpinBox->setValue(zero);

        ui->powerCntrlOVSpinBox->setEnabled(false);
        ui->powerCntrlOVSpinBox->setValue(zero);

        ui->powerCntrlOCSpinBox->setEnabled(false);
        ui->powerCntrlOCSpinBox->setValue(zero);

        ui->powerCntrlOVStartupSpinBox->setEnabled(false);
        ui->powerCntrlOVStartupSpinBox->setValue(zero);

        ui->powerCntrlOCStepSpinBox->setEnabled(false);
        ui->powerCntrlOCStepSpinBox->setValue(zero);

        ui->powerCntrlCurrentNoiseSpinBox->setEnabled(false);
        ui->powerCntrlCurrentNoiseSpinBox->setValue(zero);

        ui->powerCntrlOVStepSpinBox->setEnabled(false);
        ui->powerCntrlOVStepSpinBox->setValue(zero);

        ui->powerCntrlVinLimit255SpinBox->setEnabled(false);
        ui->powerCntrlVinLimit255SpinBox->setValue(zero);

        ui->powerCntrlVinTurnOnSpinBox->setEnabled(false);
        ui->powerCntrlVinTurnOnSpinBox->setValue(zero);

        ui->powerCntrlModuleComboBox->clear();
        ui->powerCntrlModuleComboBox->addItem(amptOffStr);
        ui->powerCntrlModuleComboBox->addItem(amptOnStr);
        ui->powerCntrlModuleComboBox->setEnabled(false);

        ui->powerCntrlMPPComboBox->clear();
        ui->powerCntrlMPPComboBox->addItem(amptOffStr);
        ui->powerCntrlMPPComboBox->addItem(amptOnStr);
        ui->powerCntrlMPPComboBox->setEnabled(false);
    }

    ui->powerCntrlVinTurnOnLabel->setText(tFontColor + powerCntrlVinTurnOnStr + endFont );
    ui->powerCntrlVinStopRadioLabel->setText(tFontColor + powerCntrlVinStopRadioStr + endFont);
    ui->powerCntrlVinLimit255Label->setText(tFontColor + powerCntrlVinLimit255Str + endFont);
    ui->powerCntrlOVLabel->setText( tFontColor + powerCntrlOVStr + endFont );
    ui->powerCntrlOCLabel->setText( tFontColor + powerCntrlOCStr + endFont );
    ui->powerCntrlOVStartupLabel->setText( tFontColor + powerCntrlOVStartupStr + endFont );
    ui->powerCntrlOCStepLabel->setText(tFontColor + powerCntrlOCStepStr + endFont );
    ui->powerCntrlCurrentNoiseLabel->setText( tFontColor + powerCntrlCurrentNoiseStr + endFont );
    ui->powerCntrlOVStepLabel->setText( tFontColor + powerCntrlOVStepStr + endFont );
    ui->powerCntrlVinLimit255Label->setText( tFontColor + powerCntrlVinLimit255Str + endFont );
    ui->powerCntrlModuleLabel->setText( tFontColor + powerCntrlModuleStr + endFont );
    ui->powerCntrlMPPLabel->setText( tFontColor + powerCntrlMPPStr + endFont );

    ui->powerCntrlSaveAllPushButton->setEnabled(false);
    ui->powerCntrlSavePushButton->setEnabled(false);
    ui->powerCntrlSendPushButton->setEnabled(false);

    m_powerCntrlChangesTracked->setIgnoreSignals(false);

}

void AmptGUI_X::handleResetLinearCoeffs( void )
{
    m_linearCoeffsChangesTracked->setIgnoreSignals(true);
    // qDebug() << Q_FUNC_INFO << "############################################################ called!!!";

    QString tFontColor = blackFont;

    if (ResetParameterBlockValues == true)
    {
        tFontColor = greyFont;

    ui->linearCoeffsLinearCoefficientsRowLabel->setEnabled(false);
    ui->linearCoeffsLinearCoefficientsRowLabel->setText(tFontColor + linearCoeffsCoefficientsRowLabelStr + endFont);

    ui->linearCoeffsLinearOffsetsRowLabel->setEnabled(false);
    ui->linearCoeffsLinearOffsetsRowLabel->setText( tFontColor + linearCoeffsOffsetRowLabelStr + endFont);

    ui->linearCoeffsVOutColumnLabel->setEnabled(false);
    ui->linearCoeffsVOutColumnLabel->setText(tFontColor + linearCoeffsVOutColumnStr + endFont);

    ui->linearCoeffsVIn1ColumnLabel->setEnabled(false);
    ui->linearCoeffsVIn1ColumnLabel->setText(tFontColor + linearCoeffsVIn1ColumnStr + endFont);

    ui->linearCoeffsVIn2ColumnLabel->setEnabled(false);
    ui->linearCoeffsVIn2ColumnLabel->setText(tFontColor + linearCoeffsVIn2ColumnStr + endFont);

    ui->linearCoeffsIOutColumnLabel->setEnabled(false);
    ui->linearCoeffsIOutColumnLabel->setText(tFontColor + linearCoeffsIOutColumnStr + endFont);

    ui->linearCoeffsIIn1ColumnLabel->setEnabled(false);
    ui->linearCoeffsIIn1ColumnLabel->setText(tFontColor + linearCoeffsIIn1ColumnStr + endFont);

    ui->linearCoeffsIIn2ColumnLabel->setEnabled(false);
    ui->linearCoeffsIIn2ColumnLabel->setText(tFontColor + linearCoeffsIIn2ColumnStr + endFont);

    ui->linearCoeffsTextColumnLabel->setEnabled(false);
    ui->linearCoeffsTextColumnLabel->setText(tFontColor + linearCoeffsTextColumnStr + endFont);

    // int currentIndex = ui->AllTabs->currentIndex();
    // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
    // QTabBar* bar=ui->AllTabs->tabBar();
    // bar->setTabTextColor(currentIndex, Qt::black);

    //if (ResetParameterBlockValues == true)
    //{
    ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsVOutCoefficientDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsVOutOffsetDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsVIn1CoefficientDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsVIn1CoefficientDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsVIn1OffsetDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsVIn1OffsetDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsIOutCoefficientDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsIOutCoefficientDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsIOutOffsetDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsIOutOffsetDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsVIn2CoefficientDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsVIn2CoefficientDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsVIn2OffsetDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsVIn2OffsetDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsTextCoefficientDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsTextCoefficientDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsTextOffsetDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsTextOffsetDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsIIn1CoefficientDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsIIn1CoefficientDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsIIn1OffsetDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsIIn1OffsetDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsIIn2CoefficientDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsIIn2CoefficientDoubleSpinBox->setValue(zeroAsDouble);
    ui->linearCoeffsIIn2OffsetDoubleSpinBox->setEnabled(false);
    ui->linearCoeffsIIn2OffsetDoubleSpinBox->setValue(zeroAsDouble);

    ui->linearCoeffsSendPushButton->setEnabled(false);
    }

    ui->linearCoeffsSavePushButton->setEnabled(false);
    m_linearCoeffsChangesTracked->resetAllTrackedValues();
    m_linearCoeffsChangesTracked->setIgnoreSignals(false);
}

void AmptGUI_X::handleResetAllTabTitles( void )
{
    int currentIndex = 0;
    QTabBar* bar=ui->AllTabs->tabBar();
    int numberOfTabs = ui->AllTabs->count();

    for (currentIndex = 0; currentIndex < numberOfTabs; currentIndex++)
    {
        bar->setTabTextColor(currentIndex,Qt::black);
    }

    //QString aCommand;
    //QTabBar* bar=ui->AllTabs->tabBar();
    // bool saveButtonState = false;

    // bar->setTabTextColor(currentIndex,Qt::blue);
}

void AmptGUI_X::handleLinearCoeffsSendPushButton( void )
{

    // qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";

    if (m_currentActiveMAC != "")
    {

        m_linearCoeffsChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC);

        int currentIndex = ui->AllTabs->currentIndex();
        QString aCommand;
        QTabBar* bar=ui->AllTabs->tabBar();
        bool saveButtonState = false;

        bar->setTabTextColor(currentIndex,Qt::blue);

        if (m_linearCoeffsChangesTracked->getVOutCoefficientChanged())
        {
            ui->linearCoeffsVOutColumnLabel->setText(blueFont + linearCoeffsVOutColumnStr + endFont);
            ui->linearCoeffsLinearCoefficientsRowLabel->setText(blueFont + linearCoeffsCoefficientsRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getVOutOffsetChanged())
        {
            ui->linearCoeffsVOutColumnLabel->setText(blueFont + linearCoeffsVOutColumnStr + endFont);
            ui->linearCoeffsLinearOffsetsRowLabel->setText(blueFont + linearCoeffsOffsetRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getVIn1CoefficientChanged())
        {
            ui->linearCoeffsVIn1ColumnLabel->setText(blueFont + linearCoeffsVIn1ColumnStr + endFont);
            ui->linearCoeffsLinearCoefficientsRowLabel->setText(blueFont + linearCoeffsCoefficientsRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getVIn1OffsetChanged())
        {
            ui->linearCoeffsVIn1ColumnLabel->setText(blueFont + linearCoeffsVIn1ColumnStr + endFont);
            ui->linearCoeffsLinearOffsetsRowLabel->setText(blueFont + linearCoeffsOffsetRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getIOutCoefficientChanged())
        {
            ui->linearCoeffsIOutColumnLabel->setText(blueFont + linearCoeffsIOutColumnStr + endFont);
            ui->linearCoeffsLinearCoefficientsRowLabel->setText(blueFont + linearCoeffsCoefficientsRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getIOutOffsetChanged())
        {
            ui->linearCoeffsIOutColumnLabel->setText(blueFont + linearCoeffsIOutColumnStr + endFont);
            ui->linearCoeffsLinearOffsetsRowLabel->setText(blueFont + linearCoeffsOffsetRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getVIn2CoefficientChanged())
        {
            ui->linearCoeffsVIn2ColumnLabel->setText(blueFont + linearCoeffsVIn2ColumnStr + endFont);
            ui->linearCoeffsLinearCoefficientsRowLabel->setText(blueFont + linearCoeffsCoefficientsRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getVIn2OffsetChanged())
        {
            ui->linearCoeffsVIn2ColumnLabel->setText(blueFont + linearCoeffsVIn2ColumnStr + endFont);
            ui->linearCoeffsLinearOffsetsRowLabel->setText(blueFont + linearCoeffsOffsetRowLabelStr + endFont );
            saveButtonState = true;
        }


        if (m_linearCoeffsChangesTracked->getTextCoefficientChanged())
        {
            ui->linearCoeffsTextColumnLabel->setText(blueFont + linearCoeffsTextColumnStr + endFont);
            ui->linearCoeffsLinearCoefficientsRowLabel->setText(blueFont + linearCoeffsCoefficientsRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getTextOffsetChanged())
        {
            ui->linearCoeffsTextColumnLabel->setText(blueFont + linearCoeffsTextColumnStr + endFont);
            ui->linearCoeffsLinearOffsetsRowLabel->setText(blueFont + linearCoeffsOffsetRowLabelStr + endFont );
            saveButtonState = true;
        }

        if (m_linearCoeffsChangesTracked->getIIn2CoefficientChanged())
        {
            ui->linearCoeffsIIn2ColumnLabel->setText(blueFont + linearCoeffsIIn2ColumnStr + endFont);
            ui->linearCoeffsLinearCoefficientsRowLabel->setText(blueFont + linearCoeffsCoefficientsRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getIIn2OffsetChanged())
        {
            ui->linearCoeffsIIn2ColumnLabel->setText(blueFont + linearCoeffsIIn2ColumnStr + endFont);
            ui->linearCoeffsLinearOffsetsRowLabel->setText(blueFont + linearCoeffsOffsetRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getIIn1CoefficientChanged())
        {
            ui->linearCoeffsIIn1ColumnLabel->setText(blueFont + linearCoeffsIIn1ColumnStr + endFont);
            ui->linearCoeffsLinearCoefficientsRowLabel->setText(blueFont + linearCoeffsCoefficientsRowLabelStr + endFont );
            saveButtonState = true;
        }
        if (m_linearCoeffsChangesTracked->getIIn1OffsetChanged())
        {
            ui->linearCoeffsIIn1ColumnLabel->setText(blueFont + linearCoeffsIIn1ColumnStr + endFont);
            ui->linearCoeffsLinearOffsetsRowLabel->setText(blueFont + linearCoeffsOffsetRowLabelStr + endFont );
            saveButtonState = true;
        }

        ui->linearCoeffsSendPushButton->setEnabled(false);
        ui->linearCoeffsSavePushButton->setEnabled(saveButtonState);

    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " no current active MAC";
        emit publishError(errString);
        qDebug() << errString;
    }
}





void AmptGUI_X::handleLinearCoeffsVOutCoefficientDoubleSpinBoxChange(const double value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeVOutCoefficient(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearCoefficientsRowLabel->setText(redFont + linearCoeffsCoefficientsRowLabelStr + endFont);
        ui->linearCoeffsVOutColumnLabel->setText(redFont + linearCoeffsVOutColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsVOutOffsetDoubleSpinBoxChange(const double value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeVOutOffset(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearOffsetsRowLabel->setText(redFont + linearCoeffsOffsetRowLabelStr + endFont);
        ui->linearCoeffsVOutColumnLabel->setText(redFont + linearCoeffsVOutColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsVIn1CoefficientDoubleSpinBoxChange(const double value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeVIn1Coefficient(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearCoefficientsRowLabel->setText(redFont + linearCoeffsCoefficientsRowLabelStr + endFont);
        ui->linearCoeffsVIn1ColumnLabel->setText(redFont + linearCoeffsVIn1ColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsVIn1OffsetDoubleSpinBoxChange(const double value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeVIn1Offset(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearOffsetsRowLabel->setText(redFont + linearCoeffsOffsetRowLabelStr + endFont);
        ui->linearCoeffsVIn1ColumnLabel->setText(redFont + linearCoeffsVIn1ColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsVIn2CoefficientDoubleSpinBoxChange(const double value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeVIn2Coefficient(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearCoefficientsRowLabel->setText(redFont + linearCoeffsCoefficientsRowLabelStr + endFont);
        ui->linearCoeffsVIn2ColumnLabel->setText(redFont + linearCoeffsVIn1ColumnStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsVIn2OffsetDoubleSpinBoxChange(const double value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeVIn2Offset(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearOffsetsRowLabel->setText(redFont + linearCoeffsOffsetRowLabelStr + endFont);
        ui->linearCoeffsVIn2ColumnLabel->setText(redFont + linearCoeffsVIn2ColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}





void AmptGUI_X::handleLinearCoeffsIOutCoefficientDoubleSpinBoxChange(const double value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeIOutCoefficient(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearCoefficientsRowLabel->setText(redFont + linearCoeffsCoefficientsRowLabelStr + endFont);
        ui->linearCoeffsIOutColumnLabel->setText(redFont + linearCoeffsIOutColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsIOutOffsetDoubleSpinBoxChange(const double value)
{
    //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeIOutOffset(value);
        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearOffsetsRowLabel->setText(redFont + linearCoeffsOffsetRowLabelStr + endFont);
        ui->linearCoeffsIOutColumnLabel->setText(redFont + linearCoeffsIOutColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsIIn1CoefficientDoubleSpinBoxChange(const double value)
{
    //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeIIn1Coefficient(value);
        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearCoefficientsRowLabel->setText(redFont + linearCoeffsCoefficientsRowLabelStr + endFont);
        ui->linearCoeffsIIn1ColumnLabel->setText(redFont + linearCoeffsIIn1ColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsIIn1OffsetDoubleSpinBoxChange(const double value)
{
    //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeIIn1Offset(value);
        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearOffsetsRowLabel->setText(redFont + linearCoeffsOffsetRowLabelStr + endFont);
        ui->linearCoeffsIIn1ColumnLabel->setText(redFont + linearCoeffsIIn1ColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsIIn2CoefficientDoubleSpinBoxChange(const double value)
{
    //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeIIn2Coefficient(value);
        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearCoefficientsRowLabel->setText(redFont + linearCoeffsCoefficientsRowLabelStr + endFont);
        ui->linearCoeffsIIn2ColumnLabel->setText(redFont + linearCoeffsIIn2ColumnStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsIIn2OffsetDoubleSpinBoxChange(const double value)
{
    //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeIIn2Offset(value);
        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutOffsetDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearOffsetsRowLabel->setText(redFont + linearCoeffsOffsetRowLabelStr + endFont);
        ui->linearCoeffsIIn2ColumnLabel->setText(redFont + linearCoeffsIIn2ColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}




void AmptGUI_X::handleLinearCoeffsTextCoefficientDoubleSpinBoxChange(const double value)
{
    //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeTextCoefficient(value);
        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        //ui->linearCoeffsVOutCoefficientDoubleSpinBox->setEnabled(true); // LBC why?

        ui->linearCoeffsLinearCoefficientsRowLabel->setText(redFont + linearCoeffsCoefficientsRowLabelStr + endFont);
        ui->linearCoeffsTextColumnLabel->setText(redFont + linearCoeffsTextColumnStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleLinearCoeffsTextOffsetDoubleSpinBoxChange(const double value)
{
    //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_linearCoeffsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_linearCoeffsChangesTracked->changeTextOffset(value);
        //qDebug() << Q_FUNC_INFO << " changed to " << value;

        ui->linearCoeffsLinearOffsetsRowLabel->setText(redFont + linearCoeffsOffsetRowLabelStr + endFont);
        ui->linearCoeffsTextColumnLabel->setText(redFont + linearCoeffsTextColumnStr + endFont);
        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->linearCoeffsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleResetTempCntrl( void )
{
    QString tFontColor = blackFont;

    if (ResetParameterBlockValues == true)
    {
        tFontColor = greyFont;

        ui->tempCntrlTSuperHotSpinBox->setEnabled(false);
        ui->tempCntrlTSuperHotSpinBox->setValue(zero);

        ui->tempCntrlTHotSpinBox->setEnabled(false);
        ui->tempCntrlTHotSpinBox->setValue(zero);

        ui->tempCntrlTColdSpinBox->setEnabled(false);
        ui->tempCntrlTColdSpinBox->setValue(zero);

        ui->tempCntrlFallbackTimeSpinBox->setEnabled(false);
        ui->tempCntrlFallbackTimeSpinBox->setValue(zero);

        ui->tempCntrlOCProtectionSpinBox->setEnabled(false);
        ui->tempCntrlOCProtectionSpinBox->setValue(zero);
    }

    ui->tempCntrlTSuperHotLabel->setText(tFontColor + tempCntrlTSuperHotStr + endFont );
    ui->tempCntrlTHotLabel->setText(tFontColor + tempCntrlTHotStr + endFont);
    ui->tempCntrlTColdLabel->setText(tFontColor + tempCntrlTColdStr + endFont);
    ui->tempCntrlFallbackTimeLabel->setText(tFontColor + tempCntrlFallbackTimeStr + endFont);
    ui->tempCntrlOCProtectionLabel->setText(tFontColor + tempCntrlOCProtectionStr + endFont);

    ui->tempCntrlSendPushButton->setEnabled(false);
    ui->tempCntrlSavePushButton->setEnabled(false);
}

void AmptGUI_X::handleTempCntrlSendPushButton( void )
{

    // qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";

    if (m_currentActiveMAC != "")
    {

        m_tempCntrlValueChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC);

        int currentIndex = ui->AllTabs->currentIndex();
        QString aCommand;
        QTabBar* bar=ui->AllTabs->tabBar();
        bool saveButtonState = false;

        bar->setTabTextColor(currentIndex,Qt::blue);

        if (m_tempCntrlValueChangesTracked->getOCProtectionChanged())
        {

            ui->tempCntrlOCProtectionLabel->setText(blueFont + tempCntrlOCProtectionStr + endFont);
            saveButtonState = true;
        }
        if (m_tempCntrlValueChangesTracked->getTColdChanged())
        {

            ui->tempCntrlTColdLabel->setText(blueFont + tempCntrlTColdStr + endFont);
            saveButtonState = true;
        }
        if (m_tempCntrlValueChangesTracked->getTHotChanged())
        {

            ui->tempCntrlTHotLabel->setText(blueFont + tempCntrlTHotStr + endFont);
            saveButtonState = true;
        }
        if (m_tempCntrlValueChangesTracked->getTSuperHotChanged())
        {

            ui->tempCntrlTSuperHotLabel->setText(blueFont + tempCntrlTSuperHotStr + endFont);
            saveButtonState = true;
        }
        if (m_tempCntrlValueChangesTracked->getFallbackTimeChanged())
        {

            ui->tempCntrlFallbackTimeLabel->setText(blueFont + tempCntrlFallbackTimeStr + endFont);
            saveButtonState = true;
        }


        ui->tempCntrlSendPushButton->setEnabled(false);
        ui->tempCntrlSavePushButton->setEnabled(saveButtonState);

    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " no current active MAC";
        emit publishError(errString);
        qDebug() << errString;
    }
}


void AmptGUI_X::handleTempCntrlOCProtectionSpinBoxChange(const int value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_tempCntrlValueChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_tempCntrlValueChangesTracked->changeOCProtection(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;

        ui->tempCntrlOCProtectionLabel ->setText(redFont + tempCntrlOCProtectionStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->tempCntrlSendPushButton ->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleTempCntrlTColdSpinBoxChange(const int value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_tempCntrlValueChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_tempCntrlValueChangesTracked->changeTCold(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;

        ui->tempCntrlTColdLabel ->setText(redFont + tempCntrlTColdStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->tempCntrlSendPushButton ->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleTempCntrlTHotSpinBoxChange(const int value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_tempCntrlValueChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_tempCntrlValueChangesTracked->changeTHot(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;

        ui->tempCntrlTHotLabel->setText(redFont + tempCntrlTHotStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->tempCntrlSendPushButton ->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleTempCntrlTSuperHotSpinBoxChange(const int value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_tempCntrlValueChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_tempCntrlValueChangesTracked->changeTSuperHot(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;

        ui->tempCntrlTSuperHotLabel ->setText(redFont + tempCntrlTSuperHotStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->tempCntrlSendPushButton ->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleTempCntrlFallbackTimeSpinBoxChange(const int value)
{
    // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

    if (m_tempCntrlValueChangesTracked->getIgnoreSignals() == false)
    {
        // qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_tempCntrlValueChangesTracked->changeFallbackTime(value);
        // qDebug() << Q_FUNC_INFO << " changed to " << value;

        ui->tempCntrlFallbackTimeLabel->setText(redFont + tempCntrlFallbackTimeStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);
        ui->tempCntrlSendPushButton ->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleResetFineTuning( void )
{
    QString tFontColor = blackFont;

    if (ResetParameterBlockValues == true)
    {
        tFontColor = greyFont;
        ui->fineTuningVRef0DoubleSpinBox->setEnabled(false);
        ui->fineTuningVRef0DoubleSpinBox->setValue(zeroAsDouble);

        ui->fineTuningKVRefDoubleSpinBox->setEnabled(false);
        ui->fineTuningKVRefDoubleSpinBox->setValue(zeroAsDouble);

        ui->fineTuningT0DoubleSpinBox->setEnabled(false);
        ui->fineTuningT0DoubleSpinBox->setValue(zeroAsDouble);

        ui->fineTuningTempCoeffCurrentDoubleSpingBox->setEnabled(false);
        ui->fineTuningTempCoeffCurrentDoubleSpingBox->setValue(zeroAsDouble);

        ui->fineTuningTempCoeffPowerDoubleSpinBox->setEnabled(false);
        ui->fineTuningTempCoeffPowerDoubleSpinBox->setValue(zeroAsDouble);

        ui->fineTuningShortCircuitLevelSpinBox->setEnabled(false);
        ui->fineTuningShortCircuitLevelSpinBox->setValue(zero);

        ui->fineTuningShortCircuitLevelSpinBox->setEnabled(false);
        ui->fineTuningShortCircuitLevelSpinBox->setValue(zero);
    }

    ui->fineTuningVRef0Label->setText(tFontColor + fineTuningVRef0Str + endFont);
    ui->fineTuningKVRefLabel->setText(tFontColor + fineTuningKVRefStr + endFont);
    ui->fineTuningT0Label->setText(tFontColor + fineTuningT0Str + endFont);
    ui->fineTuningTempCoeffCurrentLabel->setText(tFontColor + fineTuningTempCoeffCurrentStr + endFont);
    ui->fineTuningTempCoeffPowerLabel->setText(tFontColor + fineTuningTempCoeffPowerStr + endFont);
    ui->fineTuningShortCircuitLevelLabel->setText(tFontColor + fineTuningShortCircuitLevelStr + endFont);

    ui->fineTuningSendPushButton->setEnabled(false);
    ui->fineTuningSavePushButton->setEnabled(false);

}

void AmptGUI_X::handleFineTuningSendPushButton( void )
{

    // qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";

    if (m_currentActiveMAC != "")
    {

        m_fineTuningValueChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC);

        int currentIndex = ui->AllTabs->currentIndex();
        QString aCommand;
        QTabBar* bar=ui->AllTabs->tabBar();
        bool saveButtonState = false;

        bar->setTabTextColor(currentIndex,Qt::blue);

        if (m_fineTuningValueChangesTracked->getVRef0Changed())
        {

            ui->fineTuningVRef0Label->setText(blueFont + fineTuningVRef0Str + endFont);
            saveButtonState = true;
        }
        if (m_fineTuningValueChangesTracked->getKVRefChanged())
        {

            ui->fineTuningKVRefLabel->setText(blueFont + fineTuningKVRefStr + endFont);
            saveButtonState = true;
        }
        if (m_fineTuningValueChangesTracked->getT0Changed())
        {

            ui->fineTuningT0Label->setText(blueFont + fineTuningT0Str + endFont);
            saveButtonState = true;
        }
        if (m_fineTuningValueChangesTracked->getTempCoeffCurrentChanged())
        {

            ui->fineTuningTempCoeffCurrentLabel->setText(blueFont + fineTuningTempCoeffCurrentStr + endFont);
            saveButtonState = true;
        }
        if (m_fineTuningValueChangesTracked->getTempCoeffPowerChanged())
        {

            ui->fineTuningTempCoeffPowerLabel->setText(blueFont + fineTuningTempCoeffPowerStr + endFont);
            saveButtonState = true;
        }
        if (m_fineTuningValueChangesTracked->getShortCircuitLevelChanged())
        {

            ui->fineTuningShortCircuitLevelLabel->setText(blueFont + fineTuningShortCircuitLevelStr + endFont);
            saveButtonState = true;
        }


        ui->fineTuningSendPushButton->setEnabled(false);
        ui->fineTuningSavePushButton->setEnabled(saveButtonState);

    }
    else
    {
        QString errString(Q_FUNC_INFO);
                    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " no current active MAC";
        emit publishError(errString);
        qDebug() << errString;
    }
}




 void AmptGUI_X::handleFineTuningVRef0DoubleSpinBoxChange(const double value)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

     if (m_fineTuningValueChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_fineTuningValueChangesTracked->changeVRef0(value);
         // qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->fineTuningVRef0Label->setText(redFont + fineTuningVRef0Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->fineTuningSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleFineTuningKVRefDoubleSpinBoxChange(const double value)
 {
     //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

     if (m_fineTuningValueChangesTracked->getIgnoreSignals() == false)
     {
         //qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_fineTuningValueChangesTracked->changeKVRef(value);

         //qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->fineTuningKVRefLabel->setText(redFont + fineTuningKVRefStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->fineTuningSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleFineTuningT0DoubleSpinBoxChange(const double value)
 {
     //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

     if (m_fineTuningValueChangesTracked->getIgnoreSignals() == false)
     {
         //qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_fineTuningValueChangesTracked->changeT0(value);

         //qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->fineTuningT0Label->setText(redFont + fineTuningT0Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->fineTuningSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleFineTuningTempCoeffCurrentDoubleSpinBoxChange(const double value)
 {
     //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

     if (m_fineTuningValueChangesTracked->getIgnoreSignals() == false)
     {
         //qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_fineTuningValueChangesTracked->changeTempCoeffCurrent(value);

         //qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->fineTuningTempCoeffCurrentLabel->setText(redFont + fineTuningTempCoeffCurrentStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->fineTuningSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleFineTuningTempCoeffPowerDoubleSpinBoxChange(const double value)
 {
     //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

     if (m_fineTuningValueChangesTracked->getIgnoreSignals() == false)
     {
         //qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_fineTuningValueChangesTracked->changeTempCoeffPower(value);

         //qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->fineTuningTempCoeffPowerLabel->setText(redFont + fineTuningTempCoeffPowerStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->fineTuningSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleFineTuningShortCircuitLevelSpinBoxChange(const int value)
 {
     //qDebug() << Q_FUNC_INFO << " value:" << QString::number(value);

     if (m_fineTuningValueChangesTracked->getIgnoreSignals() == false)
     {
         //qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_fineTuningValueChangesTracked->changeShortCircuitLevel(value);

         //qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->fineTuningShortCircuitLevelLabel->setText(redFont + fineTuningShortCircuitLevelStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->fineTuningSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleResetRadio( void )
 {
     QString tFontColor = blackFont;

     if (ResetParameterBlockValues == true)
     {
         tFontColor = greyFont;

         ui->radioDFK0DoubleSpinBox->setEnabled(false);
         ui->radioDFK0DoubleSpinBox->setValue(zeroAsDouble);

         ui->radioDFK1DoubleSpinBox->setEnabled(false);
         ui->radioDFK1DoubleSpinBox->setValue(zeroAsDouble);

         ui->radioDFK2DoubleSpinBox->setEnabled(false);
         ui->radioDFK2DoubleSpinBox->setValue(zeroAsDouble);

         ui->radioDFK3DoubleSpinBox->setEnabled(false);
         ui->radioDFK3DoubleSpinBox->setValue(zeroAsDouble);

         ui->radioPureOffsetSpinBox->setEnabled(false);
         ui->radioPureOffsetSpinBox->setValue(zero);

         ui->radioLowCurrentLimitTo255SpinBox->setEnabled(false);
         ui->radioLowCurrentLimitTo255SpinBox->setValue(zero);

         ui->radioVin2To255ValueLabel->setText(Blank);
         ui->radioVin2From255ValueLabel->setText(Blank);
     }

     ui->radioDFK0Label->setText(tFontColor + radioDFK0Str + endFont);
     ui->radioDFK1Label->setText(tFontColor + radioDFK1Str + endFont);
     ui->radioDFK2Label->setText(tFontColor + radioDFK2Str + endFont);
     ui->radioDFK3Label->setText(tFontColor + radioDFK3Str + endFont);
     ui->radioPureOffsetLabel->setText(tFontColor + radioPureOffsetStr + endFont);
     ui->radioLowCurrentLimitTo255Label->setText(tFontColor + radioLowCurrentLimitTo255Str + endFont);

     ui->radioSendPushButton->setEnabled(false);
     ui->radioSavePushButton->setEnabled(false);

 }

 void AmptGUI_X::handleProtectionsFETFailureCountSpinBoxChange( int s)
 {
     // qDebug() << Q_FUNC_INFO << " new value of " << s;

     QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

     // if (theFamily == Family1300V)
     // {

         if (m_protectionsChangesTracked->getIgnoreSignals() == false)
         {
             //qDebug() << Q_FUNC_INFO << " acting on signal.";
             int currentIndex = 0;
             m_protectionsChangesTracked->changeFETCount(s);

             //qDebug() << Q_FUNC_INFO << " changed to " << value;

             ui->protectionsFETFailureCountLabel->setText(redFont + protectionFETFailureCountStr + endFont);

             currentIndex = ui->AllTabs->currentIndex();
             //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
             QTabBar* bar=ui->AllTabs->tabBar();
             bar->setTabTextColor(currentIndex, Qt::red);

             ui->protectionsSendPushButton->setEnabled(true);
         }
         else
         {
             // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
         }
    // }
         /*
     else
     {
         QString errString(Q_FUNC_INFO);
         QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
         errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
         emit publishError(errString);
         qDebug() << errString;
     }
     */
 }

 void AmptGUI_X::handleProtectionsFETFailureThresholdSpinBoxChange( const int s )
 {
     // qDebug() << Q_FUNC_INFO << " new value of " << s;

     QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

     // if (theFamily == Family1300V)
     // {

         if (m_protectionsChangesTracked->getIgnoreSignals() == false)
         {
             //qDebug() << Q_FUNC_INFO << " acting on signal.";
             int currentIndex = 0;
             m_protectionsChangesTracked->changeFETThreshold(s);

             //qDebug() << Q_FUNC_INFO << " changed to " << value;

             ui->protectionsFETThresholdLabel->setText(redFont + protectionFETFailureThresholdStr + endFont);

             currentIndex = ui->AllTabs->currentIndex();
             //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
             QTabBar* bar=ui->AllTabs->tabBar();
             bar->setTabTextColor(currentIndex, Qt::red);

             ui->protectionsSendPushButton->setEnabled(true);
         }
         else
         {
             // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
         }
     // }
         /*
     else
     {
         QString errString(Q_FUNC_INFO);
         QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
         errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
         emit publishError(errString);
         qDebug() << errString;
     }
     */
 }

 void AmptGUI_X::handleProtectionsFETFailureDeltaCurrentSpinBoxChange( const int s )
 {
     // qDebug() << Q_FUNC_INFO << " new value of " << s;

     QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

     //if (theFamily == Family1300V)
     //{

         if (m_protectionsChangesTracked->getIgnoreSignals() == false)
         {
             //qDebug() << Q_FUNC_INFO << " acting on signal.";
             int currentIndex = 0;
             m_protectionsChangesTracked->changeFETDeltaCurrent(s);

             //qDebug() << Q_FUNC_INFO << " changed to " << value;

             ui->protectionsFETThresholdLabel->setText(redFont + protectionFETFailureDeltaCurrentStr + endFont);

             currentIndex = ui->AllTabs->currentIndex();
             //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
             QTabBar* bar=ui->AllTabs->tabBar();
             bar->setTabTextColor(currentIndex, Qt::red);

             ui->protectionsSendPushButton->setEnabled(true);
         }
         else
         {
             // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
         }
     //}
         /*
     else
     {
         QString errString(Q_FUNC_INFO);
         QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
         errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
         emit publishError(errString);
         qDebug() << errString;
     }
     */
 }

void AmptGUI_X::handleProtectionsProtection1SpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))
    {

        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection1(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection1Label->setText(redFont + protection1_1300VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
    {
        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection1(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection1Label->setText(redFont + protection1_1500VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(errString);
        qDebug() << errString;
    }
}

void AmptGUI_X::handleProtectionsProtection2SpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))
    {

        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection2(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection2Label->setText(redFont + protection2_1300VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
    {
        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection2(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection2Label->setText(redFont + protection2_1500VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(errString);
        qDebug() << errString;
    }
}

void AmptGUI_X::handleProtectionsProtection3SpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();


    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))
    {

        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection3(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection3Label->setText(redFont + protection3_1300VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
    {
        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection3(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection3Label->setText(redFont + protection3_1500VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(errString);
        qDebug() << errString;
    }
}

void AmptGUI_X::handleProtectionsProtection4SpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))
    {
        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection4(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection4Label->setText(redFont + protection4_1300VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
    {
        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeProtection4(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsProtection4Label->setText(redFont + protection4_1500VStr + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(errString);
        qDebug() << errString;
    }
}

void AmptGUI_X::handleProtections1300VAMFTimer1SpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;
    QString tString(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))
    {

        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeAMFTimer1(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsAMF_Timer1Label->setText(redFont + protection_AMF_Timer1Str + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1000V) || (theFamily == Family600V))
    {
        tString += " INFO: " + CurrentDateTime + " no AMF protections implemented for family " + theFamily;
        emit publishError(tString);
    }
    else
    {

        tString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(tString);
        qDebug() << tString;
    }
}

void AmptGUI_X::handleProtections1300VAMFTimer2SpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;
    QString tString(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))    {

        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeAMFTimer2(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsAMF_Timer2Label->setText(redFont + protection_AMF_Timer2Str + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1000V) || (theFamily == Family600V))
    {
        tString += " INFO: " + CurrentDateTime + " no AMF protections implemented for family " + theFamily;
        emit publishError(tString);
    }
    else
    {
        tString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(tString);
        qDebug() << tString;
    }
}

void AmptGUI_X::handleProtections1300VAMFV_OVSpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;
    QString tString(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))

    {

        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeAMFV_OV(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsAMF_V_OVLabel->setText(redFont + protection_AMF_V_OV_Str + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1000V) || (theFamily == Family600V))
    {
        tString += " INFO: " + CurrentDateTime + " no AMF protections implemented for family " + theFamily;
        emit publishError(tString);
    }
    else
    {
        tString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(tString);
        qDebug() << tString;
    }
}

void AmptGUI_X::handleProtections1300VAMFI_OCSpinBoxChange( const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;
    QString tString(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();

    if ((theFamily == Family1300V) || (theFamily == Family600V_V2))
    {
        if (m_protectionsChangesTracked->getIgnoreSignals() == false)
        {
            //qDebug() << Q_FUNC_INFO << " acting on signal.";
            int currentIndex = 0;
            m_protectionsChangesTracked->changeAMFI_OC(static_cast<unsigned int>(s));

            //qDebug() << Q_FUNC_INFO << " changed to " << value;

            ui->protectionsAMF_I_OCLabel->setText(redFont + protection_AMF_I_OC_Str + endFont);

            currentIndex = ui->AllTabs->currentIndex();
            //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
            QTabBar* bar=ui->AllTabs->tabBar();
            bar->setTabTextColor(currentIndex, Qt::red);

            ui->protectionsSendPushButton->setEnabled(true);
        }
        else
        {
            // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
        }
    }
    else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1000V) || (theFamily == Family600V))
    {
        tString += " INFO: " + CurrentDateTime + " no AMF protections implemented for family " + theFamily;
        emit publishError(tString);
    }
    else
    {
        tString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
        emit publishError(tString);
        qDebug() << tString;
    }
}

void AmptGUI_X::handleProtectionsAMF_MPPCyclesOffSpinBoxChange(const int s)
{
    // qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeAMFMPPOffCycles(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;

        ui->protectionsAMF_MPP_Off_CyclesLabel->setText(redFont + protection_AMF_MPP_Cycles_Off_Str + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleProtectionsAMF_MPPTimesOffSpinBoxChange(const int s )
{
      // qDebug() << Q_FUNC_INFO << " new value of " << s;
      if (m_protectionsChangesTracked->getIgnoreSignals() == false)
      {
          //qDebug() << Q_FUNC_INFO << " acting on signal.";
          int currentIndex = 0;
          m_protectionsChangesTracked->changeAMFMPPTimesOff(static_cast<unsigned int>(s));

          //qDebug() << Q_FUNC_INFO << " changed to " << value;

          ui->protectionsAMF_MPP_TimesOffLabel->setText(redFont + protection_AMF_MPP_Number_Of_Off_Cycles + endFont);

          currentIndex = ui->AllTabs->currentIndex();
          //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
          QTabBar* bar=ui->AllTabs->tabBar();
          bar->setTabTextColor(currentIndex, Qt::red);

          ui->protectionsSendPushButton->setEnabled(true);
      }
      else
      {
          // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
      }
}

void AmptGUI_X::handleProtectionsAMF_DebugSpinBoxChange(const int s)
{
      qDebug() << Q_FUNC_INFO << " new value of " << s;
      if (m_protectionsChangesTracked->getIgnoreSignals() == false)
      {
          //qDebug() << Q_FUNC_INFO << " acting on signal.";
          int currentIndex = 0;
          m_protectionsChangesTracked->changeAMFDebug(static_cast<unsigned int>(s));

          //qDebug() << Q_FUNC_INFO << " changed to " << value;

          ui->protectionsAMF_DebugLabel->setText(redFont + protection_Debug_Monitoring_Str + endFont);

          currentIndex = ui->AllTabs->currentIndex();
          //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
          QTabBar* bar=ui->AllTabs->tabBar();
          bar->setTabTextColor(currentIndex, Qt::red);

          ui->protectionsSendPushButton->setEnabled(true);
      }
      else
      {
          // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
      }
}

void AmptGUI_X::handleProtectionsIinLimitSpinBoxChange(const int s )
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeIinLimit(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsIinLimitLabel->setText(redFont + protection_1500V_30_IinLimitStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleProtectionsIinLimitOCStepsSpinBoxChange(const int s)
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeIinLimitOCSteps(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsIinLimitOCStepsLabel->setText(redFont + protection_1500V_30_IinLimitOCStepsStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleProtectionsIinLimitOCDelaySpinBoxChange(const int s)
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeIinLimitOCDelay(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsIinLimitOCDelayLabel->setText(redFont + protection_1500V_30_IinLimitOCDelayStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleProtectionsIinLimitTempAmbientAdjustSpinBoxChange( const int s)
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeIinLimitTempAmbientAdjust(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsIinLimitTempAmbientAdjustLabel->setText(redFont + protection_1500V_30_IinLimitTempAmbientAdjustStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}


void AmptGUI_X::handleProtectionsEF_InputCurrentThresholdSpinBoxChange(const int s)
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeEFInputCurrentThreshold(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsEFInputCurrentThresholdLabel->setText(redFont + protection_1500V_EFInputCurrentThresholdStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleProtectionsEF_OccurrenceThresholdSpinBoxChange(const int s)
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeEFOccurrenceThreshold(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsEFOccurrenceThresholdLabel->setText(redFont + protection_1500V_EFOccurrenceThresholdStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleProtectionsEF_CountDownTimerSpinBoxChange(const int s)
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeEFCountDownTimer(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsEFCountDownTimerLabel->setText(redFont + protection_1500V_EFCountDownTimerStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

void AmptGUI_X::handleProtectionsEF_AlphaNumeratorSpinBoxChange(const int s)
{
    qDebug() << Q_FUNC_INFO << " new value of " << s;
    if (m_protectionsChangesTracked->getIgnoreSignals() == false)
    {
        //qDebug() << Q_FUNC_INFO << " acting on signal.";
        int currentIndex = 0;
        m_protectionsChangesTracked->changeEFAlphaNumerator(static_cast<unsigned int>(s));

        //qDebug() << Q_FUNC_INFO << " changed to " << value;
        ui->protectionsEFAlphaNumeratorLabel->setText(redFont + protection_1500V_EFAlphaNumeratorStr + endFont);

        currentIndex = ui->AllTabs->currentIndex();
        //qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
        QTabBar* bar=ui->AllTabs->tabBar();
        bar->setTabTextColor(currentIndex, Qt::red);

        ui->protectionsSendPushButton->setEnabled(true);
    }
    else
    {
        // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
    }
}

 void AmptGUI_X::handleProtectionsSendPushButton( void )
 {
     // qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";
     QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

     if (m_currentActiveMAC != "")
     {
         QString theFamily = ui->edSettingsOptimizerFamilyComboBox->currentText();
         qDebug() << Q_FUNC_INFO << " the family is " << theFamily;

         bool saveButtonState = false;
         if ((theFamily == Family1300V) || (theFamily == Family600V_V2))
         {
             qDebug() << Q_FUNC_INFO << " using 1300V PB definition.";
             m_protectionsChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC, theFamily);

             int currentIndex = ui->AllTabs->currentIndex();
             QString aCommand;
             QTabBar* bar=ui->AllTabs->tabBar();


             bar->setTabTextColor(currentIndex,Qt::blue);

             if (m_protectionsChangesTracked->getFETCountChanged() == true)
             {
                 ui->protectionsFETFailureCountLabel->setText(blueFont + protectionFETFailureCountStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getFETThresholdChanged() == true)
             {
                 ui->protectionsFETThresholdLabel->setText(blueFont + protectionFETFailureThresholdStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getFETDeltaCurrentChanged() == true)
             {
                 ui->protectionsFETDeltaCurrentLabel->setText(blueFont + protectionFETFailureDeltaCurrentStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getProtection1Changed() == true)
             {
                 ui->protectionsProtection1Label->setText(blueFont + protection1_1300VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getProtection2Changed() == true)
             {
                 ui->protectionsProtection2Label ->setText(blueFont + protection2_1300VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getProtection3Changed() == true)
             {
                 ui->protectionsProtection3Label->setText(blueFont + protection3_1300VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getProtection4Changed() == true)
             {
                 ui->protectionsProtection4Label->setText(blueFont + protection4_1300VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFTimer1Changed() == true)
             {
                 ui->protectionsAMF_Timer1Label->setText(blueFont + protection_AMF_Timer1Str + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFTimer2Changed() == true)
             {
                 ui->protectionsAMF_Timer2Label->setText(blueFont + protection_AMF_Timer2Str + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFV_OVChanged() == true)
             {
                 ui->protectionsAMF_V_OVLabel->setText(blueFont + protection_AMF_V_OV_Str + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFI_OCChanged() == true)
             {
                 ui->protectionsAMF_I_OCLabel->setText(blueFont + protection_AMF_I_OC_Str + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFMPPOffCyclesChanged() == true)
             {
                 ui->protectionsAMF_MPP_Off_CyclesLabel->setText(blueFont + protection_AMF_MPP_Cycles_Off_Str + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFMPPTimesOffChanged() == true)
             {
                 ui->protectionsAMF_MPP_TimesOffLabel->setText(blueFont + protection_AMF_MPP_Number_Of_Off_Cycles + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFDebugChanged() == true)
             {
                 ui->protectionsAMF_DebugLabel->setText(blueFont + protection_Debug_Monitoring_Str + endFont);
                 saveButtonState = true;
             }

         }
         else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
         {
             m_protectionsChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC, theFamily);

             int currentIndex = ui->AllTabs->currentIndex();
             QString aCommand;
             QTabBar* bar=ui->AllTabs->tabBar();

             qDebug() << Q_FUNC_INFO << " using 1300V PB definition.";

             bar->setTabTextColor(currentIndex,Qt::blue);

             if (m_protectionsChangesTracked->getProtection1Changed() == true)
             {
                 ui->protectionsProtection1Label->setText(blueFont + protection1_1500VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getProtection2Changed() == true)
             {
                 ui->protectionsProtection2Label ->setText(blueFont + protection2_1500VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getProtection3Changed() == true)
             {
                 ui->protectionsProtection3Label->setText(blueFont + protection3_1500VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getProtection4Changed() == true)
             {
                 ui->protectionsProtection4Label->setText(blueFont + protection4_1500VStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getEFInputCurrentThresholdChanged() == true)
             {
                 ui->protectionsEFInputCurrentThresholdLabel->setText(blueFont + protection_1500V_EFInputCurrentThresholdStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getEFOccurrenceThresholdChanged() == true)
             {
                 ui->protectionsEFOccurrenceThresholdLabel->setText(blueFont + protection_1500V_EFOccurrenceThresholdStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getEFCountDownTimerChanged() == true)
             {
                 ui->protectionsEFCountDownTimerLabel->setText(blueFont + protection_1500V_EFCountDownTimerStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getEFAlphaNumeratorChanged() == true)
             {
                 ui->protectionsEFAlphaNumeratorLabel->setText(blueFont + protection_1500V_EFAlphaNumeratorStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getAMFDebugChanged() == true)
             {
                 ui->protectionsAMF_DebugLabel->setText(blueFont + protection_Debug_Monitoring_Str + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getIinLimitChanged() == true)
             {
                 ui->protectionsIinLimitLabel->setText(blueFont + protection_1500V_30_IinLimitStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getIinLimitOCStepsChanged() == true)
             {
                 ui->protectionsIinLimitOCStepsLabel->setText(blueFont + protection_1500V_30_IinLimitOCStepsStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getIinLimitOCDelayChanged() == true)
             {
                 ui->protectionsIinLimitOCDelayLabel->setText(blueFont + protection_1500V_30_IinLimitOCDelayStr + endFont);
                 saveButtonState = true;
             }
             if (m_protectionsChangesTracked->getIinLimitTempAmbientAdjustChanged() == true)
             {
                 ui->protectionsIinLimitTempAmbientAdjustLabel->setText(blueFont + protection_1500V_30_IinLimitTempAmbientAdjustStr + endFont);
                 saveButtonState = true;
             }
         }
         else
         {
             QString errString(Q_FUNC_INFO);
             errString += " ERROR: " + CurrentDateTime + " protections for family " + theFamily + " not implemented yet.";
             emit publishError(errString);
             qDebug() << errString;
         }
         ui->protectionsSendPushButton->setEnabled(false);
         ui->protectionsSavePushButton->setEnabled(saveButtonState);
     }
     else
     {
         QString errString(Q_FUNC_INFO);
         errString += " ERROR: " + CurrentDateTime + " no current active MAC";
         emit publishError(errString);
         qDebug() << errString;
     }

 }

 void AmptGUI_X::handleRadioSendPushButton( void )
 {

     // qDebug() << Q_FUNC_INFO << " build commands to send, enable Save button";

     if (m_currentActiveMAC != "")
     {

         m_radioValueChangesTracked->sendAllChangedValuesToMemory(m_currentActiveMAC);

         int currentIndex = ui->AllTabs->currentIndex();
         QString aCommand;
         QTabBar* bar=ui->AllTabs->tabBar();
         bool saveButtonState = false;

         bar->setTabTextColor(currentIndex,Qt::blue);

         if (m_radioValueChangesTracked->getDFK0Changed())
         {

             ui->radioDFK0Label->setText(blueFont + radioDFK0Str + endFont);
             saveButtonState = true;
         }
         if (m_radioValueChangesTracked->getDFK1Changed())
         {

             ui->radioDFK1Label->setText(blueFont + radioDFK1Str + endFont);
             saveButtonState = true;
         }
         if (m_radioValueChangesTracked->getDFK2Changed())
         {

             ui->radioDFK2Label->setText(blueFont + radioDFK2Str + endFont);
             saveButtonState = true;
         }
         if (m_radioValueChangesTracked->getDFK3Changed())
         {

             ui->radioDFK3Label->setText(blueFont + radioDFK3Str + endFont);
             saveButtonState = true;
         }
         if (m_radioValueChangesTracked->getPureOffsetChanged())
         {

             ui->radioPureOffsetLabel->setText(blueFont + radioPureOffsetStr + endFont);
             saveButtonState = true;
         }
         if (m_radioValueChangesTracked->getLowCurrentLimitTo255Changed())
         {

             ui->radioLowCurrentLimitTo255Label->setText(blueFont + radioLowCurrentLimitTo255Str + endFont);
             saveButtonState = true;
         }


         ui->radioSendPushButton->setEnabled(false);
         ui->radioSavePushButton->setEnabled(saveButtonState);

     }
     else
     {
         QString errString(Q_FUNC_INFO);
         QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
         errString += " ERROR: " + CurrentDateTime + " no current active MAC";
         emit publishError(errString);
         qDebug() << errString;
     }
 }


 void AmptGUI_X::handleRadioDFK0DoubleSpinBoxChange(const double value)
 {
     // qDebug() << Q_FUNC_INFO << "value:" << QString::number(value);

     if (m_radioValueChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_radioValueChangesTracked->changeDFK0(value);

         // qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->radioDFK0Label->setText(redFont + radioDFK0Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->radioSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }

 }

 void AmptGUI_X::handleRadioDFK1DoubleSpinBoxChange(const double value)
 {
     // qDebug() << Q_FUNC_INFO << "value:" << QString::number(value);

     if (m_radioValueChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_radioValueChangesTracked->changeDFK1(value);

         // qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->radioDFK1Label->setText(redFont + radioDFK1Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->radioSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleRadioDFK2DoubleSpinBoxChange(const double value)
 {
     // qDebug() << Q_FUNC_INFO << "value:" << QString::number(value);

     if (m_radioValueChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_radioValueChangesTracked->changeDFK2(value);

         // qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->radioDFK2Label->setText(redFont + radioDFK2Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->radioSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleRadioDFK3DoubleSpinBoxChange(const double value)
 {
     // qDebug() << Q_FUNC_INFO << "value:" << QString::number(value);

     if (m_radioValueChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_radioValueChangesTracked->changeDFK3(value);

         // qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->radioDFK3Label->setText(redFont + radioDFK3Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->radioSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleRadioPureOffsetSpinBoxChange(const int value)
 {
     // qDebug() << Q_FUNC_INFO << "value:" << QString::number(value);

     if (m_radioValueChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_radioValueChangesTracked->changePureOffset(value);

         // qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->radioPureOffsetLabel->setText(redFont + radioPureOffsetStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->radioSendPushButton ->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleRadioLowCurrentLimitTo255SpinBoxChange(const int value)
 {
     // qDebug() << Q_FUNC_INFO << "value:" << QString::number(value);

     if (m_radioValueChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_radioValueChangesTracked->changeLowCurrentLimitTo255(value);

         // qDebug() << Q_FUNC_INFO << " changed to " << value;

         ui->radioLowCurrentLimitTo255Label->setText(redFont + radioPureOffsetStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->radioSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

void AmptGUI_X::handleNetworkEndOfTestPushButton( void )
{

    bool success = false;
    QString endOfTestCommand("s ");

    if (ui->commandRadioButtonBroadcast->isChecked())
    {
        endOfTestCommand += "* " + ByteRegister_EndOfTest + " b0\r\n";
        success = true;
    }
    else if (ui->commandRadioButtonMAC->isChecked())
    {
        if (m_currentActiveMAC != "")
        {
            endOfTestCommand += "m" + m_currentActiveMAC + " " + ByteRegister_EndOfTest + "b0\r\n";
            success = true;
        }
    }
    if (success == true)
    {
        qDebug() << " INFO: sending end of test command " << endOfTestCommand << " sent to gateway...";
        m_gatewayThread.handleGatewayCommandToSend(endOfTestCommand);
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " failed to successfully construct end of test command, not sent to gateway...";
        emit publishError(errString);
        qDebug() << errString;
    }


}
void AmptGUI_X::handleNetworkNCommandPushButton( void )
{
   qDebug() << Q_FUNC_INFO << " INFO: will send N command ...";
   QString aCommand("N m");

   aCommand += ui->networkNCommandMACLineEdit->text();
   aCommand += " ";
   aCommand += ui->networkNCommandArgumentLineEdit->text();
   qDebug() << Q_FUNC_INFO << " INFO: sending gateway command " << aCommand << " to gateway ...";
   sendGatewayCommandToGateway(aCommand);
   ui->networkNCommandPushButton->setEnabled(false);
   ui->networkNCommandMACLineEdit->clear();
   ui->networkNCommandArgumentLineEdit->clear();
}

void AmptGUI_X::handleNetworkNCommandArguments( QString text )
{
    // qDebug() << Q_FUNC_INFO << " INFO: check if NCommand Arguments are of correct length and values to enable NCommand push button, text is " << text;
    bool macLineReady = false;
    bool argLineReady = false;
    const QRegularExpression MAC_RE("[0-9|A-F|a-f]{12}");
    const QRegularExpression DATA_RE("5[0-9|A-F|a-f]{8}[0-9|A-E|a-e][0-9|A-F|a-f]{4}");
    static QRegularExpressionMatch match;

    QString macLine(ui->networkNCommandMACLineEdit->text());
    if (macLine.length() == 12)
    {
        match = MAC_RE.match(macLine);
        if (match.hasMatch())
        {
            qDebug() << Q_FUNC_INFO << " INFO: a valid MAC of " << macLine << " ready for N command...";
            macLineReady = true;
        }
        else
        {
            QString ErrorStr(Q_FUNC_INFO);
            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
            ErrorStr += " ERROR: " + CurrentDateTime + " A valid MAC address must consist of 12 hexadecimal characters [0-9|A-F|a-f]{12}, correct before N Command will be sent.";
            QMessageBox * badMACDialog = new QMessageBox(this);
            badMACDialog->setText(ErrorStr);
            emit publishError(ErrorStr);
            badMACDialog->exec();
            delete badMACDialog;
        }
    }
    if (macLineReady == true)
    {
        QString argLine(ui->networkNCommandArgumentLineEdit->text());
        if (argLine.length() == 14)
        {
            match = DATA_RE.match(argLine);
            if (match.hasMatch())
            {
                qDebug() << Q_FUNC_INFO << " INFO: a valid arg of " << argLine << " ready for N command...";
                argLineReady = true;
            }
            else
            {
                QString ErrorStr(Q_FUNC_INFO);
                QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                ErrorStr += " ERROR: " + CurrentDateTime + " A valid N Command Argument must consist of 14 characters, a 5, eight hexadecimal characters, hexadecimal character other than F|f, then 4 dexidecimal characters, 5[0-9|A-F|a-f]{8}[0-9|A-E|a-e][0-9|A-F|a-f]{4}, correct before N Command will be sent.";
                QMessageBox * badArgDialog = new QMessageBox(this);
                badArgDialog->setText(ErrorStr);
                emit publishError(ErrorStr);
                badArgDialog->exec();
                delete badArgDialog;
            }
        }
    }
    if ((macLineReady == false) || (argLineReady == false))
    {
        ui->networkNCommandPushButton->setEnabled(false);
    }
    else
    {
        ui->networkNCommandPushButton->setEnabled(true);
    }

}
 void AmptGUI_X::handleNetworkDisbandNetworkPushButton( void )
 {
     QString disbandNetworkCommand("n\r\n");
     qDebug() << Q_FUNC_INFO << " INFO: sending join command:" << disbandNetworkCommand << " to gateway.";
     // m_gatewayThread.handleGatewayCommandToSend(disbandNetworkCommand);
 }

 void AmptGUI_X::handleNetworkEnableJoinPushButton( void )
 {
     QString joinCommand("j h1\r\n");
     qDebug() << Q_FUNC_INFO << " INFO: sending join command:" << joinCommand << " to gateway.";
     m_gatewayThread.handleGatewayCommandToSend(joinCommand);
 }

 void AmptGUI_X::handleNetworkDisableJoinPushButton( void )
 {
     QString joinCommand("j s1\r\n");
     qDebug() << Q_FUNC_INFO << " INFO: sending  end join command:" << joinCommand << " to gateway.";
     m_gatewayThread.handleGatewayCommandToSend(joinCommand);
 }

 void AmptGUI_X::handleResetKeys( void )
 {
     // qDebug() << Q_FUNC_INFO;

     ui->keysNetworkKeyandIVLabel->setEnabled(false);
     ui->keysEDPrivateKeyAndIVLabel->setEnabled(false);

     ui->keysNetworkKeyLineEdit->setEnabled(false);
     ui->keysNetworkKeyLineEdit->setText(Blank);
     ui->keysNetworkIVLineEdit->setEnabled(false);
     ui->keysNetworkIVLineEdit->setText(Blank);

     ui->keysEDPrivateKeyLineEdit->setEnabled(false);
     ui->keysEDPrivateKeyLineEdit->setText(Blank);
     ui->keysEDPrivateIVLineEdit->setEnabled(false);
     ui->keysEDPrivateIVLineEdit->setText(Blank);

     ui->KeysPushButton->setEnabled(false);
     ui->keysSetGatewayKeyIVRadioButton->setEnabled(false);
     ui->keysSetEDKeyIVRadioButton->setEnabled(false);
     ui->keysObtainDefaultsRadioButton->setEnabled(false);
 }


 void AmptGUI_X::handleResetVersionInfo( void )
 {
     ui->versionVersionHighLabel->setText(greyFont + versionVersionHighStr + endFont);
     ui->versionVersionHighDataLabel->setEnabled(false);
     ui->versionVersionHighDataLabel->setText(Blank);

     ui->versionVersionLowLabel->setText(greyFont + versionVersionLowStr + endFont);
     ui->versionVersionLowDataLabel->setEnabled(false);
     ui->versionVersionLowDataLabel->setText(Blank);

     ui->versionCommissionedLabel->setText(greyFont + versionCommissionedStr + endFont);
     ui->versionCommissionedDateTimeEdit->setEnabled(false);

     ui->versionShuntLabel->setText(greyFont + versionShuntStr + endFont);
     ui->versionShuntDataLabel->setEnabled(false);
     ui->versionShuntDataLabel->setText(Blank);

     ui->versionSKUHighLabel->setText(greyFont + versionSKUHighStr + endFont);
     ui->versionSKUHighDataLabel->setEnabled(false);
     ui->versionSKUHighDataLabel->setText(Blank);

     ui->versionSKULowLabel->setText(greyFont + versionSKULowStr + endFont);
     ui->versionSKULowDataLabel->setEnabled(false);
     ui->versionSKULowDataLabel->setText(Blank);

     ui->versionVersionSuffix1Label->setText(greyFont + versionVersionSuffix1Str + endFont);
     ui->versionVersionSuffix1DataLabel->setEnabled(false);
     ui->versionVersionSuffix1DataLabel->setText(Blank);

     ui->versionVersionSuffix2Label->setText(greyFont + versionVersionSuffix2Str + endFont);
     ui->versionVersionSuffix2DataLabel->setEnabled(false);
     ui->versionVersionSuffix2DataLabel->setText(Blank);

     ui->versionVersionSuffix3Label->setText(greyFont + versionVersionSuffix3Str + endFont);
     ui->versionVersionSuffix3DataLabel->setEnabled(false);
     ui->versionVersionSuffix3DataLabel->setText(Blank);
 }

 void AmptGUI_X::handleResetOutput( void )
 {
     ui->outputStartOutputPushButton->setEnabled(true);
     ui->outputStopOutputPushButton->setEnabled(false);
 }

 void  AmptGUI_X::handleResetCoeffsLine( void )
 {
    ui->macReadCoeffsVoutCoeff->setEnabled(false);
    ui->macReadCoeffsVoutCoeff->setText("");
    ui->macReadCoeffsVin1Coeff->setEnabled(false);
    ui->macReadCoeffsVin1Coeff->setText("");
    ui->macReadCoeffsIoutCoeff->setEnabled(false);
    ui->macReadCoeffsIoutCoeff->setText("");
    ui->macReadCoeffsVin2Coeff->setEnabled(false);
    ui->macReadCoeffsVin2Coeff->setText("");
    ui->macReadCoeffsIin2Coeff->setEnabled(false);
    ui->macReadCoeffsIin2Coeff->setText("");
    ui->macReadCoeffsIin1Coeff->setEnabled(false);
    ui->macReadCoeffsIin1Coeff->setText("");
    ui->macReadCOeffsVoutOffset->setEnabled(false);
    ui->macReadCOeffsVoutOffset->setText("");
    ui->macReadCOeffsIoutOffset->setEnabled(false);
    ui->macReadCOeffsIoutOffset->setText("");
    ui->macReadCOeffsIin2Offset->setEnabled(false);
    ui->macReadCOeffsIin2Offset->setText("");
    ui->macReadCOeffsIin1Offset->setEnabled(false);
    ui->macReadCOeffsIin1Offset->setText("");
    ui->macReadCoeffsDFK3->setEnabled(false);
    ui->macReadCoeffsDFK3->setText("");
    ui->macReadCoeffsOV->setEnabled(false);
    ui->macReadCoeffsOV->setText("");
    ui->macReadCoeffsOC->setEnabled(false);
    ui->macReadCoeffsOC->setText("");

 }

 void AmptGUI_X::handleResetEDSettings( void )
 {
     QString tFontColor = blackFont;

     m_edSettingsChangesTracked->setIgnoreSignals(true);

     if (ResetParameterBlockValues == true)
     {
         tFontColor = greyFont;
     }

     ui->edSettingsSyncFrequencySpinBox->setEnabled(false);
     ui->edSettingsSyncFrequencySpinBox->setValue(0);

     ui->edSettingsSyncPhaseSpinBox->setEnabled(false);
     ui->edSettingsSyncPhaseSpinBox->setValue(0);

     ui->edSettingsSyncFrequencyLabel->setText(tFontColor + edSettingsSyncFrequencyStr + endFont);
     ui->edSettingsSyncPhaseLabel->setText(tFontColor + edSettingsSyncPhaseStr + endFont);
     ui->edSettingsOptimizerFamilyLabel->setText(tFontColor + edSettingsOptimizerFamilyStr + endFont);


     /* 'Fusing parameters are always not active at the moment. */
     ui->edSettingsFuseCommsSpinBox->setEnabled(false);
     ui->edSettingsFuseCommsSpinBox->setValue(0);
     ui->edSettingsFuseCommsLabel->setText(greyFont + edSettingsFuseCommunicationsStr + endFont);

     ui->edSettingsFuseElectricalSpinBox->setEnabled(false);
     ui->edSettingsFuseElectricalSpinBox->setValue(0);
     ui->edSettingsFuseElectricalLabel->setText(greyFont + edSettingsFuseElectricalStr + endFont);



     ui->edSettingsSendPushButton->setEnabled(false);
     ui->edSettingsSavePushButton->setEnabled(false);

     m_edSettingsChangesTracked->setIgnoreSignals(false);
 }

 void AmptGUI_X::handleResetEDComms( void )
 {
     qDebug() << Q_FUNC_INFO;

     QString tFontColor = blackFont;

     m_edCommsChangesTracked->setIgnoreSignals(true);

     if (ResetParameterBlockValues == true)
     {
         tFontColor = greyFont;

         ui->edCommsNetIDSpinBox->setEnabled(false);
         ui->edCommsNetIDSpinBox->setValue(zero);

         ui->edCommsBunchSpinBox->setEnabled(false);
         ui->edCommsBunchSpinBox->setValue(zero);

         ui->edCommsGroupSpinBox->setEnabled(false);
         ui->edCommsGroupSpinBox->setValue(zero);

         ui->edCommsSyncWordSpinBox->setEnabled(false);
         ui->edCommsSyncWordSpinBox->setValue(zero);

         ui->edCommsRBunchSpinBox->setEnabled(false);
         ui->edCommsRBunchSpinBox->setValue(zero);

         ui->edCommsGBunchSpinBox->setEnabled(false);
         ui->edCommsGBunchSpinBox->setValue(zero);

         ui->edCommsChannelSpinBox->setEnabled(false);
         ui->edCommsChannelSpinBox->setValue(zero);

         ui->edCommsRadioPowerSpinBox->setEnabled(false);
         ui->edCommsRadioPowerSpinBox->setValue(zero);

         ui->edCommsGatewayAddressSpinBox->setEnabled(false);
         ui->edCommsGatewayAddressSpinBox->setValue(zero);

         ui->edCommsEndDeviceAddressSpinBox->setEnabled(false);
         ui->edCommsEndDeviceAddressSpinBox->setValue(zero);

         ui->edComms2RepeaterChannelSpinBox->setEnabled(false);
         ui->edComms2RepeaterChannelSpinBox->setValue(zero);

         ui->edComms2RepeaterPowerSpinBox->setEnabled(false);
         ui->edComms2RepeaterPowerSpinBox->setValue(zero);

         ui->edComms2RepeaterSpinBox->setEnabled(false);
         ui->edComms2RepeaterSpinBox->setValue(zero);

         ui->edComms2SlaveSpinBox->setEnabled(false);
         ui->edComms2SlaveSpinBox->setValue(zero);

         ui->edCommsHoppingAllowedSpinBox->setEnabled(false);
         ui->edCommsHoppingAllowedSpinBox->setValue(zero);

         ui->edComms2SlaveChannelSpinBox->setEnabled(false);
         ui->edComms2SlaveChannelSpinBox->setValue(zero);

         ui->edComms12KbodSpinBox->setEnabled(false);
         ui->edComms12KbodSpinBox->setValue(zero);

         ui->edComms2SearchSpinBox->setEnabled(false);
         ui->edComms2SearchSpinBox->setValue(zero);

         ui->edComms2CriticalLevel10SpinBox->setEnabled(false);
         ui->edComms2CriticalLevel10SpinBox->setValue(zero);

         ui->edComms2CriticalLevel500SpinBox->setEnabled(false);
         ui->edComms2CriticalLevel500SpinBox->setValue(zero);

         ui->edCommsGatewayChannelFlagSpinBox->setEnabled(false);
         ui->edCommsGatewayChannelFlagSpinBox->setValue(zero);

         ui->edCommsStayInRXSpinBox->setEnabled(false);
         ui->edCommsStayInRXSpinBox->setValue(zero);

         ui->edCommsStayInCWSpinBox->setEnabled(false);
         ui->edCommsStayInCWSpinBox->setValue(zero);

         ui->edComms2250KbodSpinBox->setEnabled(false);
         ui->edComms2250KbodSpinBox->setValue(zero);
     }

     ui->edCommsNetIDLabel->setText(tFontColor + edCommsNetIDStr + endFont);
     ui->edCommsBunchLabel->setText(tFontColor + edCommsBunchStr + endFont);
     ui->edCommsGroupLabel->setText(tFontColor + edCommsGroupStr + endFont);
     ui->edCommsSyncWordLabel->setText(tFontColor + edCommsSyncWordStr + endFont);
     ui->edCommsRBunchLabel->setText(tFontColor + edCommsRBunchStr + endFont);
     ui->edCommsGBunchLabel->setText(tFontColor + edCommsGBunchStr + endFont);
     ui->edCommsChannelLabel->setText(tFontColor + edCommsChannelStr + endFont);
     ui->edCommsRadioPowerLabel->setText(tFontColor + edCommsRadioPowerStr + endFont);
     ui->edCommsGatewayEdAddressLabel->setText(tFontColor + edCommsGatewayEDAddressStr + endFont);
     ui->edCommsGatewayChannelFlagLabel->setText(tFontColor + edCommsGatewayChannelFlagStr + endFont);
     ui->edCommsStayInRXLabel->setText(tFontColor + edCommsStayInRXStr + endFont);
     ui->edCommsStayInCWLabel->setText(tFontColor + edCommsStayInCWStr + endFont);
     ui->edComms2250KbodLabel->setText(greyFont + edComms2250KbodStr + endFont);

     ui->edComms2RepeaterChannelLabel->setText(tFontColor + edComms2RepeaterChannelStr + endFont);
     ui->edComms2RepeaterPowerLabel->setText(tFontColor + edComms2RepeaterPowerStr + endFont);
     ui->edComms2RepeaterLabel->setText(tFontColor + edComms2RepeaterStr + endFont);
     ui->edComms2SlaveLabel->setText(tFontColor + edComms2SlaveStr + endFont);
     ui->edCommsHoppingAllowedLabel->setText(tFontColor + edCommsHoppingStr + endFont);
     ui->edComms2SlaveChannelLabel->setText(tFontColor + edComms2SlaveChannelStr + endFont);
     ui->edComms12KbodLabel->setText(tFontColor + edComms12KbodStr + endFont);
     ui->edComms2SeachLabel->setText(tFontColor + edComms2SearchEnabledStr + endFont);
     ui->edComms2CriticalLevel10Label->setText(tFontColor + edComms2CriticalLevel10Str + endFont);
     ui->edComms2CriticalLevel500Label->setText(tFontColor + edComms2CriticalLevel500Str + endFont);

     ui->edCommsSendPushButton->setEnabled(false);
     ui->edCommsSavePushButton->setEnabled(false);
     ui->edComms2SendPushButton->setEnabled(false);
     ui->edComms2SavePushButton->setEnabled(false);

     m_edCommsChangesTracked->setIgnoreSignals(false);

 }

 void AmptGUI_X::handleEDCommsChannelValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         qDebug() << Q_FUNC_INFO << " acting on signal.";
         m_edCommsChangesTracked->changeChannel(s);

         qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsChannelLabel->setText(redFont + edCommsChannelStr + endFont);

         // currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(EDCommsTabIndex, Qt::red);
         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsGatewayAddressValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         m_edCommsChangesTracked->changeGatewayAddress(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsGatewayEdAddressLabel->setText(redFont + edCommsGatewayEDAddressStr + endFont);

         // currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(EDCommsTabIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsEndDeviceAddressValueChanged(int s)
     {
         // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

         if (m_edCommsChangesTracked->getIgnoreSignals() == false)
         {
             // qDebug() << Q_FUNC_INFO << " acting on signal.";
             m_edCommsChangesTracked->changeEndDeviceAddress(s);

             // qDebug() << Q_FUNC_INFO << " changed to " << s;

             ui->edCommsGatewayEdAddressLabel->setText(redFont + edCommsGatewayEDAddressStr + endFont);

             // currentIndex = ui->AllTabs->currentIndex();
             // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
             QTabBar* bar=ui->AllTabs->tabBar();
             bar->setTabTextColor(EDCommsTabIndex, Qt::red);

             ui->edCommsSendPushButton->setEnabled(true);
         }
         else
         {
             // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
         }
 }

 void AmptGUI_X::handleEDCommsBunchValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeBunch(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsBunchLabel->setText(redFont + edCommsBunchStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsNetIDValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeNetID(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsNetIDLabel->setText(redFont + edCommsNetIDStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsGroupValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeGroup(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsGroupLabel->setText(redFont + edCommsGroupStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsGBunchValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeGBunch(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsGBunchLabel->setText(redFont + edCommsGBunchStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsRBunchValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeRBunch(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsRBunchLabel->setText(redFont + edCommsRBunchStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsHoppingValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeHopping(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsHoppingAllowedLabel->setText(redFont + edCommsHoppingStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
}

 void AmptGUI_X::handleEDCommsRadioPowerValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeRadioPower(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsRadioPowerLabel->setText(redFont + edCommsRadioPowerStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsGWChannelFlagValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeGWChannelFlag(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsGatewayChannelFlagLabel->setText(redFont + edCommsGatewayChannelFlagStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }


 void AmptGUI_X::handleEDCommsSyncWordValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeSyncWord(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsSyncWordLabel->setText(redFont + edCommsSyncWordStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms12KbodValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->change12Kbod(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms12KbodLabel->setText(redFont + edComms12KbodStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsStayInRXValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeStayInRX(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsStayInRXLabel->setText(redFont + edCommsStayInRXStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDCommsStayInCWValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeStayInCW(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edCommsStayInCWLabel->setText(redFont + edCommsStayInCWStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edCommsSendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2RepeaterValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeRepeater(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2RepeaterLabel->setText(redFont + edComms2RepeaterStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2RepeaterPowerValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeRepeaterPower(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2RepeaterPowerLabel->setText(redFont + edComms2RepeaterPowerStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2RepeaterChannelValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;
         m_edCommsChangesTracked->changeRepeaterChannel(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2RepeaterChannelLabel->setText(redFont + edComms2RepeaterChannelStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2SearchEnabledValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;

         m_edCommsChangesTracked->changeSearchEnabled(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2SeachLabel->setText(redFont + edComms2SearchEnabledStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2CriticalLevel10ValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;

         m_edCommsChangesTracked->changeCriticalLevel10(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2CriticalLevel10Label->setText(redFont + edComms2CriticalLevel10Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2CriticalLevel500ValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;

         m_edCommsChangesTracked->changeCriticalLevel500(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2CriticalLevel500Label->setText(redFont + edComms2CriticalLevel500Str + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2SlaveValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;

         m_edCommsChangesTracked->changeSlave(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2SlaveLabel->setText(redFont + edComms2SlaveStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2SlaveChannelValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;

         m_edCommsChangesTracked->changeSlaveChannel(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2SlaveChannelLabel->setText(redFont + edComms2SlaveChannelStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleEDComms2250KbodValueChanged(int s)
 {
     // qDebug() << Q_FUNC_INFO << " value:" << QString::number(s);

     if (m_edCommsChangesTracked->getIgnoreSignals() == false)
     {
         // qDebug() << Q_FUNC_INFO << " acting on signal.";
         int currentIndex = 0;

         m_edCommsChangesTracked->change250Kbod(s);

         // qDebug() << Q_FUNC_INFO << " changed to " << s;

         ui->edComms2250KbodLabel->setText(redFont + edComms2250KbodStr + endFont);

         currentIndex = ui->AllTabs->currentIndex();
         // qDebug() << Q_FUNC_INFO << " current TAB index:" << currentIndex;
         QTabBar* bar=ui->AllTabs->tabBar();
         bar->setTabTextColor(currentIndex, Qt::red);

         ui->edComms2SendPushButton->setEnabled(true);
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " ignoring signal to change value.";
     }
 }

 void AmptGUI_X::handleCommandLineReturnPressed( void )
 {
     qDebug() << Q_FUNC_INFO << ui->commandLineEdit->text();
     sendCommandToGatewayFromCommandLine();
 }

 void AmptGUI_X::handleValidateCommandToCheck(const QString prompt, const QString command)
 {
     int retVal = 0;
     QString informationText("Command to Send: ");
     informationText += command;

     msgBox = new QMessageBox;
     msgBox->setWindowTitle("Confirm Command to Send To Gateway");
     msgBox->setText(prompt);
     msgBox->setInformativeText(informationText);
     msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
     msgBox->setDefaultButton(QMessageBox::Ok);
     msgBox->setIcon(QMessageBox::Question);
     msgBox->setModal(true);

     retVal = msgBox->exec();
     if (retVal == QMessageBox::Ok)
     {
         qDebug() << Q_FUNC_INFO << " user validated to send command:" << command << " to gateway.";
         m_gatewayThread.handleGatewayCommandToSend(command);
     }
     else
     {
         qDebug() << Q_FUNC_INFO << " user decided not to send command:" << command << " to gateway.";
     }
 }

  void AmptGUI_X::handleBeginReadingEndDeviceParameterBlock(const QString what)
  {
      qDebug() << Q_FUNC_INFO << " for " << what;
      // if timer is NULL
      // Get Bunch Size, Network Size, compute math of timer duration, set up and start timer.
      // ELSE output timer not NULL

      if (m_parameterBlockThreadTimer == nullptr)
      {
          // qDebug() << " starting Parameter Block Reading timer for " << what;

          int bunchSize = ui->gatewayBunchSizeSpinBox->value();
          int networkSize = ui->gatewayNetworkSizeSpinBox->value();

          /* Next two checks are in case gateway bunch and network size have not been received. */
          if ((bunchSize < 1) || (networkSize < 1))
          {
              qDebug() << Q_FUNC_INFO << " INFO: Sending i command because either bunchSize or networkSize is < 1";
              qDebug() << Q_FUNC_INFO << " INFO: Temporarily setting bunchSize to 16 and networkSize to 31";
              bunchSize = 16;
              networkSize = 31;
              m_gatewayThread.commandToSend("?\r\n"); // Try to get information from gateway, bunchsize should not be less than 1.
          }

          // 40 milliseconds per slot in bunch + 80 milliseconds "housekeeping", * the number of bunches, LBC should be times number of calibration repeats, put 40
          int timerDurationInMilliseconds = ((((40 * bunchSize) + 80) * (networkSize/bunchSize + 1))* 40) + 2000;

          m_parameterBlockThreadTimer = new amptTimer(true);
          m_parameterBlockThreadTimer->setIntervalAndStart(timerDurationInMilliseconds);
          m_parameterBlockThreadTimerID = m_parameterBlockThreadTimer->timer->timerId();

          // qDebug() << Q_FUNC_INFO << " amptTimer running " << m_parameterBlockThreadTimer->timer->isActive();
          qDebug() << Q_FUNC_INFO << " amptTimer single shot " << m_parameterBlockThreadTimer->timer->isSingleShot()
                      << " amptTimer is running, time remaining is " << m_parameterBlockThreadTimer->timer->remainingTime()
                      << " timerID:" << m_parameterBlockThreadTimerID;

          emit publishReadParameterBlockTimerStarted();
          connect(m_parameterBlockThreadTimer, SIGNAL(amptTimerExpired(const int)), this, SLOT(handleReadingEndDeviceParameterBlockTimeout( const int )));

      }
      else
      {
          QString ErrorStr(Q_FUNC_INFO);
          QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
          ErrorStr += " ERROR: " + CurrentDateTime + " An timer for reading end device parameter blocks is already running, new one not created...";
          qDebug() << ErrorStr;
          emit publishError(ErrorStr);
      }
  }

  void AmptGUI_X::handleReadingEndDeviceParameterBlockTimeout( const int timerID )
  {
      QString ErrorStr(Q_FUNC_INFO);
      QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
      ErrorStr += " ERROR: " + CurrentDateTime +" timer ID:" + QString::number(timerID) + " expired.";

      qDebug() << ErrorStr;
      publishError(ErrorStr);

      if ((m_parameterBlockThreadTimer != nullptr) && (timerID == m_parameterBlockThreadTimerID))
      {
          qDebug() << Q_FUNC_INFO << " publishReadParameterBlockTimeout emited.";
          emit publishReadParameterBlockTimeout();
          disconnect(m_parameterBlockThreadTimer, SIGNAL(amptTimerExpired(const int)), this, SLOT(handleReadingEndDeviceParameterBlockTimeout( const int )));
          m_parameterBlockThreadTimerID = -1;
          delete m_parameterBlockThreadTimer;
          m_parameterBlockThreadTimer = nullptr;

      }
      else
      {
          qDebug() << Q_FUNC_INFO << " unmatched timerID, received:" << timerID << " readPBTimerID:" << m_parameterBlockThreadTimerID;
      }
      // LBC Here need to decide to keep reading or error out. ?? How to do, look at how many lines read what is missing?

  }

void AmptGUI_X::handleEndDeviceParameterBlockReadSuccessful( void )
{
    // qDebug() << Q_FUNC_INFO << " ### ### ### ### 555 will clean up and remove timer ..."; // LBC stop it first, then delete?
    if (m_parameterBlockThreadTimer != nullptr)
    {
        //int remainingTime = m_parameterBlockThreadTimer->timer->remainingTime();
        disconnect(m_parameterBlockThreadTimer, SIGNAL(amptTimerExpired(const int)), this, SLOT(handleReadingEndDeviceParameterBlockTimeout( const int )));
        delete m_parameterBlockThreadTimer;
        // qDebug() << Q_FUNC_INFO << " read parameter block timer deleted..., remaining time in timer was " << QString::number(remainingTime) << " milliseconds.";
        m_parameterBlockThreadTimer = nullptr;
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        ErrorStr += " ERROR: " + CurrentDateTime + " request to delete Parameter Block Timer which does not exist ... ";
        qDebug() << ErrorStr;
        emit publishError(ErrorStr);
    }
}

void AmptGUI_X::handleEndDeviceOnMainImage(QString mac, bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& entering with mac " << mac << " on main image => " << QString::number(s);
    if (s == true)
    {
        mainImage[mac] = "1";
    }
    else
    {
        mainImage[mac] = "0";
    }
    // qDebug() << Q_FUNC_INFO << " INFO: exiting with mainImage[mac] => " << mainImage[mac];
}

void AmptGUI_X::handleStartOutputPushButton( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: enter ...";
    QString ErrorStr(Q_FUNC_INFO);
    bool outputSelected = false;
    int nMode = 0;

    /* Can log to both CSV and Raw data to files */

    if (ui->outputOutputLongFormatOTADataCheckBox->isChecked() == true)
    {
        ErrorStr += " ERROR: output to file(s) (raw or csv) only occurs when short format data is being used. (Uncheck Long Format OTA Data (Output Tab))";
        QMessageBox * uncheckLogFormatDialog = new QMessageBox(this);
        uncheckLogFormatDialog->setText(ErrorStr);
        nMode = uncheckLogFormatDialog->exec();
        delete uncheckLogFormatDialog;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " INFO: Not using Long Format ...";
        if (ui->outputFilterOutputCSVFileCheckBox->isChecked() == true)
        {
            if ((ui->outputOutputCSVFileLineEdit->text()).length() == 0)
            {
                qDebug() << " INFO: need to pop up dialog to get path/file to log CSV to...";

                QFileDialog * csvFileDialog =  new QFileDialog(this,"Directory and Filename for CSV Output",QDir::rootPath());
                nMode = csvFileDialog->exec();
                qDebug() << Q_FUNC_INFO << " INFO: nMode = " << nMode;
                QStringList strlist = csvFileDialog->selectedFiles();
                qDebug() << Q_FUNC_INFO << " INFO: selectedFiles " << strlist << " number of files:" <<strlist.size();
                if (strlist.size() > 0)
                {
                    emit publishStartOutputCSVFile(strlist.at(0));
                    //ui->outputStopOutputPushButton->setEnabled(true);
                    //ui->outputStartOutputPushButton->setEnabled(false);
                    outputSelected = true;
                }
                else
                {
                    qDebug() << Q_FUNC_INFO << " INFO: no CSV output file indicated or returned ...";
                }
            }
            else
            {
                QString CSVfile = ui->outputOutputCSVFileLineEdit->text();
                qDebug() << Q_FUNC_INFO << " INFO: outputOutputCSVFileLineEdit is not empty: " << CSVfile;
                QString HomeAndCSV = QDir::homePath() + "/" + CSVfile;
                qDebug() << Q_FUNC_INFO << " INFO: outputOutputCSVFileLineEdit is not empty: " << CSVfile << " will write to " << HomeAndCSV;
                emit publishStartOutputCSVFile(HomeAndCSV);

                //ui->outputStopOutputPushButton->setEnabled(true);
                //ui->outputStartOutputPushButton->setEnabled(false);
                outputSelected = true;
            }
        }

        if (ui->outputFilterOutputRawFileCheckBox->isChecked() == true)
        {
            outputSelected = true;
            if ((ui->outputOutputRawFileLineEdit->text()).length() == 0)
            {
                qDebug() << " INFO: need to pop up dialog to get path/file to log to...";

                QFileDialog * rawFileDialog =  new QFileDialog(this,"Directory and Filename for Raw Output",QDir::rootPath());
                int nMode = rawFileDialog->exec();
                qDebug() << Q_FUNC_INFO << " INFO: nMode = " << nMode;
                QStringList strlist = rawFileDialog->selectedFiles();
                qDebug() << Q_FUNC_INFO << " INFO: selectedFiles " << strlist << " number of files:" <<strlist.size() << " nMode=" << nMode;

                if (strlist.size() > 0)
                {
                    emit publishStartOutputRawFile(strlist.at(0));
                    //ui->outputStopOutputPushButton->setEnabled(true);
                    //ui->outputStartOutputPushButton->setEnabled(false);
                    /*
                    if ( fileExists(strlist.at(0)) == true)
                    {
                        qDebug() << Q_FUNC_INFO << " INFO: file " << strlist.at(0) << " exists.";
                    }
                    else
                    {
                        qDebug() << Q_FUNC_INFO << " INFO: file " << strlist.at(0) << " does not exist.";
                        // create file, open for writing
                        // send signal to parseOTAdataThread to start logging to named file
                        // create signal handler in parseOTADataThread to handle signal
                    }
                    */
                }
                else
                {
                    qDebug() << Q_FUNC_INFO << " INFO: no RAW output file indicated or returned ...";
                }
            }
            else
            {
                QString Rawfile = ui->outputOutputRawFileLineEdit->text();
                QString HomeAndRaw = QDir::homePath() + "/" + Rawfile;
                qDebug() << Q_FUNC_INFO << " INFO: outputOutputRawFileLineEdit is not empty: " << Rawfile << " will write to " << HomeAndRaw;
                // emit publishStartOutputRawFile(ui->outputOutputRawFileLineEdit->text());
                emit publishStartOutputRawFile(HomeAndRaw);

                //ui->outputStopOutputPushButton->setEnabled(true);
                //ui->outputStartOutputPushButton->setEnabled(false);
            }
        }

    }
    if (outputSelected == false)
    {
        ErrorStr += " ERROR: no output file (CSV or Raw) selected, no output will be generated or saved.";
        publishLogCommandsToOutput(false);
        qDebug() << ErrorStr;
        emit publishError(ErrorStr);
    }
    else
    {
        if (ui->outputIncludeCommandsInLogCheckBox->isChecked() == true)
        {
            emit publishLogCommandsToOutput( true );
        }
        ui->outputOutputLongFormatOTADataCheckBox->setEnabled(false);
    }
    // qDebug() << Q_FUNC_INFO << " exiting ...";
}

void AmptGUI_X::handleStopOutputPushButton( void )
{
    qDebug() << Q_FUNC_INFO << " enter ...";
    emit publishStopOutputFiles();
    emit publishLogCommandsToOutput(false);
    ui->outputStopOutputPushButton->setEnabled(false);
    ui->outputStartOutputPushButton->setEnabled(true);
    ui->outputOutputLongFormatOTADataCheckBox->setEnabled(true);
    qDebug() << Q_FUNC_INFO << " exit ...";
}

void AmptGUI_X::handleOutputReady( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: output buttons being set for output...";
    ui->outputStopOutputPushButton->setEnabled(true);
    ui->outputStartOutputPushButton->setEnabled(false);
    ui->outputOutputLongFormatOTADataCheckBox->setEnabled(false);
}

void AmptGUI_X::handleCSVFileOpenFailed(const QString s)
{
    QMessageBox * probConfirmDialog = new QMessageBox(this);
    probConfirmDialog->setText(s);
    /*QAbstractButton* pButtonOk = */  probConfirmDialog->addButton(tr("OK"), QMessageBox::YesRole);
    probConfirmDialog->exec();
    delete probConfirmDialog;
}

void AmptGUI_X::handleRawFileOpenFailed(const QString s)
{
    QMessageBox * probConfirmDialog = new QMessageBox(this);
    probConfirmDialog->setText(s);
    /*QAbstractButton* pButtonOk = */  probConfirmDialog->addButton(tr("OK"), QMessageBox::YesRole);
    probConfirmDialog->exec();
    delete probConfirmDialog;
}

void AmptGUI_X::handleOutputSortOTATableRadioButtonNoneClicked( const bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO:&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& " << s;
    if (s == true)
    {
        m_outputSortOTATableBy = OutputSortOTATableByNone;
        handleClearHistoryPushButton();
    }
}

void AmptGUI_X::handleOutputSortOTATableRadioButtonSerialNumberClicked( const bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: " << s;
    if (s == true)
    {
        m_outputSortOTATableBy = OutputSortOTATableBySerialNumber;
        handleClearHistoryPushButton();
    }
}

void AmptGUI_X::handleOutputSortOTATableRadioButtonMACClicked( const bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: " << s;
    if (s == true)
    {
        m_outputSortOTATableBy = OutputSortOTATableByMAC;
        handleClearHistoryPushButton();
    }
}

void AmptGUI_X::handleOutputSortOTATableRadioButtonNetworkClicked( const bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: " << s;
    if (s == true)
    {
        m_outputSortOTATableBy = OutputSortOTATableByNetwork;
        handleClearHistoryPushButton();
    }

}

void AmptGUI_X::handleOutputSortOTATableAscendingCheckBoxClicked(int s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: " << s;

    // bool prev = m_outputSortOTATableAscending;
    if (s == 2)
    {
        m_outputSortOTATableAscending = true;
    }
    else
    {
        m_outputSortOTATableAscending = false;
    }
    // qDebug() << Q_FUNC_INFO << " INFO: received " << QString::number(s) << " m_outputSortOTATableAscending was " << prev << " now set to " << m_outputSortOTATableAscending;
}

void AmptGUI_X::handleSimple( void )
{
    qDebug() << Q_FUNC_INFO << " GOT THE SIMPLE ONE.";
}

void AmptGUI_X::handleOptimizerFamilyShunt( int s )
{
    qDebug() << Q_FUNC_INFO << " int = " << s;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString tStr(Q_FUNC_INFO);

   optimizerFamilyComboBoxShuntToIndexMapIter = optimizerFamilyComboBoxShuntToIndexMap.find(s);
   if (optimizerFamilyComboBoxShuntToIndexMapIter != optimizerFamilyComboBoxShuntToIndexMap.end())
   {
       if (ui->edSettingsOptimizerFamilyComboBox->currentIndex() != optimizerFamilyComboBoxShuntToIndexMapIter.value())
       {
           ui->edSettingsOptimizerFamilyComboBox->setCurrentIndex(optimizerFamilyComboBoxShuntToIndexMapIter.value());
           tStr += " INFO: (1) " + CurrentDateTime + " changed the selected optimizer family to familyShuntIndex of " + QString::number(optimizerFamilyComboBoxShuntToIndexMapIter.value());
           qDebug() << tStr;
           publishError(tStr);
       }
       else
       {
           tStr += " INFO: " + CurrentDateTime + " selected optimizer family matches familyShuntIndex of " + QString::number(optimizerFamilyComboBoxShuntToIndexMapIter.value());
           qDebug() << tStr;
           publishError(tStr);
       }
   }
   else
   {
       tStr += " ERROR: Unknown family value " + QString(s) + " received, cannot check optimizer family";
       qDebug() << tStr;
       emit publishError(tStr);
   }
   return;
}

void AmptGUI_X::handleOptimizerFamilyChanged( const QString & mac, const int & familyShuntIndex )
{
    qDebug() << Q_FUNC_INFO << " begin received optimizer family index of " << familyShuntIndex << " for mac " << mac;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString tStr(Q_FUNC_INFO);

    if (m_currentActiveMAC == mac)
    {
        optimizerFamilyComboBoxShuntToIndexMapIter = optimizerFamilyComboBoxShuntToIndexMap.find(familyShuntIndex);
        if (optimizerFamilyComboBoxShuntToIndexMapIter != optimizerFamilyComboBoxShuntToIndexMap.end())
        {
            if (ui->edSettingsOptimizerFamilyComboBox->currentIndex() != optimizerFamilyComboBoxShuntToIndexMapIter.value())
            {
                ui->edSettingsOptimizerFamilyComboBox->setCurrentIndex(optimizerFamilyComboBoxShuntToIndexMapIter.value());
                tStr += " INFO: (3) " + CurrentDateTime + " changed the selected optimizer family to familyShuntIndex of " + QString::number(optimizerFamilyComboBoxShuntToIndexMapIter.value());
                qDebug() << tStr;
                publishError(tStr);
            }
            else
            {
                tStr += " INFO: " + CurrentDateTime + " selected optimizer family matches familyShuntIndex of " + QString::number(optimizerFamilyComboBoxShuntToIndexMapIter.value());
                qDebug() << tStr;
                publishError(tStr);
            }
        }
        else
        {
            tStr += " ERROR: Unknown family value " + QString(familyShuntIndex) + " received, cannot check optimizer family";
            qDebug() << tStr;
            emit publishError(tStr);
        }
    }
    else
    {
        tStr += " ERROR: " + CurrentDateTime + " request to set value of optimzer family to unknown mac => " + mac;
        qDebug() << tStr;
        emit publishError(tStr);
    }
    qDebug() << Q_FUNC_INFO << " exit, received optimizer family index of " << familyShuntIndex << " for mac " << mac;
}

void AmptGUI_X::handleOptimizerFamilyChanged( const QString & family )
{
    qDebug() << Q_FUNC_INFO << " received optimizer family changed to " << family;
    int ovToOutputVoltage = 0;
    double ocToOutputCurrent = 0.0;
    int defaultOVValueToUse = 200;
    int defaultOCValueToUse = 200;
    QString ovSettingToMaxOutputVoltageStr("allows maximum output voltage of ");
    QString ocSettingToMaxOutputCurrentStr("allows maximum output current of ");

    if ((family == Family1500V) || (family == Family1500V_30) || (family == Family1500V_2nd))
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((6.175 * defaultOVValueToUse) - 35.053);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @1250V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);

        ui->edSettingsOCSetToLabel->setEnabled(true);
        ui->edSettingsOCSetToSpinBox->setValue(defaultOCValueToUse);
        ui->edSettingsOCSetToSpinBox->setEnabled(true);
        ocToOutputCurrent = (0.0821 * defaultOCValueToUse) - 0.0743;
        ocSettingToMaxOutputCurrentStr += QString::number(ocToOutputCurrent) + "A (VDC @1100V)";
        ui->edSettingsOCSettingMaxCurrentOutputLabel ->setText(ocSettingToMaxOutputCurrentStr);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(true);
    }
    else if (family == Family1300V)
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((5.5393 * defaultOVValueToUse) - 6.5825);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @770V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);


        // ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOCSetToSpinBox->setEnabled(true);
        ui->edSettingsOCSetToSpinBox->setValue(defaultOCValueToUse);
        ui->edSettingsOCSetToSpinBox->setEnabled(true);
        ocToOutputCurrent = (0.0578 * defaultOCValueToUse) - 0.222;
        ocSettingToMaxOutputCurrentStr += QString::number(ocToOutputCurrent) + "A (Vin @766V)";
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setText(ocSettingToMaxOutputCurrentStr);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(true);
    }
    else if (family == Family1000V)
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((2.6826 * defaultOVValueToUse) + 516.33);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @900V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);

        ui->edSettingsOCSetToLabel->setEnabled(false);
        ui->edSettingsOCSetToSpinBox->setValue(0);
        ui->edSettingsOCSetToSpinBox->setEnabled(false);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setText("");
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(false);

    }
    else if (family == Family600V_V2)
    {
        ui->edSettingsOVSetToLabel->setEnabled(true);
        ui->edSettingsOVSetToSpinBox->setValue(defaultOVValueToUse);
        ui->edSettingsOVSetToSpinBox->setEnabled(true);
        ovToOutputVoltage = static_cast<int>((2.4401 * defaultOVValueToUse) + 6.9774);
        ovSettingToMaxOutputVoltageStr += QString::number(ovToOutputVoltage) + "V (Vin @376V)";
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText(ovSettingToMaxOutputVoltageStr);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(true);

        ui->edSettingsOCSetToLabel->setEnabled(true);
        ui->edSettingsOCSetToSpinBox->setValue(defaultOCValueToUse);
        ui->edSettingsOCSetToSpinBox->setEnabled(true);
        ocToOutputCurrent = (0.0574 * defaultOCValueToUse) + 0.242;
        ocSettingToMaxOutputCurrentStr += QString::number(ocToOutputCurrent) + "";
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setText(ocSettingToMaxOutputCurrentStr);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(true);
    }
    else
    {
        ui->edSettingsOVSetToLabel->setEnabled(false);
        ui->edSettingsOVSetToSpinBox->setValue(0);
        ui->edSettingsOVSetToSpinBox->setEnabled(false);
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setText("");
        ui->edSettingsOVSettingMaxVoltageOutputLabel->setEnabled(false);

        ui->edSettingsOCSetToLabel->setEnabled(false);
        ui->edSettingsOCSetToSpinBox->setValue(0);
        ui->edSettingsOCSetToSpinBox->setEnabled(false);
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setText("");
        ui->edSettingsOCSettingMaxCurrentOutputLabel->setEnabled(false);

        QString errString(Q_FUNC_INFO);
        errString += " ERROR: code not implemented for optimizer family " + family;
        publishError(errString);
        qDebug() << errString;
    }
}


bool AmptGUI_X::validateAndSetConfigurationValue(const QString & configurationKey, int configurationValueType, QString & value)
{
    bool retValue = false;
    QString ErrorStr(Q_FUNC_INFO);
    int valueAsInt = value.toInt();

    // qDebug() << Q_FUNC_INFO << " INFO: begin for configurationKey:" << configurationKey << " valueAsInt:" << valueAsInt;

    switch (configurationValueType)
    {
        case TwoValueCheckBox:
            if ((valueAsInt == 2) || (valueAsInt == 0))
            {
                configurationKeyToCheckBoxIter = configurationKeyToCheckBox.find(configurationKey);
                if (configurationKeyToCheckBoxIter != configurationKeyToCheckBox.end())
                {
                    if (valueAsInt == 2)
                    {
                        (configurationKeyToCheckBoxIter.value())->setChecked(true);
                    }
                    else
                    {
                        (configurationKeyToCheckBoxIter.value())->setChecked(false);
                    }
                    retValue = true;
                }
                else
                {
                    ErrorStr += " ERROR: No entry in configurationKeyToCheckBox for key: " + configurationKey;
                    emit publishError(ErrorStr);
                    qDebug() << ErrorStr;
                }
            }
            else
            {
                ErrorStr += " ERROR: invalid value for TwoValueCheckBox: " + value;
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case TwoHundredFiftySixValueSpinBox:
            if ((valueAsInt >= 0) && (valueAsInt< 256))
            {
                configurationKeyToSpinBoxIter = configurationKeyToSpinBox.find(configurationKey);
                if (configurationKeyToSpinBoxIter != configurationKeyToSpinBox.end())
                {
                    (configurationKeyToSpinBoxIter.value())->setValue(valueAsInt);
                    retValue = true;
                }
                else
                {
                    ErrorStr += " ERROR: No entry in configurationKeyToSpinBox for key: " + configurationKey;
                    emit publishError(ErrorStr);
                    qDebug() << ErrorStr;
                }
            }
            else
            {
                ErrorStr += " ERROR: invalid value for TwoHundredFiftySixValueSpinBox: " + value;
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case NetIDSpinBox:
            if ((valueAsInt >= 0) && (valueAsInt< 16))
            {
                configurationKeyToSpinBoxIter = configurationKeyToSpinBox.find(configurationKey);
                if (configurationKeyToSpinBoxIter != configurationKeyToSpinBox.end())
                {
                    (configurationKeyToSpinBoxIter.value())->setValue(valueAsInt);
                    retValue = true;
                }
                else
                {
                    ErrorStr += " ERROR: No entry in configurationKeyToSpinBox for key: " + configurationKey;
                    emit publishError(ErrorStr);
                    qDebug() << ErrorStr;
                }
            }
            else
            {
                ErrorStr += " ERROR: invalid value for NetIDSpinBox: " + value;
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case PositiveIntegerSpinBox:
            if (valueAsInt >= 0)
            {
                configurationKeyToSpinBoxIter = configurationKeyToSpinBox.find(configurationKey);
                if (configurationKeyToSpinBoxIter != configurationKeyToSpinBox.end())
                {
                    (configurationKeyToSpinBoxIter.value())->setValue(valueAsInt);
                    retValue = true;
                }
                else
                {
                    ErrorStr += " ERROR: No entry in configurationKeyToSpinBox for key: " + configurationKey;
                    emit publishError(ErrorStr);
                    qDebug() << ErrorStr;
                }
            }
            else
            {
                ErrorStr += " ERROR: invalid value for PositiveIntegerSpinBox: " + value;
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case OptimizerFamilyComboBox:
            configurationKeyToComboBoxIter = configurationKeyToComboBox.find(configurationKey);
            if (configurationKeyToComboBoxIter != configurationKeyToComboBox.end())
            {
                (configurationKeyToComboBoxIter.value())->setCurrentIndex((configurationKeyToComboBoxIter.value())->findText(value));
                retValue = true;
            }
            else
            {
                ErrorStr += " ERROR: No entry in configurationKeyToComboBox for key: " + configurationKey;
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case BooleanRadioButton:
            configurationKeyToRadioButtonIter = configurationKeyToRadioButton.find(configurationKey);
            if (configurationKeyToRadioButtonIter != configurationKeyToRadioButton.end())
            {
                // qDebug() << Q_FUNC_INFO << " INFO: key:" << configurationKey << " is in configurationKeyToRadioButton, valueAsInt is " << QString::number(valueAsInt);
                retValue = true;
                if (valueAsInt == 1)
                {
                    (configurationKeyToRadioButtonIter.value())->setChecked(true);
                    (configurationKeyToRadioButtonIter.value())->clicked(true);
                }
                else
                {
                   (configurationKeyToRadioButtonIter.value())->setChecked(false);
                   (configurationKeyToRadioButtonIter.value())->clicked(false);
                }
                // qDebug() << Q_FUNC_INFO << " radio button is checked: " <<(configurationKeyToRadioButtonIter.value())->isChecked();
            }
            else
            {
                ErrorStr += " ERROR: No entry in configurationKeyToRadioButton for key: " + configurationKey;
                emit publishError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        default:
            ErrorStr += " ERROR: Unknown configurationValueType: " + QString::number(configurationValueType);
            qDebug() << ErrorStr;
            emit publishError(ErrorStr);
    }
    // qDebug() << Q_FUNC_INFO << " INFO: end for configurationKey:" << configurationKey << " returning " << ((retValue) ? " TRUE" : " FALSE");
    return retValue;
}

void AmptGUI_X::handlePublishSavedConfiguration(const QStringList &config)
{
    QString ErrorStr(Q_FUNC_INFO);
    // qDebug() << Q_FUNC_INFO << " INFO: begin ... ";

    // qDebug() << Q_FUNC_INFO << " INFO: size of config:" << config.size();

    for (int i = 0; i < config.size(); i++)
    {
        // qDebug() << Q_FUNC_INFO << " INFO: config at " << i << " => " << config.at(i);
        QString oneConfigPair = config.at(i);
        //oneConfigPair = oneConfigPair.remove(QChar('\n'), Qt::CaseInsensitive);
        oneConfigPair = oneConfigPair.trimmed();
        int colonIndex = oneConfigPair.indexOf(QChar(':'), 0,Qt::CaseInsensitive);
        QString oneConfigPairKey = oneConfigPair.left(colonIndex + 1);
        QString oneConfigPairValue = oneConfigPair.right(oneConfigPair.size() - colonIndex - 1);

        // qDebug() << Q_FUNC_INFO << " INFO: as QString:" << oneConfigPair << " index of : => " << oneConfigPair.indexOf(QChar(':'),0,Qt::CaseInsensitive) << " key:" <<oneConfigPairKey << " value:" << oneConfigPairValue;

        QMap<QString, int>::const_iterator iter = configurationMap.find(oneConfigPairKey);

        if (iter != configurationMap.end())
        {
            // qDebug() << Q_FUNC_INFO << " INFO: found key " << oneConfigPairKey << " (i.e.) " << iter.key() << " in configurationMap with value of " << iter.value();
            if (validateAndSetConfigurationValue(iter.key(),iter.value(), oneConfigPairValue) == true)
            {
                // qDebug() << Q_FUNC_INFO << " INFO: configuration for " << iter.key() << " should be set correctly...";

            }
            else
            {
                ErrorStr += " ERROR: failed to validate configuration type of :" + QString(iter.value()) + " for value:" + oneConfigPairValue + " for key:" + oneConfigPairKey;
                qDebug() << ErrorStr;
                emit publishError(ErrorStr);
                ErrorStr = Q_FUNC_INFO;
            }
        }
        else
        {
            ErrorStr += " ERROR: received unknown configuration key:" + oneConfigPairKey + ", not found in configurationMap";
            qDebug() << ErrorStr;
            emit publishError(ErrorStr);
            ErrorStr = Q_FUNC_INFO;
        }

        // find separator of string, breaking into key/value pairs
        // if key is known, attempt to 'set' to value else log/emit error.
    }

    // qDebug() << Q_FUNC_INFO << " INFO: end ... ";
}

void AmptGUI_X::handleConfigurationSaveAmptGUI_XPushButton( void )
{
    qDebug() << Q_FUNC_INFO << " begin ... ";
    handleConfigurationSave(true);
    qDebug() << Q_FUNC_INFO << " end ...";
}

void AmptGUI_X::closeEvent(QCloseEvent *event)
{
    qDebug() << Q_FUNC_INFO << " INFO: event:" << event->type();

    QString InfoStr = " Do you wish to terminate AmptGUI_X?";
    QMessageBox * quitConfirmDialog = new QMessageBox(this);
    quitConfirmDialog->setText(InfoStr);
    /*QAbstractButton* pButtonOk = */  quitConfirmDialog->addButton(tr("QUIT"), QMessageBox::YesRole);
    /* QAbstractButton *pButtonNo = */ quitConfirmDialog->addButton(tr("NO"), QMessageBox::NoRole);
    int nMode = quitConfirmDialog->exec();
    delete quitConfirmDialog;
    qDebug() << Q_FUNC_INFO << " INFO nMode=" << nMode << " => " << ((nMode == 0) ? " Quitting" : " Would stay");

    if (nMode == 0)
    {
        // Only auto save configuration data if user wishes it.
        if (ui->configurationSaveAmptGUI_XCheckBox->isChecked() == true)
        {
            qDebug() << Q_FUNC_INFO << " INFO: configurationSaveAmptGUI_XCheckBox is checked, handling save configuration file ...";
            handleConfigurationSave(true);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: configurationSaveAmptGUI_XCheckBox is not checked, not saving configuration file ...";
        }
        // LBC check to save PB in application to file(s)


        handleUtilitiesUtilitiesDialogClose();

        QThread::msleep(900);
        emit publishTerminate();
        QThread::msleep(1400);
        // m_gatewayThread.wait();
        event->accept();

        // Create configuration "string" to send to configuration thread.
        //
        // Send termination signal to all threads (Logger will log before exit)
        // event->accept()
    }
    else
    {
        event->ignore(); // User indicated they wish to not leave the wonderful world of AmptGUI_X ...
    }
    // Pop up (Do you want to exit application?) (configurable)
    // if yes
    //     Obtain configuration and save to configuration file.
    //     Gracefully end threads (Gateway, ....)
    //     Log message that user requested application to end
    //     end ...
    //     event->accept();
    // else
    //     evemt->ignore();
    /*
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
    */
}

void AmptGUI_X::initializeOTATableWidget( void )
{
    ui->OTATableWidget->clear();
    ui->OTATableWidget->setRowCount(0);

    ui->OTATableWidget->setHorizontalHeaderItem(SerialNumIndex, new QTableWidgetItem(QString("SerialNum")));
    ui->OTATableWidget->setHorizontalHeaderItem(MACIndex, new QTableWidgetItem(QString("MAC")));
    ui->OTATableWidget->setHorizontalHeaderItem(TimeIndex, new QTableWidgetItem(QString("Time")));
    ui->OTATableWidget->setHorizontalHeaderItem(Vin1Index, new QTableWidgetItem(QString("V in1")));
    ui->OTATableWidget->setHorizontalHeaderItem(Vin2Index, new QTableWidgetItem(QString("V in2")));
    ui->OTATableWidget->setHorizontalHeaderItem(VoutIndex, new QTableWidgetItem(QString("V out")));
    ui->OTATableWidget->setHorizontalHeaderItem(Iin1Index, new QTableWidgetItem(QString("I in1")));
    ui->OTATableWidget->setHorizontalHeaderItem(Iin2Index, new QTableWidgetItem(QString("I in2")));
    ui->OTATableWidget->setHorizontalHeaderItem(IoutIndex, new QTableWidgetItem(QString("I out")));
    ui->OTATableWidget->setHorizontalHeaderItem(PowerDissIndex, new QTableWidgetItem(QString("Pwr Diss")));
    ui->OTATableWidget->setHorizontalHeaderItem(TempIndex, new QTableWidgetItem(QString("Temp")));
    ui->OTATableWidget->setHorizontalHeaderItem(StatusIndex, new QTableWidgetItem(QString("Status")));
    ui->OTATableWidget->setHorizontalHeaderItem(OVIndex, new QTableWidgetItem(QString("OV")));
    ui->OTATableWidget->setHorizontalHeaderItem(OCIndex, new QTableWidgetItem(QString("OC")));
    ui->OTATableWidget->setHorizontalHeaderItem(ModuleIndex, new QTableWidgetItem(QString("Mod")));
    ui->OTATableWidget->setHorizontalHeaderItem(MPPIndex, new QTableWidgetItem(QString("MPP")));
    ui->OTATableWidget->setHorizontalHeaderItem(ChannelIndex, new QTableWidgetItem(QString("Chnl")));
    ui->OTATableWidget->setHorizontalHeaderItem(BunchIndex, new QTableWidgetItem(QString("Bnch")));
    ui->OTATableWidget->setHorizontalHeaderItem(SlotIndex, new QTableWidgetItem(QString("Id")));

    ui->OTATableWidget->setHorizontalHeaderItem(GWOffsetIndex, new QTableWidgetItem(QString("GwOff")));
    ui->OTATableWidget->setHorizontalHeaderItem(GWRSSIIndex, new QTableWidgetItem(QString("GwRSSI")));
    ui->OTATableWidget->setHorizontalHeaderItem(EDOffsetIndex, new QTableWidgetItem(QString("EdOff")));
    ui->OTATableWidget->setHorizontalHeaderItem(EDRSSIIndex, new QTableWidgetItem(QString("EdRSSI")));


    //ui->OTATableWidget->horizontalHeader()->setDefaultSectionSize(80);
    ui->OTATableWidget->setColumnWidth(SerialNumIndex,78);
    ui->OTATableWidget->setColumnWidth(MACIndex,86);
    ui->OTATableWidget->setColumnWidth(TimeIndex,116);
    ui->OTATableWidget->setColumnWidth(Vin1Index,66);

    ui->OTATableWidget->setColumnWidth(Vin2Index,66);
    ui->OTATableWidget->setColumnWidth(VoutIndex,66);
    ui->OTATableWidget->setColumnWidth(Iin1Index,50);
    ui->OTATableWidget->setColumnWidth(Iin2Index,50);
    ui->OTATableWidget->setColumnWidth(IoutIndex,50);
    ui->OTATableWidget->setColumnWidth(PowerDissIndex,66);
    ui->OTATableWidget->setColumnWidth(TempIndex,46);
    ui->OTATableWidget->setColumnWidth(StatusIndex,48);
    ui->OTATableWidget->setColumnWidth(GWOffsetIndex,52);
    ui->OTATableWidget->setColumnWidth(GWRSSIIndex,58);
    ui->OTATableWidget->setColumnWidth(EDOffsetIndex,52);
    ui->OTATableWidget->setColumnWidth(EDRSSIIndex,58);

    ui->OTATableWidget->setColumnWidth(OVIndex,32);
    ui->OTATableWidget->setColumnWidth(OCIndex,32);
    ui->OTATableWidget->setColumnWidth(ChannelIndex,46);
    ui->OTATableWidget->setColumnWidth(BunchIndex,44);
    ui->OTATableWidget->setColumnWidth(SlotIndex,22);
    ui->OTATableWidget->setColumnWidth(ModuleIndex,40);
    ui->OTATableWidget->setColumnWidth(MPPIndex,40);

    ui->OTATableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    }

void AmptGUI_X::handleClearHistoryPushButton( void )
{
    // Stop accepting OTA data in gateway and clear queue.
    // Set current mac to blank
    // .. ... ... .. .. handleClearCurrentEndDevicePBsAndLoadNewEDPBs();
    // clear OTA table
    // clear coeffs area
    // clear Optimizer pull down
    // reset OVOC area

    qDebug() << Q_FUNC_INFO << " Entering ...";

    int rowCount = ui->OTATableWidget->rowCount();
    for (int i = rowCount; i > 0; i--)
    {
        ui->OTATableWidget->removeRow(i);
    }
    // ui->OTATableWidget->clear();
    // ui->OTATableWidget->setRowCount(0);

    initializeOTATableWidget();

    m_currentActiveMAC = "";
    emit publishCurrentActiveMAC(m_currentActiveMAC);
    ui->commandMACComboBox->clear();

    ui->parametersReadPushButton->setEnabled(false);
    ui->parametersWritePushButton->setEnabled(false);

    m_edCommsChangesTracked->setIgnoreSignals(true);
    m_edSettingsChangesTracked->setIgnoreSignals(true);
    m_powerCntrlChangesTracked->setIgnoreSignals(true);
    m_linearCoeffsChangesTracked->setIgnoreSignals(true);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(true);
    m_fineTuningValueChangesTracked->setIgnoreSignals(true);
    m_radioValueChangesTracked->setIgnoreSignals(true);
    m_protectionsChangesTracked->setIgnoreSignals(true);

    ResetParameterBlockValues = true;

    handleResetTextEditControls(); // OVOC area

    handleResetPowerCntrlWidgets();

    handleResetLinearCoeffs();
    handleResetTempCntrl();
    handleResetProtections();
    handleResetFineTuning();
    handleResetRadio();
    handleResetEDComms();
    handleResetEDSettings();

    handleResetKeys();
    handleResetVersionInfo();
    handleResetOutput();
    handleResetCoeffsLine();

    //m_gatewayChangesTracked->resetAllTrackedGatewayValues();
    m_edCommsChangesTracked->resetAllTrackedValues();
    m_edSettingsChangesTracked->resetAllTrackedValues();
    m_powerCntrlChangesTracked->resetAllTrackedValues();
    m_linearCoeffsChangesTracked->resetAllTrackedValues();
    m_tempCntrlValueChangesTracked->resetAllTrackedValues();
    m_fineTuningValueChangesTracked->resetAllTrackedValues();
    m_radioValueChangesTracked->resetAllTrackedValues();
    m_protectionsChangesTracked->resetAllTrackedValues();

    m_edCommsChangesTracked->setIgnoreSignals(false);
    m_edSettingsChangesTracked->setIgnoreSignals(false);
    m_powerCntrlChangesTracked->setIgnoreSignals(false);
    m_linearCoeffsChangesTracked->setIgnoreSignals(false);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(false);
    m_fineTuningValueChangesTracked->setIgnoreSignals(false);
    m_radioValueChangesTracked->setIgnoreSignals(false);
    m_protectionsChangesTracked->setIgnoreSignals(false);

    ResetParameterBlockValues = false;

    ui->parametersReadPushButton->setEnabled(true);
}

void AmptGUI_X::handleClearCurrentEndDevicePBsAndLoadNewEDPBs( void )
{
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " BEGIN with m_currentActiveMAC:" << m_currentActiveMAC;
    // disable read parameter block values button
    ui->parametersReadPushButton->setEnabled(false);
    ui->parametersWritePushButton->setEnabled(false);

    m_edCommsChangesTracked->setIgnoreSignals(true);
    m_edSettingsChangesTracked->setIgnoreSignals(true);
    m_powerCntrlChangesTracked->setIgnoreSignals(true);
    m_linearCoeffsChangesTracked->setIgnoreSignals(true);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(true);
    m_fineTuningValueChangesTracked->setIgnoreSignals(true);
    m_radioValueChangesTracked->setIgnoreSignals(true);
    m_protectionsChangesTracked->setIgnoreSignals(true);

    ResetParameterBlockValues = true;

    // Need to reset displayed ED parameters and clear Red/Blue tracking info.
    handleResetPowerCntrlWidgets();

    handleResetLinearCoeffs();
    handleResetTempCntrl();
    handleResetProtections();
    handleResetFineTuning();
    handleResetRadio();
    handleResetEDComms();
    handleResetEDSettings();

    handleResetKeys();
    handleResetVersionInfo();
    // handleResetOutput();

    //m_gatewayChangesTracked->resetAllTrackedGatewayValues();
    m_edCommsChangesTracked->resetAllTrackedValues();
    m_edSettingsChangesTracked->resetAllTrackedValues();
    m_powerCntrlChangesTracked->resetAllTrackedValues();
    m_linearCoeffsChangesTracked->resetAllTrackedValues();
    m_tempCntrlValueChangesTracked->resetAllTrackedValues();
    m_fineTuningValueChangesTracked->resetAllTrackedValues();
    m_radioValueChangesTracked->resetAllTrackedValues();
    m_protectionsChangesTracked->resetAllTrackedValues();


    // Here is where to check if new current mac has saved PB values

    QString partialPBKey(m_currentActiveMAC);

    if (mainImage.contains(partialPBKey))
    {
        QString onMainImage = mainImage[partialPBKey];
        // qDebug() << Q_FUNC_INFO << " INFO: &&&&& ^^^^^ &&&&& sending onMainImage:" << onMainImage;

        if (ui->parametersFlashCheckBox->isChecked())
        {
            partialPBKey += "_1_";
        }
        else
        {
            partialPBKey += "_0_";
        }
         emit publishFindStoredPBInfo(partialPBKey,onMainImage);
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        errString += " WARNING: saved PB information for mac:" + partialPBKey + " based on partial key is not available.";
        publishError(errString);
        qDebug() << errString;
    }

    m_edCommsChangesTracked->setIgnoreSignals(false);
    m_edSettingsChangesTracked->setIgnoreSignals(false);
    m_powerCntrlChangesTracked->setIgnoreSignals(false);
    m_linearCoeffsChangesTracked->setIgnoreSignals(false);
    m_tempCntrlValueChangesTracked->setIgnoreSignals(false);
    m_fineTuningValueChangesTracked->setIgnoreSignals(false);
    m_radioValueChangesTracked->setIgnoreSignals(false);
    m_protectionsChangesTracked->setIgnoreSignals(false);


    ResetParameterBlockValues = false;

    ui->parametersReadPushButton->setEnabled(true);
    // qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " END with m_currentActiveMAC:" << m_currentActiveMAC;
}

void AmptGUI_X::handleUtilitiesSelectSNOrMACValueChangedFromDial(int s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: new value of " << QString::number(s);
    if (s == 0)
    {
        ui->utilitiesSelectSNOrMACLabel->setText(utilitiesSelectSNtoMACStr);
    }
    else
    {
        ui->utilitiesSelectSNOrMACLabel->setText(utilitiesSelectMACToSNStr);
    }
    ui->utilitiesOutputSNOrMACLabel->setText("");
    ui->utilitiesSelectSNOrMACLineEdit->setText("");
}

bool AmptGUI_X::validSerialNumberSoFar(const QString s)
{

    bool validSoFar = true;
    int i = 0;
    int sLength = s.length();

    qDebug() << Q_FUNC_INFO << " INFO: validate a SN of " << s << ", length of " << QString::number(sLength);

    if (sLength > 11)
    {
        validSoFar = false;
    }

    for (i = 0; i < sLength && validSoFar; i++)
    {
        QChar currentChar = s.at(i);
        if (i == 4)
        {
            if ((currentChar == 't') || (currentChar == 'T') || (currentChar == 'a') || (currentChar == 'A') || (currentChar == 'p') || (currentChar == 'P') ||
                    (currentChar == 'k') || (currentChar == 'K') || (currentChar == 'z') || (currentChar == 'Z'))
            {
            }
            else
            {
                validSoFar = false;
            }
        }
        else
        {
            if (i == 0)
            {
                if ((currentChar >= '1') && (currentChar <= '9'))
                {

                }
                else
                {
                    validSoFar = false;
                }
            }
            else
            {
                if ((currentChar >= '0') && (currentChar <= '9'))
                {

                }
                else
                {
                    validSoFar = false;
                }
            }

        }
    }
    return validSoFar;
}

bool AmptGUI_X::validMACAddressSoFar(const QString s)
{
    bool validSoFar = true;

    int i = 0;
    int sLength = s.length();

    qDebug() << Q_FUNC_INFO << " INFO: validate a MAC Address of " << s << ", length of " << QString::number(sLength);

    if (sLength > 12)
    {
        validSoFar = false;
    }

    for (i = 0; i < sLength && validSoFar; i++)
    {
        QChar currentChar = s.at(i);
        if (((currentChar >= 'a') && (currentChar <= 'f')) || ((currentChar >= 'A') && (currentChar <= 'F')) ||
                ((currentChar >= '0') && (currentChar <= '9')))
        {

        }
        else
        {
            validSoFar = false;
        }
    }

    return validSoFar;
}

void AmptGUI_X::handleUtilitiesSelectSNOrMACLineEdit(QString s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: new value of " << s;
    QString errString(Q_FUNC_INFO);

    int sLength = s.length();
    bool validSoFar = true;

    if (ui->utilitiesSelectSNOrMACDial->value() == 0) // Serial Number
    {
        validSoFar = validSerialNumberSoFar(s);

        if (validSoFar == true)
        {
            if (sLength == 11)
            {
                QString macAddress("");
                if (serialNumberQStringToMACAddressQString(s,macAddress) == NO_ERROR)
                {
                    QString indicatorPlusMACAddress("=> ");
                    indicatorPlusMACAddress += macAddress;
                    ui->utilitiesOutputSNOrMACLabel->setText(indicatorPlusMACAddress);
                }
                else
                {
                    ui->utilitiesOutputSNOrMACLabel->setText("");
                    errString += " ERROR: conversion of serial number " + s + " to the associated MAC address failed.";
                    publishError(errString);
                    qDebug() << errString;
                }
            }
            else
            {
                ui->utilitiesOutputSNOrMACLabel->setText("");
            }
        }
        else
        {
            errString += " ERROR: removing last (non valid) character from serial number: " + s;
            publishError(errString);
            qDebug() << errString;

            QString removeLastChar = s.left(sLength - 1);
            ui->utilitiesSelectSNOrMACLineEdit->setText(removeLastChar);
        }
    }
    else // MAC address
    {
        validSoFar = validMACAddressSoFar(s);
        if (validSoFar == true)
        {

            if (sLength == 12)
            {
                char serialNumber[12];
                memset(serialNumber,0,12);
                if (macQStringToSerialNumber(s, serialNumber) == NO_ERROR)
                {
                    QString indicatorPlusSerialNumber("=> ");
                    indicatorPlusSerialNumber += QString(serialNumber);
                    ui->utilitiesOutputSNOrMACLabel->setText(indicatorPlusSerialNumber);
                }
                else
                {
                    ui->utilitiesOutputSNOrMACLabel->setText("");
                    errString += " ERROR: conversion of MAC Address " + s + " to the serial number failed.";
                    publishError(errString);
                    qDebug() << errString;
                }
            }
            else
            {
                ui->utilitiesOutputSNOrMACLabel->setText("");
            }
        }
        else
        {
            errString += " ERROR: removing last (non valid) character from MAC Address: " + s;
            publishError(errString);
            qDebug() << errString;

            QString removeLastChar = s.left(sLength - 1);
            ui->utilitiesSelectSNOrMACLineEdit->setText(removeLastChar);
        }

    }
}

void AmptGUI_X::handleUtilitiesUtilitiesDialogClose( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: enter";
    if (m_utilitiesDialog != nullptr)
    {
        qDebug() << Q_FUNC_INFO << " INFO: deleting utility dialog ...";
        disconnect(this,SIGNAL(publishAllKnownMACs(QStringList)), m_utilitiesDialog,SLOT(handlePublishAllKnownMACs(QStringList)) );
        disconnect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogClosingSignal(void)), this, SLOT(handleUtilitiesUtilitiesDialogClose()));
        disconnect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogRequestAllKnownMACs( void )), this, SLOT(handleRequestAllKnownMACs( void )));
        disconnect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogCommandToSendToGateway( const QString )), &m_gatewayThread, SLOT(handleGatewayCommandToSend(const QString)));
        disconnect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogRequestMACOTAData(const QString)), this, SLOT(handleBeginPublishOneMACOTAData(const QString)));
        disconnect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogEndRequestMACOTAData(void)), this, SLOT(handleEndPublishOneMACOTAData( void )));
        disconnect(m_utilitiesDialog, SIGNAL(publishAmptUtilitiesDialogError( const QString )), this, SLOT(handlePublishedErrors(const QString)));
        disconnect(this, SIGNAL(publishOneMACOTAData(QStringList)), m_utilitiesDialog, SLOT(handlePublishOneMACOTAOVData(QStringList)));

        handleRequestAllKnownMACs();

        delete m_utilitiesDialog;
        m_utilitiesDialog = nullptr;
        qDebug() << Q_FUNC_INFO << " INFO: deleted utility dialog ...";
    }
    else
    {
        QString infoString(Q_FUNC_INFO);
        infoString += " INFO: received dialog close when utilities dialog does not exist, ignoring ...";
        publishError(infoString);
        qDebug() << infoString;
    }
}

void AmptGUI_X::handleUtilitiesUtilitiesDialogPushButton( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: enter";
    //int retVal = 0;

    if (m_utilitiesDialog == nullptr)
    {
        m_utilitiesDialog = new AmptUtilitiesDialog;
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(m_utilitiesDialog);
        m_utilitiesDialog->resize(availableGeometry.width() / 3, availableGeometry.height() * 2 / 3);
        m_utilitiesDialog->move((availableGeometry.width() - m_utilitiesDialog->width()) / 2,
                                (availableGeometry.height() - m_utilitiesDialog->height()) / 2);

        // m_utilitiesDialog->setWindowModality(Qt::ApplicationModal);

        m_utilitiesDialog->show();
        m_utilitiesDialog->activateWindow();
        m_utilitiesDialog->raise();

        connect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogClosingSignal(void)), this, SLOT(handleUtilitiesUtilitiesDialogClose()));
        connect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogRequestAllKnownMACs( void )), this, SLOT(handleRequestAllKnownMACs( void )));
        connect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogCommandToSendToGateway( const QString )), &m_gatewayThread, SLOT(handleGatewayCommandToSend(const QString)));
        connect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogRequestMACOTAData(const QString)), this, SLOT(handleBeginPublishOneMACOTAData(const QString)));
        connect(m_utilitiesDialog, SIGNAL(AmptUtilitiesDialogEndRequestMACOTAData(void)), this, SLOT(handleEndPublishOneMACOTAData( void )));
        connect(m_utilitiesDialog, SIGNAL(publishAmptUtilitiesDialogError( const QString )), this, SLOT(handlePublishedErrors(const QString)));
        connect(this, SIGNAL(publishOneMACOTAData(QStringList)), m_utilitiesDialog, SLOT(handlePublishOneMACOTAData(QStringList)));
        connect(m_utilitiesDialog, SIGNAL(publishReplayLogLine(const QString)), this, SLOT(handlePublishReplayLogLine(const QString)));
        connect(m_utilitiesDialog, SIGNAL(publishSwitchFromOTADataToReplayData( void )), this, SLOT(handlePublishSwitchFromOTADataToReplayData( void )) );
        handleRequestAllKnownMACs();
        qDebug() << Q_FUNC_INFO << " INFO: CONNECTIONS ACCOMPLISHED...";
    }
    else
    {
        QString infoString(Q_FUNC_INFO);
        infoString += " INFO: Attempt to open utilities dialog window when it is already opened, minimized?, so bring it to the front...";
        publishError(infoString);
        qDebug() << infoString;

        m_utilitiesDialog->activateWindow();
        m_utilitiesDialog->setWindowState(Qt::WindowNoState);
        m_utilitiesDialog->raise();
    }
}

void AmptGUI_X::handleUtilitiesGatewaySetupPushButton( void )
{
    qDebug() << Q_FUNC_INFO;
    ui->utilitiesGatewaySetupPushButton->setEnabled(false);

    QString commandToSend = "P -1";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "k 0";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "K 9 1";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "L 1";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "H 0";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "z 4";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "K 6 1";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "E 1";
    sendGatewayCommandToGateway(commandToSend);

    commandToSend = "n";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    commandToSend = "G";
    sendGatewayCommandToGateway(commandToSend);
    qDebug() << Q_FUNC_INFO << " INFO: Sending command: " << commandToSend;

    ui->utilitiesGatewaySetupPushButton->setEnabled(true);
}

void AmptGUI_X::handleUtilitiesBatchCommandsSelectPushButton( void )
{
    // qDebug() << Q_FUNC_INFO << " INFO: enter ...";

    ui->utilitiesBatchCommandsSelectPushButton->setEnabled(false);
    ui->utilitiesBatchCommandsSelectLineEdit->clear();
    QFileDialog * selectBatchFileDialog =  new QFileDialog(this,"Batch Commands Directory and Filename",QDir::rootPath());
    int nMode = selectBatchFileDialog->exec();
    //qDebug() << Q_FUNC_INFO << " INFO: nMode = " << nMode;

    QStringList strlist = selectBatchFileDialog->selectedFiles();

    //qDebug() << Q_FUNC_INFO << " INFO: selectedFiles " << strlist << " number of files:" <<strlist.size();

    if (strlist.size() > 0)
    {
        // qDebug() << Q_FUNC_INFO << "publishUtilitiesBatchCommandsFile(" << strlist.at(0) << ")";
        emit publishUtilitiesBatchCommandsFile(strlist.at(0));
        ui->utilitiesBatchCommandsSelectLineEdit->setText(strlist.at(0));
        ui->utilitiesBatchCommandsStartStopLineEdit->clear();
     }
     else
     {
         // qDebug() << Q_FUNC_INFO << " INFO: no batch commands file indicated or returned ...";
         ui->utilitiesBatchCommandsSelectPushButton->setEnabled(true);
         ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
         ui->utilitiesBatchCommandsStartStopLineEdit->clear();
    }
    // qDebug() << Q_FUNC_INFO << " Line edit cursor pos " << ui->utilitiesBatchCommandsSelectLineEdit->cursorPosition();
}

void AmptGUI_X::handlePublishBatchCommandsFileValidated( bool value )
{
    // qDebug() << Q_FUNC_INFO << " INFO: enter, value = " << value;

    ui->utilitiesBatchCommandsSelectPushButton->setEnabled(true);

    if (value == true)
    {
        ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(true);
        ui->utilitiesBatchCommandsStartStopLineEdit->clear();
        ui->utilitiesBatchCommandsSelectLineEdit->setStyleSheet("color: black;");
    }
    else
    {
        ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
        ui->utilitiesBatchCommandsStartStopLineEdit->clear();
        ui->utilitiesBatchCommandsSelectLineEdit->setStyleSheet("color: red;");
    }
}

void AmptGUI_X::handlePublishBatchCommandsFileOperationBegun( void )
{
    // qDebug() << Q_FUNC_INFO << " INFO: enter";
    ui->utilitiesBatchCommandsSelectPushButton->setEnabled(false);
}

void AmptGUI_X::handlePublishBatchCommandsFileOperationEnded( void )
{
   // qDebug() << Q_FUNC_INFO << " INFO: enter";
   ui->utilitiesBatchCommandsStartStopPushButton->setEnabled(false);
   ui->utilitiesBatchCommandsSelectPushButton->setEnabled(true);
}

void AmptGUI_X::handlePublishBatchCommandStatus(const QString status)
{
    // qDebug() << Q_FUNC_INFO << " INFO: enter";
    ui->utilitiesBatchCommandsStartStopLineEdit->setText(status);
}

void AmptGUI_X::handleRequestAllKnownMACs( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: enter";
    QStringList knownMACs;

    int numberOfKnownMACs = ui->commandMACComboBox->count();
    for (int i = 0; i < numberOfKnownMACs; i++)
    {
        qDebug() << Q_FUNC_INFO << " INFO: mac at position " << i << " is " << ui->commandMACComboBox->itemText(i);
        knownMACs.append(ui->commandMACComboBox->itemText(i));
    }
    if (m_utilitiesDialog != nullptr)
    {
        connect(this,SIGNAL(publishAllKnownMACs(QStringList)), m_utilitiesDialog,SLOT(handlePublishAllKnownMACs(QStringList)));
    }
    emit publishAllKnownMACs(knownMACs);
}

void AmptGUI_X::handleBeginPublishOneMACOTAData(QString theMAC)
{
    qDebug() << Q_FUNC_INFO << " Enter with mac " << theMAC;
    m_oneMACOTAData = theMAC;
}

void AmptGUI_X::handleEndPublishOneMACOTAData( void )
{
    qDebug() << Q_FUNC_INFO << " Entering ...";
    m_oneMACOTAData = "";
}
