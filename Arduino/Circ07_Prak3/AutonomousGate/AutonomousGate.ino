#include <Servo.h>  // servo library

const int sensorPin = 0;
const int buzzerPin = 11;
const int ledPin = 13;
Servo servo1;

void setup()
{
  servo1.attach(9);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  int lightLevel;
  lightLevel = analogRead(sensorPin);
  if(lightLevel < 300) {
      openGate();   
  } else {
      closeGate();
  }
}

void openGate(){
  //Putar servo 180 derajat
  servo1.write(180);   
  //Nyalakan LED
  digitalWrite(ledPin, HIGH);
  //Hidupkan buzzer
  tone(buzzerPin, 500, 500);
  //delay(500);        
  //tone(buzzerPin, 0, 500);
  //delay(500);
}

void closeGate(){
  //Putar servo 0 derajat
  servo1.write(0);
  //Matikan LED
  digitalWrite(ledPin, LOW);
  //Hidupkan buzzer
  tone(buzzerPin, 200, 500);
  //delay(500);
  //tone(buzzerPin, 0, 500);
  //delay(500);
}
