# Cgf.CameraControl.Camera

## Overview

Cgf.CameraControl.Camera is a PlatformIO-based firmware project designed for the WT-ETH01 board. It controls video camera hardware, including pan/tilt mechanisms, LED indicators, and network connectivity. The project uses the Lanc protocol to control zoom and focus functions of compatible video cameras. Modular components provide Ethernet communication, OTA updates, web server handling, and state management.

## Features

- **Pan/Tilt Control:** Manage camera orientation via the `PanTilt` module.
- **LED Control:** Operate status LEDs using the `LedControl` module.
- **Ethernet Connectivity:** Connect and communicate over Ethernet with the `EthernetConnection` module.
- **OTA Updates:** Update firmware remotely using the `OtaUpdater` module.
- **Web Server & WebSocket:** Serve web interfaces and handle real-time communication.
- **State Management:** Track and manage device state.
- **Lanc Protocol:** Control zoom and focus of a video camera using the Lanc protocol.

## Project Structure

- `src/` - Main source code
  - `main.cpp` - Entry point
  - `Connection/` - Ethernet connection logic
  - `LED/` - LED control logic
  - `Network/` - OTA updater, web server, and WebSocket handler
  - `PanTilt/` - Pan/tilt motor control
  - `State/` - Device state management
- `include/` - Header files
- `lib/` - External libraries
- `test/` - Test code

## Getting Started

1. Install [PlatformIO](https://platformio.org/) in VS Code.
2. Clone this repository.
3. Open the project in PlatformIO.
4. Build and upload the firmware to your WT-ETH01 board.

## Usage

Configure hardware settings in `platformio.ini` and source files as needed. Use the web interface for remote control and monitoring. The firmware communicates with a video camera using the Lanc protocol, enabling remote zoom and focus control.

## License

See `LICENSE` for details.
