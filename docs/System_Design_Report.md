# Smart Greenhouse System Using SocketCAN

## 1. Problem Description

The objective of this project is to design and implement a distributed Smart Greenhouse System using SocketCAN. The system monitors environmental conditions and controls actuators through CAN communication between software ECUs.

Functions implemented:

- Temperature Monitoring
- Humidity Monitoring
- Water Pump Control
- Fan Control

---

## 2. Functional Architecture

Inputs:
- Temperature Sensor
- Humidity Sensor

Processing:
- Controller ECU

Outputs:
- Fan
- Water Pump

Diagnostics:
- Fault Detection
- Message Monitoring

---

## 3. ECU Architecture

### Sensor ECU
Responsibilities:
- Generate temperature values
- Generate humidity values
- Send heartbeat messages

### Controller ECU
Responsibilities:
- Receive sensor data
- Generate fan commands
- Generate water pump commands

### Actuator ECU
Responsibilities:
- Execute fan commands
- Execute water pump commands
- Report actuator status

### Diagnostic ECU
Responsibilities:
- Monitor CAN traffic
- Detect missing messages
- Detect invalid values
- Generate fault reports

### Dashboard
Responsibilities:
- Display system status
- Display faults

---

## 4. CAN Matrix

| CAN ID | Sender | Receiver | Signal |
|---------|---------|---------|---------|
| 0x100 | Sensor ECU | Controller ECU | Temperature |
| 0x101 | Sensor ECU | Controller ECU | Humidity |
| 0x102 | Sensor ECU | Diagnostic ECU | Heartbeat |
| 0x200 | Controller ECU | Actuator ECU | Fan Command |
| 0x201 | Controller ECU | Actuator ECU | Pump Command |
| 0x300 | Actuator ECU | Diagnostic ECU | Actuator Status |
| 0x400 | Diagnostic ECU | Dashboard | Fault Report |

---

## 5. Signal Definitions

### Temperature
- Unit: °C
- Range: 0–100
- Resolution: 1°C
- Encoding: Unsigned 8-bit integer

### Humidity
- Unit: %
- Range: 0–100
- Resolution: 1%
- Encoding: Unsigned 8-bit integer

### Fan Command
- 0 = OFF
- 1 = ON

### Pump Command
- 0 = OFF
- 1 = ON

---

## 6. Design Decisions

- SocketCAN used for communication
- Virtual CAN interface (homecan)
- Distributed architecture
- Separate ECU applications
- Fault detection through Diagnostic ECU

---

## 7. Conclusion

The Smart Greenhouse System successfully demonstrates distributed communication using SocketCAN and multiple software ECUs.
