// DC:
//  Chan OUT1,2 -> 2 chan dong co
//  Chan ENA,IN1,IN2 -> D9,8,7
//  Chan +12V -> PIN
//  Chan GND -> PIN + GND arduino
// Thu Hong Ngoai:
//  Chan giua -> 3.3V
//  Chan S -> D2
//  Chan am -> GND

#include <IRremote.hpp>

int in1 = 7;
int in2 = 8;
int e = 9;

const int IR_RECEIVE_PIN = 2;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols (&Serial);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(e, OUTPUT);
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
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(e, 80);
      Serial.println("xoay 1");
    } else if (IrReceiver.decodedIRData.command == 0x2) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(e, 80);
      Serial.println("xoay 2");
    }
    else if (IrReceiver.decodedIRData.command == 0x10) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(e, 80);
      Serial.println("Dung");
    }
    delay(1000);
  }
}