#include "Wireless.h"
#include "I2C_Devices.h"

// globals initialization
boolean bluetoothConnected = false;
boolean wifiConnected = false;
boolean wifiInfoReceived = false;
String ssid = "";
String pass = "";

// objects
BluetoothSerial SerialBT;

// BluetoothSerial library is event-based - so this function, paired with SerialBT.register_callback, acts like an Interrupt Service Routine
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  // this is the closest thing we have to checking  connection status,
  // but it's not a true connection check
  if (event == ESP_SPP_START_EVT) {
    Serial.println("Bluetooth connection established");
    bluetoothConnected = true;
  }
  if (event == ESP_SPP_DATA_IND_EVT) {
    char readChar = SerialBT.read();
    if (readChar == '?') {
      // read ssid (assumes SSID is received before password)
      LCDPrint("Reading WiFi", "Information...");
      readChar = SerialBT.read(); // skip '?'
      while (readChar != '@') {
        ssid += readChar;
        readChar = SerialBT.read();
      }
      if (readChar == '@') { // read pass
        readChar = SerialBT.read(); // skip '@'
        while (SerialBT.available()) {
          //        Serial.println("reading pass..");
          pass += readChar;
          readChar = SerialBT.read();
        }
        pass += readChar; // add last char that was read
      }
      wifiInfoReceived = !ssid.equals("") && !pass.equals("");
      if (wifiInfoReceived) {
        Serial.println("WiFi Info received:");
        Serial.println("ssid: " + ssid);
        Serial.println("pass: " + pass);
        Serial.println("");
      } else {
        Serial.println("WiFi info not received:");
        Serial.println("current ssid string: " + ssid);
        Serial.println("current pass string: " + pass);
      }
      wifiInit();
    }
    if (readChar == '$') {
      // receive audio input from Processing
    }
  }
  //  if (event == ESP_SPP_INIT_EVT) {
  //    Serial.println("Init event detected");
  //  }
  //  if (event == 0 || event == 1 || event == 8 || event == 26 ||
  //      event == 27 || event == 28 || event == 29 || event == 30 ||
  //      event == 31 || event == 33 || event == 34 || event == 35) {
  //        Serial.println(event);
  //   }
}

void bluetoothInit() {
  SerialBT.register_callback(callback);
  if (!SerialBT.begin("NIKO")) {
    Serial.println("Error in starting Bluetooth");
    // exit(1);
  } else {
    Serial.println("Bluetooth started");
    while (!bluetoothConnected) {
      Serial.println("Waiting for bluetooth connection...");
      delay(1000);
    }
    //  TODO: implement better connection check
  }
}

void wifiInit() {
  char ssidArr[ssid.length() + 1];
  char passArr[pass.length() + 1];
  ssid.toCharArray(ssidArr, ssid.length() + 1);
  pass.toCharArray(passArr, pass.length() + 1);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // clear existing connections
  WiFi.begin(ssidArr, passArr);
  Serial.println("ssidArr and passArr:");
  // for debugging:
  //  for (int i = 0; i < ssid.length(); i++) {
  //    Serial.print(ssidArr[i]);
  //  }
  //  Serial.println("");
  //  for (int i = 0; i < pass.length(); i++) {
  //    Serial.print(passArr[i]);
  //  }
  int attempts = 0; // make sure wifi connection loop times out
  LCDPrint("Attempting WiFi", "connection...");
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    Serial.println("Waiting for WiFi connection...");
    delay(1000);
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) wifiConnected = true;
  else LCDPrint("WiFi timed out", ":(");
}
