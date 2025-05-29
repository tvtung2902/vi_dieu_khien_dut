#define LED_START 3
#define LED_END 7
#define BUTTON 2

volatile bool direction = true;
volatile bool interruptFlag = false;

void setup() {
    Serial.begin(9600);
    for (int i = LED_START; i <= LED_END; i++) {
        pinMode(i, OUTPUT);
    }
    
    attachInterrupt(digitalPinToInterrupt(BUTTON), changeDirection, RISING);
}

void loop() {
    if (direction) {
        for (int i = LED_START; i <= LED_END; i++) {
            if (interruptFlag) { 
                interruptFlag = false;
                break;
            }
            digitalWrite(i, HIGH);
            delay(400);
            digitalWrite(i, LOW);
            delay(400);
        }
    } else {
        for (int i = LED_END; i >= LED_START; i--) {
            if (interruptFlag) { 
                interruptFlag = false;
                break;
            }
            digitalWrite(i, HIGH);
            delay(400);
            digitalWrite(i, LOW);
            delay(400);
        }
    }
}

void changeDirection() {
    Serial.println("interrupt");
    direction = !direction;
    interruptFlag = true;
}
