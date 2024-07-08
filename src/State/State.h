#include <WString.h>
#include <stddef.h>
#include <stdint.h>

#ifndef STATE_H
#define STATE_H

namespace Cgf
{
namespace CameraControl
{
namespace Camera
{

class State
{
  private:
    uint8_t _panSpeed;
    bool _panRight;
    uint8_t _tiltSpeed;
    bool _tiltUp;
    int _zoomSpeed;

  public:
    State();
    State(String &json);
    State(uint8_t panSpeed, bool panRight, uint8_t tiltSpeed, bool tiltUp, int zoomSpeed);

    uint8_t getPanSpeed() const;
    bool getPanRight() const;
    uint8_t getTiltSpeed() const;
    bool getTiltUp() const;
    int getZoomSpeed() const;

    String toJson() const;
};

}  // namespace Camera
}  // namespace CameraControl
}  // namespace Cgf

#endif  // STATE_H
