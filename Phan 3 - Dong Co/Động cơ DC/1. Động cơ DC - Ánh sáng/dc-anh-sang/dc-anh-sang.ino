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
    if(analogread < 800) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(e, 100);
    } else {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(e, 100);
    }
    delay(1000);
}

/*
Cách lắp:
- Cảm biến ánh sáng:
    + VCC -> 5V
    + GND -> GND
    + OUT -> A0
- Module L298N:
    + IN1 -> D7
    + IN2 -> D8
    + ENA -> D9 (PWM)
    + OUT1/OUT2 -> Motor DC
    + VCC -> Pin, GND nối chung với Arduino
*/

//- Cảm biến ánh sáng:
// trời tối : giá trị cao
// trời sáng : giá trị thấp