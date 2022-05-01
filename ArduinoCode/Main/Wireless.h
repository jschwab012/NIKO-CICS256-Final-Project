/**
 * includes, constants, and functions to handle WiFi + Bluetooth
 */

#ifndef WIRELESS_H
#define WIRELESS_H

// libraries
#include <Arduino.h>
#include "BluetoothSerial.h"
#include <WiFi.h>

// globals
extern String ssid;
extern String pass;
extern boolean bluetoothConnected;
extern boolean wifiInfoReceived;
extern boolean wifiConnected;

// objects
extern BluetoothSerial SerialBT;

// functions
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
void bluetoothInit(); // begin SerialBT 
void bluetoothReadWifiInfo(); // wait for WiFi info from the Processing interface
void wifiInit(); // start WiFi in station mode and connect using ssid + pass initialized in bluetoothReadWifiInfo()

#endif
