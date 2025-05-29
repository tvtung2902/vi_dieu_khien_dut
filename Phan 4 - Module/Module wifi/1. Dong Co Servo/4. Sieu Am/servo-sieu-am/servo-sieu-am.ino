#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define TRIG_PIN D5
#define ECHO_PIN D6
#define SERVO_PIN D7

const char* ssid = "PhongTro1_5G";
const char* password = "mythien123";

ESP8266WebServer server(80);
Servo servo;

float distance = 0;
// góc servo di chuyển đến
int targetAngle = 90;
// flag báo có giá trị góc mới nhận hay không
bool newAngleReceived = false;


const char MAIN_page[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Điều khiển Servo ESP8266</title>
</head>
<body style="font-family:Arial;text-align:center">
  <h2>Điều khiển Servo ESP8266</h2>
  <p>Khoảng cách: <span id="distance">0</span> cm</p>
  <p>
    Góc Servo (0-180°): 
    <input type="number" id="angle" min="0" max="180" value="90">
    <button id="setAngleBtn" onclick="setAngle()">Cài góc</button>
  </p>
  <script>
    function updateDistance() {
      fetch('/getDistance')
        .then(res => res.text())
        .then(data => {
          document.getElementById('distance').innerText = parseFloat(data).toFixed(2);
        });
    }

    function setAngle() {
      const angleInput = document.getElementById('angle');
      const angleBtn = document.getElementById('setAngleBtn');
      const angle = angleInput.value;

      if (angle >= 0 && angle <= 180) {
        angleBtn.disabled = true; // Disable button
        fetch('/setAngle', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body: 'angle=' + angle
        })
        .then(res => res.text())
        .then(data => console.log(data))
        .finally(() => {
          angleBtn.disabled = false; // Enable again
        });
      } else {
        alert("Vui lòng nhập góc từ 0 đến 180");
      }
    }

    setInterval(updateDistance, 500);
    updateDistance();
  </script>
</body>
</html>
)=====";



void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void handleSetAngle() {
  if (server.hasArg("angle")) {
    targetAngle = server.arg("angle").toInt();
    newAngleReceived = true;
    server.send(200, "text/plain", "Đã cài góc " + String(targetAngle) + "°");
  } else {
    server.send(400, "text/plain", "Góc không hợp lệ");
  }
}

void handleGetDistance() {
  server.send(200, "text/plain", String(distance));
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN);
  servo.write(targetAngle * 2);

  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi đã kết nối! IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/setAngle", HTTP_POST, handleSetAngle);
  server.on("/getDistance", HTTP_GET, handleGetDistance);
  server.begin();
  Serial.println("Server đã sẵn sàng");
}

void loop() {
  server.handleClient();

  // Đo khoảng cách
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Cập nhật servo nếu có góc mới
  static unsigned long lastMove = 0;
  if (millis() - lastMove > 1000 && newAngleReceived) {
    Serial.print("targetAngle from client: ");
    Serial.println(targetAngle);
    servo.write(targetAngle * 2);
    newAngleReceived = false;
    lastMove = millis();
  }
}


/*
Cách lắp:
- Servo:
  + Tín hiệu -> D7
  + VCC -> Vin
  + GND -> GND

- Cảm biến siêu âm HC-SR04:
  + Trig -> D5
  + Echo -> D6
  + VCC -> 3.3V
  + GND -> GND
*/