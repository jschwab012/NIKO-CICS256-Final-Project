#include "Wireless.h"

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
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("Bluetooth connection established");
    bluetoothConnected = true;
  }
}

void bluetoothInit() {
  SerialBT.register_callback(callback);
  if (!SerialBT.begin("Makerboard")) {
    Serial.println("Error in starting Bluetooth");
//    exit(1);
  } else {
    Serial.println("Bluetooth started");
    // bluetoothConnected = true;
  }
}

void bluetoothReadWifiInfo() {
  char readChar = SerialBT.read();
  if (readChar == '?') { // read ssid (assumes SSID is received before password)
    while (readChar != '@') {
      Serial.println("reading ssid...");
      ssid += readChar;
      readChar = SerialBT.read();
    }
  }
  
  if (readChar == '@') { // read pass
    while (SerialBT.available()) {
      Serial.println("reading pass..");
      pass += readChar;
      readChar = SerialBT.read();
    }
    pass += readChar; // add last char that was read
  }
  wifiInfoReceived = !ssid.equals("") && !pass.equals("");
  if (wifiInfoReceived) {
    Serial.println("WiFi Info received:");
    Serial.println("ssid: " + ssid.substring(1, ssid.length()));
    Serial.println("pass: " + pass.substring(1, pass.length()));
    Serial.println("");
  } else {
    Serial.println("WiFi info not received:");
    Serial.println("current ssid string: " + ssid);
    Serial.println("current pass string: " + pass);
  }
}

void wifiInit() {
  char ssidArr[ssid.length()];
  char passArr[pass.length()];
  ssid.toCharArray(ssidArr, ssid.length());
  pass.toCharArray(passArr, pass.length());
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidArr, passArr);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Waiting for WiFi connection...");
    delay(500);
  }
}
