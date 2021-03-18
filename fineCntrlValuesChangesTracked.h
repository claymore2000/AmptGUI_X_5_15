#ifndef FINECNTRLVALUECHANGESTRACKED_H
#define FINECNTRLVALUECHANGESTRACKED_H


#include "valueChangesTracked.h"

class fineCntrlValueChangesTracked : public valueChangesTracked
{

public:
    fineCntrlValueChangesTracked( void );
    ~fineCntrlValueChangesTracked( void );

    void sendAllChangedValues( void );
    void resetAllTrackedValues ( bool s = false );

    bool getVRef0Changed( void );
    void changeVRef0( const double & s);

    bool getKVRefChanged( void );
    void changeKVRef( const double & s);

    bool getT0Changed( void );
    void changeT0( const double & s);

    bool getTempCoeffCurrentChanged( void );
    void changeTempCoeffCurrent( const double & s);

    bool getTempCoeffPowerChanged( void );
    void changeTempCoeffPower( const double & s);

    bool getShortCircuitLevelChanged( void );
    void changeShortCircuitLevel( const int & s);

    void sendAllChangedValuesToMemory( const QString intendedFor );


private:

    bool vRef0Changed;
    double  vRef0;

    bool kVRefChanged;
    double  kVRef;

    bool t0Changed;
    double  t0;

    bool tempCoeffCurrentChanged;
    double  tempCoeffCurrent;

    bool tempCoeffPowerChanged;
    double  tempCoeffPower;

    bool shortCircuitLevelChanged;
    int  shortCircuitLevel;

};

#endif 
