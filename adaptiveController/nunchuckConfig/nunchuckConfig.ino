#define PRESSED LOW

#include <WiFi.h>


struct digitalButton {
  short pinNum;
  bool lastState = HIGH;
  unsigned long stateChangeTime = 0;
  String name;
  char btnIndx = 0;
};

struct analogButton {
  short pinNum;
  int lastState = 0;
  unsigned long stateChangeTime = 0;
  String name;
  char btnIndx = '0';
};

digitalButton BUTTON_UP; 
digitalButton BUTTON_RT; 
digitalButton BUTTON_DN; 
digitalButton BUTTON_LT; 
digitalButton BUTTON_BM; 
digitalButton BUTTON_J5; 
digitalButton D_PAD_UP;
digitalButton D_PAD_DN;
digitalButton D_PAD_LT;
digitalButton D_PAD_RT;
// digitalButton BUTTON_K; 

analogButton ANLG_JOY_X_AXIS; 
analogButton ANLG_JOY_Y_AXIS;
analogButton ANLG_TRG;

String macAddress;


void println(int comPort, String payload)
{
  if(comPort == 0)
  {
    Serial.println(payload);
  }
  else if(comPort == 1)
  {
    Serial1.println(payload);
  }
  else
  {
    Serial.println(payload);
    Serial1.println(payload);
  }
}

void println(int comPort, char payload, bool useAtoI = true)
{
  if(comPort == 0)
  {
    if(useAtoI)
    {
      Serial.println((int)payload - '0');
    }
    else
    {
      Serial.println(payload);
    }
  }
  else if(comPort == 1)
  {
    Serial1.println(payload);
  }
  else
  {
    if(useAtoI)
    {
      Serial.println((int)payload - '0');
    }
    else
    {
      Serial.println(payload);
    }    
    Serial1.println(payload);
  }
}



void analogButtonState(analogButton &button, short debounceTime = 10)
{
  int position = analogRead(button.pinNum);
  unsigned long currTime = millis();
  // Serial.println(position == analogLastState[button]);
  if((position - button.lastState > 100 || position - button.lastState < -100) && (currTime - button.stateChangeTime) > debounceTime)
  {
    button.lastState = position;
    button.stateChangeTime = currTime;
    Serial.print(button.name + ": ");
    Serial.println(position);
    // println(2, button.name + ": " + position);
    // println(2, button.btnIndx);
  }
}

void digitalButtonState(digitalButton &button, short debounceTime = 10)
{
  unsigned long currTime = millis();
  int currState = digitalRead(button.pinNum);
  if(currState != button.lastState && (currTime - button.stateChangeTime) > debounceTime)
  {
    button.lastState = currState;
    button.stateChangeTime = currTime;
    if(currState == PRESSED)
    {
      Serial.println(button.name + " button pressed");
      // Serial1.println(button.name + " button pressed");
      // println(2, button.name + " button pressed");
      // println(2, button.btnIndx);
    }
    else
    {
      Serial.println(button.name + " button released");
      // Serial1.println(button.name + " button released");
      // println(2, button.name + " button released");
      // println(2, button.btnIndx);
    }
  }
}


void setup() {
  Serial.begin(115200);
  // Serial1.begin(9600);

  // Initialize button variables
  BUTTON_UP.pinNum = 5;   BUTTON_UP.name = "UP";                  BUTTON_UP.btnIndx = '1';
  BUTTON_RT.pinNum = 6;   BUTTON_RT.name = "RIGHT";               BUTTON_RT.btnIndx = '2';
  BUTTON_DN.pinNum = 7;   BUTTON_DN.name = "DOWN";                BUTTON_DN.btnIndx = '3';
  BUTTON_LT.pinNum = 8;   BUTTON_LT.name = "LEFT";                BUTTON_LT.btnIndx = '4';
  BUTTON_BM.pinNum = 3;   BUTTON_BM.name = "Bumper";              BUTTON_BM.btnIndx = '5';
  BUTTON_J5.pinNum = 2;   BUTTON_J5.name = "Joystick Click";      BUTTON_J5.btnIndx = '6';
  D_PAD_UP.pinNum = 9;    D_PAD_UP.name = "D-Pad UP";             D_PAD_UP.btnIndx = '7';
  D_PAD_DN.pinNum = 10;   D_PAD_DN.name = "D-Pad Down";           D_PAD_DN.btnIndx = '8';
  D_PAD_LT.pinNum = 20;   D_PAD_LT.name = "D-Pad Left";           D_PAD_LT.btnIndx = '9';
  D_PAD_RT.pinNum = 21;   D_PAD_RT.name = "D-Pad Right";          D_PAD_RT.btnIndx = '10';
  
  ANLG_JOY_X_AXIS.pinNum = 0; ANLG_JOY_X_AXIS.name = "X-Axis";
  ANLG_JOY_Y_AXIS.pinNum = 1; ANLG_JOY_Y_AXIS.name = "Y-Axis";
  // ANLG_TRG.pinNum = 4; ANLG_TRG.name = "Trigger";

  // Initiate button pins with pullup resistor
  pinMode(BUTTON_UP.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_DN.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_LT.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_RT.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_BM.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_J5.pinNum, INPUT_PULLUP);
  pinMode(D_PAD_UP.pinNum, INPUT_PULLUP);
  pinMode(D_PAD_DN.pinNum, INPUT_PULLUP);
  pinMode(D_PAD_LT.pinNum, INPUT_PULLUP);
  pinMode(D_PAD_RT.pinNum, INPUT_PULLUP);

  WiFi.mode(WIFI_MODE_STA);
  macAddress = WiFi.macAddress();

}

void loop() {
  digitalButtonState(BUTTON_UP);
  digitalButtonState(BUTTON_DN);
  digitalButtonState(BUTTON_LT);
  digitalButtonState(BUTTON_RT);
  digitalButtonState(BUTTON_BM);
  digitalButtonState(BUTTON_J5);
  digitalButtonState(D_PAD_UP);
  digitalButtonState(D_PAD_DN);
  digitalButtonState(D_PAD_LT);
  digitalButtonState(D_PAD_RT);



  analogButtonState(ANLG_JOY_X_AXIS);
  analogButtonState(ANLG_JOY_Y_AXIS);
  // analogButtonState(ANLG_TRG);
}
