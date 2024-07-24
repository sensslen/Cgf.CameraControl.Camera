#include <Arduino.h>
#include <LibLanc.h>

#include "Connection/EthernetConnection.h"
#include "LED/LedControl.h"
#include "PanTilt/PanTilt.h"
#include "WebsocketReceiver/WebsocketReceiver.h"

#define PAN_RIGHT_PIN 14
#define PAN_LEFT_PIN 12
#define TILT_UP_PIN 4
#define TILT_DOWN_PIN 2

Cgf::CameraControl::Camera::PanTilt panTilt(PAN_RIGHT_PIN, PAN_LEFT_PIN, TILT_UP_PIN, TILT_DOWN_PIN);

#define LED_RED_PIN 17
#define LED_GREEN_PIN 5

Cgf::CameraControl::Camera::LedControl ledControl(LED_RED_PIN, LED_GREEN_PIN);

#define LANC_INPUT_PIN 36
#define LANC_OUTPUT_PIN 15

LibLanc::LancNonBlocking lanc(LANC_INPUT_PIN, LANC_OUTPUT_PIN);

/*
 * ETH_CLOCK_GPIO0_IN   - default: external clock from crystal oscillator
 * ETH_CLOCK_GPIO0_OUT  - 50MHz clock from internal APLL output on GPIO0 - possibly an inverter is needed for LAN8720
 * ETH_CLOCK_GPIO16_OUT - 50MHz clock from internal APLL output on GPIO16 - possibly an inverter is needed for LAN8720
 * ETH_CLOCK_GPIO17_OUT - 50MHz clock from internal APLL inverted output on GPIO17 - tested with LAN8720
 */
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN  //  ETH_CLOCK_GPIO17_OUT

// Pin# of the enable signal for the external crystal oscillator (-1 to disable for internal APLL source)
#define ETH_POWER_PIN 16

// Type of the Ethernet PHY (LAN8720 or TLK110)
#define ETH_TYPE ETH_PHY_LAN8720

// I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)
#define ETH_ADDR 1

// Pin# of the I²C clock signal for the Ethernet PHY
#define ETH_MDC_PIN 23

// Pin# of the I²C IO signal for the Ethernet PHY
#define ETH_MDIO_PIN 18

Cgf::CameraControl::Camera::EthernetConnection ethernetConnection(
    ETH_TYPE, ETH_ADDR, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_POWER_PIN, ETH_CLK_MODE);

Cgf::CameraControl::Camera::WebSocketReceiver websocketReceiver("/ws", 80, ethernetConnection);

void setup()
{
    ethernetConnection.begin();
    Serial.begin(115200);

    if (!panTilt.setup())
    {
        Serial.println("Failed to setup PanTilt");
    }
    if (!ledControl.setup())
    {
        Serial.println("Failed to setup LedControl");
    }

    lanc.begin();
}

void loop()
{
    auto nextStateOption = websocketReceiver.getNextState();
    if (nextStateOption.has_value())
    {
        auto nextState = nextStateOption.value();
        panTilt.setPanSpeed(nextState.getPanSpeed(), nextState.getPanRight());
        panTilt.setTiltSpeed(nextState.getTiltSpeed(), nextState.getTiltUp());
        ledControl.setColor(nextState.getRed(), nextState.getGreen());

        auto zoomSpeed = nextState.getZoomSpeed() * 8 / 255;
        lanc.setCommand(LibLanc::CommandFactory::zoom(zoomSpeed));
    }

    websocketReceiver.loop();
    lanc.loop();
}