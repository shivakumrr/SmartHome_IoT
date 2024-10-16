# SmartHome_IoT
Certainly! I'll create a README file for your GitHub repository that describes this home automation project. Here's a draft of the README content:





# Smart Home Automation System

This project implements a smart home automation system using ESP32 microcontrollers, various sensors, and MQTT communication protocol. The system is designed to monitor and control different aspects of a home environment, including lighting, temperature, humidity, and security.

## System Components

The system consists of three ESP32 modules, each responsible for different functions:

1. **Light Control Module (ESP32 #1)**
   - LED connected to GPIO23
   - LDR (Light Sensor) connected to GPIO13
   - Monitors ambient light and controls LED

2. **Temperature and Humidity Module (ESP32 #2)**
   - DHT11 Sensor connected to GPIO4
   - Buzzer connected to GPIO5
   - Monitors temperature and humidity, triggers buzzer based on conditions

3. **Security Module (ESP32 #3)**
   - PIR Sensor connected to GPIO5
   - LED connected to GPIO4
   - Detects motion and controls LED for security indication

4. **M5Stack LCD Display**
   - Works in conjunction with the Security Module
   - Displays status (red/green) based on security conditions

## Features

- Real-time monitoring of light levels, temperature, humidity, and motion
- Automated control of lighting based on ambient light conditions
- Temperature and humidity alerts via buzzer
- Motion detection and security alerts
- Visual indication of system status via LEDs and LCD display
- MQTT communication for data exchange between ESP32 modules and central control system

## Setup Instructions

1. Clone this repository to your local machine.
2. Open each ESP32 module's code in the Arduino IDE.
3. Install the required libraries:
   - PubSubClient
   - DHT sensor library
   - Appropriate ESP32 board support
4. Update the Wi-Fi credentials and MQTT broker address in each ESP32 code file:
   ```cpp
   const char* ssid = "Your_SSID";
   const char* password = "Your_Password";
   const char* mqtt_server = "Your_MQTT_Broker_IP";
   ```
5. Flash each ESP32 with its respective code.
6. Set up the Node-RED flow for central control and monitoring.

## Node-RED Flow

The Node-RED flow (provided in `flows.json`) handles the following:
- Subscribes to MQTT topics for each sensor
- Processes incoming data
- Publishes control commands to actuators (LEDs, buzzer)
- Provides a user interface for monitoring and control

Import the `nodeRed_flow.json` file into your Node-RED instance to set up the control system.

## Directory Structure

```
/
├── esp32_light_control/
│   └── aws_smart_home.ino
├── esp32_temp_humidity/
│   └── room2_temp_motor.ino
├── esp32_security/
│   └── door_pir_led.ino
├── m5stack_lcd/
│   └── m5stack_lcd.ino
├── node-red/
│   └── nodeRed_flow.json
└── README.md
```
