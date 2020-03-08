#include <Debounce.h>

Debounce botao = Debounce(2);

void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  Serial.println(botao.bounceless());

  if(botao.bounceless() == 1){
    digitalWrite(3,1);
    
  }else{
    digitalWrite(3,0);
  }
  
}
