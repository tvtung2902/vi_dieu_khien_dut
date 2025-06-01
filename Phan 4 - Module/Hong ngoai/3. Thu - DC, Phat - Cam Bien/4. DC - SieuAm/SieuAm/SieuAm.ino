#include <IRremote.h>
IRsend irsend;

const int trigPin = 5;
const int echoPin = 6;

long duration;
long distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
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

  if (distance > 15) {
    irsend.sendSony(0x10, 12);
  }
  else {
    irsend.sendSony(0x11, 12);  
  }

  delay(1000);
}


/*
Cách lắp:
- Cảm biến siêu âm HC-SR04:
    + Trig → chân 5
    + Echo → chân 6
    + VCC → 5V
    + GND → GND

- IR:
    + (-): GND
    + pin giữa: 5V
    + pin còn lại: pin D3
*/