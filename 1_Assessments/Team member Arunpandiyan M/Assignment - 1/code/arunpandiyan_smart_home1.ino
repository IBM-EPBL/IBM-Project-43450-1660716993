int buzzerPin = 2;
int safeGasPin = 3;
int dangerGasPin = 4;
int safeTheifPin = 5;
int echo = 6;
int trig = 7;
int dangerTheifPin = 8;
bool dangerTheif = false;
long cm;
int distanceThreshold = 336;
bool dangerGas = false;
int gasThreshold = 180;
int gasLeak;
int gasPin = A5;
long lecture_echo;

void setup() { 
  pinMode(trig, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(safeGasPin, OUTPUT);
  pinMode(dangerGasPin, OUTPUT);
  pinMode(safeTheifPin, OUTPUT);
  pinMode(dangerTheifPin, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  pinMode(gasPin, INPUT);
  Serial.begin(9600); 
}
void loop() { 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  cm = lecture_echo / 58; 
  Serial.print("Distance in cm : "); 
  Serial.println(cm);
  if (cm < distanceThreshold) {
    dangerTheif = true;
    digitalWrite(dangerTheifPin, HIGH);
    digitalWrite(safeTheifPin, LOW);
  } else {
    dangerTheif = false;
    digitalWrite(safeTheifPin, HIGH);
    digitalWrite(dangerTheifPin, LOW);
  }
  gasLeak = analogRead(gasPin);
  Serial.print("Gas Leak = ");
  Serial.println(gasLeak);
  if (gasLeak > gasThreshold) {
    dangerGas = true;
    digitalWrite(dangerGasPin, HIGH);
    digitalWrite(safeGasPin, LOW);
  } else {
    dangerGas = false;
    digitalWrite(safeGasPin, HIGH);
    digitalWrite(dangerGasPin, LOW);
  }
  if (dangerGas || dangerTheif) {
    digitalWrite(buzzerPin, !digitalRead(buzzerPin));
  } else {
    digitalWrite(buzzerPin, LOW);
  }
  delay(300); 
}