#include "WifiConfig.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

WifiConfig::WifiConfig(String ssid, String password) : _ssid(ssid), _password(password) {}

void WifiConfig::begin()
{
    WiFi.onEvent(std::bind(&WifiConfig::onWiFiEvent, this, std::placeholders::_1));
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
}

void WifiConfig::onWiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
        case ARDUINO_EVENT_WIFI_STA_START:
            Serial.println("WIFI Started");
            // set eth hostname here
            WiFi.setHostname("esp32-ethernet");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("WIFI Connected");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.print("WIFI MAC: ");
            Serial.print(WiFi.macAddress());
            Serial.print(", IPv4: ");
            Serial.println(WiFi.localIP());
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            Serial.println("WIFI Disconnected");
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            Serial.println("WIFI Stopped");
            break;
        default:
            break;
    }
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf