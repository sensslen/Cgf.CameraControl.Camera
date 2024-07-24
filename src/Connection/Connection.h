#pragma once

#include <functional>

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class Connection
{
  public:
    enum ConnectionState
    {
        CONNECTED,
        DISCONNECTED
    };

    virtual void begin() = 0;
    virtual void on_connection_state_changed(std::function<void(ConnectionState state)> callback) = 0;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf