// Make a Smart Home in Tinkercad, using 2+ sensors, Led, Buzzer in single code and circuit.
// Abdul Rahman S 
// REG NO : 911719104002 
// 10-09-2021

#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 2, 11, 10, 9, 8); 
float value;
int tmp = A1;


// initialize the library with the numbers of the interface pins

int pir = 0;
int dist = 0;
int photoresistor = 0;
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(12, INPUT);
  lcd.begin(16, 2);
  pinMode(tmp,INPUT);
}
void loop() 
{
  
  digitalWrite(5, LOW);//buzzer off
  photoresistor = analogRead(A2);
  pir = digitalRead(12); //pir motion sensor in the room
  
  if (pir == HIGH) {
    digitalWrite(13, HIGH); //the light turns on 
  } else {
    digitalWrite(13, LOW);//the light turns off 
  }
  dist = 0.01723 * readUltrasonicDistance(7, A0); //outside the house the ultrasonic detects burglers 
  if (dist <= 60 && dist >= 0) {
    digitalWrite(5, HIGH);  //the buzzer turns on after the detection 
  }
  
  if (photoresistor < 200) { //the photoresistor turns on a yellow light 
    digitalWrite(4, HIGH);   //at night above the front door
  } else {
    digitalWrite(4, LOW);
  }
  
  delay(10); // Delay a little bit to improve simulation performance
  value = analogRead(tmp)*0.004882814; // temperature calculations for celsius
  value = (value - 0.5) * 100.0;
  lcd.setCursor(0,0);
  lcd.print("Tmp:");
  lcd.print(value);
  lcd.print(char (178));// for real simulation use lcd.print ((char)223)
  lcd.print("C");
  delay(1000);
    
  
	
}