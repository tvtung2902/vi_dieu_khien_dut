const int pinA0 = 0;
const int LED = 13;

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  int value = analogRead(pinA0);
  Serial.println(value);
  if (value > 500) {  
    digitalWrite(LED, HIGH); 
    Serial.println("Motion detected!");
  } else {
      digitalWrite(LED, LOW); 
      Serial.println("No motion detected.");
  }
  delay(200);
}

//* lí thuyết:
// nếu ko có chuyển động => giá trị cảm biến đọc được thấp => đèn ko sáng
// nếu có chuyển động => giá trị cảm biến đọc được cao => đèn sáng