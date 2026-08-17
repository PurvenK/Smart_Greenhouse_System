# Smart Greenhouse System Using SocketCAN

## Project Description

This project implements a distributed Smart Greenhouse System using SocketCAN in C. The system monitors temperature and humidity and controls a fan and water pump through CAN communication between multiple software ECUs.

The implementation demonstrates distributed system design, CAN network communication, diagnostics, fault detection, and system validation.

## System Architecture

```
                 SocketCAN (homecan)

        +----------------+
        | Sensor ECU     |
        | Temperature    |
        | Humidity       |
        +----------------+
                |
                v

        +----------------+
        | Controller ECU |
        | Decision Logic |
        +----------------+
                |
        -----------------
        |               |
        v               v

+---------------+   +---------------+
| Fan Control   |   | Pump Control  |
| Actuator ECU  |   | Actuator ECU  |
+---------------+   +---------------+

                |
                v

        +----------------+
        | Diagnostic ECU |
        +----------------+
```

## ECU Responsibilities

### Sensor ECU

* Generate temperature values
* Generate humidity values
* Send sensor data over CAN
* Send heartbeat messages

### Controller ECU

* Receive temperature and humidity data
* Decide fan operation
* Decide water pump operation
* Send actuator commands

### Actuator ECU

* Receive fan commands
* Receive pump commands
* Simulate actuator behavior
* Report actuator status

### Diagnostic ECU

* Monitor heartbeat messages
* Detect invalid sensor values
* Detect communication failures
* Generate fault reports

### Dashboard

* Display temperature
* Display humidity
* Display fan status
* Display water pump status
* Display fault information

## CAN Message Matrix

| CAN ID | Sender         | Receiver       | Signal          |
| ------ | -------------- | -------------- | --------------- |
| 0x100  | Sensor ECU     | Controller ECU | Temperature     |
| 0x101  | Sensor ECU     | Controller ECU | Humidity        |
| 0x102  | Sensor ECU     | Diagnostic ECU | Heartbeat       |
| 0x200  | Controller ECU | Actuator ECU   | Fan Command     |
| 0x201  | Controller ECU | Actuator ECU   | Pump Command    |
| 0x300  | Actuator ECU   | Diagnostic ECU | Actuator Status |
| 0x400  | Diagnostic ECU | Dashboard      | Fault Report    |

## Requirements

### Software

* Ubuntu Linux
* GCC Compiler
* Make
* SocketCAN
* can-utils

### Installation

```bash
sudo apt update
sudo apt install gcc make can-utils
```

## CAN Interface Setup

```bash
sudo modprobe vcan
sudo ip link add homecan type vcan
sudo ip link set homecan up
```

Verify:

```bash
ip link show homecan
```

## Build Instructions

Compile all ECUs:

```bash
make
```

Or compile individually:

```bash
gcc sensor_ecu.c -o sensor_ecu
gcc controller_ecu.c -o controller_ecu
gcc actuator_ecu.c -o actuator_ecu
gcc diagnostic_ecu.c -o diagnostic_ecu
gcc dashboard.c -o dashboard
```

## Execution Instructions

Open five terminals.

Terminal 1:

```bash
./sensor_ecu
```

Terminal 2:

```bash
./controller_ecu
```

Terminal 3:

```bash
./actuator_ecu
```

Terminal 4:

```bash
./diagnostic_ecu
```

Terminal 5:

```bash
./dashboard
```

## Fault Testing

### Sensor ECU Timeout

Stop Sensor ECU and verify:

```
FAULT: Sensor ECU Timeout
```

### Invalid Temperature

Send a temperature value above the valid range and verify:

```
FAULT: Invalid Temperature
```

### Invalid Humidity

Send a humidity value above the valid range and verify:

```
FAULT: Invalid Humidity
```

## Technologies Used

* C Programming
* Linux SocketCAN
* CAN Protocol
* Virtual CAN Interface (vcan)

## Conclusion

This project demonstrates a distributed CAN-based Smart Greenhouse System using multiple software ECUs communicating through SocketCAN. The implementation includes sensing, control, diagnostics, fault handling, and system monitoring.
