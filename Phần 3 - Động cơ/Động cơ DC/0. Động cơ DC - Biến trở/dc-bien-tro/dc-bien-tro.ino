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

// cách lắp:
// Biến trở: giữa -> A0, 2 chân ngoài -> 5V và GND
// L298N: IN1 -> D7, IN2 -> D8, ENA -> D9, OUT1/OUT2 -> Motor
// Nguồn motor cấp vào chân VCC của L298N, GND nối chung Arduino