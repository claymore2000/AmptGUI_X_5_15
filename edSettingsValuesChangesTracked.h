#ifndef EDSETTINGSVALUECHANGESTRACKED_H
#define EDSETTINGSVALUECHANGESTRACKED_H


#include "valueChangesTracked.h"

class edSettingsValueChangesTracked : public valueChangesTracked
{

public:
    edSettingsValueChangesTracked( void );
    ~edSettingsValueChangesTracked( void );

    void sendAllChangedValues( void );
    void resetAllTrackedValues ( bool s = false );

    bool getSyncFrequencyChanged( void );
    void changeSyncFrequency( const int & s);

    bool getSyncPhaseChanged( void );
    void changeSyncPhase( const int & s);

    bool getFuseCommunicationChanged( void );
    void changeFuseCommunication( const int & s);

    bool getFuseElectricalChanged( void );
    void changeFuseElectrical( const int & s);

    void sendAllChangedValuesToMemory( const QString intendedFor );

private:

    bool syncFrequencyChanged;
    int  syncFrequency;

    bool syncPhaseChanged;
    int  syncPhase;

    bool fuseCommunicationChanged;
    int fuseCommunication;

    bool fuseElectricalChanged;
    int fuseElectrical;

};

#endif 
