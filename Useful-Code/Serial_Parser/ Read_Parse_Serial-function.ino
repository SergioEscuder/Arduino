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
                  Serial.println(F("\nReceived separation character")); //, processing mini_string: "));   Serial.println(mini_string);
                    valuesPos++;
                  // Clean mini_string index counter
                  current_value_digits_counter = 0;
                }
          }
      // ******************************************** IF WE ARE STILL RECEIVING INCOMING DATA ********************************************
                        
                        


 
      // ******************************************** If we have arrived to the end character ********************************************
        if (  (c != CLOSE_CHAR)   ) {           // '>' is our ending character
         // inString[stringPos] = c;
          stringPos ++;
        }else{
          if (DEBUG) Serial.println(F("End character received."));
            
          //got what we need here! We can disconnect now
          startRead = false;
          //client.stop();
          Serial.flush();
          Serial.println(F("disconnecting."));
         // Parse_Serial();
         Process_received_data();
         //Print_values_array();
         }
      // ******************************************** If we have arrived to the end character ********************************************
 
      }
    } // While serial
  }  // if serial  
 }
 
 
