#include<OneWire.h>
#include<DallasTemperature.h>

int DS18B20 = 2;
int Buzzer = 13;

OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");  
  Serial.print(tempC);
  Serial.print(" \xC2\xB0");
  Serial.println("C");

  if(tempC > 20){
    tone(Buzzer, 2000);
  }
  else {
    noTone(Buzzer);
  }
  delay(500);
}
