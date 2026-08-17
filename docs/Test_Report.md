# Smart Greenhouse System Test Report

## Test Environment

- Ubuntu Linux
- SocketCAN
- Virtual CAN Interface (homecan)
- GCC Compiler

---

## Test Case 1: Normal Operation

Objective:
Verify normal system communication.

Procedure:
1. Start Sensor ECU
2. Start Controller ECU
3. Start Actuator ECU
4. Start Diagnostic ECU
5. Start Dashboard

Expected Result:
All ECUs communicate successfully.

Result:
PASS

---

## Test Case 2: Temperature Monitoring

Objective:
Verify temperature transmission.

Expected Result:
Temperature displayed on Dashboard.

Result:
PASS

---

## Test Case 3: Humidity Monitoring

Objective:
Verify humidity transmission.

Expected Result:
Humidity displayed on Dashboard.

Result:
PASS

---

## Test Case 4: Fan Control

Objective:
Verify fan control logic.

Condition:
Temperature > 30°C

Expected Result:
Fan ON

Result:
PASS

---

## Test Case 5: Water Pump Control

Objective:
Verify pump control logic.

Condition:
Humidity < 40%

Expected Result:
Pump ON

Result:
PASS

---

## Test Case 6: Invalid Temperature Fault

Objective:
Verify fault detection.

Expected Result:
FAULT: Invalid Temperature

Result:
PASS

---

## Test Case 7: Sensor ECU Timeout

Objective:
Verify missing message detection.

Procedure:
Stop Sensor ECU.

Expected Result:
FAULT: Sensor ECU Timeout

Result:
PASS

---

## Test Case 8: Recovery

Objective:
Verify system recovery.

Procedure:
Restart Sensor ECU.

Expected Result:
Communication restored.

Result:
PASS

---

## Conclusion

All functional, diagnostic, and fault-handling requirements were successfully verified.
