#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

enum SensorCase
{
  JOYSTICK,
  LIGHT,
  SIEUAM,
  LINE,
  NHIETDO,
  GAS
};
// Thay đổi cảm biến ở đây
SensorCase sensor =  NHIETDO;
String SSID = "Cantin"; // Thay đổi tên wifi
String password = "123456789";

// Servo
Servo myservo;

// Webserver cổng 80
ESP8266WebServer server(80);

// Cảm biến ánh sáng, cảm biến khí gas, VrX hoặc VrY
const int analogPin = A0;
// Chân sw của joystick
const int SW = D3;
// D0 -> D1
const int digitalPin = D1;
// Cảm biến siêu âm
const int trigPin = D5;
const int echoPin = D6;

// Nhiệt độ - độ ẩm
#define DHT11Pin D2 // Chân D2
#define DHTType DHT11
DHT dht(DHT11Pin, DHTType);
float humidity;
float tempC;

// Khai báo propertype
void setupServo();
void setupRoutes();
void setupPinSensor();
void handleReadAnalogDigitalSensor();
// Nhận giá trị độ từ web để điều khiển servo
int receivedValue = 0;
void handleSendValue();

void setup()
{
  Serial.begin(9600); 
  delay(1000);
  WiFi.begin(SSID, password); //SSID && Pasword
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println(".");
  }
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  setupServo();
  setupPinSensor();
  setupRoutes();
  myservo.write(0);
}

void loop()
{
  server.handleClient();
  
  delay(200); // Đợi để hệ thống xử lý các yêu cầu khác
  if (receivedValue > 0)
  {
    // quay servo thuận theo góc INPUT
    myservo.write(receivedValue);
    delay(500);
    // chỉnh servo về vị trí 0 độ
    myservo.write(0);
    delay(500);
  }
}

void setupServo()
{
  myservo.attach(D4, 500, 2400);
}

void setupPinSensor()
{
  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);
  pinMode(SW, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin();
}

void setupRoutes() {
  server.on("/readSensor", handleReadAnalogDigitalSensor);
  server.on("/sendValue", handleSendValue);
  server.on("/", []()
            { server.send(200, "text/html",
                          "<!DOCTYPE html>"
                          "<html lang='en'>"
                          "<head>"
                          "<meta charset='UTF-8'>"
                          "<title>Servo Control Panel</title>"
                          "<script>"
                                            "     window.onload = function() {"
                                            "       updateSensor();"
                                            "     };"
                                            "        function updateSensor() {"
                                            "            var xhttp = new XMLHttpRequest();"
                                            "            xhttp.onreadystatechange = function () {"
                                            "                if (this.readyState == 4 && this.status == 200) {"
                                            "                    document.getElementById('sensorValue').innerHTML = this.responseText;"
                                            "                    setTimeout(updateSensor, 500);"
                                            "                }"
                                            "            };"
                                            "            xhttp.open('GET', '/readSensor', true);"
                                            "            xhttp.send();"
                                            "        }"
                          "function sendValue(){"
                          "console.log('Sending value');"
                          "var angleInput = document.getElementById('servoAngle');"
                          "var xhttp2 =  new XMLHttpRequest();"
                          "var angle = angleInput.value;"
                          "xhttp2.open('POST', 'sendValue', true);"
                          "xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                          "xhttp2.send('angle=' + angle);"
                          "}"
                          "</script>"
                          "</head>"
                          "<body>"
                          "<h1>Servo Control Panel</h1>"
                          "<p>Sensor Value: <span id='sensorValue'>Waiting for data...</span></p>"
                          "<input type='number' id='servoAngle' min='0' max='180' step='1' value='90'>"
                          "<button onclick='sendValue()'>Set Servo Angle</button>"
                          "</body>"
                          "</html>"); });

  server.begin();
}

void handleReadAnalogDigitalSensor()
{
  int analogValue = analogRead(analogPin);
  int digitalValue = digitalRead(digitalPin);
  String textAnalog = "";
  String textDigital = "";

  switch (sensor)
  {
  case LIGHT:
    textAnalog = "Light sensor (analog): " + String(analogValue);
    textDigital = "Light sensor (digital): " + String(digitalValue ? "Dark" : "Bright");
    break;
  case GAS:
    textAnalog = "Gas sensor (analog): " + String(analogValue);
    textDigital = "Gas sensor (digital): " + String(digitalValue ? "No gas" : "Gas detected");
    break;
  case JOYSTICK:
    textAnalog = "Joystick (analog): " + String(analogValue);
    textDigital = "Joystick button (digital): " + String(digitalRead(SW) ? "Released" : "Pressed");
    break;
  case SIEUAM:
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    textAnalog = "Ultrasonic sensor: " + String(distance) + " cm";
    break;
  case NHIETDO:
    humidity = dht.readHumidity();
    tempC = dht.readTemperature();
    textAnalog = "Temperature: " + String(tempC) + "°C, Humidity: " + String(humidity) + "%";
    break;
  case LINE:
    textAnalog = "Line sensor (analog): " + String(analogValue);
    textDigital = "Line sensor (digital): " + String(digitalValue ? "Black" : "White");
    break;
  default:
    textAnalog = "Unidentified sensor (analog): " + String(analogValue);
    textDigital = "Unidentified sensor (digital): " + String(digitalValue ? "Detected" : "Not detected");
    break;
  }

  String response = textAnalog + "\n" + textDigital;
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleSendValue()
{
  if (server.hasArg("angle"))
  {
    receivedValue = server.arg("angle").toInt();
    Serial.println("Received angle: " + String(receivedValue));
    myservo.write(receivedValue);
    Serial.println("Servo set to angle: " + String(receivedValue));
    server.send(200, "text/plain", "Servo set to angle: " + String(receivedValue));
  }
  else
  {
    Serial.println("Request missing 'angle' parameter");
    server.send(400, "text/plain", "Missing angle parameter");
  }
}
