#include "State.h"

#include <ArduinoJson.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

State::State() : State(0, false, 0, false, 0, 0, 0) {}

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

    if (document.containsKey("red"))
    {
        int red = document["red"];
        _redColor = std::max(std::min(red, 255), 0);
    }

    if (document.containsKey("green"))
    {
        int green = document["green"];
        _greenColor = std::max(std::min(green, 255), 0);
    }
}

State::State(uint8_t panSpeed, bool panRight, uint8_t tiltSpeed, bool tiltUp, int zoomSpeed, uint8_t red, uint8_t green)
    : _panSpeed(panSpeed)
    , _panRight(panRight)
    , _tiltSpeed(tiltSpeed)
    , _tiltUp(tiltUp)
    , _zoomSpeed(zoomSpeed)
    , _redColor(red)
    , _greenColor(green)
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

uint8_t State::getRed() const
{
    return _redColor;
}

uint8_t State::getGreen() const
{
    return _greenColor;
}

String State::toJson() const
{
    auto document = JsonDocument();
    document["pan"] = _panRight ? _panSpeed : -_panSpeed;
    document["tilt"] = _tiltUp ? _tiltSpeed : -_tiltSpeed;
    document["zoom"] = _zoomSpeed;
    document["red"] = _redColor;
    document["green"] = _greenColor;

    auto output = String();
    serializeJson(document, output);
    return output;
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
