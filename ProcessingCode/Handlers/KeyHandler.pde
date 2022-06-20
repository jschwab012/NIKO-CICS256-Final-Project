//Class for handling Keys pressed
class KeyHandler{
  
  private String keyBuffer = "";
  public boolean isSaving = true; //Shoud keyToString save to buffer
  
  //KeyBuffer methods
  public String getKeyBuffer(){return keyBuffer;}
  public void clearKeyBuffer(){keyBuffer = "";}
  
  
  //Converts the pressed key to String
  public String keyToString(){
    String pressedKey = "";
    if(key == CODED){
      switch(keyCode){
        case 16:
          pressedKey = "SHIFT";
          break;
        case 17:
          pressedKey = "CTRL";
          break;
        case 18:
          pressedKey = "ALT";
          break;
        case 20:
          pressedKey = "CAPS_LOCK";
          break;
        case 37:
          pressedKey = "LEFT";
          break;
        case 38:
          pressedKey = "UP";
          break;
        case 39:
          pressedKey = "RIGHT";
          break;
        case 40:
          pressedKey = "DOWN";
          break;
        default:
          pressedKey = "[UNDEFINED" + keyCode + "]";
          break;
      }
    }
    else{
      pressedKey = String.valueOf(key);
    }
    
    if(isSaving){
      keyBuffer += pressedKey; //Add key to buffer
    }
      
    return pressedKey; 
  }
  
  //Prints the key to stdout
  public void printKey(){
    print(keyToString());
  }
  
}
