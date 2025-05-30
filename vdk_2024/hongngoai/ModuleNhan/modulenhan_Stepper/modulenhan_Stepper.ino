#include <IRremote.h> 
#include "Stepper.h"

int in1 = 8; 
int in2 = 9; 
int in3 = 10; 
int in4 = 11; 
const int STEPS = 2048;

Stepper stepper = Stepper(STEPS, in4, in2, in3, in1);

int degreeToSteps(int d, int steps = STEPS){
  if(d == 0) return 0;
  return steps/(360/d);
}

const int IR_RECEIVE_PIN = 2;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);



  stepper.setSpeed(15);
}

int step = degreeToSteps(45);

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
          Serial.println("thuan");
          stepper.step(-step);
      } else if (IrReceiver.decodedIRData.command == 0x2) {
          stepper.step(step);
          Serial.println("nguoc");

      } 
    }
}
