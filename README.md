# Keybox-Arduino

This repository contains the software for the Keybox device, a secure key management system.

## Requirements

### Software
- [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html)
- [Servo library](https://www.arduino.cc/reference/en/libraries/servo/)
- [Keypad library](https://www.arduino.cc/reference/en/libraries/keypad/)
- [RFID RC522 library](https://github.com/OSSLibraries/Arduino_MFRC522v2)

### Hardware
To set up the Keybox, you will need the following components:
- ESP32 microcontroller
- Green, Red, and Blue LEDs
- Push button
- Servo motor (SG 90)
- RFID RC522 module
- Keypad
- Five 220 Ohm resistors

## Installation

> **Note:** This guide assumes that you are familiar with using PlatformIO Core and have correctly set up your circuit.

### Command Line Installation
1. Clone the repository to your local directory using the command: `git clone [repository URL]`
2. Build the project with: `pio run`
3. Flash the code to the ESP32 board using: `pio run -t upload`

### Manual Installation
1. Download the repository and extract its contents to your local directory.
2. Build the project with: `pio run`
3. Flash the code to the ESP32 board using: `pio run -t upload`

Follow these steps carefully, and you'll have the Keybox device up and running in no time. If you encounter any issues during the installation process, refer to the documentation provided by PlatformIO and the respective libraries.

Feel free to contribute to this project or report any bugs through issues. Happy hacking!
