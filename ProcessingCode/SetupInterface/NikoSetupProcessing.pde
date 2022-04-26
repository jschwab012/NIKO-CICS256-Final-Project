/**
  Inspiration for GUI from Mitko Nikov @ https://www.youtube.com/watch?v=N753XIKAUPo
*/
import java.util.Collections;
import java.util.ArrayList;
import java.util.Hashtable;

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
  
   if (comPort != null) {
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
  wifiButton = new Button(marginStart, 350, 200, 35, "Input WiFi Info");
}


void mousePressed() {
  // mouse clicks for setup textboxes/buttons
  comTextbox.PRESSED(mouseX, mouseY);
  if (comButton.clicked(mouseX, mouseY)) {
      comPort = comTextbox.Text;
  }
  
  // mouse clicks for WiFi textboxes/buttons
  if (comPort != null) {
    ssidTextbox.PRESSED(mouseX, mouseY);
    pwTextbox.PRESSED(mouseX, mouseY);
    if (wifiButton.clicked(mouseX, mouseY)) {
       SSID = ssidTextbox.Text;
       password = pwTextbox.Text;
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
