#include <IRremote.h>
#include <Servo.h>

const int receiverPin = 3;
IRrecv irrecv(receiverPin);
decode_results results;

int in1 = 7;
int in2 = 8;
int e = 9;

int toc_do = 0;

  void
  setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(e, OUTPUT);

  Serial.begin(9600);

  irrecv.enableIRIn();
}

void translateIR() {
  switch (results.value) {
    // quay thuan
    case 0x10:
      toc_do = 100;
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(e, toc_do);
      break;

    // quay nguoc 
    case 0x11:
      toc_do = 255;
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(e, toc_do);
      break;
  }
}

void loop() {
  if (irrecv.decode(&results)) {

    translateIR();
    Serial.println(results.value, HEX);
    delay(200);
    irrecv.resume();
  }
}

/*
Cách lắp:
- IR:
    + (-): GND
    + pin giữa: 5V
    + pin còn lại: pin D3

- Module L298N:
    + IN1 -> D7
    + IN2 -> D8
    + ENA -> D9 (PWM)
    + OUT1/OUT2 -> Motor DC
    + VCC -> Pin(+), GND nối chung với Arduino
*/