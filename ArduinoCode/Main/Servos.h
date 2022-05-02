#ifndef SERVOS_H
#define SERVOS_H

// libraries
#include <ESP32Servo.h>

// globals
typedef enum {idle, forward, backward, turnRight, turnLeft} Movement;
extern Movement state;
extern const int moveDegree;
extern const int leftL;
extern const int leftF;
extern const int rightL;
extern const int rightF;
extern const int leftV;
extern const int rightV;

// objects
extern Servo servos[4];

// functions
void servosInit();
void handleMovement();

#endif
