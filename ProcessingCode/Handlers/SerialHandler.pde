import processing.serial.*;

private final int BAUD_RATE = 230400;
private Serial port;
private final String serialName = "COM3";

public int writeLength = 64; //Arduino Buffer Size

class SerialHandler extends Serial{
  
  
  //Just use this in Main for parent
  public SerialHandler(PApplet parent){
    super(parent, serialName, BAUD_RATE);
  }
  
  //Check data is size of Arudino Buffer
  public void write(byte[] src) throws RuntimeException{
    if(src.length > writeLength){
      throw new RuntimeException("Data is too large!");
    }
    super.write(src);
  }
  public void write(String src) throws RuntimeException{
    if(src.length() > writeLength){
      throw new RuntimeException("Data is too large!");
    }
    super.write(src);
  }
  
  
}
