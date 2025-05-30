// cảm biến GAS + A0
#include <IRremote.hpp> // include the library
const int IR_SEND_PIN = 2;

int GAS_PIN = 0;
int val = 0;

void setup() { 
  Serial.begin(9600);

  Serial.print(F("Send IR signals at pin "));
  Serial.println(IR_SEND_PIN);
    
  IrSender.begin(IR_SEND_PIN); 
  IrSender.enableIROut(38);

  pinMode(GAS_PIN, INPUT);
}

uint8_t sAddress = 0x00;
uint8_t sCommand = 0x01;
uint8_t sRepeats = 0;

void loop() {
  val = analogRead(GAS_PIN);
  sCommand = val > 500 ? 0x01 : 0x02; // Ko thì 0x01, Có thì 0x02

  Serial.println();
  Serial.println(val); 
  Serial.print(F("Send now: address=0x00, command=0x"));
  Serial.print(sCommand, HEX);
  Serial.print(F(", repeats="));
  Serial.print(sRepeats);
  Serial.println();
  Serial.println(F("Send standard RC5 with 8 bit address"));
  Serial.flush();
  IrSender.sendRC5(sAddress, sCommand, sRepeats, false); 
  Serial.println(F("Sent"));
  delay(1500);
}
