int analog = A0;
int in1 = 7;
int in2 = 8;
int e = 9;

void setup() {
    Serial.begin(9600);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(e, OUTPUT);
}

void loop() {
    int analogread = analogRead(analog);
    Serial.println(analogread);
    if(analogread < 500) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(e, 40);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(e, 50 );
    }
    delay(1000);
}