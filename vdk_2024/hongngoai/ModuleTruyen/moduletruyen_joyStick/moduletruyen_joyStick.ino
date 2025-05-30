// cảm biến GAS + A0
#include <IRremote.hpp> // include the library
#include "DHT.h"
const int IR_SEND_PIN = 2;

int val = 0;

int joystick_x = A0;
int joystick_y = A1;
int joystick_z = 5;

void setup() { 
  Serial.begin(9600);

  Serial.print(F("Send IR signals at pin "));
  Serial.println(IR_SEND_PIN);
    
  IrSender.begin(IR_SEND_PIN); 
  IrSender.enableIROut(38);

  pinMode(joystick_z, INPUT_PULLUP);
}

uint8_t sAddress = 0x00;
uint8_t sCommand = 0x01;
uint8_t sRepeats = 0;

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

  if (x < 200 || y < 200){
    sCommand = 0x01;
  }
  else {
    sCommand = 0x02;
  } 
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
