#ifndef POWERCNTRLVALUESCHANGESTRACKED_H
#define POWERCNTRLVALUESCHANGESTRACKED_H

#include "valueChangesTracked.h"

class powerCntrlValuesChangesTracked : public valueChangesTracked
{
    Q_OBJECT

signals:

public:
    powerCntrlValuesChangesTracked( void );
    ~powerCntrlValuesChangesTracked( void);

	bool getVinTurnOnChanged( void );
    void changeVinTurnOn(int s);
	bool getVinTurnOffChanged( void );
    void changeVinTurnOff(int s);
	bool getVinStopRadioChanged( void );
    void changeVinStopRadio(int s);
    bool getVinLimit255Changed( void );
    void changeVinLimit255(int s);

    bool getOVStartupChanged( void );
    void changeOVStartup(int s);

	bool getOVChanged( void );
    void changeOV(int s);

	bool getOCChanged( void );
    void changeOC(int s);

	bool getCurrentNoiseChanged( void );
    void changeCurrentNoise(int s);
	bool getOVStepChanged( void );
    void changeOVStep(int s);

	bool getOCStepChanged( void );
    void changeOCStep(int s);

	bool getModuleChanged( void );
    void changeModule(const QString s);
	bool getMPPChanged( void );
    void changeMPP(const QString s);

    void sendAllChangedValuesToMemory( const QString intendedFor );
    void resetAllTrackedValues ( bool all = false );

private:

	bool vinTurnOnChanged;
	int vinTurnOn;
	bool vinTurnOffChanged;
	int vinTurnOff;
	bool vinStopRadioChanged;
	int vinStopRadio;
	bool vinLimit255Changed;
	int vinLimit255;	
	bool ovChanged;
	int ov;
    bool ocChanged;
	int oc;
	bool ovStartupChanged;
	int ovStartup;
	bool currentNoiseChanged;
    int currentNoise;
	bool ovStepChanged;
	int ovStep;
	bool ocStepChanged;
	int ocStep;
	bool moduleChanged;
	QString module;
	bool mppChanged;
	QString mpp;

};

#endif // POWERCNTRLVALUESCHANGESTRACKED_H
