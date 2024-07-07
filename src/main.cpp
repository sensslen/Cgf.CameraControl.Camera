#include <Arduino.h>
#include <LibLanc.h>
#include <ESPAsyncWebServer.h>

#include "PanTilt/PanTilt.h"

#define PAN_RIGHT_PIN 14
#define PAN_LEFT_PIN 12
#define TILT_UP_PIN 4
#define TILT_DOWN_PIN 2

Cgf::CameraControl::Camera::PanTilt panTilt(PAN_RIGHT_PIN, PAN_LEFT_PIN, TILT_UP_PIN, TILT_DOWN_PIN);

#define LANC_INPUT_PIN 36
#define LANC_OUTPUT_PIN 15

LibLanc::LancNonBlocking lanc(LANC_INPUT_PIN, LANC_OUTPUT_PIN);

void setup()
{
    Serial.begin(115200);
    if (!panTilt.setup())
    {
        Serial.println("Failed to setup PanTilt");
    }

    lanc.begin();
}

void loop()
{
    // put your main code here, to run repeatedly:
}