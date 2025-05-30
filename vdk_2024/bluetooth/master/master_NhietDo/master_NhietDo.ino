#include <SoftwareSerial.h>
#include "DHT.h"
SoftwareSerial BTSerial (10, 11);
// Connect the HC-05 TX to Arduino pin 10
// Connect the HC-05 RX to Arduino pin 11

int DHTPIN = 5; // Cảm biến nhiệt độ độ ấm nối chân d5
int DHTTYPE = DHT11;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial monitor");
  BTSerial.begin(9600);
  Serial.begin(9600);

  dht.begin();
}
void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.print("Nhiet do: ");
  Serial.println(t);

  Serial.print("Do am: ");
  Serial.println(h);

  if (t >= 34 && h >= 80) {
    BTSerial.write("1");
    Serial.println(1);
    delay(1000);
  }
  else {
    BTSerial.write("0");
    Serial.println(0);
    delay(1000);
  }
  delay(1000);
}
