int led = 13;
int pin = 7;

void setup() {
  Serial.begin(9600);   
  pinMode(led, OUTPUT);
}

void loop() {
  int val = digitalRead(pin);
  Serial.println(val);
  if(val == 0){
    digitalWrite(led, HIGH);
  }
  else{
      digitalWrite(led, LOW);
    }
    delay(20); 
}
//* lí thuyết:
// Vạch đen hấp thụ ánh sáng → Ít phản xạ → A0 đọc đc giá trị cao -> nếu > ngưỡng điện áp tham chiếu -> value = 1 -> led tắt
// Vạch trắng phản xạ ánh sáng → Nhiều phản xạ → A0 nhận giá trị thấp -> nếu < ngưỡng điện áp tham chiếu -> value = 0 -> led bật

// *lúc thực hành không dùng vật cản che ~ line đen => led tắt, ngược lại: nếu che => led sáng
