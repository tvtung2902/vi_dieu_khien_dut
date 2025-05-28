#include <Servo.h>

Servo myservo;

int ldr = A0;
int val;

void setup() {
  myservo.attach(6);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(ldr);
  Serial.print("Ánh sáng: ");
  Serial.println(val);

  if (val < 400) {
    Serial.println("Trời sáng → quay servo 30 độ rồi về 0 độ");
    myservo.write(30);
    delay(200);
    myservo.write(0);
    delay(200);
  } else {
    Serial.println("Trời tối → quay servo 180 độ rồi về 0 độ");
    myservo.write(180);
    delay(700);
    myservo.write(0);
    delay(700);
  }
}

/*
Cách lắp:
- Cảm biến ánh sáng LDR:
    + Một chân nối A0
    + Chân còn lại nối 5V và GND
- Servo:
    + Tín hiệu -> D6
    + VCC -> 5V
    + GND -> GND
*/