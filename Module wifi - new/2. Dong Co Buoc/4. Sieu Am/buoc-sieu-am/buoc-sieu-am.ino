#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "TP-LINK";
const char* password = "28032004";

ESP8266WebServer server(80);

int trigPin = D0;
int echoPin = D1;

const int in1 = D5;
const int in2 = D6;
const int in3 = D7;
const int in4 = D8;
const int stepsPerRevolution = 4096;
int currentAngle = 0;
int stepIndex = 0;
bool directionCW = true;
bool runMotor = false;
int anglePerRun = 0;

unsigned long lastStepTime = 0;
unsigned long stepInterval = 2;

const int stepSequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="vi">
<head>
  <meta charset="UTF-8">
  <title>Điều khiển động cơ & Cảm biến</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      padding: 20px;
      background: #f0f0f0;
    }
    .card {
      background: white;
      border-radius: 8px;
      box-shadow: 0 0 10px gray;
      padding: 20px;
      margin: auto;
      max-width: 400px;
    }
    input[type="number"] {
      width: 60px;
    }
  </style>
</head>
<body>
  <div class="card">
    <h2>Giá trị cảm biến siêu âm (cm)</h2>
    <p><strong id="sensor">?</strong></p>
    <hr>
    <h2>Điều khiển động cơ</h2>
    Góc: <input type="number" id="angleInput" min="10" max="360" required> độ<br><br>
    Chiều quay:
    <label><input type="radio" name="dir" value="cw" checked> Phải (CW)</label>
    <label><input type="radio" name="dir" value="ccw"> Trái (CCW)</label><br><br>
    <button id="rotateBtn" onclick="sendAngle()">Bắt đầu quay</button>
  </div>

  <script>
    function updateSensor() {
      fetch('/sensor')
        .then(res => res.json())
        .then(data => {
          document.getElementById('sensor').innerText = data;
        });
    }
    setInterval(updateSensor, 800);

    function sendAngle() {
      const angle = document.getElementById('angleInput').value;
      const dir = document.querySelector('input[name="dir"]:checked').value;
      const btn = document.getElementById('rotateBtn');

      if (!angle) {
        alert("Vui lòng nhập góc hợp lệ");
        return;
      }

      btn.disabled = true;
      btn.innerText = "loading...";

      fetch(`/set?angle=${angle}&dir=${dir}`)
        .then(res => {
          if (!res.ok) throw new Error("Lỗi khi gửi yêu cầu");
        })
        .catch(err => {
          console.error("Lỗi mạng:", err);
        })
        .finally(() => {
          btn.disabled = false;
          btn.innerText = "Bắt đầu quay";
        });
    }
  </script>
</body>
</html>
)rawliteral";

void setupMotorPins() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void stepMotor(int step) {
  digitalWrite(in1, stepSequence[step][0]);
  digitalWrite(in2, stepSequence[step][1]);
  digitalWrite(in3, stepSequence[step][2]);
  digitalWrite(in4, stepSequence[step][3]);
}

void rotateSteps(int steps, bool dirCW) {
  for (int i = 0; i < steps; i++) {
    stepMotor(stepIndex);
    stepIndex = dirCW ? (stepIndex + 1) % 8 : (stepIndex + 7) % 8;
    delay(stepInterval);
  }
}

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void handleSensor() {
    // xóa trạng thái củ của trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // gửi xung tín hiệu từ trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // đọc thời gian phản hồi từ echoPin(thời gian sóng âm truyền đi và quay lại)
  long duration = pulseIn(echoPin, HIGH);

  // tính khoảng cách theo công thức : Distance = (time * speed of sound) / 2
  // 0.034 (m/micro s)
  long distance = duration * 0.034 / 2;
      

  server.send(200, "text/plain", String(distance));
}

void handleSetAngle() {
  if (server.hasArg("angle")) {
    int angle = server.arg("angle").toInt();
    directionCW = (server.arg("dir") == "cw");
    anglePerRun = angle;
    runMotor = true;
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Thiếu tham số");
  }
}


void setup() {
  Serial.begin(115200);
  setupMotorPins();

  WiFi.begin(ssid, password);
  Serial.print("Kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nĐã kết nối WiFi. IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/sensor", handleSensor);
  server.on("/set", handleSetAngle);
  server.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Web server sẵn sàng");
}

void loop() {
  server.handleClient();

  static unsigned long lastMove = 0;
  if (runMotor && millis() - lastMove > 1000) {
    int steps = anglePerRun * stepsPerRevolution / 360;
    rotateSteps(steps, directionCW);
    lastMove = millis();
  }
}

/*
Cách lắp:
- Cảm biến siêu âm:
    + Trig -> D0
    + Echo -> D1
    + VCC -> 3.3V
    + GND -> GND

- ULN2003 + động cơ bước 28BYJ-48:
    + IN1 -> D5
    + IN2 -> D6
    + IN3 -> D7
    + IN4 -> D8
    + VCC -> +
    + GND -> GND
*/

