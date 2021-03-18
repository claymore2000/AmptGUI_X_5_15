#ifndef RADIOVALUECHANGESTRACKED_H
#define RADIOVALUECHANGESTRACKED_H


#include "valueChangesTracked.h"

class radioValueChangesTracked : public valueChangesTracked
{

public:
    radioValueChangesTracked( void );
    ~radioValueChangesTracked( void );

    void sendAllChangedValues( void );
    void resetAllTrackedValues ( bool s = false );

    bool getDFK0Changed( void );
    void changeDFK0( const double & s);

    bool getDFK1Changed( void );
    void changeDFK1( const double & s);

    bool getDFK2Changed( void );
    void changeDFK2( const double & s);

    bool getDFK3Changed( void );
    void changeDFK3( const double & s);

    bool getPureOffsetChanged( void );
    void changePureOffset( const int & s);

    bool getLowCurrentLimitTo255Changed( void );
    void changeLowCurrentLimitTo255(const int & s);

    void sendAllChangedValuesToMemory( const QString intendedFor );

private:

    bool dFK0Changed;
    double  dFK0;

    bool dFK1Changed;
    double  dFK1;

    bool dFK2Changed;
    double  dFK2;

    bool dFK3Changed;
    double  dFK3;

    bool pureOffsetChanged;
    int  pureOffset;

    bool lowCurrentLimitTo255Changed;
    int lowCurrentLimitTo255;

};

#endif 
