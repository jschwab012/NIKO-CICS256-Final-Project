/**
  Button class sourced from https://kdoore.gitbook.io/cs1335-java-and-processing/object-oriented-programming/buttons_as_objects/button-class
*/
class Button{
  ///INSTANCE VARIABLES
  float x,y; //position
  float w,h; //size
  boolean selected; //is the button selected / on? true/false
  color selectedColor, defaultColor, currentColor;
  String label; 

  ///CONSTRUCTORS - no return type declared - match Class-name
  Button(float x, float y, float w, float h, String label ){
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.label = label;
    selected = false;
    selectedColor = color(170, 170, 170); ///must be HSB color
    defaultColor = color(230, 230, 230); //slightly darker?
    currentColor = defaultColor; 
  }
  
  Button() {
     // initialize empty object
  }

  ///METHODS
  void display(){
    fill(currentColor);
    rect(x, y, w, h);
    fill(0);//black for text
    //textAlign(CENTER);
    text(label, x + w/10, y + (h/1.25));
  }

  boolean clicked( int mx, int my){
    if( mx > x && mx < x + w  && my > y && my < y+h){
      //mouse has been clicked
      selected = !selected;  //toggle the value between true and false
      if( selected){
          currentColor = selectedColor;
      }else{
          currentColor = defaultColor;
      }
      return true;
    }
    return false;
  }
  
  void setLabel(String lbl){
    label = lbl;
  }
}  //end Button class
