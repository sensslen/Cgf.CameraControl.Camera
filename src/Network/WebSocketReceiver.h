#pragma once

#include <ESPAsyncWebServer.h>
#include <WString.h>
#include <stdint.h>

#include <optional>

#include "../Connection/Connection.h"
#include "../State/State.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class WebSocketReceiver
{
  public:
    WebSocketReceiver(std::shared_ptr<AsyncWebServer> server);
    WebSocketReceiver(const char *websocketPath, std::shared_ptr<AsyncWebServer> server);
    WebSocketReceiver(String websocketPath, std::shared_ptr<AsyncWebServer> server);

    void begin();
    void loop();

    std::optional<const State> getNextState();

  private:
    void onWsEvent(
        AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

    bool _hasStateChanged;
    State _requestedState;
    std::shared_ptr<AsyncWebServer> _server;
    AsyncWebSocket _socket;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
