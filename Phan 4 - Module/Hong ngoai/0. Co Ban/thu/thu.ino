#include <IRremote.h>             
const int RECV_PIN = 11;            // Chân nhận tín hiệu IR
IRrecv irrecv(RECV_PIN);            // Tạo đối tượng IR receiver
decode_results results;             // Lưu kết quả giải mã

void setup() {
  Serial.begin(9600);              
  irrecv.enableIRIn();              // Bắt đầu nhận tín hiệu IR
}

void loop() {
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    Serial.println(results.value, HEX);
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
}
