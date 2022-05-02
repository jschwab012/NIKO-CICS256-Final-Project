#ifndef SERVOS_H
#define SERVOS_H

// libraries
#include <ESP32Servo.h>

// globals
typedef enum {idle=0, forward, backward, turnRight, turnLeft} Movement;
extern Movement moveState;
extern const int moveDegree;
extern int leftL;
extern int leftF;
extern int rightL;
extern int rightF;
extern int leftV;
extern int rightV;
extern int delayTime;
extern int currTime;

// objects
extern Servo servos[4];

// functions
void servosInit();
void handleMovement();

#endif
