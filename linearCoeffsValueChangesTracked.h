#ifndef LINEARCOEFFSVALUECHANGESTRACKED_H
#define LINEARCOEFFSVALUECHANGESTRACKED_H

#include "valueChangesTracked.h"

class linearCoeffsValueChangesTracked : public valueChangesTracked
{

public:
    linearCoeffsValueChangesTracked( void );
    ~linearCoeffsValueChangesTracked( void );

    void sendAllChangedValues( void );
    void resetAllTrackedValues ( void );

    bool getVOutCoefficientChanged( void );
    void changeVOutCoefficient( const double & s);
    bool getVOutOffsetChanged(void );
    void changeVOutOffset( const double & s);
    bool getVIn1CoefficientChanged( void );
    void changeVIn1Coefficient( const double & s);
    bool getVIn1OffsetChanged(void );
    void changeVIn1Offset( const double & s);
    bool getVIn2CoefficientChanged( void );
    void changeVIn2Coefficient( const double & s);
    bool getVIn2OffsetChanged(void );
    void changeVIn2Offset( const double & s);
    bool getIOutCoefficientChanged( void );
    void changeIOutCoefficient( const double & s);
    bool getIOutOffsetChanged(void );
    void changeIOutOffset( const double & s);
    bool getIIn1CoefficientChanged( void );
    void changeIIn1Coefficient( const double & s);
    bool getIIn1OffsetChanged(void );
    void changeIIn1Offset( const double & s);
    bool getIIn2CoefficientChanged( void );
    void changeIIn2Coefficient( const double & s);
    bool getIIn2OffsetChanged(void );
    void changeIIn2Offset( const double & s);

    bool getTextCoefficientChanged( void );
    void changeTextCoefficient( const double & s);
    bool getTextOffsetChanged(void );
    void changeTextOffset( const double & s);

    void sendAllChangedValuesToMemory( const QString intendedFor );


private:
    bool vOutCoefficientChanged;
    double vOutCoefficient;
    bool vOutOffsetChanged;
    double vOutOffset;
    bool vIn1CoefficientChanged;
    double vIn1Coefficient;
    bool vIn1OffsetChanged;
    double vIn1Offset;
    bool vIn2CoefficientChanged;
    double vIn2Coefficient;
    bool vIn2OffsetChanged;
    double vIn2Offset;

    bool iOutCoefficientChanged;
    double iOutCoefficient;
    bool iOutOffsetChanged;
    double iOutOffset;
    bool iIn1CoefficientChanged;
    double iIn1Coefficient;
    bool iIn1OffsetChanged;
    double iIn1Offset;
    bool iIn2CoefficientChanged;
    double iIn2Coefficient;
    bool iIn2OffsetChanged;
    double iIn2Offset;

    bool textCoefficientChanged;
    double textCoefficient;
    bool textOffsetChanged;
    double textOffset;

};

#endif 
