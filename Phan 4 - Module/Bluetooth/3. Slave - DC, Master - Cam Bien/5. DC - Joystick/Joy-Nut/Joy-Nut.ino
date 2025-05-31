#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 
int joyStickZ = 3;

void setup() {
  pinMode(joyStickZ, INPUT_PULLUP);
  Serial.begin(9600);     
  BT.begin(9600);         
  Serial.println("Bắt đầu gửi dữ liệu qua HC-05");
}

String lastCmd="";

void loop() {
  int z = digitalRead(joyStickZ);
  
  Serial.print("value: ");
  Serial.println(z);

  String cmd = "";
  if (z == 1) {
    cmd = "KhongBam";
  }
  else {
    cmd = "Bam";
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
    + Z: pin D3

- Module HC-05:
    + TX của HC-05 → chân 10
    + RX của HC-05 ← chân 11
    + VCC nối 5V
    + GND nối GND
*/
