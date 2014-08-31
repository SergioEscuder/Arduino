// displays at startup the Sketch running in the Arduino, this sketch uses 429 of ram. Disable it if necessary.
void Display_Running_Sketch (String the_path){
      String the_path = __FILE__;
      int slash_loc = the_path.lastIndexOf('/');
      String the_cpp_name = the_path.substring(slash_loc+1);
      int dot_loc = the_cpp_name.lastIndexOf('.');
      String the_sketchname = the_cpp_name.substring(0, dot_loc);
    
      Serial.print(F("\nArduino is running Sketch: "));
      Serial.println(the_sketchname);
      Serial.print(F("Compiled on: "));
      Serial.print(__DATE__);
      Serial.print(F(" at "));
      Serial.print(__TIME__);
      Serial.print(F("\n"));
      Serial.println();
}
