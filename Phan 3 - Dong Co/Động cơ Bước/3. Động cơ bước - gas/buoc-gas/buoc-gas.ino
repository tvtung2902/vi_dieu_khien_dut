#define GAS A0

#include <Stepper.h>

#define BUOC 2048

Stepper stepper(BUOC, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(10);
  pinMode(GAS, INPUT);
}

void loop() {
  int val = analogRead(GAS);
  Serial.print("Giá trị cảm biến khí gas: ");
  Serial.println(val);

  if (val > 150) {
    Serial.println("Khí gas thấp → Quay ngược 60 độ");
    stepper.step((-180.0 / 360.0) * BUOC);
  } else {
    Serial.println("Khí gas cao → Quay thuận 90 độ");
    stepper.step((90.0 / 360.0) * BUOC);

  }

  delay(500);
}

/*
Cách lắp:
- Cảm biến khí gas MQ:
    + Tín hiệu analog -> chân A0
    + VCC -> 5V
    + GND -> GND
- Động cơ bước ULN2003:
    + IN1 -> D8
    + IN2 -> D9
    + IN3 -> D10
    + IN4 -> D11
*/
