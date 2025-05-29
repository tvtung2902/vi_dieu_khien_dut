#define LED 13

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), displayMicros, RISING);
    attachInterrupt(digitalPinToInterrupt(3), displayMillis, RISING);
}

void loop() {
    int btnPin_2 = digitalRead(2);
    int btnPin_3 = digitalRead(3);
    Serial.println(btnPin_2);
    Serial.println(btnPin_3);

    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
}

void displayMicros() {
    Serial.print("micros() = ");
    Serial.println(micros());
}

void displayMillis() {
    Serial.print("millis() = ");
    Serial.println(millis());
}