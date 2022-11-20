#include <ArduinoJson.h>
 
#include <SoftwareSerial.h>
#include <String.h>

#define proxout 3
#define trigPin 5
#define echoPin 6
#define binid 5098
#define maxbinlevel 30

float duration, distance=50;
String str;
SoftwareSerial SIM900(9,10); //rx,tx

StaticJsonBuffer<200> jsonBuffer; 

 
void setup()
{
  SIM900.begin(9600);        // the GPRS baud rate
  Serial.begin(9600);
  SIM900.begin(9600);  /* Define baud rate for software serial communication */
  pinMode(proxout,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  str="AT+HTTPPARA=\"URL\",\"sajeevkrishna10.pythonanywhere.com/statupdate?binid="+String(binid)+"&binstatus=";

}
 
void loop()
{
  if (digitalRead(proxout)== LOW){
    //switch on the ultrasonic sensor to scare them away
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(trigPin, LOW);
  }
  else if (digitalRead(proxout)== HIGH){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Measure the response from the HC-SR04 Echo Pin
   
    duration = pulseIn(echoPin, HIGH);
    
    // Determine distance from duration
    // Use 343 metres per second as speed of sound
    
    distance = (duration/2)*0.0343;
    distance = distance - maxbinlevel;
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    
    delay(500);  
    }
 
 
 /********************GSM Communication Starts********************/
 
  Serial.println("AT");
  SIM900.println("AT");
  delay(5000);
  ShowSerialData();
  delay(5000);
  
  Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");    
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=3,1,\"APN\",\"www\"");  
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"www\""); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=1,1");
  SIM900.println("AT+SAPBR=1,1"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=2,1");
  SIM900.println("AT+SAPBR=2,1"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPINIT");
  SIM900.println("AT+HTTPINIT"); 
  delay(5000); 
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPPARA=\"CID\",1");
  SIM900.println("AT+HTTPPARA=\"CID\",1"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
 
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& object = jsonBuffer.createObject();
  
  object.set("level",distance);
  object.set("latitude",9.882591549981502);
  object.set("longitude",78.08362710443497);
  object.set("weight",random());
  
  object.printTo(Serial);
  Serial.println(" ");  
  String sendtoserver;
  object.prettyPrintTo(sendtoserver);
  delay(4000);
 
  SIM900.println("AT+HTTPPARA=\"URL\",\"http://https://x8dg57.messaging.internetofthings.ibmcloud.com/api/v0002/device/types/smartbin/devices/123/events/event_1\""); //Server address
  delay(4000);
  ShowSerialData();
 
  SIM900.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(4000);
  ShowSerialData();
 
 
  SIM900.println("AT+HTTPDATA=" + String(sendtoserver.length()) + ",100000");
  Serial.println(sendtoserver);
  delay(6000);
  ShowSerialData();
 
  SIM900.println(sendtoserver);
  delay(6000);
  ShowSerialData;
 
  SIM900.println("AT+HTTPACTION=1");
  delay(6000);
  ShowSerialData();
 
  SIM900.println("AT+HTTPREAD");
  delay(6000);
  ShowSerialData();
 
  SIM900.println("AT+HTTPTERM");
  delay(10000);
  ShowSerialData;
 
  /********************GSM Communication Stops********************/
 
}
 void ShowSerialData()
{
  while(SIM900.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM900.read())); /* Print character received on to the serial monitor */
}