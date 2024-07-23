#include "EthConfig.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

EthConfig::EthConfig(eth_phy_type_t type, int32_t phy_addr, int mdc, int mdio, int power, eth_clock_mode_t clock_mode)
    : _type(type), _phy_addr(phy_addr), _mdc(mdc), _mdio(mdio), _power(power), _clock_mode(clock_mode)
{
}

void EthConfig::begin()
{
    WiFi.onEvent(std::bind(&EthConfig::onWiFiEvent, this, std::placeholders::_1));
    ETH.begin(_type, _phy_addr, _mdc, _mdio, _power, _clock_mode);
}

void EthConfig::onWiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
        case ARDUINO_EVENT_ETH_START:
            Serial.println("ETH Started");
            // set eth hostname here
            ETH.setHostname("esp32-ethernet");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            Serial.println("ETH Connected");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            Serial.print("ETH MAC: ");
            Serial.print(ETH.macAddress());
            Serial.print(", IPv4: ");
            Serial.print(ETH.localIP());
            if (ETH.fullDuplex())
            {
                Serial.print(", FULL_DUPLEX");
            }
            Serial.print(", ");
            Serial.print(ETH.linkSpeed());
            Serial.println("Mbps");
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            Serial.println("ETH Disconnected");
            break;
        case ARDUINO_EVENT_ETH_STOP:
            Serial.println("ETH Stopped");
            break;
        default:
            break;
    }
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf