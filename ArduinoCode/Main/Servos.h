#ifndef SERVOS_H
#define SERVOS_H

// libraries
#include <Arduino.h>
#include <ESP32Servo.h>

// globals
typedef enum {idle=0, forward, backward, turnRight, turnLeft} Movement;
extern volatile Movement moveState;
extern const int moveDegree;
extern const int servoPins[4];
extern int leftL;
extern int leftF;
extern int rightL;
extern int rightF;
extern int leftV;
extern int rightV;
extern int delayTime;
extern int currTime;
extern boolean stateChanged;
extern int delayState;
extern int idleTimer;
extern boolean idleTimerFlag;

// objects
extern Servo servos[4];

// functions
void servosInit();
boolean changeState(Movement newState, int t);
void overrideState(Movement newState);
void handleStateDelay(int t);
void handleMovement();

#endif
