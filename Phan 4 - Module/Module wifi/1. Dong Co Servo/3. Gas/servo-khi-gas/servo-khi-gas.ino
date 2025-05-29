#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define SERVO_PIN D7
#define pinASensor A0

const char* ssid = "PhongTro1_5G";
const char* password = "mythien123";

ESP8266WebServer server(80);
Servo servo;

int sensor = 0;
int targetAngle = 90;
bool newAngleReceived = false;


const char MAIN_page[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>servo and sensor</title>
</head>
<body style="font-family:Arial;text-align:center">
  <h2>Điều Khiển Servo Và Hiển Thị Giá Trị Cảm Biến</h2>
  <p>Cảm biến Khí gas: <span id="sensor">đang load...</span> </p>
  <p>
    Góc Servo (0-180°): 
    <input type="number" id="angle" min="0" max="180" value="90">
    <button id="setAngleBtn" onclick="setAngle()">Cài góc</button>
  </p>
  <script>
    function updateSensor() {
      fetch('/getSensor')
        .then(res => res.text())
        .then(data => {
          document.getElementById('sensor').innerText = data;
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

    setInterval(updateSensor, 500);
    updateSensor();
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

void handleGetSensor() {
  sensor = analogRead(pinASensor);
  server.send(200, "text/plain", String(sensor));
}

void setup() {
  Serial.begin(115200);

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
  server.on("/getSensor", HTTP_GET, handleGetSensor);
  server.begin();
  Serial.println("Server đã sẵn sàng");
}

void loop() {
  server.handleClient();

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

- Cảm biến khí gas:
  + VCC -> 3.3V
  + AOUT -> A0
  + GND -> GND
*/
