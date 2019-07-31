/**
 * Robaux SWT16 Firmware Version 1.1.0
 * by Robert Pøul Menzel
 * musique@robaux.co
 * 
 * Alternate Firmware by Timo Rozendal v0.1.0
 * This will turn the SWT16 in a 16 channel midi to trigger module for use with Ableton Live
 * (with the accompanying Max for Live device). It needs a usb connection to your computer.
 * 
 * The leds display the active channels, the buttons can be used to Mute a channel (a short flicker indicates an incoming muted note)
 * The Blue led under the home button indicates midi activity
 * The home button does nothing.
 */
#include <Wire.h>
byte ledAndOutputData[2] = {0, 0};
int serialMessage=0;
int ledOnTick=0;
int buttonCheckTick=4;
byte test=0;
boolean muted[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mutedTicks[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int highestMuteTick=0;


#define HOME_BUTTON  5
#define STATUS_LED  4

#define BUTTON_LATCH_PIN 11
#define BUTTON_DATA_PIN 9
#define BUTTON_CLOCK_PIN 10

#define LEDS_LATCH_PIN A2
#define LEDS_CLOCK_PIN A3
#define LEDS_DATA_PIN A0

#define TRIGGER_OUT_LATCH  7
#define TRIGGER_OUT_CLOCK  8
#define TRIGGER_OUT_DATA  6


boolean buttonsEnabled = false;




byte triggerOutputData[2] = {0, 0};
byte triggerOutputs[2][16] = {
        {0, 0, 1, 16, 0, 0, 2, 128, 0, 0, 4, 64, 0, 0, 8, 32}, {128, 8, 0, 0, 64, 4, 0, 0, 32, 2, 0, 0, 16, 1, 0, 0}
};


