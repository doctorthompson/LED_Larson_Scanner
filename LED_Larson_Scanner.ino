#include <FastLED.h>

#define NUM_LEDS 83               // How many leds in your strip?
#define DATA_PIN 2                // (D4) Data out to strip
#define POWER_PIN 5               // (D1) MOSFET control 12V power to strip
#define COLOR 0xCC3300            // Pulse colour
#define MAX_POWER_VOLTS     12    // Automotive voltage
#define MAX_POWER_MILLIAMPS 4000  // Milliamp max (Should match inline fuse)
#define BRIGHTNESS 240            // LED Brightness (0-255)
#define BEATS 36                  // BPM of full cycle
#define DECAY 18                  // How fast pulse fades
CRGBArray<NUM_LEDS> leds;         // LED memory addresses
uint16_t lead_dot = 0;            // Current Pulse Position

void setup() {
  // Power up the strip
  analogWrite(POWER_PIN,0);
  delay(300);
  analogWrite(POWER_PIN,1023);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps( MAX_POWER_VOLTS, MAX_POWER_MILLIAMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  FastLED.delay(500);
}

void loop() {
  EVERY_N_MILLISECONDS(4) {
    leds.fadeToBlackBy(DECAY);
    lead_dot = beatsin16( BEATS, 0, NUM_LEDS-1 );
    leds[lead_dot] = COLOR;
    FastLED.show();
    
  }
}
