/**
  Inspiration for GUI from Mitko Nikov @ https://www.youtube.com/watch?v=N753XIKAUPo
*/
import java.util.Collections;
import java.util.ArrayList;
import java.util.Hashtable;

import processing.serial.*;
Serial port;

// GUI variables (in ArrayLists to allow for easy adding of new textboxes/buttons)
int windowWidth = 500;
int windowHeight = 400;
float marginStart = windowWidth / 20;

// setup elements
TEXTBOX comTextbox;
Button comButton;

// WiFi elements
TEXTBOX ssidTextbox;
TEXTBOX pwTextbox;
Button wifiButton;

// font variable
PFont f;

// data variables
String comPort;
String SSID;
String password;

void settings() {
  size(windowWidth, windowHeight); 
}

void setup() {
  printArray(Serial.list());
 // init font/text properties
 f = createFont("Arial", 28, true);
 
 // init custom GUI elements
 initLayout();
}

void draw() {  
  background(150);
  
  // init text
  textFont(f);
  fill(255);
  text("COM Port", marginStart, 35);
  
  // draw setup textboxes
  comTextbox.DRAW();
  
  // draw setup buttons
  comButton.display();
  
   if (!comPort.equals("")) {
    // draw text headers
    textFont(f);
    fill(255);
    text("SSID", marginStart, 185);
    text("Password", marginStart, 285);
    
    // draw textboxes
    ssidTextbox.DRAW();
    pwTextbox.DRAW();
    
    // draw buttons 
    wifiButton.display();
  }
}

void initLayout() {
  // init textbox objects
  comTextbox = new TEXTBOX(marginStart, 50, 250, 35);
  ssidTextbox = new TEXTBOX(marginStart, 200, 250, 35);
  pwTextbox = new TEXTBOX(marginStart, 300, 250, 35);
  
  // init button objects
  comButton = new Button(marginStart, 100, 200, 35, "Input COM Port");
  wifiButton = new Button(marginStart, 350, 300, 35, "Connect NIKO to WiFi");
  
  // init strings
  comPort = comTextbox.Text;
  SSID = ssidTextbox.Text;
  password = pwTextbox.Text;
}


void mousePressed() {
  // mouse clicks for setup textboxes/buttons
  comTextbox.PRESSED(mouseX, mouseY);
  if (comButton.clicked(mouseX, mouseY)) {
      comPort = comTextbox.Text;
      // PORT OPENING COMMENTED OUT FOR DEBUGGING PURPOSES
      if (port == null) {
          //println("Current serial list: ");
          //printArray(Serial.list());
          //println("opening bluetooth serial port");
          try {
            port = new Serial(this, comPort, 115200);
          } catch (RuntimeException e) {
            // TIP: If you get a "Port not found" error, turn your pc bluetooth off then on again
             println(e.getMessage());
          }
      }
  }
  
  // mouse clicks for WiFi textboxes/buttons
  if (!comPort.equals("")) {
    ssidTextbox.PRESSED(mouseX, mouseY);
    pwTextbox.PRESSED(mouseX, mouseY);
    if (wifiButton.clicked(mouseX, mouseY)) {
       SSID = ssidTextbox.Text;
       password = pwTextbox.Text;
       //port.write(65);
       //port.write("test string");
       port.write("?" + ssidTextbox.Text + "@" + pwTextbox.Text);
    }
  }
  println("COM Port: " + comPort + "\nSSID: " + SSID + "\nPassword: " + password + '\n');
}

void keyPressed() {
  comTextbox.KEYPRESSED(key, keyCode);
  if (comPort != null) {
   ssidTextbox.KEYPRESSED(key, keyCode);
   pwTextbox.KEYPRESSED(key, keyCode); 
  }
}
