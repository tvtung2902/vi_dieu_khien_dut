// Servo:
//  Chan do -> 5V
//  Chan nau -> GND
//  Chan cam -> D9
// Thu Hong Ngoai:
//  Chan giua -> 3.3V
//  Chan S -> D2
//  Chan am -> GND 

#include <IRremote.hpp>
#include <Servo.h>

const int IR_RECEIVE_PIN = 2;
Servo myservo;
void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols (&Serial);
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
      IrReceiver.resume();
    } else {
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      IrReceiver.resume();
    }
    Serial.println();

    if (IrReceiver.decodedIRData.command == 0x1) {
      myservo.write(90);
      delay(500);
      myservo.write(0);
      delay(500);
    } else if (IrReceiver.decodedIRData.command == 0x2) {
      myservo.write(180);
      delay(500);
      myservo.write(0);
      delay(500);
    }
  }
}