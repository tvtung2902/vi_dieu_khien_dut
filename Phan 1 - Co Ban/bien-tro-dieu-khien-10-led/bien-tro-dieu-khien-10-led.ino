int ledStart = 2;
int ledEnd = 11;
int pinA0 = 0;

void setup() {
  Serial.begin(9600);
  for (int led = ledStart; led <= ledEnd; led++) {
    pinMode(led, OUTPUT);
  }
}

void loop() {
  for (int led = ledStart; led <= ledEnd; led++) {
    int value = analogRead(pinA0);
    Serial.println(value);
    digitalWrite(led, HIGH);
    delay(value);
    digitalWrite(led, LOW);
    delay(value);
  }
}