#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);

#include "DHT.h"
#define DHT11Pin 4
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType);

float humi;
float tempC;
float tempF;


void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Bắt đầu gửi dữ liệu qua HC-05");
  HT.begin();
  delay(1000);
}

String lastCmd = "";

void loop() {
  delay(1000);
  humi = HT.readHumidity();          
  tempC = HT.readTemperature();      
  tempF = HT.readTemperature(true); 

  Serial.print("Độ ẩm: ");
  Serial.print(humi, 1);
  Serial.print("\t");
  Serial.print(tempC, 1);
  Serial.print(" °C ");
  Serial.print("\t");
  Serial.print(tempF, 1);
  Serial.println(" °F");

  String cmd = "";
  if(humi < 80){
    cmd = "Be";
  } else{
    cmd = "Lon";
  }

  // if(tempC > 34){
  //   cmd = "Lon";
  // }
  // else{
  //   cmd = "Be";
  // }

  if (cmd != lastCmd) {
    Serial.print("send");
    Serial.println(cmd);
    BT.println(cmd);
    lastCmd = cmd;
  }
  delay(500);
}

/*
Cách lắp:
- Cảm biến DHT11:
    + Chân OUT (tín hiệu) → D4
    + Chân VCC → 5V
    + Chân GND → GND

- Module HC-05:
    + TX của HC-05 → chân 10
    + RX của HC-05 ← chân 11
    + VCC nối 5V
    + GND nối GND
*/
