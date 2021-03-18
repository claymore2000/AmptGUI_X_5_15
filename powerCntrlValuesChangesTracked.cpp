#include "powerCntrlValuesChangesTracked.h"
#include "amptRegisterConstants.h"

powerCntrlValuesChangesTracked::powerCntrlValuesChangesTracked( void )
{
    resetAllTrackedValues(true);
}

powerCntrlValuesChangesTracked::~powerCntrlValuesChangesTracked( void )
{

}

void powerCntrlValuesChangesTracked::resetAllTrackedValues( bool all )
{
    // qDebug() << Q_FUNC_INFO << " time to reset powerCntrl variables...";

    vinTurnOnChanged = false;
    vinTurnOn = 0;
    vinTurnOffChanged = false;
    vinTurnOff = 0;
    vinStopRadioChanged = false;
    vinStopRadio = 0;
    vinLimit255Changed = false;
    vinLimit255 = 0;
    ovStartupChanged = false;
    ovStartup = 0;
    currentNoiseChanged = false;
    currentNoiseChanged = 0;
    ovStepChanged = false;
    ovStep = 0;
    ocStepChanged = false;
    ocStep = 0;

    if (all == true)
    {
        ovChanged = false;
        ov = 0;
        ocChanged = false;
        oc = 0;
        moduleChanged = false;
        module = "";
        mppChanged = false;
        mpp = "";
    }
}

bool powerCntrlValuesChangesTracked::getOCChanged( void )
{
    return ocChanged;
}

void powerCntrlValuesChangesTracked::changeOC(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring new value:" << s;
        ocChanged = true;
        oc = s;
    }
}

bool powerCntrlValuesChangesTracked::getOVChanged( void )
{
    return ovChanged;
}

void powerCntrlValuesChangesTracked::changeOV(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring new value:" << s;
        ovChanged = true;
        ov = s;
    }
}


bool powerCntrlValuesChangesTracked::getVinTurnOnChanged( void )
{
    return vinTurnOnChanged;
}

void powerCntrlValuesChangesTracked::changeVinTurnOn(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring new value:" << s;
        vinTurnOnChanged = true;
        vinTurnOn = s;
    }
}

bool powerCntrlValuesChangesTracked::getVinTurnOffChanged( void )
{
    return vinTurnOffChanged;
}

void powerCntrlValuesChangesTracked::changeVinTurnOff(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring new value:" << s;
        vinTurnOffChanged = true;
        vinTurnOff = s;
    }
}

bool powerCntrlValuesChangesTracked::getVinStopRadioChanged( void )
{
    return vinStopRadioChanged;
}

void powerCntrlValuesChangesTracked::changeVinStopRadio(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring new value:" << s;
        vinStopRadioChanged = true;
        vinStopRadio = s;
    }
}

bool powerCntrlValuesChangesTracked::getVinLimit255Changed( void )
{
    return vinLimit255Changed;
}

void powerCntrlValuesChangesTracked::changeVinLimit255(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring new value:" << s;
        vinLimit255Changed = true;
        vinLimit255 = s;
    }
}


bool powerCntrlValuesChangesTracked::getOCStepChanged( void )
{
    return ocStepChanged;
}

void powerCntrlValuesChangesTracked::changeOCStep(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new oc step:" << s;
        ocStepChanged = true;
        ocStep = s;
    }
}


bool powerCntrlValuesChangesTracked::getOVStepChanged( void )
{
    return ovStepChanged;
}

void powerCntrlValuesChangesTracked::changeOVStep(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new oc step:" << s;
        ovStepChanged = true;
        ovStep = s;
    }
}

void powerCntrlValuesChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    if (currentNoiseChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of currentNoise:" << currentNoise << " to gateway.";
        aCommand = commandPrefix + intendedFor + ShortIntegerRegister_CurrentNoise +  ShortIntegerRegisterCommand + QString::number(currentNoise);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vinTurnOnChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vinTurnOn:" << vinTurnOn << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_VinTurnOn + ByteRegisterCommand + QString::number(vinTurnOn);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vinTurnOffChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vinTurnOff:" << vinTurnOff << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_VinTurnOff + ByteRegisterCommand + QString::number(vinTurnOff);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vinStopRadioChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vinStopRadio:" << vinStopRadio << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_VinDisableRadio + ByteRegisterCommand + QString::number(vinStopRadio);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vinLimit255Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vinLimit255:" << vinLimit255 << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_VinLimit + ByteRegisterCommand + QString::number(vinLimit255);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (ovStepChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of ovStep:" << ovStep << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_OVStep + ByteRegisterCommand + QString::number(ovStep);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (ocStepChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of ocStep:" << ocStep << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_OCStep + ByteRegisterCommand + QString::number(ocStep);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (ovStartupChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of ovStartup:" << ovStartup << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_OVStartup + ByteRegisterCommand + QString::number(ovStartup);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (ovChanged == true)
    {
      qDebug() << Q_FUNC_INFO << " send change of ov:" << ov << " to gateway.";
      aCommand = commandPrefix + intendedFor + ByteRegister_OverVoltageLimit + ByteRegisterCommand + QString::number(ov);
      qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
      emit publishCommand(aCommand);
    }
    if (ocChanged == true)
    {
	  qDebug() << Q_FUNC_INFO << " send change of oc:" << oc << " to gateway.";
      aCommand = commandPrefix + intendedFor + ByteRegister_OverCurrentLimit + ByteRegisterCommand + QString::number(oc);
      qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
      emit publishCommand(aCommand);
    }
    if (moduleChanged == true)
    {
        QString mValue(onAsInt);
        if (module == "Off")
            mValue = offAsInt;

        qDebug() << Q_FUNC_INFO << " send change of module:" << mValue << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_ModuleOutput + ByteRegisterCommand + mValue;
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (mppChanged == true)
    {
        QString mValue(onAsInt);
        if (mpp == "Off")
            mValue = offAsInt;

        qDebug() << Q_FUNC_INFO << " send change of mpp:" << mValue << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_MPPTracking + ByteRegisterCommand + mValue;
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }


}

bool powerCntrlValuesChangesTracked::getCurrentNoiseChanged( void )
{
    return currentNoiseChanged;
}

void powerCntrlValuesChangesTracked::changeCurrentNoise(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new oc step:" << s;
        currentNoiseChanged = true;
        currentNoise = s;
    }
}

bool powerCntrlValuesChangesTracked::getOVStartupChanged(void )
{
    return ovStartupChanged;
}

void powerCntrlValuesChangesTracked::changeOVStartup(int s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new oc step:" << s;
        ovStartupChanged = true;
        ovStartup = s;
    }
}

bool powerCntrlValuesChangesTracked::getModuleChanged( void )
{
    return moduleChanged;
}

void powerCntrlValuesChangesTracked::changeModule(const QString s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new oc step:" << s;
        moduleChanged = true;
        module = s;
    }
}

bool powerCntrlValuesChangesTracked::getMPPChanged( void )
{
    return mppChanged;
}

void powerCntrlValuesChangesTracked::changeMPP(const QString s)
{
    if (ignoreSignals == false)
    {
        qDebug() << Q_FUNC_INFO << " not ignoring a new oc step:" << s;
        mppChanged = true;
        mpp = s;
    }
}
