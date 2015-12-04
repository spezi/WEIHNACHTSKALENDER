#include <FastLED.h>

//create a Button object at pin 12
/*
|| Wiring:
|| GND -----/ ------ pin 12
*/
const int buttonPin = 12;
int buttonState = 0; 

// FastLED Stuff
#define LED_PIN     5
#define NUM_LEDS    50
#define BRIGHTNESS  200
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

uint8_t green = 0;
uint8_t mitte = NUM_LEDS/2;
uint8_t counter = 0;

// pixel index starts @ 0 
uint8_t last_LED = NUM_LEDS - 1;


#define UPDATES_PER_SECOND 30

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    
    // set pullup Resistor for the button
    pinMode(buttonPin,INPUT_PULLUP);
}

void loop() {

  // put your main code here, to run repeatedly:
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    if (counter <= mitte) {
          // colorize all lights an let the pixel turn a bit more yellow day by day from both sides to the middle
           turnyello( startIndex);
          // mask pixel of the following days
           makeblack();
          // Show Animation at Christmas Eve
           if (counter == mitte) FillLEDsFromPaletteColors( startIndex); 
      } else {
          // back to beginning
           counter = 0;
        }
        
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    
      buttonState = digitalRead(buttonPin);

      if(buttonState == LOW){
          counter++;
          delay(1000);
        }
    
}

void turnyello( uint8_t colorIndex)
{
    uint8_t brightness = 255;

    for( int i = 0; i < NUM_LEDS; i++) {
            
              leds[i] = CRGB( 255, green, 0);
            
              if ( i < NUM_LEDS/2 ) {
                    green += 10;
                } else {
                    green -= 10;
                  }
                  
        colorIndex += 3;
    }
}

void makeblack()
{
  for (int i=counter; i <= mitte; i++){
      
      leds[i] = CRGB::Black;
      leds[last_LED-i] = CRGB::Black;
    }
  }

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
