/**
 * includes, constants, and functions to handle WiFi + Bluetooth
 */

#ifndef WIRELESS_H
#define WIRELESS_H

// libraries
#include <Arduino.h>
#include "I2C_Devices.h"
#include "BluetoothSerial.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// globals
extern String ssid;
extern String pass;
extern String command;
extern boolean bluetoothConnected;
extern boolean wifiInfoReceived;
extern boolean wifiConnected;
extern String weatherJSON;
struct WeatherData { int temp; const char* description; };

// objects
extern BluetoothSerial SerialBT;
extern HTTPClient http;

// functions
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
void handleCommand(String command);
void playRandom(long min, long max);
void bluetoothInit(); // begin SerialBT 
//void bluetoothReadWifiInfo(); // wait for WiFi info from the Processing interface
void wifiInit(); // start WiFi in station mode and connect using ssid + pass initialized in bluetoothReadWifiInfo()
void callWeatherAPI(String* payload);
struct WeatherData deserializeWeatherJSON(String* weatherJSON);
void displayWeather();
#endif
