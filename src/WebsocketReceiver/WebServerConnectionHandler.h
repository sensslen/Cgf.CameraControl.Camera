#pragma once

#include <ESPAsyncWebServer.h>
#include <stdint.h>

#include <memory>

#include "../Connection/Connection.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class WebServerConnectionHandler
{
  public:
    WebServerConnectionHandler(Connection &connection);
    WebServerConnectionHandler(Connection &connection, int16_t port);

    operator std::shared_ptr<AsyncWebServer>() const;

  private:
    void onConnectionStateChanged(Connection::ConnectionState state);

    std::shared_ptr<AsyncWebServer> _server;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
