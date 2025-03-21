int led = 13;
int light = 7;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  int value = digitalRead(light);
  Serial.println(value);
  if(value == 0){
    digitalWrite(led, LOW);
  }
  else {
    digitalWrite(led, HIGH);
  } 
  delay(10);
}

// trời tối : giá trị cao
// trời sáng : giá trị thấp

// không chiếu sáng : 1
// chiếu sáng : 0