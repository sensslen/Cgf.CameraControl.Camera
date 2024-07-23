#pragma once

#include <stdint.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class PanTilt
{
  public:
    PanTilt(uint8_t pinPanRight, uint8_t pinPanLeft, uint8_t pinTiltUp, uint8_t pinTiltDown);

    bool setup();

    void setPanSpeed(uint8_t speed, bool right);
    void setTiltSpeed(uint8_t speed, bool up);

  private:
    uint8_t _pinPanRight;
    uint8_t _pinPanLeft;
    uint8_t _pinTiltUp;
    uint8_t _pinTiltDown;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
