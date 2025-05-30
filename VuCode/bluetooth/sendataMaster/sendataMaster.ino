#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 
const int lightPin = A0;    // chân cảm biến ánh sáng

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

  String cmd = (value > 600) ? "toi" : "sang";
    // Chỉ gửi khi trạng thái thay đổi
  if (cmd != lastCmd) {
    Serial.print("send");
    Serial.println(cmd);
    BT.println(cmd);
    lastCmd = cmd;
  }
  delay(500); 
}
