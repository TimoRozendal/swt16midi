void setup() 
{
        randomSeed(analogRead(4));

        pinMode(TRIGGER_OUT_LATCH, OUTPUT);
        digitalWrite(TRIGGER_OUT_LATCH, 0);
        writeTriggers(TRIGGER_OUT_DATA, TRIGGER_OUT_CLOCK, 0);
        writeTriggers(TRIGGER_OUT_DATA, TRIGGER_OUT_CLOCK, 0);
        digitalWrite(TRIGGER_OUT_LATCH, 1);

        pinMode(STATUS_LED, OUTPUT);
        pinMode(HOME_BUTTON, INPUT);  //perhaps use this as mute all?

        setupButtonBoard();
        writeLedsAndOutputs();
        delay(200);
        
        Serial.begin(38400);
}






void loop() 
{
        // 1 loop is 1 tick
   
        
        if (Serial.available() > 0)
        {
            serialMessage = Serial.read();
            if (serialMessage<32)
            {
               setLedAndOutputValue(serialMessage/2, serialMessage%2);
            }
            else
            {
              //all off
              for (byte foo = 0; foo < 16; foo++) 
              {
                 setLedAndOutputValue(foo, false);
              }
            }
            writeLedsAndOutputs();
            digitalWrite(STATUS_LED, 1);
            ledOnTick=100;  //flash blue led on midi activity for 100ticks
        }
        else
        {
          if (ledOnTick>0)
          {
            ledOnTick--;
            if (ledOnTick==0)  digitalWrite(STATUS_LED, 0);
          }
        }

        buttonCheckTick--;
        if (buttonCheckTick<=0)
        {
          //check button states here
          readSwitches();
          for (uint8_t foo = 0; foo < 16; foo++) 
          {
            if (justPressed(foo)) 
            {
              muted[foo]=!muted[foo]; 
             // if (muted[foo]) 
              setLedAndOutputValue(foo, false); //turn note off that 
            }
          }
          buttonCheckTick=4;
        }

      if (highestMuteTick>0)
      {
          highestMuteTick--;
          bool shouldUpdate=false;
          for (uint8_t foo = 0; foo < 16; foo++) 
          {
            if (mutedTicks[foo]>0)
            {
              mutedTicks[foo]--;
              if (mutedTicks[foo]==0) 
              {
                 setLedAndOutputValue(foo, false);   //this fails because
                 shouldUpdate=true;
              }
            }
          }
         if (shouldUpdate)writeLedsAndOutputs();
      }          
}
        

