int ledStart = 2;
int ledEnd = 11;

void setup() {
  for(int led = ledStart; led <= ledEnd; led++){
    pinMode(led, OUTPUT);
  }
}

void loop() {
  for(int led = ledStart; led <= ledEnd; led++){
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  }
}