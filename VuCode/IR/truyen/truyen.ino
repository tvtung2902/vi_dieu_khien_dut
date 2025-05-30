#include <IRremote.h>
IRsend irsend;// gửi tín hiệu hồng hoại

int light =0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(A0);
  Serial.println(value);
  if(value>600){
    Serial.println("Tối -> Quay thuận 90 độ");
    irsend.sendSony(0x10, 12);// gửi tín hiệu HEX 0x10, 12 bits
  }
  else{
    Serial.println("Sáng -> Quay nghịch 180 độ");
    irsend.sendSony(0x11, 12);// gửi tín hiệu HEX 0x10, 12 bits
  }
  delay(1000);
}
