#include <Servo.h>

int joyX = A0;

Servo sv;

void setup() {
  sv.attach(9);
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(joyX);

  Serial.print("X: ");
  Serial.print(x);

  if (x < 400) {
    sv.write(30);
    delay(300);
    sv.write(90);
    delay(300);
    Serial.println("Joystick left → Servo 30° rồi về 90°");
  } else if (x > 600) {
    sv.write(150);
    delay(300);
    sv.write(90);
    delay(300);
    Serial.println("Joystick right → Servo 150° rồi về 90°");
  } else {
    sv.write(90);
    Serial.println("Joystick center → Servo 90° giữ nguyên");
  }
}

/*
Cách lắp:
- Servo:
  + Signal -> D9
  + VCC -> 5V
  + GND -> GND
- Joystick:
  + X (analog) -> A0
  + VCC -> 5V
  + GND -> GND
*/
