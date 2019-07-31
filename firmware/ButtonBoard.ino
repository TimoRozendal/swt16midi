byte switchVar1;
byte switchVar2;
int buttonPos[2][16] = {{1, 0, 7, 6, 3, 2, 5, 4, 10, 11, 8, 9, 14, 12, 13, 15}, {15, 12, 14, 13, 9, 8, 11, 10, 2, 3, 6, 7, 4, 5, 0, 1}};

byte buttons0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
byte buttons1[8] = {0, 0, 0, 0, 0, 0, 0, 0};

byte leds[2][8] = {  {1, 8, 4, 2, 32, 16, 128, 64},  {1, 8, 4, 2, 32, 16, 128, 64}};
byte activeLeds[2] = {0, 0};

int buttons[16] = {};
int buttonStatus[16] = {};
int lastPressed[16] = {};
int currentPressed[16] = {};

void setupButtonBoard() {
        pinMode(LEDS_LATCH_PIN, OUTPUT);
        pinMode(BUTTON_LATCH_PIN, OUTPUT);
        pinMode(BUTTON_CLOCK_PIN, OUTPUT);
        pinMode(BUTTON_DATA_PIN, INPUT);
}

void setLedValue(uint8_t led, boolean value) {
        if (led < 16) {

                boolean top = led < 8;
                int v = leds[top][led - (top ? 8 : 0)];
                if (value && !(activeLeds[top] & v)) {
                        activeLeds[top] += v;
                } else if (!value && (activeLeds[top] & v)) {
                        activeLeds[top] -= v;
                }
        }
}

void writeDisplay() {
        digitalWrite(LEDS_LATCH_PIN, 0);
        writeTriggers(LEDS_DATA_PIN, LEDS_CLOCK_PIN, activeLeds[0]);
        writeTriggers(LEDS_DATA_PIN, LEDS_CLOCK_PIN, activeLeds[1]);
        digitalWrite(LEDS_LATCH_PIN, 1);
}
byte getButtonIndex(byte button) {
        return buttonPos[0][button];
}
byte shiftIn(int myBUTTON_DATA_PIN, int myBUTTON_CLOCK_PIN) {
        int i;
        int temp = 0;
        int pinState;
        byte myDataIn = 0;
        pinMode(myBUTTON_CLOCK_PIN, OUTPUT);
        pinMode(myBUTTON_DATA_PIN, INPUT);
        for (i = 7; i >= 0; i--)  {
                digitalWrite(myBUTTON_CLOCK_PIN, 0);
                // delayMicroseconds(0.2);
                temp = digitalRead(myBUTTON_DATA_PIN);
                if (temp) {
                        pinState = 1;
                        myDataIn = myDataIn | (1 << i);
                }
                else {
                        pinState = 0;
                }
                digitalWrite(myBUTTON_CLOCK_PIN, 1);

        }
        return myDataIn;
}
boolean readSwitches() {
        for (byte foo = 0; foo < 16; foo++) {
                lastPressed[foo] = currentPressed[foo];
        }
        digitalWrite(BUTTON_LATCH_PIN, 1);
        delayMicroseconds(20);
        digitalWrite(BUTTON_LATCH_PIN, 0);
        switchVar1 = shiftIn(BUTTON_DATA_PIN, BUTTON_CLOCK_PIN);
        switchVar2 = shiftIn(BUTTON_DATA_PIN, BUTTON_CLOCK_PIN);
        for (int n = 0; n <= 7; n++) {
                buttonStatus[getButtonIndex(n)] = switchVar1 & (1 << n) ? 1 : 0;
                buttonStatus[getButtonIndex(n + 8)] = switchVar2 & (1 << n) ? 1 : 0;
        }
        for (byte foo = 0; foo < 16; foo++) {
                lastPressed[foo] = currentPressed[foo];
                currentPressed[foo] = buttonStatus[foo];
        }
        return true;
}
boolean justPressed(byte button) {
        return lastPressed[button] != currentPressed[button] && currentPressed[button] == 1 ? true : false;
}
boolean justReleased(byte button) {
        return lastPressed[button] != currentPressed[button] && currentPressed[button] == 0 ? true : false;
}
boolean clearButtons() {
        for (byte foo = 0; foo < 16; foo++) {
                lastPressed[foo] = currentPressed[foo] = 0;
        }
}
