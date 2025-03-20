int led = 3;
int pinA0 = 0;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int value = analogRead(pinA0);
  value /= 4;
  analogWrite(led, value);
}
