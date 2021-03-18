#include "protections1300VValueChangesTracked.h"
#include "amptRegisterConstants.h"
#include "amptparameterblockconstants.h"

protectionsValueChangesTracked::protectionsValueChangesTracked( void )
{
    resetAllTrackedValues(true);
}

protectionsValueChangesTracked::~protectionsValueChangesTracked( void )
{
}

void protectionsValueChangesTracked::sendAllChangedValues( void )
{
}

void protectionsValueChangesTracked::resetAllTrackedValues ( bool s )
{
    qDebug() << Q_FUNC_INFO << " entering ...";

    if (s)
        qDebug() << Q_FUNC_INFO << " INFO: called with argument of " << s;

    fetCountChanged = false;
    fetCount = 0;
    fetThresholdChanged = false;
    fetThreshold = 0;
    fetDeltaCurrentChanged = false;
    fetDeltaCurrent = 0;

    protection1Changed = false;
    protection1 = 0;
    protection2Changed = false;
    protection2 = 0;
    protection3Changed = false;
    protection3 = 0;
    protection4Changed = false;
    protection4 = 0;

    amfTimer1Changed = false;
    amfTimer1 = 0;
    amfTimer2Changed = false;
    amfTimer2 = 0;
    amfV_OVChanged = false;
    amfV_OV = 0;
    amfI_OCChanged = false;
    amfI_OC = 0;
    amfDebugChanged = false;
    amfDebug = 0;
    amfMPPOffCyclesChanged = false;
    amfMPPOffCycles = 0;
    amfMPPTimesOffChanged = false;
    amfMPPTimesOff = 0;

    efInputCurrentThresholdChanged = false;
    efInputCurrentThreshold = 0;
    efOccurrenceThresholdChanged = false;
    efOccurrenceThreshold = 0;
    efCountDownTimerChanged = false;
    efCountDownTimer = 0;
    efAlphaNumeratorChanged = false;
    efAlphaNumerator = 0;

    iinLimitChanged = false;
    iinLimit = 0;
    iinLimitOCStepsChanged = false;
    iinLimitOCSteps = 0;
    iinLimitOCDelayChanged = false;
    iinLimitOCDelay = 0;
    iinLimitTempAmbientAdjustChanged = false;
    iinLimitTempAmbientAdjust = 0;
}

bool protectionsValueChangesTracked::getFETCountChanged( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(fetCountChanged);
    return fetCountChanged;
}

void protectionsValueChangesTracked::changeFETCount(const int & s)
{
    // qDebug() << Q_FUNC_INFO << " new value:" << s;
    fetCount = s;
    fetCountChanged = true;
}

bool protectionsValueChangesTracked::getIinLimitChanged( void )
{
    return iinLimitChanged;
}
void protectionsValueChangesTracked::changeIinLimit( const unsigned int & s)
{
    iinLimit = s;
    iinLimitChanged = true;
}

bool protectionsValueChangesTracked::getIinLimitOCStepsChanged( void )
{
    return iinLimitOCStepsChanged;
}

void protectionsValueChangesTracked::changeIinLimitOCSteps(const unsigned int & s)
{
    iinLimitOCSteps = s;
    iinLimitOCStepsChanged = true;
}

bool protectionsValueChangesTracked::getIinLimitOCDelayChanged( void )
{
    return iinLimitOCDelayChanged;
}

void protectionsValueChangesTracked::changeIinLimitOCDelay(const unsigned int & s)
{
    iinLimitOCDelay = s;
    iinLimitOCDelayChanged = true;
}

bool protectionsValueChangesTracked::getIinLimitTempAmbientAdjustChanged( void )
{
    return iinLimitTempAmbientAdjustChanged;
}

void protectionsValueChangesTracked::changeIinLimitTempAmbientAdjust(const signed int &s)
{
    iinLimitTempAmbientAdjust = s;
    iinLimitTempAmbientAdjustChanged = true;
}

bool protectionsValueChangesTracked::getEFInputCurrentThresholdChanged( void )
{
    return efInputCurrentThresholdChanged;
}

void protectionsValueChangesTracked::changeEFInputCurrentThreshold( const unsigned int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    efInputCurrentThreshold = s;
    efInputCurrentThresholdChanged = true;
}

bool protectionsValueChangesTracked::getEFOccurrenceThresholdChanged( void )
{
    return efOccurrenceThresholdChanged;
}

void protectionsValueChangesTracked::changeEFOccurrenceThreshold( const unsigned int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    efOccurrenceThreshold = s;
    efOccurrenceThresholdChanged = true;
}

bool protectionsValueChangesTracked::getEFCountDownTimerChanged( void )
{
    return efCountDownTimerChanged;
}

void protectionsValueChangesTracked::changeEFCountDownTimer( const unsigned int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    efCountDownTimer = s;
    efCountDownTimerChanged = true;
}

bool protectionsValueChangesTracked::getEFAlphaNumeratorChanged( void )
{
    return efAlphaNumeratorChanged;
}

void protectionsValueChangesTracked::changeEFAlphaNumerator( const unsigned int & s )
{

    qDebug() << Q_FUNC_INFO << " new value:" << s;
    efAlphaNumerator = s;
    efAlphaNumeratorChanged = true;
}

bool protectionsValueChangesTracked::getFETThresholdChanged( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(fetThresholdChanged);
    return fetThresholdChanged;
}

void protectionsValueChangesTracked::changeFETThreshold(const int &s)
{
    // qDebug() << Q_FUNC_INFO << " new value:" << s;
    fetThreshold = s;
    fetThresholdChanged = true;
}

bool protectionsValueChangesTracked::getFETDeltaCurrentChanged( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(fetDeltaCurrentChanged);
    return fetDeltaCurrentChanged;
}

void protectionsValueChangesTracked::changeFETDeltaCurrent(const int &s)
{
    // qDebug() << Q_FUNC_INFO << " new value:" << s;
    fetDeltaCurrent = s;
    fetDeltaCurrentChanged = true;
}


bool protectionsValueChangesTracked::getProtection1Changed( void )
{
    qDebug() << Q_FUNC_INFO << " returning " << QString::number(protection1Changed);
    return protection1Changed;
}

void protectionsValueChangesTracked::changeProtection1( const unsigned int & s)
{
    qDebug() << Q_FUNC_INFO << " new value:" << s;
    protection1 = s;
    protection1Changed = true;
}

bool protectionsValueChangesTracked::getProtection2Changed( void )
{
   // qDebug() << Q_FUNC_INFO << " returning " << QString::number(protection2Changed);
    return protection2Changed;
}

void protectionsValueChangesTracked::changeProtection2( const unsigned int & s)
{
    // qDebug() << Q_FUNC_INFO << " new value:" << s;
    protection2 = s;
    protection2Changed = true;
}

bool protectionsValueChangesTracked::getProtection3Changed( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(protection3Changed);
    return protection3Changed;
}

void protectionsValueChangesTracked::changeProtection3( const unsigned int & s)
{
   //  qDebug() << Q_FUNC_INFO << " new value:" << s;
    protection3 = s;
    protection3Changed = true;
}

bool protectionsValueChangesTracked::getProtection4Changed( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(protection4Changed);
    return protection4Changed;
}

void protectionsValueChangesTracked::changeProtection4( const unsigned int & s)
{
    // qDebug() << Q_FUNC_INFO << " new value:" << s;
    protection4 = s;
    protection4Changed = true;
}

bool protectionsValueChangesTracked::getAMFTimer1Changed( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(amfTimer1Changed);
    return amfTimer1Changed;
}

void protectionsValueChangesTracked::changeAMFTimer1( const unsigned int & s)
{
    // qDebug() << Q_FUNC_INFO << " new value:" << s;
    amfTimer1 = s;
    amfTimer1Changed = true;
}

bool protectionsValueChangesTracked::getAMFTimer2Changed( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(amfTimer2Changed);
    return amfTimer2Changed;
}

void protectionsValueChangesTracked::changeAMFTimer2( const unsigned int & s)
{
    //qDebug() << Q_FUNC_INFO << " new value:" << s;
    amfTimer2 = s;
    amfTimer2Changed = true;
}

bool protectionsValueChangesTracked::getAMFV_OVChanged( void )
{
    //qDebug() << Q_FUNC_INFO << " returning " << QString::number(amfV_OVChanged);
    return amfV_OVChanged;
}
void protectionsValueChangesTracked::changeAMFV_OV( const unsigned int & s)
{
    //qDebug() << Q_FUNC_INFO << " new value:" << s;
    amfV_OV = s;
    amfV_OVChanged = true;
}

bool protectionsValueChangesTracked::getAMFI_OCChanged( void )
{
    //qDebug() << Q_FUNC_INFO << " returning " << QString::number(amfI_OCChanged);
    return amfI_OCChanged;
}
void protectionsValueChangesTracked::changeAMFI_OC( const unsigned int & s)
{
    // qDebug() << Q_FUNC_INFO << " new value:" << s;
    amfI_OC = s;
    amfI_OCChanged = true;
}

bool protectionsValueChangesTracked::getAMFMPPOffCyclesChanged( void )
{
    // qDebug() << Q_FUNC_INFO << " returning " << QString::number(amfMPPOffCycles);
    return amfMPPOffCyclesChanged;
}
void protectionsValueChangesTracked::changeAMFMPPOffCycles(const unsigned int &s)
{
    //qDebug() << Q_FUNC_INFO << " new value:" << s;
    amfMPPOffCycles = s;
    amfMPPOffCyclesChanged = true;
}

bool protectionsValueChangesTracked::getAMFMPPTimesOffChanged( void )
{
    //qDebug() << Q_FUNC_INFO << " returning " << QString::number(amfMPPTimesOff);
    return amfMPPTimesOffChanged;
}
void protectionsValueChangesTracked::changeAMFMPPTimesOff(const unsigned int &s)
{
    //qDebug() << Q_FUNC_INFO << " new value:" << s;
    amfMPPTimesOff = s;
    amfMPPTimesOffChanged = true;
}

bool protectionsValueChangesTracked::getAMFDebugChanged( void )
{
    //qDebug() << Q_FUNC_INFO << " returning " << QString::number(amfDebug);
    return amfDebugChanged;
}
void protectionsValueChangesTracked::changeAMFDebug(const unsigned int &s)
{
    //qDebug() << Q_FUNC_INFO << " new value:" << s;
    amfDebug = s;
    amfDebugChanged = true;
}

void protectionsValueChangesTracked::sendAllChangedValuesToMemory( const QString intendedFor, const QString theFamily )
{
    qDebug() << Q_FUNC_INFO << " send changed values to optimizer " << intendedFor << " ...";
    QString aCommand;
    // Need MAC address or *
    QString commandPrefix("s m");
    if (intendedFor == "*")
    {
        commandPrefix = "s ";
    }

    if (efInputCurrentThresholdChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of efInputCurrentThreshold:" << efInputCurrentThreshold << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_SetEFInputCurrentThreshold + ShortIntegerRegisterCommand +  QString::number(efInputCurrentThreshold);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (efOccurrenceThresholdChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of efOccurrenceThreshold:" << efOccurrenceThreshold << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_SetEFOccurrentThreshold + ByteRegisterCommand +  QString::number(efOccurrenceThreshold);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (efCountDownTimerChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of efCountDownTimer:" << efCountDownTimer << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_SetEFCountDownTimer + ByteRegisterCommand +  QString::number(efCountDownTimer);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (efAlphaNumeratorChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of efAlphaNumerator:" << efAlphaNumerator << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_SetEFAlphaNumerator + ByteRegisterCommand +  QString::number(efAlphaNumerator);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (fetCountChanged == true)
    {
        // qDebug() << Q_FUNC_INFO << " send change of fetCount:" << fetCount << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_FETFailureCount + ShortIntegerRegisterCommand +  QString::number(fetCount);
        // qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (fetThresholdChanged == true)
    {
        //qDebug() << Q_FUNC_INFO << " send change of fetThreshold:" << fetThreshold << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_FETCurrentThreshold + ShortIntegerRegisterCommand +  QString::number(fetThreshold);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (fetDeltaCurrentChanged == true)
    {
        //qDebug() << Q_FUNC_INFO << " send change of fetThreshold:" << fetDeltaCurrent << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_FETDeltaI + ShortIntegerRegisterCommand +  QString::number(fetDeltaCurrent);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (protection1Changed == true)
    {
        if ((theFamily == Family1300V) || (theFamily == Family1300V_2nd))
        {
            //qDebug() << Q_FUNC_INFO << " send change of VhvVoutLimit:" << protection1 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_VhvLimitVout + ShortIntegerRegisterCommand +  QString::number(protection1);
            //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
        else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
        {
            qDebug() << Q_FUNC_INFO << " send change of VoutLimitCount:" << protection1 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_SetVoutLimitCount + ShortIntegerRegisterCommand +  QString::number(protection1);
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }

    }
    if (protection2Changed == true)
    {
        if ((theFamily == Family1300V) || (theFamily == Family1300V_2nd))
        {
            //qDebug() << Q_FUNC_INFO << " send change of IhvVoutLimit:" << protection2 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_IhvLimitVout + ShortIntegerRegisterCommand +  QString::number(protection2);
            //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
        else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
        {
            qDebug() << Q_FUNC_INFO << " send change of VoutLimit:" << protection2 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_SetVoutLimit + ShortIntegerRegisterCommand +  QString::number(protection2);
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
    }
    if (protection3Changed == true)
    {
        if ((theFamily == Family1300V) || (theFamily == Family1300V_2nd))
        {
            //qDebug() << Q_FUNC_INFO << " send change of VhvVinsLimit:" << protection3 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_VhvLimitVins + ShortIntegerRegisterCommand +  QString::number(protection3);
            //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
        else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
        {
            qDebug() << Q_FUNC_INFO << " send change of IoutLimitCount:" << protection3 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_SetIoutLimitCount + ShortIntegerRegisterCommand +  QString::number(protection3);
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
    }
    if (protection4Changed == true)
    {
        if ((theFamily == Family1300V) || (theFamily == Family1300V_2nd))
        {
            //qDebug() << Q_FUNC_INFO << " send change of IhvVinsLimit:" << protection4 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_IhvLimitVins + ShortIntegerRegisterCommand +  QString::number(protection4);
            //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
        else if ((theFamily == Family1500V) || (theFamily == Family1500V_30) || (theFamily == Family1500V_2nd))
        {
            qDebug() << Q_FUNC_INFO << " send change of IoutLimit:" << protection4 << " to gateway.";
            aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_SetIoutLimit + ShortIntegerRegisterCommand +  QString::number(protection4);
            qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
            emit publishCommand(aCommand);
        }
    }
    if (amfTimer1Changed == true)
    {
        //qDebug() << Q_FUNC_INFO << " send change of amfTimer1:" << amfTimer1 << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_AMFTimer1 + ByteRegisterCommand +  QString::number(amfTimer1);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (amfTimer2Changed == true)
    {
        //qDebug() << Q_FUNC_INFO << " send change of amfTimer2:" << amfTimer2 << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_AMFTimer2 + ByteRegisterCommand +  QString::number(amfTimer2);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (amfV_OVChanged == true)
    {
        //qDebug() << Q_FUNC_INFO << " send change of amfV_OV:" << amfV_OV << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_AMFV_OV + ShortIntegerRegisterCommand +  QString::number(amfV_OV);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (amfI_OCChanged == true)
    {
        //qDebug() << Q_FUNC_INFO << " send change of amfI_OC:" << amfI_OC << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_AMFI_OC + ShortIntegerRegisterCommand +  QString::number(amfI_OC);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if ((amfMPPOffCyclesChanged == true) || (amfMPPTimesOffChanged == true))
    {
        // qDebug() << Q_FUNC_INFO << " send change of amfMPPOffCycles:" << amfMPPOffCycles << " and/or change of amfMPPTimesOff:" << amfMPPTimesOff << " to gateway.";

        // qDebug() << Q_FUNC_INFO << " (0xF0 & (amfMPPOffCycles < 4)) => " << (0x00F0 & (amfMPPOffCycles << 4)) << " from " << (amfMPPOffCycles << 4);
        unsigned char value = ((0x00F0 & (amfMPPOffCycles << 4)) | (0x000F & amfMPPTimesOff));
        aCommand = commandPrefix + intendedFor +  ByteRegister_AMF_Timer2MPPOffCyclesAndTimesToCycle + ByteRegisterCommandInHex +  QString::number(value,16);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }
    if (amfDebugChanged == true)
    {
        // qDebug() << Q_FUNC_INFO << " send change of amfDebug:" << amfDebug << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_AMF_Debug + ByteRegisterCommand +  QString::number(amfDebug);
        //qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (iinLimitChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iinLimit:" << iinLimit << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ShortIntegerRegister_IinLimit + ShortIntegerRegisterCommand +  QString::number(iinLimit);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (iinLimitOCStepsChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iinLimitOCSteps:" << iinLimitOCSteps << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_SetIinLimitOCSteps + ByteRegisterCommand +  QString::number(iinLimitOCSteps);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (iinLimitOCDelayChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iinLimitOCDelay:" << iinLimitOCDelay << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_SetIinLimitOCDelay + ByteRegisterCommand +  QString::number(iinLimitOCDelay);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

    if (iinLimitTempAmbientAdjustChanged == true)
    {
        qDebug() << Q_FUNC_INFO << " send change of iinLimitTempAmbientAdjust:" << iinLimitTempAmbientAdjust << " to gateway.";
        aCommand = commandPrefix + intendedFor +  ByteRegister_SetIinLimitTempAmbientAdjust + ByteRegisterCommand +  QString::number(iinLimitTempAmbientAdjust);
        qDebug() << Q_FUNC_INFO << " emit command:" << aCommand;
        emit publishCommand(aCommand);
    }

}
