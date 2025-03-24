#define LED_START 3
#define LED_END 7
#define BUTTON 2

volatile bool reverse = false;
volatile bool interruptFlag = false;

unsigned long previousMillis = 0;
const int interval = 400;

void setup() {
    Serial.begin(9600);
    
    for (int i = LED_START; i <= LED_END; i++) {
        pinMode(i, OUTPUT);
    }

    pinMode(BUTTON, INPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON), changeDirection, RISING);
}

void loop() {
    unsigned long currentMillis = millis();

    if (interruptFlag) {
        interruptFlag = false;
        reverse = !reverse;
    }

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (reverse) {
            for (int i = LED_END; i >= LED_START; i--) {
                if (interruptFlag) {
                    interruptFlag = false;
                    break;
                }
                digitalWrite(i, HIGH);
                unsigned long ledMillis = millis();
                while (millis() - ledMillis < interval) {
                    if (interruptFlag) {
                        interruptFlag = false;
                        break;
                    }
                }
                digitalWrite(i, LOW);
            }
        } else {
            for (int i = LED_START; i <= LED_END; i++) {
                if (interruptFlag) {
                    interruptFlag = false;
                    break;
                }
                digitalWrite(i, HIGH);
                unsigned long ledMillis = millis();
                while (millis() - ledMillis < interval) {
                    if (interruptFlag) {
                        interruptFlag = false;
                        break;
                    }
                }
                digitalWrite(i, LOW);
            }
        }
    }
}

void changeDirection() {
    Serial.println("interrupt");
    interruptFlag = true;
}
