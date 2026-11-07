# Wireless Kindle Page Turner

Compact wireless page-turning device built on two ESP32-C3 boards, custom PCBs, servo actuation, and a 3D-printed enclosure.

## Demo

_Video coming soon._

## Overview

This is a wireless assistive device that turns Kindle pages without the user touching the screen. A handheld **TX** remote sends a Bluetooth Low Energy (BLE) command to an **RX** unit clipped to the side of the Kindle. The RX unit drives a servo arm that taps the screen with a grounded conductive stylus tip.

## System Block Diagram

## Hardware

### TX Board
- Seeed Studio XIAO ESP32-C3
- Omron B3F-4000 push button
- 3.7 V 702030 LiPo, charged over USB-C by the XIAO

### RX Board
- Seeed Studio XIAO ESP32-C3
- Adafruit MiniBoost 5V 1A (TPS61023), enabled from D3
- 3.7 V 603450 LiPo with a KCD11 power switch
- TowerPro SG92R micro servo on D2
- 1000 µF bulk capacitor on the 5 V servo rail
- Conductive stylus tip wired to ground

### PCB Design (Altium Designer)
- Two-layer layouts with ground planes
- Custom footprints
- Power management for servo loads

| Board | Schematic | Altium project | Gerbers | BOM |
|---|---|---|---|---|
| TX | [`tx_schematic.pdf`](hardware/pcb/tx/tx_schematic.pdf) | [`tx/altium/`](hardware/pcb/tx/altium/) | [`tx_gerbers.zip`](hardware/pcb/tx/tx_gerbers.zip) | [`tx_bom.xlsx`](hardware/pcb/tx/tx_bom.xlsx) |
| RX | [`rx_schematic.pdf`](hardware/pcb/rx/rx_schematic.pdf) | [`rx/altium/`](hardware/pcb/rx/altium/) | [`rx_gerbers.zip`](hardware/pcb/rx/rx_gerbers.zip) | [`rx_bom.xlsx`](hardware/pcb/rx/rx_bom.xlsx) |

Shared schematic/footprint libraries: [`hardware/pcb/libraries/`](hardware/pcb/libraries/). `Kindle_Custom.PcbLib` and `SolderPad.SchLib` are custom; the XIAO ESP32-C3 library is from Seeed Studio and the MiniBoost library is from Adafruit.

## Enclosure

Both enclosures were 3D printed in PLA on a Bambu Lab printer. All parts print without supports.

**TX remote:** a rounded handheld case with finger grooves on the sides, a thumb recess around the button, and a press-fit lid. The battery sits under the PCB.

**RX unit:** clips onto the right edge of the Kindle (Paperwhite 11th gen in a case), lined with felt for grip. The electronics box sits behind the Kindle, and the servo is mounted outside the edge with a hook-shaped arm that reaches over the bezel to tap the screen. The lid snaps into grooves in the box.

| Part | TX | RX |
|---|---|---|
| Case | [`tx_tray.stl`](hardware/enclosure/tx/tx_tray.stl) | [`rx_body.stl`](hardware/enclosure/rx/rx_body.stl) |
| Lid | [`tx_lid.stl`](hardware/enclosure/tx/tx_lid.stl) | [`rx_lid.stl`](hardware/enclosure/rx/rx_lid.stl) |
| Other | [`tx_button.stl`](hardware/enclosure/tx/tx_button.stl) | [`rx_arm.stl`](hardware/enclosure/rx/rx_arm.stl) |

The idea of a servo arm clipped to the edge of the Kindle came from [Kindle Page Turner](https://www.thingiverse.com/thing:3039314) by alexmikes on Thingiverse! The enclosures here were designed from scratch.

## Firmware

Written in Arduino for the XIAO ESP32-C3.

- **TX** ([`tx.ino`](firmware/tx/tx.ino)): stays in deep sleep until the button wakes it. It then connects to the RX over BLE, sends a tap command, and stays connected for one minute so the next presses are instant before going back to sleep.
- **RX** ([`rx.ino`](firmware/rx/rx.ino)): advertises as a BLE server, enables the boost converter, and moves the servo to the tap angle and back when a command arrives. The servo is detached between taps to avoid buzzing and save power.

Requires the ESP32 board package and the ESP32Servo library.

## Results

| Metric | Result | Notes |
|---|---:|---|
| TX standby current | 50 µA | Deep sleep, measured in series with the battery |
| TX standby life (estimate) | ~14 months | 500 mAh battery at 50 µA |
| RX idle current | 30 mA | BLE advertising, servo detached |
| RX run time (estimate) | ~33 hours | 1000 mAh battery at 30 mA |
| Page-turn success rate | | |
| Button-to-turn latency | | First press vs. while connected |
| Wireless range | | |

## Project Status

**Completed**
- TX and RX PCB design, fabrication and assembly
- TX and RX firmware with BLE link and deep sleep
- 3D-printed TX and RX enclosures

**Current**
- Tuning the tap angle and testing on the Kindle

**Next**
- Mount the RX from the top edge of the Kindle to carry more of the weight
- Enlarge some holes in the RX enclosure
- Lower RX power use with BLE power saving and by turning the boost converter off between taps
