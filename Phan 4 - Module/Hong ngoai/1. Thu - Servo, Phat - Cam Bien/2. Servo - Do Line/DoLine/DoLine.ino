#include <IRremote.h>
IRsend irsend;

int pin = 2;

void setup()
{ 
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int value = digitalRead(pin);
  Serial.println(value);

  if(value == 1){
    irsend.sendSony(0x10, 12);// gửi tín hiệu HEX 0x10, 12 bits
  }
  else{
    irsend.sendSony(0x11, 12);// gửi tín hiệu HEX 0x10, 12 bits
  }
  delay(1000);
}

/*
Cách lắp:
- Cảm biến dò line:
    + 1 chân nối D2
    + 2 chân còn lại nối 5V và GND

- IR:
    + (-): GND
    + pin giữa: 5V
    + pin còn lại: pin D3
*/
