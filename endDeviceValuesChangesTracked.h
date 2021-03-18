#ifndef EDCOMMSVALUESCHANGESTRACKED_H
#define EDCOMMSVALUESCHANGESTRACKED_H

#include "valueChangesTracked.h"

class edCommsValueChangesTracked : public valueChangesTracked
{
    Q_OBJECT

public:
    edCommsValueChangesTracked( void );
    ~edCommsValueChangesTracked( void);

    void sendAllChangedValues( void );
    void resetAllTrackedValues( void );

    bool getChannelChanged( void );
    void changeChannel( const int & s);

    bool getGatewayAddressChanged( void );
    void changeGatewayAddress( const int & s);

    bool getEndDeviceAddressChanged( void );
    void changeEndDeviceAddress(const int & s);

    bool getBunchChanged( void );
    void changeBunch( const int & s);

    bool getNetIDChanged( void );
    void changeNetID(const int & s);

    bool getGroupChanged( void );
    void changeGroup(const int & s);

    bool getGBunchChanged( void );
    void changeGBunch(const int & s);

    bool getRBunchChanged( void );
    void changeRBunch(const int & s);

    bool getHoppingChanged( void );
    void changeHopping(const int & s);

    bool getRadioPowerChanged( void );
    void changeRadioPower(const int & s);

    bool getGWChannelFlagChanged( void );
    void changeGWChannelFlag(const int & s);

    bool getSyncWordChanged( void );
    void changeSyncWord(const int & s);

    bool get12KbodChanged( void );
    void change12Kbod(const int & s);

    bool getStayInRXChanged( void );
    void changeStayInRX(const int & s);

    bool getStayInCWChanged( void );
    void changeStayInCW(const int & s);

    bool getRepeaterChanged( void );
    void changeRepeater(const int & s);

    bool getRepeaterPowerChanged( void );
    void changeRepeaterPower(const int & s);

    bool getRepeaterChannelChanged( void );
    void changeRepeaterChannel(const int & s);

    bool getSearchEnabledChanged( void );
    void changeSearchEnabled(const int & s);

    bool getCriticalLevel500Changed( void );
    void changeCriticalLevel500(const int & s);

    bool getCriticalLevel10Changed( void );
    void changeCriticalLevel10(const int & s);

    bool getSlaveChanged( void );
    void changeSlave(const int & s);

    bool getSlaveChannelChanged( void );
    void changeSlaveChannel(const int & s);

    bool get250KbodChanged( void );
    void change250Kbod(const int & s);

    void sendAllChangedValuesToMemory( const QString intendedFor, int oldGWAddr, int oldEDAddr, int oldBunch, int oldNetID );

private:
    bool channelChanged;
    int channel;
    bool gatewayAddressChanged;
    int gatewayAddress;
    bool endDeviceAddressChanged;
    int endDeviceAddress;
    bool bunchChanged;
    int bunch;
    bool netIDChanged;
    int netID;
    bool groupChanged;
    int group;
    bool gBunchChanged;
    int gBunch;
    bool rBunchChanged;
    int rBunch;
    bool hoppingChanged;
    int hopping;
    bool radioPowerChanged;
    int radioPower;
    bool gwChannelFlagChanged;
    int gwChannelFlag;
    bool syncwordChanged;
    int syncword;
    bool twelveKbodChanged;
    int twelveKbod;
    bool stayInRXChanged;
    int stayInRX;
    bool stayInCWChanged;
    int stayInCW;
    bool repeaterChanged;
    int repeater;
    bool repeaterPowerChanged;
    int repeaterPower;
    bool repeaterChannelChanged;
    int repeaterChannel;
    bool searchEnabledChanged;
    int searchEnabled;
    bool CriticalLevel10Changed;
    int CriticalLevel10;
    bool slaveChanged;
    int slave;
    bool slaveChannelChanged;
    int slaveChannel;
    bool two50KbodChanged;
    int two50Kbod;
    bool CriticalLevel500Changed;
    int CriticalLevel500;

};


#endif // EDCOMMSVALUESCHANGESTRACKED_H
