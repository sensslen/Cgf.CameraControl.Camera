#pragma once

#include <Arduino.h>
#include <WiFi.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class WifiConfig
{
  public:
    WifiConfig(String ssid, String password);
    void begin();

  private:
    void onWiFiEvent(WiFiEvent_t event);

    String _ssid;
    String _password;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf