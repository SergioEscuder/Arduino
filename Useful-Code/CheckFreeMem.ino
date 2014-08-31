void CheckFreeMem(){
    #ifdef FreeMem 
    //    if (millis() - previousmillis_FreeMem > interval_FreeMem)
        {
      //    previousmillis_FreeMem = millis();
          Serial.println();
          Serial.print(F("freeMemory()="));       Serial.println(freeMemory());
          Serial.print(F("freeRam   ()="));       Serial.println(freeRam ());
          Serial.println();
        }
    #endif
}
