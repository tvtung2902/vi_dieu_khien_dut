#include <Stepper.h>
#include "DHT.h"

int dhtPin = 4;
#define DHTType DHT11
DHT ht(dhtPin, DHTType);

#define BUOC 2048
Stepper stp(BUOC, 8, 10, 9, 11);

float hum;
float tc;
float tf;

void setup() {
  Serial.begin(9600);
  stp.setSpeed(10);
  ht.begin();
  delay(1000);
}

void loop() {
  hum = ht.readHumidity();
  tc = ht.readTemperature();
  tf = ht.readTemperature(true);

  if (hum > 75) {
    Serial.println("Ẩm thấp → Quay ngược 60 độ");
    stp.step((-60.0 / 360.0) * BUOC);
  } else {
    Serial.println("Ẩm cao → Quay 90 độ");
    stp.step((90.0 / 360.0) * BUOC);
  }

  Serial.print("Độ ẩm: ");
  Serial.print(hum, 1);
  Serial.print("\t");
  Serial.print(tc, 1);
  Serial.print(" °C ");
  Serial.print(tf, 1);
  Serial.println(" °F");

  delay(2000);
}

/*
Cách lắp:
- Cảm biến DHT11: 
    + VCC -> 5V
    + GND -> GND
    + DATA -> D4
- ULN2003:
    + IN1 -> D8
    + IN2 -> D9
    + IN3 -> D10
    + IN4 -> D11
*/
