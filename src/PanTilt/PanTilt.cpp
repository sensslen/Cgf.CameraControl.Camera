#include "PanTilt.h"

#include <Arduino.h>

#define PWM_FREQUENCY 500
#define PWM_RESOLUTION 8

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

PanTilt::PanTilt(uint8_t pinPanRight, uint8_t pinPanLeft, uint8_t pinTiltUp, uint8_t pinTiltDown)
    : _pinPanRight(pinPanRight), _pinPanLeft(pinPanLeft), _pinTiltUp(pinTiltUp), _pinTiltDown(pinTiltDown)
{
}

bool PanTilt::setup()
{
    if (!ledcAttach(_pinPanRight, PWM_FREQUENCY, PWM_RESOLUTION))
    {
        return false;
    }
    if (!ledcAttach(_pinPanLeft, PWM_FREQUENCY, PWM_RESOLUTION))
    {
        return false;
    }
    if (!ledcAttach(_pinTiltUp, PWM_FREQUENCY, PWM_RESOLUTION))
    {
        return false;
    }
    if (!ledcAttach(_pinTiltDown, PWM_FREQUENCY, PWM_RESOLUTION))
    {
        return false;
    }
    return true;
}

void PanTilt::setPanSpeed(uint8_t speed, bool right)
{
    if (right)
    {
        ledcWrite(_pinPanLeft, 0);
        ledcWrite(_pinPanRight, speed);
    }
    else
    {
        ledcWrite(_pinPanRight, 0);
        ledcWrite(_pinPanLeft, speed);
    }
}

void PanTilt::setTiltSpeed(uint8_t speed, bool up)
{
    if (up)
    {
        ledcWrite(_pinTiltDown, 0);
        ledcWrite(_pinTiltUp, speed);
    }
    else
    {
        ledcWrite(_pinTiltUp, 0);
        ledcWrite(_pinTiltDown, speed);
    }
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
