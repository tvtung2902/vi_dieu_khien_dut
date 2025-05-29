#include "DHT.h" 
#define DHT11Pin 4
#define DHTType DHT11

int ALARM = 7;  
int toneVal; 
float sinVal; 

DHT HT(DHT11Pin, DHTType);
float humi;
float tempC;
float tempF;

void setup() {
    pinMode(ALARM, OUTPUT);
    Serial.begin(9600); 
    HT.begin();
    delay(1000);
}

void loop() {
    delay(1000);

    humi = HT.readHumidity();        // Đọc giá trị độ ẩm từ cảm biến
    tempC = HT.readTemperature();    // Đọc giá trị nhiệt độ theo độ C từ cảm biến
    tempF = HT.readTemperature(true); // Đọc giá trị nhiệt độ theo độ F từ cảm biến

    Serial.print("Độ ẩm: ");
    Serial.print(humi, 1);
    Serial.print("\t");
    Serial.print(tempC, 1);
    Serial.print(" °C ");
    Serial.print("\t");
    Serial.print(tempF, 1);
    Serial.println(" °F");

    if (humi > 72) {  
        for (int x = 0; x < 180; x++) {  
            sinVal = (sin(x * (3.1412 / 180)));  
            toneVal = 2000 + (int(sinVal * 1000));
            tone(ALARM, toneVal);
            delay(2);
        }
    } else {
        noTone(ALARM);
    }
}