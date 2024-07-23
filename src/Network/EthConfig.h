#pragma once

#include <Arduino.h>
#include <ETH.h>
#include <WiFi.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class EthConfig
{
  public:
    EthConfig(eth_phy_type_t type, int32_t phy_addr, int mdc, int mdio, int power, eth_clock_mode_t clock_mode);
    void begin();

  private:
    void onWiFiEvent(WiFiEvent_t event);

    eth_phy_type_t _type;
    int32_t _phy_addr;
    int _mdc;
    int _mdio;
    int _power;
    eth_clock_mode_t _clock_mode;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf