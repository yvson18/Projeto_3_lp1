#include "Arduino.h"
#include "Debounce.h"


Debounce::Debounce(int buttonPin){
    pinMode(buttonPin,INPUT_PULLUP);
    _buttonPin = buttonPin;
}

bool Debounce :: bounceless(){
  #define debounceDelay  50
  static int outputSignal = LOW;
  static int currentButtonState = HIGH;
  static int lastButtonState = HIGH;
  static long firstOcilationTime;

  int reading = digitalRead(_buttonPin);

  if(reading != lastButtonState){
    firstOcilationTime = millis();
    
  }

  if((millis() - firstOcilationTime) > debounceDelay){
    
    if(reading != currentButtonState){
      currentButtonState = reading;
      
        if(currentButtonState == LOW){
         outputSignal = !outputSignal;
        }
    }
  }

  lastButtonState = reading;
  return outputSignal;
}
