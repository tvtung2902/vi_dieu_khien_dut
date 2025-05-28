int joyStickX = A0;
int buttonPin = 2;

int in1 = 7;
int in2 = 8;
int e = 9;

void setup() {
    Serial.begin(9600);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
    int xValue = analogRead(joyStickX);
    int buttonState = digitalRead(buttonPin);

    Serial.print("Joystick X: ");
    Serial.print(xValue);
    Serial.print(" | Button: ");
    Serial.println(buttonState == LOW ? "Pressed" : "Released");

    if (buttonState == LOW) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(e, 0);
    } else {
        if (xValue < 400) {
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(e, 40);
        } else if (xValue > 600) {
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            analogWrite(e, 50);
        } else {
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            analogWrite(e, 0);
        }
    }
    delay(200);
}

/*
Cách lắp:
- Joystick:
    + VRx -> A0
    + VCC -> 5V
    + GND -> GND
- Nút nhấn:
    + Chân digital 2 (buttonPin)
    + Chân kia nối GND
- Module L298N:
    + IN1 -> D7
    + IN2 -> D8
    + ENA -> D9 (PWM)
    + OUT1/OUT2 -> Motor DC
    + VCC -> nguồn motor (ví dụ 12V), GND chung với Arduino
*/
