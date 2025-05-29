#include <Servo.h>

int doline = 2;
int val;
Servo sv;

void setup() {
  sv.attach(9);
  pinMode(doline, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(doline);
  Serial.print("Trạng thái dò line (digital): ");
  Serial.println(val);

  if (val == 1) {
    Serial.println("Line đen → Servo quay 30°");
    sv.write(30);
    delay(200);
    sv.write(0);
    delay(200);
  } else {
    Serial.println("Line trắng→ Servo quay 180°");
    sv.write(180);
    delay(700);
    sv.write(0);
    delay(700);
  }
}

/*
Cách lắp:
- Servo:
  + Tín hiệu -> D9
  + VCC -> 5V
  + GND -> GND
- Cảm biến dò line:
  + OUT -> D2
  + VCC -> 5V
  + GND -> GND
*/
