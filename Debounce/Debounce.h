#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include "Arduino.h"

class Debounce{
    
     public: 
     Debounce(int buttonPin);
     bool bounceless();    
    
    
    private: 
      int _buttonPin;
  
};


#endif
