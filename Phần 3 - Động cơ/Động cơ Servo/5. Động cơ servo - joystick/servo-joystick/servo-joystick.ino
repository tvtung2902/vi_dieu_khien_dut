#include <Servo.h>

int joyX = A0;
int joyZ = 3;

Servo sv;

void setup() {
  sv.attach(9);
  pinMode(joyZ, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(joyX);
  int z = digitalRead(joyZ);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(", Z: ");
  Serial.println(z);

  if (z == LOW) {
    sv.write(90);
    Serial.println("Button pressed → Servo stop at 90°");
  } else if (x < 400) {
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
  + Z -> D3 (INPUT_PULLUP)
  + VCC -> 5V
  + GND -> GND
*/
