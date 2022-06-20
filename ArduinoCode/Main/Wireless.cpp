#include "Wireless.h"
#include "MP3.h"
#include "Servos.h"

// globals initialization
boolean bluetoothConnected = false;
boolean wifiConnected = false;
boolean wifiInfoReceived = false;
String ssid = "";
String pass = "";
String command = "";
String weatherJSON = "";

// objects
BluetoothSerial SerialBT;
HTTPClient http;

// BluetoothSerial library is event-based - so this function, paired with SerialBT.register_callback, acts like an Interrupt Service Routine
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  // this is the closest thing we have to checking  connection status,
  // but it's not a true connection check
  if (event == ESP_SPP_START_EVT) {
    Serial.println("Bluetooth started");
//    bluetoothConnected = true;
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
      readChar = SerialBT.read(); // skip '$'
      while (SerialBT.available()) {
         Serial.println("reading audio command..");
        command += readChar;
        readChar = SerialBT.read();
      }
      command += readChar; // add last char that was read
      Serial.print("Command received: "); Serial.println(command);
      handleCommand(command);
      command = "";
    }
    if (readChar == ';') {
      // receive signal confirming bluetooth connection
      Serial.println("Bluetooth connection established");
      bluetoothConnected = true;
      LCDPrintSmile(); // smiley face :)
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

void handleCommand(String command) {
  if (command.equals("goodbye")) {
    Serial.println("goodbye command");
    playMP3(1);
  }
  if (command.equals("hello")) {
    Serial.println("hello command");
    playMP3(2);
  }
  if(command.equals("forward")){
    Serial.println("forward command");
    playMP3(3);
    changeState(forward, 5000);
  }
  if(command.equals("backward")){
    Serial.println("backward command");
    playMP3(3);
    changeState(backward, 5000);
  }
  if(command.equals("stop")){
    Serial.println("stop command");
    playMP3(3);
    changeState(idle, 0);
  }
//  if(command.equals("joke")) {
//    // 004 through 007 are jokes, random is exclusive
//    playRandom(4, 8);
//  }
//  if(command.equals("sing")) {
//    // 008 through 013 are jokes, random is exclusive
//    playRandom(8, 14);
//  }
}

void playRandom(long minimum, long maximum) {
  playMP3(random(minimum, maximum));
}

void bluetoothInit() {
  SerialBT.register_callback(callback);
  if (!SerialBT.begin("NIKO")) {
    Serial.println("Error in starting Bluetooth");
    // exit(1);
  } else {
    Serial.println("Bluetooth initialized");
//    while (!bluetoothConnected) {
//      Serial.println("Waiting for bluetooth connection...");
//      delay(1000);
//    }
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
  if (WiFi.status() == WL_CONNECTED) {
    LCDPrintSmile();
    wifiConnected = true;
  }
  else {
    LCDPrint("WiFi timed out", ":(");
    ssid = "";
    pass = "";
  }
}

void callWeatherAPI(String* payload) {
  LCDPrint("Fetching Weather", "Data...");
  if (wifiConnected) {
    http.begin("http://api.openweathermap.org/data/2.5/forecast?q=amherst,US&cnt=3&appid=db70af7b7584ff5dca7652af19201a48");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      *payload = http.getString();
      Serial.println("Weather Data String:");
      Serial.println(*payload);
      http.end();
    }
  } else {
    LCDPrint("No WiFi,", "no weather :(");
  }
}

struct WeatherData deserializeWeatherJSON(String* json) {
  DynamicJsonDocument doc(1280);
  DeserializationError error = deserializeJson(doc, *json);

  if (error) {
    LCDPrint("Error with", "getting weather");
    struct WeatherData errorData = {0, ""};
    return errorData;
  }

  JsonArray list = doc["list"];

  JsonObject list_1 = list[1];
  JsonObject list_1_main = list_1["main"];
  float list_1_main_temp = list_1_main["temp"]; // 282.85

  JsonObject list_2 = list[2];
  JsonObject list_2_weather_0 = list_2["weather"][0];
  const char* list_2_weather_0_description = list_2_weather_0["description"]; // "light rain"

  struct WeatherData weatherData = { (int)((9.0/5.0)*(list_1_main_temp - 273.0) + 32.0), list_2_weather_0_description }; // placeholder
  return weatherData;
}

void displayWeather() {
  callWeatherAPI(&weatherJSON);
  struct WeatherData deserializedData = deserializeWeatherJSON(&weatherJSON);
  if (deserializedData.temp != 0) {
    char tempBuf[30];
    char digitBuf[10];
    const char* temp = "Temp: ";
    strcpy(tempBuf, temp);
    strcat(tempBuf, itoa(deserializedData.temp, digitBuf, 10));
    
    char descBuf[30];
    const char* desc = "Desc: ";
    strcpy(descBuf, desc);
    strcat(descBuf, deserializedData.description);
    LCDPrint(tempBuf, descBuf);
  }
}
