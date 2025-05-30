 /*
- Joystick:
 + SW -> D1
 + VrX || VrY -> A0
- DC 
 + in1 -> D5
 + in2 -> D6
 + e -> D7
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Stepper.h"

String SSID = "Cantin"; // Thay đổi tên wifi
String password = "123456789";


// Webserver cổng 80
ESP8266WebServer server(80);

// Cảm biến ánh sáng, cảm biến khí gas, VrX hoặc VrY
const int analogPin = A0;
// Chân sw của joystick
const int SW = D1;

// Nhận giá trị độ từ web để điều khiển dc
  int angleValue = 0;
  int directionValue = 1;
  int step = 0;
// ĐỘNG CƠ BƯỚC 
int in1 = D5;  // D5
int in2 = D6;  // D6
int in3 = D7;  // D7
int in4 = D8;  // D8 

const int STEPS = 2048;
Stepper stepper = Stepper(STEPS, in4, in2, in3, in1);

int degreeToSteps(int d, int steps = STEPS){
  if(d == 0) return 0;
  return steps/(360/d);
}


// Khai báo propertype
void setupStepper();
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

  setupStepper();
  setupPinSensor();
  setupRoutes();
}

void loop()
{
  server.handleClient();

  delay(200); // Đợi để hệ thống xử lý các yêu cầu khác
  if(step != 0){
    stepper.step(step);
  }
}

void setupStepper()
{
  stepper.setSpeed(15);
}

void setupPinSensor()
{
  pinMode(analogPin, INPUT);
  pinMode(SW, INPUT_PULLUP);
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
                                            "function sendValue() {"
                                            "   var angleInput = document.getElementById('angle');"
                                            "   var directionInputs = document.getElementsByName('direction');"
                                            "   var angle = angleInput.value;"
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
                                            "   xhttp2.send('angle=' + angle + '&direction=' + direction);"
                                            "}"
                                            "    </script>"
                                            "</head>"
                                            ""
                                            "<body>"
                                            "    <h1>DC Control Panel</h1>"
                                            "    <p>Sensor Value: <span id='sensorValue'>Waiting for data...</span></p>"
                                            "    <br>"
                                            "<label >angle:</label><br>"
                                            "<input type='number' id='angle' name='angle' min='0' max='255' value='75'><br><br>"
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
  String textAnalog = "";
  String textDigital = "";

  
  textAnalog = "Joystick (analog): " + String(analogValue);
  textDigital = "Joystick button (digital): " + String(digitalRead(SW) ? "Released" : "Pressed");
  
  String response = textAnalog + "\n" + textDigital;
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleSendValue()
{
  if (server.hasArg("angle") && server.hasArg("direction"))
  {
    angleValue = server.arg("angle").toInt();
    directionValue = server.arg("direction").toInt();
    Serial.println("Received angle: " + String(angleValue) + ", direction: " + String(directionValue));

    if (angleValue > 0) {
        if(directionValue == 1) {
        //quay dc theo chieu kim dong ho
            Serial.println("quay thuan");
            step = degreeToSteps(-angleValue);
        }
        else if (directionValue == -1) {
        // quay dc nguoc chieu kim dong ho
            Serial.println("quay nguoc");
            step = degreeToSteps(angleValue);
        } else {
        // dung lai
            Serial.println("dung lai");
            step = 0;
        }
    }
  

    Serial.println("DC set to angle: " + String(angleValue));
    server.send(200, "text/plain", "DC set to angle: " + String(angleValue));
  }
  else
  {
    Serial.println("Request missing parameters");
    server.send(400, "text/plain", "Missing angle parameter");
  }
}