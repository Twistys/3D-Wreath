#include <PinButton.h>
#include <FastLED.h>
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

SoftwareSerial softSerial(/*rx =*/D5, /*tx =*/D6);

#define FPSerial softSerial
#define NUM_LEDS 50
#define DATA_PIN D8
#define BUTTON_PIN D2

//define which LEDs are in spots
CRGBArray<NUM_LEDS> leds;
CRGBSet red1(leds(1,2));
CRGBSet white1(leds(3,4));
CRGBSet red2(leds(5,6));
CRGBSet white2(leds(7,8));
CRGBSet red3(leds(9,10));
CRGBSet white3(leds(11,12));
CRGBSet red4(leds(13,14));
CRGBSet white4(leds(15,16));
CRGBSet red5(leds(17,18));
CRGBSet white5(leds(19,20));
CRGBSet red6(leds(21,22));
CRGBSet white6(leds(23,24));

PinButton myButton(BUTTON_PIN);
DFRobotDFPlayerMini myDFPlayer;
long randNumber;
bool wreathActive = false;
int wreathBrightness = 0;

// {Active, Brightness, FadeDirection, Color}
int wreathArray[NUM_LEDS][4] = {{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0},{0,255,1,0}};


void setup(){
  FPSerial.begin(9600);
  Serial.begin(115200);
  
  if (!myDFPlayer.begin(FPSerial, true, false)) {  //Use serial to communicate with mp3.
  Serial.println(F("Unable to begin:"));
  while(true){
    delay(0); // Code to compatible with ESP8266 watch dog.
  }
  }
  Serial.println(F("DFPlayer Mini online."));


  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  FastLED.addLeds<WS2812B, DATA_PIN, BGR>(leds, NUM_LEDS);
  //set_max_power_in_volts_and_milliamps(5, 500); // FastLED Power management set at 5V, 500mA.
  FastLED.setBrightness(240); // out of 255
  randNumber = 0;
}

void loop() {
  // Read hardware pin, convert to click events
  myButton.update();
  FastLED.show();

  if (myButton.isSingleClick()) {
    // Only triggers on a single, short click (i.e. not
    // on the first click of a double-click, nor on a long click).
    Serial.println("single");
   // print a random number from 0 to 299
  randNumber = random(10) + 1;
  Serial.println(randNumber);
  wreathActive = true;
  myDFPlayer.volume(19);
  myDFPlayer.play(randNumber);
  for (int i = 0; i <= NUM_LEDS; i++) { wreathArray[i][0] = 0; wreathArray[i][1] = 255; wreathArray[i][2] = 1; wreathArray[i][3] = 0; }

  }

  if (myButton.isDoubleClick()) {
    FastLED.clear();
    Serial.println("double");
    wreathActive = false;
    randNumber = 0;
    myDFPlayer.volume(0);
    myDFPlayer.stop();
  }

  if (wreathActive) {
  //turn on LEDs

    EVERY_N_MILLISECONDS(10) {
      wreathBrightness = 0;
      int randomLED = random8(0, NUM_LEDS);
      int randomColor = random(3);
      if (randomColor == 0) {
        randomColor = 100; // white
      }
      else if (randomColor == 1) {
        randomColor = 0; // red
      }
      else {
        randomColor = 95; // green
      }

      if (wreathArray[randomLED][0] == 0) {
        wreathArray[randomLED][0] = 1;
        wreathArray[randomLED][3] = randomColor;
      }
    }

    for (int i = 0; i <= NUM_LEDS; i++) {
      // If the LED is active, start or continue the fade in/out sequence.
      if (wreathArray[i][0] == 1) {
        // Increment the brightness either up or down
        wreathArray[i][1] = wreathArray[i][1] + (1 * wreathArray[i][2]);

        // Once full brightness reached, reverse direction.
        if (wreathArray[i][1] >= 255) {
          wreathArray[i][1] = 255;
          wreathArray[i][2] = -wreathArray[i][2];
        }

        // Once brightness fades back to zero, reset LED to inactive.
        if (wreathArray[i][1] <= 0) {
          wreathArray[i][0] = 0;
          wreathArray[i][1] = 0;
          wreathArray[i][2] = 1;
        }

        // Set each LED to blue, full saturation, brightness from loop.
        if (wreathArray[i][3] == 100) {
          leds[i] = CHSV(wreathArray[i][3], 0, wreathArray[i][1]);
        }
        else if(wreathArray[i][3] == 0) {
          leds[i] = CHSV(wreathArray[i][3], 255, wreathArray[i][1]);
        }
        else {
          leds[i] = CHSV(wreathArray[i][3], 255, wreathArray[i][1]);
        }
      }
    }

  }
}

