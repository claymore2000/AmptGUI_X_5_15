#ifndef TEMPCNTRLVALUECHANGESTRACKED_H
#define TEMPCNTRLVALUECHANGESTRACKED_H


#include "valueChangesTracked.h"

class tempCntrlValueChangesTracked : public valueChangesTracked
{

public:
    tempCntrlValueChangesTracked( void );
    ~tempCntrlValueChangesTracked( void );

    void sendAllChangedValues( void );
    void resetAllTrackedValues ( bool s = false );

    bool getOCProtectionChanged( void );
    void changeOCProtection( const int & s);

    bool getTColdChanged( void );
    void changeTCold( const int & s);

    bool getTHotChanged( void );
    void changeTHot( const int & s);
 
    bool getTSuperHotChanged( void );
    void changeTSuperHot( const int & s);

    bool getFallbackTimeChanged( void );
    void changeFallbackTime( const int & s);

   void sendAllChangedValuesToMemory( const QString intendedFor );

private:

    bool ocProtectionChanged;
    int  ocProtection;
    bool tColdChanged;
    int  tCold;
	bool tHotChanged;
    int  tHot;
    bool tSuperHotChanged;
    int  tSuperHot;
    bool fallbackTimeChanged;
    int  fallbackTime;

};

#endif 
