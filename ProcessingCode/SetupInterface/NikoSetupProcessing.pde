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
int windowHeight = 475;
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

//AudioRec stuff
int isAudioRecRunning = 0; //0 off, 1 loading, 2 recording
boolean isAudioRecListening = false;

Button recordingButton;
//Audio Recognition
AudioRecognition audioRec;
void settings() {
  size(windowWidth, windowHeight); 
}

void setup() {
  printArray(Serial.list());
 // init font/text properties
 f = createFont("Arial", 28, true);
 
 // init custom GUI elements
 initLayout();
 
 //Init voice recognition
 thread("initAudioRec");
}

void draw() {  
  background(150);
  
  // init text
  textFont(f);
  fill(255);
  text("Make Sure to pair NIKO", marginStart, 30);
  text("in your device's bluetooth settings!", marginStart, 55);
  text("COM Port", marginStart, 95);
  
  // draw setup textboxes
  comTextbox.DRAW();
  
  // draw setup buttons
  comButton.display();
  
   if (!comPort.equals("")) {
    // draw text headers
    textFont(f);
    fill(255);
    text("SSID", marginStart, 245);
    text("Password", marginStart, 345);
    
    // draw textboxes
    ssidTextbox.DRAW();
    pwTextbox.DRAW();
    
    // draw buttons  //<>// //<>//
    wifiButton.display(); //<>// //<>//
  }
  
  if(!comPort.equals("")){
    recordingButton.display();
    recordingLight();
  }
  //send recognized audio here
  sendSerialSpeechMessage();
}

//void processAudioRec() {
  
//}

void initLayout() {
  // init textbox objects
  comTextbox = new TEXTBOX(marginStart, 110, 250, 35);
  ssidTextbox = new TEXTBOX(marginStart, 260, 250, 35);
  pwTextbox = new TEXTBOX(marginStart, 360, 250, 35);
  
  // init button objects
  comButton = new Button(marginStart, 160, 200, 35, "Input COM Port");
  wifiButton = new Button(marginStart, 410, 300, 35, "Connect NIKO to WiFi");
  recordingButton = new Button(windowWidth - 215, windowHeight - 115, 200, 35, "Start Recording");
  
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
          println("Current serial list: ");
          printArray(Serial.list());
          println("opening bluetooth serial port");
          try {
            println("test print");
            port = new Serial(this, comPort, 115200);
            port.write(';');
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
       try {
          port.write("?" + ssidTextbox.Text + "@" + pwTextbox.Text);
       } catch (NullPointerException e) {
          println(e.getMessage()); 
       }
    }
  }
  println("COM Port: " + comPort + "\nSSID: " + SSID + "\nPassword: " + password + '\n');
  
  //mouse clicks for Recording textboxes/button
  if(recordingButton.clicked(mouseX, mouseY)){
    if(isAudioRecRunning == 0){
      thread("startRecording");
    } else if(isAudioRecRunning == 2){
      exitAudioRec();
    }
  }
}

void keyPressed() {
  comTextbox.KEYPRESSED(key, keyCode);
  if (comPort != null) {
   ssidTextbox.KEYPRESSED(key, keyCode);
   pwTextbox.KEYPRESSED(key, keyCode); 
  }
}

//Recording stuff
void initAudioRec(){
  audioRec = new AudioRecognition();
  audioRec.configVoiceRec();
}

//Start recording and change internal values
void startRecording(){
  isAudioRecRunning = 1;'
  recordingButton.setLabel("Stop Recording");
  isAudioRecListening = true;
  audioRec.startRec();
  isAudioRecRunning = 2;
}

//Stop recording and change internal values
void exitAudioRec(){
  recordingButton.setLabel("Start Recording");
  isAudioRecRunning = 0;
  isAudioRecListening = false;
  audioRec.stopRec();
}

//Set the color of the rec light
void recordingLight(){
  if(isAudioRecRunning == 1){
    fill(255, 255, 0);
  }
  else if(isAudioRecRunning == 2){
    fill(0, 255, 0);
  }
  else{
    fill(255, 0, 0);
  }
  circle(windowWidth - 25, windowHeight - 55, 25);
}

//Send message to arduino if niko is said
//stops recording if exit is sent
void sendSerialSpeechMessage(){
  try{
    if(isAudioRecRunning == 2){
      String result = audioRec.recieveRec(isAudioRecListening);
      if(result.length() > 0){
        String resultArr[] = result.split("\\s+");
        if(resultArr.length >= 2){
          if(resultArr[0].equals("niko")){
            if(resultArr[1].equals("exit")){
              exitAudioRec(); 
            }
            else{
              String sendString = '$' + resultArr[1];
              println("Sending to NIKO: " + sendString);
              port.write(sendString);
            }
          }
        }
      }
    }
  } catch(Exception e){
    e.printStackTrace();
  }
}
