/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QMap>
#include <QDir>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QByteArray>
#include <QStandardPaths>
#include <QDataStream>
#include <QTextStream>


#include "endDeviceParameterBlockInfoThread.h"
#include "amptgui_x_status.h"
#include "amptgui_x_utilities.h"
#include "amptparameterblockconstants.h"
#include "amptgui_x_utilities.h"
#include "parameter_block_1300V.h"

static const QString formatIt("yyyy_MM_dd_HH_mm_ss");
static const QString comma(",");
static QMap<QString, bool> mainImage;
static QMap<QString, ParameterBlock_Union * > parameterBlocksStorage;
static QMap<QString, ParameterBlock_Union *>::iterator endofParameterBlockStorage;


QDataStream &operator<<(QDataStream &out, const ParameterBlock_Union * pbu)
{
    qDebug() << Q_FUNC_INFO << " writing parameter block family " << pbu->parameterBlockFamily << " Family600V_V2:" << Family600V_V2;

    out << pbu->parameterBlockFamily;

    if (pbu->parameterBlockFamily == Family1000V_Shunt)
    {
        out << pbu->PB.a1000VPB.barrier;
        out << pbu->PB.a1000VPB.netId;
        out << pbu->PB.a1000VPB.myBunch;
        out << pbu->PB.a1000VPB.groupId;
        out << pbu->PB.a1000VPB.myMac[0];
        out << pbu->PB.a1000VPB.myMac[1];
        out << pbu->PB.a1000VPB.myMac[2];
        out << pbu->PB.a1000VPB.myMac[3];
        out << pbu->PB.a1000VPB.myMac[4];
        out << pbu->PB.a1000VPB.myMac[5];
        out << pbu->PB.a1000VPB.dFk[0];
        out << pbu->PB.a1000VPB.dFk[1];
        out << pbu->PB.a1000VPB.dFk[2];
        out << pbu->PB.a1000VPB.dFk[3];
        out << pbu->PB.a1000VPB.vrefPolynom[0];
        out << pbu->PB.a1000VPB.vrefPolynom[1];
        out << pbu->PB.a1000VPB.vrefPolynom[2];
        out << pbu->PB.a1000VPB.linearK[0][0];
        out << pbu->PB.a1000VPB.linearK[0][1];
        out << pbu->PB.a1000VPB.linearK[1][0];
        out << pbu->PB.a1000VPB.linearK[1][1];
        out << pbu->PB.a1000VPB.linearK[2][0];
        out << pbu->PB.a1000VPB.linearK[2][1];
        out << pbu->PB.a1000VPB.linearK[3][0];
        out << pbu->PB.a1000VPB.linearK[3][1];
        out << pbu->PB.a1000VPB.linearK[4][0];
        out << pbu->PB.a1000VPB.linearK[4][1];
        out << pbu->PB.a1000VPB.linearK[5][0];
        out << pbu->PB.a1000VPB.linearK[5][1];
        out << pbu->PB.a1000VPB.linearK[6][0];
        out << pbu->PB.a1000VPB.linearK[6][1];
        out << pbu->PB.a1000VPB.curKey[0];
        out << pbu->PB.a1000VPB.curKey[1];
        out << pbu->PB.a1000VPB.curKey[2];
        out << pbu->PB.a1000VPB.curKey[3];
        out << pbu->PB.a1000VPB.curKey[4];
        out << pbu->PB.a1000VPB.curKey[5];
        out << pbu->PB.a1000VPB.curKey[6];
        out << pbu->PB.a1000VPB.curKey[7];
        out << pbu->PB.a1000VPB.curKey[8];
        out << pbu->PB.a1000VPB.curKey[9];
        out << pbu->PB.a1000VPB.curKey[10];
        out << pbu->PB.a1000VPB.curKey[11];
        out << pbu->PB.a1000VPB.curKey[12];
        out << pbu->PB.a1000VPB.curKey[13];
        out << pbu->PB.a1000VPB.curKey[14];
        out << pbu->PB.a1000VPB.curKey[15];
        out << pbu->PB.a1000VPB.curIV[0];
        out << pbu->PB.a1000VPB.curIV[1];
        out << pbu->PB.a1000VPB.curIV[2];
        out << pbu->PB.a1000VPB.curIV[3];
        out << pbu->PB.a1000VPB.curIV[4];
        out << pbu->PB.a1000VPB.curIV[5];
        out << pbu->PB.a1000VPB.curIV[6];
        out << pbu->PB.a1000VPB.curIV[7];
        out << pbu->PB.a1000VPB.curIV[8];
        out << pbu->PB.a1000VPB.curIV[9];
        out << pbu->PB.a1000VPB.curIV[10];
        out << pbu->PB.a1000VPB.curIV[11];
        out << pbu->PB.a1000VPB.curIV[12];
        out << pbu->PB.a1000VPB.curIV[13];
        out << pbu->PB.a1000VPB.curIV[14];
        out << pbu->PB.a1000VPB.curIV[15];
        out << pbu->PB.a1000VPB.fetFailureCount;
        out << pbu->PB.a1000VPB.fetCurrentThreshold;
        out << pbu->PB.a1000VPB.fetDeltaCurrent;
        out << pbu->PB.a1000VPB.oscLowCurrentLimitInmA;
        out << pbu->PB.a1000VPB.oscDeltaV;
        out << pbu->PB.a1000VPB.oscOVStartupDelay;
        out << pbu->PB.a1000VPB.oscAfterStartupDelay;
        out << pbu->PB.a1000VPB.oscLowCurrentOnlyDelay;
        out << pbu->PB.a1000VPB.tests[0];
        out << pbu->PB.a1000VPB.tests[1];
        out << pbu->PB.a1000VPB.tests[2];
        out << pbu->PB.a1000VPB.tests[3];
        out << pbu->PB.a1000VPB.installDate;
        out << pbu->PB.a1000VPB.k_ov_volt;
        out << pbu->PB.a1000VPB.k_oc_cur;
        out << pbu->PB.a1000VPB.syncword;
        out << pbu->PB.a1000VPB.vin_disable_radio;
        out << pbu->PB.a1000VPB.rbunch;
        out << pbu->PB.a1000VPB.gbunch;
        out << pbu->PB.a1000VPB.shortCircuitLevel;
        out << pbu->PB.a1000VPB.reserved;
        out << pbu->PB.a1000VPB.synch_phase;
        out << pbu->PB.a1000VPB.synch_freq;
        out << pbu->PB.a1000VPB.bandwidth250;
        out << pbu->PB.a1000VPB.channel;
        out << pbu->PB.a1000VPB.utcProgram;
        out << pbu->PB.a1000VPB.utcLow;
        out << pbu->PB.a1000VPB.utcHigh;
        out << pbu->PB.a1000VPB.tkCurrent;
        out << pbu->PB.a1000VPB.tkPower;
        out << pbu->PB.a1000VPB.mpp;
        out << pbu->PB.a1000VPB.module;
        out << pbu->PB.a1000VPB.ov;
        out << pbu->PB.a1000VPB.oc;
        out << pbu->PB.a1000VPB.radioPower;
        out << pbu->PB.a1000VPB.edAddr;
        out << pbu->PB.a1000VPB.gwAddr;
        out << pbu->PB.a1000VPB.repeaterChannel;
        out << pbu->PB.a1000VPB.repeaterPower;
        out << pbu->PB.a1000VPB.boolByte1;
        out << pbu->PB.a1000VPB.showState;
        out << pbu->PB.a1000VPB.CriticalLevel500;
        out << pbu->PB.a1000VPB.CriticalLevel10;
        out << pbu->PB.a1000VPB.pureOffset;
        out << pbu->PB.a1000VPB.defCyclesTo500;
        out << pbu->PB.a1000VPB.defCyclesTo10;
        out << pbu->PB.a1000VPB.defCyclesToStep500Channel;
        out << pbu->PB.a1000VPB.defCyclesToStep10Channel;
        out << pbu->PB.a1000VPB.defCycles2SoftKick;
        out << pbu->PB.a1000VPB.defCycles2HardKick;
        out << pbu->PB.a1000VPB.imageAddr;
        out << pbu->PB.a1000VPB.versionLow;
        out << pbu->PB.a1000VPB.versionHigh;
        out << pbu->PB.a1000VPB.starting500Channel;
        out << pbu->PB.a1000VPB.boolByte2;
        out << pbu->PB.a1000VPB.prepAddr;
        out << pbu->PB.a1000VPB.repStep;
        out << pbu->PB.a1000VPB.ov_startup;
        out << pbu->PB.a1000VPB.t_mod_off;
        out << pbu->PB.a1000VPB.toff_fallback;
        out << pbu->PB.a1000VPB.ton_fallback;
        out << pbu->PB.a1000VPB.fallback_time;
        out << pbu->PB.a1000VPB.network_cnst_1;
        out << pbu->PB.a1000VPB.network_cnst_2;
        out << pbu->PB.a1000VPB.oc_protection;
        out << pbu->PB.a1000VPB.oc_step;
        out << pbu->PB.a1000VPB.cur_noise;
        out << pbu->PB.a1000VPB.ov_step;
        out << pbu->PB.a1000VPB.shunt;
        out << pbu->PB.a1000VPB.max_off;
        out << pbu->PB.a1000VPB.vin_limit;
        out << pbu->PB.a1000VPB.vin_turn_on;
        out << pbu->PB.a1000VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family600V_Shunt)
    {
        out << pbu->PB.a600V_V2VPB.barrier;
        out << pbu->PB.a600V_V2VPB.netId;
        out << pbu->PB.a600V_V2VPB.myBunch;
        out << pbu->PB.a600V_V2VPB.groupId;
        out << pbu->PB.a600V_V2VPB.myMac[0];
        out << pbu->PB.a600V_V2VPB.myMac[1];
        out << pbu->PB.a600V_V2VPB.myMac[2];
        out << pbu->PB.a600V_V2VPB.myMac[3];
        out << pbu->PB.a600V_V2VPB.myMac[4];
        out << pbu->PB.a600V_V2VPB.myMac[5];
        out << pbu->PB.a600V_V2VPB.dFk[0];
        out << pbu->PB.a600V_V2VPB.dFk[1];
        out << pbu->PB.a600V_V2VPB.dFk[2];
        out << pbu->PB.a600V_V2VPB.dFk[3];
        out << pbu->PB.a600V_V2VPB.vrefPolynom[0];
        out << pbu->PB.a600V_V2VPB.vrefPolynom[1];
        out << pbu->PB.a600V_V2VPB.vrefPolynom[2];
        out << pbu->PB.a600V_V2VPB.linearK[0][0];
        out << pbu->PB.a600V_V2VPB.linearK[0][1];
        out << pbu->PB.a600V_V2VPB.linearK[1][0];
        out << pbu->PB.a600V_V2VPB.linearK[1][1];
        out << pbu->PB.a600V_V2VPB.linearK[2][0];
        out << pbu->PB.a600V_V2VPB.linearK[2][1];
        out << pbu->PB.a600V_V2VPB.linearK[3][0];
        out << pbu->PB.a600V_V2VPB.linearK[3][1];
        out << pbu->PB.a600V_V2VPB.linearK[4][0];
        out << pbu->PB.a600V_V2VPB.linearK[4][1];
        out << pbu->PB.a600V_V2VPB.linearK[5][0];
        out << pbu->PB.a600V_V2VPB.linearK[5][1];
        out << pbu->PB.a600V_V2VPB.linearK[6][0];
        out << pbu->PB.a600V_V2VPB.linearK[6][1];
        out << pbu->PB.a600V_V2VPB.curKey[0];
        out << pbu->PB.a600V_V2VPB.curKey[1];
        out << pbu->PB.a600V_V2VPB.curKey[2];
        out << pbu->PB.a600V_V2VPB.curKey[3];
        out << pbu->PB.a600V_V2VPB.curKey[4];
        out << pbu->PB.a600V_V2VPB.curKey[5];
        out << pbu->PB.a600V_V2VPB.curKey[6];
        out << pbu->PB.a600V_V2VPB.curKey[7];
        out << pbu->PB.a600V_V2VPB.curKey[8];
        out << pbu->PB.a600V_V2VPB.curKey[9];
        out << pbu->PB.a600V_V2VPB.curKey[10];
        out << pbu->PB.a600V_V2VPB.curKey[11];
        out << pbu->PB.a600V_V2VPB.curKey[12];
        out << pbu->PB.a600V_V2VPB.curKey[13];
        out << pbu->PB.a600V_V2VPB.curKey[14];
        out << pbu->PB.a600V_V2VPB.curKey[15];
        out << pbu->PB.a600V_V2VPB.curIV[0];
        out << pbu->PB.a600V_V2VPB.curIV[1];
        out << pbu->PB.a600V_V2VPB.curIV[2];
        out << pbu->PB.a600V_V2VPB.curIV[3];
        out << pbu->PB.a600V_V2VPB.curIV[4];
        out << pbu->PB.a600V_V2VPB.curIV[5];
        out << pbu->PB.a600V_V2VPB.curIV[6];
        out << pbu->PB.a600V_V2VPB.curIV[7];
        out << pbu->PB.a600V_V2VPB.curIV[8];
        out << pbu->PB.a600V_V2VPB.curIV[9];
        out << pbu->PB.a600V_V2VPB.curIV[10];
        out << pbu->PB.a600V_V2VPB.curIV[11];
        out << pbu->PB.a600V_V2VPB.curIV[12];
        out << pbu->PB.a600V_V2VPB.curIV[13];
        out << pbu->PB.a600V_V2VPB.curIV[14];
        out << pbu->PB.a600V_V2VPB.curIV[15];
        out << pbu->PB.a600V_V2VPB.fetFailureCount;
        out << pbu->PB.a600V_V2VPB.fetCurrentThreshold;
        out << pbu->PB.a600V_V2VPB.fetDeltaCurrent;
        out << pbu->PB.a600V_V2VPB.oscLowCurrentLimitInmA;
        out << pbu->PB.a600V_V2VPB.oscDeltaV;
        out << pbu->PB.a600V_V2VPB.oscOVStartupDelay;
        out << pbu->PB.a600V_V2VPB.oscAfterStartupDelay;
        out << pbu->PB.a600V_V2VPB.oscLowCurrentOnlyDelay;
        out << pbu->PB.a600V_V2VPB.versionSuffix[0];
        out << pbu->PB.a600V_V2VPB.versionSuffix[1];
        out << pbu->PB.a600V_V2VPB.versionSuffix[2];
        out << pbu->PB.a600V_V2VPB.tests;
        out << pbu->PB.a600V_V2VPB.installDate;
        out << pbu->PB.a600V_V2VPB.k_ov_volt;
        out << pbu->PB.a600V_V2VPB.k_oc_cur;
        out << pbu->PB.a600V_V2VPB.syncword;
        out << pbu->PB.a600V_V2VPB.vin_disable_radio;
        out << pbu->PB.a600V_V2VPB.rbunch;
        out << pbu->PB.a600V_V2VPB.gbunch;
        out << pbu->PB.a600V_V2VPB.shortCircuitLevel;
        out << pbu->PB.a600V_V2VPB.reserved;
        out << pbu->PB.a600V_V2VPB.synch_phase;
        out << pbu->PB.a600V_V2VPB.synch_freq;
        out << pbu->PB.a600V_V2VPB.bandwidth250;
        out << pbu->PB.a600V_V2VPB.channel;
        out << pbu->PB.a600V_V2VPB.utcProgram;
        out << pbu->PB.a600V_V2VPB.utcLow;
        out << pbu->PB.a600V_V2VPB.utcHigh;
        out << pbu->PB.a600V_V2VPB.tkCurrent;
        out << pbu->PB.a600V_V2VPB.tkPower;
        out << pbu->PB.a600V_V2VPB.mpp;
        out << pbu->PB.a600V_V2VPB.module;
        out << pbu->PB.a600V_V2VPB.ov;
        out << pbu->PB.a600V_V2VPB.oc;
        out << pbu->PB.a600V_V2VPB.radioPower;
        out << pbu->PB.a600V_V2VPB.edAddr;
        out << pbu->PB.a600V_V2VPB.gwAddr;
        out << pbu->PB.a600V_V2VPB.repeaterChannel;
        out << pbu->PB.a600V_V2VPB.repeaterPower;
        out << pbu->PB.a600V_V2VPB.showState;
        out << pbu->PB.a600V_V2VPB.CriticalLevel500;
        out << pbu->PB.a600V_V2VPB.CriticalLevel10;
        out << pbu->PB.a600V_V2VPB.pureOffset;
        out << pbu->PB.a600V_V2VPB.defCyclesTo500;
        out << pbu->PB.a600V_V2VPB.defCyclesTo10;
        out << pbu->PB.a600V_V2VPB.defCyclesToStep500Channel;
        out << pbu->PB.a600V_V2VPB.defCyclesToStep10Channel;
        out << pbu->PB.a600V_V2VPB.defCycles2SoftKick;
        out << pbu->PB.a600V_V2VPB.defCycles2HardKick;
        out << pbu->PB.a600V_V2VPB.imageAddr;
        out << pbu->PB.a600V_V2VPB.versionLow;
        out << pbu->PB.a600V_V2VPB.versionHigh;
        out << pbu->PB.a600V_V2VPB.starting500Channel;
        out << pbu->PB.a600V_V2VPB.boolByte2;
        out << pbu->PB.a600V_V2VPB.prepAddr;
        out << pbu->PB.a600V_V2VPB.repStep;
        out << pbu->PB.a600V_V2VPB.ov_startup;
        out << pbu->PB.a600V_V2VPB.t_mod_off;
        out << pbu->PB.a600V_V2VPB.toff_fallback;
        out << pbu->PB.a600V_V2VPB.ton_fallback;
        out << pbu->PB.a600V_V2VPB.fallback_time;
        out << pbu->PB.a600V_V2VPB.network_cnst_1;
        out << pbu->PB.a600V_V2VPB.network_cnst_2;
        out << pbu->PB.a600V_V2VPB.oc_protection;
        out << pbu->PB.a600V_V2VPB.oc_step;
        out << pbu->PB.a600V_V2VPB.cur_noise;
        out << pbu->PB.a600V_V2VPB.ov_step;
        out << pbu->PB.a600V_V2VPB.shunt;
        out << pbu->PB.a600V_V2VPB.max_off;
        out << pbu->PB.a600V_V2VPB.vin_limit;
        out << pbu->PB.a600V_V2VPB.vin_turn_on;
        out << pbu->PB.a600V_V2VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family600V_V2_2nd_Shunt)
    {
        out << pbu->PB.a600V_V2_2ndVPB.barrier;
        out << pbu->PB.a600V_V2_2ndVPB.netId;
        out << pbu->PB.a600V_V2_2ndVPB.myBunch;
        out << pbu->PB.a600V_V2_2ndVPB.groupId;
        out << pbu->PB.a600V_V2_2ndVPB.myMac[0];
        out << pbu->PB.a600V_V2_2ndVPB.myMac[1];
        out << pbu->PB.a600V_V2_2ndVPB.myMac[2];
        out << pbu->PB.a600V_V2_2ndVPB.myMac[3];
        out << pbu->PB.a600V_V2_2ndVPB.myMac[4];
        out << pbu->PB.a600V_V2_2ndVPB.myMac[5];
        out << pbu->PB.a600V_V2_2ndVPB.dFk[0];
        out << pbu->PB.a600V_V2_2ndVPB.dFk[1];
        out << pbu->PB.a600V_V2_2ndVPB.dFk[2];
        out << pbu->PB.a600V_V2_2ndVPB.dFk[3];
        out << pbu->PB.a600V_V2_2ndVPB.vrefPolynom[0];
        out << pbu->PB.a600V_V2_2ndVPB.vrefPolynom[1];
        out << pbu->PB.a600V_V2_2ndVPB.vrefPolynom[2];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[0][0];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[0][1];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[1][0];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[1][1];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[2][0];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[2][1];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[3][0];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[3][1];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[4][0];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[4][1];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[5][0];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[5][1];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[6][0];
        out << pbu->PB.a600V_V2_2ndVPB.linearK[6][1];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[0];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[1];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[2];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[3];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[4];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[5];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[6];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[7];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[8];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[9];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[10];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[11];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[12];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[13];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[14];
        out << pbu->PB.a600V_V2_2ndVPB.curKey[15];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[0];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[1];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[2];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[3];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[4];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[5];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[6];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[7];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[8];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[9];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[10];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[11];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[12];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[13];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[14];
        out << pbu->PB.a600V_V2_2ndVPB.curIV[15];
        out << pbu->PB.a600V_V2_2ndVPB.fetFailureCount;
        out << pbu->PB.a600V_V2_2ndVPB.fetCurrentThreshold;
        out << pbu->PB.a600V_V2_2ndVPB.fetDeltaCurrent;
        out << pbu->PB.a600V_V2_2ndVPB.LowCurrentLimitTo255;
        out << pbu->PB.a600V_V2_2ndVPB.VhvLimitVout;
        out << pbu->PB.a600V_V2_2ndVPB.IhvLimitVout;
        out << pbu->PB.a600V_V2_2ndVPB.VhvLimitVins;
        out << pbu->PB.a600V_V2_2ndVPB.IhvLimitVins;
        out << pbu->PB.a600V_V2_2ndVPB.versionSuffix[0];
        out << pbu->PB.a600V_V2_2ndVPB.versionSuffix[1];
        out << pbu->PB.a600V_V2_2ndVPB.versionSuffix[2];
        out << pbu->PB.a600V_V2_2ndVPB.tests;
        out << pbu->PB.a600V_V2_2ndVPB.installDate;
        out << pbu->PB.a600V_V2_2ndVPB.k_ov_volt;
        out << pbu->PB.a600V_V2_2ndVPB.k_oc_cur;
        out << pbu->PB.a600V_V2_2ndVPB.syncword;
        out << pbu->PB.a600V_V2_2ndVPB.vin_disable_radio;
        out << pbu->PB.a600V_V2_2ndVPB.rbunch;
        out << pbu->PB.a600V_V2_2ndVPB.gbunch;
        out << pbu->PB.a600V_V2_2ndVPB.shortCircuitLevel;
        out << pbu->PB.a600V_V2_2ndVPB.reserved;
        out << pbu->PB.a600V_V2_2ndVPB.synch_phase;
        out << pbu->PB.a600V_V2_2ndVPB.synch_freq;
        out << pbu->PB.a600V_V2_2ndVPB.bandwidth250;
        out << pbu->PB.a600V_V2_2ndVPB.channel;
        out << pbu->PB.a600V_V2_2ndVPB.utcProgram;
        out << pbu->PB.a600V_V2_2ndVPB.utcLow;
        out << pbu->PB.a600V_V2_2ndVPB.utcHigh;
        out << pbu->PB.a600V_V2_2ndVPB.tkCurrent;
        out << pbu->PB.a600V_V2_2ndVPB.tkPower;
        out << pbu->PB.a600V_V2_2ndVPB.mpp;
        out << pbu->PB.a600V_V2_2ndVPB.module;
        out << pbu->PB.a600V_V2_2ndVPB.ov;
        out << pbu->PB.a600V_V2_2ndVPB.oc;
        out << pbu->PB.a600V_V2_2ndVPB.radioPower;
        out << pbu->PB.a600V_V2_2ndVPB.edAddr;
        out << pbu->PB.a600V_V2_2ndVPB.gwAddr;
        out << pbu->PB.a600V_V2_2ndVPB.repeaterChannel;
        out << pbu->PB.a600V_V2_2ndVPB.repeaterPower;
        out << pbu->PB.a600V_V2_2ndVPB.showState;
        out << pbu->PB.a600V_V2_2ndVPB.CriticalLevel500;
        out << pbu->PB.a600V_V2_2ndVPB.CriticalLevel10;
        out << pbu->PB.a600V_V2_2ndVPB.pureOffset;
        out << pbu->PB.a600V_V2_2ndVPB.defCyclesTo500;
        out << pbu->PB.a600V_V2_2ndVPB.defCyclesTo10;
        out << pbu->PB.a600V_V2_2ndVPB.defCyclesToStep500Channel;
        out << pbu->PB.a600V_V2_2ndVPB.defCyclesToStep10Channel;
        out << pbu->PB.a600V_V2_2ndVPB.defCycles2SoftKick;
        out << pbu->PB.a600V_V2_2ndVPB.defCycles2HardKick;
        out << pbu->PB.a600V_V2_2ndVPB.imageAddr;
        out << pbu->PB.a600V_V2_2ndVPB.versionLow;
        out << pbu->PB.a600V_V2_2ndVPB.versionHigh;
        out << pbu->PB.a600V_V2_2ndVPB.starting500Channel;
        out << pbu->PB.a600V_V2_2ndVPB.boolByte2;
        out << pbu->PB.a600V_V2_2ndVPB.prepAddr;
        out << pbu->PB.a600V_V2_2ndVPB.repStep;
        out << pbu->PB.a600V_V2_2ndVPB.ov_startup;
        out << pbu->PB.a600V_V2_2ndVPB.t_mod_off;
        out << pbu->PB.a600V_V2_2ndVPB.toff_fallback;
        out << pbu->PB.a600V_V2_2ndVPB.ton_fallback;
        out << pbu->PB.a600V_V2_2ndVPB.fallback_time;
        out << pbu->PB.a600V_V2_2ndVPB.network_cnst_1;
        out << pbu->PB.a600V_V2_2ndVPB.network_cnst_2;
        out << pbu->PB.a600V_V2_2ndVPB.oc_protection;
        out << pbu->PB.a600V_V2_2ndVPB.oc_step;
        out << pbu->PB.a600V_V2_2ndVPB.cur_noise;
        out << pbu->PB.a600V_V2_2ndVPB.ov_step;
        out << pbu->PB.a600V_V2_2ndVPB.shunt;
        out << pbu->PB.a600V_V2_2ndVPB.max_off;
        out << pbu->PB.a600V_V2_2ndVPB.vin_limit;
        out << pbu->PB.a600V_V2_2ndVPB.vin_turn_on;
        out << pbu->PB.a600V_V2_2ndVPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1300V_Shunt)
    {
        out << pbu->PB.a1300VPB.barrier;
        out << pbu->PB.a1300VPB.netId;
        out << pbu->PB.a1300VPB.myBunch;
        out << pbu->PB.a1300VPB.groupId;
        out << pbu->PB.a1300VPB.myMac[0];
        out << pbu->PB.a1300VPB.myMac[1];
        out << pbu->PB.a1300VPB.myMac[2];
        out << pbu->PB.a1300VPB.myMac[3];
        out << pbu->PB.a1300VPB.myMac[4];
        out << pbu->PB.a1300VPB.myMac[5];
        out << pbu->PB.a1300VPB.dFk[0];
        out << pbu->PB.a1300VPB.dFk[1];
        out << pbu->PB.a1300VPB.dFk[2];
        out << pbu->PB.a1300VPB.dFk[3];
        out << pbu->PB.a1300VPB.vrefPolynom[0];
        out << pbu->PB.a1300VPB.vrefPolynom[1];
        out << pbu->PB.a1300VPB.vrefPolynom[2];
        out << pbu->PB.a1300VPB.linearK[0][0];
        out << pbu->PB.a1300VPB.linearK[0][1];
        out << pbu->PB.a1300VPB.linearK[1][0];
        out << pbu->PB.a1300VPB.linearK[1][1];
        out << pbu->PB.a1300VPB.linearK[2][0];
        out << pbu->PB.a1300VPB.linearK[2][1];
        out << pbu->PB.a1300VPB.linearK[3][0];
        out << pbu->PB.a1300VPB.linearK[3][1];
        out << pbu->PB.a1300VPB.linearK[4][0];
        out << pbu->PB.a1300VPB.linearK[4][1];
        out << pbu->PB.a1300VPB.linearK[5][0];
        out << pbu->PB.a1300VPB.linearK[5][1];
        out << pbu->PB.a1300VPB.linearK[6][0];
        out << pbu->PB.a1300VPB.linearK[6][1];
        out << pbu->PB.a1300VPB.curKey[0];
        out << pbu->PB.a1300VPB.curKey[1];
        out << pbu->PB.a1300VPB.curKey[2];
        out << pbu->PB.a1300VPB.curKey[3];
        out << pbu->PB.a1300VPB.curKey[4];
        out << pbu->PB.a1300VPB.curKey[5];
        out << pbu->PB.a1300VPB.curKey[6];
        out << pbu->PB.a1300VPB.curKey[7];
        out << pbu->PB.a1300VPB.curKey[8];
        out << pbu->PB.a1300VPB.curKey[9];
        out << pbu->PB.a1300VPB.curKey[10];
        out << pbu->PB.a1300VPB.curKey[11];
        out << pbu->PB.a1300VPB.curKey[12];
        out << pbu->PB.a1300VPB.curKey[13];
        out << pbu->PB.a1300VPB.curKey[14];
        out << pbu->PB.a1300VPB.curKey[15];
        out << pbu->PB.a1300VPB.curIV[0];
        out << pbu->PB.a1300VPB.curIV[1];
        out << pbu->PB.a1300VPB.curIV[2];
        out << pbu->PB.a1300VPB.curIV[3];
        out << pbu->PB.a1300VPB.curIV[4];
        out << pbu->PB.a1300VPB.curIV[5];
        out << pbu->PB.a1300VPB.curIV[6];
        out << pbu->PB.a1300VPB.curIV[7];
        out << pbu->PB.a1300VPB.curIV[8];
        out << pbu->PB.a1300VPB.curIV[9];
        out << pbu->PB.a1300VPB.curIV[10];
        out << pbu->PB.a1300VPB.curIV[11];
        out << pbu->PB.a1300VPB.curIV[12];
        out << pbu->PB.a1300VPB.curIV[13];
        out << pbu->PB.a1300VPB.curIV[14];
        out << pbu->PB.a1300VPB.curIV[15];
        out << pbu->PB.a1300VPB.fetFailureCount;
        out << pbu->PB.a1300VPB.fetCurrentThreshold;
        out << pbu->PB.a1300VPB.fetDeltaCurrent;
        out << pbu->PB.a1300VPB.LowCurrentLimitTo255;
        out << pbu->PB.a1300VPB.VhvLimitVout;
        out << pbu->PB.a1300VPB.IhvLimitVout;
        out << pbu->PB.a1300VPB.VhvLimitVins;
        out << pbu->PB.a1300VPB.IhvLimitVins;
        out << pbu->PB.a1300VPB.versionSuffix[0];
        out << pbu->PB.a1300VPB.versionSuffix[1];
        out << pbu->PB.a1300VPB.versionSuffix[2];
        out << pbu->PB.a1300VPB.tests;
        out << pbu->PB.a1300VPB.installDate;
        out << pbu->PB.a1300VPB.k_ov_volt;
        out << pbu->PB.a1300VPB.k_oc_cur;
        out << pbu->PB.a1300VPB.syncword;
        out << pbu->PB.a1300VPB.vin_disable_radio;
        out << pbu->PB.a1300VPB.rbunch;
        out << pbu->PB.a1300VPB.gbunch;
        out << pbu->PB.a1300VPB.shortCircuitLevel;
        out << pbu->PB.a1300VPB.reserved;
        out << pbu->PB.a1300VPB.synch_phase;
        out << pbu->PB.a1300VPB.synch_freq;
        out << pbu->PB.a1300VPB.bandwidth250;
        out << pbu->PB.a1300VPB.channel;
        out << pbu->PB.a1300VPB.utcProgram;
        out << pbu->PB.a1300VPB.utcLow;
        out << pbu->PB.a1300VPB.utcHigh;
        out << pbu->PB.a1300VPB.tkCurrent;
        out << pbu->PB.a1300VPB.tkPower;
        out << pbu->PB.a1300VPB.mpp;
        out << pbu->PB.a1300VPB.module;
        out << pbu->PB.a1300VPB.ov;
        out << pbu->PB.a1300VPB.oc;
        out << pbu->PB.a1300VPB.radioPower;
        out << pbu->PB.a1300VPB.edAddr;
        out << pbu->PB.a1300VPB.gwAddr;
        out << pbu->PB.a1300VPB.repeaterChannel;
        out << pbu->PB.a1300VPB.repeaterPower;
        out << pbu->PB.a1300VPB.showState;
        out << pbu->PB.a1300VPB.CriticalLevel500;
        out << pbu->PB.a1300VPB.CriticalLevel10;
        out << pbu->PB.a1300VPB.pureOffset;
        out << pbu->PB.a1300VPB.defCyclesTo500;
        out << pbu->PB.a1300VPB.defCyclesTo10;
        out << pbu->PB.a1300VPB.defCyclesToStep500Channel;
        out << pbu->PB.a1300VPB.defCyclesToStep10Channel;
        out << pbu->PB.a1300VPB.defCycles2SoftKick;
        out << pbu->PB.a1300VPB.defCycles2HardKick;
        out << pbu->PB.a1300VPB.imageAddr;
        out << pbu->PB.a1300VPB.versionLow;
        out << pbu->PB.a1300VPB.versionHigh;
        out << pbu->PB.a1300VPB.starting500Channel;
        out << pbu->PB.a1300VPB.boolByte2;
        out << pbu->PB.a1300VPB.prepAddr;
        out << pbu->PB.a1300VPB.repStep;
        out << pbu->PB.a1300VPB.ov_startup;
        out << pbu->PB.a1300VPB.t_mod_off;
        out << pbu->PB.a1300VPB.toff_fallback;
        out << pbu->PB.a1300VPB.ton_fallback;
        out << pbu->PB.a1300VPB.fallback_time;
        out << pbu->PB.a1300VPB.network_cnst_1;
        out << pbu->PB.a1300VPB.network_cnst_2;
        out << pbu->PB.a1300VPB.oc_protection;
        out << pbu->PB.a1300VPB.oc_step;
        out << pbu->PB.a1300VPB.cur_noise;
        out << pbu->PB.a1300VPB.ov_step;
        out << pbu->PB.a1300VPB.shunt;
        out << pbu->PB.a1300VPB.max_off;
        out << pbu->PB.a1300VPB.vin_limit;
        out << pbu->PB.a1300VPB.vin_turn_on;
        out << pbu->PB.a1300VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1300V_2nd_Shunt)
    {
        out << pbu->PB.a1300_2ndVPB.barrier;
        out << pbu->PB.a1300_2ndVPB.netId;
        out << pbu->PB.a1300_2ndVPB.myBunch;
        out << pbu->PB.a1300_2ndVPB.groupId;
        out << pbu->PB.a1300_2ndVPB.myMac[0];
        out << pbu->PB.a1300_2ndVPB.myMac[1];
        out << pbu->PB.a1300_2ndVPB.myMac[2];
        out << pbu->PB.a1300_2ndVPB.myMac[3];
        out << pbu->PB.a1300_2ndVPB.myMac[4];
        out << pbu->PB.a1300_2ndVPB.myMac[5];
        out << pbu->PB.a1300_2ndVPB.dFk[0];
        out << pbu->PB.a1300_2ndVPB.dFk[1];
        out << pbu->PB.a1300_2ndVPB.dFk[2];
        out << pbu->PB.a1300_2ndVPB.dFk[3];
        out << pbu->PB.a1300_2ndVPB.vrefPolynom[0];
        out << pbu->PB.a1300_2ndVPB.vrefPolynom[1];
        out << pbu->PB.a1300_2ndVPB.vrefPolynom[2];
        out << pbu->PB.a1300_2ndVPB.linearK[0][0];
        out << pbu->PB.a1300_2ndVPB.linearK[0][1];
        out << pbu->PB.a1300_2ndVPB.linearK[1][0];
        out << pbu->PB.a1300_2ndVPB.linearK[1][1];
        out << pbu->PB.a1300_2ndVPB.linearK[2][0];
        out << pbu->PB.a1300_2ndVPB.linearK[2][1];
        out << pbu->PB.a1300_2ndVPB.linearK[3][0];
        out << pbu->PB.a1300_2ndVPB.linearK[3][1];
        out << pbu->PB.a1300_2ndVPB.linearK[4][0];
        out << pbu->PB.a1300_2ndVPB.linearK[4][1];
        out << pbu->PB.a1300_2ndVPB.linearK[5][0];
        out << pbu->PB.a1300_2ndVPB.linearK[5][1];
        out << pbu->PB.a1300_2ndVPB.linearK[6][0];
        out << pbu->PB.a1300_2ndVPB.linearK[6][1];
        out << pbu->PB.a1300_2ndVPB.curKey[0];
        out << pbu->PB.a1300_2ndVPB.curKey[1];
        out << pbu->PB.a1300_2ndVPB.curKey[2];
        out << pbu->PB.a1300_2ndVPB.curKey[3];
        out << pbu->PB.a1300_2ndVPB.curKey[4];
        out << pbu->PB.a1300_2ndVPB.curKey[5];
        out << pbu->PB.a1300_2ndVPB.curKey[6];
        out << pbu->PB.a1300_2ndVPB.curKey[7];
        out << pbu->PB.a1300_2ndVPB.curKey[8];
        out << pbu->PB.a1300_2ndVPB.curKey[9];
        out << pbu->PB.a1300_2ndVPB.curKey[10];
        out << pbu->PB.a1300_2ndVPB.curKey[11];
        out << pbu->PB.a1300_2ndVPB.curKey[12];
        out << pbu->PB.a1300_2ndVPB.curKey[13];
        out << pbu->PB.a1300_2ndVPB.curKey[14];
        out << pbu->PB.a1300_2ndVPB.curKey[15];
        out << pbu->PB.a1300_2ndVPB.curIV[0];
        out << pbu->PB.a1300_2ndVPB.curIV[1];
        out << pbu->PB.a1300_2ndVPB.curIV[2];
        out << pbu->PB.a1300_2ndVPB.curIV[3];
        out << pbu->PB.a1300_2ndVPB.curIV[4];
        out << pbu->PB.a1300_2ndVPB.curIV[5];
        out << pbu->PB.a1300_2ndVPB.curIV[6];
        out << pbu->PB.a1300_2ndVPB.curIV[7];
        out << pbu->PB.a1300_2ndVPB.curIV[8];
        out << pbu->PB.a1300_2ndVPB.curIV[9];
        out << pbu->PB.a1300_2ndVPB.curIV[10];
        out << pbu->PB.a1300_2ndVPB.curIV[11];
        out << pbu->PB.a1300_2ndVPB.curIV[12];
        out << pbu->PB.a1300_2ndVPB.curIV[13];
        out << pbu->PB.a1300_2ndVPB.curIV[14];
        out << pbu->PB.a1300_2ndVPB.curIV[15];
        out << pbu->PB.a1300_2ndVPB.fetFailureCount;
        out << pbu->PB.a1300_2ndVPB.fetCurrentThreshold;
        out << pbu->PB.a1300_2ndVPB.fetDeltaCurrent;
        out << pbu->PB.a1300_2ndVPB.LowCurrentLimitTo255;
        out << pbu->PB.a1300_2ndVPB.VhvLimitVout;
        out << pbu->PB.a1300_2ndVPB.IhvLimitVout;
        out << pbu->PB.a1300_2ndVPB.VhvLimitVins;
        out << pbu->PB.a1300_2ndVPB.IhvLimitVins;
        out << pbu->PB.a1300_2ndVPB.versionSuffix[0];
        out << pbu->PB.a1300_2ndVPB.versionSuffix[1];
        out << pbu->PB.a1300_2ndVPB.versionSuffix[2];
        out << pbu->PB.a1300_2ndVPB.tests;
        out << pbu->PB.a1300_2ndVPB.installDate;
        out << pbu->PB.a1300_2ndVPB.k_ov_volt;
        out << pbu->PB.a1300_2ndVPB.k_oc_cur;
        out << pbu->PB.a1300_2ndVPB.syncword;
        out << pbu->PB.a1300_2ndVPB.vin_disable_radio;
        out << pbu->PB.a1300_2ndVPB.rbunch;
        out << pbu->PB.a1300_2ndVPB.gbunch;
        out << pbu->PB.a1300_2ndVPB.shortCircuitLevel;
        out << pbu->PB.a1300_2ndVPB.reserved;
        out << pbu->PB.a1300_2ndVPB.synch_phase;
        out << pbu->PB.a1300_2ndVPB.synch_freq;
        out << pbu->PB.a1300_2ndVPB.bandwidth250;
        out << pbu->PB.a1300_2ndVPB.channel;
        out << pbu->PB.a1300_2ndVPB.utcProgram;
        out << pbu->PB.a1300_2ndVPB.utcLow;
        out << pbu->PB.a1300_2ndVPB.utcHigh;
        out << pbu->PB.a1300_2ndVPB.tkCurrent;
        out << pbu->PB.a1300_2ndVPB.tkPower;
        out << pbu->PB.a1300_2ndVPB.mpp;
        out << pbu->PB.a1300_2ndVPB.module;
        out << pbu->PB.a1300_2ndVPB.ov;
        out << pbu->PB.a1300_2ndVPB.oc;
        out << pbu->PB.a1300_2ndVPB.radioPower;
        out << pbu->PB.a1300_2ndVPB.edAddr;
        out << pbu->PB.a1300_2ndVPB.gwAddr;
        out << pbu->PB.a1300_2ndVPB.repeaterChannel;
        out << pbu->PB.a1300_2ndVPB.repeaterPower;
        out << pbu->PB.a1300_2ndVPB.showState;
        out << pbu->PB.a1300_2ndVPB.CriticalLevel500;
        out << pbu->PB.a1300_2ndVPB.CriticalLevel10;
        out << pbu->PB.a1300_2ndVPB.pureOffset;
        out << pbu->PB.a1300_2ndVPB.defCyclesTo500;
        out << pbu->PB.a1300_2ndVPB.defCyclesTo10;
        out << pbu->PB.a1300_2ndVPB.defCyclesToStep500Channel;
        out << pbu->PB.a1300_2ndVPB.defCyclesToStep10Channel;
        out << pbu->PB.a1300_2ndVPB.defCycles2SoftKick;
        out << pbu->PB.a1300_2ndVPB.defCycles2HardKick;
        out << pbu->PB.a1300_2ndVPB.imageAddr;
        out << pbu->PB.a1300_2ndVPB.versionLow;
        out << pbu->PB.a1300_2ndVPB.versionHigh;
        out << pbu->PB.a1300_2ndVPB.starting500Channel;
        out << pbu->PB.a1300_2ndVPB.boolByte2;
        out << pbu->PB.a1300_2ndVPB.prepAddr;
        out << pbu->PB.a1300_2ndVPB.repStep;
        out << pbu->PB.a1300_2ndVPB.ov_startup;
        out << pbu->PB.a1300_2ndVPB.t_mod_off;
        out << pbu->PB.a1300_2ndVPB.toff_fallback;
        out << pbu->PB.a1300_2ndVPB.ton_fallback;
        out << pbu->PB.a1300_2ndVPB.fallback_time;
        out << pbu->PB.a1300_2ndVPB.network_cnst_1;
        out << pbu->PB.a1300_2ndVPB.network_cnst_2;
        out << pbu->PB.a1300_2ndVPB.oc_protection;
        out << pbu->PB.a1300_2ndVPB.oc_step;
        out << pbu->PB.a1300_2ndVPB.cur_noise;
        out << pbu->PB.a1300_2ndVPB.ov_step;
        out << pbu->PB.a1300_2ndVPB.shunt;
        out << pbu->PB.a1300_2ndVPB.max_off;
        out << pbu->PB.a1300_2ndVPB.vin_limit;
        out << pbu->PB.a1300_2ndVPB.vin_turn_on;
        out << pbu->PB.a1300_2ndVPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1500V_Shunt)
    {
        out << pbu->PB.a1500VPB.barrier;
        out << pbu->PB.a1500VPB.netId;
        out << pbu->PB.a1500VPB.myBunch;
        out << pbu->PB.a1500VPB.groupId;
        out << pbu->PB.a1500VPB.myMac[0];
        out << pbu->PB.a1500VPB.myMac[1];
        out << pbu->PB.a1500VPB.myMac[2];
        out << pbu->PB.a1500VPB.myMac[3];
        out << pbu->PB.a1500VPB.myMac[4];
        out << pbu->PB.a1500VPB.myMac[5];
        out << pbu->PB.a1500VPB.dFk[0];
        out << pbu->PB.a1500VPB.dFk[1];
        out << pbu->PB.a1500VPB.dFk[2];
        out << pbu->PB.a1500VPB.dFk[3];
        out << pbu->PB.a1500VPB.vrefPolynom[0];
        out << pbu->PB.a1500VPB.vrefPolynom[1];
        out << pbu->PB.a1500VPB.vrefPolynom[2];
        out << pbu->PB.a1500VPB.linearK[0][0];
        out << pbu->PB.a1500VPB.linearK[0][1];
        out << pbu->PB.a1500VPB.linearK[1][0];
        out << pbu->PB.a1500VPB.linearK[1][1];
        out << pbu->PB.a1500VPB.linearK[2][0];
        out << pbu->PB.a1500VPB.linearK[2][1];
        out << pbu->PB.a1500VPB.linearK[3][0];
        out << pbu->PB.a1500VPB.linearK[3][1];
        out << pbu->PB.a1500VPB.linearK[4][0];
        out << pbu->PB.a1500VPB.linearK[4][1];
        out << pbu->PB.a1500VPB.linearK[5][0];
        out << pbu->PB.a1500VPB.linearK[5][1];
        out << pbu->PB.a1500VPB.linearK[6][0];
        out << pbu->PB.a1500VPB.linearK[6][1];
        out << pbu->PB.a1500VPB.curKey[0];
        out << pbu->PB.a1500VPB.curKey[1];
        out << pbu->PB.a1500VPB.curKey[2];
        out << pbu->PB.a1500VPB.curKey[3];
        out << pbu->PB.a1500VPB.curKey[4];
        out << pbu->PB.a1500VPB.curKey[5];
        out << pbu->PB.a1500VPB.curKey[6];
        out << pbu->PB.a1500VPB.curKey[7];
        out << pbu->PB.a1500VPB.curKey[8];
        out << pbu->PB.a1500VPB.curKey[9];
        out << pbu->PB.a1500VPB.curKey[10];
        out << pbu->PB.a1500VPB.curKey[11];
        out << pbu->PB.a1500VPB.curKey[12];
        out << pbu->PB.a1500VPB.curKey[13];
        out << pbu->PB.a1500VPB.curKey[14];
        out << pbu->PB.a1500VPB.curKey[15];
        out << pbu->PB.a1500VPB.curIV[0];
        out << pbu->PB.a1500VPB.curIV[1];
        out << pbu->PB.a1500VPB.curIV[2];
        out << pbu->PB.a1500VPB.curIV[3];
        out << pbu->PB.a1500VPB.curIV[4];
        out << pbu->PB.a1500VPB.curIV[5];
        out << pbu->PB.a1500VPB.curIV[6];
        out << pbu->PB.a1500VPB.curIV[7];
        out << pbu->PB.a1500VPB.curIV[8];
        out << pbu->PB.a1500VPB.curIV[9];
        out << pbu->PB.a1500VPB.curIV[10];
        out << pbu->PB.a1500VPB.curIV[11];
        out << pbu->PB.a1500VPB.curIV[12];
        out << pbu->PB.a1500VPB.curIV[13];
        out << pbu->PB.a1500VPB.curIV[14];
        out << pbu->PB.a1500VPB.curIV[15];
        out << pbu->PB.a1500VPB.fetFailureCount;
        out << pbu->PB.a1500VPB.fetCurrentThreshold;
        out << pbu->PB.a1500VPB.fetDeltaCurrent;
        out << pbu->PB.a1500VPB.LowCurrentLimitTo255;
        out << pbu->PB.a1500VPB.VoutLimitCount;
        out << pbu->PB.a1500VPB.VoutLimit;
        out << pbu->PB.a1500VPB.IoutLimitCount;
        out << pbu->PB.a1500VPB.IoutLimit;
        out << pbu->PB.a1500VPB.versionSuffix[0];
        out << pbu->PB.a1500VPB.versionSuffix[1];
        out << pbu->PB.a1500VPB.versionSuffix[2];
        out << pbu->PB.a1500VPB.tests;
        out << pbu->PB.a1500VPB.installDate;
        out << pbu->PB.a1500VPB.k_ov_volt;
        out << pbu->PB.a1500VPB.k_oc_cur;
        out << pbu->PB.a1500VPB.syncword;
        out << pbu->PB.a1500VPB.vin_disable_radio;
        out << pbu->PB.a1500VPB.rbunch;
        out << pbu->PB.a1500VPB.gbunch;
        out << pbu->PB.a1500VPB.shortCircuitLevel;
        out << pbu->PB.a1500VPB.reserved;
        out << pbu->PB.a1500VPB.synch_phase;
        out << pbu->PB.a1500VPB.synch_freq;
        out << pbu->PB.a1500VPB.bandwidth250;
        out << pbu->PB.a1500VPB.channel;
        out << pbu->PB.a1500VPB.utcProgram;
        out << pbu->PB.a1500VPB.utcLow;
        out << pbu->PB.a1500VPB.utcHigh;
        out << pbu->PB.a1500VPB.tkCurrent;
        out << pbu->PB.a1500VPB.tkPower;
        out << pbu->PB.a1500VPB.mpp;
        out << pbu->PB.a1500VPB.module;
        out << pbu->PB.a1500VPB.ov;
        out << pbu->PB.a1500VPB.oc;
        out << pbu->PB.a1500VPB.radioPower;
        out << pbu->PB.a1500VPB.edAddr;
        out << pbu->PB.a1500VPB.gwAddr;
        out << pbu->PB.a1500VPB.repeaterChannel;
        out << pbu->PB.a1500VPB.repeaterPower;
        out << pbu->PB.a1500VPB.showState;
        out << pbu->PB.a1500VPB.CriticalLevel500;
        out << pbu->PB.a1500VPB.CriticalLevel10;
        out << pbu->PB.a1500VPB.pureOffset;
        out << pbu->PB.a1500VPB.defCyclesTo500;
        out << pbu->PB.a1500VPB.defCyclesTo10;
        out << pbu->PB.a1500VPB.defCyclesToStep500Channel;
        out << pbu->PB.a1500VPB.defCyclesToStep10Channel;
        out << pbu->PB.a1500VPB.defCycles2SoftKick;
        out << pbu->PB.a1500VPB.defCycles2HardKick;
        out << pbu->PB.a1500VPB.imageAddr;
        out << pbu->PB.a1500VPB.versionLow;
        out << pbu->PB.a1500VPB.versionHigh;
        out << pbu->PB.a1500VPB.starting500Channel;
        out << pbu->PB.a1500VPB.boolByte2;
        out << pbu->PB.a1500VPB.prepAddr;
        out << pbu->PB.a1500VPB.repStep;
        out << pbu->PB.a1500VPB.ov_startup;
        out << pbu->PB.a1500VPB.t_mod_off;
        out << pbu->PB.a1500VPB.toff_fallback;
        out << pbu->PB.a1500VPB.ton_fallback;
        out << pbu->PB.a1500VPB.fallback_time;
        out << pbu->PB.a1500VPB.network_cnst_1;
        out << pbu->PB.a1500VPB.network_cnst_2;
        out << pbu->PB.a1500VPB.oc_protection;
        out << pbu->PB.a1500VPB.oc_step;
        out << pbu->PB.a1500VPB.cur_noise;
        out << pbu->PB.a1500VPB.ov_step;
        out << pbu->PB.a1500VPB.shunt;
        out << pbu->PB.a1500VPB.max_off;
        out << pbu->PB.a1500VPB.vin_limit;
        out << pbu->PB.a1500VPB.vin_turn_on;
        out << pbu->PB.a1500VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1500V_2nd_Shunt)
    {
        out << pbu->PB.a1500_2ndVPB.barrier;
        out << pbu->PB.a1500_2ndVPB.netId;
        out << pbu->PB.a1500_2ndVPB.myBunch;
        out << pbu->PB.a1500_2ndVPB.groupId;
        out << pbu->PB.a1500_2ndVPB.myMac[0];
        out << pbu->PB.a1500_2ndVPB.myMac[1];
        out << pbu->PB.a1500_2ndVPB.myMac[2];
        out << pbu->PB.a1500_2ndVPB.myMac[3];
        out << pbu->PB.a1500_2ndVPB.myMac[4];
        out << pbu->PB.a1500_2ndVPB.myMac[5];
        out << pbu->PB.a1500_2ndVPB.dFk[0];
        out << pbu->PB.a1500_2ndVPB.dFk[1];
        out << pbu->PB.a1500_2ndVPB.dFk[2];
        out << pbu->PB.a1500_2ndVPB.dFk[3];
        out << pbu->PB.a1500_2ndVPB.vrefPolynom[0];
        out << pbu->PB.a1500_2ndVPB.vrefPolynom[1];
        out << pbu->PB.a1500_2ndVPB.vrefPolynom[2];
        out << pbu->PB.a1500_2ndVPB.linearK[0][0];
        out << pbu->PB.a1500_2ndVPB.linearK[0][1];
        out << pbu->PB.a1500_2ndVPB.linearK[1][0];
        out << pbu->PB.a1500_2ndVPB.linearK[1][1];
        out << pbu->PB.a1500_2ndVPB.linearK[2][0];
        out << pbu->PB.a1500_2ndVPB.linearK[2][1];
        out << pbu->PB.a1500_2ndVPB.linearK[3][0];
        out << pbu->PB.a1500_2ndVPB.linearK[3][1];
        out << pbu->PB.a1500_2ndVPB.linearK[4][0];
        out << pbu->PB.a1500_2ndVPB.linearK[4][1];
        out << pbu->PB.a1500_2ndVPB.linearK[5][0];
        out << pbu->PB.a1500_2ndVPB.linearK[5][1];
        out << pbu->PB.a1500_2ndVPB.linearK[6][0];
        out << pbu->PB.a1500_2ndVPB.linearK[6][1];
        out << pbu->PB.a1500_2ndVPB.curKey[0];
        out << pbu->PB.a1500_2ndVPB.curKey[1];
        out << pbu->PB.a1500_2ndVPB.curKey[2];
        out << pbu->PB.a1500_2ndVPB.curKey[3];
        out << pbu->PB.a1500_2ndVPB.curKey[4];
        out << pbu->PB.a1500_2ndVPB.curKey[5];
        out << pbu->PB.a1500_2ndVPB.curKey[6];
        out << pbu->PB.a1500_2ndVPB.curKey[7];
        out << pbu->PB.a1500_2ndVPB.curKey[8];
        out << pbu->PB.a1500_2ndVPB.curKey[9];
        out << pbu->PB.a1500_2ndVPB.curKey[10];
        out << pbu->PB.a1500_2ndVPB.curKey[11];
        out << pbu->PB.a1500_2ndVPB.curKey[12];
        out << pbu->PB.a1500_2ndVPB.curKey[13];
        out << pbu->PB.a1500_2ndVPB.curKey[14];
        out << pbu->PB.a1500_2ndVPB.curKey[15];
        out << pbu->PB.a1500_2ndVPB.curIV[0];
        out << pbu->PB.a1500_2ndVPB.curIV[1];
        out << pbu->PB.a1500_2ndVPB.curIV[2];
        out << pbu->PB.a1500_2ndVPB.curIV[3];
        out << pbu->PB.a1500_2ndVPB.curIV[4];
        out << pbu->PB.a1500_2ndVPB.curIV[5];
        out << pbu->PB.a1500_2ndVPB.curIV[6];
        out << pbu->PB.a1500_2ndVPB.curIV[7];
        out << pbu->PB.a1500_2ndVPB.curIV[8];
        out << pbu->PB.a1500_2ndVPB.curIV[9];
        out << pbu->PB.a1500_2ndVPB.curIV[10];
        out << pbu->PB.a1500_2ndVPB.curIV[11];
        out << pbu->PB.a1500_2ndVPB.curIV[12];
        out << pbu->PB.a1500_2ndVPB.curIV[13];
        out << pbu->PB.a1500_2ndVPB.curIV[14];
        out << pbu->PB.a1500_2ndVPB.curIV[15];
        out << pbu->PB.a1500_2ndVPB.ef_InputCurrentThreshold;
        out << pbu->PB.a1500_2ndVPB.ef_OccurrenceThreshold;
        out << pbu->PB.a1500_2ndVPB.ef_CountDownTimer;
        out << pbu->PB.a1500_2ndVPB.ef_AlphaNumerator;
        out << pbu->PB.a1500_2ndVPB.ef_ModuleOff;
        out << pbu->PB.a1500_2ndVPB.LowCurrentLimitTo255;
        out << pbu->PB.a1500_2ndVPB.VoutLimitCount;
        out << pbu->PB.a1500_2ndVPB.VoutLimit;
        out << pbu->PB.a1500_2ndVPB.IoutLimitCount;
        out << pbu->PB.a1500_2ndVPB.IoutLimit;
        out << pbu->PB.a1500_2ndVPB.versionSuffix[0];
        out << pbu->PB.a1500_2ndVPB.versionSuffix[1];
        out << pbu->PB.a1500_2ndVPB.versionSuffix[2];
        out << pbu->PB.a1500_2ndVPB.monitoring;
        out << pbu->PB.a1500_2ndVPB.installDate;
        out << pbu->PB.a1500_2ndVPB.k_ov_volt;
        out << pbu->PB.a1500_2ndVPB.k_oc_cur;
        out << pbu->PB.a1500_2ndVPB.syncword;
        out << pbu->PB.a1500_2ndVPB.vin_disable_radio;
        out << pbu->PB.a1500_2ndVPB.rbunch;
        out << pbu->PB.a1500_2ndVPB.gbunch;
        out << pbu->PB.a1500_2ndVPB.shortCircuitLevel;
        out << pbu->PB.a1500_2ndVPB.reserved;
        out << pbu->PB.a1500_2ndVPB.synch_phase;
        out << pbu->PB.a1500_2ndVPB.synch_freq;
        out << pbu->PB.a1500_2ndVPB.bandwidth250;
        out << pbu->PB.a1500_2ndVPB.channel;
        out << pbu->PB.a1500_2ndVPB.utcProgram;
        out << pbu->PB.a1500_2ndVPB.utcLow;
        out << pbu->PB.a1500_2ndVPB.utcHigh;
        out << pbu->PB.a1500_2ndVPB.tkCurrent;
        out << pbu->PB.a1500_2ndVPB.tkPower;
        out << pbu->PB.a1500_2ndVPB.mpp;
        out << pbu->PB.a1500_2ndVPB.module;
        out << pbu->PB.a1500_2ndVPB.ov;
        out << pbu->PB.a1500_2ndVPB.oc;
        out << pbu->PB.a1500_2ndVPB.radioPower;
        out << pbu->PB.a1500_2ndVPB.edAddr;
        out << pbu->PB.a1500_2ndVPB.gwAddr;
        out << pbu->PB.a1500_2ndVPB.repeaterChannel;
        out << pbu->PB.a1500_2ndVPB.repeaterPower;
        out << pbu->PB.a1500_2ndVPB.showState;
        out << pbu->PB.a1500_2ndVPB.CriticalLevel500;
        out << pbu->PB.a1500_2ndVPB.CriticalLevel10;
        out << pbu->PB.a1500_2ndVPB.pureOffset;
        out << pbu->PB.a1500_2ndVPB.defCyclesTo500;
        out << pbu->PB.a1500_2ndVPB.defCyclesTo10;
        out << pbu->PB.a1500_2ndVPB.defCyclesToStep500Channel;
        out << pbu->PB.a1500_2ndVPB.defCyclesToStep10Channel;
        out << pbu->PB.a1500_2ndVPB.defCycles2SoftKick;
        out << pbu->PB.a1500_2ndVPB.defCycles2HardKick;
        out << pbu->PB.a1500_2ndVPB.imageAddr;
        out << pbu->PB.a1500_2ndVPB.versionLow;
        out << pbu->PB.a1500_2ndVPB.versionHigh;
        out << pbu->PB.a1500_2ndVPB.starting500Channel;
        out << pbu->PB.a1500_2ndVPB.boolByte2;
        out << pbu->PB.a1500_2ndVPB.prepAddr;
        out << pbu->PB.a1500_2ndVPB.repStep;
        out << pbu->PB.a1500_2ndVPB.ov_startup;
        out << pbu->PB.a1500_2ndVPB.t_mod_off;
        out << pbu->PB.a1500_2ndVPB.toff_fallback;
        out << pbu->PB.a1500_2ndVPB.ton_fallback;
        out << pbu->PB.a1500_2ndVPB.fallback_time;
        out << pbu->PB.a1500_2ndVPB.network_cnst_1;
        out << pbu->PB.a1500_2ndVPB.network_cnst_2;
        out << pbu->PB.a1500_2ndVPB.oc_protection;
        out << pbu->PB.a1500_2ndVPB.oc_step;
        out << pbu->PB.a1500_2ndVPB.cur_noise;
        out << pbu->PB.a1500_2ndVPB.ov_step;
        out << pbu->PB.a1500_2ndVPB.shunt;
        out << pbu->PB.a1500_2ndVPB.max_off;
        out << pbu->PB.a1500_2ndVPB.vin_limit;
        out << pbu->PB.a1500_2ndVPB.vin_turn_on;
        out << pbu->PB.a1500_2ndVPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1500V_30_Shunt)
    {
        out << pbu->PB.a1500_30VPB.barrier;
        out << pbu->PB.a1500_30VPB.netId;
        out << pbu->PB.a1500_30VPB.myBunch;
        out << pbu->PB.a1500_30VPB.groupId;
        out << pbu->PB.a1500_30VPB.myMac[0];
        out << pbu->PB.a1500_30VPB.myMac[1];
        out << pbu->PB.a1500_30VPB.myMac[2];
        out << pbu->PB.a1500_30VPB.myMac[3];
        out << pbu->PB.a1500_30VPB.myMac[4];
        out << pbu->PB.a1500_30VPB.myMac[5];
        out << pbu->PB.a1500_30VPB.dFk[0];
        out << pbu->PB.a1500_30VPB.dFk[1];
        out << pbu->PB.a1500_30VPB.dFk[2];
        out << pbu->PB.a1500_30VPB.dFk[3];
        out << pbu->PB.a1500_30VPB.vrefPolynom[0];
        out << pbu->PB.a1500_30VPB.vrefPolynom[1];
        out << pbu->PB.a1500_30VPB.vrefPolynom[2];
        out << pbu->PB.a1500_30VPB.linearK[0][0];
        out << pbu->PB.a1500_30VPB.linearK[0][1];
        out << pbu->PB.a1500_30VPB.linearK[1][0];
        out << pbu->PB.a1500_30VPB.linearK[1][1];
        out << pbu->PB.a1500_30VPB.linearK[2][0];
        out << pbu->PB.a1500_30VPB.linearK[2][1];
        out << pbu->PB.a1500_30VPB.linearK[3][0];
        out << pbu->PB.a1500_30VPB.linearK[3][1];
        out << pbu->PB.a1500_30VPB.linearK[4][0];
        out << pbu->PB.a1500_30VPB.linearK[4][1];
        out << pbu->PB.a1500_30VPB.linearK[5][0];
        out << pbu->PB.a1500_30VPB.linearK[5][1];
        out << pbu->PB.a1500_30VPB.linearK[6][0];
        out << pbu->PB.a1500_30VPB.linearK[6][1];
        out << pbu->PB.a1500_30VPB.curKey[0];
        out << pbu->PB.a1500_30VPB.curKey[1];
        out << pbu->PB.a1500_30VPB.curKey[2];
        out << pbu->PB.a1500_30VPB.curKey[3];
        out << pbu->PB.a1500_30VPB.curKey[4];
        out << pbu->PB.a1500_30VPB.curKey[5];
        out << pbu->PB.a1500_30VPB.curKey[6];
        out << pbu->PB.a1500_30VPB.curKey[7];
        out << pbu->PB.a1500_30VPB.curKey[8];
        out << pbu->PB.a1500_30VPB.curKey[9];
        out << pbu->PB.a1500_30VPB.curKey[10];
        out << pbu->PB.a1500_30VPB.curKey[11];
        out << pbu->PB.a1500_30VPB.curKey[12];
        out << pbu->PB.a1500_30VPB.curKey[13];
        out << pbu->PB.a1500_30VPB.curKey[14];
        out << pbu->PB.a1500_30VPB.curKey[15];
        out << pbu->PB.a1500_30VPB.curIV[0];
        out << pbu->PB.a1500_30VPB.curIV[1];
        out << pbu->PB.a1500_30VPB.curIV[2];
        out << pbu->PB.a1500_30VPB.curIV[3];
        out << pbu->PB.a1500_30VPB.curIV[4];
        out << pbu->PB.a1500_30VPB.curIV[5];
        out << pbu->PB.a1500_30VPB.curIV[6];
        out << pbu->PB.a1500_30VPB.curIV[7];
        out << pbu->PB.a1500_30VPB.curIV[8];
        out << pbu->PB.a1500_30VPB.curIV[9];
        out << pbu->PB.a1500_30VPB.curIV[10];
        out << pbu->PB.a1500_30VPB.curIV[11];
        out << pbu->PB.a1500_30VPB.curIV[12];
        out << pbu->PB.a1500_30VPB.curIV[13];
        out << pbu->PB.a1500_30VPB.curIV[14];
        out << pbu->PB.a1500_30VPB.curIV[15];
        out << pbu->PB.a1500_30VPB.fetFailureCount;
        out << pbu->PB.a1500_30VPB.fetCurrentThreshold;
        out << pbu->PB.a1500_30VPB.fetDeltaCurrent;
        out << pbu->PB.a1500_30VPB.LowCurrentLimitTo255;
        out << pbu->PB.a1500_30VPB.VoutLimitCount;
        out << pbu->PB.a1500_30VPB.VoutLimit;
        out << pbu->PB.a1500_30VPB.IoutLimitCount;
        out << pbu->PB.a1500_30VPB.IoutLimit;
        out << pbu->PB.a1500_30VPB.versionSuffix[0];
        out << pbu->PB.a1500_30VPB.versionSuffix[1];
        out << pbu->PB.a1500_30VPB.versionSuffix[2];
        out << pbu->PB.a1500_30VPB.monitoring;
        out << pbu->PB.a1500_30VPB.installDate;
        out << pbu->PB.a1500_30VPB.IinLimit;
        out << pbu->PB.a1500_30VPB.syncword;
        out << pbu->PB.a1500_30VPB.vin_disable_radio;
        out << pbu->PB.a1500_30VPB.rbunch;
        out << pbu->PB.a1500_30VPB.gbunch;
        out << pbu->PB.a1500_30VPB.shortCircuitLevel;
        out << pbu->PB.a1500_30VPB.reserved;
        out << pbu->PB.a1500_30VPB.synch_phase;
        out << pbu->PB.a1500_30VPB.synch_freq;
        out << pbu->PB.a1500_30VPB.bandwidth250;
        out << pbu->PB.a1500_30VPB.channel;
        out << pbu->PB.a1500_30VPB.utcProgram;
        out << pbu->PB.a1500_30VPB.utcLow;
        out << pbu->PB.a1500_30VPB.utcHigh;
        out << pbu->PB.a1500_30VPB.tkCurrent;
        out << pbu->PB.a1500_30VPB.tkPower;
        out << pbu->PB.a1500_30VPB.mpp;
        out << pbu->PB.a1500_30VPB.module;
        out << pbu->PB.a1500_30VPB.ov;
        out << pbu->PB.a1500_30VPB.oc;
        out << pbu->PB.a1500_30VPB.radioPower;
        out << pbu->PB.a1500_30VPB.edAddr;
        out << pbu->PB.a1500_30VPB.gwAddr;
        out << pbu->PB.a1500_30VPB.repeaterChannel;
        out << pbu->PB.a1500_30VPB.repeaterPower;
        out << pbu->PB.a1500_30VPB.IinOCStepsAndDelay;
        out << pbu->PB.a1500_30VPB.CriticalLevel500;
        out << pbu->PB.a1500_30VPB.CriticalLevel10;
        out << pbu->PB.a1500_30VPB.pureOffset;
        out << pbu->PB.a1500_30VPB.defCyclesTo500;
        out << pbu->PB.a1500_30VPB.defCyclesTo10;
        out << pbu->PB.a1500_30VPB.defCyclesToStep500Channel;
        out << pbu->PB.a1500_30VPB.defCyclesToStep10Channel;
        out << pbu->PB.a1500_30VPB.defCycles2SoftKick;
        out << pbu->PB.a1500_30VPB.defCycles2HardKick;
        out << pbu->PB.a1500_30VPB.imageAddr;
        out << pbu->PB.a1500_30VPB.versionLow;
        out << pbu->PB.a1500_30VPB.versionHigh;
        out << pbu->PB.a1500_30VPB.starting500Channel;
        out << pbu->PB.a1500_30VPB.boolByte2;
        out << pbu->PB.a1500_30VPB.prepAddr;
        out << pbu->PB.a1500_30VPB.repStep;
        out << pbu->PB.a1500_30VPB.ov_startup;
        out << pbu->PB.a1500_30VPB.t_mod_off;
        out << pbu->PB.a1500_30VPB.toff_fallback;
        out << pbu->PB.a1500_30VPB.ton_fallback;
        out << pbu->PB.a1500_30VPB.fallback_time;
        out << pbu->PB.a1500_30VPB.network_cnst_1;
        out << pbu->PB.a1500_30VPB.network_cnst_2;
        out << pbu->PB.a1500_30VPB.oc_protection;
        out << pbu->PB.a1500_30VPB.oc_step;
        out << pbu->PB.a1500_30VPB.cur_noise;
        out << pbu->PB.a1500_30VPB.ov_step;
        out << pbu->PB.a1500_30VPB.shunt;
        out << pbu->PB.a1500_30VPB.max_off;
        out << pbu->PB.a1500_30VPB.vin_limit;
        out << pbu->PB.a1500_30VPB.vin_turn_on;
        out << pbu->PB.a1500_30VPB.IinLimitTempAmbientAdjust;
    }


    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: Trying to save parameters of unknown family => " +  QString::number(pbu->parameterBlockFamily);
        qDebug() << ErrorStr;
    }
    return out;
}



QDataStream &operator>>(QDataStream &in, ParameterBlock_Union * pbu)
{
    BYTE temp;

    in >> pbu->parameterBlockFamily;
    if (pbu->parameterBlockFamily == 20)
    {
        in >> pbu->PB.a1000VPB.barrier;
        in >> pbu->PB.a1000VPB.netId;
        in >> pbu->PB.a1000VPB.myBunch;
        in >> pbu->PB.a1000VPB.groupId;
        in >> pbu->PB.a1000VPB.myMac[0];
        in >> pbu->PB.a1000VPB.myMac[1];
        in >> pbu->PB.a1000VPB.myMac[2];
        in >> pbu->PB.a1000VPB.myMac[3];
        in >> pbu->PB.a1000VPB.myMac[4];
        in >> pbu->PB.a1000VPB.myMac[5];
        in >> pbu->PB.a1000VPB.dFk[0];
        in >> pbu->PB.a1000VPB.dFk[1];
        in >> pbu->PB.a1000VPB.dFk[2];
        in >> pbu->PB.a1000VPB.dFk[3];
        in >> pbu->PB.a1000VPB.vrefPolynom[0];
        in >> pbu->PB.a1000VPB.vrefPolynom[1];
        in >> pbu->PB.a1000VPB.vrefPolynom[2];
        in >> pbu->PB.a1000VPB.linearK[0][0];
        in >> pbu->PB.a1000VPB.linearK[0][1];
        in >> pbu->PB.a1000VPB.linearK[1][0];
        in >> pbu->PB.a1000VPB.linearK[1][1];
        in >> pbu->PB.a1000VPB.linearK[2][0];
        in >> pbu->PB.a1000VPB.linearK[2][1];
        in >> pbu->PB.a1000VPB.linearK[3][0];
        in >> pbu->PB.a1000VPB.linearK[3][1];
        in >> pbu->PB.a1000VPB.linearK[4][0];
        in >> pbu->PB.a1000VPB.linearK[4][1];
        in >> pbu->PB.a1000VPB.linearK[5][0];
        in >> pbu->PB.a1000VPB.linearK[5][1];
        in >> pbu->PB.a1000VPB.linearK[6][0];
        in >> pbu->PB.a1000VPB.linearK[6][1];

        in >> temp;
        pbu->PB.a1000VPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a1000VPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1000VPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a1000VPB.fetFailureCount;
        in >> pbu->PB.a1000VPB.fetCurrentThreshold;
        in >> pbu->PB.a1000VPB.fetDeltaCurrent;
        in >> pbu->PB.a1000VPB.oscLowCurrentLimitInmA;
        in >> pbu->PB.a1000VPB.oscDeltaV;
        in >> pbu->PB.a1000VPB.oscOVStartupDelay;
        in >> pbu->PB.a1000VPB.oscAfterStartupDelay;
        in >> pbu->PB.a1000VPB.oscLowCurrentOnlyDelay;
        in >> pbu->PB.a1000VPB.tests[0];
        in >> pbu->PB.a1000VPB.tests[1];
        in >> pbu->PB.a1000VPB.tests[2];
        in >> pbu->PB.a1000VPB.tests[3];
        in >> pbu->PB.a1000VPB.installDate;
        in >> pbu->PB.a1000VPB.k_ov_volt;
        in >> pbu->PB.a1000VPB.k_oc_cur;
        in >> pbu->PB.a1000VPB.syncword;
        in >> pbu->PB.a1000VPB.vin_disable_radio;
        in >> pbu->PB.a1000VPB.rbunch;
        in >> pbu->PB.a1000VPB.gbunch;
        in >> pbu->PB.a1000VPB.shortCircuitLevel;
        in >> pbu->PB.a1000VPB.reserved;
        in >> pbu->PB.a1000VPB.synch_phase;
        in >> pbu->PB.a1000VPB.synch_freq;
        in >> pbu->PB.a1000VPB.bandwidth250;
        in >> pbu->PB.a1000VPB.channel;
        in >> pbu->PB.a1000VPB.utcProgram;
        in >> pbu->PB.a1000VPB.utcLow;
        in >> pbu->PB.a1000VPB.utcHigh;
        in >> pbu->PB.a1000VPB.tkCurrent;
        in >> pbu->PB.a1000VPB.tkPower;
        in >> pbu->PB.a1000VPB.mpp;
        in >> pbu->PB.a1000VPB.module;
        in >> pbu->PB.a1000VPB.ov;
        in >> pbu->PB.a1000VPB.oc;
        in >> pbu->PB.a1000VPB.radioPower;
        in >> pbu->PB.a1000VPB.edAddr;
        in >> pbu->PB.a1000VPB.gwAddr;
        in >> pbu->PB.a1000VPB.repeaterChannel;
        in >> pbu->PB.a1000VPB.repeaterPower;
        in >> pbu->PB.a1000VPB.showState;
        in >> pbu->PB.a1000VPB.CriticalLevel500;
        in >> pbu->PB.a1000VPB.CriticalLevel10;
        in >> pbu->PB.a1000VPB.pureOffset;
        in >> pbu->PB.a1000VPB.defCyclesTo500;
        in >> pbu->PB.a1000VPB.defCyclesTo10;
        in >> pbu->PB.a1000VPB.defCyclesToStep500Channel;
        in >> pbu->PB.a1000VPB.defCyclesToStep10Channel;
        in >> pbu->PB.a1000VPB.defCycles2SoftKick;
        in >> pbu->PB.a1000VPB.defCycles2HardKick;
        in >> pbu->PB.a1000VPB.imageAddr;
        in >> pbu->PB.a1000VPB.versionLow;
        in >> pbu->PB.a1000VPB.versionHigh;
        in >> pbu->PB.a1000VPB.starting500Channel;
        in >> pbu->PB.a1000VPB.boolByte2;
        in >> pbu->PB.a1000VPB.prepAddr;
        in >> pbu->PB.a1000VPB.repStep;
        in >> pbu->PB.a1000VPB.ov_startup;
        in >> pbu->PB.a1000VPB.t_mod_off;
        in >> pbu->PB.a1000VPB.toff_fallback;
        in >> pbu->PB.a1000VPB.ton_fallback;
        in >> pbu->PB.a1000VPB.fallback_time;
        in >> pbu->PB.a1000VPB.network_cnst_1;
        in >> pbu->PB.a1000VPB.network_cnst_2;
        in >> pbu->PB.a1000VPB.oc_protection;
        in >> pbu->PB.a1000VPB.oc_step;
        in >> pbu->PB.a1000VPB.cur_noise;
        in >> pbu->PB.a1000VPB.ov_step;
        in >> pbu->PB.a1000VPB.shunt;
        in >> pbu->PB.a1000VPB.max_off;
        in >> pbu->PB.a1000VPB.vin_limit;
        in >> pbu->PB.a1000VPB.vin_turn_on;
        in >> pbu->PB.a1000VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == 12)
    {
        in >> pbu->PB.a600V_V2VPB.barrier;
        in >> pbu->PB.a600V_V2VPB.netId;
        in >> pbu->PB.a600V_V2VPB.myBunch;
        in >> pbu->PB.a600V_V2VPB.groupId;
        in >> pbu->PB.a600V_V2VPB.myMac[0];
        in >> pbu->PB.a600V_V2VPB.myMac[1];
        in >> pbu->PB.a600V_V2VPB.myMac[2];
        in >> pbu->PB.a600V_V2VPB.myMac[3];
        in >> pbu->PB.a600V_V2VPB.myMac[4];
        in >> pbu->PB.a600V_V2VPB.myMac[5];
        in >> pbu->PB.a600V_V2VPB.dFk[0];
        in >> pbu->PB.a600V_V2VPB.dFk[1];
        in >> pbu->PB.a600V_V2VPB.dFk[2];
        in >> pbu->PB.a600V_V2VPB.dFk[3];
        in >> pbu->PB.a600V_V2VPB.vrefPolynom[0];
        in >> pbu->PB.a600V_V2VPB.vrefPolynom[1];
        in >> pbu->PB.a600V_V2VPB.vrefPolynom[2];
        in >> pbu->PB.a600V_V2VPB.linearK[0][0];
        in >> pbu->PB.a600V_V2VPB.linearK[0][1];
        in >> pbu->PB.a600V_V2VPB.linearK[1][0];
        in >> pbu->PB.a600V_V2VPB.linearK[1][1];
        in >> pbu->PB.a600V_V2VPB.linearK[2][0];
        in >> pbu->PB.a600V_V2VPB.linearK[2][1];
        in >> pbu->PB.a600V_V2VPB.linearK[3][0];
        in >> pbu->PB.a600V_V2VPB.linearK[3][1];
        in >> pbu->PB.a600V_V2VPB.linearK[4][0];
        in >> pbu->PB.a600V_V2VPB.linearK[4][1];
        in >> pbu->PB.a600V_V2VPB.linearK[5][0];
        in >> pbu->PB.a600V_V2VPB.linearK[5][1];
        in >> pbu->PB.a600V_V2VPB.linearK[6][0];
        in >> pbu->PB.a600V_V2VPB.linearK[6][1];

        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2VPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a600V_V2VPB.fetFailureCount;
        in >> pbu->PB.a600V_V2VPB.fetCurrentThreshold;
        in >> pbu->PB.a600V_V2VPB.fetDeltaCurrent;
        in >> pbu->PB.a600V_V2VPB.oscLowCurrentLimitInmA;
        in >> pbu->PB.a600V_V2VPB.oscDeltaV;
        in >> pbu->PB.a600V_V2VPB.oscOVStartupDelay;
        in >> pbu->PB.a600V_V2VPB.oscAfterStartupDelay;
        in >> pbu->PB.a600V_V2VPB.oscLowCurrentOnlyDelay;
        in >> pbu->PB.a600V_V2VPB.versionSuffix[0];
        in >> pbu->PB.a600V_V2VPB.versionSuffix[1];
        in >> pbu->PB.a600V_V2VPB.versionSuffix[2];
        in >> pbu->PB.a600V_V2VPB.tests;
        in >> pbu->PB.a600V_V2VPB.installDate;
        in >> pbu->PB.a600V_V2VPB.k_ov_volt;
        in >> pbu->PB.a600V_V2VPB.k_oc_cur;
        in >> pbu->PB.a600V_V2VPB.syncword;
        in >> pbu->PB.a600V_V2VPB.vin_disable_radio;
        in >> pbu->PB.a600V_V2VPB.rbunch;
        in >> pbu->PB.a600V_V2VPB.gbunch;
        in >> pbu->PB.a600V_V2VPB.shortCircuitLevel;
        in >> pbu->PB.a600V_V2VPB.reserved;
        in >> pbu->PB.a600V_V2VPB.synch_phase;
        in >> pbu->PB.a600V_V2VPB.synch_freq;
        in >> pbu->PB.a600V_V2VPB.bandwidth250;
        in >> pbu->PB.a600V_V2VPB.channel;
        in >> pbu->PB.a600V_V2VPB.utcProgram;
        in >> pbu->PB.a600V_V2VPB.utcLow;
        in >> pbu->PB.a600V_V2VPB.utcHigh;
        in >> pbu->PB.a600V_V2VPB.tkCurrent;
        in >> pbu->PB.a600V_V2VPB.tkPower;
        in >> pbu->PB.a600V_V2VPB.mpp;
        in >> pbu->PB.a600V_V2VPB.module;
        in >> pbu->PB.a600V_V2VPB.ov;
        in >> pbu->PB.a600V_V2VPB.oc;
        in >> pbu->PB.a600V_V2VPB.radioPower;
        in >> pbu->PB.a600V_V2VPB.edAddr;
        in >> pbu->PB.a600V_V2VPB.gwAddr;
        in >> pbu->PB.a600V_V2VPB.repeaterChannel;
        in >> pbu->PB.a600V_V2VPB.repeaterPower;
        in >> pbu->PB.a600V_V2VPB.showState;
        in >> pbu->PB.a600V_V2VPB.CriticalLevel500;
        in >> pbu->PB.a600V_V2VPB.CriticalLevel10;
        in >> pbu->PB.a600V_V2VPB.pureOffset;
        in >> pbu->PB.a600V_V2VPB.defCyclesTo500;
        in >> pbu->PB.a600V_V2VPB.defCyclesTo10;
        in >> pbu->PB.a600V_V2VPB.defCyclesToStep500Channel;
        in >> pbu->PB.a600V_V2VPB.defCyclesToStep10Channel;
        in >> pbu->PB.a600V_V2VPB.defCycles2SoftKick;
        in >> pbu->PB.a600V_V2VPB.defCycles2HardKick;
        in >> pbu->PB.a600V_V2VPB.imageAddr;
        in >> pbu->PB.a600V_V2VPB.versionLow;
        in >> pbu->PB.a600V_V2VPB.versionHigh;
        in >> pbu->PB.a600V_V2VPB.starting500Channel;
        in >> pbu->PB.a600V_V2VPB.boolByte2;
        in >> pbu->PB.a600V_V2VPB.prepAddr;
        in >> pbu->PB.a600V_V2VPB.repStep;
        in >> pbu->PB.a600V_V2VPB.ov_startup;
        in >> pbu->PB.a600V_V2VPB.t_mod_off;
        in >> pbu->PB.a600V_V2VPB.toff_fallback;
        in >> pbu->PB.a600V_V2VPB.ton_fallback;
        in >> pbu->PB.a600V_V2VPB.fallback_time;
        in >> pbu->PB.a600V_V2VPB.network_cnst_1;
        in >> pbu->PB.a600V_V2VPB.network_cnst_2;
        in >> pbu->PB.a600V_V2VPB.oc_protection;
        in >> pbu->PB.a600V_V2VPB.oc_step;
        in >> pbu->PB.a600V_V2VPB.cur_noise;
        in >> pbu->PB.a600V_V2VPB.ov_step;
        in >> pbu->PB.a600V_V2VPB.shunt;
        in >> pbu->PB.a600V_V2VPB.max_off;
        in >> pbu->PB.a600V_V2VPB.vin_limit;
        in >> pbu->PB.a600V_V2VPB.vin_turn_on;
        in >> pbu->PB.a600V_V2VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family600V_V2_2nd)
    {
        in >> pbu->PB.a600V_V2_2ndVPB.barrier;
        in >> pbu->PB.a600V_V2_2ndVPB.netId;
        in >> pbu->PB.a600V_V2_2ndVPB.myBunch;
        in >> pbu->PB.a600V_V2_2ndVPB.groupId;
        in >> pbu->PB.a600V_V2_2ndVPB.myMac[0];
        in >> pbu->PB.a600V_V2_2ndVPB.myMac[1];
        in >> pbu->PB.a600V_V2_2ndVPB.myMac[2];
        in >> pbu->PB.a600V_V2_2ndVPB.myMac[3];
        in >> pbu->PB.a600V_V2_2ndVPB.myMac[4];
        in >> pbu->PB.a600V_V2_2ndVPB.myMac[5];
        in >> pbu->PB.a600V_V2_2ndVPB.dFk[0];
        in >> pbu->PB.a600V_V2_2ndVPB.dFk[1];
        in >> pbu->PB.a600V_V2_2ndVPB.dFk[2];
        in >> pbu->PB.a600V_V2_2ndVPB.dFk[3];
        in >> pbu->PB.a600V_V2_2ndVPB.vrefPolynom[0];
        in >> pbu->PB.a600V_V2_2ndVPB.vrefPolynom[1];
        in >> pbu->PB.a600V_V2_2ndVPB.vrefPolynom[2];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[0][0];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[0][1];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[1][0];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[1][1];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[2][0];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[2][1];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[3][0];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[3][1];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[4][0];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[4][1];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[5][0];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[5][1];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[6][0];
        in >> pbu->PB.a600V_V2_2ndVPB.linearK[6][1];

        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a600V_V2_2ndVPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a600V_V2_2ndVPB.fetFailureCount;
        in >> pbu->PB.a600V_V2_2ndVPB.fetCurrentThreshold;
        in >> pbu->PB.a600V_V2_2ndVPB.fetDeltaCurrent;
        in >> pbu->PB.a600V_V2_2ndVPB.LowCurrentLimitTo255;
        in >> pbu->PB.a600V_V2_2ndVPB.VhvLimitVout;
        in >> pbu->PB.a600V_V2_2ndVPB.IhvLimitVout;
        in >> pbu->PB.a600V_V2_2ndVPB.VhvLimitVins;
        in >> pbu->PB.a600V_V2_2ndVPB.IhvLimitVins;
        in >> pbu->PB.a600V_V2_2ndVPB.versionSuffix[0];
        in >> pbu->PB.a600V_V2_2ndVPB.versionSuffix[1];
        in >> pbu->PB.a600V_V2_2ndVPB.versionSuffix[2];
        in >> pbu->PB.a600V_V2_2ndVPB.tests;
        in >> pbu->PB.a600V_V2_2ndVPB.installDate;
        in >> pbu->PB.a600V_V2_2ndVPB.k_ov_volt;
        in >> pbu->PB.a600V_V2_2ndVPB.k_oc_cur;
        in >> pbu->PB.a600V_V2_2ndVPB.syncword;
        in >> pbu->PB.a600V_V2_2ndVPB.vin_disable_radio;
        in >> pbu->PB.a600V_V2_2ndVPB.rbunch;
        in >> pbu->PB.a600V_V2_2ndVPB.gbunch;
        in >> pbu->PB.a600V_V2_2ndVPB.shortCircuitLevel;
        in >> pbu->PB.a600V_V2_2ndVPB.reserved;
        in >> pbu->PB.a600V_V2_2ndVPB.synch_phase;
        in >> pbu->PB.a600V_V2_2ndVPB.synch_freq;
        in >> pbu->PB.a600V_V2_2ndVPB.bandwidth250;
        in >> pbu->PB.a600V_V2_2ndVPB.channel;
        in >> pbu->PB.a600V_V2_2ndVPB.utcProgram;
        in >> pbu->PB.a600V_V2_2ndVPB.utcLow;
        in >> pbu->PB.a600V_V2_2ndVPB.utcHigh;
        in >> pbu->PB.a600V_V2_2ndVPB.tkCurrent;
        in >> pbu->PB.a600V_V2_2ndVPB.tkPower;
        in >> pbu->PB.a600V_V2_2ndVPB.mpp;
        in >> pbu->PB.a600V_V2_2ndVPB.module;
        in >> pbu->PB.a600V_V2_2ndVPB.ov;
        in >> pbu->PB.a600V_V2_2ndVPB.oc;
        in >> pbu->PB.a600V_V2_2ndVPB.radioPower;
        in >> pbu->PB.a600V_V2_2ndVPB.edAddr;
        in >> pbu->PB.a600V_V2_2ndVPB.gwAddr;
        in >> pbu->PB.a600V_V2_2ndVPB.repeaterChannel;
        in >> pbu->PB.a600V_V2_2ndVPB.repeaterPower;
        in >> pbu->PB.a600V_V2_2ndVPB.showState;
        in >> pbu->PB.a600V_V2_2ndVPB.CriticalLevel500;
        in >> pbu->PB.a600V_V2_2ndVPB.CriticalLevel10;
        in >> pbu->PB.a600V_V2_2ndVPB.pureOffset;
        in >> pbu->PB.a600V_V2_2ndVPB.defCyclesTo500;
        in >> pbu->PB.a600V_V2_2ndVPB.defCyclesTo10;
        in >> pbu->PB.a600V_V2_2ndVPB.defCyclesToStep500Channel;
        in >> pbu->PB.a600V_V2_2ndVPB.defCyclesToStep10Channel;
        in >> pbu->PB.a600V_V2_2ndVPB.defCycles2SoftKick;
        in >> pbu->PB.a600V_V2_2ndVPB.defCycles2HardKick;
        in >> pbu->PB.a600V_V2_2ndVPB.imageAddr;
        in >> pbu->PB.a600V_V2_2ndVPB.versionLow;
        in >> pbu->PB.a600V_V2_2ndVPB.versionHigh;
        in >> pbu->PB.a600V_V2_2ndVPB.starting500Channel;
        in >> pbu->PB.a600V_V2_2ndVPB.boolByte2;
        in >> pbu->PB.a600V_V2_2ndVPB.prepAddr;
        in >> pbu->PB.a600V_V2_2ndVPB.repStep;
        in >> pbu->PB.a600V_V2_2ndVPB.ov_startup;
        in >> pbu->PB.a600V_V2_2ndVPB.t_mod_off;
        in >> pbu->PB.a600V_V2_2ndVPB.toff_fallback;
        in >> pbu->PB.a600V_V2_2ndVPB.ton_fallback;
        in >> pbu->PB.a600V_V2_2ndVPB.fallback_time;
        in >> pbu->PB.a600V_V2_2ndVPB.network_cnst_1;
        in >> pbu->PB.a600V_V2_2ndVPB.network_cnst_2;
        in >> pbu->PB.a600V_V2_2ndVPB.oc_protection;
        in >> pbu->PB.a600V_V2_2ndVPB.oc_step;
        in >> pbu->PB.a600V_V2_2ndVPB.cur_noise;
        in >> pbu->PB.a600V_V2_2ndVPB.ov_step;
        in >> pbu->PB.a600V_V2_2ndVPB.shunt;
        in >> pbu->PB.a600V_V2_2ndVPB.max_off;
        in >> pbu->PB.a600V_V2_2ndVPB.vin_limit;
        in >> pbu->PB.a600V_V2_2ndVPB.vin_turn_on;
        in >> pbu->PB.a600V_V2_2ndVPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1300V)
    {
        in >> pbu->PB.a1300VPB.barrier;
        in >> pbu->PB.a1300VPB.netId;
        in >> pbu->PB.a1300VPB.myBunch;
        in >> pbu->PB.a1300VPB.groupId;
        in >> pbu->PB.a1300VPB.myMac[0];
        in >> pbu->PB.a1300VPB.myMac[1];
        in >> pbu->PB.a1300VPB.myMac[2];
        in >> pbu->PB.a1300VPB.myMac[3];
        in >> pbu->PB.a1300VPB.myMac[4];
        in >> pbu->PB.a1300VPB.myMac[5];
        in >> pbu->PB.a1300VPB.dFk[0];
        in >> pbu->PB.a1300VPB.dFk[1];
        in >> pbu->PB.a1300VPB.dFk[2];
        in >> pbu->PB.a1300VPB.dFk[3];
        in >> pbu->PB.a1300VPB.vrefPolynom[0];
        in >> pbu->PB.a1300VPB.vrefPolynom[1];
        in >> pbu->PB.a1300VPB.vrefPolynom[2];
        in >> pbu->PB.a1300VPB.linearK[0][0];
        in >> pbu->PB.a1300VPB.linearK[0][1];
        in >> pbu->PB.a1300VPB.linearK[1][0];
        in >> pbu->PB.a1300VPB.linearK[1][1];
        in >> pbu->PB.a1300VPB.linearK[2][0];
        in >> pbu->PB.a1300VPB.linearK[2][1];
        in >> pbu->PB.a1300VPB.linearK[3][0];
        in >> pbu->PB.a1300VPB.linearK[3][1];
        in >> pbu->PB.a1300VPB.linearK[4][0];
        in >> pbu->PB.a1300VPB.linearK[4][1];
        in >> pbu->PB.a1300VPB.linearK[5][0];
        in >> pbu->PB.a1300VPB.linearK[5][1];
        in >> pbu->PB.a1300VPB.linearK[6][0];
        in >> pbu->PB.a1300VPB.linearK[6][1];

        in >> temp;
        pbu->PB.a1300VPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a1300VPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300VPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a1300VPB.fetFailureCount;
        in >> pbu->PB.a1300VPB.fetCurrentThreshold;
        in >> pbu->PB.a1300VPB.fetDeltaCurrent;
        in >> pbu->PB.a1300VPB.LowCurrentLimitTo255;
        in >> pbu->PB.a1300VPB.VhvLimitVout;
        in >> pbu->PB.a1300VPB.IhvLimitVout;
        in >> pbu->PB.a1300VPB.VhvLimitVins;
        in >> pbu->PB.a1300VPB.IhvLimitVins;
        in >> pbu->PB.a1300VPB.versionSuffix[0];
        in >> pbu->PB.a1300VPB.versionSuffix[1];
        in >> pbu->PB.a1300VPB.versionSuffix[2];
        in >> pbu->PB.a1300VPB.tests;
        in >> pbu->PB.a1300VPB.installDate;
        in >> pbu->PB.a1300VPB.k_ov_volt;
        in >> pbu->PB.a1300VPB.k_oc_cur;
        in >> pbu->PB.a1300VPB.syncword;
        in >> pbu->PB.a1300VPB.vin_disable_radio;
        in >> pbu->PB.a1300VPB.rbunch;
        in >> pbu->PB.a1300VPB.gbunch;
        in >> pbu->PB.a1300VPB.shortCircuitLevel;
        in >> pbu->PB.a1300VPB.reserved;
        in >> pbu->PB.a1300VPB.synch_phase;
        in >> pbu->PB.a1300VPB.synch_freq;
        in >> pbu->PB.a1300VPB.bandwidth250;
        in >> pbu->PB.a1300VPB.channel;
        in >> pbu->PB.a1300VPB.utcProgram;
        in >> pbu->PB.a1300VPB.utcLow;
        in >> pbu->PB.a1300VPB.utcHigh;
        in >> pbu->PB.a1300VPB.tkCurrent;
        in >> pbu->PB.a1300VPB.tkPower;
        in >> pbu->PB.a1300VPB.mpp;
        in >> pbu->PB.a1300VPB.module;
        in >> pbu->PB.a1300VPB.ov;
        in >> pbu->PB.a1300VPB.oc;
        in >> pbu->PB.a1300VPB.radioPower;
        in >> pbu->PB.a1300VPB.edAddr;
        in >> pbu->PB.a1300VPB.gwAddr;
        in >> pbu->PB.a1300VPB.repeaterChannel;
        in >> pbu->PB.a1300VPB.repeaterPower;
        in >> pbu->PB.a1300VPB.showState;
        in >> pbu->PB.a1300VPB.CriticalLevel500;
        in >> pbu->PB.a1300VPB.CriticalLevel10;
        in >> pbu->PB.a1300VPB.pureOffset;
        in >> pbu->PB.a1300VPB.defCyclesTo500;
        in >> pbu->PB.a1300VPB.defCyclesTo10;
        in >> pbu->PB.a1300VPB.defCyclesToStep500Channel;
        in >> pbu->PB.a1300VPB.defCyclesToStep10Channel;
        in >> pbu->PB.a1300VPB.defCycles2SoftKick;
        in >> pbu->PB.a1300VPB.defCycles2HardKick;
        in >> pbu->PB.a1300VPB.imageAddr;
        in >> pbu->PB.a1300VPB.versionLow;
        in >> pbu->PB.a1300VPB.versionHigh;
        in >> pbu->PB.a1300VPB.starting500Channel;
        in >> pbu->PB.a1300VPB.boolByte2;
        in >> pbu->PB.a1300VPB.prepAddr;
        in >> pbu->PB.a1300VPB.repStep;
        in >> pbu->PB.a1300VPB.ov_startup;
        in >> pbu->PB.a1300VPB.t_mod_off;
        in >> pbu->PB.a1300VPB.toff_fallback;
        in >> pbu->PB.a1300VPB.ton_fallback;
        in >> pbu->PB.a1300VPB.fallback_time;
        in >> pbu->PB.a1300VPB.network_cnst_1;
        in >> pbu->PB.a1300VPB.network_cnst_2;
        in >> pbu->PB.a1300VPB.oc_protection;
        in >> pbu->PB.a1300VPB.oc_step;
        in >> pbu->PB.a1300VPB.cur_noise;
        in >> pbu->PB.a1300VPB.ov_step;
        in >> pbu->PB.a1300VPB.shunt;
        in >> pbu->PB.a1300VPB.max_off;
        in >> pbu->PB.a1300VPB.vin_limit;
        in >> pbu->PB.a1300VPB.vin_turn_on;
        in >> pbu->PB.a1300VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1300V_2nd_Shunt)
    {
        in >> pbu->PB.a1300_2ndVPB.barrier;
        in >> pbu->PB.a1300_2ndVPB.netId;
        in >> pbu->PB.a1300_2ndVPB.myBunch;
        in >> pbu->PB.a1300_2ndVPB.groupId;
        in >> pbu->PB.a1300_2ndVPB.myMac[0];
        in >> pbu->PB.a1300_2ndVPB.myMac[1];
        in >> pbu->PB.a1300_2ndVPB.myMac[2];
        in >> pbu->PB.a1300_2ndVPB.myMac[3];
        in >> pbu->PB.a1300_2ndVPB.myMac[4];
        in >> pbu->PB.a1300_2ndVPB.myMac[5];
        in >> pbu->PB.a1300_2ndVPB.dFk[0];
        in >> pbu->PB.a1300_2ndVPB.dFk[1];
        in >> pbu->PB.a1300_2ndVPB.dFk[2];
        in >> pbu->PB.a1300_2ndVPB.dFk[3];
        in >> pbu->PB.a1300_2ndVPB.vrefPolynom[0];
        in >> pbu->PB.a1300_2ndVPB.vrefPolynom[1];
        in >> pbu->PB.a1300_2ndVPB.vrefPolynom[2];
        in >> pbu->PB.a1300_2ndVPB.linearK[0][0];
        in >> pbu->PB.a1300_2ndVPB.linearK[0][1];
        in >> pbu->PB.a1300_2ndVPB.linearK[1][0];
        in >> pbu->PB.a1300_2ndVPB.linearK[1][1];
        in >> pbu->PB.a1300_2ndVPB.linearK[2][0];
        in >> pbu->PB.a1300_2ndVPB.linearK[2][1];
        in >> pbu->PB.a1300_2ndVPB.linearK[3][0];
        in >> pbu->PB.a1300_2ndVPB.linearK[3][1];
        in >> pbu->PB.a1300_2ndVPB.linearK[4][0];
        in >> pbu->PB.a1300_2ndVPB.linearK[4][1];
        in >> pbu->PB.a1300_2ndVPB.linearK[5][0];
        in >> pbu->PB.a1300_2ndVPB.linearK[5][1];
        in >> pbu->PB.a1300_2ndVPB.linearK[6][0];
        in >> pbu->PB.a1300_2ndVPB.linearK[6][1];

        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1300_2ndVPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a1300_2ndVPB.fetFailureCount;
        in >> pbu->PB.a1300_2ndVPB.fetCurrentThreshold;
        in >> pbu->PB.a1300_2ndVPB.fetDeltaCurrent;
        in >> pbu->PB.a1300_2ndVPB.LowCurrentLimitTo255;
        in >> pbu->PB.a1300_2ndVPB.VhvLimitVout;
        in >> pbu->PB.a1300_2ndVPB.IhvLimitVout;
        in >> pbu->PB.a1300_2ndVPB.VhvLimitVins;
        in >> pbu->PB.a1300_2ndVPB.IhvLimitVins;
        in >> pbu->PB.a1300_2ndVPB.versionSuffix[0];
        in >> pbu->PB.a1300_2ndVPB.versionSuffix[1];
        in >> pbu->PB.a1300_2ndVPB.versionSuffix[2];
        in >> pbu->PB.a1300_2ndVPB.tests;
        in >> pbu->PB.a1300_2ndVPB.installDate;
        in >> pbu->PB.a1300_2ndVPB.k_ov_volt;
        in >> pbu->PB.a1300_2ndVPB.k_oc_cur;
        in >> pbu->PB.a1300_2ndVPB.syncword;
        in >> pbu->PB.a1300_2ndVPB.vin_disable_radio;
        in >> pbu->PB.a1300_2ndVPB.rbunch;
        in >> pbu->PB.a1300_2ndVPB.gbunch;
        in >> pbu->PB.a1300_2ndVPB.shortCircuitLevel;
        in >> pbu->PB.a1300_2ndVPB.reserved;
        in >> pbu->PB.a1300_2ndVPB.synch_phase;
        in >> pbu->PB.a1300_2ndVPB.synch_freq;
        in >> pbu->PB.a1300_2ndVPB.bandwidth250;
        in >> pbu->PB.a1300_2ndVPB.channel;
        in >> pbu->PB.a1300_2ndVPB.utcProgram;
        in >> pbu->PB.a1300_2ndVPB.utcLow;
        in >> pbu->PB.a1300_2ndVPB.utcHigh;
        in >> pbu->PB.a1300_2ndVPB.tkCurrent;
        in >> pbu->PB.a1300_2ndVPB.tkPower;
        in >> pbu->PB.a1300_2ndVPB.mpp;
        in >> pbu->PB.a1300_2ndVPB.module;
        in >> pbu->PB.a1300_2ndVPB.ov;
        in >> pbu->PB.a1300_2ndVPB.oc;
        in >> pbu->PB.a1300_2ndVPB.radioPower;
        in >> pbu->PB.a1300_2ndVPB.edAddr;
        in >> pbu->PB.a1300_2ndVPB.gwAddr;
        in >> pbu->PB.a1300_2ndVPB.repeaterChannel;
        in >> pbu->PB.a1300_2ndVPB.repeaterPower;
        in >> pbu->PB.a1300_2ndVPB.showState;
        in >> pbu->PB.a1300_2ndVPB.CriticalLevel500;
        in >> pbu->PB.a1300_2ndVPB.CriticalLevel10;
        in >> pbu->PB.a1300_2ndVPB.pureOffset;
        in >> pbu->PB.a1300_2ndVPB.defCyclesTo500;
        in >> pbu->PB.a1300_2ndVPB.defCyclesTo10;
        in >> pbu->PB.a1300_2ndVPB.defCyclesToStep500Channel;
        in >> pbu->PB.a1300_2ndVPB.defCyclesToStep10Channel;
        in >> pbu->PB.a1300_2ndVPB.defCycles2SoftKick;
        in >> pbu->PB.a1300_2ndVPB.defCycles2HardKick;
        in >> pbu->PB.a1300_2ndVPB.imageAddr;
        in >> pbu->PB.a1300_2ndVPB.versionLow;
        in >> pbu->PB.a1300_2ndVPB.versionHigh;
        in >> pbu->PB.a1300_2ndVPB.starting500Channel;
        in >> pbu->PB.a1300_2ndVPB.boolByte2;
        in >> pbu->PB.a1300_2ndVPB.prepAddr;
        in >> pbu->PB.a1300_2ndVPB.repStep;
        in >> pbu->PB.a1300_2ndVPB.ov_startup;
        in >> pbu->PB.a1300_2ndVPB.t_mod_off;
        in >> pbu->PB.a1300_2ndVPB.toff_fallback;
        in >> pbu->PB.a1300_2ndVPB.ton_fallback;
        in >> pbu->PB.a1300_2ndVPB.fallback_time;
        in >> pbu->PB.a1300_2ndVPB.network_cnst_1;
        in >> pbu->PB.a1300_2ndVPB.network_cnst_2;
        in >> pbu->PB.a1300_2ndVPB.oc_protection;
        in >> pbu->PB.a1300_2ndVPB.oc_step;
        in >> pbu->PB.a1300_2ndVPB.cur_noise;
        in >> pbu->PB.a1300_2ndVPB.ov_step;
        in >> pbu->PB.a1300_2ndVPB.shunt;
        in >> pbu->PB.a1300_2ndVPB.max_off;
        in >> pbu->PB.a1300_2ndVPB.vin_limit;
        in >> pbu->PB.a1300_2ndVPB.vin_turn_on;
        in >> pbu->PB.a1300_2ndVPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1500V_30)
    {
        in >> pbu->PB.a1500_30VPB.barrier;
        in >> pbu->PB.a1500_30VPB.netId;
        in >> pbu->PB.a1500_30VPB.myBunch;
        in >> pbu->PB.a1500_30VPB.groupId;
        in >> pbu->PB.a1500_30VPB.myMac[0];
        in >> pbu->PB.a1500_30VPB.myMac[1];
        in >> pbu->PB.a1500_30VPB.myMac[2];
        in >> pbu->PB.a1500_30VPB.myMac[3];
        in >> pbu->PB.a1500_30VPB.myMac[4];
        in >> pbu->PB.a1500_30VPB.myMac[5];
        in >> pbu->PB.a1500_30VPB.dFk[0];
        in >> pbu->PB.a1500_30VPB.dFk[1];
        in >> pbu->PB.a1500_30VPB.dFk[2];
        in >> pbu->PB.a1500_30VPB.dFk[3];
        in >> pbu->PB.a1500_30VPB.vrefPolynom[0];
        in >> pbu->PB.a1500_30VPB.vrefPolynom[1];
        in >> pbu->PB.a1500_30VPB.vrefPolynom[2];
        in >> pbu->PB.a1500_30VPB.linearK[0][0];
        in >> pbu->PB.a1500_30VPB.linearK[0][1];
        in >> pbu->PB.a1500_30VPB.linearK[1][0];
        in >> pbu->PB.a1500_30VPB.linearK[1][1];
        in >> pbu->PB.a1500_30VPB.linearK[2][0];
        in >> pbu->PB.a1500_30VPB.linearK[2][1];
        in >> pbu->PB.a1500_30VPB.linearK[3][0];
        in >> pbu->PB.a1500_30VPB.linearK[3][1];
        in >> pbu->PB.a1500_30VPB.linearK[4][0];
        in >> pbu->PB.a1500_30VPB.linearK[4][1];
        in >> pbu->PB.a1500_30VPB.linearK[5][0];
        in >> pbu->PB.a1500_30VPB.linearK[5][1];
        in >> pbu->PB.a1500_30VPB.linearK[6][0];
        in >> pbu->PB.a1500_30VPB.linearK[6][1];

        in >> temp;
        pbu->PB.a1500_30VPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a1500_30VPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_30VPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a1500_30VPB.fetFailureCount;
        in >> pbu->PB.a1500_30VPB.fetCurrentThreshold;
        in >> pbu->PB.a1500_30VPB.fetDeltaCurrent;
        in >> pbu->PB.a1500_30VPB.LowCurrentLimitTo255;
        in >> pbu->PB.a1500_30VPB.VoutLimitCount;
        in >> pbu->PB.a1500_30VPB.VoutLimit;
        in >> pbu->PB.a1500_30VPB.IoutLimitCount;
        in >> pbu->PB.a1500_30VPB.IoutLimit;
        in >> pbu->PB.a1500_30VPB.versionSuffix[0];
        in >> pbu->PB.a1500_30VPB.versionSuffix[1];
        in >> pbu->PB.a1500_30VPB.versionSuffix[2];
        in >> pbu->PB.a1500_30VPB.monitoring;
        in >> pbu->PB.a1500_30VPB.installDate;
        in >> pbu->PB.a1500_30VPB.IinLimit;
        in >> pbu->PB.a1500_30VPB.syncword;
        in >> pbu->PB.a1500_30VPB.vin_disable_radio;
        in >> pbu->PB.a1500_30VPB.rbunch;
        in >> pbu->PB.a1500_30VPB.gbunch;
        in >> pbu->PB.a1500_30VPB.shortCircuitLevel;
        in >> pbu->PB.a1500_30VPB.reserved;
        in >> pbu->PB.a1500_30VPB.synch_phase;
        in >> pbu->PB.a1500_30VPB.synch_freq;
        in >> pbu->PB.a1500_30VPB.bandwidth250;
        in >> pbu->PB.a1500_30VPB.channel;
        in >> pbu->PB.a1500_30VPB.utcProgram;
        in >> pbu->PB.a1500_30VPB.utcLow;
        in >> pbu->PB.a1500_30VPB.utcHigh;
        in >> pbu->PB.a1500_30VPB.tkCurrent;
        in >> pbu->PB.a1500_30VPB.tkPower;
        in >> pbu->PB.a1500_30VPB.mpp;
        in >> pbu->PB.a1500_30VPB.module;
        in >> pbu->PB.a1500_30VPB.ov;
        in >> pbu->PB.a1500_30VPB.oc;
        in >> pbu->PB.a1500_30VPB.radioPower;
        in >> pbu->PB.a1500_30VPB.edAddr;
        in >> pbu->PB.a1500_30VPB.gwAddr;
        in >> pbu->PB.a1500_30VPB.repeaterChannel;
        in >> pbu->PB.a1500_30VPB.repeaterPower;
        in >> pbu->PB.a1500_30VPB.IinOCStepsAndDelay;
        in >> pbu->PB.a1500_30VPB.CriticalLevel500;
        in >> pbu->PB.a1500_30VPB.CriticalLevel10;
        in >> pbu->PB.a1500_30VPB.pureOffset;
        in >> pbu->PB.a1500_30VPB.defCyclesTo500;
        in >> pbu->PB.a1500_30VPB.defCyclesTo10;
        in >> pbu->PB.a1500_30VPB.defCyclesToStep500Channel;
        in >> pbu->PB.a1500_30VPB.defCyclesToStep10Channel;
        in >> pbu->PB.a1500_30VPB.defCycles2SoftKick;
        in >> pbu->PB.a1500_30VPB.defCycles2HardKick;
        in >> pbu->PB.a1500_30VPB.imageAddr;
        in >> pbu->PB.a1500_30VPB.versionLow;
        in >> pbu->PB.a1500_30VPB.versionHigh;
        in >> pbu->PB.a1500_30VPB.starting500Channel;
        in >> pbu->PB.a1500_30VPB.boolByte2;
        in >> pbu->PB.a1500_30VPB.prepAddr;
        in >> pbu->PB.a1500_30VPB.repStep;
        in >> pbu->PB.a1500_30VPB.ov_startup;
        in >> pbu->PB.a1500_30VPB.t_mod_off;
        in >> pbu->PB.a1500_30VPB.toff_fallback;
        in >> pbu->PB.a1500_30VPB.ton_fallback;
        in >> pbu->PB.a1500_30VPB.fallback_time;
        in >> pbu->PB.a1500_30VPB.network_cnst_1;
        in >> pbu->PB.a1500_30VPB.network_cnst_2;
        in >> pbu->PB.a1500_30VPB.oc_protection;
        in >> pbu->PB.a1500_30VPB.oc_step;
        in >> pbu->PB.a1500_30VPB.cur_noise;
        in >> pbu->PB.a1500_30VPB.ov_step;
        in >> pbu->PB.a1500_30VPB.shunt;
        in >> pbu->PB.a1500_30VPB.max_off;
        in >> pbu->PB.a1500_30VPB.vin_limit;
        in >> pbu->PB.a1500_30VPB.vin_turn_on;
        in >> pbu->PB.a1500_30VPB.IinLimitTempAmbientAdjust;
    }
    else if (pbu->parameterBlockFamily == Family1500V)
    {
        in >> pbu->PB.a1500VPB.barrier;
        in >> pbu->PB.a1500VPB.netId;
        in >> pbu->PB.a1500VPB.myBunch;
        in >> pbu->PB.a1500VPB.groupId;
        in >> pbu->PB.a1500VPB.myMac[0];
        in >> pbu->PB.a1500VPB.myMac[1];
        in >> pbu->PB.a1500VPB.myMac[2];
        in >> pbu->PB.a1500VPB.myMac[3];
        in >> pbu->PB.a1500VPB.myMac[4];
        in >> pbu->PB.a1500VPB.myMac[5];
        in >> pbu->PB.a1500VPB.dFk[0];
        in >> pbu->PB.a1500VPB.dFk[1];
        in >> pbu->PB.a1500VPB.dFk[2];
        in >> pbu->PB.a1500VPB.dFk[3];
        in >> pbu->PB.a1500VPB.vrefPolynom[0];
        in >> pbu->PB.a1500VPB.vrefPolynom[1];
        in >> pbu->PB.a1500VPB.vrefPolynom[2];
        in >> pbu->PB.a1500VPB.linearK[0][0];
        in >> pbu->PB.a1500VPB.linearK[0][1];
        in >> pbu->PB.a1500VPB.linearK[1][0];
        in >> pbu->PB.a1500VPB.linearK[1][1];
        in >> pbu->PB.a1500VPB.linearK[2][0];
        in >> pbu->PB.a1500VPB.linearK[2][1];
        in >> pbu->PB.a1500VPB.linearK[3][0];
        in >> pbu->PB.a1500VPB.linearK[3][1];
        in >> pbu->PB.a1500VPB.linearK[4][0];
        in >> pbu->PB.a1500VPB.linearK[4][1];
        in >> pbu->PB.a1500VPB.linearK[5][0];
        in >> pbu->PB.a1500VPB.linearK[5][1];
        in >> pbu->PB.a1500VPB.linearK[6][0];
        in >> pbu->PB.a1500VPB.linearK[6][1];

        in >> temp;
        pbu->PB.a1500VPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a1500VPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500VPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a1500VPB.fetFailureCount;
        in >> pbu->PB.a1500VPB.fetCurrentThreshold;
        in >> pbu->PB.a1500VPB.fetDeltaCurrent;
        in >> pbu->PB.a1500VPB.LowCurrentLimitTo255;
        in >> pbu->PB.a1500VPB.VoutLimitCount;
        in >> pbu->PB.a1500VPB.VoutLimit;
        in >> pbu->PB.a1500VPB.IoutLimitCount;
        in >> pbu->PB.a1500VPB.IoutLimit;
        in >> pbu->PB.a1500VPB.versionSuffix[0];
        in >> pbu->PB.a1500VPB.versionSuffix[1];
        in >> pbu->PB.a1500VPB.versionSuffix[2];
        in >> pbu->PB.a1500VPB.tests;
        in >> pbu->PB.a1500VPB.installDate;
        in >> pbu->PB.a1500VPB.k_ov_volt;
        in >> pbu->PB.a1500VPB.k_oc_cur;
        in >> pbu->PB.a1500VPB.syncword;
        in >> pbu->PB.a1500VPB.vin_disable_radio;
        in >> pbu->PB.a1500VPB.rbunch;
        in >> pbu->PB.a1500VPB.gbunch;
        in >> pbu->PB.a1500VPB.shortCircuitLevel;
        in >> pbu->PB.a1500VPB.reserved;
        in >> pbu->PB.a1500VPB.synch_phase;
        in >> pbu->PB.a1500VPB.synch_freq;
        in >> pbu->PB.a1500VPB.bandwidth250;
        in >> pbu->PB.a1500VPB.channel;
        in >> pbu->PB.a1500VPB.utcProgram;
        in >> pbu->PB.a1500VPB.utcLow;
        in >> pbu->PB.a1500VPB.utcHigh;
        in >> pbu->PB.a1500VPB.tkCurrent;
        in >> pbu->PB.a1500VPB.tkPower;
        in >> pbu->PB.a1500VPB.mpp;
        in >> pbu->PB.a1500VPB.module;
        in >> pbu->PB.a1500VPB.ov;
        in >> pbu->PB.a1500VPB.oc;
        in >> pbu->PB.a1500VPB.radioPower;
        in >> pbu->PB.a1500VPB.edAddr;
        in >> pbu->PB.a1500VPB.gwAddr;
        in >> pbu->PB.a1500VPB.repeaterChannel;
        in >> pbu->PB.a1500VPB.repeaterPower;
        in >> pbu->PB.a1500VPB.showState;
        in >> pbu->PB.a1500VPB.CriticalLevel500;
        in >> pbu->PB.a1500VPB.CriticalLevel10;
        in >> pbu->PB.a1500VPB.pureOffset;
        in >> pbu->PB.a1500VPB.defCyclesTo500;
        in >> pbu->PB.a1500VPB.defCyclesTo10;
        in >> pbu->PB.a1500VPB.defCyclesToStep500Channel;
        in >> pbu->PB.a1500VPB.defCyclesToStep10Channel;
        in >> pbu->PB.a1500VPB.defCycles2SoftKick;
        in >> pbu->PB.a1500VPB.defCycles2HardKick;
        in >> pbu->PB.a1500VPB.imageAddr;
        in >> pbu->PB.a1500VPB.versionLow;
        in >> pbu->PB.a1500VPB.versionHigh;
        in >> pbu->PB.a1500VPB.starting500Channel;
        in >> pbu->PB.a1500VPB.boolByte2;
        in >> pbu->PB.a1500VPB.prepAddr;
        in >> pbu->PB.a1500VPB.repStep;
        in >> pbu->PB.a1500VPB.ov_startup;
        in >> pbu->PB.a1500VPB.t_mod_off;
        in >> pbu->PB.a1500VPB.toff_fallback;
        in >> pbu->PB.a1500VPB.ton_fallback;
        in >> pbu->PB.a1500VPB.fallback_time;
        in >> pbu->PB.a1500VPB.network_cnst_1;
        in >> pbu->PB.a1500VPB.network_cnst_2;
        in >> pbu->PB.a1500VPB.oc_protection;
        in >> pbu->PB.a1500VPB.oc_step;
        in >> pbu->PB.a1500VPB.cur_noise;
        in >> pbu->PB.a1500VPB.ov_step;
        in >> pbu->PB.a1500VPB.shunt;
        in >> pbu->PB.a1500VPB.max_off;
        in >> pbu->PB.a1500VPB.vin_limit;
        in >> pbu->PB.a1500VPB.vin_turn_on;
        in >> pbu->PB.a1500VPB.vin_switch_off;
    }
    else if (pbu->parameterBlockFamily == Family1500V_2nd)
    {
        in >> pbu->PB.a1500_2ndVPB.barrier;
        in >> pbu->PB.a1500_2ndVPB.netId;
        in >> pbu->PB.a1500_2ndVPB.myBunch;
        in >> pbu->PB.a1500_2ndVPB.groupId;
        in >> pbu->PB.a1500_2ndVPB.myMac[0];
        in >> pbu->PB.a1500_2ndVPB.myMac[1];
        in >> pbu->PB.a1500_2ndVPB.myMac[2];
        in >> pbu->PB.a1500_2ndVPB.myMac[3];
        in >> pbu->PB.a1500_2ndVPB.myMac[4];
        in >> pbu->PB.a1500_2ndVPB.myMac[5];
        in >> pbu->PB.a1500_2ndVPB.dFk[0];
        in >> pbu->PB.a1500_2ndVPB.dFk[1];
        in >> pbu->PB.a1500_2ndVPB.dFk[2];
        in >> pbu->PB.a1500_2ndVPB.dFk[3];
        in >> pbu->PB.a1500_2ndVPB.vrefPolynom[0];
        in >> pbu->PB.a1500_2ndVPB.vrefPolynom[1];
        in >> pbu->PB.a1500_2ndVPB.vrefPolynom[2];
        in >> pbu->PB.a1500_2ndVPB.linearK[0][0];
        in >> pbu->PB.a1500_2ndVPB.linearK[0][1];
        in >> pbu->PB.a1500_2ndVPB.linearK[1][0];
        in >> pbu->PB.a1500_2ndVPB.linearK[1][1];
        in >> pbu->PB.a1500_2ndVPB.linearK[2][0];
        in >> pbu->PB.a1500_2ndVPB.linearK[2][1];
        in >> pbu->PB.a1500_2ndVPB.linearK[3][0];
        in >> pbu->PB.a1500_2ndVPB.linearK[3][1];
        in >> pbu->PB.a1500_2ndVPB.linearK[4][0];
        in >> pbu->PB.a1500_2ndVPB.linearK[4][1];
        in >> pbu->PB.a1500_2ndVPB.linearK[5][0];
        in >> pbu->PB.a1500_2ndVPB.linearK[5][1];
        in >> pbu->PB.a1500_2ndVPB.linearK[6][0];
        in >> pbu->PB.a1500_2ndVPB.linearK[6][1];

        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curKey[15] = static_cast<char>(temp);

        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[0] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[1] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[2] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[3] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[4] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[5] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[6] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[7] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[8] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[9] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[10] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[11] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[12] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[13] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[14] = static_cast<char>(temp);
        in >> temp;
        pbu->PB.a1500_2ndVPB.curIV[15] = static_cast<char>(temp);

        in >> pbu->PB.a1500_2ndVPB.ef_InputCurrentThreshold;
        in >> pbu->PB.a1500_2ndVPB.ef_OccurrenceThreshold;
        in >> pbu->PB.a1500_2ndVPB.ef_CountDownTimer;
        in >> pbu->PB.a1500_2ndVPB.ef_AlphaNumerator;
        in >> pbu->PB.a1500_2ndVPB.ef_ModuleOff;
        in >> pbu->PB.a1500_2ndVPB.LowCurrentLimitTo255;
        in >> pbu->PB.a1500_2ndVPB.VoutLimitCount;
        in >> pbu->PB.a1500_2ndVPB.VoutLimit;
        in >> pbu->PB.a1500_2ndVPB.IoutLimitCount;
        in >> pbu->PB.a1500_2ndVPB.IoutLimit;
        in >> pbu->PB.a1500_2ndVPB.versionSuffix[0];
        in >> pbu->PB.a1500_2ndVPB.versionSuffix[1];
        in >> pbu->PB.a1500_2ndVPB.versionSuffix[2];
        in >> pbu->PB.a1500_2ndVPB.monitoring;
        in >> pbu->PB.a1500_2ndVPB.installDate;
        in >> pbu->PB.a1500_2ndVPB.k_ov_volt;
        in >> pbu->PB.a1500_2ndVPB.k_oc_cur;
        in >> pbu->PB.a1500_2ndVPB.syncword;
        in >> pbu->PB.a1500_2ndVPB.vin_disable_radio;
        in >> pbu->PB.a1500_2ndVPB.rbunch;
        in >> pbu->PB.a1500_2ndVPB.gbunch;
        in >> pbu->PB.a1500_2ndVPB.shortCircuitLevel;
        in >> pbu->PB.a1500_2ndVPB.reserved;
        in >> pbu->PB.a1500_2ndVPB.synch_phase;
        in >> pbu->PB.a1500_2ndVPB.synch_freq;
        in >> pbu->PB.a1500_2ndVPB.bandwidth250;
        in >> pbu->PB.a1500_2ndVPB.channel;
        in >> pbu->PB.a1500_2ndVPB.utcProgram;
        in >> pbu->PB.a1500_2ndVPB.utcLow;
        in >> pbu->PB.a1500_2ndVPB.utcHigh;
        in >> pbu->PB.a1500_2ndVPB.tkCurrent;
        in >> pbu->PB.a1500_2ndVPB.tkPower;
        in >> pbu->PB.a1500_2ndVPB.mpp;
        in >> pbu->PB.a1500_2ndVPB.module;
        in >> pbu->PB.a1500_2ndVPB.ov;
        in >> pbu->PB.a1500_2ndVPB.oc;
        in >> pbu->PB.a1500_2ndVPB.radioPower;
        in >> pbu->PB.a1500_2ndVPB.edAddr;
        in >> pbu->PB.a1500_2ndVPB.gwAddr;
        in >> pbu->PB.a1500_2ndVPB.repeaterChannel;
        in >> pbu->PB.a1500_2ndVPB.repeaterPower;
        in >> pbu->PB.a1500_2ndVPB.showState;
        in >> pbu->PB.a1500_2ndVPB.CriticalLevel500;
        in >> pbu->PB.a1500_2ndVPB.CriticalLevel10;
        in >> pbu->PB.a1500_2ndVPB.pureOffset;
        in >> pbu->PB.a1500_2ndVPB.defCyclesTo500;
        in >> pbu->PB.a1500_2ndVPB.defCyclesTo10;
        in >> pbu->PB.a1500_2ndVPB.defCyclesToStep500Channel;
        in >> pbu->PB.a1500_2ndVPB.defCyclesToStep10Channel;
        in >> pbu->PB.a1500_2ndVPB.defCycles2SoftKick;
        in >> pbu->PB.a1500_2ndVPB.defCycles2HardKick;
        in >> pbu->PB.a1500_2ndVPB.imageAddr;
        in >> pbu->PB.a1500_2ndVPB.versionLow;
        in >> pbu->PB.a1500_2ndVPB.versionHigh;
        in >> pbu->PB.a1500_2ndVPB.starting500Channel;
        in >> pbu->PB.a1500_2ndVPB.boolByte2;
        in >> pbu->PB.a1500_2ndVPB.prepAddr;
        in >> pbu->PB.a1500_2ndVPB.repStep;
        in >> pbu->PB.a1500_2ndVPB.ov_startup;
        in >> pbu->PB.a1500_2ndVPB.t_mod_off;
        in >> pbu->PB.a1500_2ndVPB.toff_fallback;
        in >> pbu->PB.a1500_2ndVPB.ton_fallback;
        in >> pbu->PB.a1500_2ndVPB.fallback_time;
        in >> pbu->PB.a1500_2ndVPB.network_cnst_1;
        in >> pbu->PB.a1500_2ndVPB.network_cnst_2;
        in >> pbu->PB.a1500_2ndVPB.oc_protection;
        in >> pbu->PB.a1500_2ndVPB.oc_step;
        in >> pbu->PB.a1500_2ndVPB.cur_noise;
        in >> pbu->PB.a1500_2ndVPB.ov_step;
        in >> pbu->PB.a1500_2ndVPB.shunt;
        in >> pbu->PB.a1500_2ndVPB.max_off;
        in >> pbu->PB.a1500_2ndVPB.vin_limit;
        in >> pbu->PB.a1500_2ndVPB.vin_turn_on;
        in >> pbu->PB.a1500_2ndVPB.vin_switch_off;
    }




    else
    {

    }
    return in;
}

EndDeviceParameterBlockInfoThread::EndDeviceParameterBlockInfoThread(QObject *parent) :
    QThread(parent)
{
    m_operational = false;
    m_logData = false;
    m_parametersReadFromFlash = true; /* Got to 'choose' one */
    m_saveParameterBlockInfo = false;
    m_saveParameterBlockPathBase = "";
}

EndDeviceParameterBlockInfoThread::~EndDeviceParameterBlockInfoThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void EndDeviceParameterBlockInfoThread::setCurrentOptimizerFamily(QString s)
{
      m_currentOptimizerFamily = s;
      qDebug() << Q_FUNC_INFO << " setting current family to " << s << Qt::endl;
}

void EndDeviceParameterBlockInfoThread::handleOptimizerFamilyChanged( const QString & s)
{
    if (s.length() > 2)
    {
        m_currentOptimizerFamily = s;
        qDebug() << Q_FUNC_INFO << " Family changed: to " << s << Qt::endl;
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

        qDebug() << Q_FUNC_INFO << " ERROR: " + CurrentDateTime + " Unknown Family " << s << Qt::endl;
        ErrorStr += " ERROR: ";
        ErrorStr += CurrentDateTime;
        ErrorStr += " Unknown Family ";
        ErrorStr += s;
        emit publishEndDeviceParameterBlockInfoThreadFamilyError(ErrorStr);
    }
}

void EndDeviceParameterBlockInfoThread::stopEndDeviceParameterBlockInfoThreadOperation( void )
{
    m_operational = false;
}

void EndDeviceParameterBlockInfoThread::handleCompleteEndDeviceParameterBlockInfoAvailable(const QString & key, const QString & data240)
{
    const QMutexLocker locker(&m_mutex);
    m_pbKeyAndData.clear();
    m_pbKeyAndData = key + comma + data240;
    m_parsedParameterBlockDataList.append(m_pbKeyAndData);
}

void EndDeviceParameterBlockInfoThread::handleEndDeviceCoeffLineAvailable(const QString & mac, const QString & coeffLine)
{
       // qDebug() << Q_FUNC_INFO << " Enter...";
       QString macAndData = mac+ comma + coeffLine;
       m_parsedCoeffLineDataList.append(macAndData);
       // qDebug() << Q_FUNC_INFO << " appended " << macAndData + " m_parsedCoeffLineDataList, size is " << m_parsedCoeffLineDataList.size();

}

void EndDeviceParameterBlockInfoThread::startEndDeviceParameterBlockInfoThreadInterface(int waitTimeout, const bool logging, QString docsDirectoryPath)
{
    const QMutexLocker locker(&m_mutex);
    m_waitTimeout = waitTimeout;
    m_logData = logging;
	m_operational = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString parameterBlockBaseName = docsDirectoryPath + "/AmptGUI_X";
    bool successfulStartOfThread = true;

	if (m_logData)
	  {
		// Create name, try to open for write,
	  }

    QDir docsDirectory(docsDirectoryPath);

    if (! docsDirectory.exists())
    {
        QString errString(Q_FUNC_INFO);
        errString += " ERROR: " + CurrentDateTime + " documents directory " + docsDirectoryPath + " does not exist!";
        emit publishEndDeviceParameterBlockInfoThreadError(errString);
        qDebug() << errString;
        successfulStartOfThread = false;
    }
    else
    {
        QDir parameterBlockBaseDir(parameterBlockBaseName);

        if (! parameterBlockBaseDir.exists())
        {
            if (parameterBlockBaseDir.mkdir(".") == false)
            {
                QString errString(Q_FUNC_INFO);
                errString += " ERROR: " + CurrentDateTime + " FAILED to create directory parameter block base directory " + parameterBlockBaseName;
                emit publishEndDeviceParameterBlockInfoThreadError(errString);
                qDebug() << errString;
                successfulStartOfThread = false;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " INFO: success in creating directory " << parameterBlockBaseName;
            }
        }
        if (successfulStartOfThread == true)
        {
            // qDebug() << Q_FUNC_INFO << " INFO: directory already exists " << parameterBlockBaseName;
            parameterBlockBaseName += "/ParameterBlockData";

            QDir parameterBlockBaseDir2(parameterBlockBaseName);

            if (! parameterBlockBaseDir2.exists())
            {
                if (parameterBlockBaseDir2.mkdir(".") == false)
                {
                    QString errString(Q_FUNC_INFO);
                    errString += " ERROR: " + CurrentDateTime + " FAILED to create directory parameter block base directory " + parameterBlockBaseName;
                    emit publishEndDeviceParameterBlockInfoThreadError(errString);
                    qDebug() << errString;
                    successfulStartOfThread = false;
                }
                else
                {
                    qDebug() << Q_FUNC_INFO << " INFO: created " << parameterBlockBaseName;
                }
            }
            else
            {
                // qDebug() << Q_FUNC_INFO << " INFO: already in existence " << parameterBlockBaseName;
            }
        }
    }

    if (successfulStartOfThread == true)
    {
        m_saveParameterBlockPathBase = parameterBlockBaseName;
        if (!isRunning())
            start();
        else
            m_cond.wakeOne();
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        errString += " ERROR: " + CurrentDateTime + " FATAL: Thread failed to start/wake!!!";
        emit publishEndDeviceParameterBlockInfoThreadError(errString);
        qDebug() << errString;
    }
}

bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo600V_V2_2nd(QStringList & macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;

    // qDebug() << Q_FUNC_INFO << " &&&& &&&& &&&& Trying out the new 600V2 PB ...";

    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    ParameterBlock_600V_V2_2nd  a600V_V2_2nd;
    bool ok = false;
    AmptGUI_X_Status rV = NO_ERROR;

    QString temp = justTheData.mid(0,4);
    quint16 barrier = 0;
    hexStringToDecimalUnsignedInt(temp ,barrier, true );
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.barrier,true);

    temp = justTheData.mid(4,2);
    a600V_V2_2nd.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a600V_V2_2nd.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6)); // (BYTE *) malloc(6);
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            // memcpy( (void *)a600V_V2_2nd.myMac, (void *)macAsHexString, 6 );
            memcpy( static_cast<void *>(a600V_V2_2nd.myMac), static_cast<void *>(macAsHexString), 6);
        }
    }
    // LBC COpy mac into PB

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            // memcpy( (void *)a600V_V2_2nd.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy( static_cast<void *>(a600V_V2_2nd.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }

    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a600V_V2_2nd.curIV, (void *)aesIVAsHexString, 16 );
            memcpy(static_cast<void *>(a600V_V2_2nd.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }

    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2_2nd.fetFailureCount, true );

    temp = justTheData.mid(260,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2_2nd.fetCurrentThreshold, true );

    temp = justTheData.mid(264,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2_2nd.fetDeltaCurrent, true );

    temp = justTheData.mid(268,4);

    qDebug() << " HHHHHHHHHHHHHHHHHHHHHHHHH" << temp;

    hexStringToDecimalSignedInt(temp ,a600V_V2_2nd.LowCurrentLimitTo255, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalUnsignedInt(temp ,a600V_V2_2nd.VhvLimitVout, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalUnsignedInt(temp ,a600V_V2_2nd.IhvLimitVout, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalUnsignedInt(temp ,a600V_V2_2nd.VhvLimitVins, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalUnsignedInt(temp ,a600V_V2_2nd.IhvLimitVins, true );

    temp = justTheData.mid(288,6);
    QString versionSuffix = temp;
    QString versionSuffixHexStr;

    BYTE *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a600V_V2_2nd.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            //memcpy(static_cast<void *>(a600V_V2_2nd.versionSuffix), static_cast<void *>(versionSuffixHexStr), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }
    a600V_V2_2nd.versionSuffix[0] = static_cast<BYTE>(versionSuffixHexStr.at(0).toLatin1());
    a600V_V2_2nd.versionSuffix[1] = static_cast<BYTE>(versionSuffixHexStr.at(1).toLatin1());
    a600V_V2_2nd.versionSuffix[2] = static_cast<BYTE>(versionSuffixHexStr.at(2).toLatin1());

    QString test = justTheData.mid(294,2);
    a600V_V2_2nd.tests = static_cast<BYTE>(test.toInt(&ok,16));

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    // qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,2);
    a600V_V2_2nd.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(306,2);
    a600V_V2_2nd.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(308,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.syncword,true);

    temp = justTheData.mid(312,2);
    a600V_V2_2nd.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a600V_V2_2nd.rbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(316,2);
    a600V_V2_2nd.gbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(318,2);
    a600V_V2_2nd.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a600V_V2_2nd.reserved = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(322,2);
    a600V_V2_2nd.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a600V_V2_2nd.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a600V_V2_2nd.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a600V_V2_2nd.channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a600V_V2_2nd.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a600V_V2_2nd.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a600V_V2_2nd.tkPower,true);

    temp = justTheData.mid(370,2);
    a600V_V2_2nd.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a600V_V2_2nd.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a600V_V2_2nd.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a600V_V2_2nd.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a600V_V2_2nd.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a600V_V2_2nd.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a600V_V2_2nd.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));;

    temp = justTheData.mid(384,2);
    a600V_V2_2nd.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a600V_V2_2nd.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<quint8>(temp.toInt(&ok,16));
    a600V_V2_2nd.boolByte1 = boolByte1;

    //qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a600V_V2_2nd.showState = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a600V_V2_2nd.CriticalLevel500);

    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a600V_V2_2nd.CriticalLevel10);

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a600V_V2_2nd.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.versionHigh,true);

    temp = justTheData.mid(436,2);
    a600V_V2_2nd.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<BYTE>(temp.toInt(&ok,16));
    a600V_V2_2nd.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2_2nd.prepAddr,true);

    temp = justTheData.mid(444,2);
    a600V_V2_2nd.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a600V_V2_2nd.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a600V_V2_2nd.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a600V_V2_2nd.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a600V_V2_2nd.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a600V_V2_2nd.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a600V_V2_2nd.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a600V_V2_2nd.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a600V_V2_2nd.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a600V_V2_2nd.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a600V_V2_2nd.cur_noise,true);

    temp = justTheData.mid(468,2);
    a600V_V2_2nd.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a600V_V2_2nd.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a600V_V2_2nd.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a600V_V2_2nd.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a600V_V2_2nd.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a600V_V2_2nd.vin_switch_off = static_cast<BYTE>(temp.toInt(&ok,16));


    QString linearKs = QString::number(static_cast<double>(a600V_V2_2nd.linearK[0][0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[1][0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[2][0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[3][0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[4][0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[5][0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[6][0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a600V_V2_2nd.linearKs being sent: " << linearKs;

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0),macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a600V_V2_2nd.linearKs have been sent: " << linearKs;


    QString edComms = QString::number(a600V_V2_2nd.netId) + comma + QString::number(a600V_V2_2nd.myBunch) + comma +
            QString::number(a600V_V2_2nd.groupId) + comma + QString::number(a600V_V2_2nd.syncword) + comma +
            QString::number(a600V_V2_2nd.rbunch) + comma + QString::number(a600V_V2_2nd.gbunch) + comma +
            QString::number(a600V_V2_2nd.channel) + comma + QString::number(a600V_V2_2nd.radioPower) + comma +
            QString::number(a600V_V2_2nd.edAddr) + comma + QString::number(a600V_V2_2nd.gwAddr) + comma +
            QString::number(a600V_V2_2nd.repeaterChannel) + comma + QString::number(a600V_V2_2nd.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a600V_V2_2nd.starting500Channel) + comma +
            QString::number(a600V_V2_2nd.CriticalLevel10) + comma + QString::number(a600V_V2_2nd.CriticalLevel500) + comma +
            QString::number(a600V_V2_2nd.showState) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms;

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = versionSuffixHexStr + comma + QString::number(a600V_V2_2nd.fetFailureCount) + comma + QString::number(a600V_V2_2nd.fetCurrentThreshold) + comma +
            QString::number(a600V_V2_2nd.fetDeltaCurrent) + comma + QString::number(a600V_V2_2nd.LowCurrentLimitTo255) + comma +
            QString::number(a600V_V2_2nd.VhvLimitVout) + comma + QString::number(a600V_V2_2nd.IhvLimitVout) + comma +
            QString::number(a600V_V2_2nd.VhvLimitVins) + comma + QString::number(a600V_V2_2nd.IhvLimitVins);

    if ((versionSuffixHexStr == "1F ") || (versionSuffixHexStr == "1G "))
    {
        int Timer1 = a600V_V2_2nd.cur_noise & 0x00FF;
        int Timer2 = (a600V_V2_2nd.cur_noise & 0xFF00) >> 8;
        int CyclesOff = ((a600V_V2_2nd.reserved & 0xF0) >> 4);

        // qDebug() << Q_FUNC_INFO << " INFO: reserved: " << a600V_V2_2nd.reserved;

        // qDebug() << Q_FUNC_INFO << " INFO: HIGH NIBBLE of RESERVE: " << CyclesOff;
        int TimesToCycleMPP = (a600V_V2_2nd.reserved & 0x0F);
        // qDebug() << Q_FUNC_INFO << " INFO: LOW NIBBLE of RESERVE: " << TimesToCycleMPP;

        edProtections += comma + QString::number(Timer1) + comma + QString::number(Timer2) + comma +
                QString::number(a600V_V2_2nd.defCycles2SoftKick) + comma + QString::number(a600V_V2_2nd.defCycles2HardKick) + comma +
                QString::number(CyclesOff,16) + comma + QString::number(TimesToCycleMPP,16) + comma +
                QString::number(a600V_V2_2nd.tests & 0x01);
    }

    // qDebug() << Q_FUNC_INFO << " &&&& &&&& &&&& &&&& protections being sent " << edProtections;
    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);
    // qDebug() << Q_FUNC_INFO << " protections sent " << edProtections;


    QString powerCntrl = QString::number(a600V_V2_2nd.vin_disable_radio) + comma + QString::number(a600V_V2_2nd.ov) + comma + QString::number(a600V_V2_2nd.oc) + comma +
            QString::number(a600V_V2_2nd.ov_startup) + comma + QString::number(a600V_V2_2nd.oc_step) + comma +
            QString::number(a600V_V2_2nd.cur_noise) + comma + QString::number(a600V_V2_2nd.ov_step) + comma +
            QString::number(a600V_V2_2nd.vin_limit) + comma + QString::number(a600V_V2_2nd.vin_turn_on) + comma +
            QString::number(a600V_V2_2nd.vin_switch_off) + comma + QString::number(a600V_V2_2nd.module) + comma + QString::number(a600V_V2_2nd.mpp);


   // qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), powerCntrl);

    // qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a600V_V2_2nd.t_mod_off) + comma + QString::number(a600V_V2_2nd.toff_fallback) + comma +
            QString::number(a600V_V2_2nd.ton_fallback) + comma + QString::number(a600V_V2_2nd.fallback_time) + comma +
            QString::number(a600V_V2_2nd.oc_protection);

   // qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    // qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a600V_V2_2nd.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.tkCurrent)) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.tkPower)) + comma +
            QString::number(a600V_V2_2nd.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a600V_V2_2nd.dFk[0])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.dFk[1])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.dFk[2])) + comma +
            QString::number(static_cast<double>(a600V_V2_2nd.dFk[3])) + comma +
            QString::number(a600V_V2_2nd.pureOffset) + comma +
            QString::number(a600V_V2_2nd.LowCurrentLimitTo255);

    //qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    //qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    //qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    //qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    //qDebug() << Q_FUNC_INFO << " suffix1:" << versionSuffix.at(0) << " suffix2:" << versionSuffix.at(1) << " suffix3:" << versionSuffix.at(2);

   //  qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);

    QString versionInfo = QString::number(a600V_V2_2nd.versionHigh) + comma + QString::number(a600V_V2_2nd.versionLow) + comma +
            QString::number(a600V_V2_2nd.utcHigh) + comma + QString::number(a600V_V2_2nd.utcLow) + comma +
            QString::number(a600V_V2_2nd.shunt) + comma + QString::number(a600V_V2_2nd.utcProgram) + comma + versionSuffixHexStr;
    //qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    //qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    /*
    QString protectionsInfo = versionSuffixHexStr + comma + QString::number(a600V_V2_2nd.fetFailureCount) + comma +
            QString::number(a600V_V2_2nd.fetCurrentThreshold) + comma + QString::number(a600V_V2_2nd.fetDeltaCurrent) + comma +
            QString::number(a600V_V2_2nd.VhvLimitVout) + comma + QString::number(a600V_V2_2nd.IhvLimitVout) + comma +
            QString::number(a600V_V2_2nd.VhvLimitVins) + comma + QString::number(a600V_V2_2nd.IhvLimitVins);


    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0), macFlashFamily.at(2), protectionsInfo);
    */

    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a600V_V2_2nd.synch_freq) + comma + QString::number(a600V_V2_2nd.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));



    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);

        // qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a600V_V2_2ndVPB = a600V_V2_2nd;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        // qDebug() << Q_FUNC_INFO << " INFO: SIZE OF parameterBlocksStorage before insert:" << parameterBlocksStorage.size() << " key is " << pbKey;
        parameterBlocksStorage.insert(pbKey,pPB);
        // qDebug() << Q_FUNC_INFO << " INFO: SIZE OF parameterBlocksStorage after insert:" << parameterBlocksStorage.size() << " key is " << pbKey;
        if (m_saveParameterBlockInfo == true)
        {
            // qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }


    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }

    return retValue;
}




bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo600V_V2(QStringList & macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    ParameterBlock_600V_V2 a600V_V2PB;

    bool ok = false;
    AmptGUI_X_Status rV = NO_ERROR;

    // qDebug() << Q_FUNC_INFO << " starting ...";

    QString temp = justTheData.mid(288,6);
    QString versionSuffix = temp;
    QString versionSuffixHexStr;

    BYTE *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a600V_V2PB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            //memcpy(static_cast<void *>(a600V_V2_2nd.versionSuffix), static_cast<void *>(versionSuffixHexStr), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }

    // qDebug() << Q_FUNC_INFO << " INFO: versionSuffixStr " << versionSuffixHexStr << " versionSuffix: " << versionSuffix;

    if ((versionSuffixHexStr == "1F ") || (versionSuffixHexStr == "1G "))
    {
        return endDeviceParameterBlockInfo600V_V2_2nd(macFlashFamily,justTheData,Family600V_V2_2nd_Shunt);
        // CALL new 600V2 PB ...
        // return return of value
    }

    temp = justTheData.mid(0,4);
    quint16 barrier = 0;
    hexStringToDecimalUnsignedInt(temp ,barrier, true );
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.barrier,true);

    temp = justTheData.mid(4,2);
    a600V_V2PB.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a600V_V2PB.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());

    // qDebug() << Q_FUNC_INFO << " KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK myMac " << myMac;
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6)); //(BYTE *) malloc(6);
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);

        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            //memcpy( (void *)a600V_V2PB.myMac, (void *)macAsHexString, 6 );
            // qDebug() << Q_FUNC_INFO << "KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK "
                    // << macAsHexString[0] << " " << macAsHexString[1] << " " << macAsHexString[2];

            memcpy( static_cast<void *>(a600V_V2PB.myMac), static_cast<void *>(macAsHexString), 6);
            // qDebug() << Q_FUNC_INFO << "KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK "
                     // << a600V_V2PB.myMac[0] << " " << a600V_V2PB.myMac[1] << " " << a600V_V2PB.myMac[2];
        }
    }
    a600V_V2PB.versionSuffix[0] = static_cast<BYTE>(versionSuffixHexStr.at(0).toLatin1());
    a600V_V2PB.versionSuffix[1] = static_cast<BYTE>(versionSuffixHexStr.at(1).toLatin1());
    a600V_V2PB.versionSuffix[2] = static_cast<BYTE>(versionSuffixHexStr.at(2).toLatin1());
    // LBC COpy mac into PB

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); //(BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            //memcpy( (void *)a600V_V2PB.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy(static_cast<void *>(a600V_V2PB.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }


    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); //(BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a600V_V2PB.curIV, (void *)aesIVAsHexString, 16 );
            memcpy( static_cast<void *>(a600V_V2PB.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }

    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2PB.fetFailureCount, true );

    temp = justTheData.mid(260,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2PB.fetCurrentThreshold, true );

    temp = justTheData.mid(264,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2PB.fetDeltaCurrent, true );

    temp = justTheData.mid(268,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2PB.oscLowCurrentLimitInmA, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalUnsignedInt(temp ,a600V_V2PB.oscDeltaV, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2PB.oscOVStartupDelay, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2PB.oscAfterStartupDelay, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalSignedInt(temp ,a600V_V2PB.oscLowCurrentOnlyDelay, true );

    // temp = justTheData.mid(288,6);
    // QString versionSuffix = temp;
    // QString versionSuffixHexStr;

    /*
    BYTE *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a600V_V2PB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            //memcpy(static_cast<void *>(a600V_V2_2nd.versionSuffix), static_cast<void *>(versionSuffixHexStr), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }
    */

    temp = justTheData.mid(294,2);
    QString test = temp;
    a600V_V2PB.tests = static_cast<BYTE>(test.toInt());

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    // qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,2);
    a600V_V2PB.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(306,2);
    a600V_V2PB.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(308,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.syncword,true);

    temp = justTheData.mid(312,2);
    a600V_V2PB.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a600V_V2PB.rbunch = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(316,2);
    a600V_V2PB.gbunch = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(318,2);
    a600V_V2PB.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a600V_V2PB.reserved = static_cast<BYTE>(temp.toInt());

    temp = justTheData.mid(322,2);
    a600V_V2PB.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a600V_V2PB.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a600V_V2PB.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a600V_V2PB.channel = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a600V_V2PB.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a600V_V2PB.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a600V_V2PB.tkPower,true);

    temp = justTheData.mid(370,2);
    a600V_V2PB.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a600V_V2PB.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a600V_V2PB.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a600V_V2PB.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a600V_V2PB.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a600V_V2PB.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a600V_V2PB.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(384,2);
    a600V_V2PB.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a600V_V2PB.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<BYTE>(temp.toInt(&ok,16));
    a600V_V2PB.boolByte1 = boolByte1;

    // qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a600V_V2PB.showState = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a600V_V2PB.CriticalLevel500);

    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a600V_V2PB.CriticalLevel10);

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a600V_V2PB.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.versionHigh,true);

    temp = justTheData.mid(436,2);
    a600V_V2PB.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<BYTE>(temp.toInt(&ok,16));
    a600V_V2PB.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a600V_V2PB.prepAddr,true);

    temp = justTheData.mid(444,2);
    a600V_V2PB.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a600V_V2PB.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a600V_V2PB.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a600V_V2PB.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a600V_V2PB.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a600V_V2PB.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a600V_V2PB.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a600V_V2PB.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a600V_V2PB.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a600V_V2PB.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a600V_V2PB.cur_noise,true);

    temp = justTheData.mid(468,2);
    a600V_V2PB.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a600V_V2PB.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a600V_V2PB.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a600V_V2PB.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a600V_V2PB.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a600V_V2PB.vin_switch_off = static_cast<BYTE>(temp.toInt(&ok,16));


    QString linearKs = QString::number(static_cast<double>(a600V_V2PB.linearK[0][0])) + comma + QString::number(static_cast<double>(a600V_V2PB.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.linearK[1][0])) + comma + QString::number(static_cast<double>(a600V_V2PB.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.linearK[2][0])) + comma + QString::number(static_cast<double>(a600V_V2PB.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.linearK[3][0])) + comma + QString::number(static_cast<double>(a600V_V2PB.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.linearK[4][0])) + comma + QString::number(static_cast<double>(a600V_V2PB.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.linearK[5][0])) + comma + QString::number(static_cast<double>(a600V_V2PB.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.linearK[6][0])) + comma + QString::number(static_cast<double>(a600V_V2PB.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a600V_V2PB.linearKs being sent: " << linearKs << "for mac:" << macFlashFamily.at(0) << " " << macFlashFamily.at(1) << " " << macFlashFamily.at(2);

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0), macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a600V_V2PB.linearKs have been sent: " << linearKs;


    QString edComms = QString::number(a600V_V2PB.netId) + comma + QString::number(a600V_V2PB.myBunch) + comma +
            QString::number(a600V_V2PB.groupId) + comma + QString::number(a600V_V2PB.syncword) + comma +
            QString::number(a600V_V2PB.rbunch) + comma + QString::number(a600V_V2PB.gbunch) + comma +
            QString::number(a600V_V2PB.channel) + comma + QString::number(a600V_V2PB.radioPower) + comma +
            QString::number(a600V_V2PB.edAddr) + comma + QString::number(a600V_V2PB.gwAddr) + comma +
            QString::number(a600V_V2PB.repeaterChannel) + comma + QString::number(a600V_V2PB.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a600V_V2PB.starting500Channel) + comma +
            QString::number(a600V_V2PB.CriticalLevel10) + comma + QString::number(a600V_V2PB.CriticalLevel500) + comma +
            QString::number(a600V_V2PB.showState) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms;

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = QString::number(a600V_V2PB.fetFailureCount) + comma + QString::number(a600V_V2PB.fetCurrentThreshold) + comma +
            QString::number(a600V_V2PB.fetDeltaCurrent) + comma + QString::number(a600V_V2PB.oscLowCurrentLimitInmA) + comma +
            QString::number(a600V_V2PB.oscDeltaV) + comma + QString::number(a600V_V2PB.oscOVStartupDelay) + comma +
            QString::number(a600V_V2PB.oscAfterStartupDelay) + comma + QString::number(a600V_V2PB.oscLowCurrentOnlyDelay);

    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);


    // qDebug() << Q_FUNC_INFO << " OSC protections being sent " << edProtections;
    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);


    QString powerCntrl = QString::number(a600V_V2PB.vin_disable_radio) + comma + QString::number(a600V_V2PB.ov) + comma + QString::number(a600V_V2PB.oc) + comma +
            QString::number(a600V_V2PB.ov_startup) + comma + QString::number(a600V_V2PB.oc_step) + comma +
            QString::number(a600V_V2PB.cur_noise) + comma + QString::number(a600V_V2PB.ov_step) + comma +
            QString::number(a600V_V2PB.vin_limit) + comma + QString::number(a600V_V2PB.vin_turn_on) + comma +
            QString::number(a600V_V2PB.vin_switch_off) + comma + QString::number(a600V_V2PB.module) + comma + QString::number(a600V_V2PB.mpp);


   // qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), powerCntrl);

    // qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a600V_V2PB.t_mod_off) + comma + QString::number(a600V_V2PB.toff_fallback) + comma +
            QString::number(a600V_V2PB.ton_fallback) + comma + QString::number(a600V_V2PB.fallback_time) + comma +
            QString::number(a600V_V2PB.oc_protection);

   // qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    // qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a600V_V2PB.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.tkCurrent)) + comma +
            QString::number(static_cast<double>(a600V_V2PB.tkPower)) + comma + QString::number(a600V_V2PB.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a600V_V2PB.dFk[0])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.dFk[1])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.dFk[2])) + comma +
            QString::number(static_cast<double>(a600V_V2PB.dFk[3])) + comma +
            QString::number(a600V_V2PB.pureOffset);

    //qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    //qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    //qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    //qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    //qDebug() << Q_FUNC_INFO << " suffix1:" << versionSuffix.at(0) << " suffix2:" << versionSuffix.at(1) << " suffix3:" << versionSuffix.at(2);

    // qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);


    QString versionInfo = QString::number(a600V_V2PB.versionHigh) + comma + QString::number(a600V_V2PB.versionLow) + comma +
            QString::number(a600V_V2PB.utcHigh) + comma + QString::number(a600V_V2PB.utcLow) + comma +
            QString::number(a600V_V2PB.shunt) + comma + QString::number(a600V_V2PB.utcProgram) + comma + versionSuffixHexStr;

    //QString versionInfo = QString::number(a600V_V2PB.versionHigh) + comma + QString::number(a600V_V2PB.versionLow) + comma +
     //       QString::number(a600V_V2PB.utcHigh) + comma + QString::number(a600V_V2PB.utcLow) + comma + QString::number(a600V_V2PB.shunt) + comma
      //      + QString::number(a600V_V2PB.utcProgram);

    //qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    //qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a600V_V2PB.synch_freq) + comma + QString::number(a600V_V2PB.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));


    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);
        // qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a600V_V2VPB = a600V_V2PB;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        // qDebug() << Q_FUNC_INFO << " INFO: SIZE OF parameterBlocksStorage before insert:" << parameterBlocksStorage.size() << " key is " << pbKey;
        parameterBlocksStorage.insert(pbKey,pPB);
        // qDebug() << Q_FUNC_INFO << " INFO: SIZE OF parameterBlocksStorage after insert:" << parameterBlocksStorage.size() << " key is " << pbKey;

        if (m_saveParameterBlockInfo == true)
        {
            // qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }

    return retValue;
}


bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo1000V(QStringList & macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    ParameterBlock_1000V a1000VPB;
    bool ok = false;
    AmptGUI_X_Status rV = NO_ERROR;

    QString temp = justTheData.mid(0,4);
    quint16 barrier = 0;
    hexStringToDecimalUnsignedInt(temp ,barrier, true );
    hexStringToDecimalUnsignedInt(temp,a1000VPB.barrier,true);

    temp = justTheData.mid(4,2);
    a1000VPB.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a1000VPB.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6));
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            //memcpy( (void *)a1000VPB.myMac, (void *)macAsHexString, 6 );
            memcpy(static_cast<void *>(a1000VPB.myMac), static_cast<void *>(macAsHexString), 6);
        }
    }
    // LBC COpy mac into PB

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a1000VPB.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a1000VPB.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a1000VPB.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a1000VPB.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a1000VPB.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a1000VPB.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a1000VPB.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a1000VPB.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            //memcpy( (void *)a1000VPB.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy( static_cast<void *>(a1000VPB.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }


    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a1000VPB.curIV, (void *)aesIVAsHexString, 16 );
            memcpy(static_cast<void *>(a1000VPB.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }

    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a1000VPB.fetFailureCount, true );

    temp = justTheData.mid(260,4);
    hexStringToDecimalSignedInt(temp ,a1000VPB.fetCurrentThreshold, true );

    temp = justTheData.mid(264,4);
    hexStringToDecimalSignedInt(temp ,a1000VPB.fetDeltaCurrent, true );

    temp = justTheData.mid(268,4);
    hexStringToDecimalSignedInt(temp ,a1000VPB.oscLowCurrentLimitInmA, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalUnsignedInt(temp ,a1000VPB.oscDeltaV, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalSignedInt(temp ,a1000VPB.oscOVStartupDelay, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalSignedInt(temp ,a1000VPB.oscAfterStartupDelay, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalSignedInt(temp ,a1000VPB.oscLowCurrentOnlyDelay, true );

    temp = justTheData.mid(288,8);
    QString test = temp;

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    // qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,2);
    a1000VPB.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(306,2);
    a1000VPB.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(308,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.syncword,true);

    temp = justTheData.mid(312,2);
    a1000VPB.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a1000VPB.rbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(316,2);
    a1000VPB.gbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(318,2);
    a1000VPB.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a1000VPB.reserved = static_cast<BYTE>(temp.toInt());

    temp = justTheData.mid(322,2);
    a1000VPB.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a1000VPB.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a1000VPB.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a1000VPB.channel = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a1000VPB.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a1000VPB.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a1000VPB.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a1000VPB.tkPower,true);

    temp = justTheData.mid(370,2);
    a1000VPB.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a1000VPB.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a1000VPB.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a1000VPB.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a1000VPB.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a1000VPB.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a1000VPB.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(384,2);
    a1000VPB.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a1000VPB.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<BYTE>(temp.toInt(&ok,16));
    a1000VPB.boolByte1 = boolByte1;

    // qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a1000VPB.showState = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a1000VPB.CriticalLevel500);

    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a1000VPB.CriticalLevel10);

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a1000VPB.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.versionHigh,true);

    temp = justTheData.mid(436,2);
    a1000VPB.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<quint8>(temp.toInt(&ok,16));
    a1000VPB.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a1000VPB.prepAddr,true);

    temp = justTheData.mid(444,2);
    a1000VPB.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a1000VPB.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a1000VPB.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a1000VPB.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a1000VPB.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a1000VPB.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a1000VPB.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a1000VPB.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a1000VPB.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a1000VPB.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a1000VPB.cur_noise,true);

    temp = justTheData.mid(468,2);
    a1000VPB.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a1000VPB.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a1000VPB.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a1000VPB.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a1000VPB.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a1000VPB.vin_switch_off = static_cast<BYTE>(temp.toInt(&ok,16));


    QString linearKs = QString::number(static_cast<double>(a1000VPB.linearK[0][0])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[1][0])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[2][0])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[3][0])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[4][0])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[5][0])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[6][0])) + comma +
            QString::number(static_cast<double>(a1000VPB.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a1000VPB.linearKs being sent: " << linearKs;

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0),macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a1000VPB.linearKs have been sent: " << linearKs;


    QString edComms = QString::number(a1000VPB.netId) + comma + QString::number(a1000VPB.myBunch) + comma +
            QString::number(a1000VPB.groupId) + comma + QString::number(a1000VPB.syncword) + comma +
            QString::number(a1000VPB.rbunch) + comma + QString::number(a1000VPB.gbunch) + comma +
            QString::number(a1000VPB.channel) + comma + QString::number(a1000VPB.radioPower) + comma +
            QString::number(a1000VPB.edAddr) + comma + QString::number(a1000VPB.gwAddr) + comma +
            QString::number(a1000VPB.repeaterChannel) + comma + QString::number(a1000VPB.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a1000VPB.starting500Channel) + comma +
            QString::number(a1000VPB.CriticalLevel10) + comma + QString::number(a1000VPB.CriticalLevel500) + comma +
            QString::number(a1000VPB.showState) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms;

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = QString::number(a1000VPB.fetFailureCount) + comma + QString::number(a1000VPB.fetCurrentThreshold) + comma +
            QString::number(a1000VPB.fetDeltaCurrent) + comma + QString::number(a1000VPB.oscLowCurrentLimitInmA) + comma +
            QString::number(a1000VPB.oscDeltaV) + comma + QString::number(a1000VPB.oscOVStartupDelay) + comma +
            QString::number(a1000VPB.oscAfterStartupDelay) + comma + QString::number(a1000VPB.oscLowCurrentOnlyDelay);

    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2),edProtections);




    QString powerCntrl = QString::number(a1000VPB.vin_disable_radio) + comma + QString::number(a1000VPB.ov) + comma + QString::number(a1000VPB.oc) + comma +
            QString::number(a1000VPB.ov_startup) + comma + QString::number(a1000VPB.oc_step) + comma +
            QString::number(a1000VPB.cur_noise) + comma + QString::number(a1000VPB.ov_step) + comma +
            QString::number(a1000VPB.vin_limit) + comma + QString::number(a1000VPB.vin_turn_on) + comma +
            QString::number(a1000VPB.vin_switch_off) + comma + QString::number(a1000VPB.module) + comma + QString::number(a1000VPB.mpp);


   // qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), powerCntrl);

    // qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a1000VPB.t_mod_off) + comma + QString::number(a1000VPB.toff_fallback) + comma +
            QString::number(a1000VPB.ton_fallback) + comma + QString::number(a1000VPB.fallback_time) + comma +
            QString::number(a1000VPB.oc_protection);

   // qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    // qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a1000VPB.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a1000VPB.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a1000VPB.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a1000VPB.tkCurrent)) + comma +
            QString::number(static_cast<double>(a1000VPB.tkPower)) + comma +
            QString::number(a1000VPB.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a1000VPB.dFk[0])) + comma +
            QString::number(static_cast<double>(a1000VPB.dFk[1])) + comma +
            QString::number(static_cast<double>(a1000VPB.dFk[2])) + comma +
            QString::number(static_cast<double>(a1000VPB.dFk[3])) + comma +
            QString::number(a1000VPB.pureOffset);

    //qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    //qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    //qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    //qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    //qDebug() << Q_FUNC_INFO << " suffix1:" << versionSuffix.at(0) << " suffix2:" << versionSuffix.at(1) << " suffix3:" << versionSuffix.at(2);

    // qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);


    QString versionInfo = QString::number(a1000VPB.versionHigh) + comma + QString::number(a1000VPB.versionLow) + comma +
            QString::number(a1000VPB.utcHigh) + comma + QString::number(a1000VPB.utcLow) + comma + QString::number(a1000VPB.shunt) + comma
            + QString::number(a1000VPB.utcProgram);

    //qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    //qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a1000VPB.synch_freq) + comma + QString::number(a1000VPB.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));



    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);

        // qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a1000VPB = a1000VPB;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        parameterBlocksStorage.insert(pbKey,pPB);

        if (m_saveParameterBlockInfo == true)
        {
            qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo1300V_2nd(QStringList & macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    ParameterBlock_1300V_2nd a1300VPB;
    bool ok = false;
    AmptGUI_X_Status rV = NO_ERROR;

    // qDebug() << Q_FUNC_INFO << " starting ...";
    QString temp = justTheData.mid(0,4);
    quint16 barrier = 0;
    hexStringToDecimalUnsignedInt(temp ,barrier, true );
    hexStringToDecimalUnsignedInt(temp,a1300VPB.barrier,true);

    temp = justTheData.mid(4,2);
    a1300VPB.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a1300VPB.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6)); // (BYTE *) malloc(6);
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.myMac, (void *)macAsHexString, 6 );
            memcpy( static_cast<void *>(a1300VPB.myMac), static_cast<void *>(macAsHexString), 6);
        }
    }
    // LBC COpy mac into PB

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a1300VPB.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a1300VPB.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a1300VPB.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy( static_cast<void *>(a1300VPB.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }


    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curIV, (void *)aesIVAsHexString, 16 );
            memcpy(static_cast<void *>(a1300VPB.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }

    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.fetFailureCount, true );

    temp = justTheData.mid(260,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.fetCurrentThreshold, true );

    temp = justTheData.mid(264,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.fetDeltaCurrent, true );

    temp = justTheData.mid(268,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.LowCurrentLimitTo255, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.VhvLimitVout, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.IhvLimitVout, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.VhvLimitVins, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.IhvLimitVins, true );

    temp = justTheData.mid(288,6);
    QString versionSuffix = temp;
    QString versionSuffixHexStr;

    BYTE * versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a1300VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            //memcpy(static_cast<void *>(a1300VPB.versionSuffix), static_cast<void *>(versionSuffixHexStr), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }
    a1300VPB.versionSuffix[0] = static_cast<BYTE>(versionSuffixHexStr.at(0).toLatin1());
    a1300VPB.versionSuffix[1] = static_cast<BYTE>(versionSuffixHexStr.at(1).toLatin1());
    a1300VPB.versionSuffix[2] = static_cast<BYTE>(versionSuffixHexStr.at(2).toLatin1());

    qDebug() << Q_FUNC_INFO << " INFO: 1300V version " << a1300VPB.versionSuffix[0]
             <<a1300VPB.versionSuffix[1] << a1300VPB.versionSuffix[2] << "\n";

    QString test = justTheData.mid(294,2);
    a1300VPB.tests = static_cast<BYTE>(test.toInt());

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    // qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,2);
    a1300VPB.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(306,2);
    a1300VPB.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(308,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.syncword,true);

    temp = justTheData.mid(312,2);
    a1300VPB.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a1300VPB.rbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(316,2);
    a1300VPB.gbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(318,2);
    a1300VPB.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a1300VPB.reserved = static_cast<BYTE>(temp.toInt());

    temp = justTheData.mid(322,2);
    a1300VPB.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a1300VPB.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a1300VPB.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a1300VPB.channel = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a1300VPB.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a1300VPB.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a1300VPB.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a1300VPB.tkPower,true);

    temp = justTheData.mid(370,2);
    a1300VPB.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a1300VPB.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a1300VPB.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a1300VPB.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a1300VPB.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a1300VPB.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a1300VPB.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));;

    temp = justTheData.mid(384,2);
    a1300VPB.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a1300VPB.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<quint8>(temp.toInt(&ok,16));
    a1300VPB.boolByte1 = boolByte1;

    //qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a1300VPB.showState = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a1300VPB.CriticalLevel500);

    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a1300VPB.CriticalLevel10);

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a1300VPB.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.versionHigh,true);

    temp = justTheData.mid(436,2);
    a1300VPB.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<BYTE>(temp.toInt(&ok,16));
    a1300VPB.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.prepAddr,true);

    temp = justTheData.mid(444,2);
    a1300VPB.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a1300VPB.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a1300VPB.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a1300VPB.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a1300VPB.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a1300VPB.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a1300VPB.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a1300VPB.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a1300VPB.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a1300VPB.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a1300VPB.cur_noise,true);

    temp = justTheData.mid(468,2);
    a1300VPB.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a1300VPB.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a1300VPB.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a1300VPB.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a1300VPB.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a1300VPB.vin_switch_off = static_cast<BYTE>(temp.toInt(&ok,16));


    QString linearKs = QString::number(static_cast<double>(a1300VPB.linearK[0][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[1][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[2][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[3][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[4][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[5][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[6][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a1300VPB.linearKs being sent: " << linearKs;

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0),macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a1300VPB.linearKs have been sent: " << linearKs;


    QString edComms = QString::number(a1300VPB.netId) + comma + QString::number(a1300VPB.myBunch) + comma +
            QString::number(a1300VPB.groupId) + comma + QString::number(a1300VPB.syncword) + comma +
            QString::number(a1300VPB.rbunch) + comma + QString::number(a1300VPB.gbunch) + comma +
            QString::number(a1300VPB.channel) + comma + QString::number(a1300VPB.radioPower) + comma +
            QString::number(a1300VPB.edAddr) + comma + QString::number(a1300VPB.gwAddr) + comma +
            QString::number(a1300VPB.repeaterChannel) + comma + QString::number(a1300VPB.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a1300VPB.starting500Channel) + comma +
            QString::number(a1300VPB.CriticalLevel10) + comma + QString::number(a1300VPB.CriticalLevel500) + comma +
            QString::number(a1300VPB.showState) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms;

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = versionSuffixHexStr + comma + QString::number(a1300VPB.fetFailureCount) + comma + QString::number(a1300VPB.fetCurrentThreshold) + comma +
            QString::number(a1300VPB.fetDeltaCurrent) + comma + QString::number(a1300VPB.LowCurrentLimitTo255) + comma +
            QString::number(a1300VPB.VhvLimitVout) + comma + QString::number(a1300VPB.IhvLimitVout) + comma +
            QString::number(a1300VPB.VhvLimitVins) + comma + QString::number(a1300VPB.IhvLimitVins);

    if (versionSuffixHexStr == "1_D")
    {
        int Timer1 = a1300VPB.cur_noise & 0x000F;
        int Timer2 = (a1300VPB.cur_noise & 0xFF00) >> 8;

        int CyclesOff = (a1300VPB.reserved & 0xF0);
        // qDebug() << Q_FUNC_INFO << " INFO: HIGH NIBBLE of RESERVE: " << CyclesOff;
        int TimesToCycleMPP = (a1300VPB.reserved & 0x0F);
        // qDebug() << Q_FUNC_INFO << " INFO: LOW NIBBLE of RESERVE: " << TimesToCycleMPP;

        edProtections += comma + QString::number(Timer1) + comma + QString::number(Timer2) + comma +
                QString::number(a1300VPB.defCycles2SoftKick) + comma + QString::number(a1300VPB.defCycles2HardKick) + comma +
                QString::number(CyclesOff) + comma + QString::number(TimesToCycleMPP) + comma +
                QString::number(a1300VPB.tests & 0x01);

        // edProtections += comma + QString::number(Timer1) + comma + QString::number(Timer2) + comma +  QString::number(a1300VPB.defCycles2SoftKick) + comma + QString::number(a1300VPB.defCycles2HardKick);
    }

    //qDebug() << Q_FUNC_INFO << " protections being sent " << edProtections;
    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);
    //qDebug() << Q_FUNC_INFO << " protections sent " << edProtections;


    QString powerCntrl = QString::number(a1300VPB.vin_disable_radio) + comma + QString::number(a1300VPB.ov) + comma + QString::number(a1300VPB.oc) + comma +
            QString::number(a1300VPB.ov_startup) + comma + QString::number(a1300VPB.oc_step) + comma +
            QString::number(a1300VPB.cur_noise) + comma + QString::number(a1300VPB.ov_step) + comma +
            QString::number(a1300VPB.vin_limit) + comma + QString::number(a1300VPB.vin_turn_on) + comma +
            QString::number(a1300VPB.vin_switch_off) + comma + QString::number(a1300VPB.module) + comma + QString::number(a1300VPB.mpp);


   // qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), powerCntrl);

    // qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a1300VPB.t_mod_off) + comma + QString::number(a1300VPB.toff_fallback) + comma +
            QString::number(a1300VPB.ton_fallback) + comma + QString::number(a1300VPB.fallback_time) + comma +
            QString::number(a1300VPB.oc_protection);

   // qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    // qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a1300VPB.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a1300VPB.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a1300VPB.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a1300VPB.tkCurrent)) + comma +
            QString::number(static_cast<double>(a1300VPB.tkPower)) + comma +
            QString::number(a1300VPB.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a1300VPB.dFk[0])) + comma +
            QString::number(static_cast<double>(a1300VPB.dFk[1])) + comma +
            QString::number(static_cast<double>(a1300VPB.dFk[2])) + comma +
            QString::number(static_cast<double>(a1300VPB.dFk[3])) + comma +
            QString::number(a1300VPB.pureOffset) + comma +
            QString::number(a1300VPB.LowCurrentLimitTo255);

    //qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    //qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    //qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    //qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    //qDebug() << Q_FUNC_INFO << " suffix1:" << versionSuffix.at(0) << " suffix2:" << versionSuffix.at(1) << " suffix3:" << versionSuffix.at(2);

   //  qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);

    QString versionInfo = QString::number(a1300VPB.versionHigh) + comma + QString::number(a1300VPB.versionLow) + comma +
            QString::number(a1300VPB.utcHigh) + comma + QString::number(a1300VPB.utcLow) + comma +
            QString::number(a1300VPB.shunt) + comma + QString::number(a1300VPB.utcProgram) + comma + versionSuffixHexStr;
    //qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    //qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    /*
    QString protectionsInfo = versionSuffixHexStr + comma + QString::number(a1300VPB.fetFailureCount) + comma +
            QString::number(a1300VPB.fetCurrentThreshold) + comma + QString::number(a1300VPB.fetDeltaCurrent) + comma +
            QString::number(a1300VPB.VhvLimitVout) + comma + QString::number(a1300VPB.IhvLimitVout) + comma +
            QString::number(a1300VPB.VhvLimitVins) + comma + QString::number(a1300VPB.IhvLimitVins);


    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0), macFlashFamily.at(2), protectionsInfo);
*/


    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a1300VPB.synch_freq) + comma + QString::number(a1300VPB.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));



    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);
        // qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a1300_2ndVPB = a1300VPB;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        parameterBlocksStorage.insert(pbKey,pPB);

        if (m_saveParameterBlockInfo == true)
        {
            qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }



    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo1300V(QStringList & macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    ParameterBlock_1300V a1300VPB;
    bool ok = false;
    AmptGUI_X_Status rV = NO_ERROR;

    static const QString Version2nd_VersionSuffixRange_Str = "^1[F|G][' '|0|1-9]";
    static const QRegularExpression Version2nd_VersionSuffixRange_RE(Version2nd_VersionSuffixRange_Str);
    static QRegularExpressionMatch match;

    // qDebug() << Q_FUNC_INFO << " starting ...";

    QString temp = justTheData.mid(288,6);
    QString versionSuffix = temp;
    QString versionSuffixHexStr;

    BYTE *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a1300VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            //memcpy(static_cast<void *>(a600V_V2_2nd.versionSuffix), static_cast<void *>(versionSuffixHexStr), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }

    // qDebug() << Q_FUNC_INFO << " INFO: versionSuffixStr " << versionSuffixHexStr << " versionSuffix: " << versionSuffix;

    match = Version2nd_VersionSuffixRange_RE.match(versionSuffixHexStr);
    //if ((versionSuffixHexStr == "1F ") || (versionSuffixHexStr == "1G "))
    if (match.hasMatch())
    {
        return endDeviceParameterBlockInfo1300V_2nd(macFlashFamily,justTheData,Family1300V_2nd_Shunt);
    }

    temp = justTheData.mid(0,4);
    quint16 barrier = 0;
    hexStringToDecimalUnsignedInt(temp ,barrier, true );
    hexStringToDecimalUnsignedInt(temp,a1300VPB.barrier,true);

    temp = justTheData.mid(4,2);
    a1300VPB.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a1300VPB.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6)); // (BYTE *) malloc(6);
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.myMac, (void *)macAsHexString, 6 );
            memcpy( static_cast<void *>(a1300VPB.myMac), static_cast<void *>(macAsHexString), 6);
        }
    }
    // LBC COpy mac into PB

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a1300VPB.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a1300VPB.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a1300VPB.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a1300VPB.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a1300VPB.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy( static_cast<void *>(a1300VPB.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }


    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curIV, (void *)aesIVAsHexString, 16 );
            memcpy(static_cast<void *>(a1300VPB.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }

    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.fetFailureCount, true );

    temp = justTheData.mid(260,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.fetCurrentThreshold, true );

    temp = justTheData.mid(264,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.fetDeltaCurrent, true );

    temp = justTheData.mid(268,4);
    hexStringToDecimalSignedInt(temp ,a1300VPB.LowCurrentLimitTo255, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.VhvLimitVout, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.IhvLimitVout, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.VhvLimitVins, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalUnsignedInt(temp ,a1300VPB.IhvLimitVins, true );

    temp = justTheData.mid(288,6);
    versionSuffix = temp;

    versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a1300VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            //memcpy(static_cast<void *>(a1300VPB.versionSuffix), static_cast<void *>(versionSuffixHexStr), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }
    a1300VPB.versionSuffix[0] = static_cast<BYTE>(versionSuffixHexStr.at(0).toLatin1());
    a1300VPB.versionSuffix[1] = static_cast<BYTE>(versionSuffixHexStr.at(1).toLatin1());
    a1300VPB.versionSuffix[2] = static_cast<BYTE>(versionSuffixHexStr.at(2).toLatin1());

    qDebug() << Q_FUNC_INFO << " INFO: 1300V version " << a1300VPB.versionSuffix[0]
             <<a1300VPB.versionSuffix[1] << a1300VPB.versionSuffix[2] << "\n";

    QString test = justTheData.mid(294,2);
    a1300VPB.tests = static_cast<BYTE>(test.toInt());

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    // qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,2);
    a1300VPB.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(306,2);
    a1300VPB.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(308,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.syncword,true);

    temp = justTheData.mid(312,2);
    a1300VPB.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a1300VPB.rbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(316,2);
    a1300VPB.gbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(318,2);
    a1300VPB.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a1300VPB.reserved = static_cast<BYTE>(temp.toInt());

    temp = justTheData.mid(322,2);
    a1300VPB.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a1300VPB.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a1300VPB.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a1300VPB.channel = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a1300VPB.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a1300VPB.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a1300VPB.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a1300VPB.tkPower,true);

    temp = justTheData.mid(370,2);
    a1300VPB.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a1300VPB.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a1300VPB.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a1300VPB.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a1300VPB.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a1300VPB.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a1300VPB.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));;

    temp = justTheData.mid(384,2);
    a1300VPB.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a1300VPB.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<quint8>(temp.toInt(&ok,16));
    a1300VPB.boolByte1 = boolByte1;

    //qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a1300VPB.showState = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a1300VPB.CriticalLevel500);

    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a1300VPB.CriticalLevel10);

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a1300VPB.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.versionHigh,true);

    temp = justTheData.mid(436,2);
    a1300VPB.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<BYTE>(temp.toInt(&ok,16));
    a1300VPB.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a1300VPB.prepAddr,true);

    temp = justTheData.mid(444,2);
    a1300VPB.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a1300VPB.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a1300VPB.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a1300VPB.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a1300VPB.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a1300VPB.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a1300VPB.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a1300VPB.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a1300VPB.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a1300VPB.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a1300VPB.cur_noise,true);

    temp = justTheData.mid(468,2);
    a1300VPB.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a1300VPB.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a1300VPB.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a1300VPB.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a1300VPB.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a1300VPB.vin_switch_off = static_cast<BYTE>(temp.toInt(&ok,16));


    QString linearKs = QString::number(static_cast<double>(a1300VPB.linearK[0][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[1][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[2][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[3][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[4][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[5][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[6][0])) + comma +
            QString::number(static_cast<double>(a1300VPB.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a1300VPB.linearKs being sent: " << linearKs;

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0),macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a1300VPB.linearKs have been sent: " << linearKs;


    QString edComms = QString::number(a1300VPB.netId) + comma + QString::number(a1300VPB.myBunch) + comma +
            QString::number(a1300VPB.groupId) + comma + QString::number(a1300VPB.syncword) + comma +
            QString::number(a1300VPB.rbunch) + comma + QString::number(a1300VPB.gbunch) + comma +
            QString::number(a1300VPB.channel) + comma + QString::number(a1300VPB.radioPower) + comma +
            QString::number(a1300VPB.edAddr) + comma + QString::number(a1300VPB.gwAddr) + comma +
            QString::number(a1300VPB.repeaterChannel) + comma + QString::number(a1300VPB.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a1300VPB.starting500Channel) + comma +
            QString::number(a1300VPB.CriticalLevel10) + comma + QString::number(a1300VPB.CriticalLevel500) + comma +
            QString::number(a1300VPB.showState) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms;

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = versionSuffixHexStr + comma + QString::number(a1300VPB.fetFailureCount) + comma + QString::number(a1300VPB.fetCurrentThreshold) + comma +
            QString::number(a1300VPB.fetDeltaCurrent) + comma + QString::number(a1300VPB.LowCurrentLimitTo255) + comma +
            QString::number(a1300VPB.VhvLimitVout) + comma + QString::number(a1300VPB.IhvLimitVout) + comma +
            QString::number(a1300VPB.VhvLimitVins) + comma + QString::number(a1300VPB.IhvLimitVins);

    if (versionSuffixHexStr == "1_D")
    {
        int Timer1 = a1300VPB.cur_noise & 0x000F;
        int Timer2 = (a1300VPB.cur_noise & 0xFF00) >> 8;

        int CyclesOff = (a1300VPB.reserved & 0xF0);
        // qDebug() << Q_FUNC_INFO << " INFO: HIGH NIBBLE of RESERVE: " << CyclesOff;
        int TimesToCycleMPP = (a1300VPB.reserved & 0x0F);
        // qDebug() << Q_FUNC_INFO << " INFO: LOW NIBBLE of RESERVE: " << TimesToCycleMPP;

        edProtections += comma + QString::number(Timer1) + comma + QString::number(Timer2) + comma +
                QString::number(a1300VPB.defCycles2SoftKick) + comma + QString::number(a1300VPB.defCycles2HardKick) + comma +
                QString::number(CyclesOff) + comma + QString::number(TimesToCycleMPP) + comma +
                QString::number(a1300VPB.tests & 0x01);

        // edProtections += comma + QString::number(Timer1) + comma + QString::number(Timer2) + comma +  QString::number(a1300VPB.defCycles2SoftKick) + comma + QString::number(a1300VPB.defCycles2HardKick);
    }

    //qDebug() << Q_FUNC_INFO << " protections being sent " << edProtections;
    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);
    //qDebug() << Q_FUNC_INFO << " protections sent " << edProtections;


    QString powerCntrl = QString::number(a1300VPB.vin_disable_radio) + comma + QString::number(a1300VPB.ov) + comma + QString::number(a1300VPB.oc) + comma +
            QString::number(a1300VPB.ov_startup) + comma + QString::number(a1300VPB.oc_step) + comma +
            QString::number(a1300VPB.cur_noise) + comma + QString::number(a1300VPB.ov_step) + comma +
            QString::number(a1300VPB.vin_limit) + comma + QString::number(a1300VPB.vin_turn_on) + comma +
            QString::number(a1300VPB.vin_switch_off) + comma + QString::number(a1300VPB.module) + comma + QString::number(a1300VPB.mpp);


   // qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), powerCntrl);

    // qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a1300VPB.t_mod_off) + comma + QString::number(a1300VPB.toff_fallback) + comma +
            QString::number(a1300VPB.ton_fallback) + comma + QString::number(a1300VPB.fallback_time) + comma +
            QString::number(a1300VPB.oc_protection);

   // qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    // qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a1300VPB.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a1300VPB.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a1300VPB.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a1300VPB.tkCurrent)) + comma +
            QString::number(static_cast<double>(a1300VPB.tkPower)) + comma +
            QString::number(a1300VPB.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a1300VPB.dFk[0])) + comma +
            QString::number(static_cast<double>(a1300VPB.dFk[1])) + comma +
            QString::number(static_cast<double>(a1300VPB.dFk[2])) + comma +
            QString::number(static_cast<double>(a1300VPB.dFk[3])) + comma +
            QString::number(a1300VPB.pureOffset) + comma +
            QString::number(a1300VPB.LowCurrentLimitTo255);

    //qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    //qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    //qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    //qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    //qDebug() << Q_FUNC_INFO << " suffix1:" << versionSuffix.at(0) << " suffix2:" << versionSuffix.at(1) << " suffix3:" << versionSuffix.at(2);

   //  qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);

    QString versionInfo = QString::number(a1300VPB.versionHigh) + comma + QString::number(a1300VPB.versionLow) + comma +
            QString::number(a1300VPB.utcHigh) + comma + QString::number(a1300VPB.utcLow) + comma +
            QString::number(a1300VPB.shunt) + comma + QString::number(a1300VPB.utcProgram) + comma + versionSuffixHexStr;
    //qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    //qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    /*
    QString protectionsInfo = versionSuffixHexStr + comma + QString::number(a1300VPB.fetFailureCount) + comma +
            QString::number(a1300VPB.fetCurrentThreshold) + comma + QString::number(a1300VPB.fetDeltaCurrent) + comma +
            QString::number(a1300VPB.VhvLimitVout) + comma + QString::number(a1300VPB.IhvLimitVout) + comma +
            QString::number(a1300VPB.VhvLimitVins) + comma + QString::number(a1300VPB.IhvLimitVins);


    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0), macFlashFamily.at(2), protectionsInfo);
*/


    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a1300VPB.synch_freq) + comma + QString::number(a1300VPB.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));



    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);
        // qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a1300VPB = a1300VPB;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        parameterBlocksStorage.insert(pbKey,pPB);

        if (m_saveParameterBlockInfo == true)
        {
            qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo1500V_2nd(QStringList &macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;
    AmptGUI_X_Status rV = NO_ERROR;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    qDebug() << Q_FUNC_INFO << " INFO: 1500V_2nd tShunt " << QString::number(tShunt);

    ParameterBlock_1500V_2nd a1500VPB;
    QString temp = justTheData.mid(288,6);
    QString versionSuffix = temp;
    QString versionSuffixHexStr;

    BYTE *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a1500VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }

    qDebug() << Q_FUNC_INFO << " INFO: versionSuffixStr " << versionSuffixHexStr << " versionSuffix: " << versionSuffix;



    bool ok = false;

    temp = justTheData.mid(0,4);

    hexStringToDecimalUnsignedInt(temp,a1500VPB.barrier,true);

    temp = justTheData.mid(4,2);
    a1500VPB.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a1500VPB.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6)); // (BYTE *) malloc(6);
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            // memcpy( (void *)a1500VPB.myMac, (void *)macAsHexString, 6 );
            memcpy(static_cast<void *>(a1500VPB.myMac), static_cast<void *>(macAsHexString), 6);
        }
    }

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a1500VPB.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a1500VPB.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a1500VPB.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy( static_cast<void *>(a1500VPB.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }

    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curIV, (void *)aesIVAsHexString, 16 );
            memcpy(static_cast<void *>(a1500VPB.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }

    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.ef_InputCurrentThreshold, true );

    temp = justTheData.mid(260,2);
    a1500VPB.ef_OccurrenceThreshold = static_cast<BYTE>(temp.toInt(&ok, 16));

    qDebug() << Q_FUNC_INFO << " INFO: ef_OccurrenceThreshold " << QString::number(a1500VPB.ef_OccurrenceThreshold);

    temp = justTheData.mid(262,2);
    a1500VPB.ef_CountDownTimer = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(264,2);
    a1500VPB.ef_AlphaNumerator = static_cast<BYTE>(temp.toInt(&ok,16));

    qDebug() << Q_FUNC_INFO << " INFO: ef_AlphaNumerator " << QString::number(a1500VPB.ef_AlphaNumerator);


    temp = justTheData.mid(266,2);
    a1500VPB.ef_ModuleOff = static_cast<BYTE>(temp.toInt(&ok,16));

    qDebug() << Q_FUNC_INFO << " INFO: ef_ModuleOff " << QString::number(a1500VPB.ef_ModuleOff);

    temp = justTheData.mid(268,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.LowCurrentLimitTo255, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.VoutLimitCount, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalUnsignedInt(temp ,a1500VPB.VoutLimit, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.IoutLimitCount, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.IoutLimit, true );


    temp = justTheData.mid(288,6);

    /*
    *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3));
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            // memcpy( (void *)a1500VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            memcpy(static_cast<void *>(a1500VPB.versionSuffix), static_cast<void *>(a1500VPB.versionSuffix), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }
    */

    a1500VPB.versionSuffix[0] = static_cast<BYTE>(versionSuffixHexStr.at(0).toLatin1());
    a1500VPB.versionSuffix[1] = static_cast<BYTE>(versionSuffixHexStr.at(1).toLatin1());
    a1500VPB.versionSuffix[2] = static_cast<BYTE>(versionSuffixHexStr.at(2).toLatin1());

    qDebug() << Q_FUNC_INFO << " INFO: 1500V_2nd version " << a1500VPB.versionSuffix[0]
             <<a1500VPB.versionSuffix[1] << a1500VPB.versionSuffix[2] << "\n";

    QString test = justTheData.mid(294,2);
    a1500VPB.monitoring = static_cast<BYTE>(test.toInt());

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    // qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,2);
    a1500VPB.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));
    temp = justTheData.mid(306,2);
    a1500VPB.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(308,4);
    a1500VPB.syncword = 0;
    hexStringToDecimalUnsignedInt(temp,a1500VPB.syncword,true);

    temp = justTheData.mid(312,2);
    a1500VPB.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a1500VPB.rbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(316,2);
    a1500VPB.gbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(318,2);
    a1500VPB.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a1500VPB.reserved = static_cast<BYTE>(temp.toInt());

    temp = justTheData.mid(322,2);
    a1500VPB.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a1500VPB.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a1500VPB.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a1500VPB.channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a1500VPB.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a1500VPB.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a1500VPB.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a1500VPB.tkPower,true);

    temp = justTheData.mid(370,2);
    a1500VPB.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a1500VPB.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a1500VPB.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a1500VPB.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a1500VPB.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a1500VPB.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a1500VPB.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(384,2);
    a1500VPB.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a1500VPB.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<quint8>(temp.toInt(&ok,16));
    a1500VPB.boolByte1 = boolByte1;

    // qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a1500VPB.showState = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a1500VPB.CriticalLevel500);
    // qDebug() << Q_FUNC_INFO << " CriticalLevel500 value from Hex byte: " << a1500VPB.CriticalLevel500;


    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a1500VPB.CriticalLevel10);
    // qDebug() << Q_FUNC_INFO << " CriticalLevel10 value from Hex byte: " << a1500VPB.CriticalLevel10;

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a1500VPB.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.versionHigh,true);

    temp = justTheData.mid(436,2);
    a1500VPB.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<quint8>(temp.toInt(&ok,16));
    a1500VPB.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.prepAddr,true);

    temp = justTheData.mid(444,2);
    a1500VPB.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a1500VPB.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a1500VPB.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a1500VPB.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a1500VPB.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a1500VPB.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a1500VPB.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a1500VPB.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a1500VPB.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a1500VPB.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a1500VPB.cur_noise,true);

    temp = justTheData.mid(468,2);
    a1500VPB.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a1500VPB.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a1500VPB.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a1500VPB.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a1500VPB.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a1500VPB.vin_switch_off = static_cast<BYTE>(temp.toInt(&ok,16));


    QString linearKs = QString::number(static_cast<double>(a1500VPB.linearK[0][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[1][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[2][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[3][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[4][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[5][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[6][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a1500VPB.linearKs being sent: " << linearKs;

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0),macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a1500VPB.linearKs have been sent: " << linearKs;


    QString edComms = QString::number(a1500VPB.netId) + comma + QString::number(a1500VPB.myBunch) + comma +
            QString::number(a1500VPB.groupId) + comma + QString::number(a1500VPB.syncword) + comma +
            QString::number(a1500VPB.rbunch) + comma + QString::number(a1500VPB.gbunch) + comma +
            QString::number(a1500VPB.channel) + comma + QString::number(a1500VPB.radioPower) + comma +
            QString::number(a1500VPB.edAddr) + comma + QString::number(a1500VPB.gwAddr) + comma +
            QString::number(a1500VPB.repeaterChannel) + comma + QString::number(a1500VPB.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a1500VPB.starting500Channel) + comma +
            QString::number(a1500VPB.CriticalLevel10) + comma + QString::number(a1500VPB.CriticalLevel500) + comma +
            QString::number(a1500VPB.showState) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms << " channel: "  << QString::number(a1500VPB.channel);

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = QString::number(a1500VPB.VoutLimitCount) + comma + QString::number(a1500VPB.VoutLimit) + comma +
            QString::number(a1500VPB.IoutLimitCount) + comma + QString::number(a1500VPB.IoutLimit) + comma +
            QString::number(a1500VPB.ef_InputCurrentThreshold) + comma + QString::number(a1500VPB.ef_OccurrenceThreshold) + comma +
            QString::number(a1500VPB.ef_CountDownTimer) + comma +
            QString::number(a1500VPB.ef_AlphaNumerator) + comma + QString::number(a1500VPB.ef_ModuleOff) + comma +
            QString::number(a1500VPB.monitoring);

    qDebug() << Q_FUNC_INFO << " INFO: 1500V protections being sent ..." << edProtections;

    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);
    qDebug() << Q_FUNC_INFO << " INFO: 1500V protections have been sent ..." << edProtections;


    QString cntrlVolts = QString::number(a1500VPB.vin_disable_radio) + comma + QString::number(a1500VPB.ov) + comma + QString::number(a1500VPB.oc) + comma +
            QString::number(a1500VPB.ov_startup) + comma + QString::number(a1500VPB.oc_step) + comma +
            QString::number(a1500VPB.cur_noise) + comma + QString::number(a1500VPB.ov_step) + comma +
            QString::number(a1500VPB.vin_limit) + comma + QString::number(a1500VPB.vin_turn_on) + comma +
            QString::number(a1500VPB.vin_switch_off) + comma + QString::number(a1500VPB.module) + comma + QString::number(a1500VPB.mpp);


   // qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), cntrlVolts);

    // qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a1500VPB.t_mod_off) + comma + QString::number(a1500VPB.toff_fallback) + comma +
            QString::number(a1500VPB.ton_fallback) + comma + QString::number(a1500VPB.fallback_time) + comma +
            QString::number(a1500VPB.oc_protection);

   // qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    // qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a1500VPB.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a1500VPB.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a1500VPB.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a1500VPB.tkCurrent)) + comma +
            QString::number(static_cast<double>(a1500VPB.tkPower)) + comma +
            QString::number(a1500VPB.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a1500VPB.dFk[0])) + comma +
            QString::number(static_cast<double>(a1500VPB.dFk[1])) + comma +
            QString::number(static_cast<double>(a1500VPB.dFk[2])) + comma +
            QString::number(static_cast<double>(a1500VPB.dFk[3])) + comma +
            QString::number(a1500VPB.pureOffset)+ comma +
            QString::number(a1500VPB.LowCurrentLimitTo255);


    //qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    //qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    //qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    //qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    // qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);

    // qDebug() << Q_FUNC_INFO << " versionSuffixHexStr:" << versionSuffixHexStr;

    QString versionInfo = QString::number(a1500VPB.versionHigh) + comma + QString::number(a1500VPB.versionLow) + comma +
            QString::number(a1500VPB.utcHigh) + comma + QString::number(a1500VPB.utcLow) + comma +
            QString::number(a1500VPB.shunt) + comma + QString::number(a1500VPB.utcProgram) + comma + versionSuffixHexStr;
    // qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    // qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a1500VPB.synch_freq) + comma + QString::number(a1500VPB.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));



    // Convert Data into a 240 byte character array
    // Then based on family, store into MAP<string, struct *>

    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);
        // qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a1500_2ndVPB = a1500VPB;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        parameterBlocksStorage.insert(pbKey,pPB);

        if (m_saveParameterBlockInfo == true)
        {
            qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo1500V(QStringList & macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;
    AmptGUI_X_Status rV = NO_ERROR;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    qDebug() << Q_FUNC_INFO << CurrentDateTime << " INFO: entering ...";

    ParameterBlock_1500V a1500VPB;
    bool ok = false;

    static const QString Version2nd_VersionSuffixRange_Str = "^1BG";
    static const QRegularExpression Version2nd_VersionSuffixRange_RE(Version2nd_VersionSuffixRange_Str);
    static const QString Version2nd_VersionSuffixRange2_Str = "^1BH";
    static const QRegularExpression Version2nd_VersionSuffixRange2_RE(Version2nd_VersionSuffixRange2_Str);
    static const QString Version2nd_VersionSuffixRange3_Str = "^1BJ";
    static const QRegularExpression Version2nd_VersionSuffixRange3_RE(Version2nd_VersionSuffixRange3_Str);
    static QRegularExpressionMatch match;
    static QRegularExpressionMatch match2;
    static QRegularExpressionMatch match3;

    qDebug() << Q_FUNC_INFO << " starting ...";

    QString temp = justTheData.mid(288,6);
    QString versionSuffix = temp;
    QString versionSuffixHexStr;

    BYTE *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3)); // (BYTE *) malloc(3);
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            memcpy( (void *)a1500VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }

    qDebug() << Q_FUNC_INFO << " INFO: versionSuffixStr " << versionSuffixHexStr << " versionSuffix: " << versionSuffix;

    match = Version2nd_VersionSuffixRange_RE.match(versionSuffixHexStr);
    match2 = Version2nd_VersionSuffixRange2_RE.match(versionSuffixHexStr);
    match3 = Version2nd_VersionSuffixRange3_RE.match(versionSuffixHexStr);


    if ((match.hasMatch()) || (match2.hasMatch()) || match3.hasMatch())
    {

        return endDeviceParameterBlockInfo1500V_2nd(macFlashFamily,justTheData,Family1500V_2nd_Shunt);
    }
    qDebug() << Q_FUNC_INFO << " INFO: Regular 1500V versionSuffixStr " << versionSuffixHexStr << " versionSuffix: " << versionSuffix;


    temp = justTheData.mid(0,4);

    hexStringToDecimalUnsignedInt(temp,a1500VPB.barrier,true);

    temp = justTheData.mid(4,2);
    a1500VPB.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a1500VPB.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6)); // (BYTE *) malloc(6);
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            // memcpy( (void *)a1500VPB.myMac, (void *)macAsHexString, 6 );
            memcpy(static_cast<void *>(a1500VPB.myMac), static_cast<void *>(macAsHexString), 6);
        }
    }

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a1500VPB.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a1500VPB.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a1500VPB.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a1500VPB.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a1500VPB.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy( static_cast<void *>(a1500VPB.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }




    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curIV, (void *)aesIVAsHexString, 16 );
            memcpy(static_cast<void *>(a1500VPB.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }


    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.fetFailureCount, true );

    temp = justTheData.mid(260,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.fetCurrentThreshold, true );

    temp = justTheData.mid(264,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.fetDeltaCurrent, true );

    temp = justTheData.mid(268,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.LowCurrentLimitTo255, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.VoutLimitCount, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalUnsignedInt(temp ,a1500VPB.VoutLimit, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.IoutLimitCount, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalSignedInt(temp ,a1500VPB.IoutLimit, true );


    temp = justTheData.mid(288,6);

    /*
    *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3));
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            // memcpy( (void *)a1500VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            memcpy(static_cast<void *>(a1500VPB.versionSuffix), static_cast<void *>(a1500VPB.versionSuffix), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }
    */

    a1500VPB.versionSuffix[0] = static_cast<BYTE>(versionSuffixHexStr.at(0).toLatin1());
    a1500VPB.versionSuffix[1] = static_cast<BYTE>(versionSuffixHexStr.at(1).toLatin1());
    a1500VPB.versionSuffix[2] = static_cast<BYTE>(versionSuffixHexStr.at(2).toLatin1());

    qDebug() << Q_FUNC_INFO << " INFO: 1500V version " << a1500VPB.versionSuffix[0]
             <<a1500VPB.versionSuffix[1] << a1500VPB.versionSuffix[2] << "\n";

    QString test = justTheData.mid(294,2);
    a1500VPB.tests = static_cast<BYTE>(test.toInt());

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    // qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,2);
    a1500VPB.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));
    temp = justTheData.mid(306,2);
    a1500VPB.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(308,4);
    a1500VPB.syncword = 0;
    hexStringToDecimalUnsignedInt(temp,a1500VPB.syncword,true);

    temp = justTheData.mid(312,2);
    a1500VPB.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a1500VPB.rbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(316,2);
    a1500VPB.gbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(318,2);
    a1500VPB.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a1500VPB.reserved = static_cast<BYTE>(temp.toInt());

    temp = justTheData.mid(322,2);
    a1500VPB.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a1500VPB.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a1500VPB.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a1500VPB.channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a1500VPB.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a1500VPB.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a1500VPB.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a1500VPB.tkPower,true);

    temp = justTheData.mid(370,2);
    a1500VPB.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a1500VPB.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a1500VPB.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a1500VPB.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a1500VPB.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a1500VPB.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a1500VPB.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(384,2);
    a1500VPB.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a1500VPB.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<quint8>(temp.toInt(&ok,16));
    a1500VPB.boolByte1 = boolByte1;

    // qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a1500VPB.showState = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a1500VPB.CriticalLevel500);
    // qDebug() << Q_FUNC_INFO << " CriticalLevel500 value from Hex byte: " << a1500VPB.CriticalLevel500;


    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a1500VPB.CriticalLevel10);
    // qDebug() << Q_FUNC_INFO << " CriticalLevel10 value from Hex byte: " << a1500VPB.CriticalLevel10;

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a1500VPB.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.versionHigh,true);

    temp = justTheData.mid(436,2);
    a1500VPB.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<quint8>(temp.toInt(&ok,16));
    a1500VPB.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a1500VPB.prepAddr,true);

    temp = justTheData.mid(444,2);
    a1500VPB.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a1500VPB.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a1500VPB.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a1500VPB.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a1500VPB.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a1500VPB.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a1500VPB.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a1500VPB.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a1500VPB.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a1500VPB.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a1500VPB.cur_noise,true);

    temp = justTheData.mid(468,2);
    a1500VPB.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a1500VPB.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a1500VPB.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a1500VPB.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a1500VPB.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a1500VPB.vin_switch_off = static_cast<BYTE>(temp.toInt(&ok,16));


    QString linearKs = QString::number(static_cast<double>(a1500VPB.linearK[0][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[1][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[2][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[3][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[4][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[5][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[6][0])) + comma +
            QString::number(static_cast<double>(a1500VPB.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a1500VPB.linearKs being sent: " << linearKs;

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0),macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a1500VPB.linearKs have been sent: " << linearKs;


    QString edComms = QString::number(a1500VPB.netId) + comma + QString::number(a1500VPB.myBunch) + comma +
            QString::number(a1500VPB.groupId) + comma + QString::number(a1500VPB.syncword) + comma +
            QString::number(a1500VPB.rbunch) + comma + QString::number(a1500VPB.gbunch) + comma +
            QString::number(a1500VPB.channel) + comma + QString::number(a1500VPB.radioPower) + comma +
            QString::number(a1500VPB.edAddr) + comma + QString::number(a1500VPB.gwAddr) + comma +
            QString::number(a1500VPB.repeaterChannel) + comma + QString::number(a1500VPB.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a1500VPB.starting500Channel) + comma +
            QString::number(a1500VPB.CriticalLevel10) + comma + QString::number(a1500VPB.CriticalLevel500) + comma +
            QString::number(a1500VPB.showState) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms << " channel: "  << QString::number(a1500VPB.channel);

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = QString::number(a1500VPB.VoutLimitCount) + comma + QString::number(a1500VPB.VoutLimit) + comma +
            QString::number(a1500VPB.IoutLimitCount) + comma + QString::number(a1500VPB.IoutLimit);

    // qDebug() << Q_FUNC_INFO << " 1500V protections being sent ..." << edProtections;

    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);
    // qDebug() << Q_FUNC_INFO << " 1500V protections have been sent ..." << edProtections;




    QString cntrlVolts = QString::number(a1500VPB.vin_disable_radio) + comma + QString::number(a1500VPB.ov) + comma + QString::number(a1500VPB.oc) + comma +
            QString::number(a1500VPB.ov_startup) + comma + QString::number(a1500VPB.oc_step) + comma +
            QString::number(a1500VPB.cur_noise) + comma + QString::number(a1500VPB.ov_step) + comma +
            QString::number(a1500VPB.vin_limit) + comma + QString::number(a1500VPB.vin_turn_on) + comma +
            QString::number(a1500VPB.vin_switch_off) + comma + QString::number(a1500VPB.module) + comma + QString::number(a1500VPB.mpp);


   // qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), cntrlVolts);

    // qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a1500VPB.t_mod_off) + comma + QString::number(a1500VPB.toff_fallback) + comma +
            QString::number(a1500VPB.ton_fallback) + comma + QString::number(a1500VPB.fallback_time) + comma +
            QString::number(a1500VPB.oc_protection);

   // qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    // qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a1500VPB.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a1500VPB.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a1500VPB.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a1500VPB.tkCurrent)) + comma +
            QString::number(static_cast<double>(a1500VPB.tkPower)) + comma +
            QString::number(a1500VPB.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a1500VPB.dFk[0])) + comma +
            QString::number(static_cast<double>(a1500VPB.dFk[1])) + comma +
            QString::number(static_cast<double>(a1500VPB.dFk[2])) + comma +
            QString::number(static_cast<double>(a1500VPB.dFk[3])) + comma +
            QString::number(a1500VPB.pureOffset)+ comma +
            QString::number(a1500VPB.LowCurrentLimitTo255);


    //qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    //qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    //qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    //qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    // qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);

    // qDebug() << Q_FUNC_INFO << " versionSuffixHexStr:" << versionSuffixHexStr;

    QString versionInfo = QString::number(a1500VPB.versionHigh) + comma + QString::number(a1500VPB.versionLow) + comma +
            QString::number(a1500VPB.utcHigh) + comma + QString::number(a1500VPB.utcLow) + comma +
            QString::number(a1500VPB.shunt) + comma + QString::number(a1500VPB.utcProgram) + comma + versionSuffixHexStr;
    // qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    // qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a1500VPB.synch_freq) + comma + QString::number(a1500VPB.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));



    // Convert Data into a 240 byte character array
    // Then based on family, store into MAP<string, struct *>

    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);
        // qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a1500VPB = a1500VPB;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        parameterBlocksStorage.insert(pbKey,pPB);

        if (m_saveParameterBlockInfo == true)
        {
            qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceParameterBlockInfo1500V_30(QStringList & macFlashFamily, QString & justTheData, const int tShunt)
{
    bool retValue = true;
    AmptGUI_X_Status rV = NO_ERROR;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    ParameterBlock_1500V_30 a1500_30VPB;
    bool ok = false;

    QString temp = justTheData.mid(0,4);

    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.barrier,true);

    temp = justTheData.mid(4,2);
    a1500_30VPB.netId = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(6,2);
    a1500_30VPB.myBunch = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(8,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.groupId, true);

    QString myMac((justTheData.mid(12,12)).toUpper());
    BYTE *macAsHexString = static_cast<BYTE *>(malloc(6)); // (BYTE *) malloc(6);
    if ((rV = macQStringTo6ByteHexString(myMac,macAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create MAC Hex string for MAC:" + myMac + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (macAsHexString != nullptr)
        {
            // memcpy( (void *)a1500_30VPB.myMac, (void *)macAsHexString, 6 );
            memcpy(static_cast<void *>(a1500_30VPB.myMac), static_cast<void *>(macAsHexString), 6);
        }
    }

    temp = justTheData.mid(24,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.dFk[0],true);

    temp = justTheData.mid(32,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.dFk[1],true);

    temp = justTheData.mid(40,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.dFk[2],true);

    temp = justTheData.mid(48,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.dFk[3],true);

    temp = justTheData.mid(56,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.vrefPolynom[0],true);

    temp = justTheData.mid(64,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.vrefPolynom[1],true);

    temp = justTheData.mid(72,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.vrefPolynom[2],true);

    temp = justTheData.mid(80,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[0][0],true);

    temp = justTheData.mid(88,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[0][1],true);

    temp = justTheData.mid(96,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[1][0],true);

    temp = justTheData.mid(104,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[1][1],true);

    temp = justTheData.mid(112,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[2][0],true);

    temp = justTheData.mid(120,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[2][1],true);

    temp = justTheData.mid(128,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[3][0],true);

    temp = justTheData.mid(136,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[3][1],true);

    temp = justTheData.mid(144,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[4][0],true);

    temp = justTheData.mid(152,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[4][1],true);

    temp = justTheData.mid(160,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[5][0],true);

    temp = justTheData.mid(168,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[5][1],true);

    temp = justTheData.mid(176,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[6][0],true);

    temp = justTheData.mid(184,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.linearK[6][1],true);

    QString AESKey = justTheData.mid(192,32);
    QString AESKeyHexStr;
    BYTE *aesKeyAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESKey,aesKeyAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes Key String for " + AESKey + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesKeyAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curKey, (void *)aesKeyAsHexString, 16 );
            memcpy( static_cast<void *>(a1500_30VPB.curKey), static_cast<void *>(aesKeyAsHexString), 16);
            AESKeyHexStr = QString::fromUtf8((char *)aesKeyAsHexString,16);
        }
    }




    QString AESIV  = justTheData.mid(224,32);
    QString AESIVHexStr;
    BYTE *aesIVAsHexString = static_cast<BYTE *>(malloc(16)); // (BYTE *)malloc(16);

    if ((rV = aesStrQStringTo16ByteHexString(AESIV,aesIVAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create aes IV String for " + AESIV + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (aesIVAsHexString != nullptr)
        {
            // memcpy( (void *)a1300VPB.curIV, (void *)aesIVAsHexString, 16 );
            memcpy(static_cast<void *>(a1500_30VPB.curIV), static_cast<void *>(aesIVAsHexString), 16);
            AESIVHexStr = QString::fromUtf8((char *)aesIVAsHexString,16);
        }
    }


    temp = justTheData.mid(256,4);
    hexStringToDecimalSignedInt(temp ,a1500_30VPB.fetFailureCount, true );

    temp = justTheData.mid(260,4);
    hexStringToDecimalSignedInt(temp ,a1500_30VPB.fetCurrentThreshold, true );

    temp = justTheData.mid(264,4);
    hexStringToDecimalSignedInt(temp ,a1500_30VPB.fetDeltaCurrent, true );

    temp = justTheData.mid(268,4);
    hexStringToDecimalSignedInt(temp ,a1500_30VPB.LowCurrentLimitTo255, true );

    temp = justTheData.mid(272,4);
    hexStringToDecimalSignedInt(temp ,a1500_30VPB.VoutLimitCount, true );

    temp = justTheData.mid(276,4);
    hexStringToDecimalUnsignedInt(temp ,a1500_30VPB.VoutLimit, true );

    temp = justTheData.mid(280,4);
    hexStringToDecimalSignedInt(temp ,a1500_30VPB.IoutLimitCount, true );

    temp = justTheData.mid(284,4);
    hexStringToDecimalSignedInt(temp ,a1500_30VPB.IoutLimit, true );


    temp = justTheData.mid(288,6);
    QString versionSuffix = temp;
    QString versionSuffixHexStr;

    BYTE *versionSuffixAsHexString = static_cast<BYTE *>(malloc(3));
    if ((rV = versionSuffixQStringTo3ByteHexString(versionSuffix,versionSuffixAsHexString)) != NO_ERROR)
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " Failed to create VERSION Hex string for :" + versionSuffix + " error code(" + QString::number(rV) + ")";
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    else
    {
        if (versionSuffixAsHexString != nullptr)
        {
            // memcpy( (void *)a1500_30VPB.versionSuffix, (void *)versionSuffixAsHexString, 3 );
            memcpy(static_cast<void *>(a1500_30VPB.versionSuffix), static_cast<void *>(a1500_30VPB.versionSuffix), 3);
            versionSuffixHexStr = QString::fromUtf8((char *)versionSuffixAsHexString,3);
        }
    }
    a1500_30VPB.versionSuffix[0] = static_cast<BYTE>(versionSuffixHexStr.at(0).toLatin1());
    a1500_30VPB.versionSuffix[1] = static_cast<BYTE>(versionSuffixHexStr.at(1).toLatin1());
    a1500_30VPB.versionSuffix[2] = static_cast<BYTE>(versionSuffixHexStr.at(2).toLatin1());

    qDebug() << Q_FUNC_INFO << " INFO: 1500V version " << a1500_30VPB.versionSuffix[0]
             <<a1500_30VPB.versionSuffix[1] << a1500_30VPB.versionSuffix[2] << "\n";

    QString test = justTheData.mid(294,2);
    a1500_30VPB.monitoring = static_cast<BYTE>(test.toInt());

    temp = justTheData.mid(296,8);
    qint32 InstallDate = 0;
    hexStringToDecimalSignedLong(temp,InstallDate,true);

    qDebug() << Q_FUNC_INFO << " time_t install date " << InstallDate;

    QDateTime qDTime(QDateTime::fromTime_t(static_cast<quint32>(InstallDate)));
    QString qTime = qDTime.toString(formatIt);

    temp = justTheData.mid(304,4);
    hexStringToDecimalSignedInt(temp, a1500_30VPB.IinLimit, true);
    /*
    a1500_30VPB.k_ov_volt = static_cast<BYTE>(temp.toInt(&ok,16));
    temp = justTheData.mid(306,2);
    a1500_30VPB.k_oc_cur = static_cast<BYTE>(temp.toInt(&ok,16));
   */
    temp = justTheData.mid(308,4);
    a1500_30VPB.syncword = 0;
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.syncword,true);

    temp = justTheData.mid(312,2);
    a1500_30VPB.vin_disable_radio =  static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(314,2);
    a1500_30VPB.rbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(316,2);
    a1500_30VPB.gbunch = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(318,2);
    a1500_30VPB.shortCircuitLevel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(320,2);
    a1500_30VPB.reserved = static_cast<BYTE>(temp.toInt());

    temp = justTheData.mid(322,2);
    a1500_30VPB.synch_phase = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(324,2);
    a1500_30VPB.synch_freq = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(326,2);
    a1500_30VPB.bandwidth250 = static_cast<BYTE>(temp.toInt(&ok));

    temp = justTheData.mid(328,2);
    a1500_30VPB.channel = static_cast<BYTE>(temp.toInt(&ok, 16));

    temp = justTheData.mid(330,8);
    qint32 utcProgram = 0;
    hexStringToDecimalSignedLong(temp,utcProgram,true);
    QDateTime qDTUTCTime(QDateTime::fromTime_t(static_cast<quint32>(utcProgram)));
    QString qUTCTime = qDTUTCTime.toString(formatIt);

    temp = justTheData.mid(338,8);
    hexStringToDecimalUnsignedLong(temp,a1500_30VPB.utcLow,true);

    temp = justTheData.mid(346,8);
    hexStringToDecimalUnsignedLong(temp,a1500_30VPB.utcHigh,true);

    temp = justTheData.mid(354,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.tkCurrent,true);

    temp = justTheData.mid(362,8);
    fourByteHexStringToFloat(temp,a1500_30VPB.tkPower,true);

    temp = justTheData.mid(370,2);
    a1500_30VPB.mpp = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(372,2);
    a1500_30VPB.module = static_cast<BOOL>(temp.toInt());

    temp = justTheData.mid(374,2);
    a1500_30VPB.ov = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(376,2);
    a1500_30VPB.oc = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(378,2);
    a1500_30VPB.radioPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(380,2);
    a1500_30VPB.edAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(382,2);
    a1500_30VPB.gwAddr = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(384,2);
    a1500_30VPB.repeaterChannel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(386,2);
    a1500_30VPB.repeaterPower = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(388,2);
    quint8 boolByte1 = static_cast<quint8>(temp.toInt(&ok,16));
    a1500_30VPB.boolByte1 = boolByte1;

    // qDebug() << Q_FUNC_INFO << " boolByte1:" << boolByte1;

    temp = justTheData.mid(390,2);
    a1500_30VPB.IinOCStepsAndDelay = static_cast<BYTE>(temp.toInt(&ok,16));
    qDebug() << Q_FUNC_INFO << " IinOCStepsAndDelay: " << a1500_30VPB.IinOCStepsAndDelay << " XXXXXXXXXXXXXX";

    temp = justTheData.mid(392,2);
    hexStringToDecimalSignedByte(temp,a1500_30VPB.CriticalLevel500);
    // qDebug() << Q_FUNC_INFO << " CriticalLevel500 value from Hex byte: " << a1500_30VPB.CriticalLevel500;


    temp = justTheData.mid(394,2);
    hexStringToDecimalSignedByte(temp, a1500_30VPB.CriticalLevel10);
    // qDebug() << Q_FUNC_INFO << " CriticalLevel10 value from Hex byte: " << a1500_30VPB.CriticalLevel10;

    temp = justTheData.mid(396,4);
    hexStringToDecimalSignedInt(temp,a1500_30VPB.pureOffset,true);

    temp = justTheData.mid(400,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.defCyclesTo500,true);

    temp = justTheData.mid(404,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.defCyclesTo10,true);

    temp = justTheData.mid(408,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.defCyclesToStep500Channel,true);

    temp = justTheData.mid(412,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.defCyclesToStep10Channel,true);

    temp = justTheData.mid(416,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.defCycles2SoftKick,true);

    temp = justTheData.mid(420,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.defCycles2HardKick,true);

    temp = justTheData.mid(424,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.imageAddr,true);

    temp = justTheData.mid(428,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.versionLow,true);

    temp = justTheData.mid(432,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.versionHigh,true);

    temp = justTheData.mid(436,2);
    a1500_30VPB.starting500Channel = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(438,2);
    quint8 boolByte2 = static_cast<quint8>(temp.toInt(&ok,16));
    a1500_30VPB.boolByte2 = boolByte2;

    // qDebug() << Q_FUNC_INFO << " boolByte2:" << boolByte2;

    temp = justTheData.mid(440,4);
    hexStringToDecimalUnsignedInt(temp,a1500_30VPB.prepAddr,true);

    temp = justTheData.mid(444,2);
    a1500_30VPB.repStep = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(446,2);
    a1500_30VPB.ov_startup = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(448,2);
    a1500_30VPB.t_mod_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(450,2);
    a1500_30VPB.toff_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(452,2);
    a1500_30VPB.ton_fallback = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(454,2);
    a1500_30VPB.fallback_time = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(456,2);
    a1500_30VPB.network_cnst_1 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(458,2);
    a1500_30VPB.network_cnst_2 = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(460,2);
    a1500_30VPB.oc_protection = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(462,2);
    a1500_30VPB.oc_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(464,4);
    hexStringToDecimalSignedInt(temp,a1500_30VPB.cur_noise,true);

    temp = justTheData.mid(468,2);
    a1500_30VPB.ov_step = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(470,2);
    a1500_30VPB.shunt = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(472,2);
    a1500_30VPB.max_off = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(474,2);
    a1500_30VPB.vin_limit = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(476,2);
    a1500_30VPB.vin_turn_on = static_cast<BYTE>(temp.toInt(&ok,16));

    temp = justTheData.mid(478,2);
    a1500_30VPB.IinLimitTempAmbientAdjust = static_cast<BYTE>(temp.toInt(&ok,16));

    QString linearKs = QString::number(static_cast<double>(a1500_30VPB.linearK[0][0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[0][1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[1][0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[1][1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[2][0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[2][1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[3][0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[3][1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[4][0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[4][1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[5][0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[5][1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[6][0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.linearK[6][1]));

    // qDebug() << Q_FUNC_INFO << " a1500_30VPB.linearKs being sent: " << linearKs;

    emit publishEndDeviceLinearKandOffs(macFlashFamily.at(0),macFlashFamily.at(2), linearKs);

    // qDebug() << Q_FUNC_INFO << " a1500_30VPB.linearKs have been sent: " << linearKs;

    QString edComms = QString::number(a1500_30VPB.netId) + comma + QString::number(a1500_30VPB.myBunch) + comma +
            QString::number(a1500_30VPB.groupId) + comma + QString::number(a1500_30VPB.syncword) + comma +
            QString::number(a1500_30VPB.rbunch) + comma + QString::number(a1500_30VPB.gbunch) + comma +
            QString::number(a1500_30VPB.channel) + comma + QString::number(a1500_30VPB.radioPower) + comma +
            QString::number(a1500_30VPB.edAddr) + comma + QString::number(a1500_30VPB.gwAddr) + comma +
            QString::number(a1500_30VPB.repeaterChannel) + comma + QString::number(a1500_30VPB.repeaterPower) + comma +
            QString::number(boolByte1) + comma + QString::number(a1500_30VPB.starting500Channel) + comma +
            QString::number(a1500_30VPB.CriticalLevel10) + comma + QString::number(a1500_30VPB.CriticalLevel500) + comma +
            QString::number(a1500_30VPB.IinOCStepsAndDelay) + comma + QString::number(boolByte2);

   // qDebug() << Q_FUNC_INFO << " edComms being sent: " << edComms;

    emit publishEndDeviceCommunicationSettings(macFlashFamily.at(0),edComms);

   // qDebug() << Q_FUNC_INFO << " edComms have been sent: " << edComms;

    QString edProtections = QString::number(a1500_30VPB.VoutLimitCount) + comma + QString::number(a1500_30VPB.VoutLimit) + comma +
            QString::number(a1500_30VPB.IoutLimitCount) + comma + QString::number(a1500_30VPB.IoutLimit) + comma +
            QString::number(a1500_30VPB.IinLimit) + comma + QString::number(a1500_30VPB.IinOCStepsAndDelay) + comma +
            QString::number(a1500_30VPB.monitoring) + comma + QString::number(a1500_30VPB.IinLimitTempAmbientAdjust);

    qDebug() << Q_FUNC_INFO << " 1500V 30V protections being sent ..." << edProtections;

    emit publishEndDeviceProtectionSettings(macFlashFamily.at(0),macFlashFamily.at(2), edProtections);
    qDebug() << Q_FUNC_INFO << " 1500V 30V protections have been sent ..." << edProtections;



    QString cntrlVolts = QString::number(a1500_30VPB.vin_disable_radio) + comma + QString::number(a1500_30VPB.ov) + comma +
            QString::number(a1500_30VPB.oc) + comma +
            QString::number(a1500_30VPB.ov_startup) + comma + QString::number(a1500_30VPB.oc_step) + comma +
            QString::number(a1500_30VPB.cur_noise) + comma + QString::number(a1500_30VPB.ov_step) + comma +
            QString::number(a1500_30VPB.vin_limit) + comma +
            QString::number(a1500_30VPB.vin_turn_on) + comma + QString::number(a1500_30VPB.IinLimitTempAmbientAdjust) + comma +
            QString::number(a1500_30VPB.module) + comma + QString::number(a1500_30VPB.mpp);


   qDebug() << Q_FUNC_INFO << "cntrlVolts to be sent: " << cntrlVolts;

    emit publishEndDevicePowerCntrlSettings(macFlashFamily.at(0), cntrlVolts);

    qDebug() << Q_FUNC_INFO << "cntrlVolts has been sent: " << cntrlVolts;

    QString tempCntrls = QString::number(a1500_30VPB.t_mod_off) + comma + QString::number(a1500_30VPB.toff_fallback) + comma +
            QString::number(a1500_30VPB.ton_fallback) + comma + QString::number(a1500_30VPB.fallback_time) + comma +
            QString::number(a1500_30VPB.oc_protection);

   qDebug() << Q_FUNC_INFO << " tempCntrl to be sent: " << tempCntrls;

    emit publishEndDeviceTempCntrlSettings(macFlashFamily.at(0), tempCntrls);

    qDebug() << Q_FUNC_INFO << " tempCntrl has been sent: " << tempCntrls;

    QString fineTuning = QString::number(static_cast<double>(a1500_30VPB.vrefPolynom[0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.vrefPolynom[1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.vrefPolynom[2])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.tkCurrent)) + comma +
            QString::number(static_cast<double>(a1500_30VPB.tkPower)) + comma +
            QString::number(a1500_30VPB.shortCircuitLevel);

    QString radio = QString::number(static_cast<double>(a1500_30VPB.dFk[0])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.dFk[1])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.dFk[2])) + comma +
            QString::number(static_cast<double>(a1500_30VPB.dFk[3])) + comma +
            QString::number(a1500_30VPB.pureOffset)+ comma +
            QString::number(a1500_30VPB.LowCurrentLimitTo255);


    qDebug() << Q_FUNC_INFO << " fine tuning to be sent: " << fineTuning;
    emit publishEndDeviceFineTuningSettings(macFlashFamily.at(0), fineTuning);
    qDebug() << Q_FUNC_INFO << " fine tuning has been sent: " << fineTuning;

    qDebug() << Q_FUNC_INFO << " radio to be sent: " << radio;
    emit publishEndDeviceRadioSettings(macFlashFamily.at(0), macFlashFamily.at(2), radio);
    qDebug() << Q_FUNC_INFO << " radio has been sent: " << radio;

    // qDebug() << Q_FUNC_INFO << "\n\n\n *** ### *** vS:" << versionSuffix<< " suffix1:" << versionSuffix.at(0) << versionSuffix.at(1)<< " suffix2:" << versionSuffix.at(2)  << versionSuffix.at(3) << " suffix3:" << versionSuffix.at(4) << versionSuffix.at(5);

    // qDebug() << Q_FUNC_INFO << " versionSuffixHexStr:" << versionSuffixHexStr;

    QString versionInfo = QString::number(a1500_30VPB.versionHigh) + comma + QString::number(a1500_30VPB.versionLow) + comma +
            QString::number(a1500_30VPB.utcHigh) + comma + QString::number(a1500_30VPB.utcLow) + comma +
            QString::number(a1500_30VPB.shunt) + comma + QString::number(a1500_30VPB.utcProgram) + comma + versionSuffixHexStr;
    // qDebug() << Q_FUNC_INFO << " version info to be sent: " << versionInfo;
    emit publishEndDeviceVersionSettings(macFlashFamily.at(0), macFlashFamily.at(2), versionInfo);
    // qDebug() << Q_FUNC_INFO << "version info has been sent: " << versionInfo;

    QString keyInfo = AESKey + comma + AESIV;

    emit publishEndDeviceKeySettings(macFlashFamily.at(0),keyInfo);

    QString edSettingsInfo = QString::number(a1500_30VPB.synch_freq) + comma + QString::number(a1500_30VPB.synch_phase);

    emit publishEndDeviceSettings(macFlashFamily.at(0), edSettingsInfo);

    emit publishEndDeviceNewPBs(macFlashFamily.at(0));



    // Convert Data into a 240 byte character array
    // Then based on family, store into MAP<string, struct *>

    if (mainImage.contains(macFlashFamily.at(0)))
    {
        QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
        emit publishEndDeviceOptimizerFamily(macFlashFamily.at(0),tShunt);
        emit publishEndDeviceOnMainImage(macFlashFamily.at(0), mainImage[macFlashFamily.at(0)]);
        qDebug() << Q_FUNC_INFO << " would store PB info with key:" << pbKey;

        ParameterBlock_Union * pPB = new ParameterBlock_Union;
        pPB->parameterBlockFamily = tShunt;
        pPB->PB.a1500_30VPB = a1500_30VPB;  // LBC does this do a "deep copy"?
        pPB->rawData = justTheData;
        parameterBlocksStorage.insert(pbKey,pPB);

        if (m_saveParameterBlockInfo == true)
        {
            qDebug() << Q_FUNC_INFO << " INFO: would save parameter block information to file...";
            if (endDeviceSaveParameterBlockInfo(pbKey))
            {
                qDebug() << Q_FUNC_INFO << " INFO: success from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: fail from endDeviceSaveParameterBlockInfo(" << pbKey << ")";
            }
        }
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: " + CurrentDateTime + " no running image information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }

    qDebug() << Q_FUNC_INFO << " Exiting ...";
    return retValue;
}

void EndDeviceParameterBlockInfoThread::handleFindStoredPBInfo(const QString s, const QString t)
{
  QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

  qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " BEGIN with partial key:" << s << " mainImage:" << t ;

   QMap<QString, ParameterBlock_Union *>::iterator currentParameterBlockStorage = parameterBlocksStorage.begin();
   endofParameterBlockStorage = parameterBlocksStorage.end();
   QString tKey;
   bool notFound = true;

   while ((notFound) && (currentParameterBlockStorage != endofParameterBlockStorage))
   {
       tKey = currentParameterBlockStorage.key();
       // qDebug() << Q_FUNC_INFO << " INFO: current key is " << tKey << " tKey.right(1):" << tKey.right(1);
       if (tKey.contains(s) && (tKey.right(1) == t) )
       // if (tKey.contains(s) )
       {
           // qDebug() << Q_FUNC_INFO << " INFO: partial key:" << s << " is contained with key:" << tKey << " and correct image " << t;
           ParameterBlock_Union * pPB = currentParameterBlockStorage.value();
           // qDebug() << Q_FUNC_INFO << " INFO: PB family: " << pPB->parameterBlockFamily << "\t\nstored raw data: " << pPB->rawData;
           // remove from map
           parameterBlocksStorage.remove(tKey);
           // qDebug() << Q_FUNC_INFO << " INFO: removed " << tKey;
           notFound = false;
           tKey.chop(2);
           QStringList keyAsList;
           keyAsList = tKey.split("_");
           // qDebug() << Q_FUNC_INFO << " INFO: newkey => " << tKey;

           if ( ! validateAndPlaceParameterBlockValues(keyAsList, pPB->rawData, pPB->parameterBlockFamily))
           {
               QString ErrorStr(Q_FUNC_INFO);
               ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for key:" + tKey;
               emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
               qDebug() << ErrorStr;
           }
       }
       else
       {
           ++currentParameterBlockStorage;
       }
   } /* END while ((notFound) && (currentParameterBlockStorage != endofParameterBlockStorage)) */

  qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " END with partial key:" << s;
}

void EndDeviceParameterBlockInfoThread::handleEndDeviceSaveParameterBlockInfoSignal(const bool s)
{
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    // qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " received 'save signal' of " << s;
    m_saveParameterBlockInfo = s;
}

bool EndDeviceParameterBlockInfoThread::endDeviceWrite1500V_30ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        // qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        // qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a1500_30VPB.barrier << Qt::endl;
            out << "netID:" << pPB->PB.a1500_30VPB.netId << "\t" << "bunch:" << pPB->PB.a1500_30VPB.myBunch << Qt::endl;
            out << "groupId:" << pPB->PB.a1500_30VPB.groupId << Qt::endl;
            out << "mac:" << pPB->PB.a1500_30VPB.myMac << Qt::endl;
            out << "dFk0:" << pPB->PB.a1500_30VPB.dFk[0] << "\tdFk1:" << pPB->PB.a1500_30VPB.dFk[1] << "\tdFk2:" << pPB->PB.a1500_30VPB.dFk[2] << "\tdFk3:" << pPB->PB.a1500_30VPB.dFk[3] << Qt::endl;
            out << "vrefPolynom[0]:" << pPB->PB.a1500_30VPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a1500_30VPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a1500_30VPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a1500_30VPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a1500_30VPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a1500_30VPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a1500_30VPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a1500_30VPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a1500_30VPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a1500_30VPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a1500_30VPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a1500_30VPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a1500_30VPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a1500_30VPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a1500_30VPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a1500_30VPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a1500_30VPB.linearK[6][1] << Qt::endl;
            out << "fetFailureCount:" << pPB->PB.a1500_30VPB.fetFailureCount << "\tfetCurrentThreshold:" << pPB->PB.a1500_30VPB.fetCurrentThreshold << "\tfetDeltaCurrent:" << pPB->PB.a1500_30VPB.fetDeltaCurrent << Qt::endl;

            out << "LowCurrentLimit255:" << pPB->PB.a1500_30VPB.LowCurrentLimitTo255 << Qt::endl;
            out << "VoutLimitCount:" << pPB->PB.a1500_30VPB.VoutLimitCount << "\tVoutLimit:" << pPB->PB.a1500_30VPB.VoutLimit << Qt::endl;
            out << "IoutLimitCount:" << pPB->PB.a1500_30VPB.IoutLimitCount << "\tIoutLimit:" << pPB->PB.a1500_30VPB.IoutLimit << Qt::endl;
            out << "versionSuffix[0]:" << pPB->PB.a1500_30VPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a1500_30VPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a1500_30VPB.versionSuffix[2] << Qt::endl;
            out << "tests:" << pPB->PB.a1500_30VPB.monitoring << Qt::endl;

            out << "installDate:" << pPB->PB.a1500_30VPB.installDate << Qt::endl;
            out << "IinLimit:" << pPB->PB.a1500_30VPB.IinLimit << Qt::endl;
            out << "syncword:" << pPB->PB.a1500_30VPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a1500_30VPB.vin_disable_radio << Qt::endl;
            out << "rbunch:" << pPB->PB.a1500_30VPB.rbunch << "\tgbunch:" << pPB->PB.a1500_30VPB.gbunch << Qt::endl;
            out << "shortCircuitLevel:" << pPB->PB.a1500_30VPB.shortCircuitLevel << Qt::endl;
            out << "reserved:" << pPB->PB.a1500_30VPB.reserved << Qt::endl;
            out << "synch_phase:" << pPB->PB.a1500_30VPB.synch_phase << "\tsynch_freq:" << pPB->PB.a1500_30VPB.synch_freq << Qt::endl;
            out << "bandwidth:" << pPB->PB.a1500_30VPB.bandwidth250 << Qt::endl;
            out << "channel:" << pPB->PB.a1500_30VPB.channel << Qt::endl;
            out << "utcProgram:" << pPB->PB.a1500_30VPB.utcProgram << "\tutcLow:" << pPB->PB.a1500_30VPB.utcLow << "\tutcHigh:" << pPB->PB.a1500_30VPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a1500_30VPB.tkCurrent << "\ttKPower:" << pPB->PB.a1500_30VPB.tkPower << Qt::endl;

            out << "mpp:" << pPB->PB.a1500_30VPB.mpp << "\tmodule:" << pPB->PB.a1500_30VPB.module << Qt::endl;
            out << "ov:" << pPB->PB.a1500_30VPB.ov << "\toc:" << pPB->PB.a1500_30VPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a1500_30VPB.radioPower << Qt::endl;
            out << "edAddr:" << pPB->PB.a1500_30VPB.edAddr << "\tgwAddr:" << pPB->PB.a1500_30VPB.gwAddr << Qt::endl;
            out << "repeaterChannel:" << pPB->PB.a1500_30VPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a1500_30VPB.repeaterPower << Qt::endl;;
            out << "boolByte1:" << pPB->PB.a1500_30VPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x80) == 0x80) << Qt::endl;
            out << "\tSlave:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x40) == 0x40) << Qt::endl;
            out << "\tRelay:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x20) == 0x20) << Qt::endl;
            out << "\tHopping Allow:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x08) == 0x08) << Qt::endl;
            out << "\t12kbod:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x04) == 0x04) << Qt::endl;
            out << "\tensureWDReset:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x02) == 0x02) << Qt::endl;
            out << "\tproduction:" << ((pPB->PB.a1500_30VPB.boolByte1 & 0x01) == 0x01) << Qt::endl;

            out << "boolByte2:" << pPB->PB.a1500_30VPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x80) == 0x80) << Qt::endl;
            out << "\tfuse Comms:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x40) == 0x40) << Qt::endl;
            out << "\tfuse OVOC:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x20) == 0x20) << Qt::endl;
            out << "\tuse FEC:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x10) == 0x10) << Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x08) == 0x08) << Qt::endl;
            out << "\tSpeculative Report:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x04) == 0x04) << Qt::endl;
            out << "\t250kbod:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x02) == 0x02) << Qt::endl;
            out << "\ttry Other Image:" << ((pPB->PB.a1500_30VPB.boolByte2 & 0x01) == 0x01) << Qt::endl;


            out << "IinOCStepsAndDelay:" << pPB->PB.a1500_30VPB.IinOCStepsAndDelay << Qt::endl;
            out << "CriticalLevel500:" << pPB->PB.a1500_30VPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a1500_30VPB.CriticalLevel10 << Qt::endl;
            out << "pureOffset:" << pPB->PB.a1500_30VPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a1500_30VPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a1500_30VPB.defCyclesTo10 << Qt::endl;
            out << "defCyclesToStep500Channel:" << pPB->PB.a1500_30VPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a1500_30VPB.defCyclesToStep10Channel << Qt::endl;
            out << "defCycles2SoftKick:" << pPB->PB.a1500_30VPB.defCycles2SoftKick << "\tdefCycles2HardKick:" << pPB->PB.a1500_30VPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a1500_30VPB.imageAddr << Qt::endl;
            out << "versionLow:" << pPB->PB.a1500_30VPB.versionLow << "\tversionHigh:" << pPB->PB.a1500_30VPB.versionHigh << Qt::endl;
            out << "starting500Channel:" << pPB->PB.a1500_30VPB.starting500Channel << Qt::endl;

            out << "prepAddr:" << pPB->PB.a1500_30VPB.prepAddr << Qt::endl;

            out << "repStep:" << pPB->PB.a1500_30VPB.repStep << Qt::endl;

            out << "ov_startup:" << pPB->PB.a1500_30VPB.ov_startup << Qt::endl;
            out << "t_mod_off:" << pPB->PB.a1500_30VPB.t_mod_off << "\toff_fallback:" << pPB->PB.a1500_30VPB.toff_fallback << "\tton_fallback:" << pPB->PB.a1500_30VPB.ton_fallback << "\tfallback_time:" << pPB->PB.a1500_30VPB.fallback_time << Qt::endl;
            out << "network_cnst_1:" << pPB->PB.a1500_30VPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a1500_30VPB.network_cnst_2 <<Qt::endl;
            out << "oc_protection:" << pPB->PB.a1500_30VPB.oc_protection << "\toc_step" << pPB->PB.a1500_30VPB.oc_step << Qt::endl;

            out << "cur_noise:" << pPB->PB.a1500_30VPB.cur_noise << Qt::endl;
            out << "ov_step:" << pPB->PB.a1500_30VPB.ov_step << Qt::endl;
            out << "shunt:" << pPB->PB.a1500_30VPB.shunt << Qt::endl;
            out << "max_off:" << pPB->PB.a1500_30VPB.max_off << Qt::endl;


            out << "vin_limit:" << pPB->PB.a1500_30VPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a1500_30VPB.vin_turn_on << "\tIinLimitTempAmbientAdjust:" << pPB->PB.a1500_30VPB.IinLimitTempAmbientAdjust << Qt::endl;
            pbFile.flush();
            pbFile.close();
        }
        emit publishEndDeviceParametersSavedToFile(pbFileName);
    }
    else
    {
        retValue = false;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceWrite1500V_2nd_ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a1500_2ndVPB.barrier;
            out << "\tnetID:" << pPB->PB.a1500_2ndVPB.netId << "\tbunch:" << pPB->PB.a1500_2ndVPB.myBunch;
            out << "\tgroupId:" << pPB->PB.a1500_2ndVPB.groupId;
            out << "\tmac:" << pPB->PB.a1500_2ndVPB.myMac << Qt::endl;
            out << "dFk0:" << pPB->PB.a1500_2ndVPB.dFk[0] << "\tdFk1:" << pPB->PB.a1500_2ndVPB.dFk[1] << "\tdFk2:" << pPB->PB.a1500_2ndVPB.dFk[2] << "\tdFk3:" << pPB->PB.a1500_2ndVPB.dFk[3];
            out << "\tvrefPolynom[0]:" << pPB->PB.a1500_2ndVPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a1500_2ndVPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a1500_2ndVPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a1500_2ndVPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a1500_2ndVPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a1500_2ndVPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a1500_2ndVPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a1500_2ndVPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a1500_2ndVPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a1500_2ndVPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a1500_2ndVPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a1500_2ndVPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a1500_2ndVPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a1500_2ndVPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a1500_2ndVPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a1500_2ndVPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a1500_2ndVPB.linearK[6][1] << Qt::endl;
            out << "ef_InputCurrentThreshold:" << pPB->PB.a1500_2ndVPB.ef_InputCurrentThreshold
                << "\tef_OccurrenceThreshold:" << pPB->PB.a1500_2ndVPB.ef_OccurrenceThreshold
                << "\tef_CountDownTimer:" << pPB->PB.a1500_2ndVPB.ef_CountDownTimer << Qt::endl;
            out << "ef_AlphaNumerator:" << pPB->PB.a1500_2ndVPB.ef_AlphaNumerator
                << "\tef_ModuleOff:" << pPB->PB.a1500_2ndVPB.ef_ModuleOff << Qt::endl;
            out << "\tmonitoring:" << pPB->PB.a1500_2ndVPB.monitoring << Qt::endl;

            out << "LowCurrentLimit255:" << pPB->PB.a1500_2ndVPB.LowCurrentLimitTo255;
            out << "\tVoutLimitCount:" << pPB->PB.a1500_2ndVPB.VoutLimitCount << "\tVoutLimit:" << pPB->PB.a1500_2ndVPB.VoutLimit;
            out << "\tIoutLimitCount:" << pPB->PB.a1500_2ndVPB.IoutLimitCount << "\tIoutLimit:" << pPB->PB.a1500_2ndVPB.IoutLimit << Qt::endl;
            out << "versionSuffix[0]:" << pPB->PB.a1500_2ndVPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a1500_2ndVPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a1500_2ndVPB.versionSuffix[2];


            out << "installDate:" << pPB->PB.a1500_2ndVPB.installDate;
            out << "\tk_ov_volt:" << pPB->PB.a1500_2ndVPB.k_ov_volt << "\tk_oc_cur:" << pPB->PB.a1500_2ndVPB.k_oc_cur;
            out << "\tsyncword:" << pPB->PB.a1500_2ndVPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a1500_2ndVPB.vin_disable_radio;
            out << "\trbunch:" << pPB->PB.a1500_2ndVPB.rbunch << "\tgbunch:" << pPB->PB.a1500_2ndVPB.gbunch;
            out << "\tshortCircuitLevel:" << pPB->PB.a1500_2ndVPB.shortCircuitLevel;
            out << "\treserved:" << pPB->PB.a1500_2ndVPB.reserved << Qt::endl;
            out << "synch_phase:" << pPB->PB.a1500_2ndVPB.synch_phase << "\tsynch_freq:" << pPB->PB.a1500_2ndVPB.synch_freq;
            out << "\tbandwidth:" << pPB->PB.a1500_2ndVPB.bandwidth250;
            out << "\tchannel:" << pPB->PB.a1500_2ndVPB.channel << Qt::endl;
            out << "utcProgram:" << pPB->PB.a1500_2ndVPB.utcProgram << "\tutcLow:" << pPB->PB.a1500_2ndVPB.utcLow << "\tutcHigh:" << pPB->PB.a1500_2ndVPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a1500_2ndVPB.tkCurrent << "\ttKPower:" << pPB->PB.a1500_2ndVPB.tkPower;

            out << "\tmpp:" << pPB->PB.a1500_2ndVPB.mpp << "\tmodule:" << pPB->PB.a1500_2ndVPB.module;
            out << "\tov:" << pPB->PB.a1500_2ndVPB.ov << "\toc:" << pPB->PB.a1500_2ndVPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a1500_2ndVPB.radioPower;
            out << "\tedAddr:" << pPB->PB.a1500_2ndVPB.edAddr << "\tgwAddr:" << pPB->PB.a1500_2ndVPB.gwAddr;
            out << "\trepeaterChannel:" << pPB->PB.a1500_2ndVPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a1500_2ndVPB.repeaterPower << Qt::endl;
            out << "boolByte1:" << pPB->PB.a1500_2ndVPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x80) == 0x80);
            out << "\tSlave:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x40) == 0x40);
            out << "\tRelay:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x20) == 0x20);
            out << "\tHopping Allow:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x08) == 0x08);
            out << "\t12kbod:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x04) == 0x04);
            out << "\tensureWDReset:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x02) == 0x02);
            out << "\tproduction:" << ((pPB->PB.a1500_2ndVPB.boolByte1 & 0x01) == 0x01) << Qt::endl;

            out << "boolByte2:" << pPB->PB.a1500_2ndVPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x80) == 0x80);
            out << "\tfuse Comms:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x40) == 0x40);
            out << "\tfuse OVOC:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x20) == 0x20);
            out << "\tuse FEC:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x10) == 0x10) << Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x08) == 0x08);
            out << "\tSpeculative Report:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x04) == 0x04);
            out << "\t250kbod:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x02) == 0x02);
            out << "\ttry Other Image:" << ((pPB->PB.a1500_2ndVPB.boolByte2 & 0x01) == 0x01) << Qt::endl;


            out << "showState:" << pPB->PB.a1500_2ndVPB.showState;
            out << "\tCriticalLevel500:" << pPB->PB.a1500_2ndVPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a1500_2ndVPB.CriticalLevel10;
            out << "\tpureOffset:" << pPB->PB.a1500_2ndVPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a1500_2ndVPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a1500_2ndVPB.defCyclesTo10;
            out << "\tdefCyclesToStep500Channel:" << pPB->PB.a1500_2ndVPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a1500_2ndVPB.defCyclesToStep10Channel;
            out << "\tdefCycles2SoftKick:" << pPB->PB.a1500_2ndVPB.defCycles2SoftKick << "\tdefCycles2HardKick:" << pPB->PB.a1500_2ndVPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a1500_2ndVPB.imageAddr;
            out << "\tversionLow:" << pPB->PB.a1500_2ndVPB.versionLow << "\tversionHigh:" << pPB->PB.a1500_2ndVPB.versionHigh;
            out << "\tstarting500Channel:" << pPB->PB.a1500_2ndVPB.starting500Channel << Qt::endl;

            out << "prepAddr:" << pPB->PB.a1500_2ndVPB.prepAddr;
            out << "\trepStep:" << pPB->PB.a1500_2ndVPB.repStep;

            out << "\tov_startup:" << pPB->PB.a1500_2ndVPB.ov_startup << Qt::endl;
            out << "t_mod_off:" << pPB->PB.a1500_2ndVPB.t_mod_off << "\toff_fallback:" << pPB->PB.a1500_2ndVPB.toff_fallback << "\tton_fallback:" << pPB->PB.a1500_2ndVPB.ton_fallback << "\tfallback_time:" << pPB->PB.a1500_2ndVPB.fallback_time << Qt::endl;
            out << "network_cnst_1:" << pPB->PB.a1500_2ndVPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a1500_2ndVPB.network_cnst_2;
            out << "\toc_protection:" << pPB->PB.a1500_2ndVPB.oc_protection << "\toc_step" << pPB->PB.a1500_2ndVPB.oc_step << Qt::endl;

            out << "cur_noise:" << pPB->PB.a1500_2ndVPB.cur_noise;
            out << "\tov_step:" << pPB->PB.a1500_2ndVPB.ov_step;
            out << "\tshunt:" << pPB->PB.a1500_2ndVPB.shunt;
            out << "\tmax_off:" << pPB->PB.a1500_2ndVPB.max_off << Qt::endl;


            out << "vin_limit:" << pPB->PB.a1500_2ndVPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a1500_2ndVPB.vin_turn_on << "\tvin_switch_off:" << pPB->PB.a1500_2ndVPB.vin_switch_off << Qt::endl;
            pbFile.flush();
            pbFile.close();
        }

        emit publishEndDeviceParametersSavedToFile(pbFileName);
    }
    else
    {
        retValue = false;
    }

    return retValue;
}



bool EndDeviceParameterBlockInfoThread::endDeviceWrite1500VParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a1500VPB.barrier;
            out << "\tnetID:" << pPB->PB.a1500VPB.netId << "\tbunch:" << pPB->PB.a1500VPB.myBunch;
            out << "\tgroupId:" << pPB->PB.a1500VPB.groupId;
            out << "\tmac:" << pPB->PB.a1500VPB.myMac << Qt::endl;
            out << "dFk0:" << pPB->PB.a1500VPB.dFk[0] << "\tdFk1:" << pPB->PB.a1500VPB.dFk[1] << "\tdFk2:" << pPB->PB.a1500VPB.dFk[2] << "\tdFk3:" << pPB->PB.a1500VPB.dFk[3];
            out << "\tvrefPolynom[0]:" << pPB->PB.a1500VPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a1500VPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a1500VPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a1500VPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a1500VPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a1500VPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a1500VPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a1500VPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a1500VPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a1500VPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a1500VPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a1500VPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a1500VPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a1500VPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a1500VPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a1500VPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a1500VPB.linearK[6][1] << Qt::endl;
            out << "fetFailureCount:" << pPB->PB.a1500VPB.fetFailureCount << "\tfetCurrentThreshold:" << pPB->PB.a1500VPB.fetCurrentThreshold << "\tfetDeltaCurrent:" << pPB->PB.a1500VPB.fetDeltaCurrent << Qt::endl;

            out << "LowCurrentLimit255:" << pPB->PB.a1500VPB.LowCurrentLimitTo255;
            out << "\tVoutLimitCount:" << pPB->PB.a1500VPB.VoutLimitCount << "\tVoutLimit:" << pPB->PB.a1500VPB.VoutLimit;
            out << "\tIoutLimitCount:" << pPB->PB.a1500VPB.IoutLimitCount << "\tIoutLimit:" << pPB->PB.a1500VPB.IoutLimit << Qt::endl;
            out << "versionSuffix[0]:" << pPB->PB.a1500VPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a1500VPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a1500VPB.versionSuffix[2];
            out << "\ttests:" << pPB->PB.a1500VPB.tests << Qt::endl;

            out << "installDate:" << pPB->PB.a1500VPB.installDate;
            out << "\tk_ov_volt:" << pPB->PB.a1500VPB.k_ov_volt << "\tk_oc_cur:" << pPB->PB.a1500VPB.k_oc_cur;
            out << "\tsyncword:" << pPB->PB.a1500VPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a1500VPB.vin_disable_radio;
            out << "\trbunch:" << pPB->PB.a1500VPB.rbunch << "\tgbunch:" << pPB->PB.a1500VPB.gbunch;
            out << "\tshortCircuitLevel:" << pPB->PB.a1500VPB.shortCircuitLevel;
            out << "\treserved:" << pPB->PB.a1500VPB.reserved << Qt::endl;
            out << "synch_phase:" << pPB->PB.a1500VPB.synch_phase << "\tsynch_freq:" << pPB->PB.a1500VPB.synch_freq;
            out << "\tbandwidth:" << pPB->PB.a1500VPB.bandwidth250;
            out << "\tchannel:" << pPB->PB.a1500VPB.channel << Qt::endl;
            out << "utcProgram:" << pPB->PB.a1500VPB.utcProgram << "\tutcLow:" << pPB->PB.a1500VPB.utcLow << "\tutcHigh:" << pPB->PB.a1500VPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a1500VPB.tkCurrent << "\ttKPower:" << pPB->PB.a1500VPB.tkPower;

            out << "\tmpp:" << pPB->PB.a1500VPB.mpp << "\tmodule:" << pPB->PB.a1500VPB.module;
            out << "\tov:" << pPB->PB.a1500VPB.ov << "\toc:" << pPB->PB.a1500VPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a1500VPB.radioPower;
            out << "\tedAddr:" << pPB->PB.a1500VPB.edAddr << "\tgwAddr:" << pPB->PB.a1500VPB.gwAddr;
            out << "\trepeaterChannel:" << pPB->PB.a1500VPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a1500VPB.repeaterPower << Qt::endl;
            out << "boolByte1:" << pPB->PB.a1500VPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a1500VPB.boolByte1 & 0x80) == 0x80);
            out << "\tSlave:" << ((pPB->PB.a1500VPB.boolByte1 & 0x40) == 0x40);
            out << "\tRelay:" << ((pPB->PB.a1500VPB.boolByte1 & 0x20) == 0x20);
            out << "\tHopping Allow:" << ((pPB->PB.a1500VPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a1500VPB.boolByte1 & 0x08) == 0x08);
            out << "\t12kbod:" << ((pPB->PB.a1500VPB.boolByte1 & 0x04) == 0x04);
            out << "\tensureWDReset:" << ((pPB->PB.a1500VPB.boolByte1 & 0x02) == 0x02);
            out << "\tproduction:" << ((pPB->PB.a1500VPB.boolByte1 & 0x01) == 0x01) << Qt::endl;

            out << "boolByte2:" << pPB->PB.a1500VPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a1500VPB.boolByte2 & 0x80) == 0x80);
            out << "\tfuse Comms:" << ((pPB->PB.a1500VPB.boolByte2 & 0x40) == 0x40);
            out << "\tfuse OVOC:" << ((pPB->PB.a1500VPB.boolByte2 & 0x20) == 0x20);
            out << "\tuse FEC:" << ((pPB->PB.a1500VPB.boolByte2 & 0x10) == 0x10) << Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a1500VPB.boolByte2 & 0x08) == 0x08);
            out << "\tSpeculative Report:" << ((pPB->PB.a1500VPB.boolByte2 & 0x04) == 0x04);
            out << "\t250kbod:" << ((pPB->PB.a1500VPB.boolByte2 & 0x02) == 0x02);
            out << "\ttry Other Image:" << ((pPB->PB.a1500VPB.boolByte2 & 0x01) == 0x01) << Qt::endl;


            out << "showState:" << pPB->PB.a1500VPB.showState;
            out << "\tCriticalLevel500:" << pPB->PB.a1500VPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a1500VPB.CriticalLevel10;
            out << "\tpureOffset:" << pPB->PB.a1500VPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a1500VPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a1500VPB.defCyclesTo10;
            out << "\tdefCyclesToStep500Channel:" << pPB->PB.a1500VPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a1500VPB.defCyclesToStep10Channel;
            out << "\tdefCycles2SoftKick:" << pPB->PB.a1500VPB.defCycles2SoftKick << "\tdefCycles2HardKick:" << pPB->PB.a1500VPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a1500VPB.imageAddr;
            out << "\tversionLow:" << pPB->PB.a1500VPB.versionLow << "\tversionHigh:" << pPB->PB.a1500VPB.versionHigh;
            out << "\tstarting500Channel:" << pPB->PB.a1500VPB.starting500Channel << Qt::endl;

            out << "prepAddr:" << pPB->PB.a1500VPB.prepAddr;
            out << "\trepStep:" << pPB->PB.a1500VPB.repStep;

            out << "\tov_startup:" << pPB->PB.a1500VPB.ov_startup << Qt::endl;
            out << "t_mod_off:" << pPB->PB.a1500VPB.t_mod_off << "\toff_fallback:" << pPB->PB.a1500VPB.toff_fallback << "\tton_fallback:" << pPB->PB.a1500VPB.ton_fallback << "\tfallback_time:" << pPB->PB.a1500VPB.fallback_time << Qt::endl;
            out << "network_cnst_1:" << pPB->PB.a1500VPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a1500VPB.network_cnst_2;
            out << "\toc_protection:" << pPB->PB.a1500VPB.oc_protection << "\toc_step" << pPB->PB.a1500VPB.oc_step << Qt::endl;

            out << "cur_noise:" << pPB->PB.a1500VPB.cur_noise;
            out << "\tov_step:" << pPB->PB.a1500VPB.ov_step;
            out << "\tshunt:" << pPB->PB.a1500VPB.shunt;
            out << "\tmax_off:" << pPB->PB.a1500VPB.max_off << Qt::endl;


            out << "vin_limit:" << pPB->PB.a1500VPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a1500VPB.vin_turn_on << "\tvin_switch_off:" << pPB->PB.a1500VPB.vin_switch_off << Qt::endl;
            pbFile.flush();
            pbFile.close();
        }

        emit publishEndDeviceParametersSavedToFile(pbFileName);
    }
    else
    {
        retValue = false;
    }

    return retValue;
}



bool EndDeviceParameterBlockInfoThread::endDeviceWrite1300VParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a1300VPB.barrier;
            out << "\tnetID:" << pPB->PB.a1300VPB.netId << "\tbunch:" << pPB->PB.a1300VPB.myBunch;
            out << "\tgroupId:" << pPB->PB.a1300VPB.groupId;
            out << "\tmac:" << pPB->PB.a1300VPB.myMac << Qt::endl;
            out << "dFk0:" << pPB->PB.a1300VPB.dFk[0] << "\tdFk1:" << pPB->PB.a1300VPB.dFk[1] << "\tdFk2:" << pPB->PB.a1300VPB.dFk[2] << "\tdFk3:" << pPB->PB.a1300VPB.dFk[3];
            out << "\tvrefPolynom[0]:" << pPB->PB.a1300VPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a1300VPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a1300VPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a1300VPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a1300VPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a1300VPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a1300VPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a1300VPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a1300VPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a1300VPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a1300VPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a1300VPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a1300VPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a1300VPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a1300VPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a1300VPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a1300VPB.linearK[6][1] << Qt::endl;
            out << "fetFailureCount:" << pPB->PB.a1300VPB.fetFailureCount << "\tfetCurrentThreshold:" << pPB->PB.a1300VPB.fetCurrentThreshold << "\tfetDeltaCurrent:" << pPB->PB.a1300VPB.fetDeltaCurrent << Qt::endl;

            out << "LowCurrentLimit255:" << pPB->PB.a1300VPB.LowCurrentLimitTo255;
            out << "\tVhvLimitVout:" << pPB->PB.a1300VPB.VhvLimitVout << "\tIhvLimitVout:" << pPB->PB.a1300VPB.IhvLimitVout;
            out << "\tVhvLimitVins:" << pPB->PB.a1300VPB.VhvLimitVins << "\tIhvLimitVins:" << pPB->PB.a1300VPB.IhvLimitVins << Qt::endl;
            out << "versionSuffix[0]:" << pPB->PB.a1300VPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a1300VPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a1300VPB.versionSuffix[2];
            out << "\ttests:" << pPB->PB.a1300VPB.tests << Qt::endl;

            out << "installDate:" << pPB->PB.a1300VPB.installDate;
            out << "\tk_ov_volt:" << pPB->PB.a1300VPB.k_ov_volt << "\tk_oc_cur:" << pPB->PB.a1300VPB.k_oc_cur;
            out << "\tsyncword:" << pPB->PB.a1300VPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a1300VPB.vin_disable_radio;
            out << "\trbunch:" << pPB->PB.a1300VPB.rbunch << "\tgbunch:" << pPB->PB.a1300VPB.gbunch;
            out << "\tshortCircuitLevel:" << pPB->PB.a1300VPB.shortCircuitLevel;
            out << "\treserved:" << pPB->PB.a1300VPB.reserved << Qt::endl;
            out << "synch_phase:" << pPB->PB.a1300VPB.synch_phase << "\tsynch_freq:" << pPB->PB.a1300VPB.synch_freq;
            out << "\tbandwidth:" << pPB->PB.a1300VPB.bandwidth250;
            out << "\tchannel:" << pPB->PB.a1300VPB.channel << Qt::endl;
            out << "utcProgram:" << pPB->PB.a1300VPB.utcProgram << "\tutcLow:" << pPB->PB.a1300VPB.utcLow << "\tutcHigh:" << pPB->PB.a1300VPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a1300VPB.tkCurrent << "\ttKPower:" << pPB->PB.a1300VPB.tkPower;

            out << "\tmpp:" << pPB->PB.a1300VPB.mpp << "\tmodule:" << pPB->PB.a1300VPB.module;
            out << "\tov:" << pPB->PB.a1300VPB.ov << "\toc:" << pPB->PB.a1300VPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a1300VPB.radioPower;
            out << "\tedAddr:" << pPB->PB.a1300VPB.edAddr << "\tgwAddr:" << pPB->PB.a1300VPB.gwAddr;
            out << "\trepeaterChannel:" << pPB->PB.a1300VPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a1300VPB.repeaterPower << Qt::endl;
            out << "boolByte1:" << pPB->PB.a1300VPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a1300VPB.boolByte1 & 0x80) == 0x80);
            out << "\tSlave:" << ((pPB->PB.a1300VPB.boolByte1 & 0x40) == 0x40);
            out << "\tRelay:" << ((pPB->PB.a1300VPB.boolByte1 & 0x20) == 0x20);
            out << "\tHopping Allow:" << ((pPB->PB.a1300VPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a1300VPB.boolByte1 & 0x08) == 0x08);
            out << "\t12kbod:" << ((pPB->PB.a1300VPB.boolByte1 & 0x04) == 0x04);
            out << "\tensureWDReset:" << ((pPB->PB.a1300VPB.boolByte1 & 0x02) == 0x02);
            out << "\tproduction:" << ((pPB->PB.a1300VPB.boolByte1 & 0x01) == 0x01) << Qt::endl;

            out << "boolByte2:" << pPB->PB.a1300VPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a1300VPB.boolByte2 & 0x80) == 0x80);
            out << "\tfuse Comms:" << ((pPB->PB.a1300VPB.boolByte2 & 0x40) == 0x40);
            out << "\tfuse OVOC:" << ((pPB->PB.a1300VPB.boolByte2 & 0x20) == 0x20);
            out << "\tuse FEC:" << ((pPB->PB.a1300VPB.boolByte2 & 0x10) == 0x10) << Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a1300VPB.boolByte2 & 0x08) == 0x08);
            out << "\tSpeculative Report:" << ((pPB->PB.a1300VPB.boolByte2 & 0x04) == 0x04);
            out << "\t250kbod:" << ((pPB->PB.a1300VPB.boolByte2 & 0x02) == 0x02);
            out << "\ttry Other Image:" << ((pPB->PB.a1300VPB.boolByte2 & 0x01) == 0x01) << Qt::endl;


            out << "showState:" << pPB->PB.a1300VPB.showState;
            out << "\tCriticalLevel500:" << pPB->PB.a1300VPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a1300VPB.CriticalLevel10;
            out << "\tpureOffset:" << pPB->PB.a1300VPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a1300VPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a1300VPB.defCyclesTo10;
            out << "\tdefCyclesToStep500Channel:" << pPB->PB.a1300VPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a1300VPB.defCyclesToStep10Channel;
            out << "\tdefCycles2SoftKick:" << pPB->PB.a1300VPB.defCycles2SoftKick << "\tdefCycles2HardKick:" << pPB->PB.a1300VPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a1300VPB.imageAddr;
            out << "\tversionLow:" << pPB->PB.a1300VPB.versionLow << "\tversionHigh:" << pPB->PB.a1300VPB.versionHigh << Qt::endl;
            out << "starting500Channel:" << pPB->PB.a1300VPB.starting500Channel;

            out << "\tprepAddr:" << pPB->PB.a1300VPB.prepAddr << Qt::endl;

            out << "repStep:" << pPB->PB.a1300VPB.repStep << Qt::endl;

            out << "ov_startup:" << pPB->PB.a1300VPB.ov_startup;
            out << "\tt_mod_off:" << pPB->PB.a1300VPB.t_mod_off << "\toff_fallback:" << pPB->PB.a1300VPB.toff_fallback << "\tton_fallback:" << pPB->PB.a1300VPB.ton_fallback << "\tfallback_time:" << pPB->PB.a1300VPB.fallback_time;
            out << "\tnetwork_cnst_1:" << pPB->PB.a1300VPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a1300VPB.network_cnst_2 <<Qt::endl;
            out << "oc_protection:" << pPB->PB.a1300VPB.oc_protection << "\toc_step" << pPB->PB.a1300VPB.oc_step;

            out << "\tcur_noise:" << pPB->PB.a1300VPB.cur_noise;
            out << "\tov_step:" << pPB->PB.a1300VPB.ov_step;
            out << "\tshunt:" << pPB->PB.a1300VPB.shunt;
            out << "max_off:" << pPB->PB.a1300VPB.max_off << Qt::endl;


            out << "vin_limit:" << pPB->PB.a1300VPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a1300VPB.vin_turn_on << "\tvin_switch_off:" << pPB->PB.a1300VPB.vin_switch_off << Qt::endl;
            pbFile.flush();
            pbFile.close();
        }

        emit publishEndDeviceParametersSavedToFile(pbFileName);
    }
    else
    {
        retValue = false;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceWrite1300V_2nd_ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a1300_2ndVPB.barrier;
            out << "\tnetID:" << pPB->PB.a1300_2ndVPB.netId << "\tbunch:" << pPB->PB.a1300_2ndVPB.myBunch;
            out << "\tgroupId:" << pPB->PB.a1300_2ndVPB.groupId;
            out << "\tmac:" << pPB->PB.a1300_2ndVPB.myMac << Qt::endl;
            out << "dFk0:" << pPB->PB.a1300_2ndVPB.dFk[0] << "\tdFk1:" << pPB->PB.a1300_2ndVPB.dFk[1] << "\tdFk2:" << pPB->PB.a1300_2ndVPB.dFk[2] << "\tdFk3:" << pPB->PB.a1300_2ndVPB.dFk[3];
            out << "\tvrefPolynom[0]:" << pPB->PB.a1300_2ndVPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a1300_2ndVPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a1300_2ndVPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a1300_2ndVPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a1300_2ndVPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a1300_2ndVPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a1300_2ndVPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a1300_2ndVPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a1300_2ndVPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a1300_2ndVPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a1300_2ndVPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a1300_2ndVPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a1300_2ndVPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a1300_2ndVPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a1300_2ndVPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a1300_2ndVPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a1300_2ndVPB.linearK[6][1] << Qt::endl;
            out << "fetFailureCount:" << pPB->PB.a1300_2ndVPB.fetFailureCount << "\tfetCurrentThreshold:" << pPB->PB.a1300_2ndVPB.fetCurrentThreshold << "\tfetDeltaCurrent:" << pPB->PB.a1300_2ndVPB.fetDeltaCurrent << Qt::endl;

            out << "LowCurrentLimit255:" << pPB->PB.a1300_2ndVPB.LowCurrentLimitTo255;
            out << "\tVhvLimitVout:" << pPB->PB.a1300_2ndVPB.VhvLimitVout << "\tIhvLimitVout:" << pPB->PB.a1300_2ndVPB.IhvLimitVout;
            out << "\tVhvLimitVins:" << pPB->PB.a1300_2ndVPB.VhvLimitVins << "\tIhvLimitVins:" << pPB->PB.a1300_2ndVPB.IhvLimitVins << Qt::endl;
            out << "versionSuffix[0]:" << pPB->PB.a1300_2ndVPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a1300_2ndVPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a1300_2ndVPB.versionSuffix[2];
            out << "\ttests:" << pPB->PB.a1300_2ndVPB.tests << Qt::endl;

            out << "installDate:" << pPB->PB.a1300_2ndVPB.installDate;
            out << "\tk_ov_volt:" << pPB->PB.a1300_2ndVPB.k_ov_volt << "\tk_oc_cur:" << pPB->PB.a1300_2ndVPB.k_oc_cur;
            out << "\tsyncword:" << pPB->PB.a1300_2ndVPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a1300_2ndVPB.vin_disable_radio;
            out << "\trbunch:" << pPB->PB.a1300_2ndVPB.rbunch << "\tgbunch:" << pPB->PB.a1300_2ndVPB.gbunch;
            out << "\tshortCircuitLevel:" << pPB->PB.a1300_2ndVPB.shortCircuitLevel;
            out << "\treserved:" << pPB->PB.a1300_2ndVPB.reserved << Qt::endl;
            out << "synch_phase:" << pPB->PB.a1300_2ndVPB.synch_phase << "\tsynch_freq:" << pPB->PB.a1300_2ndVPB.synch_freq;
            out << "\tbandwidth:" << pPB->PB.a1300_2ndVPB.bandwidth250;
            out << "\tchannel:" << pPB->PB.a1300_2ndVPB.channel << Qt::endl;
            out << "utcProgram:" << pPB->PB.a1300_2ndVPB.utcProgram << "\tutcLow:" << pPB->PB.a1300_2ndVPB.utcLow << "\tutcHigh:" << pPB->PB.a1300_2ndVPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a1300_2ndVPB.tkCurrent << "\ttKPower:" << pPB->PB.a1300_2ndVPB.tkPower;

            out << "\tmpp:" << pPB->PB.a1300_2ndVPB.mpp << "\tmodule:" << pPB->PB.a1300_2ndVPB.module;
            out << "\tov:" << pPB->PB.a1300_2ndVPB.ov << "\toc:" << pPB->PB.a1300_2ndVPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a1300_2ndVPB.radioPower;
            out << "\tedAddr:" << pPB->PB.a1300_2ndVPB.edAddr << "\tgwAddr:" << pPB->PB.a1300_2ndVPB.gwAddr;
            out << "\trepeaterChannel:" << pPB->PB.a1300_2ndVPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a1300_2ndVPB.repeaterPower << Qt::endl;
            out << "boolByte1:" << pPB->PB.a1300_2ndVPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x80) == 0x80);
            out << "\tSlave:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x40) == 0x40);
            out << "\tRelay:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x20) == 0x20);
            out << "\tHopping Allow:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x08) == 0x08);
            out << "\t12kbod:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x04) == 0x04);
            out << "\tensureWDReset:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x02) == 0x02);
            out << "\tproduction:" << ((pPB->PB.a1300_2ndVPB.boolByte1 & 0x01) == 0x01) << Qt::endl;

            out << "boolByte2:" << pPB->PB.a1300_2ndVPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x80) == 0x80);
            out << "\tfuse Comms:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x40) == 0x40);
            out << "\tfuse OVOC:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x20) == 0x20);
            out << "\tuse FEC:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x10) == 0x10) << Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x08) == 0x08);
            out << "\tSpeculative Report:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x04) == 0x04);
            out << "\t250kbod:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x02) == 0x02);
            out << "\ttry Other Image:" << ((pPB->PB.a1300_2ndVPB.boolByte2 & 0x01) == 0x01) << Qt::endl;


            out << "showState:" << pPB->PB.a1300_2ndVPB.showState;
            out << "\tCriticalLevel500:" << pPB->PB.a1300_2ndVPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a1300_2ndVPB.CriticalLevel10;
            out << "\tpureOffset:" << pPB->PB.a1300_2ndVPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a1300_2ndVPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a1300_2ndVPB.defCyclesTo10;
            out << "\tdefCyclesToStep500Channel:" << pPB->PB.a1300_2ndVPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a1300_2ndVPB.defCyclesToStep10Channel;
            out << "\tdefCycles2SoftKick:" << pPB->PB.a1300_2ndVPB.defCycles2SoftKick << "\tdefCycles2HardKick:" << pPB->PB.a1300_2ndVPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a1300_2ndVPB.imageAddr;
            out << "\tversionLow:" << pPB->PB.a1300_2ndVPB.versionLow << "\tversionHigh:" << pPB->PB.a1300_2ndVPB.versionHigh << Qt::endl;
            out << "starting500Channel:" << pPB->PB.a1300_2ndVPB.starting500Channel;

            out << "\tprepAddr:" << pPB->PB.a1300_2ndVPB.prepAddr << Qt::endl;

            out << "repStep:" << pPB->PB.a1300_2ndVPB.repStep << Qt::endl;

            out << "ov_startup:" << pPB->PB.a1300_2ndVPB.ov_startup;
            out << "\tt_mod_off:" << pPB->PB.a1300_2ndVPB.t_mod_off << "\toff_fallback:" << pPB->PB.a1300_2ndVPB.toff_fallback << "\tton_fallback:" << pPB->PB.a1300_2ndVPB.ton_fallback << "\tfallback_time:" << pPB->PB.a1300_2ndVPB.fallback_time;
            out << "\tnetwork_cnst_1:" << pPB->PB.a1300_2ndVPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a1300_2ndVPB.network_cnst_2 <<Qt::endl;
            out << "oc_protection:" << pPB->PB.a1300_2ndVPB.oc_protection << "\toc_step" << pPB->PB.a1300_2ndVPB.oc_step;

            out << "\tcur_noise:" << pPB->PB.a1300_2ndVPB.cur_noise;
            out << "\tov_step:" << pPB->PB.a1300_2ndVPB.ov_step;
            out << "\tshunt:" << pPB->PB.a1300_2ndVPB.shunt;
            out << "max_off:" << pPB->PB.a1300_2ndVPB.max_off << Qt::endl;


            out << "vin_limit:" << pPB->PB.a1300_2ndVPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a1300_2ndVPB.vin_turn_on << "\tvin_switch_off:" << pPB->PB.a1300_2ndVPB.vin_switch_off << Qt::endl;
            pbFile.flush();
            pbFile.close();
        }

        emit publishEndDeviceParametersSavedToFile(pbFileName);
    }
    else
    {
        retValue = false;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceWrite1000VParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a1000VPB.barrier;
            out << "\tnetID:" << pPB->PB.a1000VPB.netId << "\t" << "bunch:" << pPB->PB.a1000VPB.myBunch;
            out << "\tgroupId:" << pPB->PB.a1000VPB.groupId;
            out << "\tmac:" << pPB->PB.a1000VPB.myMac << Qt::endl;
            out << "dFk0:" << pPB->PB.a1000VPB.dFk[0] << "\tdFk1:" << pPB->PB.a1000VPB.dFk[1] << "\tdFk2:" << pPB->PB.a1000VPB.dFk[2] << "\tdFk3:" << pPB->PB.a1000VPB.dFk[3];
            out << "\tvrefPolynom[0]:" << pPB->PB.a1000VPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a1000VPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a1000VPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a1000VPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a1000VPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a1000VPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a1000VPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a1000VPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a1000VPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a1000VPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a1000VPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a1000VPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a1000VPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a1000VPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a1000VPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a1000VPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a1000VPB.linearK[6][1] << Qt::endl;
            out << "fetFailureCount:" << pPB->PB.a1000VPB.fetFailureCount << "\tfetCurrentThreshold:" << pPB->PB.a1000VPB.fetCurrentThreshold << "\tfetDeltaCurrent:" << pPB->PB.a1000VPB.fetDeltaCurrent << Qt::endl;

            out << "\toscLowCurrentLimitInmA:" << pPB->PB.a1000VPB.oscLowCurrentLimitInmA;
            out << "\toscDeltaV:" << pPB->PB.a1000VPB.oscDeltaV << "\toscOVStartupDelay:" << pPB->PB.a1000VPB.oscOVStartupDelay;
            out << "\toscAfterStartupDelay:" << pPB->PB.a1000VPB.oscAfterStartupDelay << "\toscLowCurrentOnlyDelay:" << pPB->PB.a1000VPB.oscLowCurrentOnlyDelay << Qt::endl;
           // out << "versionSuffix[0]:" << pPB->PB.a1000VPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a1000VPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a1000VPB.versionSuffix[2] << Qt::endl;
            out << "tests:" << pPB->PB.a1000VPB.tests[0] << pPB->PB.a1000VPB.tests[1] << pPB->PB.a1000VPB.tests[2] << pPB->PB.a1000VPB.tests[3];

            out << "\tinstallDate:" << pPB->PB.a1000VPB.installDate << Qt::endl;
            out << "k_ov_volt:" << pPB->PB.a1000VPB.k_ov_volt << "\tk_oc_cur:" << pPB->PB.a1000VPB.k_oc_cur;
            out << "\tsyncword:" << pPB->PB.a1000VPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a1000VPB.vin_disable_radio;
            out << "\trbunch:" << pPB->PB.a1000VPB.rbunch << "\tgbunch:" << pPB->PB.a1000VPB.gbunch;
            out << "\tshortCircuitLevel:" << pPB->PB.a1000VPB.shortCircuitLevel;
            out << "\treserved:" << pPB->PB.a1000VPB.reserved << Qt::endl;
            out << "synch_phase:" << pPB->PB.a1000VPB.synch_phase << "\tsynch_freq:" << pPB->PB.a1000VPB.synch_freq;
            out << "\tbandwidth:" << pPB->PB.a1000VPB.bandwidth250;
            out << "\tchannel:" << pPB->PB.a1000VPB.channel;
            out << "utcProgram:" << pPB->PB.a1000VPB.utcProgram << "\tutcLow:" << pPB->PB.a1000VPB.utcLow << "\tutcHigh:" << pPB->PB.a1000VPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a1000VPB.tkCurrent << "\ttKPower:" << pPB->PB.a1000VPB.tkPower << Qt::endl;

            out << "mpp:" << pPB->PB.a1000VPB.mpp << "\tmodule:" << pPB->PB.a1000VPB.module;
            out << "\tov:" << pPB->PB.a1000VPB.ov << "\toc:" << pPB->PB.a1000VPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a1000VPB.radioPower;
            out << "\tedAddr:" << pPB->PB.a1000VPB.edAddr << "\tgwAddr:" << pPB->PB.a1000VPB.gwAddr;
            out << "\trepeaterChannel:" << pPB->PB.a1000VPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a1000VPB.repeaterPower << Qt::endl;
            out << "boolByte1:" << pPB->PB.a1000VPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a1000VPB.boolByte1 & 0x80) == 0x80);
            out << "\tSlave:" << ((pPB->PB.a1000VPB.boolByte1 & 0x40) == 0x40);
            out << "\tRelay:" << ((pPB->PB.a1000VPB.boolByte1 & 0x20) == 0x20);
            out << "\tHopping Allow:" << ((pPB->PB.a1000VPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a1000VPB.boolByte1 & 0x08) == 0x08);
            out << "\t12kbod:" << ((pPB->PB.a1000VPB.boolByte1 & 0x04) == 0x04);
            out << "\tensureWDReset:" << ((pPB->PB.a1000VPB.boolByte1 & 0x02) == 0x02);
            out << "\tproduction:" << ((pPB->PB.a1000VPB.boolByte1 & 0x01) == 0x01) << Qt::endl;

            out << "boolByte2:" << pPB->PB.a1000VPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a1000VPB.boolByte2 & 0x80) == 0x80);
            out << "\tfuse Comms:" << ((pPB->PB.a1000VPB.boolByte2 & 0x40) == 0x40);
            out << "\tfuse OVOC:" << ((pPB->PB.a1000VPB.boolByte2 & 0x20) == 0x20);
            out << "\tuse FEC:" << ((pPB->PB.a1000VPB.boolByte2 & 0x10) == 0x10) << Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a1000VPB.boolByte2 & 0x08) == 0x08);
            out << "\tSpeculative Report:" << ((pPB->PB.a1000VPB.boolByte2 & 0x04) == 0x04);
            out << "\t250kbod:" << ((pPB->PB.a1000VPB.boolByte2 & 0x02) == 0x02);
            out << "\ttry Other Image:" << ((pPB->PB.a1000VPB.boolByte2 & 0x01) == 0x01) << Qt::endl;


            out << "showState:" << pPB->PB.a1000VPB.showState;
            out << "\tCriticalLevel500:" << pPB->PB.a1000VPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a1000VPB.CriticalLevel10;
            out << "\tpureOffset:" << pPB->PB.a1000VPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a1000VPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a1000VPB.defCyclesTo10 ;
            out << "\tdefCyclesToStep500Channel:" << pPB->PB.a1000VPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a1000VPB.defCyclesToStep10Channel;
            out << "\tdefCycles2SoftKick:" << pPB->PB.a1000VPB.defCycles2SoftKick << "\tdefCycles2HardKick:" << pPB->PB.a1000VPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a1000VPB.imageAddr;
            out << "\tversionLow:" << pPB->PB.a1000VPB.versionLow << "\tversionHigh:" << pPB->PB.a1000VPB.versionHigh;
            out << "\tstarting500Channel:" << pPB->PB.a1000VPB.starting500Channel << Qt::endl;

            out << "prepAddr:" << pPB->PB.a1000VPB.prepAddr;
            out << "\trepStep:" << pPB->PB.a1000VPB.repStep;

            out << "\tov_startup:" << pPB->PB.a1000VPB.ov_startup;
            out << "\tt_mod_off:" << pPB->PB.a1000VPB.t_mod_off << "\toff_fallback:" << pPB->PB.a1000VPB.toff_fallback << "\tton_fallback:" << pPB->PB.a1000VPB.ton_fallback << "\tfallback_time:" << pPB->PB.a1000VPB.fallback_time;
            out << "network_cnst_1:" << pPB->PB.a1000VPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a1000VPB.network_cnst_2 <<Qt::endl;
            out << "oc_protection:" << pPB->PB.a1000VPB.oc_protection << "\toc_step" << pPB->PB.a1000VPB.oc_step;

            out << "\tcur_noise:" << pPB->PB.a1000VPB.cur_noise << Qt::endl;
            out << "ov_step:" << pPB->PB.a1000VPB.ov_step;
            out << "\tshunt:" << pPB->PB.a1000VPB.shunt;
            out << "\tmax_off:" << pPB->PB.a1000VPB.max_off;


            out << "\tvin_limit:" << pPB->PB.a1000VPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a1000VPB.vin_turn_on << "\tvin_switch_off:" << pPB->PB.a1000VPB.vin_switch_off << Qt::endl;
            pbFile.flush();
            pbFile.close();
        }
        emit publishEndDeviceParametersSavedToFile(pbFileName);

    }
    else
    {
        retValue = false;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceWrite600V_V2_2ndParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();


        if ((pPB->PB.a600V_V2_2ndVPB.versionSuffix[0] != '1') || (pPB->PB.a600V_V2_2ndVPB.versionSuffix[2] != ' ') )
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " expected firmware version of '1F ' or '1G ' not found, not writing Parameter Block information to file.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
            return retValue;
        }
        qDebug() << Q_FUNC_INFO << " INFO: found 600V_V2_2nd parameterBlockFamily" << pPB->parameterBlockFamily ;

        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a600V_V2_2ndVPB.barrier;
            out << "\tnetID:" << pPB->PB.a600V_V2_2ndVPB.netId << "\tbunch:" << pPB->PB.a600V_V2_2ndVPB.myBunch;
            out << "\tgroupId:" << pPB->PB.a600V_V2_2ndVPB.groupId << Qt::endl;
            out << "mac:" << pPB->PB.a600V_V2_2ndVPB.myMac << "\ttimeStamp Read:" << CurrentDateTime << Qt::endl;
            out << "dFk0:" << pPB->PB.a600V_V2_2ndVPB.dFk[0] << "\tdFk1:" << pPB->PB.a600V_V2_2ndVPB.dFk[1] << "\tdFk2:" << pPB->PB.a600V_V2_2ndVPB.dFk[2] << "\tdFk3:" << pPB->PB.a600V_V2_2ndVPB.dFk[3];
            out << "\tvrefPolynom[0]:" << pPB->PB.a600V_V2_2ndVPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a600V_V2_2ndVPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a600V_V2_2ndVPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a600V_V2_2ndVPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a600V_V2_2ndVPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a600V_V2_2ndVPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a600V_V2_2ndVPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a600V_V2_2ndVPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a600V_V2_2ndVPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a600V_V2_2ndVPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a600V_V2_2ndVPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a600V_V2_2ndVPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a600V_V2_2ndVPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a600V_V2_2ndVPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a600V_V2_2ndVPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a600V_V2_2ndVPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a600V_V2_2ndVPB.linearK[6][1] << Qt::endl;
            out << "fetFailureCount:" << pPB->PB.a600V_V2_2ndVPB.fetFailureCount << "\tfetCurrentThreshold:" << pPB->PB.a600V_V2_2ndVPB.fetCurrentThreshold << "\tfetDeltaCurrent:" << pPB->PB.a600V_V2_2ndVPB.fetDeltaCurrent << Qt::endl;

            out << "LowCurrentLimit255:" << pPB->PB.a600V_V2_2ndVPB.LowCurrentLimitTo255;
            out << "\tVhvLimitVout:" << pPB->PB.a600V_V2_2ndVPB.VhvLimitVout << "\tIhvLimitVout:" << pPB->PB.a600V_V2_2ndVPB.IhvLimitVout;
            out << "\tVhvLimitVins:" << pPB->PB.a600V_V2_2ndVPB.VhvLimitVins << "\tIhvLimitVins:" << pPB->PB.a600V_V2_2ndVPB.IhvLimitVins << Qt::endl;

            out << "versionSuffix[0]:" << pPB->PB.a600V_V2_2ndVPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a600V_V2_2ndVPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a600V_V2_2ndVPB.versionSuffix[2];
            out << "\ttests:" << pPB->PB.a600V_V2_2ndVPB.tests << "\n\t::: Memory Fix: (debug MF Output) " << (pPB->PB.a600V_V2_2ndVPB.tests ? "On" : "Off" ) << Qt::endl;

            out << "installDate:" << pPB->PB.a600V_V2_2ndVPB.installDate;
            out << "\tk_ov_volt:" << pPB->PB.a600V_V2_2ndVPB.k_ov_volt << "\tk_oc_cur:" << pPB->PB.a600V_V2_2ndVPB.k_oc_cur;
            out << "\tsyncword:" << pPB->PB.a600V_V2_2ndVPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a600V_V2_2ndVPB.vin_disable_radio;
            out << "\trbunch:" << pPB->PB.a600V_V2_2ndVPB.rbunch << "\tgbunch:" << pPB->PB.a600V_V2_2ndVPB.gbunch;
            out << "\tshortCircuitLevel:" << pPB->PB.a600V_V2_2ndVPB.shortCircuitLevel << Qt::endl;
            out << "reserved: " << pPB->PB.a600V_V2_2ndVPB.reserved << "\n\t::: Memory Fix: " << ((pPB->PB.a600V_V2_2ndVPB.reserved & 0xF0) >> 4) << ":" << (pPB->PB.a600V_V2_2ndVPB.reserved & 0x0F);
            out << "\tsynch_phase:" << pPB->PB.a600V_V2_2ndVPB.synch_phase << "\tsynch_freq:" << pPB->PB.a600V_V2_2ndVPB.synch_freq << Qt::endl;
            out << "\tbandwidth:" << pPB->PB.a600V_V2_2ndVPB.bandwidth250;
            out << "\tchannel:" << pPB->PB.a600V_V2_2ndVPB.channel << Qt::endl;
            out << "utcProgram:" << pPB->PB.a600V_V2_2ndVPB.utcProgram << "\tutcLow:" << pPB->PB.a600V_V2_2ndVPB.utcLow << "\tutcHigh:" << pPB->PB.a600V_V2_2ndVPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a600V_V2_2ndVPB.tkCurrent << "\ttKPower:" << pPB->PB.a600V_V2_2ndVPB.tkPower;

            out << "mpp:" << pPB->PB.a600V_V2_2ndVPB.mpp << "\tmodule:" << pPB->PB.a600V_V2_2ndVPB.module;
            out << "\tov:" << pPB->PB.a600V_V2_2ndVPB.ov << "\toc:" << pPB->PB.a600V_V2_2ndVPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a600V_V2_2ndVPB.radioPower;
            out << "\tedAddr:" << pPB->PB.a600V_V2_2ndVPB.edAddr << "\tgwAddr:" << pPB->PB.a600V_V2_2ndVPB.gwAddr << Qt::endl;
            out << "repeaterChannel:" << pPB->PB.a600V_V2_2ndVPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a600V_V2_2ndVPB.repeaterPower << Qt::endl;
            out << "boolByte1:" << pPB->PB.a600V_V2_2ndVPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x80) == 0x80);
            out << "\tSlave:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x40) == 0x40);
            out << "\tRelay:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x20) == 0x20);
            out << "\tHopping Allow:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x08) == 0x08);
            out << "\t12kbod:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x04) == 0x04);
            out << "\tensureWDReset:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x02) == 0x02);
            out << "\tproduction:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte1 & 0x01) == 0x01);

            out << "boolByte2:" << pPB->PB.a600V_V2_2ndVPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x80) == 0x80);
            out << "\tfuse Comms:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x40) == 0x40);
            out << "\tfuse OVOC:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x20) == 0x20);
            out << "\tuse FEC:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x10) == 0x10)<< Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x08) == 0x08);
            out << "\tSpeculative Report:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x04) == 0x04);
            out << "\t250kbod:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x02) == 0x02);
            out << "\ttry Other Image:" << ((pPB->PB.a600V_V2_2ndVPB.boolByte2 & 0x01) == 0x01) << Qt::endl;


            out << "showState:" << pPB->PB.a600V_V2_2ndVPB.showState;
            out << "\tCriticalLevel500:" << pPB->PB.a600V_V2_2ndVPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a600V_V2_2ndVPB.CriticalLevel10;
            out << "\tpureOffset:" << pPB->PB.a600V_V2_2ndVPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a600V_V2_2ndVPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a600V_V2_2ndVPB.defCyclesTo10 << Qt::endl;
            out << "defCyclesToStep500Channel:" << pPB->PB.a600V_V2_2ndVPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a600V_V2_2ndVPB.defCyclesToStep10Channel << Qt::endl;
            out << "defCycles2SoftKick: \t::: Memory Fix Output Voltage Threshold: " << pPB->PB.a600V_V2_2ndVPB.defCycles2SoftKick;
            out << "\tdefCycles2HardKick: \t::: Memory Fix Output Current Threshold (mA):" << pPB->PB.a600V_V2_2ndVPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a600V_V2_2ndVPB.imageAddr;
            out << "\tversionLow:" << pPB->PB.a600V_V2_2ndVPB.versionLow << "\tversionHigh:" << pPB->PB.a600V_V2_2ndVPB.versionHigh;
            out << "\tstarting500Channel:" << pPB->PB.a600V_V2_2ndVPB.starting500Channel << Qt::endl;


            out << "prepAddr:" << pPB->PB.a600V_V2_2ndVPB.prepAddr;

            out << "\trepStep:" << pPB->PB.a600V_V2_2ndVPB.repStep;

            out << "\tov_startup:" << pPB->PB.a600V_V2_2ndVPB.ov_startup << Qt::endl;
            out << "t_mod_off:" << pPB->PB.a600V_V2_2ndVPB.t_mod_off << "\toff_fallback:" << pPB->PB.a600V_V2_2ndVPB.toff_fallback << "\tton_fallback:" << pPB->PB.a600V_V2_2ndVPB.ton_fallback << "\tfallback_time:" << pPB->PB.a600V_V2_2ndVPB.fallback_time;
            out << "\tnetwork_cnst_1:" << pPB->PB.a600V_V2_2ndVPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a600V_V2_2ndVPB.network_cnst_2;
            out << "\toc_protection:" << pPB->PB.a600V_V2_2ndVPB.oc_protection << "\toc_step" << pPB->PB.a600V_V2_2ndVPB.oc_step << Qt::endl;

            out << "cur_noise:\t::: Memory Fix Timer1 (0 disables MF algorithm):" << (pPB->PB.a600V_V2_2ndVPB.cur_noise & 0x00FF) << " Timer2:" << ((pPB->PB.a600V_V2_2ndVPB.cur_noise & 0xFF00) >> 8) << Qt::endl;
            out << "ov_step:" << pPB->PB.a600V_V2_2ndVPB.ov_step;
            out << "\tshunt:" << pPB->PB.a600V_V2_2ndVPB.shunt;
            out << "\tmax_off:" << pPB->PB.a600V_V2_2ndVPB.max_off;


            out << "vin_limit:" << pPB->PB.a600V_V2_2ndVPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a600V_V2_2ndVPB.vin_turn_on << "\tvin_switch_off:" << pPB->PB.a600V_V2_2ndVPB.vin_switch_off << Qt::endl;
            pbFile.flush();
            pbFile.close();
        }
        emit publishEndDeviceParametersSavedToFile(pbFileName);
    }
    else
    {
        retValue = false;
    }

    return retValue;
}


bool EndDeviceParameterBlockInfoThread::endDeviceWrite600V_V2ParameterBlockInfoToFile(const QString & s, const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;

        if ((pPB->parameterBlockFamily == 13) || (pPB->PB.a600V_V2_2ndVPB.versionSuffix[1] == 'F') || (pPB->PB.a600V_V2_2ndVPB.versionSuffix[1] == 'G'))
        {
            qDebug() << " INFO: determined 600V_V2 has memory fix code in it, so calling endDeviceWrite600V_V2_2ndParameterBlockInfoToFile";
            return endDeviceWrite600V_V2_2ndParameterBlockInfoToFile(s, pbDirectoryToWriteTo);
        }
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pb.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);

            out << "barrier:" << pPB->PB.a600V_V2VPB.barrier;
            out << "\tnetID:" << pPB->PB.a600V_V2VPB.netId << "\t" << " bunch:" << pPB->PB.a600V_V2VPB.myBunch;
            out << "\tgroupId:" << pPB->PB.a600V_V2VPB.groupId << Qt::endl;
            out << "mac:" << pPB->PB.a600V_V2VPB.myMac << "\ttimeStamp Read: " << CurrentDateTime <<  Qt::endl;
            out << "dFk0:" << pPB->PB.a600V_V2VPB.dFk[0] << "\tdFk1:" << pPB->PB.a600V_V2VPB.dFk[1] << "\tdFk2:" << pPB->PB.a600V_V2VPB.dFk[2] << "\tdFk3:" << pPB->PB.a600V_V2VPB.dFk[3];
            out << "\tvrefPolynom[0]:" << pPB->PB.a600V_V2VPB.vrefPolynom[0] << "\tvrefPolynom[1]:" << pPB->PB.a600V_V2VPB.vrefPolynom[1] << "\tvrefPolynom[2]:" << pPB->PB.a600V_V2VPB.vrefPolynom[2] << Qt::endl;
            out << "Vout:\tlinearK[0][0]:" << pPB->PB.a600V_V2VPB.linearK[0][0] << "\tlinearK[0][1]:" << pPB->PB.a600V_V2VPB.linearK[0][1] << Qt::endl;
            out << "Vin1:\tlinearK[1][0]:" << pPB->PB.a600V_V2VPB.linearK[1][0] << "\tlinearK[1][1]:" << pPB->PB.a600V_V2VPB.linearK[1][1] << Qt::endl;
            out << "Iout:\tlinearK[2][0]:" << pPB->PB.a600V_V2VPB.linearK[2][0] << "\tlinearK[2][1]:" << pPB->PB.a600V_V2VPB.linearK[2][1] << Qt::endl;
            out << "Vin2:\tlinearK[3][0]:" << pPB->PB.a600V_V2VPB.linearK[3][0] << "\tlinearK[3][1]:" << pPB->PB.a600V_V2VPB.linearK[3][1] << Qt::endl;
            out << "Temp:\tlinearK[4][0]:" << pPB->PB.a600V_V2VPB.linearK[4][0] << "\tlinearK[4][1]:" << pPB->PB.a600V_V2VPB.linearK[4][1] << Qt::endl;
            out << "Iin2:\tlinearK[5][0]:" << pPB->PB.a600V_V2VPB.linearK[5][0] << "\tlinearK[5][1]:" << pPB->PB.a600V_V2VPB.linearK[5][1] << Qt::endl;
            out << "Iin1:\tlinearK[6][0]:" << pPB->PB.a600V_V2VPB.linearK[6][0] << "\tlinearK[6][1]:" << pPB->PB.a600V_V2VPB.linearK[6][1] << Qt::endl;
            out << "fetFailureCount:" << pPB->PB.a600V_V2VPB.fetFailureCount << "\tfetCurrentThreshold:" << pPB->PB.a600V_V2VPB.fetCurrentThreshold << "\tfetDeltaCurrent:" << pPB->PB.a600V_V2VPB.fetDeltaCurrent << Qt::endl;

            out << "oscLowCurrentLimitInmA:" << pPB->PB.a600V_V2VPB.oscLowCurrentLimitInmA;
            out << "\toscDeltaV:" << pPB->PB.a600V_V2VPB.oscDeltaV << "\toscOVStartupDelay:" << pPB->PB.a600V_V2VPB.oscOVStartupDelay;
            out << "\toscAfterStartupDelay:" << pPB->PB.a600V_V2VPB.oscAfterStartupDelay << "\toscLowCurrentOnlyDelay:" << pPB->PB.a600V_V2VPB.oscLowCurrentOnlyDelay << Qt::endl;
            out << "versionSuffix[0]:" << pPB->PB.a600V_V2VPB.versionSuffix[0] << "\tversionSuffix[1]:" << pPB->PB.a600V_V2VPB.versionSuffix[1] << "\tversionSuffix[2]:" << pPB->PB.a600V_V2VPB.versionSuffix[2];
            out << "\ttests:" << pPB->PB.a600V_V2VPB.tests << Qt::endl;

            out << "installDate:" << pPB->PB.a600V_V2VPB.installDate;
            out << "\tk_ov_volt:" << pPB->PB.a600V_V2VPB.k_ov_volt << "\tk_oc_cur:" << pPB->PB.a600V_V2VPB.k_oc_cur;
            out << "\tsyncword:" << pPB->PB.a600V_V2VPB.syncword << Qt::endl;

            out << "vin_disable_radio:" << pPB->PB.a600V_V2VPB.vin_disable_radio;
            out << "\trbunch:" << pPB->PB.a600V_V2VPB.rbunch << "\tgbunch:" << pPB->PB.a600V_V2VPB.gbunch;
            out << "\tshortCircuitLevel:" << pPB->PB.a600V_V2VPB.shortCircuitLevel;
            out << "\treserved:" << pPB->PB.a600V_V2VPB.reserved;
            out << "\tsynch_phase:" << pPB->PB.a600V_V2VPB.synch_phase << "\tsynch_freq:" << pPB->PB.a600V_V2VPB.synch_freq << Qt::endl;
            out << "bandwidth:" << pPB->PB.a600V_V2VPB.bandwidth250;
            out << "\tchannel:" << pPB->PB.a600V_V2VPB.channel;
            out << "\tutcProgram:" << pPB->PB.a600V_V2VPB.utcProgram << "\tutcLow:" << pPB->PB.a600V_V2VPB.utcLow << "\tutcHigh:" << pPB->PB.a600V_V2VPB.utcHigh << Qt::endl;

            out << "tkCurrent:" << pPB->PB.a600V_V2VPB.tkCurrent << "\ttKPower:" << pPB->PB.a600V_V2VPB.tkPower << Qt::endl;

            out << "mpp:" << pPB->PB.a600V_V2VPB.mpp << "\tmodule:" << pPB->PB.a600V_V2VPB.module;
            out << "\tov:" << pPB->PB.a600V_V2VPB.ov << "\toc:" << pPB->PB.a600V_V2VPB.oc << Qt::endl;


            out << "radioPower:" << pPB->PB.a600V_V2VPB.radioPower;
            out << "\tedAddr:" << pPB->PB.a600V_V2VPB.edAddr << "\tgwAddr:" << pPB->PB.a600V_V2VPB.gwAddr;
            out << "\trepeaterChannel:" << pPB->PB.a600V_V2VPB.repeaterChannel << "\trepeaterPower:" << pPB->PB.a600V_V2VPB.repeaterPower << Qt::endl;

            out << "boolByte1:" << pPB->PB.a600V_V2VPB.boolByte1 << Qt::endl;
            out << "\tSearchEnabled:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x80) == 0x80);
            out << "\tSlave:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x40) == 0x40);
            out << "\tRelay:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x20) == 0x20);
            out << "\tHopping Allow:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x10) == 0x10) << Qt::endl;
            out << "\tGateway Channel:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x08) == 0x08);
            out << "\t12kbod:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x04) == 0x04);
            out << "\tensureWDReset:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x02) == 0x02);
            out << "\tproduction:" << ((pPB->PB.a600V_V2VPB.boolByte1 & 0x01) == 0x01) << Qt::endl;

            out << "boolByte2:" << pPB->PB.a600V_V2VPB.boolByte2 << Qt::endl;
            out << "\tReport UTC:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x80) == 0x80);
            out << "\tfuse Comms:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x40) == 0x40);
            out << "\tfuse OVOC:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x20) == 0x20);
            out << "\tuse FEC:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x10) == 0x10) << Qt::endl;
            out << "\tstayInRX:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x08) == 0x08);
            out << "\tSpeculative Report:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x04) == 0x04);
            out << "\t250kbod:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x02) == 0x02);
            out << "\ttry Other Image:" << ((pPB->PB.a600V_V2VPB.boolByte2 & 0x01) == 0x01) << Qt::endl;

            out << "showState:" << pPB->PB.a600V_V2VPB.showState;
            out << "\tCriticalLevel500:" << pPB->PB.a600V_V2VPB.CriticalLevel500 << "\tCriticalLevel10:" << pPB->PB.a600V_V2VPB.CriticalLevel10;
            out << "\tpureOffset:" << pPB->PB.a600V_V2VPB.pureOffset << Qt::endl;

            out << "defCyclesTo500:" << pPB->PB.a600V_V2VPB.defCyclesTo500 << "\tdefCyclesTo10:" << pPB->PB.a600V_V2VPB.defCyclesTo10;
            out << "\tdefCyclesToStep500Channel:" << pPB->PB.a600V_V2VPB.defCyclesToStep500Channel << "\tdefCyclesToStep10Channel:" << pPB->PB.a600V_V2VPB.defCyclesToStep10Channel;
            out << "\tdefCycles2SoftKick:" << pPB->PB.a600V_V2VPB.defCycles2SoftKick << "\tdefCycles2HardKick:" << pPB->PB.a600V_V2VPB.defCycles2HardKick << Qt::endl;

            out << "imageAddr:" << pPB->PB.a600V_V2VPB.imageAddr;
            out << "\tversionLow:" << pPB->PB.a600V_V2VPB.versionLow << "\tversionHigh:" << pPB->PB.a600V_V2VPB.versionHigh;
            out << "\tstarting500Channel:" << pPB->PB.a600V_V2VPB.starting500Channel << Qt::endl;

            out << "prepAddr:" << pPB->PB.a600V_V2VPB.prepAddr;
            out << "\trepStep:" << pPB->PB.a600V_V2VPB.repStep << Qt::endl;

            out << "ov_startup:" << pPB->PB.a600V_V2VPB.ov_startup;
            out << "\tt_mod_off:" << pPB->PB.a600V_V2VPB.t_mod_off << "\toff_fallback:" << pPB->PB.a600V_V2VPB.toff_fallback << "\tton_fallback:" << pPB->PB.a600V_V2VPB.ton_fallback << "\tfallback_time:" << pPB->PB.a600V_V2VPB.fallback_time << Qt::endl;
            out << "network_cnst_1:" << pPB->PB.a600V_V2VPB.network_cnst_1 << "\tnetwork_cnst_2:" << pPB->PB.a600V_V2VPB.network_cnst_2;
            out << "\toc_protection:" << pPB->PB.a600V_V2VPB.oc_protection << "\toc_step" << pPB->PB.a600V_V2VPB.oc_step << Qt::endl;

            out << "cur_noise:" << pPB->PB.a600V_V2VPB.cur_noise;
            out << "\tov_step:" << pPB->PB.a600V_V2VPB.ov_step;
            out << "\tshunt:" << pPB->PB.a600V_V2VPB.shunt;
            out << "\tmax_off:" << pPB->PB.a600V_V2VPB.max_off << Qt::endl;

            out << "vin_limit:" << pPB->PB.a600V_V2VPB.vin_limit << "\tvin_turn_on:" << pPB->PB.a600V_V2VPB.vin_turn_on << "\tvin_switch_off:" << pPB->PB.a600V_V2VPB.vin_switch_off << Qt::endl;
            pbFile.flush();
            pbFile.close();



        }
        emit publishEndDeviceParametersSavedToFile(pbFileName);
    }
    else
    {
        retValue = false;
    }

    return retValue;
}


bool EndDeviceParameterBlockInfoThread::endDeviceWriteParameterBlockInfoAsCharacterDataToFile(const QString & s,const QString & pbDirectoryToWriteTo)
{
    bool retValue = true;

    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    endofParameterBlockStorage = parameterBlocksStorage.end();
    QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
    if (thePBInfo != endofParameterBlockStorage)
    {
        qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
        ParameterBlock_Union * pPB = thePBInfo.value();
        qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
        QString pbFileName(pbDirectoryToWriteTo);
        pbFileName += "/pbRawData.txt";
        QFile pbFile(pbFileName);
        if( !pbFile.open(QFile::WriteOnly | QFile::Text))
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " failed to open file " + pbFileName + ", not saving parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(errString);
            qDebug() << errString;
            retValue = false;
        }
        else
        {
            QTextStream out(&pbFile);
            out << pPB->rawData;
            pbFile.flush();
            pbFile.close();
        }
    }
    else
    {
        retValue = false;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::endDeviceSaveParameterBlockInfo(const QString & s)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString errString(Q_FUNC_INFO);
    QDir pbDirectoryToWriteTo;

    qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " received key of " << s;
    // QString pbKey = macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2) + "_" + QString::number(mainImage[macFlashFamily.at(0)]);
    // Check that user documents exists
    // if so, does AmptGUI_X exist? If not create it
    // does AmptGUI_X/PBs exist?  If not, create it
    if (m_saveParameterBlockPathBase != "")
    {
       QStringList pbPartialKeys = s.split("_");
       if (pbPartialKeys.size() != 4)
       {

           errString += " ERROR: " + CurrentDateTime + " NOT SAVING PB info, number of expected parts (4) of key:" + s + " not received, got " + QString::number(pbPartialKeys.size());
           emit publishEndDeviceParameterBlockInfoThreadError(errString);
           qDebug() << errString;
           retValue = false;
       }
       else
       {
           QString pathToSaveTo(m_saveParameterBlockPathBase);
           QString errString(Q_FUNC_INFO);
           // "mac" portion of path
           pathToSaveTo += "/" + pbPartialKeys.at(0);

           QDir tDir(pathToSaveTo);
           if (! tDir.exists())
           {
               if (tDir.mkdir(".") == false)
               {
                   errString += " ERROR: " + CurrentDateTime + " NOT SAVING PB info, failed to create directory:" + pathToSaveTo;
                   emit publishEndDeviceParameterBlockInfoThreadFlashError(errString);
                   qDebug() << errString;
                   retValue = false;
               }
           }
           else
           {
               // qDebug() << Q_FUNC_INFO << " INFO: directory " << pathToSaveTo << " already exists ...";
           }

           if (retValue == true)
           {
               // qDebug() << Q_FUNC_INFO << " INFO: path of " << pathToSaveTo << " is good to go...";
               if (pbPartialKeys.at(3) == "1")
               {
                   pathToSaveTo += "/MainImage";
               }
               else
               {
                   pathToSaveTo += "8KImage";
               }
               QDir imageDir(pathToSaveTo);
               if (! imageDir.exists())
               {
                   if (imageDir.mkdir(".") == false)
                   {
                       errString += " ERROR: " + CurrentDateTime + " NOT SAVING PB info, failed to create directory:" + pathToSaveTo;
                       emit publishEndDeviceParameterBlockInfoThreadFlashError(errString);
                       qDebug() << errString;
                       retValue = false;
                   }
               }
               else
               {
                   // qDebug() << Q_FUNC_INFO << " INFO: directory " << pathToSaveTo << " already exists ...";
               }
           }

           if (retValue == true)
           {
               // qDebug() << Q_FUNC_INFO << " INFO: path of " << pathToSaveTo << " is good to go...";
               if (pbPartialKeys.at(1) == "1")
               {
                   pathToSaveTo += "/flash";
               }
               else
               {
                   pathToSaveTo += "/memory";
               }
               QDir flashDir(pathToSaveTo);
               if (! flashDir.exists())
               {
                   if (flashDir.mkdir(".") == false)
                   {
                       errString += " ERROR: " + CurrentDateTime + " NOT SAVING PB info, failed to create directory:" + pathToSaveTo;
                       emit publishEndDeviceParameterBlockInfoThreadFlashError(errString);
                       qDebug() << errString;
                       retValue = false;
                   }
               }
               else
               {
                   // qDebug() << Q_FUNC_INFO << " INFO: directory " << pathToSaveTo << " already exists ...";
               }
           }

           if (retValue == true)
           {
               // qDebug() << Q_FUNC_INFO << " INFO: path of " << pathToSaveTo << " is good to go...";

               pathToSaveTo += "/" + CurrentDateTime;

               QDir dateDir(pathToSaveTo);
               if (! dateDir.exists())
               {
                   if (dateDir.mkdir(".") == false)
                   {
                       errString += " ERROR: " + CurrentDateTime + " NOT SAVING PB info, failed to create directory:" + pathToSaveTo;
                       emit publishEndDeviceParameterBlockInfoThreadFlashError(errString);
                       qDebug() << errString;
                       retValue = false;
                   }
                   else
                   {
                       pbDirectoryToWriteTo = dateDir;
                   }
               }
               else
               {
                   // qDebug() << Q_FUNC_INFO << " INFO: directory " << pathToSaveTo << " already exists ...";
                   pbDirectoryToWriteTo = dateDir;
               }
           }
           if (retValue == true)
           {
               endofParameterBlockStorage = parameterBlocksStorage.end();
               QMap<QString, ParameterBlock_Union * >::iterator thePBInfo = parameterBlocksStorage.find(s);
               if (thePBInfo != endofParameterBlockStorage)
               {
                   QString notYet(Q_FUNC_INFO);

                   //qDebug() << Q_FUNC_INFO << " INFO: found pbinfo for key:" << s;
                   ParameterBlock_Union * pPB = thePBInfo.value();
                   //qDebug() << Q_FUNC_INFO << " INFO: parameterBlockFamily" << pPB->parameterBlockFamily ;
                   switch(pPB->parameterBlockFamily)
                   {
                   case Family600V_Shunt:
                       notYet += " ERROR: request to write 600V parameters, not implemented yet, so writing data to file as raw character data...";
                       emit publishEndDeviceParameterBlockInfoThreadError(notYet);
                       qDebug() << notYet;
                       retValue = endDeviceWriteParameterBlockInfoAsCharacterDataToFile(s,pathToSaveTo);
                       break;
                   case Family1000V_Shunt:
                       qDebug() << Q_FUNC_INFO << " INFO: writing parameters for 1000V (" << s << ") to " << pathToSaveTo;
                       retValue = endDeviceWrite1000VParameterBlockInfoToFile(s,pathToSaveTo);
                       break;
                   case Family1300V_Shunt:
                       qDebug() << Q_FUNC_INFO << " INFO: writing parameters for 1300V (" << s << ") to " << pathToSaveTo;
                       retValue = endDeviceWrite1300VParameterBlockInfoToFile(s,pathToSaveTo);
                       break;
                   case Family1300V_2nd_Shunt:
                       qDebug() << Q_FUNC_INFO << " INFO: writing parameters for 1300V_2nw (" << s << ") to " << pathToSaveTo;
                       retValue = endDeviceWrite1300V_2nd_ParameterBlockInfoToFile(s,pathToSaveTo);
                       break;
                   case Family1500V_Shunt:
                       qDebug() << Q_FUNC_INFO << " INFO: writing parameters for 1500V (" << s << ") to " << pathToSaveTo;
                       retValue = endDeviceWrite1500VParameterBlockInfoToFile(s,pathToSaveTo);
                       break;
                   case Family1500V_2nd_Shunt:
                       qDebug() << Q_FUNC_INFO << " INFO: writing parameters for 1500V_2nd (" << s << ") to " << pathToSaveTo;
                       retValue = endDeviceWrite1500V_2nd_ParameterBlockInfoToFile(s,pathToSaveTo);
                       break;

                   case Family600V_V2_Shunt:
                       qDebug() << Q_FUNC_INFO << " INFO: writing parameters for 600V_V2 (" << s << ") to " << pathToSaveTo;
                       retValue = endDeviceWrite600V_V2ParameterBlockInfoToFile(s,pathToSaveTo);
                       break;
                   case Family1500V_30_Shunt:
                       qDebug() << Q_FUNC_INFO << " INFO: writing parameters for 1500V_30 (" << s << ") to " << pathToSaveTo;
                       retValue = endDeviceWrite1500V_30ParameterBlockInfoToFile(s,pathToSaveTo);
                       break;
                   default:
                       notYet += " ERROR: unknown family shunt, cant save/write PB info in 'proper form' for (" + s + "), writing 240 byte data to " + pathToSaveTo;
                       emit publishEndDeviceParameterBlockInfoThreadError(notYet);
                       qDebug() << notYet;
                       retValue = endDeviceWriteParameterBlockInfoAsCharacterDataToFile(s,pathToSaveTo);
                       break;
                   }
               }
               else
               {
                   errString += " ERROR: did not locate data in parameterBlockStorage for key:" + s + ", not writing PB data to file...";
                   emit publishEndDeviceParameterBlockInfoThreadError(errString);
                   qDebug() << errString;
               }
               // OK, now the fun begins, save the PB data in a readable form in directory...
               // use key to get access to structure.
               // use tShunt (and possibly version) to guide how to print out information...
           }
       }
    }
    else
    {
        errString += " ERROR: " + CurrentDateTime + " expected base path to save parameter block information is empty...";
        emit publishEndDeviceParameterBlockInfoThreadError(errString);
        qDebug() << errString;
        retValue = false;
    }

    return retValue;
}

bool EndDeviceParameterBlockInfoThread::validateCorrectFamilyBasedOnShunt(QStringList & optimizerKey, const int & shunt)
{
    bool retValue = true;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    qDebug() << Q_FUNC_INFO << " mac:" << optimizerKey.at(0) << " original memory key portion:" << optimizerKey.at(1) <<
                " original family key portion:" << optimizerKey.at(2) <<
                " shunt:" << shunt << " shuntFamily:" << m_optimizerFamilies[shunt];

    if (optimizerKey.at(2) != m_optimizerFamilies[shunt])
    {
        QString WarningStr(Q_FUNC_INFO);

        WarningStr += " WARNING: " + CurrentDateTime + " Correcting optimizer family in key from " + optimizerKey.at(2) + " to " + m_optimizerFamilies[shunt];
        emit publishEndDeviceParameterBlockInfoThreadFamilyError(WarningStr);
        // qDebug() << WarningStr;
        optimizerKey[2] = m_optimizerFamilies[shunt];
        qDebug() << Q_FUNC_INFO << " Optimizer Key NOW " << optimizerKey.at(0) << optimizerKey.at(1) << optimizerKey.at(2);

        emit publishEndDeviceOptimizerFamily(optimizerKey.at(0), shunt);
        emit publishOptimizerFamilyShunt(shunt);

        if (optimizerKey.at(2) != m_optimizerFamilies[shunt])
        {
            QString ErrString(Q_FUNC_INFO);
            ErrString += " ERROR: " + CurrentDateTime + " change of optimizerFamilies[" + QString(shunt)  + "] did not occur!";
            qDebug() << ErrString;
            emit publishEndDeviceParameterBlockInfoThreadError(ErrString);
        }
    }
    return retValue;
}

void EndDeviceParameterBlockInfoThread::handleOnMainImage(const QString & mac, const bool s)
{
    qDebug() << Q_FUNC_INFO << " mac:" << mac << " on main image:" << QString::number(s) << " inserting into mainImage hash.";
    mainImage.insert(mac,s);
    emit publishEndDeviceOnMainImage(mac,s);
}

bool EndDeviceParameterBlockInfoThread::validateCoeffLineData(const QString mac, const QString coeffLine)
{
   bool ok;

   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
   QString macAndCoeffsListToEmit(mac);
   // qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " entering with mac:" << mac << " coeffLine:" << coeffLine;

   QString temp = coeffLine.mid(0,4);
  //  qDebug() << Q_FUNC_INFO << " INFO: temp is " << temp << " coeffLine.mid(0,4):" << coeffLine.mid(0,4);

   unsigned short unsignedShortWorkspace = 0;
   unsigned char unsignedByte = 0;

   signed short signedShortWorkspace = 0;
   double doubleWorkspace = 0.0;

   hexStringToDecimalUnsignedInt(temp,unsignedShortWorkspace,true);

   // qDebug() << Q_FUNC_INFO << " INFO: first number is " << unsignedShortWorkspace;
   doubleWorkspace = unsignedShortWorkspace / 1000.0;
   // qDebug() << Q_FUNC_INFO << " INFO: first number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',2);

   temp = coeffLine.mid(4,4);
   // qDebug() << Q_FUNC_INFO << " INFO: second temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: second number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace / 1000.0;
   // qDebug() << Q_FUNC_INFO << " INFO: second number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',2 );

   temp = coeffLine.mid(8,4);
   // qDebug() << Q_FUNC_INFO << " INFO: third temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: third number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace / 1000.0;
   // qDebug() << Q_FUNC_INFO << " INFO: third number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',3 );

   temp = coeffLine.mid(12,4);
   // qDebug() << Q_FUNC_INFO << " INFO: fourth temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: fourth number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace / 1000.0;
   // qDebug() << Q_FUNC_INFO << " INFO: fourth number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',2 );

   temp = coeffLine.mid(16,4);
   // qDebug() << Q_FUNC_INFO << " INFO: fifth temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: fifth number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace / 1000.0;
   // qDebug() << Q_FUNC_INFO << " INFO: fifth number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',3 );

   temp = coeffLine.mid(20,4);
   // qDebug() << Q_FUNC_INFO << " INFO: sixth temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: sixth number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace / 1000.0;
   // qDebug() << Q_FUNC_INFO << " INFO: sixth number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',3 );

   temp = coeffLine.mid(24,4);
   // qDebug() << Q_FUNC_INFO << " INFO: seventh temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: seventh number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace;
   // qDebug() << Q_FUNC_INFO << " INFO: seventh number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',1 );

   temp = coeffLine.mid(28,4);
   // qDebug() << Q_FUNC_INFO << " INFO: eigth temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: eigth number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace;
   // qDebug() << Q_FUNC_INFO << " INFO: eigth number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',1 );

   temp = coeffLine.mid(32,4);
   //qDebug() << Q_FUNC_INFO << " INFO: ninth temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: ninth number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace;
   // qDebug() << Q_FUNC_INFO << " INFO: ninth number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',1 );

   temp = coeffLine.mid(36,4);
   // qDebug() << Q_FUNC_INFO << " INFO: tenth temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: tenth number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace;
   // qDebug() << Q_FUNC_INFO << " INFO: tenth number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',1 );

   temp = coeffLine.mid(40,4);
   // qDebug() << Q_FUNC_INFO << " INFO: eleventh temp is " << temp;
   hexStringToDecimalSignedInt(temp,signedShortWorkspace,true);
   // qDebug() << Q_FUNC_INFO << " INFO: eleventh number is " << signedShortWorkspace;
   doubleWorkspace = signedShortWorkspace;
   // qDebug() << Q_FUNC_INFO << " INFO: eleventh number is " << doubleWorkspace;
   macAndCoeffsListToEmit += comma + QString::number(doubleWorkspace,'f',2 );

   temp = coeffLine.mid(44,2);
   // qDebug() << Q_FUNC_INFO << " INFO: eleventh temp is " << temp;
   unsignedByte = static_cast<unsigned char>(temp.toInt(&ok,16));
   // qDebug() << Q_FUNC_INFO << " INFO: eleventh number is " << temp;
   macAndCoeffsListToEmit += comma + QString::number(unsignedByte);

   if (ok == true)
   {
       temp = coeffLine.mid(46,2);
       // qDebug() << Q_FUNC_INFO << " INFO: 12th temp is " << temp;
       unsignedByte = static_cast<unsigned char>(temp.toInt(&ok,16));
       // qDebug() << Q_FUNC_INFO << " INFO: 12th number is " << temp;
       macAndCoeffsListToEmit += comma + QString::number(unsignedByte);

       if (ok == true)
       {
           // qDebug() << Q_FUNC_INFO << "INFO: conversions succssful, macAndCoeffsListToEmit=" << macAndCoeffsListToEmit;
           emit publishEndDeviceValidCoeffLineData(macAndCoeffsListToEmit);
       }
   }

   // qDebug() << Q_FUNC_INFO << "INFO: exiting with retValue of " << ok;


   return ok;
}

void EndDeviceParameterBlockInfoThread::run()
{

  QString parameterBlockData;
  QString coeffLineData;
  QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
  bool ok = false;
 
  m_optimizerFamilies.insert(Family600V_Shunt,Family600V);
  m_optimizerFamilies.insert(Family1000V_Shunt,Family1000V);
  m_optimizerFamilies.insert(Family1300V_Shunt,Family1300V);
  m_optimizerFamilies.insert(Family1500V_Shunt,Family1500V);
  m_optimizerFamilies.insert(Family600V_V2_Shunt,Family600V_V2);
  m_optimizerFamilies.insert(Family1500V_30_Shunt,Family1500V_30);

  // qDebug() << Q_FUNC_INFO << " running...";

  while (m_operational)
    {
      // mutex these operations
      if (m_parsedParameterBlockDataList.isEmpty() == false)
		{
          parameterBlockData = m_parsedParameterBlockDataList.takeFirst();

          // qDebug() << Q_FUNC_INFO << " got PB info to emit and store ... " << parameterBlockData << Qt::endl;

          QStringList keyAndData = parameterBlockData.split(comma);

          if (keyAndData.size() != 2)
          {
              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
              QString ErrorStr = " ERROR: " + CurrentDateTime + " EndDeviceParameterBlockInfoThread had malformed entry of " + parameterBlockData;
              qDebug() << Q_FUNC_INFO << ErrorStr;
              emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
              break;
          }

          QStringList macFlashFamily = (keyAndData.at(0)).split('_');
          if (macFlashFamily.size() != 3)
          {
              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
              QString ErrorStr = " ERROR: " + CurrentDateTime + " EndDeviceParameterBlockInfoThread had malformed key in " + keyAndData.at(0) + " key size is " + macFlashFamily.size();
              qDebug() << Q_FUNC_INFO << ErrorStr;
              emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
              break;
          }

          QString justTheData = keyAndData.at(1);

          // qDebug() << Q_FUNC_INFO << " mac:" << macFlashFamily.at(0) << " flash:" << macFlashFamily.at(1) << " family:" << macFlashFamily.at(2) << " data:" << keyAndData.at(1) << " size of Data: " << (keyAndData.at(1)).size() << Qt::endl;

          QByteArray dataAsByteArray = justTheData.toLocal8Bit();


          // qDebug() << Q_FUNC_INFO << " size of dataAsByteArray: " << dataAsByteArray.size();
          // LBC 07/26/2018 char * buffer = dataAsByteArray.data();
          // qDebug() << Q_FUNC_INFO << " no crashee. ";

          QString tShuntAt = justTheData.mid(470,2);
          int tShunt = tShuntAt.toInt(&ok,16);

          // qDebug() << Q_FUNC_INFO << " INFO: using tSHUNT:" << QString::number(tShunt) << " to choose course of action.";

          if (validateAndPlaceParameterBlockValues(macFlashFamily, justTheData, tShunt) == false)
          {
              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
              QString ErrorStr = " ERROR: " + CurrentDateTime + " unable to place parameter block values for MAC " + macFlashFamily.at(0);
              qDebug() << Q_FUNC_INFO << ErrorStr;
              emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
          }
        } /* END if (m_parsedParameterBlockDataList.isEmpty() == false) */
      else if (m_parsedCoeffLineDataList.isEmpty() == false)
      {
          coeffLineData = m_parsedCoeffLineDataList.takeFirst();
          QStringList keyAndData = coeffLineData.split(comma);

          emit publishEndDeviceReceivedCoeffLineData();

          if (keyAndData.size() != 2)
          {
              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
              QString ErrorStr = " ERROR: " + CurrentDateTime + " EndDeviceParameterBlockInfoThread coefficient line data had malformed entry of " + coeffLineData;
              qDebug() << Q_FUNC_INFO << ErrorStr;
              emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
              break;
          }
          // figure out data
          if (validateCoeffLineData(keyAndData.at(0), keyAndData.at(1)) == true)
          {

          }
      }
	  else
		{
          QThread::msleep(80);
		}
	}

  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";

  emit publishEndDeviceParameterBlockInfoThreadExit();
}

bool EndDeviceParameterBlockInfoThread::validateAndPlaceParameterBlockValues(QStringList &macFlashFamily, QString & justTheData, const int tShunt)
{
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString ErrorStr(Q_FUNC_INFO);
    bool retValue = false;

    if (m_optimizerFamilies.contains(tShunt))
    {
        // qDebug() << Q_FUNC_INFO << " would map raw PB data to a " << m_optimizerFamilies[tShunt] << " type parameter block.";
        switch(tShunt)
        {
        case Family600V_Shunt:
            // Make sure Key is correct (How to store parameter block data mac_family_mem
            ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information (Family600V_Shunt not implemented), cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
            emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
            qDebug() << ErrorStr;
            break;
        case Family1000V_Shunt:
            if (validateCorrectFamilyBasedOnShunt(macFlashFamily,tShunt))
            {
                if ( ! endDeviceParameterBlockInfo1000V( macFlashFamily, justTheData, tShunt ))
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                    qDebug() << ErrorStr;
                }
                else
                {
                    retValue = true;
                }
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " failed validating family based on shunt:" + QString::number(tShunt) + " key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case Family1300V_Shunt:
            if (validateCorrectFamilyBasedOnShunt(macFlashFamily,tShunt))
            {
                if ( ! endDeviceParameterBlockInfo1300V( macFlashFamily, justTheData, tShunt ))
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                    qDebug() << ErrorStr;
                }
                else
                {
                    retValue = true;
                }
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " failed validating family based on shunt:" + QString::number(tShunt) + " key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case Family1300V_2nd_Shunt:
            if (validateCorrectFamilyBasedOnShunt(macFlashFamily,tShunt))
            {
                if ( ! endDeviceParameterBlockInfo1300V_2nd( macFlashFamily, justTheData, tShunt ))
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                    qDebug() << ErrorStr;
                }
                else
                {
                    retValue = true;
                }
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " failed validating family based on shunt:" + QString::number(tShunt) + " key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case Family1500V_Shunt:
            if (validateCorrectFamilyBasedOnShunt(macFlashFamily,tShunt))
            {
                if ( ! endDeviceParameterBlockInfo1500V( macFlashFamily, justTheData, tShunt ))
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                    qDebug() << ErrorStr;
                }
                else
                {
                    retValue = true;
                }
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " failed validating family based on shunt:" + QString::number(tShunt) + " key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case Family1500V_2nd_Shunt:
            if (validateCorrectFamilyBasedOnShunt(macFlashFamily,tShunt))
            {
                if ( ! endDeviceParameterBlockInfo1500V_2nd( macFlashFamily, justTheData, tShunt ))
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                    qDebug() << ErrorStr;
                }
                else
                {
                    retValue = true;
                }
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " failed validating family based on shunt:" + QString::number(tShunt) + " key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case Family1500V_30_Shunt:
            if (validateCorrectFamilyBasedOnShunt(macFlashFamily,tShunt))
            {
                if ( ! endDeviceParameterBlockInfo1500V_30( macFlashFamily, justTheData, tShunt ))
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                    qDebug() << ErrorStr;
                }
                else
                {
                    retValue = true;
                }
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " failed validating family based on shunt:" + QString::number(tShunt) + " key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        case Family600V_V2_Shunt:
            if (validateCorrectFamilyBasedOnShunt(macFlashFamily,tShunt))
            {
                if ( ! endDeviceParameterBlockInfo600V_V2( macFlashFamily, justTheData, tShunt ))
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " failed mapping PB information, cannot store PB info for partial key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                    qDebug() << ErrorStr;
                }
                else
                {
                    retValue = true;
                }
            }
            else
            {
                ErrorStr += " ERROR: " + CurrentDateTime + " failed validating family based on shunt:" + QString::number(tShunt) + " key:" + macFlashFamily.at(0) + "_" + macFlashFamily.at(1) + "_" + macFlashFamily.at(2);
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                qDebug() << ErrorStr;
            }
            break;
        default:
            ErrorStr += " ERROR: " + CurrentDateTime + " Cannot locate optimizer family for shunt " + QString::number(tShunt) + " to map parameter block information.";
            emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
            qDebug() << ErrorStr;
            break;
        }
    }
    else
    {
        ErrorStr += " ERROR: " + CurrentDateTime + " Cannot locate shunt " + QString::number(tShunt) + " in m_optimizerFamilies, cannot display parameter block info for " + macFlashFamily.at(0);
        emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
    return retValue;
}

void EndDeviceParameterBlockInfoThread::setEndDeviceParameterBlockInfoThreadLogging( bool logging )
{
    m_logData = logging;
}


void EndDeviceParameterBlockInfoThread::setParameterBlockReadFrom(const bool s)
{
    m_parametersReadFromFlash = s;
    // qDebug() << Q_FUNC_INFO << " Read from: " << s << Qt::endl;
}


void EndDeviceParameterBlockInfoThread::handleParametersReadFromChange( const bool s)
{
    qDebug() << Q_FUNC_INFO << " reading from flash:" << s;
    m_parametersReadFromFlash = s;
}


void EndDeviceParameterBlockInfoThread::handleSelectedMACChange(const QString & theMAC)
{
  qDebug() << Q_FUNC_INFO << " informed on change in active MAC of " << theMAC;
}

void EndDeviceParameterBlockInfoThread::handleTerminate( void )
{
    qDebug() << Q_FUNC_INFO << " begin ...";
    m_mutex.lock();
    m_parsedParameterBlockDataList.clear();
    m_operational = false;
    qDebug() << Q_FUNC_INFO << " Size of parameterBlocksStorage:" <<  parameterBlocksStorage.size();
    int success = NO_ERROR;

    if (parameterBlocksStorage.size() > 0)
    {

        endofParameterBlockStorage = parameterBlocksStorage.end();
        QMap<QString, ParameterBlock_Union *>::iterator iter = parameterBlocksStorage.begin();
        QString pbKey("");
        ParameterBlock_Union * pbUnion = nullptr;

        QString currentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        QString docsDirectory = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0);
        QString pbDirectory = docsDirectory + "/AmptGUI_X/ParameterBlockData/"; // + currentDateTime;

        if (! QDir(pbDirectory).exists())
        {
            if (QDir().mkdir(pbDirectory))
            {
              qDebug() << Q_FUNC_INFO << " successfully created parameter block directory " << pbDirectory;
              pbDirectory += currentDateTime + "/";
              if ( ! QDir(pbDirectory).exists())
              {
                  if (QDir().mkdir(pbDirectory))
                  {
                    qDebug() << Q_FUNC_INFO << " successfully created parameter block directory " << pbDirectory;
                  }
                  else
                  {
                    qDebug() << Q_FUNC_INFO << " failed to create parameter block directory " << pbDirectory;
                    QString ErrorStr = QString(Q_FUNC_INFO) + " ERROR: " + currentDateTime + " failed to create parameter block directory:" + pbDirectory;
                    success = ERROR_CREATING_DIRECTORY;
                    emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                  }
              }
            }
            else
            {
              qDebug() << Q_FUNC_INFO << " failed to create parameter block directory " << pbDirectory;
              QString ErrorStr = QString(Q_FUNC_INFO) + " ERROR: " + currentDateTime + " failed to create parameter block directory:" + pbDirectory;
              success = ERROR_CREATING_DIRECTORY;
              emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);

            }
        }
        else
        {
          // qDebug() << Q_FUNC_INFO << " parameter block directory " << pbDirectory << " already exists, proceeding ...";
          pbDirectory += currentDateTime + "/";
          if ( ! QDir(pbDirectory).exists())
          {
              if (QDir().mkdir(pbDirectory))
              {
                qDebug() << Q_FUNC_INFO << " successfully created parameter block directory " << pbDirectory;
              }
              else
              {
                qDebug() << Q_FUNC_INFO << " failed to create parameter block directory " << pbDirectory;
                QString ErrorStr = QString(Q_FUNC_INFO) + " ERROR: " + currentDateTime + " failed to create parameter block directory:" + pbDirectory;
                success = ERROR_CREATING_DIRECTORY;
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
              }
          }
          else
          {
              // qDebug() << Q_FUNC_INFO << " parameter block directory " << pbDirectory << " already exists, proceeding ...";
          }

        }


        for (iter = parameterBlocksStorage.begin(); iter != endofParameterBlockStorage && success == NO_ERROR; ++iter)
        {
            pbKey = iter.key();
            pbUnion = iter.value();

            qDebug() << Q_FUNC_INFO << " INFO: pbKey -> " << pbKey;
            QString aPBFileName = pbDirectory + "/" + pbKey + ".txt";
            QFile aPBFile(aPBFileName);
            if (aPBFile.open(QIODevice::WriteOnly | QIODevice::Text) == true)
            {
                qDebug() << Q_FUNC_INFO << " INFO: ready to write ...";
                // QTextStream tOut(&aPBFile);

                // tOut << "BBBBBBB\n";

                // tOut << QString::number(pbUnion->parameterBlockFamily) << "\n";
                // if (pbUnion->parameterBlockFamily == Family600V_V2_2nd)
                // {
                    // tOut << QString::number(pbUnion->PB.a600V_V2_2ndVPB.barrier);
                // }
                QDataStream out(&aPBFile);


                //QByteArray pbByteArray;
                // QDataStream out(&aPBFile);
                out.setVersion(QDataStream::Qt_5_12);

                out << pbUnion;
                qDebug() << Q_FUNC_INFO << " INFO: out:" << aPBFile.size();

                aPBFile.flush();
                aPBFile.close();
            }
            else
            {
                QString ErrorStr = QString(Q_FUNC_INFO) + " ERROR: " + currentDateTime + " failed to create file: " + aPBFileName;
                qDebug() << ErrorStr;
                emit publishEndDeviceParameterBlockInfoThreadError(ErrorStr);
                success = ERROR_OPENING_PBFILE;
            }
            // Create file to write to under pbDirectory, named pbKey,
            // the contents of the file will be the structure (value) binary file
                    /*;
            pPB->parameterBlockFamily = tShunt;
            pPB->PB.a1500VPB = a1500VPB;  // LBC does this do a "deep copy"?
            pPB->rawData = justTheData;
            parameterBlocksStorage.insert(pbKey,pPB);
                    */
        }
    }
    m_mutex.unlock();
    qDebug() << Q_FUNC_INFO << " end ...";
}

