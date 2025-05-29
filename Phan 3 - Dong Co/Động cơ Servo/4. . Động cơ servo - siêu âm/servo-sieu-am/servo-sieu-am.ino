#include <Servo.h>

int trig = 3;
int echo = 5;
long duration;
long distance;
Servo sv;

void setup() {
  sv.attach(9);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Khoảng cách: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    Serial.println("Vật cản gần → Servo quay 180°");
    sv.write(180);
    delay(700);
    sv.write(0);
    delay(700);
  } else {
    Serial.println("Vật cản xa → Servo quay 30°");
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
- Cảm biến siêu âm HC-SR04:
  + Trig -> D3
  + Echo -> D5
  + VCC -> 5V
  + GND -> GND
*/
