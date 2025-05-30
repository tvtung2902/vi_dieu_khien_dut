#include <SoftwareSerial.h>
SoftwareSerial BTSerial (10, 11);
// Connect the HC-05 TX to Arduino pin 10
// Connect the HC-05 RX to Arduino pin 11

#define LIGHT 5 //define line tracking digital pin 2
int val = 0;

void setup() {
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial monitor");
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(LIGHT, INPUT);
}
void loop() {
  val = digitalRead(LIGHT);
  Serial.println(val);
  if (val == 1) {
    BTSerial.write("1");
    delay(1000);
  }
  else {
    BTSerial.write("0");
    delay(1000);
  }
  delay(1000);
}
