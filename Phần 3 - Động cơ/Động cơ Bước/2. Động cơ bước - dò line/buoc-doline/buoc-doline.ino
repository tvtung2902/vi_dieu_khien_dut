#define LINE 2 

#include <Stepper.h>

#define BUOC 2048

Stepper stepper(BUOC, 8, 10, 9, 11);

void setup() {
  pinMode(LINE, INPUT);
  Serial.begin(9600);
  stepper.setSpeed(10);  // Tốc độ quay RPM
}

void loop() {
  int val = digitalRead(LINE);
  Serial.print("Giá trị cảm biến dò line: ");
  Serial.println(val);

  if (val == 1) {
    Serial.println("Dò line: Line đen → Quay thuận 90 độ");
    stepper.step((90.0 / 360.0) * BUOC);
  } else {
    Serial.println("Dò line: Line trắng → Quay ngược 60 độ");
    stepper.step((-60.0 / 360.0) * BUOC);
  }

  delay(1000);
}

/*
Cách lắp:
- Cảm biến dò line:
    + Tín hiệu -> chân D2
    + VCC -> 5V
    + GND -> GND
- Động cơ bước ULN2003:
    + IN1 -> D8
    + IN2 -> D10
    + IN3 -> D9
    + IN4 -> D11
    + Nguồn 5V và GND chung Arduino
*/
