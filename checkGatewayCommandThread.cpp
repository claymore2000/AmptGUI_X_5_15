/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QDebug>

#include "checkGatewayCommandThread.h"
#include "amptRegisterConstants.h"

static const int ByteRegisterChannelFlag = 1;
static const int ByteRegisterMpp = 4;
static const int ByteRegisterModule = 5;
static const int ByteRegisterStayInRx = 13;
static const int ByteRegisterMACByteZero = 16;
static const int ByteRegisterMACByteOne = 17;
static const int ByteRegisterMACByteTwo = 18;
static const int ByteRegisterMACByteThree = 19;
static const int ByteRegisterMACByteFour = 20;
static const int ByteRegisterMACByteFive = 21;
static const int ByteRegisterOVLimit = 22;
static const int ByteRegisterOCLimit = 23;
static const int ByteRegisterBaseChannel = 26;
static const int ByteRegisterWriteEntirePBToFlash = 28;
static const int ByteRegisterDisbandNetwork = 31;
static const int ByteRegisterReadPBFromRAM = 32;
static const int ByteRegisterWriteMostPBToFlash = 33;
static const int ByteRegisterEDRadioPower = 36;
static const int ByteRegisterEDFrequencyHopping = 40;
static const int ByteRegisterIsRepeater = 41;
static const int ByteRegisterIsSlave = 42;
static const int ByteRegisterRepeaterChannel = 43;
static const int ByteRegisterRepeaterPower = 44;
static const int ByteRegisterSearchModeEnabled = 45;
static const int ByteRegisterEndOfTest = 49;
static const int ByteRegisterSynchronizeMPPCycles = 51;
static const int ByteRegisterSetStartSlaveChannel = 53;
static const int ByteRegisterCheckFlash = 55;
static const int ByteRegisterSwitchSecurity = 56;
static const int ByteRegisterReportParameterBlockFromFlash = 57;
static const int ByteRegisterCalibrationRepeat = 58;
static const int ByteRegisterRepeaterSlaveBaudRate = 59;
static const int ByteRegisterRepeaterStep = 61;
static const int ByteRegisterOVStartup = 62;
static const int ByteRegisterOCFallback = 63;
static const int ByteRegisterToffFallback = 64;
static const int ByteRegisterTonFallback = 65;
static const int ByteRegisterFallbackTime = 66;
static const int ByteRegisterNetCnst1 = 67;
static const int ByteRegisterNetCnst2 = 68;
static const int ByteRegisterT_OC_Jump = 69;
static const int ByteRegisterOCStep = 70;
static const int ByteRegisterOVStep = 73;
static const int ByteRegisterShunt = 74;
static const int ByteRegisterMaxOff = 75;
static const int ByteRegisterVinDisableRadio = 79;
static const int ByteRegisterNumberOfBunchesBeforeRepeat = 80;
static const int ByteRegisterGlobalBunchNumber = 81;
static const int ByteRegisterOCShortCircuitLimit = 82;
static const int ByteRegisterFuseCommunication = 83;
static const int ByteRegisterFuseOVandOC = 84;
static const int ByteRegisterSyncPhase = 93;
static const int ByteRegisterSyncFrequency = 94;
static const int ByteRegisterTempCalibrate = 96;
static const int ByteRegisterSetMPPCycle = 97;
static const int ByteRegisterWriteMainPBUsing8KPB = 110;
static const int ByteRegisterWriteAllMainPBUsing8KPB = 111;
static const int ByteRegisterReadMainPBFrom8KFlash = 112;
static const int ByteRegisterReadCoefficients = 113;
static const int ByteRegisterSet_MFTimer1 = 114;
static const int ByteRegisterSet_MFTimer2 = 115;
static const int ByteRegisterSet_MFTimer2MPPOffCyclesAndTimesToCycle = 116;
static const int ByteRegisterSet_MonitoringNetStatus = 117;
static const int ByteRegisterSet_EFOccurrenceThreshold = 118;
static const int ByteRegisterSet_EFCountDownTimer = 119;
static const int ByteRegisterSet_EFAlphaNumerator = 120;
static const int ByteRegisterClear_EFModuleOff = 121;
static const int ByteRegisterSet_IinLimitOCSteps = 122;
static const int ByteRegisterSet_IinLimitOCDelay = 123;
static const int ByteRegisterSet_IinLimitTempAmbientAdjust = 124;

static const int ShortIntegerRegisterGroupID = 1;
static const int ShortIntegerRegisterNetworkID = 2;
static const int ShortIntegerRegisterGWEDAddress = 3;
static const int ShortIntegerRegisterSearchCycles_C2 = 4;
static const int ShortIntegerRegisterSearchCycles_C4 = 5;
static const int ShortIntegerRegisterSearchCycles_C3 = 6;
static const int ShortIntegerRegisterSearchCycles_C1 = 7;
static const int ShortIntegerRegisterSearchCycles_SoftKick = 8;
static const int ShortIntegerRegisterSearchCycles_Restart = 9;
static const int ShortIntegerRegisterSetImageAddress = 10;
static const int ShortIntegerRegisterSetVersionLowMain = 11;
static const int ShortIntegerRegisterSetVersionHigh8K = 12;
static const int ShortIntegerRegisterBootImage = 13;
static const int ShortIntegerRegisterSyncWord = 14;
static const int ShortIntegerRegisterCurrentNoise = 17;
static const int ShortIntegerRegisterMicroOffset = 18;
static const int ShortIntegerRegisterOscLowCurrentLimitInmA = 19;
static const int ShortIntegerRegisterSetLowCurrentLimitTo255 = 19; /* 1300V, 1500V */
static const int ShortIntegerRegisterOscDeltaVolts = 20;
static const int ShortIntegerRegisterSetVhvLimitVout = 20;         /* 1300V */
static const int ShortIntegerRegisterOscOVStartupDelay = 21;
static const int ShortIntegerRegisterSetIhvLimitVout = 21;         /* 1300V */
static const int ShortIntegerRegisterOscAfterStartupDelay = 22;
static const int ShortIntegerRegisterSetVhvLimitVins = 22;         /* 1300V */
static const int ShortIntegerRegisterOscLowCurrentOnlyDelay = 23;
static const int ShortIntegerRegisterSetIhvLimitVins = 23;         /* 1300V */
static const int ShortIntegerRegisterReadOnePBRow = 24;
static const int ShortIntegerRegisterVoutOV = 24;                  /* 600V */
static const int ShortIntegerRegisterSetPBByte = 25;
static const int ShortIntegerRegisterIoutOC = 25;                  /* 600V */
static const int ShortIntegerRegisterFETFailureCount = 26;
static const int ShortIntegerRegisterFETCurrentThreshold = 27;
static const int ShortIntegerRegisterFETDelta = 28;
static const int ShortIntegerRegisterSetVoutLimitCount = 33;
static const int ShortIntegerRegisterSetVoutLimit = 34;
static const int ShortIntegerRegisterSetIoutLimitCount = 35;
static const int ShortIntegerRegisterSetIoutLimit = 36;
static const int ShortIntegerRegisterSetMFV_OV = 37;
static const int ShortIntegerRegisterSetMFI_OC = 38;
static const int ShortIntegerRegisterSet_EFInputCurrentThreshold = 39;
static const int ShortIntegerRegisterSet_IinLimit = 40;

static const int FloatRegisterDFK0 = 1;
static const int FloatRegisterDFK1 = 2;
static const int FloatRegisterDFK2 = 3;
static const int FloatRegisterDFK3 = 4;
static const int FloatRegisterTK_CUR = 5;
static const int FloatRegisterTK_POW = 6;
static const int FloatRegisterLinearCoefficientVout = 10;
static const int FloatRegisterLinearOffsetVout = 11;
static const int FloatRegisterLinearCoefficientVin1 = 12;
static const int FloatRegisterLinearOffsetVin1 = 13;
static const int FloatRegisterLinearCoefficientIout = 14;
static const int FloatRegisterLinearOffsetIout = 15;
static const int FloatRegisterLinearCoefficientVin2 = 16;
static const int FloatRegisterLinearOffsetVin2 = 17;
static const int FloatRegisterLinearCoefficientText = 18;
static const int FloatRegisterLinearOffsetText = 19;
static const int FloatRegisterLinearCoefficientIin2 = 20;
static const int FloatRegisterLinearOffsetIin2 = 21;
static const int FloatRegisterLinearCoefficientIin1 = 22;
static const int FloatRegisterLinearOffsetIin1 = 23;
static const int FloatRegisterVRef0 = 24;
static const int FloatRegisterKVRef = 25;
static const int FloatRegisterT0 = 26;

static const QString EndOfCommandProseForMACCommand(" for the optimizer with MAC ");
static const QString EndOfCommandProseForBroadcastCommand(" for all optimizers?");
static const QString EndOfCommandProseForGroupCommand(" for all optimizers in Group ");
static const QString EndOfCommandProseForNetworkCommand(" for the optimizer with Networl Address ");



CheckGatewayCommandThread::CheckGatewayCommandThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true;
}

CheckGatewayCommandThread::~CheckGatewayCommandThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void CheckGatewayCommandThread::stopCheckGatewayCommandThreadOperation( void )
{
    m_operational = false;
}


void CheckGatewayCommandThread::startCheckGatewayCommandThreadInterface(int waitTimeout, const bool logging)
{
    const QMutexLocker locker(&m_mutex);
    m_waitTimeout = waitTimeout;
    m_logData = logging;
	m_operational = true;

	if (m_logData)
	  {
		// Create name, try to open for write,
	  }

    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

void CheckGatewayCommandThread::handleCheckingAGatewayCommand(const QString & type, const QString & command)
{
  qDebug() << Q_FUNC_INFO << " queuing command type " << type << " and command " << command;
  QString toCheck = type + "," + command;

  m_mutex.lock();
  m_gatewayCommandsToValidateList.append(toCheck);
  m_mutex.unlock();

  qDebug() << Q_FUNC_INFO << " queued " << toCheck;
}

void CheckGatewayCommandThread::handleValidatingFormatOfEndDeviceCommand(const QString & command)
{
    qDebug() << Q_FUNC_INFO << " queuing end device command to validate " << command;
    m_endDeviceCommandsToValidateList.append(command);
}


void::CheckGatewayCommandThread::validateCommandToGateway(QString s)
{
    qDebug() << Q_FUNC_INFO << s << " length:" << s.length();
    s = s.trimmed();

    QString ErrorStr(Q_FUNC_INFO);
    ErrorStr += " ERROR: Invalid command " + s;
    QString commandProse("");



    qDebug() << Q_FUNC_INFO << s << " length:" << s.length();

    const QChar firstChar = s.at(0);
    qDebug() << Q_FUNC_INFO << " first char is " << firstChar;

    bool ok = false;

    if (firstChar == 'A')
    {

    }
    else if (firstChar == 'B')
    {
        (s.mid(2)).toInt(&ok,16);
        if (((s.length() == 5) || (s.length() == 6)) && (ok == true))
        {
            int gwAddr = 0;
            int edAddr = 0;

            if (s.length() == 5)
            {
                gwAddr = (s.mid(2,1)).toInt(&ok,16);
                edAddr = (s.mid(3)).toInt(&ok,16);
                commandProse += "Do you wish to set the Gateway to GW Addr of " + QString::number(gwAddr,16) + "(hex) and ED Addr of " + QString::number(edAddr,16) + "(hex)?";

                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                gwAddr = (s.mid(2,2)).toInt(&ok,16);
                edAddr = (s.mid(4)).toInt(&ok,16);
                commandProse += "Do you wish to set the Gateway to GW Addr of " + QString::number(gwAddr,16) + " and ED Addr of " + QString::number(edAddr,16) + "?";

                emit publishValidateCommandToUser(commandProse,s);
            }

        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'd')
    {
        int zeroOrOne = (s.mid(2)).toInt(&ok,10);
        if (((s.length() == 3) && (ok == true) && (zeroOrOne == 0)) || (zeroOrOne == 1))
        {
            commandProse += "Do you wish to turn ";
            if (zeroOrOne)
            {
                commandProse += " bunch 255 (machine gun mode) on?";
            }
            else
            {
                commandProse += " bunch 255 (machine gun mode) off?";
            }
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'E')
    {
        int zeroOrOne = (s.mid(2)).toInt(&ok,10);
        if (((s.length() == 3) && (ok == true) && (zeroOrOne == 0)) || (zeroOrOne == 1))
        {           
            commandProse += "Do you wish to turn ";
            if (zeroOrOne)
            {
                commandProse += " Echo on?";
            }
            else
            {
                commandProse += " Echo off?";
            }
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'G')
    {
        if (s.length() == 1)
        {
            commandProse += "Do you wish to write the Gateway Parameters to Flash?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'H')
    {
        int zeroOrOne = (s.mid(2)).toInt(&ok,10);
        if (((s.length() == 3) && (ok == true) && (zeroOrOne == 0)) || (zeroOrOne == 1))
        {
            commandProse += "Do you wish to turn ";
            if (zeroOrOne)
            {
                commandProse += " on Hopping?";
            }
            else
            {
                commandProse += " off Hopping?";
            }
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'h')
    {
        int minusToPlus255 = (s.mid(2)).toInt(&ok,10);
        if ((ok == true) && (minusToPlus255 > -256) && (minusToPlus255 <= 255))
        {
            if (minusToPlus255 < 0)
            {
                commandProse += "Do you wish to set the Gateway Base Channel (only) to " + QString::number(minusToPlus255) + "?";
            }
            else
            {
                commandProse += "Do you wish to set the Gateway and End Devices Base Channel to " + QString::number(minusToPlus255) + "?";
            }
            publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'I')
    {
        if (s.length() == 1)
        {
            commandProse += "Do you wish to determine if Gateway can boot over USB or if SDAG is at bootloader?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'i')
    {
        if (s.length() == 1)
        {
            commandProse += "Do you wish to print out some of the gateway parameters?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'j')
    {
        int value = (s.mid(3)).toInt(&ok,10);

        if ((s.length() > 3) && (s.length() < 6) && (ok == true) && (value >= 0) && ((s.at(2) == 's') || (s.at(2) == 'm') || (s.at(2) == 'h') || (s.at(2) == 'd')))
        {
            QString duration("seconds");

            if (s.at(2) == 'm')
            {
                duration = "minutes";
            }
            else if (s.at(2) == 'h')
            {
                duration = "hours";
            }
            else if (s.at(2) == 'd')
            {
                duration = "days";
            }
            commandProse += "Do you wish to enter join mode for " + QString::number(value) + " " + duration +"?";
            emit publishValidateCommandToUser(commandProse, s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'K')
    {
        if (s.length() >= 5)
        {
            int operation = (s.mid(2,1)).toInt(&ok,10);
            qDebug() << Q_FUNC_INFO << " operation is " << operation;

            if ((operation >= 0) && (operation <= 5))
            {
                emit validatedCommand(s);
            }
            else if (operation == 6) // bunch size
            {
                int value = (s.mid(4)).toInt(&ok,10);
                if ((ok == true) && (value >= 1) && (value <= 16))
                {
                    commandProse += "Do you wish to set the bunch size to " + QString::number(value) + "?";
                    publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                }
            }
            else if (operation == 7)
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
            else if (operation == 8)
            {
                int value = (s.mid(4)).toInt(&ok,10);
                if ((ok == true) && (value >= 1) && (value <= 16))
                {
                    commandProse += "Do you wish to set the BOA bunch size to " + QString::number(value) + " (default is 2)?";
                    emit publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                }
            }
            else if (operation == 9)
            {
                int value = (s.mid(4)).toInt(&ok,10);
                if ((ok == true) && (value >= 0) && (value <= 1))
                {
                    commandProse += "Do you wish to turn ";
                    if (value)
                    {
                        commandProse += " on Super Cycles?";
                    }
                    else
                    {
                        commandProse += " off Super Cycles?";
                    }
                    emit publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                }
            }
            else if (operation == 10)
            {
                int value = (s.mid(4)).toInt(&ok,16);
                if (ok == true)
                {
                    commandProse += "Do you wish to set the Gateway (only) Syncword to " + QString::number(value,16) + "?";
                    publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                }
            }
            else if (operation == 11)
            {
                int value = (s.mid(4)).toInt(&ok,10);
                if ((ok == true) && (value >= 0) && (value <= 6))
                {
                    QString transmitOn(" Omni Antenna Pair only?");
                    if (value == 1)
                    {
                        transmitOn = " Patch Antenna Pair only?";
                    }
                    else if (value == 2)
                    {
                        transmitOn = " All Four Antennas?";
                    }
                    else if (value == 3)
                    {
                        transmitOn = " Omni Antenna 0 only?";
                    }
                    else if (value == 4)
                    {
                        transmitOn = " Omni Antenna 1 only?";
                    }
                    else if (value == 5)
                    {
                        transmitOn = " Patch Antenna 0 only?";
                    }
                    else if (value == 6)
                    {
                        transmitOn = " Patch Antenna 1 only?";
                    }
                    commandProse += " Do you wish to set the SDAG to transmit using" + transmitOn;
                    publishValidateCommandToUser(commandProse, s);
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                }
            }
            else if (operation == 12)
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
            else if (operation == 13)
            {
                int value = (s.mid(4)).toInt(&ok,10);
                if ((ok == true) && (value >= 0) && (value <= 1))
                {
                    commandProse += "Do you wish to turn ";
                    if (value)
                    {
                        commandProse += " on RF Coprocessor Diagnostics (SDAG Only)?";
                    }
                    else
                    {
                        commandProse += " off RF Coprocessor Diagnostics (SDAG Only)?";
                    }
                    emit publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                }
            }
            else if (operation == 14)
            {
                int value = (s.mid(4)).toInt(&ok,10);
                if ((ok == true) && (value >= 0) && (value <= 1))
                {
                    commandProse += "Do you wish to set ";
                    if (value)
                    {
                        commandProse += " Gateway baud rate to 2.4 kbaud?";
                    }
                    else
                    {
                        commandProse += " Gateway baud rate to 12 kbaud (default)?";
                    }
                    emit publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                }
            }

            else
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }

        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'k')
    {
        int networkSize = (s.mid(2)).toInt(&ok,10);
        if ((ok == true) && (networkSize >=0) && (networkSize < 4080))
        {
            commandProse += "Do you wish to set the network size to " + QString::number(networkSize) + "?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'L')
    {
        int zeroOrOne = (s.mid(2)).toInt(&ok,10);
        if (((s.length() == 3) && (ok == true) && (zeroOrOne == 0)) || (zeroOrOne == 1))
        {
            commandProse += "Do you wish to turn";
            if (zeroOrOne == 0)
            {
                commandProse += " on ED Short Format Output?";
            }
            else
            {
                commandProse += " on ED Long Format Output?";
            }
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'N')
    {
        if (s.length() == 30)
        {
            commandProse += "Do you wish to send the MAC specific commissioning command?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'n')
    {
        if (s.length() == 1)
        {
            commandProse += "Do you wish to disband the network?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'O')
    {
        if (s.length() == 1)
        {
            commandProse += "Do you wish to print out the Gateway Scaling Coefficients (No meaning on SDAG)?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'Y')
    {
        int zeroThrough4 = (s.mid(2)).toInt(&ok,10);
        if ((s.length() == 3) && (ok == true) && (zeroThrough4 >= 0) && (zeroThrough4 <= 4))
        {
            QString transmit = " listen only?";
            if (zeroThrough4 == 1)
            {
                transmit = " normal (transmit and receive)?";
            }
            else if ((zeroThrough4 >= 2) && (zeroThrough4 <=4))
            {
                transmit = " FCC Testing Mode:" + QString::number(zeroThrough4) + "?";
            }
            commandProse += "Do you wish to set the Gateway Antenna to" + transmit;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == 'z')
    {
        int oneThrough255 = (s.mid(2)).toInt(&ok,10);
        if ((s.length() <= 5) && (ok == true) && (oneThrough255 > 0) && (oneThrough255 <= 255))
        {
            commandProse += "Do you wish to repeat Gateway Commands " + QString::number(oneThrough255) + " times?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else if (firstChar == '?')
    {
        if (s.length() == 1)
        {
            commandProse += "Do you wish to print out full set of Gateway Parameters?";
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
        }
    }
    else
    {
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
    }

}

bool CheckGatewayCommandThread::confirmFloatRegisterNumberAndValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & s)
{
    bool ok = true;
    int floatRegisterNumber = amptRegister.toInt(&ok,10);
    QString ErrorStr(Q_FUNC_INFO);

    if ((ok == true) && (floatRegisterNumber > 0) && (floatRegisterNumber <= FloatRegisterT0))
    {
        //float valueToSetAmptRegister = 0.0;

        if (commandType == FloatRegisterCommand)
        {
            float valueToSetAmptRegister = amptRegisterValue.toFloat(&ok);
            if (ok == false)
            {
                if (ok == false)
                {
                    ErrorStr += " ERROR: Converting Register Value " + amptRegisterValue + " to float value, got " + QString::number(static_cast<double>(valueToSetAmptRegister));
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
            }
        }
        else
        {
            ErrorStr += " ERROR: Invalid Float Register Command Type:" + commandType;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        QString endOfCommandProse("");

        if (s.mid(2,1) == "m")
        {
            endOfCommandProse += EndOfCommandProseForMACCommand + s.mid(3,12) + "?";
        }
        else if (s.mid(2,1) == "*")
        {
            endOfCommandProse += EndOfCommandProseForBroadcastCommand;
        }
        else if (s.mid(2,1) == "s")
        {
            endOfCommandProse += EndOfCommandProseForGroupCommand + s.mid(3,4) + "?";
        }
        else if (s.mid(2,1) == "#")
        {
            endOfCommandProse += EndOfCommandProseForNetworkCommand + s.mid(3,3) + "?";
        }
        else
        {
            ErrorStr += " ERROR: Invalid float Register Command Type:" + commandType;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        QString commandProse("");

        if (floatRegisterNumber == FloatRegisterDFK0)
        {
            commandProse += "Do you wish to set the DFK0 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterDFK1)
        {
            commandProse += "Do you wish to set the DFK1 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterDFK2)
        {
            commandProse += "Do you wish to set the DFK2 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterDFK3)
        {
            commandProse += "Do you wish to set the DFK3 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterTK_CUR)
        {
            commandProse += "Do you wish to set the Temperature Coefficient for Current value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterTK_POW)
        {
            commandProse += "Do you wish to set the Temperature Coefficient for Power value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearCoefficientVout)
        {
            commandProse += "Do you wish to set the Linear Coefficient for Vout value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearOffsetVout)
        {
            commandProse += "Do you wish to set the Linear Offset for Vout value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearCoefficientVin1)
        {
            commandProse += "Do you wish to set the Linear Coefficient for Vin1 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearOffsetVin1)
        {
            commandProse += "Do you wish to set the Linear Offset for Vin1 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearCoefficientIout)
        {
            commandProse += "Do you wish to set the Linear Coefficient for Iout value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearOffsetIout)
        {
            commandProse += "Do you wish to set the Linear Offset for Iout value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearCoefficientVin2)
        {
            commandProse += "Do you wish to set the Linear Coefficient for Vin2 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearOffsetVin2)
        {
            commandProse += "Do you wish to set the Linear Offset for Vin2 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearCoefficientText)
        {
            commandProse += "Do you wish to set the Linear Coefficient for External Temperature value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearOffsetText)
        {
            commandProse += "Do you wish to set the Linear Offset for External Temperature value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearCoefficientIin2)
        {
            commandProse += "Do you wish to set the Linear Coefficient for Iin2 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearOffsetIin2)
        {
            commandProse += "Do you wish to set the Linear Offset for Iin2 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearCoefficientIin1)
        {
            commandProse += "Do you wish to set the Linear Coefficient for Iin1 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterLinearOffsetIin1)
        {
            commandProse += "Do you wish to set the Linear Offset for Iin1 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterVRef0)
        {
            commandProse += "Do you wish to set the Quadratic Polynomial for VRef0 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterKVRef)
        {
            commandProse += "Do you wish to set the Quadratic Polynomial for KVRef value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (floatRegisterNumber == FloatRegisterT0)
        {
            commandProse += "Do you wish to set the Quadratic Polynomial for T0 (degrees C) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            ErrorStr += " ERROR: Invalid or Unrecognized Float Register Number:" + amptRegister;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }
    }
    else
    {
        ErrorStr += " ERROR: Invalid or Unrecognized Float Register Number (Out Of Range):" + amptRegister;
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
        return false;
    }
    return true;
}

bool CheckGatewayCommandThread::confirmShortIntegerRegisterNumberAndValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & s)
{
    bool ok = true;
    int shortIntegerRegisterNumber = amptRegister.toInt(&ok,10);
    QString ErrorStr(Q_FUNC_INFO);

    if ((ok == true) && (shortIntegerRegisterNumber > 0) && (shortIntegerRegisterNumber <= ShortIntegerRegisterSet_IinLimit)) // LBC what is maximum value?
    {
        int valueToSetAmptRegister = 0;
        if (commandType == ShortIntegerRegisterCommand)
        {
            valueToSetAmptRegister = amptRegisterValue.toInt(&ok,10);
            if (ok == false)
            {
                ErrorStr += " ERROR: Converting Register Value " + amptRegisterValue + " to decimal value, got " + QString::number(valueToSetAmptRegister);
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else if (commandType == ShortIntegerRegisterCommandInHex)
        {
            valueToSetAmptRegister = amptRegisterValue.toInt(&ok,16);
            if (ok == false)
            {
                ErrorStr += " ERROR: Converting Register Value " + amptRegisterValue + " to hex value.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else if (commandType == ShortIntegerRegisterCommandInHex )
        {
            valueToSetAmptRegister = amptRegisterValue.toInt(&ok,10);
            if (ok == false)
            {
                ErrorStr += " ERROR: Converting Register Value " + amptRegisterValue + " to signed decimal value.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else
        {
            ErrorStr += " ERROR: Invalid Short Integer Register Command Type:" + commandType;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        QString endOfCommandProse("");

        if (s.mid(2,1) == "m")
        {
            endOfCommandProse += EndOfCommandProseForMACCommand + s.mid(3,12) + "?";
        }
        else if (s.mid(2,1) == "*")
        {
            endOfCommandProse += EndOfCommandProseForBroadcastCommand;
        }
        else if (s.mid(2,1) == "s")
        {
            endOfCommandProse += EndOfCommandProseForGroupCommand + s.mid(3,4) + "?";
        }
        else if (s.mid(2,1) == "#")
        {
            endOfCommandProse += EndOfCommandProseForNetworkCommand + s.mid(3,3) + "?";
        }
        else
        {
            ErrorStr += " ERROR: Invalid Short Integer Register Command Type:" + commandType;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        QString commandProse("");

        if (shortIntegerRegisterNumber == ShortIntegerRegisterGroupID)
        {
            commandProse += "Do you wish to set the Group ID value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterNetworkID)
        {
            commandProse += "Do you wish to set the Bunch ID/Network ID value to " + amptRegisterValue+ endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterGWEDAddress)
        {
            commandProse += "Do you wish to set the GWED Address value to " + amptRegisterValue+ endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSearchCycles_C2)
        {
            commandProse += "Do you wish to set the Search Cycles Hopping Channels (C2) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSearchCycles_C4)
        {
            commandProse += "Do you wish to set the Search Cycles Hopping Channels (C4) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSearchCycles_C3)
        {
            commandProse += "Do you wish to set the Search Cycles Hopping Channels (C3) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSearchCycles_C1)
        {
            commandProse += "Do you wish to set the Search Cycles Hopping Channels (C1) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSearchCycles_SoftKick)
        {
            commandProse += "Do you wish to set the Search Cycles Hopping Channels (Soft Kick) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSearchCycles_Restart)
        {
            commandProse += "Do you wish to set the Search Cycles Hopping Channels (C5, Restart) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetImageAddress)
        {
            commandProse += "Do you wish to set the Image Address (which Image will be booted) value to  " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetVersionLowMain)
        {
            commandProse += "Do you wish to set the Version Low value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetVersionHigh8K)
        {
            commandProse += "Do you wish to set the Version High value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterBootImage)
        {
            commandProse += "Do you wish to set the Try Before You Buy value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSyncWord)
        {
            commandProse += "Do you wish to set the Sync Word value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterCurrentNoise)
        {
            commandProse += "Do you wish to set the Current Noise value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterMicroOffset)
        {
            commandProse += "Do you wish to set the Micro Offset (Pure Offset) value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetLowCurrentLimitTo255)
        {
            commandProse += "Do you wish to set the Low Current Limit to 255 value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetVhvLimitVout)
        {
            commandProse += "Do you wish to set the Vhv Limit Vout value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetIhvLimitVout )
        {
            commandProse += "Do you wish to set the Ihv Limit Vout value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetVhvLimitVins)
        {
            commandProse += "Do you wish to set the Vhv Limit Vins value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetIhvLimitVins )
        {
            commandProse += "Do you wish to set the Ihv Limit Vins value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterVoutOV )
        {
            commandProse += "Do you wish to set the VoutOV value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterIoutOC )
        {
            commandProse += "Do you wish to set the IoutOC value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterFETFailureCount )
        {
            commandProse += "Do you wish to set the FET Failure Count value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterFETCurrentThreshold )
        {
            commandProse += "Do you wish to set the FET Current Threshold value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterFETDelta )
        {
            commandProse += "Do you wish to set the FET Delta value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetVoutLimitCount )
        {
            commandProse += "Do you wish to set the Vout Limit Count value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetVoutLimit )
        {
            commandProse += "Do you wish to set the Vout Limit value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetIoutLimitCount )
        {
            commandProse += "Do you wish to set the Iout Limit Count value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetIoutLimit )
        {
            commandProse += "Do you wish to set the Iout Limit value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetMFV_OV )
        {
            commandProse += "Do you wish to set the Vout Limit value for the Memory Fix Algo. to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSetMFI_OC )
        {
            commandProse += "Do you wish to set the Iout Limit value for the Memory Fix Algo. to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSet_EFInputCurrentThreshold )
        {
            commandProse += "Do you wish to set the Input Current Threshold value for the Engine Failure Algo. to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (shortIntegerRegisterNumber == ShortIntegerRegisterSet_IinLimit)
        {
            commandProse += "Do you wish to set the Input Current Limit for the Input Current Limit Protection Algo. to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            ErrorStr += " ERROR: Unknown or Unrecognized Short Integer Register number " + amptRegister;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

    }
    else
    {
        ErrorStr += " ERROR: Invalid or Unrecognized Short Integer Register Number (Out of Range):" + amptRegister;
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
        return false;
    }
    return true;
}

bool CheckGatewayCommandThread::confirmByteRegisterNumberAndValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & s)
{
    bool ok = true;
    int byteRegisterNumber = amptRegister.toInt(&ok,10);
    QString ErrorStr(Q_FUNC_INFO);

    if ((ok == true) && (byteRegisterNumber > 0) && (byteRegisterNumber <= ByteRegisterSet_IinLimitTempAmbientAdjust))
    {
        int valueToSetAmptByteRegister = 0;

        if (commandType == ByteRegisterCommand)
        {
            valueToSetAmptByteRegister = amptRegisterValue.toInt(&ok,10);
            if (ok == false)
            {
                ErrorStr += " ERROR: Converting Register Value " + amptRegisterValue + " to decimal value.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else if (commandType == ByteRegisterCommandInHex)
        {
            valueToSetAmptByteRegister = amptRegisterValue.toInt(&ok,16);
            if (ok == false)
            {
                ErrorStr += " ERROR: Converting Register Value " + amptRegisterValue + " to hex value.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else
        {
            ErrorStr += " ERROR: Invalid Byte Register Command Type:" + commandType;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        QString commandProse("");
        qDebug() << Q_FUNC_INFO << " valueToSetAmptByteRegister = " << valueToSetAmptByteRegister;

        QString endOfCommandProse("");

        if (s.mid(2,1) == "m")
        {
            endOfCommandProse += EndOfCommandProseForMACCommand + s.mid(3,12) + "?";
        }
        else if (s.mid(2,1) == "*")
        {
            endOfCommandProse += EndOfCommandProseForBroadcastCommand;
        }
        else if (s.mid(2,1) == "s")
        {
            endOfCommandProse += EndOfCommandProseForGroupCommand + s.mid(3,4) + "?";
        }
        else if (s.mid(2,1) == "#")
        {
            endOfCommandProse += EndOfCommandProseForNetworkCommand + s.mid(3,3) + "?";
        }
        else
        {
            ErrorStr += " ERROR: Invalid Byte Register Command Type:" + commandType;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        if (byteRegisterNumber == 0)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterChannelFlag) // Channel Flag
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to turn Channel Flag off" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to turn Channel Flag on" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                ErrorStr += " ERROR: Invalid value (" + amptRegisterValue + ") for Byte Register " + amptRegister;
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
        }
        else if (byteRegisterNumber == 2)
        {
            return false;
        }
        else if (byteRegisterNumber == 3)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterMpp) // MPP
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to turn MPP off" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to turn MPP on" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                ErrorStr += " ERROR: Invalid value (" + amptRegisterValue + ") for Byte Register " + amptRegister;
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
        }
        else if (byteRegisterNumber == ByteRegisterModule) // Module
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish turn Module off" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish turn Module on" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                ErrorStr += " ERROR: Invalid value (" + amptRegisterValue + ") for Byte Register " + amptRegister;
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
        }
        else if (byteRegisterNumber == 6)
        {
            return false;
        }
        else if (byteRegisterNumber == 7)
        {
            return false;
        }
        else if (byteRegisterNumber == 8)
        {
            return false;
        }
        else if (byteRegisterNumber == 9)
        {
            return false;
        }
        else if (byteRegisterNumber == 10)
        {
            return false;
        }
        else if (byteRegisterNumber == 11)
        {
            return false;
        }
        else if (byteRegisterNumber == 12)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterStayInRx) // Stay in RX
        {
            if (amptRegisterValue >= 1)
            {
                commandProse += "Do you wish to set the optimizer in RX only radio mode (if firmware supports it)" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
        }
        else if (byteRegisterNumber == 14) // InstallationDate?
        {
            return false;
        }
        else if (byteRegisterNumber == 15)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterMACByteZero) // MAC Byte 0, (1st 2 hex numbers of MAC)
        {
            commandProse += "Do you wish to set the first MAC byte (MAC[0]) to the value of " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterMACByteOne) // MAC Byte 1, (3rd & 4th hex numbers of MAC)
        {
            commandProse += "Do you wish to set the second MAC byte (MAC[1]) to the value of " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterMACByteTwo) // MAC Byte 2, (5th & 6th hex numbers of MAC)
        {
            commandProse += "Do you wish to set the third MAC byte (MAC[2]) to the value of " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterMACByteThree) // MAC Byte 3, (7th & 8th hex numbers of MAC)
        {
            commandProse += "Do you wish to set the fourth MAC byte (MAC[3]) to the value of " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterMACByteFour) // MAC Byte 4, (9th & 10th hex numbers of MAC)
        {
            commandProse += "Do you wish to set the fifth MAC byte (MAC[4]) to the value of " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterMACByteFive) // MAC Byte 5, (11th & 12th hex numbers of MAC)
        {
            commandProse += "Do you wish to set the sixth MAC byte (MAC[5]) to the value of " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterOVLimit) // OV limit
        {
            commandProse += "Do you wish set the Over Voltage Limit (OV) to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterOCLimit) // OC limit
        {
            commandProse += "Do you wish set the Over Current Limit (OC) to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == 24)
        {
            return false;
        }
        else if (byteRegisterNumber == 25)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterBaseChannel) // Base Channel
        {
            commandProse += "Do you wish set the base channel to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == 27)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterWriteEntirePBToFlash)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to write to entire Parameter Block to Flash" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == 29)
        {
            return false;
        }
        else if (byteRegisterNumber == 30)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterDisbandNetwork)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to disband the optimizer from the network (must also issue save command after)" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterReadPBFromRAM)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to read the optimizers entire Parameter Block from RAM" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
                // LBC need to also emit to disable PB read write, also for cases b2, b3, indicate what has been read?
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterWriteMostPBToFlash)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to write to most of Parameter Block to Flash (NOT OV,OC,Module,MPP)" + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == 34)
        {
            return false;
        }
        else if (byteRegisterNumber == 35)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterEDRadioPower)
        {
            if (commandType == ByteRegisterCommandInHex)
            {
                if ((valueToSetAmptByteRegister == 0xED) ||
                        (valueToSetAmptByteRegister == 0xEF) ||
                        (valueToSetAmptByteRegister == 0x91) ||
                        (valueToSetAmptByteRegister == 0x51) ||
                        (valueToSetAmptByteRegister == 0x70) ||
                        (valueToSetAmptByteRegister == 0x50) ||
                        (valueToSetAmptByteRegister == 0x40) ||
                        (valueToSetAmptByteRegister == 0xEF))
                {
                    commandProse += "Do you wish to set the ED Radio Power to the value of " + amptRegisterValue + endOfCommandProse;
                    emit publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    ErrorStr += " ERROR: Invalid ED Radio Power value " + amptRegisterValue;
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
            }
            else
            {
                ErrorStr += " ERROR: ED Radio Power value " + amptRegisterValue + " must be specified in hex.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else if (byteRegisterNumber == 37)
        {
            return false;
        }
        else if (byteRegisterNumber == 38)
        {
            return false;
        }
        else if (byteRegisterNumber == 39)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterEDFrequencyHopping)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to disable Frequency Hopping" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to enable Frequency Hopping" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterIsRepeater)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to disable repeater funcationality" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to enable repeater functionality" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterIsSlave)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to disable slave funcationality" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to enable slave functionality" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterRepeaterChannel)
        {
            commandProse += "Do you wish set the repeater channel to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterRepeaterPower)
        {
            if (commandType == ByteRegisterCommandInHex)
            {
                if ((valueToSetAmptByteRegister == 0xED) ||
                        (valueToSetAmptByteRegister == 0xEF) ||
                        (valueToSetAmptByteRegister == 0x91) ||
                        (valueToSetAmptByteRegister == 0x51) ||
                        (valueToSetAmptByteRegister == 0x70) ||
                        (valueToSetAmptByteRegister == 0x50) ||
                        (valueToSetAmptByteRegister == 0x40) ||
                        (valueToSetAmptByteRegister == 0xEF))
                {
                    commandProse += "Do you wish to set the Repeater Radio Power to the value of " + amptRegisterValue + endOfCommandProse;
                    emit publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    ErrorStr += " ERROR: Invalid Repeater Radio Power value " + amptRegisterValue;
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
            }
            else
            {
                ErrorStr += " ERROR: Repeater Radio Power value " + amptRegisterValue + " must be specified in hex.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterSearchModeEnabled)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to disable search mode funcationality" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to enable search mode functionality" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == 46)
        {
            return false;
        }
        else if (byteRegisterNumber == 47)
        {
            return false;
        }
        else if (byteRegisterNumber == 48)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterFuseCommunication)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterFuseOVandOC)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterWriteMainPBUsing8KPB)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterEndOfTest)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to execute the End Of Test command" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == 50)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterSynchronizeMPPCycles)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to restart the MPP cycle" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == 52)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterSetStartSlaveChannel)
        {
            commandProse += "Do you wish set the Start Slave Channel to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == 54)
        {
            return false;
        }
        else if (byteRegisterNumber == ByteRegisterCheckFlash)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to check flash (must be running 8K image)" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterSwitchSecurity)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to switch to the new AES key" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterReportParameterBlockFromFlash)
        {
            if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to report the parameter block from flash" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterCalibrationRepeat)
        {
            commandProse += "Do you wish set calibration repeat value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterRepeaterSlaveBaudRate)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to set the Repeater/Slave baud rate to 500 kbod" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to set the Repeater/Slave baud rate to 250 kbod" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterRepeaterStep)
        {
            if ((valueToSetAmptByteRegister >= 10) && (valueToSetAmptByteRegister <=25))
            {
                commandProse += "Do you wish to set the Repeater Step to " + amptRegisterValue + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterOVStartup)
        {
            commandProse += "Do you wish set the OV startup value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterOCFallback)
        {
            commandProse += "Do you wish set the OC Fallback value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterToffFallback)
        {
            commandProse += "Do you wish set the Toff Fallback value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterTonFallback)
        {
            commandProse += "Do you wish set the Ton Fallback value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterFallbackTime)
        {
            commandProse += "Do you wish set the Fallback Time value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterNetCnst1)
        {
            commandProse += "Do you wish set the Net Cnst1 value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterNetCnst2)
        {
            commandProse += "Do you wish set the Net Cnst2 value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterT_OC_Jump)
        {
            commandProse += "Do you wish set the T_OC_JUMP value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterOCStep)
        {
            commandProse += "Do you wish set the OC Step value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterOVStep)
        {
            commandProse += "Do you wish set the OV Step value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterShunt)
        {
            commandProse += "Do you wish set the Shunt value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterMaxOff)
        {
            if ((valueToSetAmptByteRegister >= 0) && (valueToSetAmptByteRegister <= 127))
            {
                commandProse += "Do you wish to set the Max Off to " + amptRegisterValue + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterVinDisableRadio)
        {
            commandProse += "Do you wish set the Vin Disable Radio value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterNumberOfBunchesBeforeRepeat)
        {
            commandProse += "Do you wish set the Number of Bunches before repeat value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterGlobalBunchNumber)
        {
            commandProse += "Do you wish set the Global Bunch Number value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterOCShortCircuitLimit)
        {
            commandProse += "Do you wish set the OC Short Circuit Limit value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSyncPhase)
        {
            commandProse += "Do you wish set the Sync Phase value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSyncFrequency)
        {
            commandProse += "Do you wish set the Sync Phase value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterTempCalibrate)
        {
            commandProse += "Do you wish set the Temp Calibrate value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSetMPPCycle)
        {
            commandProse += "Do you wish set the Set MPP Cycle value " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterWriteMostPBToFlash)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to write 8K parameter block from 8K image (Not OV, OC, Module, MPP) to 8K flash" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to write 8K parameter block from 8K image (Not OV, OC, Module, MPP) to Main flash" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterWriteAllMainPBUsing8KPB)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to write 8K parameter block from 8K image to 8K flash" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to write 8K parameter block from 8K image to Main flash" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterReadMainPBFrom8KFlash)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to read 8K parameter block from 8K image" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to read Main parameter block from 8K image" + endOfCommandProse;
                publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterReadCoefficients)
        {
            commandProse += "Do you wish read coeffiecients from main image " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSet_MFTimer1)
        {
            commandProse += "Do you wish to set the Memory Fix Timer1 register value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSet_MFTimer2)
        {
            commandProse += "Do you wish to set the Memory Fix Timer2 register value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSet_MFTimer2MPPOffCyclesAndTimesToCycle)
        {
            commandProse += "Do you wish to set the Memory Fix Timer2 MPP Off Cycles and times to cycle register value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSet_MonitoringNetStatus)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to disable the debug output of the MF or EF algorithm by sending value of " + amptRegisterValue + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 1)
            {
                commandProse += "Do you wish to enable the debug output of the MF algorithm by sending value of " + amptRegisterValue + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else if (valueToSetAmptByteRegister == 2)
            {
                commandProse += "Do you wish to enable the debug output of the EF algorithm by sending value of " + amptRegisterValue + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterSet_EFOccurrenceThreshold)
        {
            if (valueToSetAmptByteRegister == 0)
            {
                commandProse += "Do you wish to set (0 = disable) the Engine Failure Algorithm Occurrence Threshold register value to " + amptRegisterValue + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                commandProse += "Do you wish to enable the Engine Failure Algorithm and set the Occurrence Threshold register value to " + amptRegisterValue + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
        }
        else if (byteRegisterNumber == ByteRegisterSet_EFCountDownTimer)
        {
            commandProse += "Do you wish to set the Engine Failure Algorithm CountDown Timer register value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSet_EFAlphaNumerator)
        {
            commandProse += "Do you wish to set the Engine Failure Algorithm Alpha Numerator register value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterClear_EFModuleOff)
        {
            commandProse += "Do you wish to clear the Engine Failure Algorithm Failed condition" + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else if (byteRegisterNumber == ByteRegisterSet_IinLimitOCSteps)
        {
            QString justTheUpperNibbleValue;
            QString tmp = amptRegisterValue;
            unsigned char upperNibble = tmp.toUInt();
            bool proceed = false;

            if (upperNibble <= 15)
            {
                upperNibble = (upperNibble << 4); // move to 'upper' nibble
                justTheUpperNibbleValue = QString::number(upperNibble);
                proceed = true;
            }
            else if ((upperNibble >= 16) && (!(upperNibble & 0x0F))) // don't want anything in lower nibble
            {
                justTheUpperNibbleValue = amptRegisterValue;
                proceed = true;
            }
            if (proceed == true)
            {
                if (valueToSetAmptByteRegister == 0)
                {
                    commandProse += "Do you wish to disable (0 = disable) the IinLimit Protection by setting the IinLimitOCStepsAndDelay register (upper Nibble) value to " + amptRegisterValue + endOfCommandProse;
                    emit publishValidateCommandToUser(commandProse,s);
                }
                else
                {
                    commandProse += "Do you wish to enable the IinLimit Protection by setting the IinLimitOCStepsAndDelay register (upper Nibble) value to " + amptRegisterValue + endOfCommandProse;
                    emit publishValidateCommandToUser(commandProse,s);
                }
            }
            else
            {
                ErrorStr += " ERROR: Invalid upper nibble value for Byte Register Number:" + amptRegister;
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterSet_IinLimitOCDelay)
        {
            QString justLowerNibbleValue;
            QString tmp = amptRegisterValue;
            unsigned char lowerNibble = tmp.toUInt();

            if (lowerNibble <= 15)
            {
                commandProse += "Do you wish to set the Delay portion of the IinLimitOCStepsAndDelay register (lower nibble) value to " + amptRegisterValue + endOfCommandProse;
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                ErrorStr += " ERROR: Invalid lower nibble value for Byte Register Number:" + amptRegister;
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else if (byteRegisterNumber == ByteRegisterSet_IinLimitTempAmbientAdjust)
        {
            commandProse += "Do you wish to set the IinLimit Temperature Ambient Adjust register value to " + amptRegisterValue + endOfCommandProse;
            emit publishValidateCommandToUser(commandProse,s);
        }
        else
        {
            ErrorStr += " ERROR: Invalid or Unrecognized Byte Register Number:" + amptRegister;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }
    }
    else
    {
        ErrorStr += " ERROR: Invalid or Unrecognized Byte Register Number:" + amptRegister;
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
        return false;
    }

    return true;
}

bool CheckGatewayCommandThread::validateRegisterType(const QString registerType)
{
    if ((registerType == "b") || (registerType == "h") || (registerType == "i")  || (registerType == "H") || (registerType == "n") || (registerType == "f"))
    {
        return true;
    }
    return false;
}


bool CheckGatewayCommandThread::validateRegisterNumberForType(int indexIntoCommand, QString s, QString & properlyFormedCommandString, QString & amptRegisterNumber, QString & amptRegisterType, QString & amptRegisterTypeValue)
{
    QString ErrorStr(Q_FUNC_INFO);

    ErrorStr += " ERROR: Invalid register/register type/value to set." + s;
    bool ok = false;


    // indexIntoCommand should be pointing to a leading blank before register in a command, no matter the command type (m,#,s,*)
    if (s.at(indexIntoCommand) != ' ')
    {
        ErrorStr += ", expected space not found.";
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
        return false;
    }
    else
    {
        while (s.at(indexIntoCommand) == ' ') // move past blanks,looking for start of second group of alpha's (should be m,#,s, or *).
        {

            // qDebug() << Q_FUNC_INFO << " char at " << indexIntoCommand << " is " << s.at(indexIntoCommand);
            indexIntoCommand++;
            if (s.length() <= indexIntoCommand)
            {
                ErrorStr += ", could not locate register.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }

        // LBC 05/08/2019 indexIntoCommand; // Should now be pointing to first character of register number.

        int indexIntoCommand2 = s.indexOf(' ',indexIntoCommand);
        if (indexIntoCommand2 == -1)
        {
            ErrorStr += ", could not locate register.";
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }
        amptRegisterNumber = s.mid(indexIntoCommand, indexIntoCommand2 - indexIntoCommand);

        indexIntoCommand = indexIntoCommand2; // Pointing to blank, remove all blanks (hopefully) in front of address type/value argument

        while (s.at(indexIntoCommand) == ' ') // move past blanks,looking for start of second group of alpha's (should be m,#,s, or *).
        {
            // qDebug() << Q_FUNC_INFO << " char at " << indexIntoCommand << " is " << s.at(indexIntoCommand);
            indexIntoCommand++;
            if (s.length() <= indexIntoCommand)
            {
                ErrorStr += ", could not locate register.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }

        amptRegisterType = s.mid(indexIntoCommand,1);

        if (validateRegisterType(amptRegisterType) == true)
        {
            amptRegisterTypeValue = s.mid(indexIntoCommand+1);
            if (amptRegisterType == FloatRegisterCommand)
            {
                amptRegisterTypeValue.toFloat(&ok);
                if (ok == false)
                {
                    ErrorStr += ", Invalid register value: " + amptRegisterTypeValue + " for float.";
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
            }
            else
            {
                amptRegisterTypeValue.toInt(&ok,16); // Either a base 10 or base 16 will be valid, just confirming valid numbers...
                if ((ok == false) && (amptRegisterTypeValue.at(0) != '0')) // Some valid Ampt Register values have/begin with 0
                {
                    ErrorStr += ", Invalid register value: " + amptRegisterTypeValue + " for BYTE/Short Integer";
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
            }
        }
        else
        {
            ErrorStr += ", Invalid register type.";
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        properlyFormedCommandString += " " + amptRegisterNumber + " " + amptRegisterType + amptRegisterTypeValue;
        // qDebug() << Q_FUNC_INFO << " properly formed: " << properlyFormedCommandString;

    }
    return true;
}

bool CheckGatewayCommandThread::validateCommandTypeAndRegisterAndRegisterValue(const QString & commandType, const QString & amptRegister, const QString & amptRegisterValue, const QString & command)
{
    qDebug() << Q_FUNC_INFO << " commandType:" << commandType << " amptRegister:" << amptRegister << " amptRegisterValue:" << amptRegisterValue << " command:" << command;

    if ((commandType == ByteRegisterCommand) || (commandType == ByteRegisterCommandInHex))
    {
        return confirmByteRegisterNumberAndValue(commandType, amptRegister, amptRegisterValue, command);
    }
    else if ((commandType == ShortIntegerRegisterCommand) || (commandType == ShortIntegerRegisterCommandInHex) || (commandType == ShortIntegerRegisterCommandNegative))
    {
        return confirmShortIntegerRegisterNumberAndValue(commandType, amptRegister, amptRegisterValue, command);
    }
    else if (commandType == FloatRegisterCommand)
    {
        return confirmFloatRegisterNumberAndValue(commandType, amptRegister, amptRegisterValue, command);
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        ErrorStr += " ERROR: Unknown command type:" + commandType + " in command:" + command;
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
        //return false;
    }
    return false;
}

bool CheckGatewayCommandThread::validateCommandFormatToEndDevice(QString s, QString & properlyFormedCommandString, QString & amptAddressType, QString & amptRegisterNumber, QString & amptRegisterType, QString & amptRegisterTypeValue)

{
    s = s.trimmed(); // Remove leading and trailing spaces

    properlyFormedCommandString = "";
    QString ErrorStr(Q_FUNC_INFO);
    QString commandProse("");
    QString address("");

    ErrorStr += " ERROR: Invalid command form " + s;
    bool ok = false;
    const QChar firstChar = s.at(0);

    int indexIntoCommand = s.indexOf(' ',0);
    int indexIntoCommand2 = 0;

    if (indexIntoCommand != 1) // checks there is a blank at position 1
    {
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
        return false;
    }

    properlyFormedCommandString = firstChar;
    properlyFormedCommandString += " ";

    while (s.at(indexIntoCommand) == ' ') // move past blanks,looking for start of second group of alpha's (should be m,#,s, or *).
    {
        // qDebug() << Q_FUNC_INFO << " char at " << indexIntoCommand << " is " << s.at(indexIntoCommand);

        indexIntoCommand++;
        if (s.length() <= indexIntoCommand)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }
    }

    QChar typeOfCommandRecipient = s.at(indexIntoCommand);

    // qDebug() << Q_FUNC_INFO << " typeOfCommandRecipient:" << typeOfCommandRecipient << " indexIntoCommand:" << indexIntoCommand << " properlyFormedCommandString:" << properlyFormedCommandString;

    if (typeOfCommandRecipient == 'm')
    {
        properlyFormedCommandString += typeOfCommandRecipient;
        indexIntoCommand2 = indexIntoCommand + 1; // Index indexIntoCommand2 one char past 'm'

        int lengthOfValidMACAddress = 12;


        indexIntoCommand = s.indexOf(' ',indexIntoCommand2);
        if (indexIntoCommand == -1)
        {
            if ((indexIntoCommand2 + lengthOfValidMACAddress) == 15)
            {
                address = s.mid(indexIntoCommand2, lengthOfValidMACAddress);
                // LBC Check validity of MAC address, is it a valid hex number of 12 digits?
                address.toLongLong(&ok,16);
                if (ok == false)
                {
                    ErrorStr += ", invalid hexidecimal MAC address:" + address;
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
                properlyFormedCommandString += address;
                return true;
            }
            else
            {
                ErrorStr += ", missing register and register type/value or invalid mac address.";
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }

        int passedInMACAddressLength = indexIntoCommand - indexIntoCommand2;

        if (passedInMACAddressLength != lengthOfValidMACAddress)
        {
            ErrorStr += ", invalid length of MAC address:" + QString(passedInMACAddressLength);
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        address = s.mid(indexIntoCommand2, passedInMACAddressLength);
        address.toLongLong(&ok,16); // Ensure MAC address is a valid (12 character from above check) hex value
        if (ok == false)
        {
            ErrorStr += ", invalid hexidecimal MAC address:" + address;
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }

        properlyFormedCommandString += address;
        indexIntoCommand2 = indexIntoCommand;
        // qDebug() << Q_FUNC_INFO << " typeOfCommandRecipient:" << typeOfCommandRecipient << " indexIntoCommand:" << indexIntoCommand << " properlyFormedCommandString:" << properlyFormedCommandString + " address:" + address;
    }
    else if (typeOfCommandRecipient == '*')
    {
        properlyFormedCommandString += typeOfCommandRecipient;
        address = "*";

        // qDebug() << Q_FUNC_INFO << " typeOfCommandRecipient:" << typeOfCommandRecipient << " indexIntoCommand:" << indexIntoCommand << " properlyFormedCommandString:" << properlyFormedCommandString;

        if (s.length() == (s.indexOf('*') + 1))
        {
            if ((firstChar == 'r') || (firstChar == 'f') || (firstChar == 'F'))
            {
                return true;
            }
            else
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
        }
        else
        {
            indexIntoCommand++; // should be pointing to a blank char
            if (s.at(indexIntoCommand) != ' ')
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
                return false;
            }
            else
            {
                // qDebug() << Q_FUNC_INFO << " typeOfCommandRecipient:" << typeOfCommandRecipient << " indexIntoCommand:" << indexIntoCommand << " properlyFormedCommandString:" << properlyFormedCommandString + " address:" + address;

                indexIntoCommand2 = indexIntoCommand;
            }
        }
    }
    else if (typeOfCommandRecipient == 's')
    {
        properlyFormedCommandString += typeOfCommandRecipient;
        if (s.length() == indexIntoCommand)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }
        else
        {
            // find the Group

            indexIntoCommand2 = indexIntoCommand++; // Index indexIntoCommand2 to s, move indexIntoCommand2 to position s + 1

            int lengthOfCommand = s.length();
            int lengthOfValidGroupAddress = 4;

            // qDebug() << Q_FUNC_INFO << " lengthOfCommand - indexOfCommand" << lengthOfCommand - indexIntoCommand;

            if (lengthOfCommand - indexIntoCommand == lengthOfValidGroupAddress)
            {
                address = s.mid(indexIntoCommand,lengthOfValidGroupAddress);
                // LBC Check validity of Group address
                address.toLongLong(&ok,16);
                if (ok == false)
                {
                    ErrorStr += ", invalid hexidecimal group address:" + address;
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }

                if ((firstChar == 'r') || (firstChar == 'f') || (firstChar == 'F'))
                {
                    properlyFormedCommandString += address;
                    return true;
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
            }
            else
            {
                indexIntoCommand2++; // Start of Hex address (hopefully)
                indexIntoCommand = s.indexOf(' ',indexIntoCommand);

                int lengthOfGroupAddressPassedIn = indexIntoCommand - indexIntoCommand2;

                if (lengthOfGroupAddressPassedIn != lengthOfValidGroupAddress)
                {
                    ErrorStr += ", invalid length of Group address:" + QString::number(lengthOfGroupAddressPassedIn);
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }

                address = s.mid(indexIntoCommand2,lengthOfGroupAddressPassedIn);

                address.toLongLong(&ok,16);
                if (ok == false)
                {
                    ErrorStr += ", invalid hexidecimal group address:" + address;
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }

                properlyFormedCommandString += address;

                indexIntoCommand2 = indexIntoCommand; // should be pointing to a blank char
                if (s.at(indexIntoCommand2) != ' ')
                {
                    ErrorStr += " group command missing register and value.";
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
                // qDebug() << Q_FUNC_INFO << " typeOfCommandRecipient:" << typeOfCommandRecipient << " indexIntoCommand:" << indexIntoCommand << " properlyFormedCommandString:" << properlyFormedCommandString + " address:" + address;
            }
        }
    }
    else if (typeOfCommandRecipient == '#')
    {
        properlyFormedCommandString += typeOfCommandRecipient;
        if (s.length() == indexIntoCommand)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return false;
        }
        else
        {
            // find the NetworkID
            indexIntoCommand2 = indexIntoCommand++; // Index indexIntoCommand2 to s, move indexIntoCommand2 to position s + 1

            int lengthOfCommand = s.length();
            int lengthOfValidNetworkAddress = 3;

            // qDebug() << Q_FUNC_INFO << " lengthOfCommand - indexOfCommand" << lengthOfCommand - indexIntoCommand;

            if (lengthOfCommand - indexIntoCommand == lengthOfValidNetworkAddress)
            {
                address = s.mid(indexIntoCommand,lengthOfValidNetworkAddress);
                // LBC Check validity of Network address
                address.toLongLong(&ok,16);
                if (ok == false)
                {
                    ErrorStr += ", invalid hexidecimal network address:" + address;
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }

                properlyFormedCommandString += address;
                if ((firstChar == 'r') || (firstChar == 'f') || (firstChar == 'F'))
                {
                    return true;
                }
                else
                {
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
            }

            else
            {
                indexIntoCommand2++; // Start of Hex address (hopefully)
                indexIntoCommand = s.indexOf(' ',indexIntoCommand);

                int lengthOfNetworkAddressPassedIn = indexIntoCommand - indexIntoCommand2;

                if (lengthOfNetworkAddressPassedIn != lengthOfValidNetworkAddress)
                {
                    ErrorStr += ", invalid length of Network address:" + QString::number(lengthOfNetworkAddressPassedIn);
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }

                address = s.mid(indexIntoCommand2,lengthOfNetworkAddressPassedIn);

                address.toLongLong(&ok,16);
                if (ok == false)
                {
                    ErrorStr += ", invalid hexidecimal Network address:" + address;
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }

                properlyFormedCommandString += address;

                indexIntoCommand2 = indexIntoCommand; // should be pointing to a blank char
                if (s.at(indexIntoCommand2) != ' ')
                {
                    ErrorStr += ", network command missing register and value.";
                    qDebug() << ErrorStr;
                    emit checkGatewayCommandThreadError(ErrorStr);
                    return false;
                }
                // qDebug() << Q_FUNC_INFO << " typeOfCommandRecipient:" << typeOfCommandRecipient << " indexIntoCommand:" << indexIntoCommand << " properlyFormedCommandString:" << properlyFormedCommandString + " address:" + address;
            }

        }
    }
    else
    {
        ErrorStr += ", Unknown type of address/command recipient.";
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
        return false;
    }

    amptAddressType = typeOfCommandRecipient;

    // qDebug() << Q_FUNC_INFO << "properlyFormed so far: " << properlyFormedCommandString;


    if (validateRegisterNumberForType(indexIntoCommand, s, properlyFormedCommandString, amptRegisterNumber, amptRegisterType, amptRegisterTypeValue) == true)
    {
        return true;
    }

    return false;
}

void::CheckGatewayCommandThread::confirmCommandToEndDevice(QString s)
{
    s = s.trimmed();

    QString ErrorStr(Q_FUNC_INFO);
    ErrorStr += " ERROR: Invalid or misformed command " + s;
    QString commandProse("");

    QString properlyFormedCommandString("");
    QString amptAddressType("");
    QString amptRegisterNumber("");
    QString amptRegisterType("");
    QString amptRegisterValue("");

    if (validateCommandFormatToEndDevice(s, properlyFormedCommandString, amptAddressType, amptRegisterNumber, amptRegisterType, amptRegisterValue) == true)
    {
        qDebug() << Q_FUNC_INFO << " a 'properly' formed command string " << properlyFormedCommandString <<" aDDType:" << amptAddressType << " aRegNumber:" << amptRegisterNumber << " aRegType:" << amptRegisterType << " aRegisterTypeValue:" << amptRegisterValue;
        const QChar firstChar = properlyFormedCommandString.at(0);
        const QChar addressIndication = properlyFormedCommandString.at(2);

        // First see if command is an r,f,or F command for the different address types
        if ((properlyFormedCommandString.length() == 15) && (addressIndication == 'm'))
        {
            if (firstChar == 'r')
            {
                commandProse += "Do you wish to reboot/restart the optimizer with MAC " + properlyFormedCommandString.mid(3,12) + "?";
                emit publishValidateCommandToUser(commandProse,s);
            }
            else if (firstChar == 'f')
            {
                commandProse += "Do you wish to save parameter settings to flash (small f) for MAC " + properlyFormedCommandString.mid(3,12) + "?";
                emit publishValidateCommandToUser(commandProse,s);
            }
            else if (firstChar == 'F')
            {
                commandProse += "Do you wish to save parameter settings to flash (big F) for MAC " + properlyFormedCommandString.mid(3,12) + "?";
                emit publishValidateCommandToUser(commandProse,s);
            }
            else
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
            return;
        }
        else if ((properlyFormedCommandString.length() == 3) && (addressIndication == '*'))
        {
            if (firstChar == 'r')
            {
                commandProse += "Do you wish to reboot/restart all optimizers";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else if (firstChar == 'f')
            {
                commandProse += "Do you wish to save parameter block information (except for OV, OC, Module, MPP) for all optimizers?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else if (firstChar == 'F')
            {
                commandProse += "Do you wish to save all parameter block information for all optimizers?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
            return;
        }
        else if ((properlyFormedCommandString.length() == 7) && (addressIndication == 's'))
        {
            QString address = properlyFormedCommandString.mid(3,4);

            if (firstChar == 'r')
            {
                commandProse += "Do you wish to reboot/restart optimizers with Group Address " + address + "?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else if (firstChar == 'f')
            {
                commandProse += "Do you wish to save parameter block information (except for OV, OC, Module, MPP) for optimizers with Group Address " + address + "?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else if (firstChar == 'F')
            {
                commandProse += "Do you wish to save all parameter block information for optimizers with Group Address " + address + "?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
            return;
        }
        else if ((properlyFormedCommandString.length() == 6) && (addressIndication == '#'))
        {
            QString address = properlyFormedCommandString.mid(3,3);

            if (firstChar == 'r')
            {
                commandProse += "Do you wish to reboot/restart optimizers with Network Address " + address + "?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else if (firstChar == 'f')
            {
                commandProse += "Do you wish to save parameter block information (except for OV, OC, Module, MPP) for optimizers with Network Address " + address + "?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else if (firstChar == 'F')
            {
                commandProse += "Do you wish to save all parameter block information for optimizers with Network Address " + address + "?";
                emit publishValidateCommandToUser(commandProse,properlyFormedCommandString);
            }
            else
            {
                qDebug() << ErrorStr;
                emit checkGatewayCommandThreadError(ErrorStr);
            }
            return;
        }

        // If here a valid "full send form command has been observed. Call the correct verification/confirm function for the address type.


        if (validateCommandTypeAndRegisterAndRegisterValue(amptRegisterType,amptRegisterNumber,amptRegisterValue, properlyFormedCommandString) == false)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return;
        }
    }


    /*
    else if ((firstChar == 's') && (macIndication == 'm'))
    {
        QString ensureCommandHasOnlyOneBlankBetweenPieces("");
        int indexIntoCommand = s.indexOf(' ',0);
        if (indexIntoCommand != 1)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return;
        }
        ensureCommandHasOnlyOneBlankBetweenPieces += "s m";
        indexIntoCommand = s.indexOf(' ',3);
        qDebug() << Q_FUNC_INFO << " second blank char found at:" << indexIntoCommand;

        if (indexIntoCommand != 15)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return;
        }
        ensureCommandHasOnlyOneBlankBetweenPieces += s.mid(3,12);
        indexIntoCommand = 16;

        while (s.indexOf(' ',indexIntoCommand) == -1)
        {
            indexIntoCommand++;
        }

        int indexIntoCommand2 = s.indexOf(' ',indexIntoCommand);
        if (indexIntoCommand2 == -1)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return;
        }

        qDebug() << Q_FUNC_INFO << " third blank found at:" << indexIntoCommand2;

        QString amptRegister = s.mid(indexIntoCommand, indexIntoCommand2 - indexIntoCommand);


        qDebug() << Q_FUNC_INFO << " Register is " << amptRegister;

        ensureCommandHasOnlyOneBlankBetweenPieces += " " + amptRegister + " ";

        indexIntoCommand = indexIntoCommand2;

        qDebug() << Q_FUNC_INFO << " reset of command:" << s.mid(indexIntoCommand);

        while (s.indexOf(' ',indexIntoCommand) != -1)
        {
            indexIntoCommand++;
            qDebug() << Q_FUNC_INFO << "rest of command:" << s.mid(indexIntoCommand);

            if (s.length() <= indexIntoCommand)
            {
                qDebug() << ErrorStr << " ERROR: space(s) not found after Ampt Register located.";
                emit checkGatewayCommandThreadError(ErrorStr);
                return;
            }
        }

        QString typeOfRegisterCommand = s.mid(indexIntoCommand,1);
        QString valueToSend = s.mid(indexIntoCommand + 1);



        ensureCommandHasOnlyOneBlankBetweenPieces += typeOfRegisterCommand + valueToSend;

        qDebug() << Q_FUNC_INFO << "Register:" << amptRegister << " typeOfCommand:" << typeOfRegisterCommand << " value:" << valueToSend << " full command:" << ensureCommandHasOnlyOneBlankBetweenPieces;

        if (validateCommandTypeAndRegisterAndRegisterValue(typeOfRegisterCommand,amptRegister,valueToSend, ensureCommandHasOnlyOneBlankBetweenPieces) == false)
        {
            qDebug() << ErrorStr;
            emit checkGatewayCommandThreadError(ErrorStr);
            return;
        }
    }
    else
    {
        qDebug() << ErrorStr;
        emit checkGatewayCommandThreadError(ErrorStr);
    }
*/
}

void CheckGatewayCommandThread::run()
{

  while (m_operational)
  {
      if (m_gatewayCommandsToValidateList.isEmpty() == false)
      {
          m_mutex.lock();
          QString typeAndCommand = m_gatewayCommandsToValidateList.takeFirst();
          m_mutex.unlock();
          qDebug() << Q_FUNC_INFO << " got " << typeAndCommand;

          QStringList typeAndCommandInstance = typeAndCommand.split(',');

          QString ErrorStr(Q_FUNC_INFO);

          if (typeAndCommandInstance.size() == 2)
          {
              QString type = typeAndCommandInstance.at(0);
              if (type == "Gateway")
              {
                  qDebug() << Q_FUNC_INFO << " type GATEWAY";
                  validateCommandToGateway(typeAndCommandInstance.at(1));
              }
              else if (type == "MAC")
              {
                  qDebug() << Q_FUNC_INFO << " type MAC";
                  confirmCommandToEndDevice(typeAndCommandInstance.at(1));
              }
              else if (type == "Network")
              {
                  qDebug() << Q_FUNC_INFO << " type Network";
                  confirmCommandToEndDevice(typeAndCommandInstance.at(1));
              }
              else if (type == "Broadcast")
              {
                  qDebug() << Q_FUNC_INFO << " type Broadcast";
                  confirmCommandToEndDevice(typeAndCommandInstance.at(1));
              }
              else if (type == "Group")
              {
                  qDebug() << Q_FUNC_INFO << " type Group";
                  confirmCommandToEndDevice(typeAndCommandInstance.at(1));
              }
              else
              {
                  ErrorStr += " ERROR: type of command not recognized:" + typeAndCommand;
                  qDebug() << ErrorStr;
                  emit checkGatewayCommandThreadError(ErrorStr);
              }
          }
          else
          {
              ErrorStr += " ERROR: Number of arguments found in " + typeAndCommand + " does not equal expected value of 2.";
              emit checkGatewayCommandThreadError(ErrorStr);
              qDebug() << ErrorStr;
          }
      }
      else if (m_endDeviceCommandsToValidateList.isEmpty() == false)
      {
          QString properlyFormedCommandString("");
          QString amptAddressType("");
          QString amptRegisterNumber("");
          QString amptRegisterType("");
          QString amptRegisterValue("");

          QString command = m_endDeviceCommandsToValidateList.takeFirst();

          if (validateCommandFormatToEndDevice(command, properlyFormedCommandString, amptAddressType, amptRegisterNumber, amptRegisterType, amptRegisterValue) == true)
          {
              qDebug() << Q_FUNC_INFO << " a properly formed command string " << properlyFormedCommandString <<" aDDType:" << amptAddressType << " aRegNumber:" << amptRegisterNumber << " aRegType:" << amptRegisterType << " aRegisterTypeValue:" << amptRegisterValue;

              emit validatedCommand(properlyFormedCommandString);
              properlyFormedCommandString.clear();
          }
          else
          {
              QString ErrorStr(Q_FUNC_INFO);
              ErrorStr += " ERROR: command " + command + " failed validation.";
              qDebug() << ErrorStr;
              emit checkGatewayCommandThreadError(ErrorStr);
          }
      }
      else
      {
          QThread::msleep(650);
          // qDebug() << Qt::endl << "no data " << Qt::endl;
      }
	}

  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";
  emit this->checkGatewayCommandThreadExit();  
}

void CheckGatewayCommandThread::setCheckGatewayCommandThreadLogging( bool logging )
{
    m_logData = logging;
}

void CheckGatewayCommandThread::handleTerminate( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: begin ...";

    m_mutex.lock();
    m_gatewayCommandsToValidateList.clear();
    m_operational = false;
    m_mutex.unlock();

    qDebug() << Q_FUNC_INFO << " INFO: end ...";
}
