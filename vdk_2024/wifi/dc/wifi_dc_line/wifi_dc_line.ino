/*
- Những cảm biến đọc digital + analog:
- GND -> GND
- 5+/VCC -> Vin
 + A0 -> A0
 + D0 -> D1
- DC 
 + in1 -> D5
 + in2 -> D6
 + e -> D7

*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Thay đổi cảm biến ở đây
String SSID = "Cantin"; // Thay đổi tên wifi
String password = "123456789";

// Webserver cổng 80
ESP8266WebServer server(80);

// Cảm biến ánh sáng, cảm biến khí gas, VrX hoặc VrY
const int analogPin = A0;
// D0 -> D1
const int digitalPin = D1;

// Nhận giá trị độ từ web để điều khiển dc
int speedValue = 0;
int directionValue = 1;
int in1 = D5;
int in2 = D6;
int e = D7;

// Khai báo propertype
void setupDC();
void setupRoutes();
void setupPinSensor();
void handleReadAnalogDigitalSensor();
void handleSendValue();

void setup()
{
  Serial.begin(9600);
  delay(1000);
  WiFi.begin(SSID, password); // SSID && Pasword
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println(".");
  }
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  setupPinSensor();
  setupDC();
  setupRoutes();
}

void loop()
{
  server.handleClient();

  delay(200); // Đợi để hệ thống xử lý các yêu cầu khác

}

void setupDC()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(e, OUTPUT);
}

void setupPinSensor()
{
  pinMode(analogPin, INPUT);
  pinMode(digitalPin, INPUT);
  
}

void setupRoutes()
{
  server.on("/readSensor", handleReadAnalogDigitalSensor);
  server.on("/sendValue", handleSendValue);
  server.on("/", []()
            { server.send(200, "text/html", "<!DOCTYPE html>"
                                            "<html lang='en'>"
                                            ""
                                            "<head>"
                                            "    <meta charset='UTF-8'>"
                                            "    <title>Servo Control Panel</title>"
                                            "    <script>"
                                            "        function updateSensor() {"
                                            "            var xhttp = new XMLHttpRequest();"
                                            "            xhttp.onreadystatechange = function () {"
                                            "                if (this.readyState == 4 && this.status == 200) {"
                                            "                    document.getElementById('sensorValue').innerHTML = this.responseText;"
                                            "                }"
                                            "            };"
                                            "            xhttp.open('GET', '/readSensor', true);"
                                            "            xhttp.send();"
                                            "        }"
                                            "function sendValue() {"
                                            "   var speedInput = document.getElementById('speed');"
                                            "   var directionInputs = document.getElementsByName('direction');"
                                            "   var speed = speedInput.value;"
                                            "   var direction;"
                                            "   for (var i = 0; i < directionInputs.length; i++) {"
                                                    "if (directionInputs[i].checked) {"
                                                        "direction = directionInputs[i].value;"
                                                        "break;"
                                                    "}"
                                            "   }"
                                            "   var xhttp2 = new XMLHttpRequest();"
                                            "   xhttp2.open('POST', 'sendValue', true);"
                                            "   xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                                            "   xhttp2.send('speed=' + speed + '&direction=' + direction);"
                                            "}"
                                            "setInterval(updateSensor, 500);"
                                            "    </script>"
                                            "</head>"
                                            ""
                                            "<body>"
                                            "    <h1>DC Control Panel</h1>"
                                            "    <p>Sensor Value: <span id='sensorValue'>Waiting for data...</span></p>"
                                            "    <br>"
                                            "<label >Speed:</label><br>"
                                            "<input type='number' id='speed' name='speed' min='0' max='255' value='75'><br><br>"
                                            "<label for='direction'>Direction:</label><br>"
                                            "<input type='radio' id='forward' name='direction' value='1' checked>"
                                            "<label for='forward'>clockwise</label><br>"
                                            "<input type='radio' id='backward' name='direction' value='-1'>"
                                            "<label for='backward'>counter-clock-wise</label><br>"
                                            "<input type='radio' id='stop' name='direction' value='0'>"
                                            "<label for='stop'>stop</label><br><br>"
                                            
                                            "<input type='submit' value='Send' onclick = sendValue()>"
                                            "    <p id='result'></p>"
                                            "</body>"
                                            ""
                                            "</html>"); });

  server.begin();
}

void handleReadAnalogDigitalSensor()
{
  int analogValue = analogRead(analogPin);
  int digitalValue = digitalRead(digitalPin);  

  String textAnalog = "Line sensor (analog): " + String(analogValue);
  String textDigital = "Line sensor (digital): " + String(digitalValue ? "Black" : "White");

  String response = textAnalog + "\n" + textDigital;
  // String response = textDigital;
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleSendValue()
{
  if (server.hasArg("speed") && server.hasArg("direction"))
  {
    speedValue = server.arg("speed").toInt();
    directionValue = server.arg("direction").toInt();
    Serial.println("Received speed: " + String(speedValue) + ", direction: " + String(directionValue));

    if (speedValue > 0) {
        if(directionValue == 1) {
        //quay dc theo chieu kim dong ho
            Serial.println("quay thuan");
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            analogWrite(e, speedValue);
        }
        else if (directionValue == -1) {
        // quay dc nguoc chieu kim dong ho
            Serial.println("quay nguoc");
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            analogWrite(e, speedValue);
        } else {
        // dung lai
            Serial.println("dung lai");
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
        }
    }
  

    Serial.println("DC set to speed: " + String(speedValue));
    server.send(200, "text/plain", "DC set to speed: " + String(speedValue));
  }
  else
  {
    Serial.println("Request missing parameters");
    server.send(400, "text/plain", "Missing angle parameter");
  }
}
