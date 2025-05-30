#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);  // RX, TX nối đến HC-05

void setup() {
  Serial.begin(9600);     // Serial Monitor
  BT.begin(9600);        // Tốc độ AT mode HC-05 (thường là 38400)
  Serial.println("Nhập lệnh AT và nhấn Enter để gửi đến HC-05.");
}

void loop() {
  // Nếu có dữ liệu từ Serial Monitor (PC), gửi tới HC-05
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');  // Đọc 1 dòng lệnh
    cmd.trim();                                 // Bỏ khoảng trắng đầu/cuối nếu có

    Serial.print("Gửi đến HC-05: ");
    Serial.println(cmd);

    BT.println(cmd);  // Gửi lệnh tới HC-05
  }

  // Nếu có dữ liệu phản hồi từ HC-05, in ra Serial Monitor
  if (BT.available()) {
    String response = BT.readStringUntil('\n');
    Serial.print("Phản hồi HC-05: ");
    Serial.println(response);
  }
}
