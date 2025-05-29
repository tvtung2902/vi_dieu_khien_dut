int led = 13;
int ALARM = 4;
int LM35 = 0;
float tmpVal = 0;
float sinVal;
float toneVal;

void setup() {
  Serial.begin(9600);
  pinMode(ALARM, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int val = analogRead(LM35);
  tmpVal = (float) val * (5.0 / 1024) * 100;
  Serial.println(tmpVal);

  if(tmpVal > 20.0){
    for(int x = 0; x < 180; x++){
      sinVal = (sin(x * (3.14 / 180)));
      toneVal = 2000 + int(sinVal * 1000);
      tone(ALARM, toneVal);
      digitalWrite(led, HIGH);
      delay(2);
    }
  }
  else{
    noTone(ALARM);
    digitalWrite(led, LOW);
  }
  delay(200);
}