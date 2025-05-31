#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 

const int trigPin = 3;
const int echoPin = 5;

long duration;
long distance;
String lastCmd = "";

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Bắt đầu gửi dữ liệu khoảng cách qua HC-05");
}

void loop() {
  // Phát xung siêu âm
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Đo thời gian phản hồi
  duration = pulseIn(echoPin, HIGH);

  // Tính khoảng cách (cm)
  distance = duration * 0.034 / 2;

  Serial.print("Khoảng cách: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Gửi lệnh tùy khoảng cách
  String cmd = (distance > 15) ? "Xa" : "Gan";

  if (cmd != lastCmd) {
    Serial.print("send");
    Serial.println(cmd);
    BT.println(cmd);
    lastCmd = cmd;
  }

  delay(500);
}

/*
Cách lắp:
- Cảm biến siêu âm HC-SR04:
    + Trig → chân 3
    + Echo → chân 5
    + VCC → 5V
    + GND → GND

- Module HC-05:
    + TX HC-05 → chân 10
    + RX HC-05 ← chân 11
    + VCC → 5V
    + GND → GND
*/
