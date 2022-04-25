#include <ESP32Servo.h>
#define POT A0

Servo myservo1; 
Servo myservo2; 
Servo myservo3;
Servo myservo4;
void setup() {
  myservo1.attach(18);
  myservo2.attach(23);
  myservo3.attach(15); 
  myservo4.attach(2);
}

void loop() {
  myservo1.write(analogRead(A0)/4095.0*180);
  myservo2.write(analogRead(A0)/4095.0*180);
  myservo3.write(analogRead(A0)/4095.0*180);
  myservo4.write(analogRead(A0)/4095.0*180);
  delay(5);
}
