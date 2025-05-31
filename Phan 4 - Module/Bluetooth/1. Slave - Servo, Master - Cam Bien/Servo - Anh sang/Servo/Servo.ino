#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(4, 5); 
Servo myservo;

String currentState = "";

void setup() {
  myservo.attach(9);   
  myservo.write(0); 
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Sẵn sàng nhận lệnh từ HC-05.");
}

void loop() {
  if (BT.available()) {
    String response = BT.readStringUntil('\n');
    response.trim();
    Serial.print("Phản hồi HC-05: ");
    Serial.println(response);
    currentState = response;
  }

  if (currentState == "toi") {
    Serial.println("Trời tối → quay servo 180 độ rồi về 0 độ");
    myservo.write(180);
    delay(700);
    myservo.write(0);
    delay(700);
  }
  else if (currentState == "sang") {
    Serial.println("Trời sáng → quay servo 30 độ rồi về 0 độ");
    myservo.write(30);
    delay(200);
    myservo.write(0);
    delay(200);
  }
}

/*
Cách lắp:
- Module HC-05:
    + TX của HC-05 → chân 4
    + RX của HC-05 ← chân 5
    + VCC nối 5V
    + GND nối GND
- Servo:
    + Tín hiệu → chân D9
    + VCC → 5V
    + GND → GND
*/
