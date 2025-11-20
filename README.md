 ## Smart Environment Monitoring System

This is the Demo concept for a scalable environmental sensing platform designed to monitor air quality and environmental conditions in real time. This is a demo-level implementation simulating how large cities could deploy distributed sensor nodes to provide live environmental data to citizens, improving public health, awareness, and smart-city planning.

## 🌍 Project Overview

The Smart Environment Monitoring System showcases how IoT sensor nodes can measure:

Temperature

Humidity

CO₂ concentration

Air Quality Index (AQI)

PM2.5 particulate matter

This repository includes:

A Proteus simulation-based node

A Node-RED real-time dashboard

MQTT data streaming pipeline

Reference hardware components for real implementation

## 📁 Repository Structure
```
Smart Environment Monitoring System/
├── Docs/
├── Images/
│ ├── schematic.png
│ ├── gauges.png
│ ├── trends.png
│ ├── Block Diagram.jpg
│ └── NodeRED_Flow.png
├── Firmware/
│ ├── firmware.ino
│ └── bridge.py
├── Hardware/
│ └── Proteus schematics/
│ └── Smart Environment Monitoring system.pdsprj
├── Dashboard/
│ └── NodeRED_Flow.json
└── README.md 
```
## 🛠️ Real Hardware Node (For Real Deployment)

Microcontroller

ESP32-WROOM (Wi-Fi, BLE, low-power)

Sensors

BME280 (Temperature, Humidity, Pressure)

MH-Z19B (CO₂) or PMS5003 (PM2.5)

Power Options

USB 5V

Or 18650 Li-ion + TP4056 charger module

Optional

SSD1306 OLED

Enclosure / protoboard

Jumper wires, resistors

Software

Arduino IDE / PlatformIO

Python (optional backend)

MQTT broker (Cloud MQTT / Mosquitto)

Node-RED

## 🧪 Simulation Setup (Proteus Demo)

Since many of  real sensors cannot run directly in proteus simulation, the following substitutes are used:

Proteus 8.0+

MQ-9 (used as simulated CO₂ sensor)

DFRobot Analog Air Quality Sensor for PM2.5

Arduino Mega / UNO

Virtual Serial Port Driver (free VSPD / Com0Com)

Mosquitto MQTT Broker

Node-RED

## 🔗 Simulation Data Flow
Proteus → VSPD → Python Bridge Script → MQTT Broker → Node-RED Dashboard

Why the Serial → MQTT Bridge?

Proteus outputs data only through virtual COM ports.
The Python bridge script reads serial values, converts them into JSON, and publishes them to the MQTT broker so Node-RED can display them live.

## 📡 MQTT Topics sets to
environment/data

## 🖥️ Node-RED Dashboard

Features:

Live gauges for all environmental metrics

 optional WebSocket for connecting multiple clients

 real-time updates

Auto-scaling trend charts

Fault-tolerant MQTT reconnection

Dashboard flow file:

Dashboard/NodeRED_Flow.json

 ## 📊 Images
System Schematic

Docs/schematic.png

Gauge Interface

Docs/gauges.png

Trend Charts

Docs/trends.png


## 🔧 PM2.5 Calibration Note

The simulation sensor outputs PM2.5 in µg / 0.1L, which causes unrealistic high values.

Use this calibration to reduce concentrations to realistic levels:

ug_m3 = sensor_raw_data * calibration_factor


Recommended:

calibration_factor = 0.164  used in this demo


This matches near to real PM2.5 environmental concentrations per one declitre.

## 🚀 How to Run
1. Create Virtual COM Ports

Link COM3 ↔ COM4 (or any pair) using Free VSPD / Com0Com.

2. Run the Python Bridge
python bridge.py

3. Start Mosquitto if not start automatically
mosquitto

4. Start Node-RED
node-red

5. Open the Dashboard

Open in browser:

http://localhost:1880/ui

## 🏙️ Smart-City Vision

This project demonstrates how affordable IoT nodes can build a city-wide environmental monitoring network, enabling:

Public air-quality transparency

Early health hazard alerts

Research and climate analysis

Better urban-planning decisions

📄 License

MIT License

🤝 Contributions

You are welcome to crone and contribute all!!😜
