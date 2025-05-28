#define LINE 2

int in1 = 7;
int in2 = 8;
int e = 9;
int val = 0;

void setup() {
    pinMode(LINE, INPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(e, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    val = digitalRead(LINE);
    if (val == 1) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(e, 50);
    } else {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(e, 50);
    }
    Serial.println(val);
    delay(200);
}

/*
Cách lắp:
- Cảm biến dò line: OUT -> D2, VCC -> 5V, GND -> GND
- Module L298N:
    + IN1 -> D7
    + IN2 -> D8
    + ENA -> D9 (PWM)
    + OUT1/OUT2 -> Motor DC
    + VCC -> nguồn motor, GND nối chung với Arduino
*/


//* lí thuyết cảm biến dò line:
// Vạch đen hấp thụ ánh sáng → Ít phản xạ → A0 đọc đc giá trị cao -> nếu > ngưỡng điện áp tham chiếu -> value = 1 -> quay thuận
// Vạch trắng phản xạ ánh sáng → Nhiều phản xạ → A0 nhận giá trị thấp -> nếu < ngưỡng điện áp tham chiếu -> value = 0 -> quay ngược

// *lúc thực hành không dùng vật cản che ~ line đen => quay xuôi, ngược lại: nếu che => quay ngược