#include <ESP32Servo.h>
#define POT A0

Servo servo1; 
Servo servo2; 
Servo servo3;
Servo servo4;
void setup() {
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
void loop() {
  for(int i=90;i<=90+moveDegree;i++){
    Serial.print(i);
    delay(10);
    servo1.write(i);
    servo3.write(i);
    
    servo2.write(90-moveDegree+(i-90));
    servo4.write(90-moveDegree+(i-90));
  }
  for(int i=90+moveDegree;i>=90;i--){

    Serial.print(i);
    delay(10);
    servo1.write(i);
    servo3.write(i);
    
    servo2.write(90-(90+moveDegree-i));
    servo4.write(90-(90+moveDegree-i));
  }
//  servo1.write(analogRead(A0)/4095.0*180);
//  servo2.write(analogRead(A0)/4095.0*180);
//  servo3.write(analogRead(A0)/4095.0*180);
//  servo4.write(analogRead(A0)/4095.0*180);
}
