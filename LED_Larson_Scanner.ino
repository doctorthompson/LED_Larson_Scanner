#include <FastLED.h>

#define NUM_LEDS 87               // How many leds in your strip?
#define DATA_PIN 2                // Data pin D4 on NodeMCU
#define COLOR 0xcc3300            // Pulse colour
#define MAX_POWER_VOLTS     12    // Voltage
#define MAX_POWER_MILLIAMPS 4000  // Milliamps MAX
#define BRIGHTNESS 240            // LED Brightness (0-255)
#define BEATS 36                  // BPM of full cycle

CRGBArray<NUM_LEDS> leds;         // LED memory addresses
uint16_t lead_dot = 0;            // Current Pulse Position

void setup() {
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
    lead_dot = beatsin16( BEATS, 0, NUM_LEDS-1 );
    leds[lead_dot] = COLOR;
    FastLED.show();
    leds.fadeToBlackBy(18);
  }
}
