# Working Principle

The Humanoid Eye Robot uses an **Arduino** and **6 servo motors** to imitate the two main behaviours of a human eye: **blinking** and **eyeball movement**. Blinking runs automatically, and the eyeball is steered with a joystick.

## System Overview

```
Joystick (X, Y) ──► Arduino ──► PWM signals ──► 2 eyeball servos (left-right, up-down)
                       │
                       └──────► PWM signals ──► 4 eyelid servos (upper + lower, both eyes)
                       ▲
        External 5V supply (servo power, common GND with Arduino)
```

## 1. Servo Control

A hobby servo contains a DC motor, a gear train, a potentiometer and a control circuit. The Arduino sends a PWM pulse every 20 ms, and the pulse width sets the target angle:

| Pulse width | Servo angle |
|-------------|-------------|
| ~1.0 ms     | 0°          |
| ~1.5 ms     | 90° (center)|
| ~2.0 ms     | 180°        |

The potentiometer reports the shaft's current position, and the control circuit compares it with the target and drives the motor until they match. This is **closed-loop feedback**. The Arduino `Servo.h` library generates the pulses when `write(angle)` is called.

## 2. Blinking System (4 servos)

- Each eye has one **upper eyelid** servo and one **lower eyelid** servo.
- On startup, all servos move to **90°** (open position).
- To blink, the Arduino moves all four eyelids to their closed angles at once. Upper and lower eyelids move in opposite directions, so their offsets (`*_DELTA`) have opposite signs.
- The eyelids stay closed for about 120 ms, then reopen in 10 small steps. Closing is fast and opening is slower, like a real human blink.
- The gap between blinks is random (2-5 seconds), so the motion looks natural instead of mechanical.

```
Open (90°) ──fast──► Closed (90° ± delta) ──hold 120 ms──► slow reopen (10 steps) ──► Open
                                random wait 2-5 s ◄──────────────────────────────────┘
```

## 3. Eyeball Movement (2 servos)

- **Servo 4 (pin 7):** rotates the eyeballs left and right.
- **Servo 3 (pin 4):** tilts the eyeballs up and down.
- Both eyeballs are connected by a mechanical linkage, so one pair of servos moves them together.

## 4. Joystick Input

- The joystick has two potentiometers (X and Y axes). The Arduino's 10-bit ADC reads each as a value from **0 to 1023**, with about 512 at rest.
- **Auto-calibration:** at startup, the Arduino averages 10 readings per axis to find the real rest position (`joyCenter`), because every joystick rests slightly differently.
- **Dead zone:** values within ±60 of the center are treated as "no input", so the eye stays steady and does not jitter.
- **Mapping:** the joystick value is mapped separately on each side of the center to a servo angle:
  - X axis: 50° (left) ← 90° → 130° (right)
  - Y axis: 60° (down) ← 90° → 120° (up)
- **Smoothing:** the servo moves **1° per loop cycle (10 ms)** toward the target angle instead of jumping, which gives smooth, eye-like motion. When the joystick is released, the eye glides back to the center.

## 5. Control Loop

```
setup():
    attach all servos
    move all servos to 90°
    measure joystick rest values
    schedule first blink

loop():
    read joystick X, Y
    convert to target angles (dead zone + mapping)
    move eyeball servos 1° toward target
    if time >= next blink time:
        blink()
        schedule next blink (random 2-5 s)
    delay(10 ms)
```

Blink timing uses `millis()`, so the Arduino does not block the joystick control while waiting between blinks. (Only the blink itself, about 250 ms, briefly pauses the eyeball.)

## 6. Power

Six servos can draw several amps when they move together. They are powered from an **external 5V 3-5A supply**, not from the Arduino 5V pin. The external supply's **GND is connected to Arduino GND** so the PWM signals have a common reference.

## Summary

| Function | Servos | Trigger |
|----------|--------|---------|
| Blinking | 4 (pins 2, 3, 5, 6) | Automatic, random timing |
| Eyeball left-right | 1 (pin 7) | Joystick X |
| Eyeball up-down | 1 (pin 4) | Joystick Y |
