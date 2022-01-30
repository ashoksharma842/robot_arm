
enum LED {MANUAL_LED = 10, AUTO_LED, PROGRAM_LED};
enum BUTTONS {MANUAL_BUTTON = 2, ENTER_BUTTON, AUTO_BUTTON, PROGRAM_BUTTON};

void setup() {
  // put your setup code here, to run once:
  pinMode(MANUAL_LED, OUTPUT);
  pinMode(AUTO_LED, OUTPUT);
  pinMode(PROGRAM_LED, OUTPUT);
  pinMode(MANUAL_BUTTON, INPUT);
  pinMode(ENTER_BUTTON, INPUT);
  pinMode(AUTO_BUTTON, INPUT);
  pinMode(PROGRAM_BUTTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(MANUAL_BUTTON) == HIGH){
    digitalWrite(MANUAL_LED, HIGH);
    digitalWrite(AUTO_LED, LOW);
    digitalWrite(PROGRAM_LED, LOW);
  }
  if(digitalRead(AUTO_BUTTON) == HIGH){
    digitalWrite(MANUAL_LED, LOW);
    digitalWrite(AUTO_LED, HIGH);
    digitalWrite(PROGRAM_LED, LOW);
  }
  if(digitalRead(PROGRAM_BUTTON) == HIGH){
    digitalWrite(MANUAL_LED, LOW);
    digitalWrite(AUTO_LED, LOW);
    digitalWrite(PROGRAM_LED, HIGH);
  }
}
