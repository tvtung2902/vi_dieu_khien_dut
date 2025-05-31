#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(4, 5);

int in1 = 7;
int in2 = 8;
int e = 9;

String currentState = "";

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(e, OUTPUT);

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
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(e, 100);

  } else if (currentState == "CoGas") {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(e, 100);
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

- Module L298N:
    + IN1 -> D7
    + IN2 -> D8
    + ENA -> D9 (PWM)
    + OUT1/OUT2 -> Motor DC
    + VCC -> Pin, GND nối chung với Arduino
*/