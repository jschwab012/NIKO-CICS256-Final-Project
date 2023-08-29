#include "I2C_Devices.h"
#include "Wireless.h"
#include "Servos.h"
#include "MP3.h"

/**
 * Interacting with each I2C device:
 * Each device's corresponding [devicename]Init() method shoulhd be called in setup()
 * 1. Print to center LCD: LCDPrint("message1", "message2") or LCDPrint("message1") or LCDPrint(NULL, "message2") (time to print 2 messages: ~40ms)
 * 2. Eye (OLED) functions: Call the corresponding method and if it takes in an eye param, call like so: displayEyeMessage(message, 'r') (time to print: 27ms)
 * 3. Edge Sensor: call EDGE_SENSOR.readRangeContinuousMillimeters() directly (time to read: 32ms)
 * 4. IR Obstacle avoidance sensor: call digitalRead(IR_PIN) directly (time to read: ~0ms);
 * 5. Gesture sensor (this one is weirder because of how the library works): call paj7620ReadReg(GESTURE_ADDR, 1, &gestureData) (time to read: ~0ms)
 * 6. Gyro: still figuring out best way to do reads
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting setup process");

  // initialize I2C devices
  I2CInit();
  initMP3();

  // setup connection
  bluetoothInit();
  
  pinMode(0, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  servosInit();
}
void loop(){
  //Main sensors (IR, light)
  handleIRDetection();
  handleEdgeDetection();

  //Secondary sensors
  handleGestures();

  //Movement
  handleMovement();
}
