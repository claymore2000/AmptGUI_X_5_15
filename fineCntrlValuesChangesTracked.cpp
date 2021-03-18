#include "fineCntrlValuesChangesTracked.h"
#include "amptRegisterConstants.h"

fineCntrlValueChangesTracked::fineCntrlValueChangesTracked( void )
{
    resetAllTrackedValues(true);
}

fineCntrlValueChangesTracked::~fineCntrlValueChangesTracked( void )
{
}

void fineCntrlValueChangesTracked::sendAllChangedValues( void )
{
}

void fineCntrlValueChangesTracked::resetAllTrackedValues ( bool s )
{
    if (s == true)
    {
        vRef0Changed = false;
        vRef0 = 0.0;
        kVRefChanged = false;
        kVRef = 0.0;
        t0Changed = false;
        t0 = 0.0;
        tempCoeffCurrentChanged = false;
        tempCoeffCurrent = 0.0;
        tempCoeffPowerChanged = false;
        tempCoeffPower = 0.0;
        shortCircuitLevelChanged = false;
        shortCircuitLevel = 0;
    }
}


bool fineCntrlValueChangesTracked::getVRef0Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(vRef0Changed);
    return vRef0Changed;
}

void fineCntrlValueChangesTracked::changeVRef0(const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    vRef0 = s;
    vRef0Changed = true;
}


bool fineCntrlValueChangesTracked::getKVRefChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(kVRefChanged);
    return kVRefChanged;
}

void fineCntrlValueChangesTracked::changeKVRef( const double& s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    kVRef = s;
    kVRefChanged = true;
}

bool fineCntrlValueChangesTracked::getT0Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(t0Changed);
    return t0Changed;
}

void fineCntrlValueChangesTracked::changeT0( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    t0 = s;
    t0Changed = true;
}


bool fineCntrlValueChangesTracked::getTempCoeffCurrentChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(tempCoeffCurrentChanged);
    return tempCoeffCurrentChanged;
}

void fineCntrlValueChangesTracked::changeTempCoeffCurrent( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    tempCoeffCurrent = s;
    tempCoeffCurrentChanged = true;
}

bool fineCntrlValueChangesTracked::getTempCoeffPowerChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(tempCoeffPowerChanged);
    return tempCoeffPowerChanged;
}

void fineCntrlValueChangesTracked::changeTempCoeffPower( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    tempCoeffPower = s;
    tempCoeffPowerChanged = true;
}

bool fineCntrlValueChangesTracked::getShortCircuitLevelChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(shortCircuitLevelChanged);
    return shortCircuitLevelChanged;
}

void fineCntrlValueChangesTracked::changeShortCircuitLevel( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    shortCircuitLevel = s;
    shortCircuitLevelChanged = true;
}
void fineCntrlValueChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    if (vRef0Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vRef0:" << vRef0 << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_Vref0 + FloatRegisterCommand +  QString::number(vRef0);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (kVRefChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of kVRef:" << kVRef << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_Kvref + FloatRegisterCommand + QString::number(kVRef);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (t0Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of t0:" << t0 << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_T0 + FloatRegisterCommand + QString::number(t0);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (tempCoeffCurrentChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of temp Coeff. Current:" << tempCoeffCurrent << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_TK_CUR + FloatRegisterCommand + QString::number(tempCoeffCurrent);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (tempCoeffPowerChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of temp Coeff. Power:" << tempCoeffPower << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_TK_POW + FloatRegisterCommand + QString::number(tempCoeffPower);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (shortCircuitLevelChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of short circuit limit:" << shortCircuitLevel << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_OCShortCircuitLimit + ByteRegisterCommand + QString::number(shortCircuitLevel);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);

    }
}



