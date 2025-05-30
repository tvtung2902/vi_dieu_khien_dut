#include <IRremote.h> // thư viện hỗ trợ IR remote

const int receiverPin = 3; // chân digital 8 dùng để đọc tín hiệu
IRrecv irrecv(receiverPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín hiệu

#include <Stepper.h>

#define BUOC 2048

Stepper stepper(BUOC, 8, 10, 9, 11);

double goc_quay=0;
void setup()
{
  Serial.begin(9600);// serial 
  irrecv.enableIRIn(); // start the IR receiver
  stepper.setSpeed(10);
}
// translate IR signals
void translateIR()
{
  switch(results.value)
  {
    case 0x10:  goc_quay=90.0;
                break;    
    case 0x11:  goc_quay=-180.0;
                break;
  }
}
void loop()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    translateIR();
    Serial.println(results.value, HEX);
    stepper.step((goc_quay / 360.0) * BUOC);
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
}
