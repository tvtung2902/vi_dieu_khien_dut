#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo;
ESP8266WebServer server(80);
// Đối với wifi khi setup cổng thì cần thêm A với D ví dụ A0, D4 
// Cảm biến dò Line 
// int SensorLine = D0; // D0 nối với chân số D3 của wifi (1 là đen , 0 là trắng) , VCC nối 3V3 của wifi, GND nối GND của wifi
// int SensorLine = A0; // A0 Chân đọc giá trị của cảm biến dò line (1024 là đen , 0 là trắng)

// Nhiệt độ - độ ẩm 
#include "DHT.h"
const int DHTPIN = D4;      
const int DHTTYPE = DHT11; 
DHT dht(DHTPIN, DHTTYPE); 
float humi; 
float tempC; 
float tempF; 
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
  WiFi.begin("TUHOC_KHU_A", ""); //SSID && Pasword
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println(".");
  }
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  // ===============================================================================
  // Giao diện trang chủ
  dht.begin();
  server.on("/", [] {server.send(200,"text/html", WebPage);});
  setupRoutes();
  server.begin();  // Bắt đầu web server
}

void handleReadSerial() {
  // Gửi giá trị cảm biến về client
  humi = dht.readHumidity(); 
  tempC = dht.readTemperature(); 
  tempF = dht.readTemperature(true); 
  server.send(200, "text/plain", "Giá trị cảm biến nhiệt độ độ ẩm: Humidity = " + String(humi, 0) + "%" + " , Temperature = " + String(tempC, 1) + "oC ~ " + String(tempF, 1) + "oF" + "\n");
  
  Serial.print("Humidity:");
  Serial.print(humi,0); 
  Serial.print("%"); 
  Serial.print(" Temprature:");
  Serial.print(tempC,1); 
  Serial.print("oC ~ "); 
  Serial.print(tempF,1); 
  Serial.println("oF");
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

// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <Servo.h>
// #include <OneWire.h>       
// #include "DHT.h"    

// const int DHTPIN = D4;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
// const int DHTTYPE = DHT11;
// Servo myservo;
// ESP8266WebServer server(80);

// // Có thể dùng các giá trị đã define nếu không nhớ được giá trị chân GPIO
// // Ở đây mình dùng chân built in có sẵn trên ESP8266 luôn nha! 
// // (Lưu ý: trạng thái LOW, HIGH bị đảo ở trong trường hợp dùng chân built in)

// int led_status = 0;
// OneWire ds(DHTPIN); 
// DHT dht(DHTPIN, DHTTYPE);

// String  WebPage = {
//   "<!DOCTYPE html><html><head>"
//     "<title>Web realtime - Light Sensor</title>"
//     "<meta charset=\"UTF-8\">"
//     "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
//     "<style>"
//     "html {font-family: Helvetica;display: inline-block;margin: 0px auto;text-align: center;}"
//     ".button {background-color: #4CAF50;border: none;color: white;padding: 16px 40px;text-decoration: none;font-size: 30px;margin: 2px;cursor: pointer;}"
//     ".button2 {background-color: #555555;}"
//     ".btn{background-color: #4CAF50;border: none;color: white;padding: 8px 20px;text-decoration: none;font-size: 16px;margin: 2px;cursor: pointer;}"
//     ".degrees-input {width: 60px;height: 30px;font-size: 20px;text-align: center;}"
//     "</style>"
//     "</head><body>"
//     "<h1><p id=\"serialMonitor\"> None </p><h1><br>"
//     "<div id=\"motor_controller\">"
//     "    <p>Điều khuyển động cơ Servo</p>"
//     "    Degrees: <input class=\"degrees-input\" type=\"text\" id=\"degrees\" value=\"\">"
//     "    <a href=\"#\" class=\"btn\" onclick=\"sendValue()\">Send</a>"
//     "</div>"
//     "</body><script>"
//     "window.onload = function() {"
//        "readSerial();"
//     "};"
//     "function readSerial() {"
//     "var serialMonitor = document.getElementById('serialMonitor');"
//     "var xhttp = new XMLHttpRequest();"
//     "xhttp.onreadystatechange = function() {"
//     "if (this.readyState == 4 && this.status == 200) {"
//     "serialMonitor.innerHTML = this.responseText;"
//     "setTimeout(readSerial, 500);"
//     "}"
//     "};"
//     "xhttp.open('GET', 'readSerial', true);"
//     "xhttp.send();"
//     "}"
//     "function sendValue() { var degreesInput = document.getElementById('degrees'); var xhttp2 = new XMLHttpRequest(); var degrees = degreesInput.value; xhttp2.open('POST', 'sendValue', true); xhttp2.setRequestHeader('Content-type', 'application/x-www-form-urlencoded'); xhttp2.send('degrees=' + degrees); }"
//     "</script></html>"
// };

// void setup() {
//   dht.begin(); 
//   myservo.attach(D1, 500,2400);
//   Serial.begin(9600);

//   // Thiết lập LED// Thiết lập trạng thái mức điện cao cho chân tín hiệu LED

//   // ===========THIẾT LẬP KẾT NỐI WIFI====================================================
//   delay(1000);
//   WiFi.begin("TUHOC_KHU_A", ""); //SSID && Pasword
//   while (WiFi.waitForConnectResult() != WL_CONNECTED) {
//     Serial.println(".");
//   }
//   Serial.println("IP: ");
//   Serial.println(WiFi.localIP());
//   // ===============================================================================
//   // Giao diện trang chủ
//   server.on("/", [] {server.send(200,"text/html", WebPage);});
//   setupRoutes();
//   server.begin();  // Bắt đầu web server
// }

// void handleReadSerial() {
//   // Gửi giá trị cảm biến về client
//   //int light = digitalRead(D2);
//   float h = dht.readHumidity();    //Đọc độ ẩm
//   float t = dht.readTemperature();
//   server.send(200, "text/plain", "Giá trị độ ẩm: " + String(h) + ", nhiệt độ: " + String(t));
// }

// int receivedValue = 0;
// void handleSendValue() {
//   if (server.hasArg("degrees")) {
//     receivedValue = server.arg("degrees").toInt();
//   }
// }

// void setupRoutes() {
//   server.on("/readSerial", handleReadSerial);
//   server.on("/sendValue", handleSendValue);
// }


// void loop() {
//   // Xử lý các yêu cầu từ client
//   server.handleClient();
//   if (receivedValue > 0) {
//     float h = dht.readHumidity();    //Đọc độ ẩm
//   float t = dht.readTemperature();
//   if (h >=85 && t >=27){
//     myservo.write(receivedValue);
//       delay(500); 
//       myservo.write(0);
//       delay(500); 
//   }
//   else{
//     myservo.write(180);
//       delay(500); 
//       myservo.write(0);
//       delay(500); 
//   }
//     //quay servo thuận theo góc INPUT
//       Serial.print(receivedValue);
//       // 5/3.3
      
//   }
// }