#include "I2C_Devices.h"

/**
 * Interacting with each I2C device:
 * Each device's corresponding [devicename]Init() method should be called in setup()
 * 1. Print to center LCD: LCDPrint("message1", "message2") or LCDPrint("message1") or LCDPrint(NULL, "message2")
 * 2. Eye (OLED) functions: Call the corresponding method and if it takes in an eye param, call like so: displayEyeMessage(message, 'r') {
 * 3. Edge Sensor: call EDGE_SENSOR.readRangeContinuousMillimeters() directly
 * 4. IR Obstacle avoidance sensor: call digitalRead(IR_PIN) directly
 * 5. Gesture sensor (this one is weirder because of how the library works): call paj7620ReadReg(GESTURE_ADDR, 1, &gestureData)
 * 6. Gyro: still figuring out best way to do reads
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("starting");
  LCDInit();
  eyesInit();
  edgeSensorInit();
  IRObstInit();
  gestureInit();
  gyroInit();
}

uint8_t gestureData;
void loop() {
  // TODO: Confirm whether Wire.begin() is necessary here (don't think it is...?)
}
