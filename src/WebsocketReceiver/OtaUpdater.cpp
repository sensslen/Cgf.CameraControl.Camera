#include "OtaUpdater.h"

#include <ElegantOTA.h>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

OtaUpdater::OtaUpdater(std::shared_ptr<AsyncWebServer> server) : _server(server) {}

void OtaUpdater::begin()
{
    ElegantOTA.begin(_server.get());
}

void OtaUpdater::loop()
{
    ElegantOTA.loop();
}

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf
