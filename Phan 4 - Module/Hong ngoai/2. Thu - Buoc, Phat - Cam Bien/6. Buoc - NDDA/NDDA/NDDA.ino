#include <IRremote.h>
IRsend irsend;

#include "DHT.h"
#define DHT11Pin 4
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType);

float humi;
float tempC;
float tempF;

void setup() {
  HT.begin();
  delay(1000);

  Serial.begin(9600);
}

void loop() {
  delay(1000);
  humi = HT.readHumidity();          // Đọc giá trị độ ẩm từ cảm biến
  tempC = HT.readTemperature();      // Đọc giá trị nhiệt độ theo độ C từ cảm biến
  tempF = HT.readTemperature(true);  // Đọc giá trị nhiệt độ theo độ F từ cảm biến

  Serial.print("Độ ẩm: ");
  Serial.print(humi, 1);
  Serial.print("\t");
  Serial.print(tempC, 1);
  Serial.print(" °C ");
  Serial.print("\t");
  Serial.print(tempF, 1);
  Serial.println(" °F");

  if (humi < 60) {
    irsend.sendSony(0x10, 12);  // gửi tín hiệu HEX 0x10, 12 bits
  } else {
    irsend.sendSony(0x11, 12);  // gửi tín hiệu HEX 0x11, 12 bits
  }
}

/*
Cách lắp:
- Cảm biến DHT11:
    + Chân OUT (tín hiệu) → D4
    + Chân VCC → 5V
    + Chân GND → GND

- IR:
    + (-): GND
    + pin giữa: 5V
    + pin còn lại: pin D3
*/