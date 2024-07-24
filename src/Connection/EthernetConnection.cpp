#include "EthernetConnection.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

EthernetConnection::EthernetConnection(
    eth_phy_type_t type, int32_t phy_addr, int mdc, int mdio, int power, eth_clock_mode_t clock_mode)
    : _type(type), _phy_addr(phy_addr), _mdc(mdc), _mdio(mdio), _power(power), _clock_mode(clock_mode)
{
}

void EthernetConnection::begin()
{
    WiFi.onEvent(std::bind(&EthernetConnection::onWiFiEvent, this, std::placeholders::_1));
    ETH.begin(_type, _phy_addr, _mdc, _mdio, _power, _clock_mode);
}

void EthernetConnection::on_connection_state_changed(std::function<void(ConnectionState state)> callback)
{
    if (_on_connection_state_changed == nullptr)
    {
        _on_connection_state_changed = callback;
        callback(_state);
    }
}

void EthernetConnection::onWiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
        case ARDUINO_EVENT_ETH_START:
            // set eth hostname here
            ETH.setHostname("esp32-ethernet");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            Serial.print("IP: ");
            Serial.println(ETH.localIP());
            onConnectionStateChanged(ConnectionState::CONNECTED);
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            onConnectionStateChanged(ConnectionState::DISCONNECTED);
            break;
        default:
            break;
    }
}

void EthernetConnection::onConnectionStateChanged(ConnectionState state)
{
    _state = state;
    if (_on_connection_state_changed != nullptr)
    {
        _on_connection_state_changed(state);
    }
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf