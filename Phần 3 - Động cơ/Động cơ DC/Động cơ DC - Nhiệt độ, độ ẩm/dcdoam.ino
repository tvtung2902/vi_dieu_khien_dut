


#include "DHT.h" // Sử dụng thư viện DHT

#define DHT11Pin 4 // Chọn chân kết nối với DHT11 là chân số 4
#define DHTType DHT11 // Chọn loại cảm biến DHT11

DHT HT(DHT11Pin, DHTType); // Khởi tạo đối tượng DHT

float humi; // Biến để lưu giá trị độ ẩm
float tempC; // Biến để lưu giá trị nhiệt độ theo độ Celsius (°C)
float tempF; // Biến để lưu giá trị nhiệt độ theo độ Fahrenheit (°F)


int analog = A0;
int in1 = 7;
int in2 = 8;
int e = 9;
void setup() {
    Serial.begin(9600);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(e, OUTPUT);
        HT.begin(); // Khởi động cảm biến DHT
    delay(1000); // Chờ 1 giây
}

void loop() {




        humi = HT.readHumidity(); // Đọc giá trị độ ẩm từ cảm biến
    tempC = HT.readTemperature(); // Đọc giá trị nhiệt độ theo độ C từ cảm biến
    tempF = HT.readTemperature(true); // Đọc giá trị nhiệt độ theo độ F từ cảm biến
    
    if(humi > 75){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(e, 70);
    } else {
                digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(e, 70 );
    }


    // In giá trị độ ẩm và nhiệt độ ra Serial Monitor với độ chính xác 1 chữ số thập phân
    Serial.print("Độ ẩm: ");
    Serial.print(humi, 1);
    Serial.print("\t");
    Serial.print(tempC, 1);
    Serial.print(" °C ");
    Serial.print(tempF, 1);
    Serial.println(" °F");
    delay(1000);
}