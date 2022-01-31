#include <Servo.h>
Servo myservo[4];
enum eSERVO {GRIP_SERVO = 6, ELBOW_SERVO, SHOULDER_SERVO, BASE_SERVO};
enum eLED {MANUAL_LED = 10, AUTO_LED, PROGRAM_LED};
enum eBUTTONS {MANUAL_BUTTON = 2, ENTER_BUTTON, AUTO_BUTTON, PROGRAM_BUTTON};
enum eADC_DATA {BASE = 0, SHOULDER, ELBOW, GRIP};
volatile int ADC_values[4] = {0};
enum eOPERATING_MODE{MANUAL_MODE = 0, AUTO_MODE, PROGRAM_MODE};
int operatingMode = MANUAL_MODE;
unsigned int avg = 0;
const unsigned int maxADCval = 1023; //check the max value of ADC

void setup() {
  Serial.begin(9600);
  pinMode(MANUAL_LED, OUTPUT);
  pinMode(AUTO_LED, OUTPUT);
  pinMode(PROGRAM_LED, OUTPUT);
  pinMode(MANUAL_BUTTON, INPUT);
  pinMode(ENTER_BUTTON, INPUT);
  pinMode(AUTO_BUTTON, INPUT);
  pinMode(PROGRAM_BUTTON, INPUT);
  myservo[GRIP].attach(GRIP_SERVO);
  myservo[ELBOW].attach(ELBOW_SERVO);
  myservo[SHOULDER].attach(SHOULDER_SERVO);
  myservo[BASE].attach(BASE_SERVO);
}

void loop() {
  operatingMode = getOperatingMode();
  OperatingModeIndication(operatingMode);
  
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 10; j++){
      avg += analogRead(i);
    }
    ADC_values[i] = avg/10;
    avg = 0;
  }
  for(int i = 0; i < 4; i++){
    myservo[i].write(map(ADC_values[i], 0, maxADCval, 0, 180));
  }
}

int getOperatingMode(void)
{
  if(digitalRead(MANUAL_BUTTON) == HIGH){
    return MANUAL_MODE;
  }
  if(digitalRead(AUTO_BUTTON) == HIGH){
    return AUTO_MODE;
  }
  if(digitalRead(PROGRAM_BUTTON) == HIGH){
    return PROGRAM_MODE;
  }
}
void OperatingModeIndication(int mode)
{
   switch(mode){
     case(MANUAL_MODE): {
      digitalWrite(MANUAL_LED, HIGH);
      digitalWrite(AUTO_LED, LOW);
      digitalWrite(PROGRAM_LED, LOW);
      break;
    }
    case(AUTO_MODE): {
      digitalWrite(MANUAL_LED, LOW);
      digitalWrite(AUTO_LED, HIGH);
      digitalWrite(PROGRAM_LED, LOW);
      break;
    }
    case(PROGRAM_MODE): {
      digitalWrite(MANUAL_LED, LOW);
      digitalWrite(AUTO_LED, LOW);
      digitalWrite(PROGRAM_LED, HIGH);
      break;
    }
   }
}
