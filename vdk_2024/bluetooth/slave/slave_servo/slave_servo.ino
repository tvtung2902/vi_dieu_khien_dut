#include <SoftwareSerial.h>
#include<Servo.h> 

const int TX = 10;
const int RX = 11;
SoftwareSerial BTSerial (TX, RX); // TX RX
// Connect the HC-05 TX to Arduino pin 10
// Connect the HC-05 RX to Arduino pin 11

Servo myservo; 
void setup() {
  myservo.attach(9); 
  Serial.begin(9600);
  // HC-05 default baud rate is 9600
  BTSerial.begin(9600);
}
void loop() {
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.println(data);
    Serial.write(data);
    if(data == '1') {
      myservo.write(180); 
      delay(1000);
      myservo.write(0); 
    }
    else if(data == '0') {
      myservo.write(90); 
      delay(1000);
      myservo.write(0); 
    }
  }
  delay(1000);
}
