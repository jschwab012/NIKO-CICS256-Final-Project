#include "Wireless.h"

// globals initialization
boolean bluetoothConnected = false;
boolean wifiConnected = false;
boolean wifiInfoReceived = false;
String ssid = "";
String pass = "";
String weatherJSON = "";

// objects
BluetoothSerial SerialBT;
HTTPClient http;

// BluetoothSerial library is event-based - so this function, paired with SerialBT.register_callback, acts like an Interrupt Service Routine
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  // this is the closest thing we have to checking  connection status,
  // but it's not a true connection check
//  if (event == ESP_SPP_START_EVT) {
//    Serial.println("Bluetooth connection established");
//    bluetoothConnected = true;
//  }
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
    if (readChar == ';') {
      // receive signal confirming bluetooth connection
      Serial.println("Bluetooth connection established");
      bluetoothConnected = true;
      LCDPrint("               _", " _____________/ "); // smiley face :)
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
//    while (!bluetoothConnected) {
//      Serial.println("Waiting for bluetooth connection...");
//      Serial.println(bluetoothConnected);
//      delay(2000);
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
  if (WiFi.status() == WL_CONNECTED) wifiConnected = true;
  else LCDPrint("WiFi timed out", ":(");
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
  DynamicJsonDocument doc(3072);
  DeserializationError error = deserializeJson(doc, *json);

  if (error) {
    LCDPrint("Error with", "getting weather");
    struct WeatherData errorData = {0, ""};
    return errorData;
  }

  const char* cod = doc["cod"]; // "200"
  int message = doc["message"]; // 0
  int cnt = doc["cnt"]; // 3

  JsonArray list = doc["list"];

  JsonObject list_0 = list[0];
  long list_0_dt = list_0["dt"]; // 1651568400

  JsonObject list_0_main = list_0["main"];
  float list_0_main_temp = list_0_main["temp"]; // 282.09
  float list_0_main_feels_like = list_0_main["feels_like"]; // 279.61
  float list_0_main_temp_min = list_0_main["temp_min"]; // 281.99
  float list_0_main_temp_max = list_0_main["temp_max"]; // 282.09
  int list_0_main_pressure = list_0_main["pressure"]; // 1017
  int list_0_main_sea_level = list_0_main["sea_level"]; // 1017
  int list_0_main_grnd_level = list_0_main["grnd_level"]; // 990
  int list_0_main_humidity = list_0_main["humidity"]; // 87
  float list_0_main_temp_kf = list_0_main["temp_kf"]; // 0.1

  JsonObject list_0_weather_0 = list_0["weather"][0];
  int list_0_weather_0_id = list_0_weather_0["id"]; // 802
  const char* list_0_weather_0_main = list_0_weather_0["main"]; // "Clouds"
  const char* list_0_weather_0_description = list_0_weather_0["description"]; // "scattered clouds"
  const char* list_0_weather_0_icon = list_0_weather_0["icon"]; // "03n"

  int list_0_clouds_all = list_0["clouds"]["all"]; // 33

  JsonObject list_0_wind = list_0["wind"];
  float list_0_wind_speed = list_0_wind["speed"]; // 4.53
  int list_0_wind_deg = list_0_wind["deg"]; // 103
  float list_0_wind_gust = list_0_wind["gust"]; // 7.96

  int list_0_visibility = list_0["visibility"]; // 10000
  int list_0_pop = list_0["pop"]; // 0

  const char* list_0_sys_pod = list_0["sys"]["pod"]; // "n"

  const char* list_0_dt_txt = list_0["dt_txt"]; // "2022-05-03 09:00:00"

  JsonObject list_1 = list[1];
  long list_1_dt = list_1["dt"]; // 1651579200

  JsonObject list_1_main = list_1["main"];
  float list_1_main_temp = list_1_main["temp"]; // 282.85
  float list_1_main_feels_like = list_1_main["feels_like"]; // 280.71
  float list_1_main_temp_min = list_1_main["temp_min"]; // 282.85
  float list_1_main_temp_max = list_1_main["temp_max"]; // 283.21
  int list_1_main_pressure = list_1_main["pressure"]; // 1016
  int list_1_main_sea_level = list_1_main["sea_level"]; // 1016
  int list_1_main_grnd_level = list_1_main["grnd_level"]; // 990
  int list_1_main_humidity = list_1_main["humidity"]; // 87
  float list_1_main_temp_kf = list_1_main["temp_kf"]; // -0.36

  JsonObject list_1_weather_0 = list_1["weather"][0];
  int list_1_weather_0_id = list_1_weather_0["id"]; // 803
  const char* list_1_weather_0_main = list_1_weather_0["main"]; // "Clouds"
  const char* list_1_weather_0_description = list_1_weather_0["description"]; // "broken clouds"
  const char* list_1_weather_0_icon = list_1_weather_0["icon"]; // "04d"

  int list_1_clouds_all = list_1["clouds"]["all"]; // 67

  JsonObject list_1_wind = list_1["wind"];
  float list_1_wind_speed = list_1_wind["speed"]; // 4.16
  int list_1_wind_deg = list_1_wind["deg"]; // 110
  float list_1_wind_gust = list_1_wind["gust"]; // 7.59

  int list_1_visibility = list_1["visibility"]; // 10000
  int list_1_pop = list_1["pop"]; // 0

  const char* list_1_sys_pod = list_1["sys"]["pod"]; // "d"

  const char* list_1_dt_txt = list_1["dt_txt"]; // "2022-05-03 12:00:00"

  JsonObject list_2 = list[2];
  long list_2_dt = list_2["dt"]; // 1651590000

  JsonObject list_2_main = list_2["main"];
  float list_2_main_temp = list_2_main["temp"]; // 284.48
  float list_2_main_feels_like = list_2_main["feels_like"]; // 284.04
  float list_2_main_temp_min = list_2_main["temp_min"]; // 284.48
  float list_2_main_temp_max = list_2_main["temp_max"]; // 284.48
  int list_2_main_pressure = list_2_main["pressure"]; // 1014
  int list_2_main_sea_level = list_2_main["sea_level"]; // 1014
  int list_2_main_grnd_level = list_2_main["grnd_level"]; // 988
  int list_2_main_humidity = list_2_main["humidity"]; // 91
  int list_2_main_temp_kf = list_2_main["temp_kf"]; // 0

  JsonObject list_2_weather_0 = list_2["weather"][0];
  int list_2_weather_0_id = list_2_weather_0["id"]; // 500
  const char* list_2_weather_0_main = list_2_weather_0["main"]; // "Rain"
  const char* list_2_weather_0_description = list_2_weather_0["description"]; // "light rain"
  const char* list_2_weather_0_icon = list_2_weather_0["icon"]; // "10d"

  int list_2_clouds_all = list_2["clouds"]["all"]; // 100

  JsonObject list_2_wind = list_2["wind"];
  float list_2_wind_speed = list_2_wind["speed"]; // 4.17
  int list_2_wind_deg = list_2_wind["deg"]; // 118
  float list_2_wind_gust = list_2_wind["gust"]; // 8.96

  int list_2_visibility = list_2["visibility"]; // 10000
  float list_2_pop = list_2["pop"]; // 0.91

  float list_2_rain_3h = list_2["rain"]["3h"]; // 0.85

  const char* list_2_sys_pod = list_2["sys"]["pod"]; // "d"

  const char* list_2_dt_txt = list_2["dt_txt"]; // "2022-05-03 15:00:00"

  JsonObject city = doc["city"];
  long city_id = city["id"]; // 5145695
  const char* city_name = city["name"]; // "Amherst"

  float city_coord_lat = city["coord"]["lat"]; // 41.3978
  float city_coord_lon = city["coord"]["lon"]; // -82.2224

  const char* city_country = city["country"]; // "US"
  int city_population = city["population"]; // 12021
  int city_timezone = city["timezone"]; // -14400
  long city_sunrise = city["sunrise"]; // 1651573406
  long city_sunset = city["sunset"]; // 1651624077

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
