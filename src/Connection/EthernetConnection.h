#pragma once

#include <Arduino.h>
#include <ETH.h>
#include <WiFi.h>

#include "Connection.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class EthernetConnection : public Connection
{
  public:
    EthernetConnection(
        eth_phy_type_t type, int32_t phy_addr, int mdc, int mdio, int power, eth_clock_mode_t clock_mode);
    virtual void begin() override;

    virtual void on_connection_state_changed(std::function<void(ConnectionState state)> callback) override;

  private:
    void onWiFiEvent(WiFiEvent_t event);
    void onConnectionStateChanged(ConnectionState state);

    eth_phy_type_t _type;
    int32_t _phy_addr;
    int _mdc;
    int _mdio;
    int _power;
    eth_clock_mode_t _clock_mode;
    ConnectionState _state = ConnectionState::DISCONNECTED;

    std::function<void(ConnectionState state)> _on_connection_state_changed = nullptr;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf