#include <IRremote.h>
#include <Servo.h>

const int receiverPin = 3;
IRrecv irrecv(receiverPin);
decode_results results;

#include <Stepper.h>

#define BUOC 2048

Stepper stepper(BUOC, 8, 10, 9, 11);

double goc_quay = 0;

void setup() {
  stepper.setSpeed(10);

  Serial.begin(9600);

  irrecv.enableIRIn();
}

void translateIR() {
  switch (results.value) {
    case 0x10:
      goc_quay = 90.0;
      break;
    case 0x11:
      goc_quay = -180.0;
      break;
    case 0x12:
      goc_quay = 0;
      break;  
  }
}

void loop() {
  if (irrecv.decode(&results)) {

    translateIR();
    Serial.println(results.value, HEX);
    stepper.step((goc_quay / 360.0) * BUOC);
    delay(200);
    irrecv.resume();
  }
}

/*
Cách lắp:
- IR:
    + (-): GND
    + pin giữa: 5V
    + pin còn lại: pin D3

- Servo:
    + Tín hiệu → chân D9
    + VCC → 5V
    + GND → GND
*/
