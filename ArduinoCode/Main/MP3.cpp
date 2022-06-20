#include "MP3.h"

// Connections for serial interface to the YX5300 module
const uint8_t ARDUINO_RX = 15;    // connect to TX of MP3 Player module
const uint8_t ARDUINO_TX = 13;    // connect to RX of MP3 Player module

SoftwareSerial  MP3Stream(ARDUINO_RX, ARDUINO_TX);
MD_YX5300 mp3(MP3Stream);

void initMP3(){
  MP3Stream.begin(MD_YX5300::SERIAL_BPS);
  mp3.begin();
}

void playMP3(uint8_t trackNum){
  Serial.print("Playing track num "); Serial.println(trackNum);
  mp3.playTrack(trackNum);
  delay(500);
}
