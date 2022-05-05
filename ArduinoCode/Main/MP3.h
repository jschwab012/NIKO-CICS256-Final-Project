#ifndef MP3_H
#define MP3_H

//Include libraries
#include <MD_YX5300.h>
#include <SoftwareSerial.h>

// Connections for serial interface to the YX5300 module
extern const uint8_t ARDUINO_RX;    // connect to TX of MP3 Player module
extern const uint8_t ARDUINO_TX;    // connect to RX of MP3 Player module

extern SoftwareSerial  MP3Stream;
extern MD_YX5300 mp3;

//Functions
void initMP3();
void playMP3(uint8_t trackNum);

#endif
