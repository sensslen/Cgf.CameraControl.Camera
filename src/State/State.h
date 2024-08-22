#pragma once

#include <WString.h>
#include <stddef.h>
#include <stdint.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class State
{
  private:
    uint8_t _panSpeed;
    bool _panRight;
    uint8_t _tiltSpeed;
    bool _tiltUp;
    int _zoomSpeed;
    uint8_t _redColor;
    uint8_t _greenColor;

  public:
    State();
    State(String &json);
    State(uint8_t panSpeed, bool panRight, uint8_t tiltSpeed, bool tiltUp, int zoomSpeed, uint8_t red, uint8_t green);

    uint8_t getPanSpeed() const;
    bool getPanRight() const;
    uint8_t getTiltSpeed() const;
    bool getTiltUp() const;
    int getZoomSpeed() const;
    uint8_t getRed() const;
    uint8_t getGreen() const;

    String toJson() const;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
