#define LINE 2 // Định nghĩa chân tín hiệu số 2 cho cảm biến dò line


int in1 = 7;
int in2 = 8;
int e = 9;

int val = 0;

void setup() {
    pinMode(LINE, INPUT); // Cấu hình chân LINE là đầu vào

    Serial.begin(9600); // Cấu hình tốc độ baud 9600 bps
}
//DEN BAT DEN, TRANG TAT DEN
void loop() {
    val = digitalRead(LINE); // Đọc giá trị từ cảm biến
    if(val == 1){
              digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(e, 100);
    }
    else if(val == 0){
              digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(e, 100 );
    }
    Serial.println(val); // In giá trị ra Serial Monitor
    delay(500); // Chờ 500ms trước khi đọc lại

}