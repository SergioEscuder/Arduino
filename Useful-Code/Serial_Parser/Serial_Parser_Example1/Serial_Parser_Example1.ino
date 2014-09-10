/*
  
  Serial Parser
  
  This sketch will read the Serial port for incoming data and will parse the int values received in the format @1255;3488;56;22;45#
  
   -----------------------------------------
  
  
  Authors: Sergio Escuder
  
  
  Licence: GNU GPL V3

*/

//----------------------------------------------------------------------------------------------------------------------------------
// Defines
//----------------------------------------------------------------------------------------------------------------------------------
  bool DEBUG  = 0;

  #define OPEN_CHAR   '@'
  #define CLOSE_CHAR  '#'
  
// HTML Variables ****************************  
  boolean startRead = false; // is reading?
  byte valuesPos = 0;
  const byte values_SIZE = 10;                // Also limits HTTP response read funtion
  int previous_values[values_SIZE];
  int current_values[values_SIZE];    // Store values received in an array as number int
  // *******************************************


  // Serial parser
  byte current_value_digits_counter = 0;      // 0-255  Counts how many digits does the current INT being received has
  
  
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println(F("Starting..."));
  Serial.println(F("Input request in the form:    @1255;3488;56;22;45#"));
}

void loop()
{
  // put your main code here, to run repeatedly:
  Read_Parse_Serial();
}



void Read_Parse_Serial()
 {
 // OBJECTIVE: Read incoming data and capture & return everything between '@' and '#'
 // @1255;3488;56;22;45#
 
    if (Serial.available()) {
      Serial.println(F("\nReceiving from Serial"));

    // Keep reading all incoming data
    while(Serial.available()){
      //***************************** //
      // Read character entering by Serial
      char c = Serial.read();
      // Print received value
      if (DEBUG) Serial.print(c);  // THIS WILL PRINT ALL HEADERS AND HTML RETURN
      //***************************** //
     

      // ******************************************** If we receive the starting character "#", set flag ********************************************
      if (c == OPEN_CHAR ) {
        if (DEBUG) Serial.println(F("Start character received."));
        startRead = true; //Ready to start reading the part
        
        // Save status of previous_values array
        // Transfer values from current array to 'previous' for next loop comparison
        for (byte i = 0; i < 10; i = i + 1) { previous_values[i] = current_values[i]; }

        Serial.println(F("Clean variables"));
        for (int i = 0; i < 10; i = i + 1) {  current_values[i] = 0; }        //memset( &current_values, 0, 10 );
        current_value_digits_counter = 0;
        valuesPos = 0;
      // ******************************************** If we receive the starting character "#", set flag ********************************************
        
        
        
        
      // ******************************************** IF WE ARE STILL RECEIVING INCOMING DATA ********************************************
      }else if(startRead){
        
         if (!DEBUG)  Serial.print(c);  // THIS WILL PRINT ONLY USEFUL INFO
          
          // Do not process the last character because its not an int, its the ending character
          if (  (c != CLOSE_CHAR)   ) {
                Serial.print(F("Array position: "));Serial.print(valuesPos);
                if (c != ';') {     
                  Serial.print(F("\tReceived int number: "));            Serial.print(c-'0');
                  Serial.print(F("\t\tSaving to current_value_digits_counter: ")); Serial.println(current_value_digits_counter);
                  current_value_digits_counter++;
                  current_values[valuesPos] = current_values[valuesPos]*10 + (c - '0');
                  
                } else {
                  Serial.println(F("\nReceived separation character"));
                    valuesPos++;
                  // Clean current int digit index counter
                  current_value_digits_counter = 0;
                }
          }
      // ******************************************** IF WE ARE STILL RECEIVING INCOMING DATA ********************************************
                        
                        


 
      // ******************************************** If we have arrived to the end character ********************************************
        if (  (c != CLOSE_CHAR)   ) {           // '>' is our ending character
         // inString[stringPos] = c;
         // stringPos ++;
        }else{
          if (DEBUG) Serial.println(F("End character received."));
            
          //got what we need here! We can disconnect now
          startRead = false;
          //client.stop();
          Serial.flush();
          Serial.println(F("disconnecting."));
         // Parse_Serial();
         // Process_received_data();  // Go to another function to do stuff with the data received
          Print_values_array();
         }
      // ******************************************** If we have arrived to the end character ********************************************

      }
    } // While serial
  }  // if serial  
 }
 
 
 
void Print_values_array()
{
    Serial.print(F("Current  Values: "));  for (byte i = 0; i < 10; i = i + 1) {  Serial.print(current_values[i]);    Serial.print("\t");       } Serial.println();
    Serial.print(F("Previous Values: "));  for (byte i = 0; i < 10; i = i + 1) {  Serial.print(previous_values[i]);   Serial.print("\t");       } Serial.println();
}
