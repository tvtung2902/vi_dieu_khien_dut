#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "TP-LINK";
const char* password = "28032004";

ESP8266WebServer server(80);

// Pin động cơ DC
const int IN1 = D1;
const int IN2 = D2;
const int ENA = D3;

// Pin cảm biến ánh sáng
const int LDR_PIN = A0;

// Giao diện HTML
const char MAIN_page[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <title>Điều khiển Động cơ & Cảm biến ánh sáng</title>
  <style>
    * {
      box-sizing: border-box;
      margin: 0; padding: 0;
    }
    body {
      font-family: 'Segoe UI', sans-serif;
      background: linear-gradient(135deg, #f8f9fa, #e0eafc);
      color: #333;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: start;
      min-height: 100vh;
      padding: 40px 20px;
    }
    h1 {
      font-size: 2em;
      margin-bottom: 30px;
      color: #222;
    }
    label {
      font-size: 1.1em;
      margin-bottom: 10px;
    }
    input[type=number] {
      font-size: 1.2em;
      padding: 10px;
      width: 180px;
      border: 1px solid #ccc;
      border-radius: 10px;
      margin-bottom: 20px;
      outline: none;
    }
    .buttons {
      display: flex;
      gap: 15px;
      margin-bottom: 30px;
      flex-wrap: wrap;
      justify-content: center;
    }
    button {
      font-size: 1.1em;
      padding: 10px 25px;
      background-color: #007bff;
      border: none;
      border-radius: 8px;
      color: white;
      cursor: pointer;
      transition: background-color 0.3s ease;
    }
    button:hover {
      background-color: #0056b3;
    }
    #ldrValue {
      margin-top: 20px;
      font-size: 1.5em;
      color: #444;
      background: #fff;
      padding: 15px 25px;
      border-radius: 12px;
      box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    }
  </style>
</head>
<body>
  <h1>Điều khiển Động cơ & Cảm biến ánh sáng</h1>

  <label for="speedInput">Tốc độ (0 - 255):</label><br>
  <input type="number" id="speedInput" value="255" min="0" max="255" placeholder="Nhập tốc độ"><br>

  <div class="buttons">
    <button onclick="sendCommand('forward')">Xoay thuận</button>
    <button onclick="sendCommand('backward')">Xoay ngược</button>
    <button onclick="sendCommand('stop')">Dừng</button>
  </div>

  <div id="ldrValue">Đang đọc ánh sáng...</div>

  <script>
    function getSpeed() {
      let val = parseInt(document.getElementById('speedInput').value);
      if (isNaN(val) || val < 0) val = 0;
      if (val > 255) val = 255;
      return val;
    }

    function sendCommand(cmd) {
      let speed = getSpeed();
      fetch("/motor?cmd=" + cmd + "&speed=" + speed)
        .then(res => res.text());
    }

    function fetchLDR() {
      fetch("/ldr")
        .then(res => res.text())
        .then(val => {
          document.getElementById('ldrValue').innerText = "Ánh sáng: " + val;
        });
    }

    document.getElementById('speedInput').addEventListener('keydown', function(event) {
      if (event.key === 'Enter') {
        let speed = getSpeed();
        fetch("/motor?cmd=updateSpeed&speed=" + speed)
          .then(res => res.text());
      }
    });

    setInterval(fetchLDR, 1000);
    fetchLDR();
  </script>
</body>
</html>
)=====";

// Xử lý trang chính
void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

// Xử lý cảm biến ánh sáng
void handleLDR() {
  int value = analogRead(LDR_PIN);
  server.send(200, "text/plain", String(value));
}

// Xử lý động cơ DC
void handleMotor() {
  if (server.hasArg("cmd")) {
    String cmd = server.arg("cmd");
    int speed = server.hasArg("speed") ? server.arg("speed").toInt() : 1023;
    speed = constrain(speed, 0, 1023);  // Giới hạn giá trị hợp lệ

    if (cmd == "forward") {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, speed);
      server.send(200, "text/plain", "Đang xoay thuận với tốc độ " + String(speed));
    } else if (cmd == "backward") {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, speed);
      server.send(200, "text/plain", "Đang xoay ngược với tốc độ " + String(speed));
    } else if (cmd == "stop") {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
      server.send(200, "text/plain", "Đã dừng");
    } else if (cmd == "updateSpeed") {
      analogWrite(ENA, speed);
      server.send(200, "text/plain", "Đã cập nhật tốc độ: " + String(speed));
    } else {
      server.send(400, "text/plain", "Lệnh không hợp lệ");
    }
  } else {
    server.send(400, "text/plain", "Thiếu tham số cmd");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Kết nối WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nĐã kết nối WiFi!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/ldr", handleLDR);
  server.on("/motor", handleMotor);

  server.begin();
  Serial.println("Web server đã khởi động");
}

void loop() {
  server.handleClient();
}
