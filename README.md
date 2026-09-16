# Wireless Kindle Page Turner

Compact wireless page-turning device using ESP32-C3 microcontrollers, custom PCBs, servo actuation, and a 3D-printed enclosure.

## Overview

This project aims to create a small assistive device that allows users to remotely turn Kindle pages without directly interacting with the screen.

The system consists of:

- Wireless TX controller
- Wireless RX controller
- Servo-based page-turn mechanism
- Custom PCB hardware
- 3D printed enclosure

## System Architecture

TX:
- Seeed Studio XIAO ESP32-C3
- Push button input
- Wireless command transmission

RX:
- Seeed Studio XIAO ESP32-C3
- Adafruit MiniBoost 5V 1A
- LiPo battery power
- Servo control
- Touchscreen stylus interface

## PCB Design

Designed in Altium Designer:

- Custom schematics
- Two-layer PCB layout
- Ground plane design
- Through-hole and module footprints
- BOM generation

## CAD

(coming soon)

3D printed enclosure designed to:
- Clip onto Kindle edge
- Hold PCB securely
- Position servo mechanism
- Provide external switch access

## Firmware

(coming soon)

Features:
- Wireless communication
- Servo positioning
- Power management

## Current Status

PCB fabricated and ordered.

Next steps:
- PCB assembly
- Hardware testing
- Firmware validation
- Mechanical enclosure design
- Full Kindle integration

## Technologies

Hardware:
- ESP32-C3
- Servo motors
- LiPo battery systems
- Boost converters

Software:
- Arduino/C++
- Altium Designer
- CAD modeling
