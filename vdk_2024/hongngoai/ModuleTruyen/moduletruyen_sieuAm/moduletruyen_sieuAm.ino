// cảm biến GAS + A0
#include <IRremote.hpp> // include the library
#include "DHT.h"
const int IR_SEND_PIN = 2;

int val = 0;

const int trigPin = 5;
const int echoPin = 3;
long duration;
long distance;

void setup() { 
  Serial.begin(9600);

  Serial.print(F("Send IR signals at pin "));
  Serial.println(IR_SEND_PIN);
    
  IrSender.begin(IR_SEND_PIN); 
  IrSender.enableIROut(38);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

uint8_t sAddress = 0x00;
uint8_t sCommand = 0x01;
uint8_t sRepeats = 0;

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance Measured = ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance >= 20 && distance <= 30){
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
