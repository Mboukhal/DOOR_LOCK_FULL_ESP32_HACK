
# DOOR_LOCK_FULL_ESP32_HACK

## Introduction

This project involves modifying an RFID reader `Product` and implementing a door lock control system using ESP32. The goal is to have full control over the device, enabling it to connect to a backend server for RFID validation and monitoring user activities on installed doors.

## Features

- **RFID Validation:** The modified RFID reader `Product` can request access validation from a backend server.
- **Door Control:** The ESP32-based door lock can react to incoming backend responses, allowing for secure door control.
- **User Activity Tracking:** The system logs and tracks user activities on the installed doors.

## Requirements

- RFID Reader `Product`
- ESP32 microcontroller
- PlatformIO and Arduino for coding

## Setup

1. Clone the repository:

   ```bash
   git clone https://github.com/Mboukhal/DOOR_LOCK_FULL_ESP32_HACK.git
   ```

2. Install necessary libraries:

	Wiegand:
	```
	cd arduino/libraries
	git clone https://github.com/monkeyboard/Wiegand-Protocol-Library-for-Arduino.git Wiegand
	```

	ArduinoJson:
	Sketch > Include Library > Manage Librarys...
   

3. Upload the code to your ESP32 using PlatformIO.

## Configuration

- Access the web interface using the following credentials:
  - WiFi AP: `1337-DOORLOCK-CONFIG`
  - Password: `+@@1337@@+`
  - IP: `192.168.13.37`
- Use the web interface to configure the device.

## Usage

1. Ensure the RFID reader `Product` and ESP32 are properly connected.
2. Power on the system.
3. Access the web interface using the provided WiFi AP, password, and IP.
4. Configure the device with the desired backend endpoint and default code.
5. Users with valid RFID cards will have access granted, and their activities will be logged.

## Device Reset

- The device can be reset to default configuration using the original reset button.
- Buzzer, front light, and relay door lock are all controlled in the modified version.

## Contributing

Feel free to contribute to the project by opening issues or submitting pull requests.

## License

This project is licensed under the [MIT License](LICENSE).
