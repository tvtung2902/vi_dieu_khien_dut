#include <SoftwareSerial.h>
SoftwareSerial BTSerial (10, 11); 
// Connect the HC-05 TX to Arduino pin 10
// Connect the HC-05 RX to Arduino pin 11

int val = 0;

const int trigPin = 5;
const int echoPin = 3;
long duration;
long distance;

void setup() {
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial monitor");
  BTSerial.begin(9600);
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance Measured = ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance >= 20 && distance <= 30) {
    BTSerial.write("1");
    delay(1000);
  }
  else {
    BTSerial.write("0");
    delay(1000);
  }
  delay(1000);
}
