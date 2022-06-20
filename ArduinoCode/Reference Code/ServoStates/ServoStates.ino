#include <ESP32Servo.h>
#define POT A0

Servo servos[4];
enum Movement{
  idle=0,
  forward,
  backward,
  turnRight,
  turnLeft
};
Movement moveState = idle;
void setup() {
  Serial.begin(115200);
  servos[0].attach(23);
  servos[1].attach(18);
  servos[2].attach(15); 
  servos[3].attach(2);
  pinMode(0, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  
  servos[0].write(90);
  servos[1].write(90);
  servos[2].write(90);
  servos[3].write(90);
}

int moveDegree = 45;
int leftL = 90;
int leftF = 90;
int rightL = 90-moveDegree;
int rightF = 90-moveDegree;
int leftV = 1;
int rightV = 1;
void loop() {
  handleMovement();
  Serial.println(moveState);
  if(digitalRead(0) == LOW){
    moveState = forward;
  }
  else if(digitalRead(34) == LOW){
    moveState = backward;
  }
  else if(digitalRead(35) == LOW){
    moveState = turnRight;
  }
  else{
    moveState = idle;
  }
}
int delayTime = 0;
int currTime = millis();
void handleMovement(){
  int moveDegree = 45;
  int idleDegree = 90;
//  int angles = {{90, 90, 90, 90}, 
//                {90+moveDegree, 90-moveDegree, 90+moveDegree, 90-moveDegree}};
  if(millis() > currTime){
    switch(moveState){
      case idle:{
        Serial.print(signbit(90 - leftL) ? 1 : -1);
        Serial.print(" ");
        Serial.println(signbit(90 - leftF) ? 1 : -1);
        
        Serial.print(signbit(90 - rightL) ? 1 : -1);
        Serial.print(" ");
        Serial.println(signbit(90 - rightF) ? 1 : -1);
        
        Serial.print(leftL);
        Serial.print(" ");
        Serial.println(leftF);
        Serial.print(rightL);
        Serial.print(" ");
        Serial.println(rightF);
        Serial.println("----");
        if(leftL != 90) {
          leftL += signbit(90 - leftL) ? -1 : 1;
          servos[0].write(leftL);
        }
        if(leftF != 90){
          leftF += signbit(90 - leftF) ? -1 : 1;
          servos[2].write(leftF);
        }
        if(rightL != 90){
          rightL += signbit(90 - rightL) ? -1 : 1;
          servos[1].write(rightL);
        }
        if(rightF != 90){
          rightF += signbit(90 - rightF) ? -1 : 1;
          servos[3].write(rightF);
        }
        
        Serial.println("====================================");
        break;
      }
      case forward:{
        leftL = constrain(leftL, 90, 90+moveDegree);
        leftF = constrain(leftF, 90, 90+moveDegree);
        rightL = constrain(rightL, 90-moveDegree, 90);
        rightF = constrain(rightF, 90-moveDegree, 90);
        leftL += leftV;
        if(leftV < 0){
          leftF += leftV*2;
        }
        else{
          leftF += leftV;
        }
        
        rightL += rightV;
        if(rightV > 0){
          rightF += rightV*2;
        }
        else{
          rightF += rightV;
        }
        if(leftL >= 90+moveDegree || leftL <= 90){
          leftV = -leftV;
          rightV = -rightV;
        }
  //      if(rightL <= 90-moveDegree || rightL >= 90){
  //      }
        servos[0].write(leftL);
        servos[1].write(rightL);
        servos[2].write(leftF);
        servos[3].write(rightF);
        Serial.print(leftV);
        Serial.print(" ");
        Serial.println(rightV);
        Serial.print(leftL);
        Serial.print(" ");
        Serial.println(leftF);
        Serial.print(rightL);
        Serial.print(" ");
        Serial.println(rightF);
        Serial.println("----");
        break;
      }
      case backward:{
        leftL = constrain(leftL, 100-moveDegree, 100);
        leftF = constrain(leftF, 90, 90+moveDegree);
        rightL = constrain(rightL, 80, 80+moveDegree);
        rightF = constrain(rightF, 90-moveDegree, 90);
        leftL += leftV;
        if(leftV > 0){
          leftF += -leftV*2;
        }
        else{
          leftF += -leftV;
        }
        
        rightL += rightV;
        if(rightV < 0){
          rightF += -rightV*2;
        }
        else{
          rightF += -rightV;
        }
        if(leftL <= 100-moveDegree || leftL >= 100){
          leftV = -leftV;
          rightV = -rightV;
        }
  //      if(rightL <= 90-moveDegree || rightL >= 90){
  //      }
        servos[0].write(leftL);
        servos[1].write(rightL);
        servos[2].write(leftF);
        servos[3].write(rightF);
        Serial.print(leftV);
        Serial.print(" ");
        Serial.println(rightV);
        Serial.print(leftL);
        Serial.print(" ");
        Serial.println(leftF);
        Serial.print(rightL);
        Serial.print(" ");
        Serial.println(rightF);
        Serial.println("----");
        break;
      }
      case turnRight:{
        leftL = constrain(leftL, 90, 90+moveDegree+30);
        leftF = constrain(leftF, 90, 90+moveDegree);
        rightL = constrain(rightL, 90-moveDegree, 90);
        rightF = constrain(rightF, 90-moveDegree, 90);
        leftL += leftV;
        if(leftV < 0){
          leftF += leftV*2;
        }
        else{
          leftF += leftV;
        }
        
        rightL += rightV;
        if(rightV > 0){
          rightF += rightV*2;
        }
        else{
          rightF += rightV;
        }
        if(leftL >= 90+moveDegree+30 || leftL <= 90){
          leftV = -leftV;
          rightV = -rightV;
        }
        if(rightL <= 90-moveDegree || rightL >= 90){
  //        leftV = -leftV;
  //        rightV = -rightV;
        }
        servos[0].write(leftL);
        servos[1].write(rightL);
        servos[2].write(leftF);
        servos[3].write(rightF);
        Serial.print(leftV);
        Serial.print(" ");
        Serial.println(rightV);
        Serial.print(leftL);
        Serial.print(" ");
        Serial.println(leftF);
        Serial.print(rightL);
        Serial.print(" ");
        Serial.println(rightF);
        Serial.println("----");
        break;
      }
      case turnLeft:{
        
         break;
      }
      default:{
        
         break;
      }
    }
    currTime = millis() + delayTime;
  }
}
