#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LibLanc.h>

#include "PanTilt/PanTilt.h"
#include "WebsocketReceiver/WebsocketReceiver.h"

#define PAN_RIGHT_PIN 14
#define PAN_LEFT_PIN 12
#define TILT_UP_PIN 4
#define TILT_DOWN_PIN 2

Cgf::CameraControl::Camera::PanTilt panTilt(PAN_RIGHT_PIN, PAN_LEFT_PIN, TILT_UP_PIN, TILT_DOWN_PIN);

#define LANC_INPUT_PIN 36
#define LANC_OUTPUT_PIN 15

LibLanc::LancNonBlocking lanc(LANC_INPUT_PIN, LANC_OUTPUT_PIN);

Cgf::CameraControl::Camera::WebSocketReceiver websocketReceiver("/ws", 80);

void setup()
{
    Serial.begin(115200);
    if (!panTilt.setup())
    {
        Serial.println("Failed to setup PanTilt");
    }

    lanc.begin();
    websocketReceiver.begin();
}

void loop()
{
    auto nextStateOption = websocketReceiver.getNextState();
    if (nextStateOption.has_value())
    {
        auto nextState = nextStateOption.value();
        panTilt.setPanSpeed(nextState.getPanSpeed(), nextState.getPanRight());
        panTilt.setTiltSpeed(nextState.getTiltSpeed(), nextState.getTiltUp());

        auto zoomSpeed = nextState.getZoomSpeed() * 8 / 255;
        lanc.setCommand(LibLanc::CommandFactory::zoom(zoomSpeed));
    }

    lanc.loop();
}