#define LED 13

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(2), ledOn, RISING);
    attachInterrupt(digitalPinToInterrupt(3), ledOff, RISING);
}

void loop() {
    int btnPin_2 = digitalRead(2);
    int btnPin_3 = digitalRead(3);
    Serial.println(btnPin_2);
    Serial.println(btnPin_3);
}

void ledOn() {
    digitalWrite(LED, HIGH);
}

void ledOff() {
  digitalWrite(LED, LOW);
}