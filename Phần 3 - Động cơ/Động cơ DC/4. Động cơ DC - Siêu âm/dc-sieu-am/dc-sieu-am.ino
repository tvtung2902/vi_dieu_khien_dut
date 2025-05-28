int trigPin = 3;
int echoPin = 5;
int in1 = 7;
int in2 = 8;
int e = 9;

long duration;
long distance;

void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(e, OUTPUT);
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    Serial.println(distance);

    if (distance < 10) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(e, 40);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(e, 50);
    }

    delay(1000);
}

/*
Cách lắp:
- Cảm biến siêu âm HC-SR04:
    + VCC -> 5V
    + GND -> GND
    + TRIG -> D3
    + ECHO -> D5
- Module L298N:
    + IN1 -> D7
    + IN2 -> D8
    + ENA -> D9 (PWM)
    + OUT1/OUT2 -> Motor DC
    + VCC -> nguồn motor, GND nối chung với Arduino
*/