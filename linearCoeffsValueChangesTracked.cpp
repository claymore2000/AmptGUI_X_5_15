#include "linearCoeffsValueChangesTracked.h"
#include "amptRegisterConstants.h"

linearCoeffsValueChangesTracked::linearCoeffsValueChangesTracked( void )
{
    resetAllTrackedValues();
}

linearCoeffsValueChangesTracked::~linearCoeffsValueChangesTracked( void )
{
}

void linearCoeffsValueChangesTracked::sendAllChangedValues( void )
{
}

void linearCoeffsValueChangesTracked::resetAllTrackedValues ( void )
{
    vOutCoefficientChanged = false;
    vOutCoefficient = 0.0;
    vOutOffsetChanged = false;
    vOutOffset = 0.0;
    vIn1CoefficientChanged = false;
    vIn1Coefficient = 0.0;
    vIn1OffsetChanged = false;
    vIn1Offset = 0.0;
    vIn2CoefficientChanged = false;
    vIn2Coefficient = 0.0;
    vIn2OffsetChanged = false;
    vIn2Offset = 0.0;
    iOutCoefficientChanged = false;
    iOutCoefficient = 0.0;
    iOutOffsetChanged = false;
    iOutOffset = 0.0;
    iIn1CoefficientChanged = false;
    iIn1Coefficient = 0.0;
    iIn1OffsetChanged = false;
    iIn1Offset = 0.0;
    iIn2CoefficientChanged = false;
    iIn2Coefficient = 0.0;
    iIn2OffsetChanged = false;
    iIn2Offset = 0.0;
    textCoefficientChanged = false;
    textCoefficient = 0.0;
    textOffsetChanged = false;
    textOffset = 0.0;
}

bool linearCoeffsValueChangesTracked::getVOutCoefficientChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(vOutCoefficientChanged);
    return vOutCoefficientChanged;
}

void linearCoeffsValueChangesTracked::changeVOutCoefficient( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    vOutCoefficient = s;
    vOutCoefficientChanged = true;
}

bool linearCoeffsValueChangesTracked::getVOutOffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(vOutOffsetChanged);
    return vOutOffsetChanged;
}

void linearCoeffsValueChangesTracked::changeVOutOffset( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    vOutOffset = s;
    vOutOffsetChanged = true;
}


bool linearCoeffsValueChangesTracked::getVIn1CoefficientChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(vIn1CoefficientChanged);
    return vIn1CoefficientChanged;
}

void linearCoeffsValueChangesTracked::changeVIn1Coefficient( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    vIn1Coefficient = s;
    vIn1CoefficientChanged = true;
}

bool linearCoeffsValueChangesTracked::getVIn1OffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(vIn1OffsetChanged);
    return vIn1OffsetChanged;
}

void linearCoeffsValueChangesTracked::changeVIn1Offset( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    vIn1Offset = s;
    vIn1OffsetChanged = true;
}

bool linearCoeffsValueChangesTracked::getVIn2CoefficientChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(vIn2CoefficientChanged);
    return vIn2CoefficientChanged;
}

void linearCoeffsValueChangesTracked::changeVIn2Coefficient( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    vIn2Coefficient = s;
    vIn2CoefficientChanged = true;
}

bool linearCoeffsValueChangesTracked::getVIn2OffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(vIn2OffsetChanged);
    return vIn2OffsetChanged;
}

void linearCoeffsValueChangesTracked::changeVIn2Offset( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    vIn2Offset = s;
    vIn2OffsetChanged = true;
}

bool linearCoeffsValueChangesTracked::getIOutCoefficientChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(iOutCoefficientChanged);
    return iOutCoefficientChanged;
}

void linearCoeffsValueChangesTracked::changeIOutCoefficient( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    iOutCoefficient = s;
    iOutCoefficientChanged = true;
}

bool linearCoeffsValueChangesTracked::getIOutOffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(iOutOffsetChanged);
    return iOutOffsetChanged;
}

void linearCoeffsValueChangesTracked::changeIOutOffset( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    iOutOffset = s;
    iOutOffsetChanged = true;
}


bool linearCoeffsValueChangesTracked::getIIn1CoefficientChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(iIn1CoefficientChanged);
    return iIn1CoefficientChanged;
}

void linearCoeffsValueChangesTracked::changeIIn1Coefficient( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    iIn1Coefficient = s;
    iIn1CoefficientChanged = true;
}

bool linearCoeffsValueChangesTracked::getIIn1OffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(iIn1OffsetChanged);
    return iIn1OffsetChanged;
}

void linearCoeffsValueChangesTracked::changeIIn1Offset( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    iIn1Offset = s;
    iIn1OffsetChanged = true;
}

bool linearCoeffsValueChangesTracked::getIIn2CoefficientChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(iIn2CoefficientChanged);
    return iIn2CoefficientChanged;
}

void linearCoeffsValueChangesTracked::changeIIn2Coefficient( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    iIn2Coefficient = s;
    iIn2CoefficientChanged = true;
}

bool linearCoeffsValueChangesTracked::getIIn2OffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(iIn2OffsetChanged);
    return iIn2OffsetChanged;
}

void linearCoeffsValueChangesTracked::changeIIn2Offset( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    iIn2Offset = s;
    iIn2OffsetChanged = true;
}


bool linearCoeffsValueChangesTracked::getTextCoefficientChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(textCoefficientChanged);
    return textCoefficientChanged;
}

void linearCoeffsValueChangesTracked::changeTextCoefficient( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    textCoefficient = s;
    textCoefficientChanged = true;
}

bool linearCoeffsValueChangesTracked::getTextOffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(textOffsetChanged);
    return textOffsetChanged;
}

void linearCoeffsValueChangesTracked::changeTextOffset( const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    textOffset = s;
    textOffsetChanged = true;
}

void linearCoeffsValueChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    if (vOutCoefficientChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vOut Coefficient:" << vOutCoefficient << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_LinearCoefficientForVOut + FloatRegisterCommand +  QString::number(vOutCoefficient);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vOutOffsetChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vOut Offset:" << vOutOffset << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_OffsetForVOut + FloatRegisterCommand +  QString::number(vOutOffset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vIn1CoefficientChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vin1 Coefficient:" << vIn1Coefficient << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_LinearCoefficientForPin_Vin + FloatRegisterCommand +  QString::number(vIn1Coefficient);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vIn1OffsetChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vin1 Offset:" << vIn1Offset << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_OffsetForPin_Vin + FloatRegisterCommand +  QString::number(vIn1Offset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (iOutCoefficientChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iOut Coefficient:" << iOutCoefficient << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_LinearCoefficientForIOut + FloatRegisterCommand +  QString::number(iOutCoefficient);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (iOutOffsetChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iOut Offset:" << iOutOffset << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_OffsetForIOut + FloatRegisterCommand +  QString::number(iOutOffset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vIn2CoefficientChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vin2 Coefficient:" << vIn2Coefficient << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_LinearCoefficientForVin_Vin2 + FloatRegisterCommand +  QString::number(vIn2Coefficient);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (vIn2OffsetChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of vin2 Offset:" << vIn1Offset << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_OffsetForVin_Vin2 + FloatRegisterCommand +  QString::number(vIn2Offset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (iIn1CoefficientChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iin1 Coefficient:" << iIn1Coefficient << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_LinearCoefficientForIin1 + FloatRegisterCommand +  QString::number(iIn1Coefficient);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (iIn1OffsetChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iin1 Offset:" << iIn1Offset << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_OffsetForIin1 + FloatRegisterCommand +  QString::number(iIn1Offset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (iIn2CoefficientChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iin2 Coefficient:" << iIn2Coefficient << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_LinearCoefficientForTin_Iin2 + FloatRegisterCommand +  QString::number(iIn2Coefficient);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (iIn2OffsetChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iin2 Offset:" << iIn1Offset << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_OffsetForTin_Iin2 + FloatRegisterCommand +  QString::number(iIn2Offset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (textCoefficientChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of text Coefficient:" << textCoefficient << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_LinearCoefficientForText + FloatRegisterCommand +  QString::number(textCoefficient);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (textOffsetChanged== true)
    {
        qDebug() << Q_FUNC_INFO << " send change of text Offset:" << textOffset << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_OffsetForText + FloatRegisterCommand +  QString::number(textOffset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
}





