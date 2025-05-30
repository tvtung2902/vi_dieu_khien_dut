#include <SoftwareSerial.h>
const int TX = 5;
const int RX = 6;
SoftwareSerial BTSerial (TX, RX); // TX RX
// Connect the HC-05 TX to Arduino pin 10
// Connect the HC-05 RX to Arduino pin 11
int in1 = 7;
int in2 = 8;
int e = 9;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(e, OUTPUT);

  Serial.begin(9600);
  Serial.println("Enter your commands:");
  // HC-05 default baud rate is 9600
  BTSerial.begin(9600);
}
void loop() {
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.write(data);
    Serial.println(data);
    if(data == '1') {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(e, 100);
    }
    else if(data == '0') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(e, 100);
    }
    delay(500);
  }
}