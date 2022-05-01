#include <ESP32Servo.h>
#include <Wire.h>

#include <VL53L0X.h>
VL53L0X sensor;

// The parameters below can be modified
#define PHI_START   45
#define PHI_END     120
#define PHI_STEP    5

#define THETA_START 75
#define THETA_END   135
#define THETA_STEP  5

#define MAX_DISTANCE   500
#define HIGH_ACCURACY  1

// The parameters below should NOT need to be modified
#define ARM_LENGTH 30
#define SERVO1 23
#define SERVO2 18

Servo Phi;
Servo Theta;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Phi.attach(SERVO1);
  Theta.attach(SERVO2);

  Phi.write(90); // set to 90 degree resting position
  Theta.write(90); // set to 90 degree resting position)
  
  Serial.println(F("press any key to start"));
  while(!Serial.available());
  Serial.read();

  sensor.init();
  sensor.setTimeout(500);

#if HIGH_ACCURACY
  sensor.setMeasurementTimingBudget(200000); 
#endif
  Serial.println("");
  Serial.println(F("# ready")); // first line of the output
}

void loop() {
  int p, t;
  int nt, np;
  for(t=THETA_START, nt=0;t<THETA_END;t+=THETA_STEP, nt++) {
    Theta.write(t);
    for(p=PHI_START, np=0;p<PHI_END;p+=PHI_STEP, np++) {
      Phi.write(p);
      if(p==PHI_START) delay(500); // when a new scan line begins, wait more for motor to move
      else delay(PHI_STEP*5); // wait for motor to move
      
      float d = sensor.readRangeSingleMillimeters();
      if(d>MAX_DISTANCE || sensor.timeoutOccurred()) d=MAX_DISTANCE;
      float phi = p/180.f*3.14159f;
      float theta = t/180.f*3.14159f;
      float x = d*sin(theta)*cos(phi);
      float y = d*sin(theta)*sin(phi);
      float z = d*cos(theta);
      String vertex_line = "v ";
      vertex_line+=(x-ARM_LENGTH*sin(phi));
      vertex_line+=" ";
      vertex_line+=(y+ARM_LENGTH*cos(phi));
      vertex_line+=" ";
      vertex_line+=z;
      Serial.println(vertex_line);
    }
  }
  // reset servos to resting position
  Theta.write(90);
  Phi.write(90);
  
  for(t=0;t<nt-1;t++) {
    for(p=0;p<np-1;p++) {
      int index=t*np+p+1;
      String face_line = "f ";
      face_line+=index;
      face_line+=" ";
      face_line+=(index+1);
      face_line+=" ";
      face_line+=(index+np+1);
      face_line+=" ";
      face_line+=(index+np);
      Serial.println(face_line);
      
    }
  }
  Serial.println(F("# end")); // last line of the output
  while(1){delay(1);} // scan over
}

