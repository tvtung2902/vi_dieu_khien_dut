#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 
const int lightPin = A0;

void setup() {
  Serial.begin(9600);     
  BT.begin(9600);         
  Serial.println("Bắt đầu gửi dữ liệu ánh sáng qua HC-05");
}

String lastCmd="";

void loop() {
  int value = analogRead(lightPin);
  
  Serial.print("Ánh sáng: ");
  Serial.println(value);

  String cmd = (value > 700) ? "toi" : "sang";

  // gửi khi trạng thái thay đổi
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
- Cảm biến ánh sáng:
    + 1 chân nối A0
    + 2 chân còn lại nối 5V và GND

- Module HC-05:
    + TX của HC-05 → chân 10
    + RX của HC-05 ← chân 11
    + VCC nối 5V
    + GND nối GND
*/
