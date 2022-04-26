#include <ESP32Servo.h>
#define POT A0

Servo servo1; 
Servo servo2; 
Servo servo3;
Servo servo4;
void setup() {
  Serial.begin(115200);
  servo1.attach(23);
  servo2.attach(18);
  servo3.attach(15); 
  servo4.attach(2);
  
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

int moveDegree = 45;
int leftL = 90;
int leftF = 90;
int rightL = 90-moveDegree;
int rightF = 90-moveDegree;
int leftV = 1;
int rightV = 1;
void loop() {
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
  if(leftL == 90+moveDegree || leftL == 90){
    leftV = -leftV;
  }
  if(rightL == 90-moveDegree || rightL == 90){
    rightV = -rightV;
  }

  servo1.write(leftL);
  servo2.write(rightL);
  servo3.write(leftF);
  servo4.write(rightF);
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
  delay(5);
}
