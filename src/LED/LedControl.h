#pragma once

#include <stdint.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class LedControl
{
  public:
    LedControl(uint8_t pinRed, uint8_t pinGreen);

    bool setup();

    void setColor(uint8_t red, uint8_t green);

  private:
    uint8_t _pinRed;
    uint8_t _pinGreen;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
