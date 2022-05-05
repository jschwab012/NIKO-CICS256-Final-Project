#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
Adafruit_SSD1306 lcd(128, 64);
const char* mdns_name = "pcdav"; // !!! change this to your own unique name please
WebServer server(80);  // define server object, at port 80
void on_home() { server.send(200, "text/html", "<h1>Hello World!</h1>"); }
void setup(void){
  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C); lcd.setTextColor(WHITE); lcd.clearDisplay();
  lcd.display(); 
  WiFi.mode(WIFI_STA); // set ESP in STATION mode
  WiFi.begin("CICS_makerspace", "makerspace"); // this is the WiFi in classroom
  lcd.setCursor(0,0); lcd.print("Connecting..."); lcd.display();
  while(WiFi.status() != WL_CONNECTED) { delay(500); }
  lcd.clearDisplay(); lcd.setCursor(0,0); lcd.print("Connected.\nIP:");
  lcd.println(WiFi.localIP()); lcd.display(); // print out assigned IP address
  lcd.setCursor(0,30); lcd.println("Register mDNS..."); lcd.display();
  if (MDNS.begin(mdns_name)) {  // register mDNS name
    lcd.println("success."); lcd.print(mdns_name); lcd.print(".local/"); lcd.display();
  } else { lcd.print("failed."); lcd.display(); }

  server.on("/", on_home);  // home callback function
  server.on("/inline", [](){server.send(200, "text/html", "<h1>Inline callback works too!</h1>");});
  server.begin();  // starts server
}
void loop(void){
  server.handleClient();  // handle client requests, must call frequently
}
