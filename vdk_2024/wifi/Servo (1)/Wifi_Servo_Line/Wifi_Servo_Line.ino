#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo;
ESP8266WebServer server(80);
// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 
// Cảm biến dò Line 
int SensorLine = D0; // D0 nối với chân số D3 của wifi (1 là đen , 0 là trắng) , VCC nối 3V3 của wifi, GND nối GND của wifi
// int SensorLine = A0; // A0 Chân đọc giá trị của cảm biến dò line (1024 là đen , 0 là trắng)
// Đổi chân ở đây thì đổi ở dưới handleReadSerial nữa           
// + A0 
//     + Đen là 1 
//     + Trắng là 0 
// + D0 
//     + Đen là 1024 
//     + Trắng là 0 
const int LED = LED_BUILTIN; 

int led_status = 0;

String  WebPage = {
  "<!DOCTYPE html><html><head>"
    "<title>Web realtime</title>"
    "<meta charset=\"UTF-8\">"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<style>"
    "html {font-family: Helvetica;display: inline-block;margin: 0px auto;text-align: center;}"
    ".button {background-color: #4CAF50;border: none;color: white;padding: 16px 40px;text-decoration: none;font-size: 30px;margin: 2px;cursor: pointer;}"
    ".button2 {background-color: #555555;}"
    ".btn{background-color: #4CAF50;border: none;color: white;padding: 8px 20px;text-decoration: none;font-size: 16px;margin: 2px;cursor: pointer;}"
    ".degrees-input {width: 60px;height: 30px;font-size: 20px;text-align: center;}"
    "</style>"
    "</head><body>"
    "<h1><p id=\"serialMonitor\"> None </p><h1><br>"
    "<div id=\"motor_controller\">"
    "    <p>Điều khiển động cơ Servo</p>"
    "    Degrees: <input class=\"degrees-input\" type=\"text\" id=\"degrees\" value=\"\">"
    "    <a href=\"#\" class=\"btn\" onclick=\"sendValue()\">Send</a>"
    "</div>"
    "</body><script>"
    "window.onload = function() {"
       "readSerial();"
    "};"
    "function readSerial() {"
    "var serialMonitor = document.getElementById('serialMonitor');"
    "var xhttp = new XMLHttpRequest();"
    "xhttp.onreadystatechange = function() {"
    "if (this.readyState == 4 && this.status == 200) {"
    "serialMonitor.innerHTML = this.responseText;"
    "setTimeout(readSerial, 500);"
    "}"
    "};"
    "xhttp.open('GET', 'readSerial', true);"
    "xhttp.send();"
    "}"
    "function sendValue() { var degreesInput = document.getElementById('degrees'); var xhttp2 = new XMLHttpRequest(); var degrees = degreesInput.value; xhttp2.open('POST', 'sendValue', true); xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded'); xhttp2.send('degrees=' + degrees); }"
    "</script></html>"
};

void setup() {
  myservo.attach(D1, 500,2400);
  Serial.begin(9600);

  // Thiết lập LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // Thiết lập trạng thái mức điện cao cho chân tín hiệu LED

  // ===========THIẾT LẬP KẾT NỐI WIFI====================================================
  delay(1000);
  WiFi.begin("HUYNH ANH", "123456799"); //SSID && Pasword
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println(".");
  }
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  // ===============================================================================
  // Giao diện trang chủ
  server.on("/", [] {server.send(200,"text/html", WebPage);});
  setupRoutes();
  server.begin();  // Bắt đầu web server
}

void handleReadSerial() {
  // Gửi giá trị cảm biến về client
  float line = digitalRead(D0);
  // float line = analogRead(A0);
  server.send(200, "text/plain", "Giá trị cảm biến dò line: " + String(line));
}

int receivedValue = 0;
void handleSendValue() {
  if (server.hasArg("degrees")) {
    receivedValue = server.arg("degrees").toInt();
  }
}

void setupRoutes() {
  server.on("/readSerial", handleReadSerial);
  server.on("/sendValue", handleSendValue);
}


void loop() {
  // Xử lý các yêu cầu từ client
  server.handleClient();
  if (receivedValue > 0) {
    //quay servo thuận theo góc INPUT
      Serial.print(receivedValue);
      // 5/3.3
      myservo.write(receivedValue);
      delay(500); 
      myservo.write(0);
      delay(500); 
  }
}