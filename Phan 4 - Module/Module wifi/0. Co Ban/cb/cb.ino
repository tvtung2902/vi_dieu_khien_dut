const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP8266 LED Control</title>
</head>
<body>
  <h2>Điều khiển LED với ESP8266</h2>
  <button onclick="fetch('/on')">BẬT LED</button>
  <button onclick="fetch('/off')">TẮT LED</button>
  <p id="status">Trạng thái: --</p>

  <script>
    function updateStatus() {
      fetch('/status').then(response => response.text()).then(data => {
        document.getElementById('status').innerText = "Trạng thái: " + data;
      });
    }

    // Gọi status mỗi 1 giây
    setInterval(updateStatus, 1000);
    updateStatus();
  </script>
</body>
</html>
)=====";

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "PhongTro1_5G";              
const char* password = "mythien123";    

ESP8266WebServer server(80);            
const int ledPin = D1;              
bool ledState = false;          

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  ledState = true;
  server.send(200, "text/plain", "BẬT");
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  ledState = false;
  server.send(200, "text/plain", "TẮT");
}

void handleStatus() {
  server.send(200, "text/plain", ledState ? "BẬT" : "TẮT");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi kết nối thành công!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/status", handleStatus);

  server.begin();
  Serial.println("Server đã sẵn sàng");
}

void loop() {
  server.handleClient();
}

/*
Cách lắp:
- LED:
    + Chân dương -> D1
    + Chân âm -> Điện trở -> GND
*/

