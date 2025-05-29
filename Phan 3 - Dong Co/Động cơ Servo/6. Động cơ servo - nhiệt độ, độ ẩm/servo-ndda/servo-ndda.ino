#include <DHT.h>
#include <Servo.h>

#define DHTPin 4
#define DHTType DHT11

DHT dht(DHTPin, DHTType);
Servo sv;

void setup() {
  Serial.begin(9600);
  dht.begin();
  sv.attach(9);
  sv.write(0);
  delay(1000);
}

void loop() {
  float hum = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  if (isnan(hum) || isnan(tempC) || isnan(tempF)) {
    delay(2000);
    return;
  }

  Serial.print("Độ ẩm: ");
  Serial.print(hum, 1);
  Serial.print(" %\tNhiệt độ: ");
  Serial.print(tempC, 1);
  Serial.print(" °C\t");
  Serial.print(tempF, 1);
  Serial.println(" °F");

  if (hum > 75) {
    sv.write(0);
    delay(300);
    sv.write(0);
    delay(300);
  } else {
    sv.write(180);
    delay(700);
    sv.write(0);
    delay(700);
  }
}

/*
Cách lắp:
- Cảm biến DHT11:
  + VCC -> 5V
  + GND -> GND
  + DATA -> D4
- Servo:
  + Signal -> D9
  + VCC -> 5V (hoặc nguồn riêng, chung GND)
  + GND -> GND Arduino
*/
