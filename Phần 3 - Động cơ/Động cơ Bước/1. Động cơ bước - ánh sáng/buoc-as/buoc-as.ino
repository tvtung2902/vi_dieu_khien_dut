#include <Stepper.h>

#define BUOC 2048
#define LDR A0

Stepper stepper(BUOC, 8, 10, 9, 11);

void setup() {
  stepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  int l = analogRead(LDR);
  Serial.print("Ánh sáng: ");
  Serial.println(l);

  if (l < 400) {
    Serial.println("Trời sáng → Quay 90 độ");
    stepper.step((90.0 / 360.0) * BUOC);
  } else {
    Serial.println("Trời tối → Quay ngược 60 độ");
    stepper.step((-60.0 / 360.0) * BUOC);
  }

  delay(2000);
}

/*
Cách lắp:
- ULN2003:
    + IN1 -> D8
    + IN2 -> D10
    + IN3 -> D9
    + IN4 -> D11
    + Nguồn 5V và GND nối chung Arduino
- Cảm biến ánh sáng LDR:
    + Một chân nối A0
    + Chân còn lại nối 5V qua trở 10kΩ và GND
*/
