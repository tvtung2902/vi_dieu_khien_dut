#include <SoftwareSerial.h>
const int TX = 5;
const int RX = 6;
SoftwareSerial BTSerial (TX, RX); // TX RX
// Connect the HC-05 TX to Arduino pin 10
// Connect the HC-05 RX to Arduino pin 11

#include "Stepper.h"
const int STEPS = 2048;
int in1 = 8;
int in2 = 9;
int in3 = 10;
int in4 = 11;
Stepper stepper = Stepper(STEPS, in4, in2, in3, in1);


int degreeToSteps(int d, int steps = STEPS) {
  if (d == 0) return 0;
  return steps/(360/d);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Enter your commands:");
  stepper.setSpeed(15);
  BTSerial.begin(9600);
}
void loop() {
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()) {
    char data = BTSerial.read();
    int step = degreeToSteps(90);
    Serial.write(data);
    Serial.println(data);
    if(data == '1') {
      stepper.step(step);
    }
    else if(data == '0') {
      stepper.step(-step);
    }
  }
  delay(500);
}