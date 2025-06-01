#include <IRremote.h>
#include <Servo.h>

const int receiverPin = 3;
IRrecv irrecv(receiverPin);
decode_results results;

Servo myservo;

double goc_quay = 0;

void setup() {
  myservo.attach(9);
  myservo.write(0);

  Serial.begin(9600);

  irrecv.enableIRIn();
}

void translateIR() {
  switch (results.value) {
    case 0x10:
      goc_quay = 60.0;
      break;
    case 0x11:
      goc_quay = 180.0;
      break;
  }
}

void loop() {
  if (irrecv.decode(&results)) {

    translateIR();
    Serial.println(results.value, HEX);

    if (goc_quay > 90) {
      myservo.write(goc_quay);
      delay(700);
      myservo.write(0);
      delay(700);
    } else {
      myservo.write(goc_quay);
      delay(200);
      myservo.write(0);
      delay(200);
    }
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
