#include "PanTilt.h"

#include <Arduino.h>

#define PWM_FREQUENCY 200
#define PWM_RESOLUTION 10

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
        ledcWrite(_pinPanRight, calculateSpeed(speed));
    }
    else
    {
        ledcWrite(_pinPanRight, 0);
        ledcWrite(_pinPanLeft, calculateSpeed(speed));
    }
}

void PanTilt::setTiltSpeed(uint8_t speed, bool up)
{
    if (up)
    {
        ledcWrite(_pinTiltDown, 0);
        ledcWrite(_pinTiltUp, calculateSpeed(speed));
    }
    else
    {
        ledcWrite(_pinTiltUp, 0);
        ledcWrite(_pinTiltDown, calculateSpeed(speed));
    }
}

uint32_t PanTilt::calculateSpeed(const uint8_t receivedSpeed)
{
    if (receivedSpeed == 0)
    {
        return 0;
    }

    return map(receivedSpeed, 0, 255, 300, 1023);
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
