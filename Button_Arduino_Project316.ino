#include "FastLED.h"

#define NUM_LEDS 60

// Data pin that led data will be written out over
#define DATA_PIN 3

//led array set up
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

//button setup
const int buttonPin = 2;  
int buttonState = 0;   


void setup() {
// sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    pinMode(buttonPin, INPUT);    
}

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { turnOnLeds, turnOffLeds };

//sets the pattern equal to the current button press count
uint8_t gCurrentPatternNumber = count; // Index number of which pattern is current

void loop() {
 gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  counter();
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void turnOnLeds()
{
  fill_solid( leds,NUM_LEDS, CRGB(205,205,205));
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

void turnOffLeds()
{FastLED.clear();
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

void counter()
{if (digitalRead(buttonPin) == HIGH) {
   nextPattern(); 
   }
}
