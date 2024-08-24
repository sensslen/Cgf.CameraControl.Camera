#include "WebServerConnectionHandler.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

WebServerConnectionHandler::WebServerConnectionHandler(Connection &connection)
    : WebServerConnectionHandler(connection, 80)
{
}
WebServerConnectionHandler::WebServerConnectionHandler(Connection &connection, int16_t port)
    : _server(std::make_shared<AsyncWebServer>(port))
{
    connection.on_connection_state_changed([this](Connection::ConnectionState state)
                                           { this->onConnectionStateChanged(state); });
}

void WebServerConnectionHandler::onConnectionStateChanged(Connection::ConnectionState state)
{
    switch (state)
    {
        case Connection::ConnectionState::CONNECTED:
            _server->begin();
            break;
        case Connection::ConnectionState::DISCONNECTED:
            _server->end();
            break;
    }
}

WebServerConnectionHandler::operator std::shared_ptr<AsyncWebServer>() const
{
    return _server;
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
