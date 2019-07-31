
void writeTriggers(int dataPin, int clockPin, byte data) {
        int i = 0;
        pinMode(clockPin, OUTPUT);
        pinMode(dataPin, OUTPUT);
        digitalWrite(dataPin, 0);
        digitalWrite(clockPin, 0);
        for (i = 7; i >= 0; i--) {
                digitalWrite(clockPin, 0);
                digitalWrite(dataPin, data & (1 << i) ? 1 : 0);
                digitalWrite(clockPin, 1);
                digitalWrite(dataPin, 0);
        }
        digitalWrite(clockPin, 0);
}



void writeLedsAndOutputs() 
{
        digitalWrite(LEDS_LATCH_PIN, 0);
        writeTriggers(LEDS_DATA_PIN, LEDS_CLOCK_PIN, activeLeds[0]);
        writeTriggers(LEDS_DATA_PIN, LEDS_CLOCK_PIN, activeLeds[1]);
        digitalWrite(LEDS_LATCH_PIN, 1);

        digitalWrite(TRIGGER_OUT_LATCH, 0);
        writeTriggers(TRIGGER_OUT_DATA, TRIGGER_OUT_CLOCK, triggerOutputData[0]);
        writeTriggers(TRIGGER_OUT_DATA, TRIGGER_OUT_CLOCK, triggerOutputData[1]);
        digitalWrite(TRIGGER_OUT_LATCH, 1);
}

void setLedAndOutputValue(uint8_t nr, boolean value) 
{
      if (muted[nr]) 
      {
        if (value)
        {
          setLedValue(nr, false);
          mutedTicks[nr] = 100;
          highestMuteTick=100;
        }
        else setLedValue(nr, true);
        
        setOutputValue(nr, false);
      }
      else 
      {
        setLedValue(nr, value); 
        setOutputValue(nr, value);
      }
}


void setOutputValue(uint8_t output, boolean value) {
        if (output < 16) 
        {
               
          int v = triggerOutputs[0][output];
          int w = triggerOutputs[1][output];
          if (value && !(triggerOutputData[0] & v)) triggerOutputData[0] += v;
          else if (!value && (triggerOutputData[0] & v)) triggerOutputData[0] -= v;
          if (value && !(triggerOutputData[1] & w)) triggerOutputData[1] += w;
          else if (!value && (triggerOutputData[1] & w)) triggerOutputData[1] -= w;
        }
}
