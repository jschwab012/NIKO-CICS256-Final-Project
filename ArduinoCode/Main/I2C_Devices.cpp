#include "I2C_Devices.h"
#include "Servos.h"
#include "Wireless.h"

// globals initialization
const int LCD_ADDR = 0x3F;
const int OLED_ADDR = 0x3C;
const int LIGHT_SENSOR_ADDR = 0x29;
const int IR_PIN = 26;
const int GESTURE_ADDR = 0x43;
const int GYRO_ADDR = 0x68;
uint8_t gestureData = 0;
int prevIRVal = HIGH;
const int edgeFallingThreshold = 400;
const int edgeRisingThreshold = 350;
boolean edgeFallingFlag = false;
int edgeSensorDelay = 0;

// device object initialization
LiquidCrystal_I2C LCD(LCD_ADDR, 16, 2);
Adafruit_SSD1306 EYES(128, 64); // left eye (NIKO's left)
//Adafruit_SSD1306 EYE_R(128, 64); // right eye (NIKO's right)
VL53L0X EDGE_SENSOR; // analog light distance sensor
Adafruit_MPU6050 GYRO; // gyro (auto detects address I think?)

// Big LCD functions
// init LCD
void LCDInit() {
  // initialize LCD
  LCD.init();
  // turn on LCD backlight                      
  LCD.backlight();
}

// function to print messages on either or both lines of center display
void LCDPrint(const char* message1, const char* message2) {
  LCD.clear();
  // set cursor to first column, first row
  LCD.setCursor(0, 0);
  // print message
  LCD.print(message1);
  
  // set cursor to first column, second row
  LCD.setCursor(0,1);
  LCD.print(message2);
}

void LCDPrintSmile() {
  LCDPrint("               _", " _____________/ ");
}

// eye functions (some of these are kinda funky cause most of the time, each eye will do the same thing, but we want the option
// open to being able to manipulate them separately)
// inits both eyes and draws first eye frame
void eyesInit() { 
  // init EYE_L
  EYES.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); // init
  EYES.clearDisplay();         // clear software buffer
  EYES.setTextColor(WHITE);    // set text color
  EYES.display();

  // TODO: draw eyes?
  wakeUp();
}

// various drawing methods (these may need tweaking/repurposing because they might interrupt control flow of script too much?)
// (i.e., the eye animation may look nothing like this functional approach by the end)
void wakeUp() {
  EYES.clearDisplay();
  EYES.fillRect(16, 8, 96, 48, WHITE);
  EYES.fillCircle(90, 32, 12, BLACK);
  EYES.display();
}

// blinks both eyes
void blinkEyes() {
  
}

// displays a message at (0,0) on one or both eye(s)
void displayEyeMessage(const char* message) {
  EYES.clearDisplay();
  EYES.setCursor(0, 0);
  EYES.setTextSize(2);
  EYES.print(message);
  EYES.display();
}

// light (edge) distance sensor functions
// init EDGE_SENSOR (still unsure of why the constructor never needs to be called ¯\_(ツ)_/¯)
void edgeSensorInit() {
  EDGE_SENSOR.init();
  EDGE_SENSOR.setTimeout(500);
}

void handleEdgeDetection() {
  if(millis() > edgeSensorDelay){
    int edgeSensorVal = EDGE_SENSOR.readRangeSingleMillimeters();
    if(edgeSensorVal > edgeFallingThreshold){ //FALLING
      overrideState(backward);
      edgeFallingFlag = true;
    }
    else if(edgeFallingFlag && edgeSensorVal < edgeRisingThreshold){ //RISING
      overrideState(idle);
      edgeFallingFlag = false;
    }
    edgeSensorDelay = millis() + 100;
  }
  
}

// IR obst functions
//void IRAM_ATTR objectDetected() {
//  moveState = backward;
////  Serial.println("object detected");
//}
//void IRAM_ATTR objectUndetected() {
//  moveState = idle;
////  Serial.println("object undetected");
//}
void IRObstInit() {
  pinMode(IR_PIN, INPUT);
//  attachInterrupt(IR_PIN, objectDetected, FALLING);
//  attachInterrupt(IR_PIN, objectUndetected, RISING);
}

void handleIRDetection(){
  int IRVal = digitalRead(IR_PIN);
//  Serial.print("IR: "); Serial.println(IRVal);
  if(IRVal == LOW){ //FALLING
    overrideState(backward);
  }
  else if(prevIRVal == LOW && IRVal == HIGH){ //RISING
    overrideState(idle);
  }
  prevIRVal = IRVal;
}

// gesture sensor functions
void gestureInit() {
  paj7620Init();
}

uint8_t gestureRead() {
  /*
    #define PAJ7620_VAL(val, maskbit)   ( val << maskbit )
    #define GES_RIGHT_FLAG       PAJ7620_VAL(1,0)
    #define GES_LEFT_FLAG       PAJ7620_VAL(1,1)
    #define GES_UP_FLAG         PAJ7620_VAL(1,2)
    #define GES_DOWN_FLAG       PAJ7620_VAL(1,3)
    #define GES_FORWARD_FLAG      PAJ7620_VAL(1,4)
    #define GES_BACKWARD_FLAG     PAJ7620_VAL(1,5)
   */
  return paj7620ReadReg(GESTURE_ADDR, 1, &gestureData);
}

void handleGestures(){
//  Serial.print("gesture error: ");
//  Serial.println(gestureRead());
  gestureRead();
//  Serial.print("Gesture: "); Serial.println(gestureData);
  switch(gestureData){
    case GES_FORWARD_FLAG:{ //Towards the sensor
      changeState(backward, 5000);
      break;
    }
    
    case GES_BACKWARD_FLAG:{
      changeState(forward, 5000); //Away from sensor
      break;
    }
//
//    case GES_UP_FLAG: {
//      displayWeather();
//      break;
//    }

    case GES_DOWN_FLAG: {
      LCDPrint("               _", " _____________/ "); // smiley face :)
      break;
    }
    default:{
      
      break;
    }
  }
}
// gyroscope functions
void gyroInit() {
  GYRO.begin();
}

// initialize I2C devices
void I2CInit() {
  LCDInit();
  Serial.println("LCD initialized");
  LCDPrint("Pairing... Go to", "Processing!");
  
  eyesInit();
  Serial.println("Left eye initialized");
  Serial.println("Right eye initialized");
  
  edgeSensorInit();
  Serial.println("Edge (light) sensor initialized");
  
  IRObstInit();
  Serial.println("Infrared Obstacle Avoidance (front) sensor initialized");
  
  gestureInit();
  Serial.println("Gesture sensor initialized");
  
  gyroInit();
  Serial.println("Gyroscope initialized");
  Serial.println("");
}
