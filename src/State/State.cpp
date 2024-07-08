#include "State.h"

#include <ArduinoJson.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

State::State() : State(0, false, 0, false, 0) {}

State::State(String &json) : State()
{
    auto document = JsonDocument();
    auto error = deserializeJson(document, json);
    if (error != DeserializationError::Ok)
    {
        return;
    }

    if (document.containsKey("pan"))
    {
        int pan = document["pan"];
        _panSpeed = std::min(std::abs(pan), 255);
        _panRight = pan > 0;
    }

    if (document.containsKey("tilt"))
    {
        int tilt = document["tilt"];
        _tiltSpeed = std::min(std::abs(tilt), 255);
        _tiltUp = tilt > 0;
    }

    if (document.containsKey("zoom"))
    {
        int zoom = document["zoom"];
        _zoomSpeed = std::max(std::min(zoom, 255), -255);
    }
}

State::State(uint8_t panSpeed, bool panRight, uint8_t tiltSpeed, bool tiltUp, int zoomSpeed)
    : _panSpeed(panSpeed), _panRight(panRight), _tiltSpeed(tiltSpeed), _tiltUp(tiltUp), _zoomSpeed(zoomSpeed)
{
}

uint8_t State::getPanSpeed() const
{
    return _panSpeed;
}

bool State::getPanRight() const
{
    return _panRight;
}

uint8_t State::getTiltSpeed() const
{
    return _tiltSpeed;
}

bool State::getTiltUp() const
{
    return _tiltUp;
}

int State::getZoomSpeed() const
{
    return _zoomSpeed;
}

String State::toJson() const
{
    auto document = JsonDocument();
    document["pan"] = _panRight ? _panSpeed : -_panSpeed;
    document["tilt"] = _tiltUp ? _tiltSpeed : -_tiltSpeed;
    document["zoom"] = _zoomSpeed;

    auto output = String();
    serializeJson(document, output);
    return output;
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
