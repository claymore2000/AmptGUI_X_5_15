#include "endDeviceValuesChangesTracked.h"
#include "amptRegisterConstants.h"

edCommsValueChangesTracked::edCommsValueChangesTracked( void )
{
    resetAllTrackedValues();
}

edCommsValueChangesTracked::~edCommsValueChangesTracked( void )
{

}


void edCommsValueChangesTracked::resetAllTrackedValues( void )
{
    channelChanged = false;
    channel = 0;
    gatewayAddressChanged = false;
    gatewayAddress = 0;
    endDeviceAddressChanged = false;
    endDeviceAddress = 0;
    bunchChanged = false;
    bunch = 0;
    netIDChanged = false;
    netID = 0;
    groupChanged = false;
    group = 0;
    gBunchChanged = false;
    gBunch = 0;
    rBunchChanged = false;
    rBunch = 0;
    hoppingChanged = false;
    hopping = 0;
    radioPowerChanged = false;
    radioPower = 0;
    gwChannelFlagChanged = false;
    gwChannelFlag = 0;
    syncwordChanged = false;
    syncword = 0;
    twelveKbodChanged = false;
    twelveKbod = 0;
    stayInRXChanged = false;
    stayInRX = 0;
    stayInCWChanged = false;
    stayInCW = 0;
    repeaterChanged = false;
    repeater = 0;
    repeaterPowerChanged = false;
    repeaterPower = 0;
    repeaterChannelChanged = false;
    repeaterChannel = 0;
    searchEnabledChanged = false;
    searchEnabled = 0;
    CriticalLevel10Changed = false;
    CriticalLevel10 = 0;
    slaveChanged = false;
    slave = 0;
    slaveChannelChanged = false;
    slaveChannel = 0;
    two50KbodChanged = false;
    two50Kbod = 0;
    CriticalLevel500Changed = false;
    CriticalLevel500 = 0;

}

void edCommsValueChangesTracked::sendAllChangedValues( void )
{
}

bool edCommsValueChangesTracked::getChannelChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(channelChanged);
    return channelChanged;
}

void edCommsValueChangesTracked::changeChannel( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    channel = s;
    channelChanged = true;
}

bool edCommsValueChangesTracked::getGatewayAddressChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(gatewayAddressChanged);
    return gatewayAddressChanged;
}

void edCommsValueChangesTracked::changeGatewayAddress( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    gatewayAddress = s;
    gatewayAddressChanged = true;
}

bool edCommsValueChangesTracked::getEndDeviceAddressChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(endDeviceAddressChanged);
    return endDeviceAddressChanged;
}

void edCommsValueChangesTracked::changeEndDeviceAddress(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    endDeviceAddress = s;
    endDeviceAddressChanged = true;
}

bool edCommsValueChangesTracked::getBunchChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(bunchChanged);
    return bunchChanged;
}

void edCommsValueChangesTracked::changeBunch( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    bunch = s;
    bunchChanged = true;
}

bool edCommsValueChangesTracked::getNetIDChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(netIDChanged);
    return netIDChanged;
}

void edCommsValueChangesTracked::changeNetID(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    netID = s;
    netIDChanged = true;
}

bool edCommsValueChangesTracked::getGroupChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(groupChanged);
    return groupChanged;
}

void edCommsValueChangesTracked::changeGroup(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    group = s;
    groupChanged = true;
}

bool edCommsValueChangesTracked::getGBunchChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(gBunchChanged);
    return gBunchChanged;
}

void edCommsValueChangesTracked::changeGBunch(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    gBunch = s;
    gBunchChanged = true;
}

bool edCommsValueChangesTracked::getRBunchChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(rBunchChanged);
    return rBunchChanged;
}

void edCommsValueChangesTracked::changeRBunch(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    rBunch = s;
    rBunchChanged = true;
}

bool edCommsValueChangesTracked::getHoppingChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(hoppingChanged);
    return hoppingChanged;
}

void edCommsValueChangesTracked::changeHopping(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    hopping = s;
    hoppingChanged = true;
}

bool edCommsValueChangesTracked::getRadioPowerChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(radioPowerChanged);
    return radioPowerChanged;
}

void edCommsValueChangesTracked::changeRadioPower(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    radioPower = s;
    radioPowerChanged = true;
}

bool edCommsValueChangesTracked::getGWChannelFlagChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(gwChannelFlagChanged);
    return gwChannelFlagChanged;
}

void edCommsValueChangesTracked::changeGWChannelFlag(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    gwChannelFlag = s;
    gwChannelFlagChanged = true;
}

bool edCommsValueChangesTracked::getSyncWordChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(syncwordChanged);
    return syncwordChanged;
}

void edCommsValueChangesTracked::changeSyncWord(const int &s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    syncword = s;
    syncwordChanged = true;
}

bool edCommsValueChangesTracked::get12KbodChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(twelveKbodChanged);
    return twelveKbodChanged;
}

void edCommsValueChangesTracked::change12Kbod( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    twelveKbod = s;
    twelveKbodChanged = true;
}

bool edCommsValueChangesTracked::getStayInRXChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(stayInRXChanged);
    return stayInRXChanged;
}

void edCommsValueChangesTracked::changeStayInRX(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    stayInRX = s;
    stayInRXChanged = true;
}

bool edCommsValueChangesTracked::getStayInCWChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(stayInCWChanged);
    return stayInCWChanged;
}

void edCommsValueChangesTracked::changeStayInCW(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    stayInCW = s;
    stayInCWChanged = true;
}


bool edCommsValueChangesTracked::getRepeaterChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(repeaterChanged);
    return repeaterChanged;
}

void edCommsValueChangesTracked::changeRepeater(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    repeater = s;
    repeaterChanged = true;
}

bool edCommsValueChangesTracked::getRepeaterPowerChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(repeaterPowerChanged);
    return repeaterPowerChanged;
}

void edCommsValueChangesTracked::changeRepeaterPower(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    repeaterPower = s;
    repeaterPowerChanged = true;
}

bool edCommsValueChangesTracked::getRepeaterChannelChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(repeaterChannelChanged);
    return repeaterChannelChanged;
}

void edCommsValueChangesTracked::changeRepeaterChannel(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    repeaterChannel = s;
    repeaterChannelChanged = true;
}

bool edCommsValueChangesTracked::getSearchEnabledChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(searchEnabledChanged);
    return searchEnabledChanged;
}

void edCommsValueChangesTracked::changeSearchEnabled(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    searchEnabled = s;
    searchEnabledChanged = true;
}

bool edCommsValueChangesTracked::getCriticalLevel10Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(CriticalLevel10Changed);
    return CriticalLevel10Changed;
}

void edCommsValueChangesTracked::changeCriticalLevel10(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    CriticalLevel10 = s;
    CriticalLevel10Changed = true;
}

bool edCommsValueChangesTracked::getCriticalLevel500Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(CriticalLevel500Changed);
    return CriticalLevel500Changed;
}

void edCommsValueChangesTracked::changeCriticalLevel500(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    CriticalLevel500 = s;
    CriticalLevel500Changed = true;
}

bool edCommsValueChangesTracked::getSlaveChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(slaveChanged);
    return slaveChanged;
}

void edCommsValueChangesTracked::changeSlave(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    slave = s;
    slaveChanged = true;
}

bool edCommsValueChangesTracked::getSlaveChannelChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(slaveChannelChanged);
    return slaveChannelChanged;
}

void edCommsValueChangesTracked::changeSlaveChannel(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    slaveChannel = s;
    slaveChannelChanged = true;
}

bool edCommsValueChangesTracked::get250KbodChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(two50KbodChanged);
    return two50KbodChanged;
}

void edCommsValueChangesTracked::change250Kbod(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    two50Kbod = s;
    two50KbodChanged = true;
}
void edCommsValueChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor, int oldGWAddr, int oldEDAddr, int oldBunch, int oldNetID )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    QString firstNumber("");
    QString secondNumber("");

    if ( channelChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of channelChanged:" << channel << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_BaseChannel + ByteRegisterCommand +  QString::number(channel);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( gatewayAddressChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of gatewayAddress:" << gatewayAddress << " to gateway.";
        firstNumber = (QString("%1").arg(gatewayAddress, 2, 16, QChar('0'))).toUpper();

        if (endDeviceAddressChanged == true)
        {
            qDebug() << Q_FUNC_INFO << " along with change of end device address: " << endDeviceAddress << " to gateway.";

            secondNumber = (QString("%1").arg(endDeviceAddress, 2, 16, QChar('0'))).toUpper();
            aCommand = commandPrefix + intendedFor + ShortIntegerRegister_GWEDAddress + ShortIntegerRegisterCommandInHex + firstNumber + secondNumber;
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
        else
        {
            secondNumber = (QString("%1").arg(oldEDAddr, 2, 16, QChar('0'))).toUpper();
            qDebug() << Q_FUNC_INFO << " along old end device address: " << secondNumber << " to gateway.";
            aCommand = commandPrefix + intendedFor + ShortIntegerRegister_GWEDAddress + ShortIntegerRegisterCommandInHex + firstNumber + secondNumber;
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
    }
    else if ( endDeviceAddressChanged == true)
    {
        firstNumber = (QString("%1").arg(oldGWAddr, 2, 16, QChar('0'))).toUpper();
        secondNumber = (QString("%1").arg(endDeviceAddress, 2, 16, QChar('0'))).toUpper();


        qDebug() << Q_FUNC_INFO << " change of end device address: " << endDeviceAddress << " to gateway.";
        aCommand = commandPrefix + intendedFor + ShortIntegerRegister_GWEDAddress + ShortIntegerRegisterCommandInHex + firstNumber + secondNumber;
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if ( bunchChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of bunch:" << bunch << " to gateway.";
        firstNumber = (QString("%1").arg(bunch, 2, 16, QChar('0'))).toUpper();

        if (netIDChanged == true)
        {
            secondNumber = (QString("%1").arg(netID, 2, 16, QChar('0'))).toUpper();
            qDebug() << Q_FUNC_INFO << " along with change of netID: " << secondNumber << " to gateway.";
            aCommand = commandPrefix + intendedFor + ShortIntegerRegister_NetworkID + ShortIntegerRegisterCommandInHex + firstNumber + secondNumber;
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
        else
        {
            secondNumber = (QString("%1").arg(oldNetID, 2, 16, QChar('0'))).toUpper();
            qDebug() << Q_FUNC_INFO << " along old NetID: " << secondNumber << " to gateway.";
            aCommand = commandPrefix + intendedFor + ShortIntegerRegister_NetworkID + ShortIntegerRegisterCommandInHex + firstNumber + secondNumber;
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
    }
    else if ( netIDChanged == true)
    {
        firstNumber = (QString("%1").arg(oldBunch, 2, 16, QChar('0'))).toUpper();
        secondNumber = (QString("%1").arg(netID, 2, 16, QChar('0'))).toUpper();

        qDebug() << Q_FUNC_INFO << " change of netID: " << secondNumber << " to gateway.";
        aCommand = commandPrefix + intendedFor + ShortIntegerRegister_NetworkID + ShortIntegerRegisterCommandInHex + firstNumber + secondNumber;
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if ( groupChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of group:" << group << " to gateway.";

        aCommand = commandPrefix + intendedFor + ShortIntegerRegister_GroupID + ShortIntegerRegisterCommandInHex + (QString("%1").arg(group,4,16,QChar('0'))).toUpper();
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( syncwordChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of syncword:" << syncword << " to gateway.";

        aCommand = commandPrefix + intendedFor + ShortIntegerRegister_SyncWord + ShortIntegerRegisterCommandInHex + (QString("%1").arg(syncword,4,14,QChar('0'))).toUpper();
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( gBunchChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of gBunchChanged:" << gBunch << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_GlobalBunchNumber + ByteRegisterCommand +  QString::number(gBunch);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( rBunchChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of rBunchChanged:" << rBunch << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_NumberOfBunchesBeforeRepeat + ByteRegisterCommand +  QString::number(rBunch);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( hoppingChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of hoppingChanged:" << hopping << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_EDFrequencyHopping + ByteRegisterCommand +  QString::number(hopping);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( radioPowerChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of radioPowerChanged:" << radioPower << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_EDRadioPower + ByteRegisterCommand +  QString::number(radioPower);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if ( gwChannelFlagChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of gwChannelFlagChanged:" << gwChannelFlag << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_GWChannel + ByteRegisterCommand +  QString::number(gwChannelFlag);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if ( twelveKbodChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of twelveKbodChanged:" << twelveKbod << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_CommunicationBaudRate + ByteRegisterCommand +  QString::number(twelveKbod);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( stayInRXChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of stayInRXChanged:" << stayInRX << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_StayInRX + ByteRegisterCommand +  QString::number(stayInRX);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( stayInCWChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of stayInCWChanged:" << stayInCW << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_CWave + ByteRegisterCommand +  QString::number(stayInCW);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( repeaterChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of repeaterChanged:" << repeater << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_IsRepeater + ByteRegisterCommand +  QString::number(repeater);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( repeaterPowerChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of repeaterPowerChanged:" << repeaterPower << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_RepeaterPower + ByteRegisterCommand +  QString::number(repeaterPower);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( repeaterChannelChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of repeaterChannelChanged:" << repeaterChannel << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_RepeaterChannel + ByteRegisterCommand +  QString::number(repeaterChannel);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( searchEnabledChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of searchEnabledChanged:" << searchEnabled << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_SearchModeEnable + ByteRegisterCommand +  QString::number(searchEnabled);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( CriticalLevel10Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of criticalLevel10Changed:" << CriticalLevel10 << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_SearchSignalRepeater + ByteRegisterCommand +  QString::number(CriticalLevel10);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( CriticalLevel500Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of criticalLevel500Changed:" << CriticalLevel500 << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_SearchSignalSlave + ByteRegisterCommand +  QString::number(CriticalLevel500);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( slaveChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of slaveChanged:" << slave << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_IsSlave + ByteRegisterCommand +  QString::number(slave);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( slaveChannelChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of slaveChannelChanged:" << slaveChannel << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_SetStartSlaveChannel + ByteRegisterCommand +  QString::number(slaveChannel);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ( two50KbodChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of two50KbodChanged:" << two50Kbod << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_Bandwidth250 + ByteRegisterCommand +  QString::number(two50Kbod);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

}


