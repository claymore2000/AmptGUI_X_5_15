#ifndef PROTECTIONS1300VVALUECHANGESTRACKED_H
#define PROTECTIONS1300VVALUECHANGESTRACKED_H


#include "valueChangesTracked.h"

class protectionsValueChangesTracked : public valueChangesTracked
{

public:
    protectionsValueChangesTracked( void );
    ~protectionsValueChangesTracked( void );

    void sendAllChangedValues( void );
    void resetAllTrackedValues ( bool s = false );

    bool getFETCountChanged( void );
    void changeFETCount( const int & s);

    bool getFETThresholdChanged( void );
    void changeFETThreshold( const int & s);

    bool getFETDeltaCurrentChanged( void );
    void changeFETDeltaCurrent( const int & s);
 
    bool getProtection1Changed( void );
    void changeProtection1( const unsigned int & s);

    bool getProtection2Changed( void );
    void changeProtection2( const unsigned int & s);

    bool getProtection3Changed( void );
    void changeProtection3( const unsigned int & s);

    bool getProtection4Changed( void );
    void changeProtection4( const unsigned int & s);

    bool getAMFTimer1Changed( void );
    void changeAMFTimer1( const unsigned int & s);

    bool getAMFTimer2Changed( void );
    void changeAMFTimer2( const unsigned int & s);

    bool getAMFV_OVChanged( void );
    void changeAMFV_OV( const unsigned int & s);

    bool getAMFI_OCChanged( void );
    void changeAMFI_OC( const unsigned int & s);

    bool getAMFMPPTimesOffChanged( void );
    void changeAMFMPPTimesOff( const unsigned int & s);

    bool getAMFMPPOffCyclesChanged( void );
    void changeAMFMPPOffCycles( const unsigned int & s);

    bool getAMFDebugChanged( void );
    void changeAMFDebug( const unsigned int & s);

    bool getEFInputCurrentThresholdChanged( void );
    void changeEFInputCurrentThreshold( const unsigned int & s);

    bool getEFOccurrenceThresholdChanged( void );
    void changeEFOccurrenceThreshold( const unsigned int & s);

    bool getEFCountDownTimerChanged( void );
    void changeEFCountDownTimer( const unsigned int & s);

    bool getEFAlphaNumeratorChanged( void );
    void changeEFAlphaNumerator( const unsigned int & s);

    bool getIinLimitChanged( void );
    void changeIinLimit( const unsigned int & s);

    bool getIinLimitOCStepsChanged( void );
    void changeIinLimitOCSteps(const unsigned int & s);

    bool getIinLimitOCDelayChanged( void );
    void changeIinLimitOCDelay(const unsigned int & s);

    bool getIinLimitTempAmbientAdjustChanged( void );
    void changeIinLimitTempAmbientAdjust(const signed int & s);

    void sendAllChangedValuesToMemory( const QString intendedFor, const QString theFamily );

private:
    bool fetCountChanged;
    int  fetCount;
    bool fetThresholdChanged;
    int  fetThreshold;
    bool fetDeltaCurrentChanged;
    int  fetDeltaCurrent;

    bool protection1Changed;
    unsigned int  protection1;
    bool protection2Changed;
    unsigned int  protection2;
    bool protection3Changed;
    unsigned int  protection3;
    bool protection4Changed;
    unsigned int  protection4;

    bool amfTimer1Changed;
    unsigned int  amfTimer1;
    bool amfTimer2Changed;
    unsigned int  amfTimer2;
    bool amfV_OVChanged;
    unsigned int  amfV_OV;
    bool amfI_OCChanged;
    unsigned int  amfI_OC;

    bool amfMPPTimesOffChanged;
    unsigned int  amfMPPTimesOff;
    bool amfMPPOffCyclesChanged;
    unsigned int  amfMPPOffCycles;
    bool amfDebugChanged;
    unsigned int  amfDebug;

    bool efInputCurrentThresholdChanged;
    unsigned int efInputCurrentThreshold;
    bool efOccurrenceThresholdChanged;
    unsigned int efOccurrenceThreshold;
    bool efCountDownTimerChanged;
    unsigned int efCountDownTimer;
    bool efAlphaNumeratorChanged;
    unsigned int efAlphaNumerator;

    bool iinLimitChanged;
    unsigned int iinLimit;
    bool iinLimitOCStepsChanged;
    unsigned int iinLimitOCSteps;
    bool iinLimitOCDelayChanged;
    unsigned int iinLimitOCDelay;
    bool iinLimitTempAmbientAdjustChanged;
    signed int iinLimitTempAmbientAdjust;


};

#endif 
