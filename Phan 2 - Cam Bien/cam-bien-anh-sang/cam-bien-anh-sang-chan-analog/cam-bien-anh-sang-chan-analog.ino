int led = 13;
int light = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  int value = analogRead(light);
  Serial.println(value);
  if(value < 500){
    digitalWrite(led, LOW);
  }
  else if (value >= 500 && value <= 700){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
  else {
    digitalWrite(led, HIGH);
  } 
  delay(10);
}

// trời tối : giá trị cao
// trời sáng : giá trị thấp
