const int pin = 7;
const int LED = 13;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(pin, INPUT);
    Serial.begin(9600);
}

void loop() {
  int value = digitalRead(pin);
  Serial.println(value);
  if (value == 1) {  
    digitalWrite(LED, HIGH); 
    Serial.println("Motion detected!");
  } else {
      digitalWrite(LED, LOW); 
      Serial.println("No motion detected.");
  }
  delay(200);
}

//* lí thuyết:
// nếu ko có chuyển động => giá trị cảm biến đọc được thấp => nếu nhỏ hơn giá trị điện áp tham chiếu => value = 0 => đèn ko sáng
// nếu có chuyển động => giá trị cảm biến đọc được cao => nếu vượt qua điện áp tham chiếu => value = 1 => đèn sáng