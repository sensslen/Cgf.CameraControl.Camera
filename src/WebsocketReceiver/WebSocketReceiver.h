#include <ESPAsyncWebServer.h>
#include <WString.h>
#include <stdint.h>

#include <optional>

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
    WebSocketReceiver();
    WebSocketReceiver(const char *websocketPath, uint16_t websocketPort);
    WebSocketReceiver(String websocketPath, uint16_t websocketPort);

    void begin();
    void loop();

    std::optional<const State> getNextState();

  private:
    void onWsEvent(
        AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

    bool _hasStateChanged;
    State _requestedState;
    AsyncWebServer _server;
    AsyncWebSocket _socket;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
