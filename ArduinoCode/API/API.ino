#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WifiMulti.h>
#include <HTTPClient.h>
#include "arduino_secrets.h"
Adafruit_SSD1306 lcd(128, 64);
char ssid[] = "yep";
char pass[] = "123456789";
WiFiMulti wifiMulti;

char* weatherHost = "http://api.openweathermap.org/data/2.5/forecast?id=524901&appid=";
void setup(void){
  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C); lcd.setTextColor(WHITE); lcd.clearDisplay();
  lcd.display(); 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // set ESP in STATION mode
  wifiMulti.addAP(ssid, pass);

  // wait for WiFi connection
  Serial.print("Waiting for WiFi to connect...");
  while ((wifiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");
  
  
}
void loop(void){
  if((wifiMulti.run() == WL_CONNECTED)) {
    HTTPClient weatherClient;
    
    strcat(weatherHost, SECRET_WEATHER);
    weatherClient.begin(weatherHost);
    int httpCode = weatherClient.GET();
  
    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  
        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = weatherClient.getString();
            Serial.println(payload);
        }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", weatherClient.errorToString(httpCode).c_str());
    }
  
    weatherClient.end();

  }
  
    delay(5000);
}
