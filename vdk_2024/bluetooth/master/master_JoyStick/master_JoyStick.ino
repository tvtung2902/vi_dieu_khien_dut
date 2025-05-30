#include <SoftwareSerial.h>
SoftwareSerial BTSerial (10, 11); // RX | TX
// Connect the HC-05 TX to Arduino pin 10
// Connect the HC-05 RX to Arduino pin 11

int val = 0;

int joystick_x = A0;
int joystick_y = A1;
int joystick_z = 5;

void setup() {
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial monitor");
  BTSerial.begin(9600);
  Serial.begin(9600);

  pinMode(joystick_z, INPUT_PULLUP);
}
void loop() {
  int x, y, z;
  x = analogRead(joystick_x);
  y = analogRead(joystick_y);
  z = analogRead(joystick_z);

  Serial.print("x = ");
  Serial.print(x);
  Serial.print(",");

  Serial.print(" y = ");
  Serial.print(y);
  Serial.print(",");

  Serial.print(" z = ");
  Serial.println(z);
  if (x < 200 || y < 200) {
    BTSerial.write("1");
    delay(1000);
  }
  else {
    BTSerial.write("0");
    delay(1000);
  }
  delay(1000);
}
