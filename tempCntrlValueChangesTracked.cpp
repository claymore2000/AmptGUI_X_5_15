#include "tempCntrlValueChangesTracked.h"
#include "amptRegisterConstants.h"

tempCntrlValueChangesTracked::tempCntrlValueChangesTracked( void )
{
    resetAllTrackedValues(true);
}

tempCntrlValueChangesTracked::~tempCntrlValueChangesTracked( void )
{
}

void tempCntrlValueChangesTracked::sendAllChangedValues( void )
{
}

void tempCntrlValueChangesTracked::resetAllTrackedValues ( bool s )
{
    if (s == true)
    {
        ocProtectionChanged = false;
        ocProtection = 0;
        tColdChanged = false;
        tCold = 0;
        tHotChanged = false;
        tHot = 0;
        tSuperHotChanged = false;
        tSuperHot = 0;
        fallbackTimeChanged = false;
        fallbackTime = 0;
    }
}

bool tempCntrlValueChangesTracked::getOCProtectionChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(ocProtectionChanged);
    return ocProtectionChanged;
}

void tempCntrlValueChangesTracked::changeOCProtection(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    ocProtection = s;
    ocProtectionChanged = true;
}


bool tempCntrlValueChangesTracked::getTColdChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(tColdChanged);
    return tColdChanged;
}

void tempCntrlValueChangesTracked::changeTCold( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    tCold = s;
    tColdChanged = true;
}

bool tempCntrlValueChangesTracked::getTHotChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(tHotChanged);
    return tHotChanged;
}

void tempCntrlValueChangesTracked::changeTHot( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    tHot = s;
    tHotChanged = true;
}


bool tempCntrlValueChangesTracked::getTSuperHotChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(tSuperHotChanged);
    return tSuperHotChanged;
}

void tempCntrlValueChangesTracked::changeTSuperHot( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    tSuperHot = s;
    tSuperHotChanged = true;
}

bool tempCntrlValueChangesTracked::getFallbackTimeChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(fallbackTimeChanged);
    return fallbackTimeChanged;
}

void tempCntrlValueChangesTracked::changeFallbackTime( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    fallbackTime = s;
    fallbackTimeChanged = true;
}

void tempCntrlValueChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    if (ocProtectionChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of ocProtection:" << ocProtection << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_T_OC_JUMP + ByteRegisterCommand +  QString::number(ocProtection);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (tColdChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of Ton_Fallback:" << tCold << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_TOnFallback + ByteRegisterCommand + QString::number(tCold);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (tHotChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of Toff_Fallback2:" << tHot << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_TOffFallback + ByteRegisterCommand + QString::number(tHot);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (tSuperHotChanged== true)
    {
        qDebug() << Q_FUNC_INFO << " send change of OC_Fallback:" << tSuperHot << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_OCFallback + ByteRegisterCommand + QString::number(tSuperHot);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (fallbackTimeChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of Fallback Time:" << fallbackTime << " to gateway.";
        aCommand = commandPrefix + intendedFor + ByteRegister_FallbackTime + ByteRegisterCommand + QString::number(fallbackTime);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
}
