#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(4, 5);

#include <Stepper.h>
#define BUOC 2048
Stepper stepper(BUOC, 8, 10, 9, 11);

String currentState = "";

void setup() {
  stepper.setSpeed(10);
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Sẵn sàng nhận lệnh từ HC-05.");
}

void loop() {
  if (BT.available()) {
    String response = BT.readStringUntil('\n');
    response.trim();
    Serial.print("Phản hồi HC-05: ");
    Serial.println(response);
    currentState = response;
  }

  if (currentState == "KhongGas") {
    stepper.step((90.0 / 360.0) * BUOC);
  }
  else if (currentState == "CoGas") {
    stepper.step((-90.0 / 360.0) * BUOC);
  }
  delay(500);
}

/*
Cách lắp:
- Module HC-05:
    + TX của HC-05 → chân 4
    + RX của HC-05 ← chân 5
    + VCC → 5V
    + GND → GND

- Động cơ bước 28BYJ-48 + Driver ULN2003:
    + IN1 → chân 8
    + IN2 → chân 9
    + IN3 → chân 10
    + IN4 → chân 11
    + VCC → 5V
    + GND → GND
*/