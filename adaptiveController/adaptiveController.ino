// #define BUTTON_UP 2
// #define BUTTON_DN 4
// #define BUTTON_LT 5
// #define BUTTON_RT 3
// #define BUTTON_E 6
// #define BUTTON_F 7
// #define BUTTON_K 8

// #define ANLG_JOY_X_AXIS 0
// #define ANLG_JOY_Y_AXIS 1

#define PRESSED LOW

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
digitalButton BUTTON_E; 
digitalButton BUTTON_F; 
digitalButton BUTTON_K; 

analogButton ANLG_JOY_X_AXIS; 
analogButton ANLG_JOY_Y_AXIS; 


// int analogLastState[2] = {0, 0};
// short lastState[9];
// unsigned long stateChangeTime[9];

// debug/testing map for output - should not include in prod code
// String buttonNames[9] = {"X-Axis", "Y-Axis", "UP", "RIGHT", "DOWN", "LEFT", "E", "F", "K"};

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

void setup() {
  // put your setup code here, to run once:

  // Initialize serial connection
  Serial.begin(9600);
  Serial1.begin(9600);

  // Initialize button variables
  BUTTON_UP.pinNum = 2; BUTTON_UP.name = "UP";    BUTTON_UP.btnIndx = '1';
  BUTTON_RT.pinNum = 3; BUTTON_RT.name = "RIGHT"; BUTTON_RT.btnIndx = '2';
  BUTTON_DN.pinNum = 4; BUTTON_DN.name = "DOWN";  BUTTON_DN.btnIndx = '3';
  BUTTON_LT.pinNum = 5; BUTTON_LT.name = "LEFT";  BUTTON_LT.btnIndx = '4';
  BUTTON_E.pinNum = 6; BUTTON_E.name = "E";       BUTTON_E.btnIndx = '5';
  BUTTON_F.pinNum = 7; BUTTON_F.name = "F";       BUTTON_F.btnIndx = '6';
  BUTTON_K.pinNum = 8; BUTTON_K.name = "K";       BUTTON_K.btnIndx = '7';
  ANLG_JOY_X_AXIS.pinNum = 0; ANLG_JOY_X_AXIS.name = "X-Axis";
  ANLG_JOY_Y_AXIS.pinNum = 1; ANLG_JOY_Y_AXIS.name = "Y-Axis";

  // Initiate button pins with pullup resistor
  pinMode(BUTTON_UP.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_DN.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_LT.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_RT.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_E.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_F.pinNum, INPUT_PULLUP);
  pinMode(BUTTON_K.pinNum, INPUT_PULLUP);
  
  // Initialize last states
  // for(int i = 0; i < sizeof(lastState); i++)
  // {
  //   lastState[i] = HIGH;
  //   stateChangeTime[i] = 0;
  // }
  // analogLastState[0] = analogRead(ANLG_JOY_X_AXIS);
  // analogLastState[1] = analogRead(ANLG_JOY_Y_AXIS);
}

void analogButtonState(analogButton &button, short debounceTime = 10)
{
  int position = analogRead(button.pinNum);
  unsigned long currTime = millis();
  // Serial.println(position == analogLastState[button]);
  if((position - button.lastState > 20 || position - button.lastState < -20) && (currTime - button.stateChangeTime) > debounceTime)
  {
    button.lastState = position;
    button.stateChangeTime = currTime;
    Serial.print(button.name + ": ");
    Serial.println(position);
    // println(2, button.name + ": " + position);
    println(2, button.btnIndx);
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
      Serial.print(button.name + " button pressed " + button.btnIndx);
      // Serial1.println(button.name + " button pressed");
      // println(2, button.name + " button pressed");
      println(2, button.btnIndx);
    }
    else
    {
      // Serial.println(button.name + " button released");
      // Serial1.println(button.name + " button released");
      // println(2, button.name + " button released");
      println(2, button.btnIndx);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalButtonState(BUTTON_UP);
  digitalButtonState(BUTTON_DN);
  digitalButtonState(BUTTON_LT);
  digitalButtonState(BUTTON_RT);
  digitalButtonState(BUTTON_E);
  digitalButtonState(BUTTON_F);
  digitalButtonState(BUTTON_K);
  analogButtonState(ANLG_JOY_X_AXIS);
  analogButtonState(ANLG_JOY_Y_AXIS);

}
