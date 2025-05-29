#include <Stepper.h>

int joyX = 0;

#define BUOC 2048
Stepper stp(BUOC, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  stp.setSpeed(10);
}

void loop() {
  int x = analogRead(joyX);

  if (x < 400) {
    Serial.println("Quay thuận 90 độ");
    stp.step((90.0 / 360.0) * BUOC);
  }

  if (x > 600) {
    Serial.println("Quay ngược 90 độ");
    stp.step((-90.0 / 360.0) * BUOC);
  }

  delay(200);
}

/*
Cách lắp:
- Joystick:
    + Trục X -> A0
    + VCC -> 5V
    + GND -> GND
- ULN2003:
    + IN1 -> D8
    + IN2 -> D9
    + IN3 -> D10
    + IN4 -> D11
*/ 
