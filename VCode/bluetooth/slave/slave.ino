#include <SoftwareSerial.h>

SoftwareSerial BT(4, 5);  // RX, TX nối đến HC-05


#include <Stepper.h>

#define BUOC 2048
Stepper stepper(BUOC, 8, 10, 9, 11);
void setup() {
  stepper.setSpeed(10);
  Serial.begin(9600);    
  BT.begin(9600);       
  Serial.println("Nhập lệnh AT và nhấn Enter để gửi đến HC-05.");
}
String currentState = "";
void loop() {
  if (BT.available()) {
    String response = BT.readStringUntil('\n');
    response.trim();
    Serial.print("Phản hồi HC-05: ");
    Serial.println(response);
    currentState = response;
  }
    if(currentState=="toi"){
      stepper.step((120.0 / 360.0) * BUOC);
    }
    else if(currentState=="sang"){
      stepper.step((-120.0 / 360.0) * BUOC);
    }
  delay(500);
}
