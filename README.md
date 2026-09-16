# Wireless Kindle Page Turner

A compact wireless page-turning device built around ESP32-C3 microcontrollers, custom PCBs, servo actuation, and a future 3D-printed enclosure.

## Overview

This project is a wireless assistive device designed to turn Kindle pages remotely without requiring direct interaction with the touchscreen.

The system uses two custom PCBs:

- A **transmitter (TX)** board that sends user commands wirelessly
- A **receiver (RX)** board that controls a servo mechanism to physically interact with the Kindle screen

The goal is to create a compact, self-contained device that can clip onto the side of a Kindle and perform reliable page turns through a servo-driven mechanism.

## System Architecture

### Transmitter (TX)

The transmitter PCB uses:

- Seeed Studio XIAO ESP32-C3
- Push-button input
- Wireless communication

The TX board reads button presses and sends commands to the receiver.

### Receiver (RX)

The receiver PCB uses:

- Seeed Studio XIAO ESP32-C3
- Adafruit MiniBoost 5V 1A boost converter
- LiPo battery power
- Servo motor interface
- Conductive stylus connection for touchscreen interaction

The RX board receives commands from the TX board and controls the servo responsible for the page-turning mechanism.

## PCB Design

Designed using **Altium Designer**.

Design work includes:

- Custom schematic capture
- Two-layer PCB layouts
- Custom footprints and module integration
- Ground plane design
- Power distribution for servo loads
- Fabrication files and BOM generation

The RX PCB includes:
- Dedicated servo power regulation
- External battery connection
- External switch interface
- Servo header connection
- Grounded stylus interface

## Mechanical Design

The enclosure is currently in development.

Planned features:

- Clip-on Kindle mounting system
- Internal PCB mounting
- Servo mounting bracket
- External power switch access
- Cable management

The PCB has been fabricated and ordered. Mechanical design will begin after receiving and validating the physical board.

## Firmware

Firmware development is in progress.

Planned functionality:

- Wireless communication between TX and RX boards
- Servo positioning control
- Power management
- User input handling

## Current Status

✅ TX PCB designed  
✅ RX schematic completed  
✅ RX PCB designed  
✅ Fabrication files generated  
✅ PCB ordered  

Next steps:

- Assemble and test PCBs
- Validate power delivery and communication
- Develop ESP32 firmware
- Design and print enclosure
- Integrate servo mechanism with Kindle

## Technologies

### Hardware
- ESP32-C3
- Servo motors
- LiPo battery systems
- Boost converters
- Custom PCBs

### Software & Tools
- Arduino / C++
- Altium Designer
- CAD modeling
- PCB fabrication workflow
