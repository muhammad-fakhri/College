int ledPins[] = {8,9,10,11};
const int button1Pin = 3;  // pushbutton 1 pin
const int button2Pin = 4;  // pushbutton 2 pin
int button1State, button2State;

void setup()
{
  int index;

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  for(index = 0; index <= 4; index++)
  {
    pinMode(ledPins[index],OUTPUT);
  }
}


void loop()
{
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  trafficLightWithButton();
}

void trafficLightWithButton()
{
  int delayTime = 0; // time (milliseconds) to pause between LEDs
                       // make this smaller for faster switching

//  int ledPins[] = {8,9,10,11};
//                  {0,1, 2, 3};

  if ((button1State == LOW) && (button2State == LOW)){
    digitalWrite(ledPins[0], HIGH);  
    digitalWrite(ledPins[3], HIGH); 
    delay(delayTime);                
    // turn all the LEDs off:
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[3], LOW);  
    
    }
  else if((button1State == LOW) || (button2State == LOW)){
    //  giliran pertama  
    digitalWrite(ledPins[2], HIGH);  
    digitalWrite(ledPins[1], HIGH);  
    delay(delayTime);                
    // turn all the LEDs off:
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[1], LOW);  
  } 
  else {
    //  giliran pertama  
    digitalWrite(ledPins[3], HIGH);  
    digitalWrite(ledPins[1], HIGH);  
    delay(delayTime);                
    // turn all the LEDs off:
    digitalWrite(ledPins[3], LOW);
    digitalWrite(ledPins[1], LOW);  
    }           

}
