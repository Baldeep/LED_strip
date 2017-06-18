#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    300 // 60 per meter (300 max)
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// The current design of the LEDs
CRGBPalette16 currentPalette;

// The way the LEDs fade
TBlendType    currentBlending;

uint8_t brightness = 255; // (0 - 255)
uint8_t pause = 5000; // (min 100)


const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status

int buttonPressed = 0;

void setup() {

    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
  
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    if(buttonPressed == 0){
      buttonPressed = 1;
      brightness = brightness + 25;
      if(brightness > 255){
        brightness = 0;
      }
      digitalWrite(ledPin, HIGH);
    }
  } else {
    // turn LED off:
    buttonPressed = 0;
    digitalWrite(ledPin, LOW);
  }
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */


  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  FastLED.delay(pause / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
 
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

