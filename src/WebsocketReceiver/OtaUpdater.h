#pragma once

#include <ESPAsyncWebServer.h>

#include <memory>

#include "../Connection/Connection.h"

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class OtaUpdater
{
  public:
    OtaUpdater(std::shared_ptr<AsyncWebServer> server);
    void begin();
    void loop();

  private:
    std::shared_ptr<AsyncWebServer> _server;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
