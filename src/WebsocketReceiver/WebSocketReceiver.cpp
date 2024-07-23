#include "WebSocketReceiver.h"

#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ETH.h>
#include <WiFi.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

WebSocketReceiver::WebSocketReceiver() : WebSocketReceiver("/ws", 80) {}
WebSocketReceiver::WebSocketReceiver(const char *websocketPath, uint16_t websocketPort)
    : _server(websocketPort), _socket(websocketPath)
{
}
WebSocketReceiver::WebSocketReceiver(String websocketPath, uint16_t websocketPort)
    : _hasStateChanged(false), _server(websocketPort), _socket(websocketPath)
{
    _socket.onEvent(std::bind(
        &WebSocketReceiver::onWsEvent,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3,
        std::placeholders::_4,
        std::placeholders::_5,
        std::placeholders::_6));
    _server.addHandler(&_socket);
}

void WebSocketReceiver::begin()
{
    _server.begin();
}

void WebSocketReceiver::loop()
{
    _socket.cleanupClients();
}

void WebSocketReceiver::onWsEvent(
    AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
        case WS_EVT_CONNECT:
            client->text(_requestedState.toJson());
            break;
        case WS_EVT_DATA:
        {
            auto receivedString = String(data, len);
            _socket.textAll(receivedString);
            _requestedState = State(receivedString);
            _hasStateChanged = true;
            break;
        }
    }
}

std::optional<const State> WebSocketReceiver::getNextState()
{
    if (_hasStateChanged)
    {
        return std::optional<const State>(_requestedState);
    }
    return std::nullopt;
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
