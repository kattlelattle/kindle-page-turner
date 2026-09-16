# Wireless Kindle Page Turner

Compact wireless page-turning device using ESP32-C3 microcontrollers, custom PCBs, servo actuation, and a 3D-printed enclosure.

## Overview

This project is a wireless assistive device designed to remotely turn Kindle pages without directly touching the screen.

The system uses two custom PCBs:
- TX controller for user input and wireless transmission
- RX controller for servo control and touchscreen interaction

## Hardware Design

### TX Board

- Seeed Studio XIAO ESP32-C3
- Push-button input
- Wireless communication

### RX Board

- Seeed Studio XIAO ESP32-C3
- Adafruit MiniBoost 5V 1A
- LiPo battery system
- Servo interface
- Conductive stylus connection

## PCB Design

Designed in Altium Designer:

- Custom schematics
- Two-layer PCB layouts
- Custom footprints
- Ground plane routing
- Power management for servo loads
- Gerber and BOM generation

## Mechanical Design

3D printed enclosure in progress.

Planned features:
- Kindle edge mounting
- PCB mounting
- Servo mounting
- External switch access

## Firmware

Firmware development in progress.

Planned:
- Wireless TX/RX communication
- Servo control
- Power management

## Project Status

Completed:
- TX PCB design
- RX PCB design
- PCB fabrication files

Current:
- PCB ordered
- Awaiting assembly and hardware testing

Future:
- Firmware testing
- Enclosure design
- Full Kindle integration
