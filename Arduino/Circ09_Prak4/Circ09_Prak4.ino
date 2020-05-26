// Include the servo library to add servo-control functions:

#include <Servo.h> 

// Create a servo "object", called servo1. Each servo object
// controls one servo (you can have a maximum of 12):

Servo servo1;

// Define the analog input pin to measure flex sensor position:

const int flexpin = 0; 
#define buzzerPin 9
#define ledPin 6
#define servoPin 11
#define potentioPin A1


void setup() 
{ 
  // Use the serial monitor window to help debug our sketch:
   
  Serial.begin(9600);
  
  // Enable control of a servo on pin 9:

  servo1.attach(servoPin); //servo
  pinMode(buzzerPin, OUTPUT);//buzzer
  pinMode(ledPin, OUTPUT);//led indicator when singing a note
} 


void loop() 
{ 
  int flexposition;    // Input value from the analog pin.
  int servoposition;   // Output value to the servo.
  int sensorValue;

  // Read the voltage from the softpot (0-1023)
  
  sensorValue = analogRead(potentioPin);

  // Read the position of the flex sensor (0 to 1023):
  
  flexposition = analogRead(flexpin);

  // Because the voltage divider circuit only returns a portion
  // of the 0-1023 range of analogRead(), we'll map() that range
  // to the servo's range of 0 to 180 degrees. The flex sensors
  // we use are usually in the 600-900 range:
  
  servoposition = map(flexposition, 600, 900, 0, 180);
  servoposition = constrain(servoposition, 0, 180);

  // Now we'll command the servo to move to that position:

  servo1.write(servoposition);
  if(flexposition >900){
    digitalWrite(ledPin, HIGH); //led
    //digitalWrite(buzzerPin, HIGH); //buzzer
    tone(buzzerPin, 330, 1000);
    delay(1000);            // wait for tone to finish
   } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  if(sensorValue > 0){
    digitalWrite(ledPin, HIGH); //led
    tone(buzzerPin, 330, 1000);
    delay(1000);            // wait for tone to finish
  } else {
    digitalWrite(ledPin, LOW); //led
  }

  // Because every flex sensor has a slightly different resistance,
  // the 600-900 range may not exactly cover the flex sensor's
  // output. To help tune our program, we'll use the serial port to
  // print out our values to the serial monitor window:
  
  Serial.print("flex: ");
  Serial.print(flexposition);
  Serial.print("  potentio: ");
  Serial.print(sensorValue);
  Serial.print("  servo: ");
  Serial.println(servoposition);
  
  // Note that all of the above lines are "print" except for the
  // last line which is "println". This puts everything on the
  // same line, then sends a final carriage return to move to
  // the next line.

  // After you upload the sketch, turn on the serial monitor
  // (the magnifying-glass icon to the right of the icon bar).
  // You'll be able to see the sensor values. Bend the flex sensor
  // and note its minimum and maximum values. If you replace the
  // 600 and 900 in the map() function above, you'll exactly match
  // the flex sensor's range with the servo's range.
  
  delay(100);  // wait 20ms between servo updates
} 
