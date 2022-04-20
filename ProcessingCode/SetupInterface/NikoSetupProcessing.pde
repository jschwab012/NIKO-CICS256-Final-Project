/**
  Inspiration for GUI from Mitko Nikov @ https://www.youtube.com/watch?v=N753XIKAUPo
*/
import java.util.Collections;
import java.util.ArrayList;

ArrayList<TEXTBOX> textboxes = new ArrayList<TEXTBOX>();

void setup() {
 size(500, 400); 
 initLayout();
}

void draw() {
  background(180);
  
  for (TEXTBOX t : textboxes) {
    t.DRAW(); 
  }
}

void initLayout() {
  TEXTBOX receiver = new TEXTBOX();
  receiver.X = width / 15;
  receiver.Y = 50;
  receiver.W = 250;
  receiver.H = 35;
  
  TEXTBOX message = new TEXTBOX();
  message.X = width / 15;
  message.Y = 150;
  message.W = 250;
  message.H = 35;
  
  Collections.addAll(textboxes, receiver, message);
}

void mousePressed() {
  for (TEXTBOX t : textboxes) {
    t.PRESSED(mouseX, mouseY);
  }
}

void keyPressed() {
  for (TEXTBOX t : textboxes) {
    t.KEYPRESSED(key, keyCode);
  }
}
