#include "Servos.h"

// globals initialization
Movement state = idle;
const int moveDegree = 45;
const int leftL = 90;
const int leftF = 90;
const int rightL = 90-moveDegree;
const int rightF = 90-moveDegree;
const int leftV = 1;
const int rightV = 1;

// objects
Servo servos[4];

// servo functions
void servosInit() {
  // TODO: make these pin nums global variables
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

void handleMovement() {
  
}
