#include <IRremote.h>
IRsend irsend;

int pinY = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(pinY);
  Serial.println(value);

  if(value < 400){
    irsend.sendSony(0x10, 12);// gửi tín hiệu HEX 0x10, 12 bits
  }
  else if (value > 600){
    irsend.sendSony(0x11, 12);// gửi tín hiệu HEX 0x11, 12 bits
  }
  else{
    irsend.sendSony(0x12, 12);// gửi tín hiệu HEX 0x12, 12 bits
  }
  delay(1000);
}


/*
Cách lắp:
- Joystick:
    + Y: A0 (trái(nhỏ) phải(lớn) : y, trên(lớn) dưới(nhỏ) : x)

- IR:
    + (-): GND
    + pin giữa: 5V
    + pin còn lại: pin D3
*/