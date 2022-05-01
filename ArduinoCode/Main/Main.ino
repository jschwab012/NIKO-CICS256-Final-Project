#include "I2C_Devices.h"
#include "Wireless.h"

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
  if (bluetoothConnected) {
    bluetoothReadWifiInfo();
    if (wifiInfoReceived) {
       wifiInit();
    } else {
    Serial.println("WiFi cannot be initialized - missing ssid or password");
    }
  } else {
    Serial.println("Bluetooth connection failed");
  }
}

uint8_t gestureData;
void loop() {
  // TODO: Confirm whether Wire.begin() is necessary here (don't think it is...?)
}
