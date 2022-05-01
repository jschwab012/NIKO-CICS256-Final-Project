#include <WiFi.h> // header we need to include for WiFi functions
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>

#define PWM_CHANNEL 0
#define LED 25

const char* ssid = "pdav"; // !!! CHANGE THIS to your name or sth. unique
const char* pass = "12345678"; // !!! NEEDS TO BE AT LEAST 8 CHARACTER LONG
WebServer server(80);  // define server object, at port 80
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED, NEO_GRB+NEO_KHZ800);

void on_home() {
  server.send(200, "text/html", "<h1>Hello World!</h1>");
}

int led_value=0;
int R = 0;
int G = 0;
int B = 0;
void on_get() {
  String html="{\"time\":";
  html+=millis()/1000;
  html+=",\"led_value\":";
  html+=led_value;
  html+="}";
  server.send(200, "text/html", html);
}

void on_set() {
  if(server.hasArg("R") && server.hasArg("G") && server.hasArg("B")) {
    R = server.arg("R");
    G = server.arg("G");
    B = server.arg("B");
//    led_value = server.arg("value").toInt();
    pixel.setPixelColor(0, pixel.Color(R, G, B));
    pixel.show();
//    ledcWrite(PWM_CHANNEL, led_value);
    server.send(200, "text/html", "{\"result\":1}");
  } else { server.send(200, "text/html", "{\"result\":0}"); }
}
void setup(void){
  pinMode(LED, OUTPUT);
//  ledcSetup(PWM_CHANNEL, 2000, 8);
//  ledcAttachPin(LED, PWM_CHANNEL);
  pixel.begin();
  pixel.setBrightness(32);
  WiFi.mode(WIFI_AP); // set ESP in AP mode
  WiFi.softAP(ssid, pass); // sets ssid and password
  server.on("/", on_home);  // home callback function
  server.on("/get", on_get); // get callback function
  server.on("/set", on_set); // set callback function
  server.begin();
}
void loop(void){ server.handleClient();  // handle client requests, must call frequently
}





//#include <WiFi.h> 
//const char* SECRET_SSID = "test_network";
//const char* SECRET_PSW = "482rT*0u";
//
//void setup() {
//  Serial.begin(115200);
//  
//  WiFi.mode(WIFI_STA);
//  WiFi.disconnect();
////  delay(100);
//
//  Serial.println("Setup done");
//}
//
//void initWiFi() {
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(SECRET_SSID, SECRET_PSW);
//  Serial.print("Connecting to WiFi ..");
//  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print('.');
//    delay(1000);
//  }
//  Serial.println(WiFi.localIP());
//}
//
//void loop() {
//  Serial.println("scan start");
//  int n = WiFi.scanNetworks();
//  Serial.println("scan done");
//  if (n == 0) {
//    Serial.println("no networks found");
//  } else {
//    Serial.print(n);
//    Serial.println(" networks found");
//    for (int i = 0; i < n; ++i) {
//      // Print SSID and RSSI for each network found
//      Serial.print(i + 1);
//      Serial.print(": ");
//      Serial.print(WiFi.SSID(i));
//      Serial.print(" (");
//      Serial.print(WiFi.RSSI(i));
//      Serial.print(")");
//      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
//      delay(10);
//    }
//  }
//  Serial.println("");
//  delay(5000);
//}
