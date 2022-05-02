#include "I2C_Devices.h"
#include "Wireless.h"
#include "Servos.h"

/**
 * Interacting with each I2C device:
 * Each device's corresponding [devicename]Init() method should be called in setup()
 * 1. Print to center LCD: LCDPrint("message1", "message2") or LCDPrint("message1") or LCDPrint(NULL, "message2") (time to print 2 messages: ~40ms)
 * 2. Eye (OLED) functions: Call the corresponding method and if it takes in an eye param, call like so: displayEyeMessage(message, 'r') (time to print: 27ms)
 * 3. Edge Sensor: call EDGE_SENSOR.readRangeContinuousMillimeters() directly (time to read: 32ms)
 * 4. IR Obstacle avoidance sensor: call digitalRead(IR_PIN) directly (time to read: ~0ms);
 * 5. Gesture sensor (this one is weirder because of how the library works): call paj7620ReadReg(GESTURE_ADDR, 1, &gestureData) (time to read: ~0ms)
 * 6. Gyro: still figuring out best way to do reads
 */

//enum State { IDLE };
//State state = IDLE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting setup process");

  // initialize I2C devices
  I2CInit();

  // setup connection
  bluetoothInit();

  pinMode(0, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  servosInit();
}

void loop() {
//  unsigned long startTime = millis();
//  LCDPrint("This is a", "test print!");
////  displayEyeMessage("This\ is a test print for the right eye!", &EYE_R);
//  displayEyeMessage("This is a test print for the left eye!", &EYE_L);
////  EDGE_SENSOR.readRangeContinuousMillimeters();
////  digitalRead(IR_PIN);
////  paj7620ReadReg(GESTURE_ADDR, 1, &gestureData);
//  Serial.print("Edge sensor reading: "); Serial.println(EDGE_SENSOR.readRangeContinuousMillimeters());
//  Serial.print("IR sensor reading: "); Serial.println(digitalRead(IR_PIN));
//  Serial.print("Gesture sensor reading: "); Serial.print(paj7620ReadReg(GESTURE_ADDR, 1, &gestureData)); Serial.print(" "); Serial.println(gestureData);
//  unsigned long endTime = millis();
//  // gyro would be here if I knew how to read it
//  Serial.print("Executing all scan operations took: "); Serial.println(endTime - startTime);
//  delay(2000);

  Serial.println(moveState);
 if(digitalRead(0) == LOW){
    moveState = forward;
  }
  else if(digitalRead(34) == LOW){
    moveState = backward;
  }
  else if(digitalRead(35) == LOW){
    moveState = idle;
  }
  handleMovement();
}
