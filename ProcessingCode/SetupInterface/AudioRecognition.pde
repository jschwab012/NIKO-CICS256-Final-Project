import edu.cmu.sphinx.api.Configuration;
import edu.cmu.sphinx.api.LiveSpeechRecognizer;
import edu.cmu.sphinx.api.SpeechResult;

public class AudioRecognition{
  Configuration configuration;
  LiveSpeechRecognizer recognizer;
  SpeechResult result;
  
  void configVoiceRec(){
    try{
      configuration = new Configuration();
      configuration.setAcousticModelPath("resource:/edu/cmu/sphinx/models/en-us/en-us");
      configuration.setDictionaryPath("resource:/edu/cmu/sphinx/models/en-us/cmudict-en-us.dict");
      configuration.setLanguageModelPath("resource:/edu/cmu/sphinx/models/en-us/en-us.lm.bin");
      
      recognizer = new LiveSpeechRecognizer(configuration);
    }
    catch(Exception e){
      e.printStackTrace();
    }
  }
  
  void startRec(boolean start){
    recognizer.startRecognition(start);
  }
  void stopRec(){
    recognizer.stopRecognition();
  }
  
  //call in draw()
  String recieveRec(){
    result = recognizer.getResult();
    if(result != null){
      print("Hypothesis: ");
      println(result.getHypothesis());
      
      //Remove if statement to allow for infinite recognition
      if(result.getHypothesis().equals("exit")){
        stopRec();
      }
    }
    return result.getHypothesis();
  }
}
