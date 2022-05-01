#ifndef I2C_DEVICES_H
#define I2C_DEVICES_H

// libraries
#include <Arduino.h> // must include Arduino.h because we are in .h/.cpp files now
#include <LiquidCrystal_I2C.h>
#include <Adafruit_SSD1306.h>
#include <VL53L0X.h>
#include "paj7620.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h> // dependency for gyro

// address constants for I2C device declarations
extern const int LCD_ADDR; // 0x3F
extern const int OLED_ADDR; // 0x3C
extern const int LIGHT_SENSOR_ADDR; // 0x29
extern const int IR_PIN; // 33 (for now)
extern const int GESTURE_ADDR; // 0x43
//extern const int GYRO_ADDR; // 0x68

// device object declarations
extern LiquidCrystal_I2C LCD; // center LCD
extern Adafruit_SSD1306 EYE_L; // left eye (NIKO's left)
extern Adafruit_SSD1306 EYE_R; // right eye (NIKO's right)
extern VL53L0X SENSOR; // analog light distance sensor
extern Adafruit_MPU6050 GYRO;

// functions
// LCD
void LCDInit();
void LCDPrint(const char* message1, const char* message2);
// eyes (OLED)
void eyesInit();
void wakeUp();
void winkEye(const char eye);
void blinkEyes();
void displayEyeMessage(const char* message, const char eye);
// edge sensor
void edgeSensorInit();
// infrared obstacle avoidance
void IRObstInit();
// gesture
void gestureInit();
// gyro
void gyroInit();

#endif
