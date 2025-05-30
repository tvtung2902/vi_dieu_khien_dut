#include <SoftwareSerial.h>
#define TX_PIN 10
#define RX_PIN 11
SoftwareSerial BTSerial (TX_PIN, RX_PIN);

void setup() {
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands: ");
  BTSerial.begin(38400);
}

void loop() {
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}