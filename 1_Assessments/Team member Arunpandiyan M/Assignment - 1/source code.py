int diods = 13;
int pin = A0;
int value;

int red = 10;
int yellow = 11;
int green = 12;
int echo = 2;
int trigger = 3;

int const Pin_Gas = A1;
int green1 = 7;
int yellow1 = 6;
int red1 = 5;

void setup()
{
  pinMode(diods, OUTPUT);
  pinMode(pin, INPUT);
  
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(green1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(red1, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  //Lamp
  value = analogRead(pin);
  analogWrite(diods, map(value, 1023, 0, 0, 255));
  
  //Distance sensor
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  long duration = pulseIn(echo, HIGH);
  long distance = (duration / 5) / 29.1;
  
  
  if(distance < 50 && distance >= 20)
  {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  }
  if(distance < 20 && distance >= 5)
  {
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
  }
  if(distance < 5)
  {
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
  }
  
  //Smoke Detector
  int input = analogRead(Pin_Gas);
  input = map(input, 300, 750, 0, 100);
  
  if(input < 30) 
  {
    digitalWrite(green1, HIGH);
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, LOW);
  }
  if(input >= 30 && input < 50) 
  {
    digitalWrite(yellow1, HIGH);
    digitalWrite(red1, LOW);
    digitalWrite(green1, LOW);
  }
  if(input >= 80)
  {
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, HIGH);
    digitalWrite(green1, LOW);
  }
  
  delay(150);
}
