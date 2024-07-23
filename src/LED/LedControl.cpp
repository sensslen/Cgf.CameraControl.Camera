#include "LedControl.h"

#include <Arduino.h>

#define PWM_FREQUENCY 5000
#define PWM_RESOLUTION 8

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

LedControl::LedControl(uint8_t pinRed, uint8_t pinGreen) : _pinRed(pinRed), _pinGreen(pinGreen) {}

bool LedControl::setup()
{
    if (!ledcAttach(_pinRed, PWM_FREQUENCY, PWM_RESOLUTION))
    {
        return false;
    }
    if (!ledcAttach(_pinGreen, PWM_FREQUENCY, PWM_RESOLUTION))
    {
        return false;
    }
    return true;
}

void LedControl::setColor(uint8_t red, uint8_t green)
{
    ledcWrite(_pinRed, red);
    ledcWrite(_pinGreen, green);
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
