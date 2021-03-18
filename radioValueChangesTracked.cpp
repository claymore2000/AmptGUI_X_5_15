#include "radioValueChangesTracked.h"
#include "amptRegisterConstants.h"

radioValueChangesTracked::radioValueChangesTracked( void )
{
    resetAllTrackedValues(true);
}

radioValueChangesTracked::~radioValueChangesTracked( void )
{
}

void radioValueChangesTracked::sendAllChangedValues( void )
{
}

void radioValueChangesTracked::resetAllTrackedValues( bool s )
{

  if (s == true)
  {
      dFK0Changed = false;
      dFK0 = 0.0;
      dFK1Changed = false;
      dFK1 = 0.0;
      dFK2Changed = false;
      dFK2 = 0.0;
      dFK3Changed = false;
      dFK3 = 0.0;
      pureOffsetChanged = false;
      pureOffset = 0;
      lowCurrentLimitTo255Changed = false;
      lowCurrentLimitTo255 = 0;
  }

}


bool radioValueChangesTracked::getDFK0Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(dFK0Changed);
    return dFK0Changed;
}

void radioValueChangesTracked::changeDFK0(const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    dFK0 = s;
    dFK0Changed = true;
}

bool radioValueChangesTracked::getDFK1Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(dFK1Changed);
    return dFK1Changed;
}

void radioValueChangesTracked::changeDFK1(const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    dFK1 = s;
    dFK1Changed = true;
}

bool radioValueChangesTracked::getDFK2Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(dFK2Changed);
    return dFK2Changed;
}

void radioValueChangesTracked::changeDFK2(const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    dFK2 = s;
    dFK2Changed = true;
}

bool radioValueChangesTracked::getDFK3Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(dFK3Changed);
    return dFK3Changed;
}

void radioValueChangesTracked::changeDFK3(const double & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    dFK3 = s;
    dFK3Changed = true;
}

bool radioValueChangesTracked::getPureOffsetChanged( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(pureOffsetChanged);
    return pureOffsetChanged;
}

void radioValueChangesTracked::changePureOffset( const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    pureOffset = s;
    pureOffsetChanged = true;
}

bool radioValueChangesTracked::getLowCurrentLimitTo255Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(lowCurrentLimitTo255Changed);
    return lowCurrentLimitTo255Changed;
}

void radioValueChangesTracked::changeLowCurrentLimitTo255(const int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    lowCurrentLimitTo255 = s;
    lowCurrentLimitTo255Changed = true;
}

void radioValueChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    if (dFK0Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of dFK0:" << dFK0 << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_DFK0 + FloatRegisterCommand +  QString::number(dFK0);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (dFK1Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of dFK1:" << dFK1 << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_DFK1 + FloatRegisterCommand + QString::number(dFK1);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (dFK2Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of dFK2:" << dFK2 << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_DFK2 + FloatRegisterCommand + QString::number(dFK2);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (dFK3Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of dFK3:" << dFK3 << " to gateway.";
        aCommand = commandPrefix + intendedFor + FloatRegister_DFK3 + FloatRegisterCommand + QString::number(dFK3);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (pureOffsetChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of pureOffset (MicroOffset):" << pureOffset << " to gateway.";
        aCommand = commandPrefix + intendedFor + ShortIntegerRegister_MicroOffset + ShortIntegerRegisterCommand + QString::number(pureOffset);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (lowCurrentLimitTo255Changed == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of lowCurrentLimitTo255:" << lowCurrentLimitTo255 << " to gateway.";
        aCommand = commandPrefix + intendedFor + ShortIntegerRegister_LowCurrentLimitTo255 + ShortIntegerRegisterCommand + QString::number(lowCurrentLimitTo255);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

}
