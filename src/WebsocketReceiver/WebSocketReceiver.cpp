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

WebSocketReceiver::WebSocketReceiver(Connection &connection) : WebSocketReceiver("/ws", 80, connection) {}
WebSocketReceiver::WebSocketReceiver(const char *websocketPath, uint16_t websocketPort, Connection &connection)
    : WebSocketReceiver(String(websocketPath), websocketPort, connection)
{
}
WebSocketReceiver::WebSocketReceiver(String websocketPath, uint16_t websocketPort, Connection &connection)
    : _hasStateChanged(false), _server(websocketPort), _socket(websocketPath)
{
    _socket.onEvent([this](
                        AsyncWebSocket *server,
                        AsyncWebSocketClient *client,
                        AwsEventType type,
                        void *arg,
                        uint8_t *data,
                        size_t len) { this->onWsEvent(server, client, type, arg, data, len); });
    _server.addHandler(&_socket);

    connection.on_connection_state_changed([this](Connection::ConnectionState state)
                                           { this->onConnectionStateChanged(state); });
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

void WebSocketReceiver::onConnectionStateChanged(Connection::ConnectionState state)
{
    switch (state)
    {
        case Connection::ConnectionState::CONNECTED:
            _server.begin();
            break;
        case Connection::ConnectionState::DISCONNECTED:
            _server.end();
            break;
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
