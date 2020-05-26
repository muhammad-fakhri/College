int ledPins[] = {8,9,10,11,12,13};

void setup()
{
  int index;

  for(index = 0; index <= 6; index++)
  {
    pinMode(ledPins[index],OUTPUT);
    // ledPins[index] is replaced by the value in the array.
    // For example, ledPins[0] is 2
  }
}


void loop()
{
  trafficLight();
}

void trafficLight()
{
  int delayTime = 5000; // time (milliseconds) to pause between LEDs
                       // make this smaller for faster switching

//  int ledPins[] = {8,9,10,11,12,13};
//                  {0,1, 2, 3, 4, 5};
//  giliran pertama
  digitalWrite(ledPins[4], HIGH);  
  digitalWrite(ledPins[3], HIGH);  
  digitalWrite(ledPins[1], HIGH);  
  delay(delayTime);                
  // turn all the LEDs off:
  digitalWrite(ledPins[4], LOW);  
  digitalWrite(ledPins[3], LOW);
  digitalWrite(ledPins[1], LOW);  
  
//  giliran kedua
  digitalWrite(ledPins[5], HIGH);  
  digitalWrite(ledPins[2], HIGH);  
  digitalWrite(ledPins[1], HIGH);  
  delay(delayTime);                
  // turn all the LEDs off:
  digitalWrite(ledPins[5], LOW);  
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[1], LOW);              

//  giliran ketiga
  digitalWrite(ledPins[5], HIGH);  
  digitalWrite(ledPins[3], HIGH);  
  digitalWrite(ledPins[0], HIGH);  
  delay(delayTime);                
  // turn all the LEDs off:
  digitalWrite(ledPins[5], LOW); 
  digitalWrite(ledPins[3], LOW);
  digitalWrite(ledPins[0], LOW);  

}
