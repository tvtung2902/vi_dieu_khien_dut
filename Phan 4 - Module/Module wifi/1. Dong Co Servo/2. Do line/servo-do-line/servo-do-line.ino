#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "PhongTro1_5G";
const char* password = "mythien123";

ESP8266WebServer server(80);

const int linePin = D5;

const int SERVO_PIN = D1;
Servo myServo;

enum ServoState {
  MOVING_TO_TARGET,
  MOVING_TO_ZERO,
  IDLE
};

volatile int targetAngle = 90;
volatile int newTargetAngle = targetAngle;
volatile bool newAngleReceived = false;
volatile ServoState servoState = IDLE;
unsigned long lastMoveTime = 0;
const unsigned long moveInterval = 1000;

// Giao diện web
const char MAIN_page[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="utf-8">
  <title>Servo & Line</title>
  <style>
    body {
      background-color: #1a1a1a;
      color: #ffffff;
      font-family: 'Segoe UI', sans-serif;
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 30px;
    }

    h1 {
      color: #E76F51;
      margin-bottom: 30px;
    }

    label {
      font-size: 1.2em;
      margin-bottom: 5px;
    }

    input[type=number] {
      font-size: 1.5em;
      padding: 10px;
      width: 120px;
      text-align: center;
      border: 2px solid #E76F51;
      border-radius: 8px;
      background-color: #2c2c2c;
      color: #ffffff;
      outline: none;
      margin-bottom: 20px;
      transition: border 0.3s;
    }

    input[type=number]:focus {
      border-color: #F4A261;
    }

    #line {
      font-size: 1.4em;
      background-color: #2c2c2c;
      padding: 15px 25px;
      border-radius: 10px;
      border: 2px solid #E76F51;
      margin-top: 20px;
      box-shadow: 0 0 10px rgba(231, 111, 81, 0.5);
    }

    .footer {
      margin-top: 40px;
      font-size: 0.9em;
      color: #888;
    }
  </style>
</head>
<body>
  <h1>Điều Khiển Servo & Line</h1>

  <label for="angleInput">Nhập góc quay (0 - 180):</label><br>
  <input type="number" id="angleInput" value="90" min="0" max="180"><br>

  <div id="line">Đang đọc Line...</div>

  <div class="footer">ESP8266 Web Control | Màu cam gạch + đen</div>

  <script>
    function getAngle() {
      let val = parseInt(document.getElementById('angleInput').value);
      if (isNaN(val) || val < 0) val = 0;
      if (val > 180) val = 180;
      return val;
    }

    document.getElementById('angleInput').addEventListener('keydown', function(event) {
      if (event.key === 'Enter') {
        let angle = getAngle();
        fetch("/servo?angle=" + angle)
          .then(res => res.text())
          .then(data => alert(data));
      }
    });

    function fetchCB() {
      fetch("/line")
        .then(res => res.json())
        .then(data => {
          console.log(data);
          document.getElementById('line').innerText =
            "Line: " + (data.line == 0 ? "Trắng" : "Đen");
        });
    }

    setInterval(fetchCB, 1000);
  </script>
</body>
</html>
)=====";

void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

void handleLine() {
  int lineValue = digitalRead(linePin);
  
  String json = "{\"line\":" + String(lineValue) + "}";
  server.send(200, "application/json", json);
}

void handleServo() {
  if (!server.hasArg("angle")) {
    server.send(400, "text/plain", "Thiếu góc");
    return;
  }
  int angle = constrain(server.arg("angle").toInt(), 0, 180);
  newTargetAngle = angle;
  newAngleReceived = true;
  server.send(200, "text/plain", "Góc mới sẽ được áp dụng sau chu kỳ hiện tại: " + String(newTargetAngle));
}

void setup() {
  Serial.begin(115200);

  pinMode(linePin, INPUT);

  myServo.attach(SERVO_PIN, 544, 2400);
  myServo.write(0);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Kết nối WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nKết nối thành công!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/line", handleLine);
  server.on("/servo", handleServo);
  server.begin();
  servoState = MOVING_TO_TARGET;
  Serial.println("Web server đã sẵn sàng");
}

void updateServo() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastMoveTime >= moveInterval) {
    Serial.println("Xoay");
    lastMoveTime = currentTime;
    switch (servoState) {
      case MOVING_TO_TARGET:
        myServo.write(targetAngle);
        servoState = MOVING_TO_ZERO;
        break;
        
      case MOVING_TO_ZERO:
        myServo.write(0);
        servoState = MOVING_TO_TARGET;
        
        if (newAngleReceived) {
          targetAngle = newTargetAngle;
          newAngleReceived = false;
        }
        break;
        
      case IDLE:
        // Không làm gì
        break;
    }
  }
}

void loop() {
  server.handleClient();
  updateServo();
}

/*
Cách lắp:
- Servo:
  + Tín hiệu -> D1
  + VCC -> Vin
  + GND -> GND

- Cảm biến dò line:
  + VCC -> 3.3V
  + DO -> D5
  + GND -> GND
*/
