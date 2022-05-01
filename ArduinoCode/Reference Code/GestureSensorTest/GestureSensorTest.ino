#include <Wire.h>
#include "paj7620.h"

void setup()
{
  Serial.begin(9600);
  paj7620Init();
}

void loop()
{
  
  uint8_t data = 0; // Read Bank_0_Reg_0x43/0x44 for gesture result.

  paj7620ReadReg(0x43, 1, &data);
//  Serial.println(data);

  if (data == GES_UP_FLAG)
  {
    Serial.println("GES_UP_FLAG !");
  }

  if (data == GES_DOWN_FLAG)
  {
    Serial.println("GES_DOWN_FLAG !");
  }

  if (data == GES_FORWARD_FLAG)
  {
    Serial.println("GES_FORWARD_FLAG !");
  }

  if (data == GES_BACKWARD_FLAG)
  {
    Serial.println("GES_BACKWARD_FLAG !");
  }

  if (data == GES_RIGHT_FLAG)
  {
    Serial.println("GES_RIGHT_FLAG !");
  }

  if (data == GES_LEFT_FLAG)
  {
    Serial.println("GES_LEFT_FLAG !");
  }

  if (data == GES_FORWARD_FLAG){
    Serial.println("GES_FORWARD_FLAG !");
  }
  
  if (data == GES_BACKWARD_FLAG)
  {
    Serial.println("GES_BACKWARD_FLAG !");
  }
  
  if (data == GES_CLOCKWISE_FLAG){
    Serial.println("GES_CLOCKWISE_FLAG !");
  }
  
//  if (data == GES_COUNTER_CLOCKWISE_FLAG){
//    Serial.println("GES_COUNTER_CLOCKWISE_FLAG !");
//  }
  
  if (data == GES_WAVE_FLAG){
    Serial.println("GES_WAVE_FLAG !");
  }
}
