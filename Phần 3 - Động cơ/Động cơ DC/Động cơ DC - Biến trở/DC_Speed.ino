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
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    int analogread = analogRead(analog);
    int speed = map(analogread, 0, 1023, 0, 255);
    Serial.println("speed: ");
    Serial.println(speed);
    analogWrite(e, 40);
}
