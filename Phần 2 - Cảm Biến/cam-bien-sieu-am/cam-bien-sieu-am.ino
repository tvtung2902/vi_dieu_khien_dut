int led = 13;

int trigPin = 3;
int echoPin = 5;

long duration;
long distance;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // xóa trạng thái củ của trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // gửi xung tín hiệu từ trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // đọc thời gian phản hồi từ echoPin(thời gian sóng âm truyền đi và quay lại)
  duration = pulseIn(echoPin, HIGH);

  // tính khoảng cách theo công thức : Distance = (time * speed of sound) / 2
  // 0.034 (m/micro s)
  distance = duration * 0.034 / 2;
      
  // Hiển thị khoảng cách đo được lên Serial Monitor
  Serial.print("Khoảng cách đo được: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance > 15){
    digitalWrite(led, LOW);
  }
  else if (distance >= 10 && distance <= 15){
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  }
  else{
    digitalWrite(led, HIGH);
  }
  // Dừng chương trình một chút trước khi đo tiếp
  delay(500);
}


// trig: phát
// echo: thu