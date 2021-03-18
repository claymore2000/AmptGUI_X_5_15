#ifndef GATEWAYVALUECHANGESTRACKED_H
#define GATEWAYVALUECHANGESTRACKED_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QDebug>

class gatewayValuesChangesTracked : public QWidget
{
    Q_OBJECT

signals:

    void publishCommand(const QString command);
    void publishNewEndDeviceChannel( int );

public:
    gatewayValuesChangesTracked( void );
    ~gatewayValuesChangesTracked( void);
    bool getIgnoreGatewaySignals( void );
    void setIgnoreSignalsToChangeGatewayValues( bool s);
    bool getGatewayChannelValueChanged( void );
    void gatewayChannelValueChanged(int newChannel);
    bool getGatewayEndDeviceOrGatewayValueChanged( void );
    void gatewayGatewayAddressValueChanged(int newGatewayAddress);
    void gatewayEndDeviceAddressValueChanged(int newEndDeviceAddress);
    bool getGatewayBunchSizeValueChanged( void );
    void gatewayBunchSizeValueChanged(int newBunchSize);
    bool getGatewayNetworkSizeValueChanged();
    void gatewayNetworkSizeValueChanged(int newNetworkSize);
    bool getGatewayHoppingValueChanged( void );
    void gatewayHoppingValueChanged(int newHopping);
    bool getGatewayPowerValueChanged( void );
    void gatewayPowerValueChanged(const QString newPower);
    bool getGatewaySyncWordValueChanged( void );
    void gatewaySyncWordValueChanged(int newSyncword);
    bool getGatewayModeValueChanged( void );
    void gatewayModeValueChanged( int newMode );
    bool getGatewayZCountValueChanged( void );
    void gatewayZCountValueChanged( int newZCount);
    bool getGatewayCmdCountValueChanged( void );
    void gatewayCmdCountValueChanged(int newCmdCount);
    bool getGatewayFWVersionValueChanged( void );
    void gatewayFWVersionValueChanged(int newFWVersion );

    void writeAllChangedValuesToMemory( bool endDevicesAlso );
    void resetAllTrackedGatewayValues ( void );

private:
    bool ignoreSignals;
    bool channelChanged;
    int channel;
    bool gatewayAddressChanged;
    int gatewayAddress;
    bool endDeviceAddressChanged;
    int endDeviceAddress;
    bool bunchSizeChanged;
    int bunchSize;
    bool networkSizeChanged;
    int networkSize;
    bool hoppingChanged;
    int hopping;
    bool powerChanged;
    QString power;
    bool modeChanged;
    int mode;
    bool syncwordChanged;
    int syncword;
    bool zCountChanged;
    int zCount;
    bool cmdCountChanged;
    int cmdCount;
    bool fwVersionChanged;
    int fwVersion;
};

#endif // GATEWAYVALUECHANGESTRACKED_H
