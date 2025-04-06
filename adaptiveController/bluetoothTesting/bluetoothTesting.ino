void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}

char val;

void blinkCode(int code)
{
  for(int i = 0; i < code; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available())
  {
    val = Serial1.read();
    blinkCode((int)val - '0');
  }
}
