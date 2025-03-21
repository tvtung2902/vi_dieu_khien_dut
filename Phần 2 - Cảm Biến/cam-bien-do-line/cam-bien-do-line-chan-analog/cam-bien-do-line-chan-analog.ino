int led = 13;
int pinA0 = 0;

void setup() {
  Serial.begin(9600);   
  pinMode(led, OUTPUT);
}

void loop() {
  int val = analogRead(pinA0);
  Serial.println(val);
  if(val < 500){
    digitalWrite(led, HIGH);
  }
  else{
      digitalWrite(led, LOW);
    }
    delay(200); 
}

//* lí thuyết:
// Vạch đen hấp thụ ánh sáng → Ít phản xạ → A0 đọc đc giá trị cao -> led tắt
// Vạch trắng phản xạ ánh sáng → Nhiều phản xạ → A0 nhận giá trị thấp -> led bật
