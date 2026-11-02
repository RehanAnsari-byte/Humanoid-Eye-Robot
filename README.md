# Humanoid Eye Robot

An Arduino-based animatronic eye mechanism with natural, randomly timed blinking and joystick-controlled eyeball movement. The mechanism is 3D printed and driven by 6 servo motors.

## Features
- Automatic blinking with random gap (2-5 seconds) for a natural look
- 4 eyelid servos (upper and lower eyelid for both eyes)
- Eyeball left-right and up-down control using a joystick
- Smooth movement with dead zone and auto-calibration of joystick center
- All servos reset to 90° on startup

## Hardware
- Arduino Uno/Nano
- 6x SG90/MG90 servo motors
- Analog joystick module
- External 5V 3-5A power supply
- 3D printed eye mechanism

## Servo Pin Mapping
| Servo | Function | Pin |
|-------|----------|-----|
| 1 | Lower eyelid (right) | 2 |
| 2 | Upper eyelid (right) | 3 |
| 3 | Eyeball up-down | 4 |
| 4 | Eyeball left-right | 7 |
| 5 | Lower eyelid (left) | 6 |
| 6 | Upper eyelid (left) | 5 |

## Joystick Pin Mapping
| Joystick | Arduino |
|----------|---------|
| VRx | A0 |
| VRy | A1 |
| SW | 11 (unused in auto-blink version) |

## Wiring Notes
- Power the servos from an external 5V supply, not the Arduino 5V pin.
- Connect the external supply GND to Arduino GND (common ground).

## Code Structure
- `blink_only/` : eyelid blinking only
- `full_eye_control/` : blinking + joystick eyeball control
- `servo_test/` : test a single servo
- `servo_reset/` : set all servos to 90°

## Tuning
- If an eyelid moves in the wrong direction, flip the sign of its `*_DELTA` value.
- Adjust `*_DELTA` to change how far the eyelid closes.
- Adjust `BLINK_MIN_GAP` and `BLINK_MAX_GAP` to change blink timing.

## Future Improvements
- Eye tracking using a camera
- Servo calibration via Serial commands
- Emotion presets (happy, sad, surprised)

## License
MIT
