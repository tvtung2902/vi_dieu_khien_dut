#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo;
ESP8266WebServer server(80);
// Có thể dùng các giá trị đã define nếu không nhớ được giá trị chân GPIO
// Ở đây mình dùng chân built in có sẵn trên ESP8266 luôn nha! 
// (Lưu ý: trạng thái LOW, HIGH bị đảo ở trong trường hợp dùng chân built in)
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
  WiFi.begin("TP-LINK_BF9132", "voduyvu234521#"); //SSID && Pasword
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
  float light = analogRead(A0);
  server.send(200, "text/plain", "Giá trị cảm biến ánh sáng: " + String(light));
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