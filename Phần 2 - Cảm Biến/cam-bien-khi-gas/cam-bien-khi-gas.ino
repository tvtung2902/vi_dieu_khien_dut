int led = 13;
int pinA0 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, HIGH);
}

void loop() {
  int value = analogRead(pinA0);
  Serial.println(value);
  if(value > 300){
    digitalWrite(led, HIGH);
  } else{
    digitalWrite(led, LOW);
  }
  delay(500);
}
