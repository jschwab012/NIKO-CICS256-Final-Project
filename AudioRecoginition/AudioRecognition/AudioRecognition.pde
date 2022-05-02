import edu.cmu.sphinx.api.Configuration;
import edu.cmu.sphinx.api.LiveSpeechRecognizer;
import edu.cmu.sphinx.api.SpeechResult;

import processing.sound.*;

Configuration configuration;
LiveSpeechRecognizer recognizer;
SpeechResult result;

//import ddf.minim.*;

//Minim minim;
//AudioInput in;
//AudioRecorder recorder;

void setup(){

  //size(512, 200, P3D);

  //minim = new Minim(this);
  
  //in = minim.getLineIn();
  //// create a recorder that will record from the input to the filename specified
  //// the file will be located in the sketch’s root folder.
  //recorder = minim.createRecorder(in, "test.wav");
  //textFont(createFont("Arial", 12));

  try{
    configuration = new Configuration();
    configuration.setAcousticModelPath("resource:/edu/cmu/sphinx/models/en-us/en-us");
    configuration.setDictionaryPath("resource:/edu/cmu/sphinx/models/en-us/cmudict-en-us.dict");
    configuration.setLanguageModelPath("resource:/edu/cmu/sphinx/models/en-us/en-us.lm.bin");
    
    recognizer = new LiveSpeechRecognizer(configuration);
    // InputStream stream = new FileInputStream(new File("test.wav"));
    recognizer.startRecognition(true);
  }
  catch(Exception e){
  }
}

void draw(){
  if((result = recognizer.getResult()) != null){
    print("Hypothesis: ");
    println(result.getHypothesis());
    if(result.getHypothesis().equals("exit")){
      recognizer.stopRecognition();
    }
  }
        
}

//void draw()
//{
//background(0);
//stroke(255);
//// draw the waveforms
//// the values returned by left.get() and right.get() will be between -1 and 1,
//// so we need to scale them up to see the waveform
//for(int i = 0; i < in.bufferSize() - 1; i++) { line(i, 50 + in.left.get(i)*50, i+1, 50 + in.left.get(i+1)*50); line(i, 150 + in.right.get(i)*50, i+1, 150 + in.right.get(i+1)*50); } if ( recorder.isRecording() ) { text("Currently recording...", 5, 15); } else { text("Not recording.", 5, 15); } } void keyReleased() { if ( key == 'r' ) { // to indicate that you want to start or stop capturing audio data, you must call // beginRecord() and endRecord() on the AudioRecorder object. You can start and stop // as many times as you like, the audio data will be appended to the end of whatever // has been recorded so far. if ( recorder.isRecording() ) { recorder.endRecord(); } else { recorder.beginRecord(); } } if ( key == 's' ) { // we've filled the file out buffer, // now write it to the file we specified in createRecorder // the method returns the recorded audio as an AudioRecording, // see the example AudioRecorder >> RecordAndPlayback for more about that
//recorder.save();
//println(“Done saving.”);
//}
//}
