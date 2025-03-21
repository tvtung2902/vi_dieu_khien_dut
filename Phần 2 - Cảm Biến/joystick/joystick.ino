int joyStickX = 0;
int joyStickY = 1;
int joyStickZ = 3;

int ledX = 7;
int ledY = 8;
int ledT = 9;
int ledZ = 10;

void setup() {
  Serial.begin(9600);
  pinMode(joyStickZ, INPUT_PULLUP);
  pinMode(ledX, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledZ, OUTPUT);
  pinMode(ledT, OUTPUT);

}

void loop() {
  int x, y, z;
  x = analogRead(joyStickX);
  y = analogRead(joyStickY);
  z = digitalRead(joyStickZ);
  if (x < 400){
    digitalWrite(ledX, HIGH);
  }
  if (x > 600){
    digitalWrite(ledY, HIGH);
  }
  if (y < 400){
    digitalWrite(ledZ, HIGH);
  }
  if (y > 600){
    digitalWrite(ledT, HIGH);
  }
  if(z == 0){
    digitalWrite(ledX, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledZ, LOW);
    digitalWrite(ledT, LOW);
  }
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.println(z);
  delay(100);
}
