#include <Servo.h>
#include <Stepper.h>
#include <Debounce.h>

#define in1 8
#define in2 9
#define in3 10
#define in4 11

#define RED_BUTTON 2
#define BLACK_BUTTON 4

#define GREEN_LED 3

short angS1, stepsPerRotation = 64,flag = 0;
float pastAngle = 90;
bool enable = true;

Servo s1;
Stepper sP1(stepsPerRotation,in1 ,in3 ,in2 ,in4);
Debounce WHITE_BUTTON(2);


void setup(){
//------- Serial stuff ------  
  Serial.begin(9600);
  
 // -------- Servo ----------- 
  s1.attach(4);// assign the port
  angS1 = 90;
  s1.write(angS1);
  
//------ Stepp motor --------
  
  sP1.setSpeed(500);// RPM

// -- Setting of the buttons-

  pinMode(RED_BUTTON,INPUT_PULLUP);
  pinMode(BLACK_BUTTON,INPUT_PULLUP);

//------- State_Led -------------

  pinMode(GREEN_LED,OUTPUT);// if it is off, means that you  can change the position of the motor
 
}
void loop(){
  
      if(WHITE_BUTTON.bounceless() == false){
        setPositionSteppMotor(digitalRead(BLACK_BUTTON),digitalRead(RED_BUTTON));
        digitalWrite(GREEN_LED,LOW);
         s1.write(90);
        
      }else{
         digitalWrite(GREEN_LED,HIGH);
            if(Serial.available() > 0 and WHITE_BUTTON.bounceless()== true){
                mainControll();
             }      
      }
}

void steppAngleMotion(float angle){
   
   float currentAngle = angle; 
   float angleToSpin = (currentAngle - pastAngle)/360;
   short sense = 1;

   Serial.print("pastAngle: ");Serial.println(pastAngle);
   Serial.print("currentAngle: ");Serial.println(currentAngle);
   Serial.print("angleToSpin: ");Serial.println(angleToSpin);

   pastAngle = currentAngle;

   if(angleToSpin < 0){
     angleToSpin *= -1;
     sense *= -1; 
   }
  
     for(int i  = 0; i < (32 * angleToSpin); i++){
        sP1.step(sense*stepsPerRotation);
      }
      
}


void setPositionSteppMotor(bool right,bool left){
      if(right == 1 && left == 0){
        sP1.step(stepsPerRotation); 
      }else if(right == 0 && left == 1){
        sP1.step(-1 *stepsPerRotation);  
      }      
}

void mainControll(){

  String info; float anguloMotor, anguloServo;
             if(enable){
                info = Serial.readStringUntil('\n') + '\n'; 
             }
             
             const char* infoEmC = {info.c_str()};
             char anguloMotorString[4],anguloServoString[4];
             short spP = 0; 
             
             for(int i = 0; i < sizeof(anguloMotorString); i++){   
                if(infoEmC[i] != ' '){
                   anguloMotorString[i] = infoEmC[i];
                   spP++; 
                }else{
                   anguloMotorString[i] = '\0';
                   break;
                }
             }

             spP += 1;

             for(int i = 0; i < sizeof(anguloServoString); i++){   
                if(infoEmC[spP] != '\n'){
                   anguloServoString[i] = infoEmC[spP];
                   spP++; 
                }else{
                   anguloServoString[i] = '\0';
                   break;
                }
             }
              
             anguloMotor = atof(anguloMotorString);
             anguloServo = atof(anguloMotorString);
            Serial.print("anguloServo: "); Serial.println(anguloServo);

              /*     
               if(anguloMotor > 0){ // aqui deixamos maior que zero por conta de uns bugs misteriosos
                steppAngleMotion(anguloMotor);
               }
               */
                static float valorPassado = 90, valorAtual = 90;
                valorAtual = anguloServo;
                //delay(500);             
                float diferenca = abs(valorAtual - valorPassado);              
                      
               if(diferenca >= 10){  
                     if(anguloServo < 0.1){
                      //s1.write(0.1);
                     }else if(anguloServo >= 0.1){// aqui deixamos maior que zero por conta de uns bugs misteriosos
                      enable = false; 
                      s1.write(anguloServo);
                      enable = true;
                     }
                     valorPassado = valorAtual;
               }
               
}
