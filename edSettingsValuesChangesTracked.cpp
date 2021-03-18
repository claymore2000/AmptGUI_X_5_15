#include "edSettingsValuesChangesTracked.h"
#include "amptRegisterConstants.h"

edSettingsValueChangesTracked::edSettingsValueChangesTracked( void )
{
    resetAllTrackedValues(true);
}

edSettingsValueChangesTracked::~edSettingsValueChangesTracked( void )
{
}

void edSettingsValueChangesTracked::sendAllChangedValues( void )
{

}


void edSettingsValueChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    if (syncFrequencyChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of syncFrequency:" << syncFrequency << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_SyncFrequency + ByteRegisterCommand +  QString::number(syncFrequency);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (syncPhaseChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of syncPhase:" << syncPhase << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_SyncPhase + ByteRegisterCommand +  QString::number(syncPhase);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (fuseCommunicationChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of fuseCommunication:" << fuseCommunication << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_FuseCommunication + ByteRegisterCommand +  QString::number(fuseCommunication);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (fuseElectricalChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of fuseElectrical:" << fuseElectrical << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_FuseOVAndOC + ByteRegisterCommand +  QString::number(fuseElectrical);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
}

void edSettingsValueChangesTracked::resetAllTrackedValues ( bool s )
{
    if (s == true)
    {
        syncFrequencyChanged = false;
        syncFrequency = 0;
        syncPhaseChanged = false;
        syncPhase = 0;
        fuseCommunicationChanged = false;
        fuseCommunication = 0;
        fuseElectricalChanged = false;
        fuseElectrical = 0;
    }
}

bool edSettingsValueChangesTracked::getSyncPhaseChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(syncPhaseChanged);
    return syncPhaseChanged;
}

void edSettingsValueChangesTracked::changeSyncPhase( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    syncPhase = s;
    syncPhaseChanged = true;
}

bool edSettingsValueChangesTracked::getSyncFrequencyChanged()
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(syncFrequencyChanged);
    return syncFrequencyChanged;
}

void edSettingsValueChangesTracked::changeSyncFrequency(const int &s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    syncFrequency = s;
    syncFrequencyChanged = true;
}

bool edSettingsValueChangesTracked::getFuseCommunicationChanged()
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(fuseCommunicationChanged);
    return fuseCommunicationChanged;
}

void edSettingsValueChangesTracked::changeFuseCommunication(const int &s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    fuseCommunication = s;
    fuseCommunicationChanged = true;
}

bool edSettingsValueChangesTracked::getFuseElectricalChanged()
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(fuseElectricalChanged);
    return fuseElectricalChanged;
}

void edSettingsValueChangesTracked::changeFuseElectrical(const int &s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    fuseElectrical = s;
    fuseElectricalChanged = true;
}



