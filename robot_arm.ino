#include <Servo.h>
Servo myservo;
enum eLED {MANUAL_LED = 10, AUTO_LED, PROGRAM_LED};
enum eBUTTONS {MANUAL_BUTTON = 2, ENTER_BUTTON, AUTO_BUTTON, PROGRAM_BUTTON};
enum eADC_DATA {BASE = 0, SHOULDER, ELBOW, GRIP};
volatile int ADC_values[4] = {0};
enum eOPERATING_MODE{MANUAL_MODE = 0, AUTO_MODE, PROGRAM_MODE};
int operatingMode = MANUAL_MODE;
unsigned long avg = 0;
void setup() {
  Serial.begin(9600);
  pinMode(MANUAL_LED, OUTPUT);
  pinMode(AUTO_LED, OUTPUT);
  pinMode(PROGRAM_LED, OUTPUT);
  pinMode(MANUAL_BUTTON, INPUT);
  pinMode(ENTER_BUTTON, INPUT);
  pinMode(AUTO_BUTTON, INPUT);
  pinMode(PROGRAM_BUTTON, INPUT);
  myservo.attach(9);
}

void loop() {
  if(digitalRead(MANUAL_BUTTON) == HIGH){
    operatingMode = MANUAL_MODE;
    digitalWrite(MANUAL_LED, HIGH);
    digitalWrite(AUTO_LED, LOW);
    digitalWrite(PROGRAM_LED, LOW);
  }
  if(digitalRead(AUTO_BUTTON) == HIGH){
    operatingMode = AUTO_MODE;
    digitalWrite(MANUAL_LED, LOW);
    digitalWrite(AUTO_LED, HIGH);
    digitalWrite(PROGRAM_LED, LOW);
  }
  if(digitalRead(PROGRAM_BUTTON) == HIGH){
    operatingMode = PROGRAM_MODE;
    digitalWrite(MANUAL_LED, LOW);
    digitalWrite(AUTO_LED, LOW);
    digitalWrite(PROGRAM_LED, HIGH);
  }
  Serial.print("MODE = ");Serial.print(operatingMode);
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 10; j++){
      avg += analogRead(i);
    }
//    ADC_values[i] = analogRead(i);
    ADC_values[i] = avg/10;
    Serial.print("[");Serial.print(ADC_values[i]);Serial.print("]");
    avg = 0;
  }
  Serial.print("\n");
  myservo.write(map(ADC_values[0], 0, 1023, 0, 180));
}
