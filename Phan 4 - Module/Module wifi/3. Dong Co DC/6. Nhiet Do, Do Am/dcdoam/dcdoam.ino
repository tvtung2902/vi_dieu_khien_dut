#include "DHT.h"

#define DHT11Pin 4
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType);

float humi;
float tempC;
float tempF;

int analog = A0;
int in1 = 7;
int in2 = 8;
int e = 9;

void setup() {
    Serial.begin(9600);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(e, OUTPUT);
    HT.begin();
    delay(1000);
}

void loop() {
    humi = HT.readHumidity();
    tempC = HT.readTemperature();
    tempF = HT.readTemperature(true);
    
    if(humi > 75){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(e, 70);
    } else {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(e, 70);
    }

    Serial.print("Độ ẩm: ");
    Serial.print(humi, 1);
    Serial.print("\t");
    Serial.print(tempC, 1);
    Serial.print(" °C ");
    Serial.print(tempF, 1);
    Serial.println(" °F");
    delay(1000);
}

/*
Cách lắp:
- Cảm biến DHT11: 
    + VCC -> 5V
    + GND -> GND
    + DATA -> D4
- Module L298N:
    + IN1 -> D7
    + IN2 -> D8
    + ENA -> D9 (PWM)
    + OUT1/OUT2 -> Motor DC
    + VCC -> Pin(+), GND nối chung với Arduino
*/