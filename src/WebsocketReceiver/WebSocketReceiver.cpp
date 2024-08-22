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

WebSocketReceiver::WebSocketReceiver(std::shared_ptr<AsyncWebServer> server) : WebSocketReceiver("/ws", server) {}
WebSocketReceiver::WebSocketReceiver(const char *websocketPath, std::shared_ptr<AsyncWebServer> server)
    : WebSocketReceiver(String(websocketPath), server)
{
}
WebSocketReceiver::WebSocketReceiver(String websocketPath, std::shared_ptr<AsyncWebServer> server)
    : _hasStateChanged(false), _server(server), _socket(websocketPath)
{
    _socket.onEvent([this](
                        AsyncWebSocket *server,
                        AsyncWebSocketClient *client,
                        AwsEventType type,
                        void *arg,
                        uint8_t *data,
                        size_t len) { this->onWsEvent(server, client, type, arg, data, len); });
}

void WebSocketReceiver::begin()
{
    _server->addHandler(&_socket);
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
        _hasStateChanged = false;
        return std::optional<const State>(_requestedState);
    }
    return std::nullopt;
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
