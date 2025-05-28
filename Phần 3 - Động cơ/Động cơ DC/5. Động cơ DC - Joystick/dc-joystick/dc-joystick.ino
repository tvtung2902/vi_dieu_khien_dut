int joyStickX = A0;
int joyStickZ = 2;

int in1 = 7;
int in2 = 8;
int ena = 9;

void setup() {
    Serial.begin(9600);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(joyStickZ, INPUT_PULLUP);
}

void loop() {
    int xValue = analogRead(joyStickX);
    int zState = digitalRead(joyStickZ);

    Serial.print("X: ");
    Serial.print(xValue);
    Serial.print(" | Z: ");
    Serial.println(zState == LOW ? "Pressed" : "Released");

    if (zState == LOW) {
        Serial.println("Z button pressed -> Motor STOP");
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(ena, 0);
    } else {
        if (xValue < 400) {
            Serial.println("Moving LEFT");
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(ena, 40);
        } else if (xValue > 600) {
            Serial.println("Moving RIGHT");
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            analogWrite(ena, 50);
        } else {
            Serial.println("Joystick centered -> Motor STOP");
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            analogWrite(ena, 0);
        }
    }
    delay(200);
}

/*
Cách lắp mạch:

- Joystick:
    + VRx (trục X)  -> A0
    + SW (nút Z)    -> D2
    + VCC           -> 5V
    + GND           -> GND

- Module L298N:
    + IN1           -> D7
    + IN2           -> D8
    + ENA           -> D9 (PWM)
    + OUT1/OUT2     -> Motor DC
    + VCC (L298N)   -> nguồn motor (ví dụ 12V)
    + GND           -> GND chung với Arduino
*/
