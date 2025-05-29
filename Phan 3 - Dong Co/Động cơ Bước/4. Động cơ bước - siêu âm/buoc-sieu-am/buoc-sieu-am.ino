#define TRIG 3    
#define ECHO 5  

#include <Stepper.h>

#define BUOC 2048

Stepper stepper(BUOC, 8, 10, 9, 11);

long duration;
long distance;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(10);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2; // cm

  Serial.print("Khoảng cách siêu âm: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 20) {
    Serial.println("Vật cản gần → Quay ngược 60 độ");
    stepper.step((-60.0 / 360.0) * BUOC);

  } else {
    Serial.println("Vật cản xa → Quay thuận 90 độ");
    stepper.step((90.0 / 360.0) * BUOC);
  }

  delay(1000);
}

/*
Cách lắp:
- Cảm biến siêu âm HC-SR04:
    + TRIG -> chân D3
    + ECHO -> chân D5
    + VCC -> 5V
    + GND -> GND
- Động cơ bước ULN2003:
    + IN1 -> D8
    + IN2 -> D9
    + IN3 -> D10
    + IN4 -> D11
*/
