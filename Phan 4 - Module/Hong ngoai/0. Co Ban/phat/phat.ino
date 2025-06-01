#include <IRremote.h>

IRsend irsend; // Đối tượng để gửi tín hiệu IR

void setup() {
  Serial.begin(9600);
}

void loop() {
  irsend.sendSony(0x10, 12);
  Serial.println("Đã gửi mã Sony: 0x10, 12"); // gửi tín hiệu HEX 0x10, 12 bits
  delay(2000);

  irsend.sendSony(0x11, 12);
  Serial.println("Đã gửi mã Sony: 0x11"); // gửi tín hiệu HEX 0x11, 12 bits
  delay(2000);
}