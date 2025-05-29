 int ledStart = 2;
int ledEnd = 11;

void setup() {
  for(int led = ledStart; led <= ledEnd; led++){
    pinMode(led, OUTPUT);
  }
}

bool check = 0;

void loop() {
  for(int led = ledStart; led <= ledEnd / 2 + 1; led++){
    digitalWrite(led, HIGH);
    digitalWrite(ledEnd - led + ledStart, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    digitalWrite(ledEnd - led + ledStart, LOW);
    delay(100);
  }

  for(int led = ledEnd / 2 + 1; led >= ledStart; led--){
    if((check == 1 && led == ledEnd / 2 + 1 ) || (check == 1 && led == ledStart)) continue;
    digitalWrite(led, HIGH);
    digitalWrite(ledEnd - led + ledStart, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    digitalWrite(ledEnd - led + ledStart, LOW);
    delay(100);
  }
  check = 1;
}

