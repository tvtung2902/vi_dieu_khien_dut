int led = 13;
int btn = 7;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
}

void loop() {
  int value = digitalRead(btn);
  digitalWrite(led, value);
}