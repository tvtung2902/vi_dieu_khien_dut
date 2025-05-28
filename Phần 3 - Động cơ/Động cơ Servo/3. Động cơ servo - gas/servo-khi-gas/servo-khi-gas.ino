#include <Servo.h>

int gas = A0;
int val;
Servo sv;

void setup() {
  sv.attach(9);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(gas);
  Serial.print("Nồng độ khí gas: ");
  Serial.println(val);

  if (val > 400) {
    Serial.println("Phát hiện khí gas → Servo quay 180°");
    sv.write(180);
    delay(700);
    sv.write(0);
    delay(700);
  } else {
    Serial.println("Không phát hiện khí gas → Servo quay 30°");
    sv.write(30);
    delay(200);
    sv.write(0);
    delay(200);
  }
}

/*
Cách lắp:
- Servo:
  + Tín hiệu -> D9
  + VCC -> 5V
  + GND -> GND
- Cảm biến khí gas MQ2:
  + AO -> A0
  + VCC -> 5V
  + GND -> GND
*/
