# Hardware Components and Wiring

## 1. Project Overview

The Humanoid Eye Robot is an Arduino-based robotic eye mechanism that uses six servo motors for eyeball movement and eyelid animation. A joystick controls the eye's horizontal and vertical movement, while the eyelids blink automatically at random intervals.

The eye mechanism uses 3D-printed parts.

## 2. Hardware Components

| Component                |    Quantity | Purpose                                               |
| ------------------------ | ----------: | ----------------------------------------------------- |
| Arduino Uno              |           1 | Main controller for servo movement and joystick input |
| Servo motors             |           6 | Control eyeball movement and upper/lower eyelids      |
| Joystick module          |           1 | Provides horizontal and vertical control input        |
| External power adapter   |           1 | Supplies power to the servo motors                    |
| Breadboard               |           1 | Supports temporary circuit connections                |
| Jumper wires             | As required | Connect electronic components                         |
| 3D-printed eye mechanism | As required | Mechanical structure for the robotic eyes             |
| Screws                   | As required | Secure the mechanical assembly                        |

**TBD:** Exact servo motor model, external adapter voltage/current rating, and 3D-printed material have not yet been confirmed.

## 3. Servo Motor Connections

The Arduino sketch uses the following pin assignments:

| Servo variable | Arduino pin | Function                    |
| -------------- | ----------- | --------------------------- |
| `lowerR`       | D2          | Right lower eyelid          |
| `upperR`       | D3          | Right upper eyelid          |
| `eyeY`         | D4          | Eyeball up/down movement    |
| `upperL`       | D5          | Left upper eyelid           |
| `lowerL`       | D6          | Left lower eyelid           |
| `eyeX`         | D7          | Eyeball left/right movement |

These pin assignments are based on the project's Arduino sketch.

## 4. Joystick Connections

The Arduino sketch reads the joystick's two analog axes.

| Joystick signal  | Arduino Uno pin |
| ---------------- | --------------- |
| X-axis (`JOY_X`) | A0              |
| Y-axis (`JOY_Y`) | A1              |
| VCC              | TBD             |
| GND              | TBD             |

Connect the joystick's power and ground according to the specific module's pin labels. The exact module model has not been confirmed.

## 5. Power Supply and Safety

The project uses an external power adapter for the servo motors.

- Confirm that the adapter's output voltage matches the requirements of the actual servo motors.
- Ensure the power supply can provide sufficient current for all six servos, including their peak load.
- Do not power all six servo motors directly from the Arduino Uno's 5V pin.
- Connect the external supply's ground to the Arduino Uno's GND so the control signals share a common reference.
- Check the servo connector's signal, power, and ground pins before connecting it.
- Disconnect power before changing wiring or servicing the mechanism.

**TBD:** Adapter output voltage, current rating, and the final power-distribution arrangement must be verified from the actual hardware.

## 6. Mechanical Assembly

The eye mechanism is made using 3D-printed parts and screws.

The six servo motors operate the eyeball and eyelids according to the project's pin mapping. Secure the servos and moving parts firmly, and verify that the mechanism can move freely without binding or excessive resistance.

**TBD:** 3D model/design files, exact dimensions, mounting arrangement, and printed material.

## 7. Basic Hardware Setup

1. Mount the six servo motors onto the eye mechanism.
2. Connect each servo signal wire to its assigned Arduino pin.
3. Connect the joystick X-axis to A0 and Y-axis to A1.
4. Connect joystick power and ground according to the module specifications.
5. Connect the servo motors to the appropriately rated external power supply.
6. Ensure the external supply ground and Arduino GND are connected together.
7. Inspect all connections before applying power.
8. Upload `src/HumanoidEyeRobot.ino` using the Arduino IDE and test the movement carefully.

## 8. Hardware Verification Checklist

- [ ] Arduino Uno detected by the Arduino IDE.
- [ ] All six servo motors securely mounted.
- [ ] Servo signal connections checked against the pin table.
- [ ] Joystick axes connected to A0 and A1.
- [ ] External power adapter voltage and current rating verified.
- [ ] Common ground established between the Arduino and servo supply.
- [ ] Eyeball movement tested in both axes.
- [ ] Automatic eyelid blinking tested.
- [ ] Moving parts checked for mechanical obstruction.

## 9. Notes
This document describes the hardware details confirmed for the project. Unconfirmed specifications are marked **TBD** rather than assumed. Update this file when the exact servo model, power adapter rating, and other hardware specifications are available.
