#include <Servo.h>

// ---------- Servo pins ----------
Servo lowerR;   // servo 1 -> pin 2  (lower eyelid)
Servo upperR;   // servo 2 -> pin 3  (upper eyelid)
Servo eyeY;     // servo 3 -> pin 4  (eyeball up-down)
Servo eyeX;     // servo 4 -> pin 7  (eyeball left-right)
Servo lowerL;   // servo 5 -> pin 6  (lower eyelid)
Servo upperL;   // servo 6 -> pin 5  (upper eyelid)

// ---------- Joystick ----------
const int JOY_X = A0;
const int JOY_Y = A1;

// ---------- Eyeball range ----------
const int CENTER = 90;
const int X_LEFT = 50,  X_RIGHT = 130;
const int Y_DOWN = 60,  Y_UP    = 120;
const int DEAD_ZONE = 60;

// ---------- Blink settings ----------
// Open = 90. Agar koi eyelid ulti ja rahi ho to uska sign (+/-) badal do
const int UPPER_R_DELTA = +40;
const int UPPER_L_DELTA = +40;
const int LOWER_R_DELTA = -40;
const int LOWER_L_DELTA = -40;

const unsigned long BLINK_MIN_GAP = 2000;  // ms
const unsigned long BLINK_MAX_GAP = 5000;  // ms
const int CLOSE_HOLD = 120;                // ms band rehne ka time
const int OPEN_STEPS = 10;                 // khulne ke steps
const int OPEN_STEP_DELAY = 12;            // ms per step

int joyCenterX = 512, joyCenterY = 512;
int posX = CENTER, posY = CENTER;
unsigned long nextBlink = 0;

void setup() {
  lowerR.attach(2);
  upperR.attach(3);
  eyeY.attach(4);
  eyeX.attach(7);
  lowerL.attach(6);
  upperL.attach(5);

  resetAll();
  delay(2000);

  // Joystick rest value (is waqt joystick ko mat chhuo)
  long sx = 0, sy = 0;
  for (int i = 0; i < 10; i++) {
    sx += analogRead(JOY_X);
    sy += analogRead(JOY_Y);
    delay(10);
  }
  joyCenterX = sx / 10;
  joyCenterY = sy / 10;

  randomSeed(analogRead(A5));
  nextBlink = millis() + random(BLINK_MIN_GAP, BLINK_MAX_GAP);
}

void loop() {
  // ----- Eyeball joystick se -----
  int targetX = axisToAngle(analogRead(JOY_X), joyCenterX, X_LEFT, X_RIGHT);
  int targetY = axisToAngle(analogRead(JOY_Y), joyCenterY, Y_DOWN, Y_UP);

  if (targetX > posX) posX++; else if (targetX < posX) posX--;
  if (targetY > posY) posY++; else if (targetY < posY) posY--;
  eyeX.write(posX);
  eyeY.write(posY);

  // ----- Auto blink -----
  if (millis() >= nextBlink) {
    blink();
    nextBlink = millis() + random(BLINK_MIN_GAP, BLINK_MAX_GAP);
  }

  delay(10);
}

int axisToAngle(int val, int joyCenter, int minAngle, int maxAngle) {
  int diff = val - joyCenter;
  if (abs(diff) < DEAD_ZONE) return CENTER;
  if (diff < 0) return map(val, 0, joyCenter - DEAD_ZONE, minAngle, CENTER);
  return map(val, joyCenter + DEAD_ZONE, 1023, CENTER, maxAngle);
}

void resetAll() {
  lowerR.write(90);
  upperR.write(90);
  eyeY.write(90);
  eyeX.write(90);
  lowerL.write(90);
  upperL.write(90);
  posX = 90;
  posY = 90;
}

void blink() {
  // Band hona (fast)
  upperR.write(90 + UPPER_R_DELTA);
  upperL.write(90 + UPPER_L_DELTA);
  lowerR.write(90 + LOWER_R_DELTA);
  lowerL.write(90 + LOWER_L_DELTA);
  delay(CLOSE_HOLD);

  // Khulna (thoda slow)
  for (int i = OPEN_STEPS; i >= 0; i--) {
    upperR.write(90 + UPPER_R_DELTA * i / OPEN_STEPS);
    upperL.write(90 + UPPER_L_DELTA * i / OPEN_STEPS);
    lowerR.write(90 + LOWER_R_DELTA * i / OPEN_STEPS);
    lowerL.write(90 + LOWER_L_DELTA * i / OPEN_STEPS);
    delay(OPEN_STEP_DELAY);
  }
}