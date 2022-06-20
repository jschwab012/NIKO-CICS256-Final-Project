
//Settings
final int screenWidth = 800;
final int screenHeight = 600;
final int fps = 30;

//Variables
int squareSize = 50; //Can be removed, if function is removed
KeyHandler keyHandler = new KeyHandler();

//Runs once before setup
void settings(){
  size(screenWidth, screenHeight);
}

//Runs once after settings
void setup(){
  frameRate(fps);
  background(0, 0, 0);
  
  //Open the port
  //SerialHandler port = new SerialHandler(this);
}

//Runs continously at fps
void draw(){
}

//Can be removed
//Remove call is mousePressed
void drawSquare(int x, int y){
  clear();
  stroke(255, 0, 0);
  fill(255, 0, 0);
  square(x - (squareSize)/2, y - (squareSize)/2, squareSize);
}

void mousePressed(){
  drawSquare(mouseX, mouseY);
  print(keyHandler.getKeyBuffer());
  keyHandler.clearKeyBuffer();
}

void keyPressed(){
  keyHandler.printKey();
}
