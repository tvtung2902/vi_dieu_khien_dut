#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 
const int pin = 0;

void setup() {
  Serial.begin(9600);     
  BT.begin(9600);         
  Serial.println("Bắt đầu gửi dữ liệu qua HC-05");
}

String lastCmd="";

void loop() {
  int value = analogRead(pin);
  
  Serial.print("value: ");
  Serial.println(value);

  String cmd = "";
  if (value < 400) {
    cmd = "trai";
  }

  else if (value > 600){
    cmd = "phai";
  }

  else {
    cmd = "giua";
  }

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
- Joystick:
    + Y: A0 (trái(nhỏ) phải(lớn) : y, trên(lớn) dưới(nhỏ) : x)

- Module HC-05:
    + TX của HC-05 → chân 10
    + RX của HC-05 ← chân 11
    + VCC nối 5V
    + GND nối GND
*/
