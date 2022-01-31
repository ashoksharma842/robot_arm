#include <Servo.h>
#include <EEPROM.h>
Servo myservo[4];
enum eSERVO {GRIP_SERVO = 6, ELBOW_SERVO, SHOULDER_SERVO, BASE_SERVO};
enum eLED {MANUAL_LED = 10, AUTO_LED, PROGRAM_LED};
enum eBUTTONS {MANUAL_BUTTON = 2, ENTER_BUTTON, AUTO_BUTTON, PROGRAM_BUTTON};
enum eADC_DATA {BASE = 0, SHOULDER, ELBOW, GRIP};
volatile int ADC_values[4] = {0};
enum eOPERATING_MODE{MANUAL_MODE = 0, AUTO_MODE, PROGRAM_MODE};
int operatingMode = MANUAL_MODE, prevOperatingMode = MANUAL_MODE;
unsigned int avg = 0;
const unsigned int maxADCval = 1023; //check the max value of ADC

// Variables for long press of programming mode:
int lastState = LOW;
enum eButtonStae {ePRESSED = 1, eUNPRESSED = 2};
int currentState;
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
const int SHORT_PRESS_TIME = 1000; // 1 second

int addr = 1;

void setup() {
//  EEPROM.write(0, 0);
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
  attachInterrupt(digitalPinToInterrupt(ENTER_BUTTON),EnterButtonPressed,RISING); 
  int total_steps = EEPROM.read(0);
  if(total_steps > 0){
    Serial.print("programmed step number : ");Serial.println((total_steps-1)/4);
    int read_addr = 1;
    while(read_addr < total_steps){
      for(int i = 0; i < 4; i++){
        Serial.print("[");Serial.print(EEPROM.read(read_addr + i));Serial.print("]");
      }
      read_addr +=4;
      Serial.print("\n");
    }
  } else {
    Serial.println("robot not programmed");
  }
}

void loop() {
  operatingMode = GetOperatingMode();
  OperatingModeIndication(operatingMode);

  if((operatingMode == MANUAL_MODE) || (operatingMode == PROGRAM_MODE)){
    MoveArmManually();
  }
  if(operatingMode == AUTO_MODE){
    MoveArmFromProgrammedLocations();
  }
}

void EnterButtonPressed()
{
  if(operatingMode == PROGRAM_MODE){
    for(int i = 0; i < 4; i++){
      EEPROM.write(addr + i, map(ADC_values[i], 0, maxADCval, 0, 180));
      Serial.print("[");Serial.print(map(ADC_values[i], 0, maxADCval, 0, 180));Serial.print("]");
    }
    addr += 4;//4 positions of servos written
    EEPROM.write(0, addr);//store the numbers of steps on address 0
    Serial.print("->");Serial.println((addr-1)/4);
  }
}
void MoveArmFromProgrammedLocations(void)
{
  //todo
}
void MoveArmManually(void)
{
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 10; j++){
      avg += analogRead(i);
    }
    ADC_values[i] = avg/10;
    myservo[i].write(map(ADC_values[i], 0, maxADCval, 0, 180));
    avg = 0;
  }
}
int GetOperatingMode(void)
{
  if((digitalRead(MANUAL_BUTTON) == HIGH) && (prevOperatingMode != MANUAL_MODE)){
    prevOperatingMode = MANUAL_MODE;
    Serial.println("MANUAL_MODE");
    return MANUAL_MODE;
  }
  if((digitalRead(AUTO_BUTTON) == HIGH) && (prevOperatingMode != AUTO_MODE)){
    prevOperatingMode = AUTO_MODE;
    Serial.println("MANUAL_MODE");
    return AUTO_MODE;
  }
  // Press and hold for 3s for programming mode in MANUAL mode.
  if((operatingMode == MANUAL_MODE) && (prevOperatingMode != PROGRAM_MODE)){
    if((digitalRead(PROGRAM_BUTTON) == HIGH) && (lastState == LOW)){// button is pressed
      pressedTime = millis();
      currentState = ePRESSED;
    }else if((digitalRead(PROGRAM_BUTTON) == LOW) &&(lastState == HIGH) && (currentState == ePRESSED)){// button is released
      releasedTime = millis();
      currentState = eUNPRESSED;
      long pressDuration = releasedTime - pressedTime;
      if( pressDuration > SHORT_PRESS_TIME ){
        prevOperatingMode = PROGRAM_MODE;
        pressDuration = 0;
        Serial.println("PROGRAM_MODE");
        return PROGRAM_MODE;
      }
    }
    lastState = digitalRead(PROGRAM_BUTTON);
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
