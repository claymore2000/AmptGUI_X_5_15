#include "gatewayValuesChangesTracked.h"

static const QString gatewayCommandTermination("\r\n");

gatewayValuesChangesTracked::gatewayValuesChangesTracked( void )
{
    ignoreSignals = true;
    resetAllTrackedGatewayValues();

}

gatewayValuesChangesTracked::~gatewayValuesChangesTracked( void )
{

}

void gatewayValuesChangesTracked::resetAllTrackedGatewayValues( void )
{
    // qDebug() << Q_FUNC_INFO << " time to reinitialize all gateway variables...";
    channelChanged = false;
    channel = 0;
    gatewayAddressChanged = false;
    gatewayAddress = 0;
    endDeviceAddressChanged = false;
    endDeviceAddress = 0;
    bunchSizeChanged = false;
    bunchSize = 0;
    networkSizeChanged = false;
    networkSize = 0;
    hoppingChanged = false;
    hopping = 0;
    powerChanged = false;
    power = "";
    syncwordChanged = false;
    syncword = 0;
    zCountChanged = false;
    zCount = 0;
    cmdCountChanged = false;
    cmdCount = 0;
    fwVersionChanged = false;
    fwVersion = 0;
    modeChanged = false;
    mode = 0;
}

bool gatewayValuesChangesTracked::getGatewayChannelValueChanged( void )
{
    return channelChanged;
}

void gatewayValuesChangesTracked::gatewayChannelValueChanged(int newChannel)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new channel:" << newChannel;
        channelChanged = true;
        channel = newChannel;
    }
}
bool gatewayValuesChangesTracked::getGatewayEndDeviceOrGatewayValueChanged( void )
{
    return (endDeviceAddressChanged || gatewayAddressChanged);
}

void gatewayValuesChangesTracked::gatewayGatewayAddressValueChanged(int newGatewayAddress)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new gateway address:" << newGatewayAddress;
        gatewayAddressChanged = true;
        gatewayAddress = newGatewayAddress;
    }
}

void gatewayValuesChangesTracked::gatewayEndDeviceAddressValueChanged(int newEndDeviceAddress)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new end device address:" << newEndDeviceAddress;
        endDeviceAddressChanged = true;
        endDeviceAddress = newEndDeviceAddress;
    }
}

bool gatewayValuesChangesTracked::getGatewayBunchSizeValueChanged( void )
{
    return bunchSizeChanged;
}

void gatewayValuesChangesTracked::gatewayBunchSizeValueChanged(int newBunchSize)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new bunch size:" << newBunchSize;
        bunchSizeChanged = true;
        bunchSize = newBunchSize;
    }
}


bool gatewayValuesChangesTracked::getGatewayNetworkSizeValueChanged( void )
{
    return networkSizeChanged;
}

void gatewayValuesChangesTracked::gatewayNetworkSizeValueChanged(int newNetworkSize)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new network size:" << newNetworkSize;
        networkSizeChanged = true;
        networkSize = newNetworkSize;
    }
}

bool gatewayValuesChangesTracked::getGatewayHoppingValueChanged( void )
{
    return hoppingChanged;
}

void gatewayValuesChangesTracked::gatewayHoppingValueChanged(int newHopping)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new hopping value:" << newHopping;
        hoppingChanged = true;
        hopping = newHopping;
    }
}

bool gatewayValuesChangesTracked::getGatewayPowerValueChanged( void )
{
    return powerChanged;
}

void gatewayValuesChangesTracked::gatewayPowerValueChanged(const QString newPower)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new power value:" << newPower;
        powerChanged = true;
        power = newPower;
    }
}

bool gatewayValuesChangesTracked::getGatewaySyncWordValueChanged( void )
{
    return syncwordChanged;
}

void gatewayValuesChangesTracked::gatewaySyncWordValueChanged(int newSyncword)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new syncword value:" << newSyncword;
        syncwordChanged = true;
        syncword = newSyncword;
    }
}

bool gatewayValuesChangesTracked::getGatewayModeValueChanged( void )
{
   return modeChanged;
}

void gatewayValuesChangesTracked::gatewayModeValueChanged( int newMode )
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new mode value:" << newMode;
        modeChanged = true;
        mode = newMode;
    }
}

bool gatewayValuesChangesTracked::getGatewayZCountValueChanged( void )
{
    return zCountChanged;
}

void gatewayValuesChangesTracked::gatewayZCountValueChanged(int newZCount)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new zCount value:" << newZCount;
        zCountChanged = true;
        zCount = newZCount;
    }
}

bool gatewayValuesChangesTracked::getGatewayCmdCountValueChanged( void )
{
    return cmdCountChanged;
}

void gatewayValuesChangesTracked::gatewayCmdCountValueChanged(int newCmdCount)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new cmdCount value:" << newCmdCount;
        cmdCountChanged = true;
        cmdCount = newCmdCount;
    }
}

bool gatewayValuesChangesTracked::getGatewayFWVersionValueChanged( void )
{
    return fwVersionChanged;
}

void gatewayValuesChangesTracked::gatewayFWVersionValueChanged(int newFWVersion)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new fwVersion value:" << newFWVersion;
        fwVersionChanged = true;
        fwVersion = newFWVersion;
    }
}
bool gatewayValuesChangesTracked::getIgnoreGatewaySignals( void )
{
    return ignoreSignals;
}

void gatewayValuesChangesTracked::setIgnoreSignalsToChangeGatewayValues( bool s)
{
    // qDebug() << Q_FUNC_INFO << " setting ignoreSignals to " << QString::number(s);
    ignoreSignals = s;
}

void gatewayValuesChangesTracked::writeAllChangedValuesToMemory( bool endDevicesAlso )
{
    qDebug() << Q_FUNC_INFO << " INFO: send changed values to gateway (and possibly some changes to optimizer(s) ...";
    QString aCommand;
    QString endDeviceAlsoCmd("");

    if (channelChanged == true)
    {

        if ( endDevicesAlso == true )
        {
            qDebug() << Q_FUNC_INFO << " INFO: Broadcast change channel of end devices and gateway to " << channel;
            aCommand = "h " + QString::number(channel) + gatewayCommandTermination;
            qDebug() << Q_FUNC_INFO << " INFO: emit command:" + aCommand;
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " INFO: Only change channel of gateway to " << channel;
            aCommand = "h -" + QString::number(channel) + gatewayCommandTermination;
            qDebug() << Q_FUNC_INFO << " INFO: emit command:" + aCommand;
        }
        emit publishCommand(aCommand);
    }

    if ((endDeviceAddressChanged == true) || (gatewayAddressChanged == true))
    {

        QString hGatewayEndDeviceAddress = (QString::number(endDeviceAddress,16).rightJustified(2,'0')).toUpper();
        QString hGatewayGatewayAddress = (QString::number(gatewayAddress,16).rightJustified(2,'0')).toUpper();

        qDebug() << Q_FUNC_INFO << " INFO: Changing Gateway Address to 0x" << hGatewayGatewayAddress << " End Device Address to 0x" << hGatewayEndDeviceAddress;

        if ( endDevicesAlso == true )
        {
            aCommand = "s * 3 H" + hGatewayGatewayAddress + hGatewayEndDeviceAddress + gatewayCommandTermination;
            qDebug() << Q_FUNC_INFO << " INFO: emit broadcast (all end devices) command:" + aCommand;
            emit publishCommand(aCommand);
        }
        aCommand = "B " + hGatewayGatewayAddress + hGatewayEndDeviceAddress + gatewayCommandTermination;
        qDebug() << Q_FUNC_INFO << " INFO: emit command:" + aCommand;
        emit publishCommand(aCommand);
    }
    if (bunchSizeChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " INFO: Changing bunch size to " << bunchSize;
        aCommand = "K 6 " + QString::number(bunchSize) + gatewayCommandTermination;
        qDebug() << Q_FUNC_INFO << " INFO: emit commmand:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (networkSizeChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " INFO: Changing network size to " << networkSize;
        aCommand = "k " + QString::number(networkSize) + gatewayCommandTermination;
        qDebug() << Q_FUNC_INFO << " INFO: emit commmand:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (hoppingChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " INFO: Changing hopping to " << hopping;
        aCommand = "H " + QString::number(hopping) + gatewayCommandTermination;
        qDebug() << Q_FUNC_INFO << " INFO: emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (powerChanged == true)
    {
        QString tPower = QString(power);
        qDebug() << Q_FUNC_INFO << " INFO: Changing power to " << tPower;
        aCommand = "P " + tPower + gatewayCommandTermination;
        qDebug() << Q_FUNC_INFO << " INFO: emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (syncwordChanged == true)
    {
        QString tSyncWord = QString(syncword);
        qDebug() << Q_FUNC_INFO << " INFO: changing syncword to " << tSyncWord;
        if (endDevicesAlso)
        {
            aCommand = "s * 14 H" + tSyncWord + gatewayCommandTermination;
            qDebug() << Q_FUNC_INFO << " INFO: emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
        aCommand = "K 10 " + tSyncWord + gatewayCommandTermination;
        qDebug() << Q_FUNC_INFO << " INFO: emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (modeChanged == true)
    {
        QString tMode = QString(mode);
        qDebug() << Q_FUNC_INFO << " INFO: changing gateway mode to " << tMode;
        aCommand = "Y " + tMode + gatewayCommandTermination;
        qDebug() << "INFO: emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (zCountChanged == true)
    {
        QString tZCount = QString(zCount);
        qDebug() << Q_FUNC_INFO << " INFO: changed ZCount (repeat commands) to " << tZCount;
        aCommand = "Z " + tZCount + gatewayCommandTermination;
        qDebug() << " INFO: emit command:" << aCommand;
        emit publishCommand(aCommand);

    }
}
