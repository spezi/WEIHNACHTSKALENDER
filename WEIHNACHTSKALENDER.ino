#include <FastLED.h>
#include <Button.h>


//create a Button object at pin 12
/*
|| Wiring:
|| GND -----/ ------ pin 12
*/
const int buttonPin = 12;



int buttonState = 0; 

#define LED_PIN     5
#define NUM_LEDS    50
#define BRIGHTNESS  200
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

  uint8_t green = 0;

uint8_t mitte = NUM_LEDS/2;
uint8_t counter = 0;


#define UPDATES_PER_SECOND 100

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

    pinMode(buttonPin,INPUT_PULLUP);
}

void loop() {

             
  currentBlending = LINEARBLEND;
  
  // put your main code here, to run repeatedly:
      static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    
      buttonState = digitalRead(buttonPin);
    
      if(buttonState == LOW){
          counter++;
          delay(1000);
        }else{
          
          }

    
    if (counter <= mitte) {
           goyello( startIndex);
           makeblack();
           
              if (counter == mitte) FillLEDsFromPaletteColors( startIndex); 
        //counter++;
      } else {
        counter = 0;
        }
        
   

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    
    
}

void goyello( uint8_t colorIndex)
{
    uint8_t brightness = 255;
  
   
    
    for( int i = 0; i < NUM_LEDS; i++) {

              if ( i < NUM_LEDS/2 ) {
                    green += 10;
                } else {
                    green -= 10;
                  }
              
              
              leds[i] = CRGB( 255, green, 0);
      
        colorIndex += 3;
    }
}

void makeblack()
{
  

  for (int i=counter; i <= mitte; i++){
      leds[i] = CRGB::Black;
      leds[NUM_LEDS-i] = CRGB::Black;
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
