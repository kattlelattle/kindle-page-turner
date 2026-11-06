# Wireless Kindle Page Turner

Compact wireless page-turning device built on two ESP32-C3 boards, custom PCBs, servo actuation, and a 3D-printed enclosure.

## Demo

_Video coming soon._

## Overview

This is a wireless assistive device that turns Kindle pages without the user touching the screen. A handheld **TX** button sends a wireless command to an **RX** unit clipped to the Kindle. The RX unit drives a servo that sweeps a conductive stylus across the touchscreen.

## System Block Diagram

## Hardware

### TX Board
- Seeed Studio XIAO ESP32-C3
- Push-button input
- Wireless transmission

### RX Board
- Seeed Studio XIAO ESP32-C3
- Adafruit MiniBoost 5V 1A
- LiPo battery system
- Servo interface
- Conductive stylus connection

### PCB Design (Altium Designer)
- Two-layer layouts with ground planes
- Custom footprints
- Power management for servo loads

| Board | Schematic | Altium project | Gerbers | BOM |
|---|---|---|---|---|
| TX | [`tx_schematic.pdf`](hardware/pcb/tx/tx_schematic.pdf) | [`tx/altium/`](hardware/pcb/tx/altium/) | [`tx_gerbers.zip`](hardware/pcb/tx/tx_gerbers.zip) | [`tx_bom.xlsx`](hardware/pcb/tx/tx_bom.xlsx) |
| RX | [`rx_schematic.pdf`](hardware/pcb/rx/rx_schematic.pdf) | [`rx/altium/`](hardware/pcb/rx/altium/) | [`rx_gerbers.zip`](hardware/pcb/rx/rx_gerbers.zip) | [`rx_bom.xlsx`](hardware/pcb/rx/rx_bom.xlsx) |

Shared schematic/footprint libraries: [`hardware/pcb/libraries/`](hardware/pcb/libraries/). `Kindle_Custom.PcbLib` and `SolderPad.SchLib` are custom; the XIAO ESP32-C3 library is from Seeed Studio and the MiniBoost library is from Adafruit.

### Enclosure
_In progress._ Planned: Kindle edge mount, PCB and servo mounts, external switch access. CAD will go in [`hardware/enclosure/`](hardware/enclosure/).

## Firmware

_In progress._ Planned: wireless TX/RX link, servo control, power management.

- TX: [`firmware/tx/`](firmware/tx/)
- RX: [`firmware/rx/`](firmware/rx/)

## Results

| Metric | Target | Measured | Notes |
|---|---:|---:|---|
| Page-turn success rate | ___ % | ___ / ___ (___ %) | |
| Button-to-turn latency | < ___ ms | ___ ms | |
| Wireless range (line of sight) | ___ m | ___ m | |
| RX battery life (turns per charge) | ___ | ___ | |
| RX idle current | ___ mA | ___ mA | |
| Servo peak current | ___ A | ___ A | |
| Device mass (RX unit) | ___ g | ___ g | |

Raw data: [`docs/testing/`](docs/testing/)

## Project Status

**Completed**
- TX and RX PCB design
- PCB fabrication files

**Current**
- PCBs ordered, awaiting assembly and hardware testing

**Next**
- Firmware bring-up and testing
- Enclosure design
- Full Kindle integration and results
