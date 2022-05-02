#include "I2C_Devices.h"
#include "Wireless.h"
#include "Servos.h"

/**
 * Interacting with each I2C device:
 * Each device's corresponding [devicename]Init() method should be called in setup()
 * 1. Print to center LCD: LCDPrint("message1", "message2") or LCDPrint("message1") or LCDPrint(NULL, "message2") (time to print 2 messages: ~40ms)
 * 2. Eye (OLED) functions: Call the corresponding method and if it takes in an eye param, call like so: displayEyeMessage(message, 'r') (time to print: 27ms)
 * 3. Edge Sensor: call EDGE_SENSOR.readRangeContinuousMillimeters() directly (time to re: 32ms)
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
  LCDInit();
//  if (LCD != NULL) {Serial.println("LCD initialized");} else {Serial.println("Error in initializing LCD");}
  Serial.println("LCD initialized");
  LCDPrint("Pairing... Go to", "Processing!");
  
  eyesInit();
//  if (EYE_L != NULL) {Serial.println("Left eye initialized");} else {Serial.println("Error in initializing left eye");}
//  if (EYE_R != NULL) {Serial.println("Right eye initialized");} else {Serial.println("Error in initializing right eye");}
  Serial.println("Left eye initialized");
  Serial.println("Right eye initialized");
  
  edgeSensorInit();
//  if (EDGE_SENSOR != NULL) {Serial.println("Edge (light) sensor initialized");} else {Serial.println("Error in initializing edge sensor");}
  Serial.println("Edge (light) sensor initialized");
  
  IRObstInit();
  Serial.println("Infrared Obstacle Avoidance (front) sensor initialized");
  
  gestureInit();
  Serial.println("Gesture sensor initialized");
  
  gyroInit();
//  if (GYRO != NULL) {Serial.println("Gyroscope initialized");} else {Serial.println("Error in initializing Gyro");}
  Serial.println("Gyroscope initialized");
  Serial.println("");

  // setup connection
  bluetoothInit();
}

void loop() {
  unsigned long startTime = millis();
  LCDPrint("This is a", "test print!");
//  displayEyeMessage("This is a test print for the right eye!", &EYE_R);
  displayEyeMessage("This is a test print for the left eye!", &EYE_L);
//  EDGE_SENSOR.readRangeContinuousMillimeters();
//  digitalRead(IR_PIN);
//  paj7620ReadReg(GESTURE_ADDR, 1, &gestureData);
  Serial.print("Edge sensor reading: "); Serial.println(EDGE_SENSOR.readRangeContinuousMillimeters());
  Serial.print("IR sensor reading: "); Serial.println(digitalRead(IR_PIN));
  Serial.print("Gesture sensor reading: "); Serial.print(paj7620ReadReg(GESTURE_ADDR, 1, &gestureData)); Serial.print(" "); Serial.println(gestureData);
  unsigned long endTime = millis();
  // gyro would be here if I knew how to read it
  Serial.print("Executing all scan operations took: "); Serial.println(endTime - startTime);
  delay(2000);
}
