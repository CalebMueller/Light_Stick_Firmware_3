#define FASTLED_ALL_PINS_HARDWARE_SPI
#include "fastLED.h"

#include "LED_Peripheral.h"

FASTLED_USING_NAMESPACE

CRGB leds[NUM_LEDS];

int currentPatternNum{0};

// example: PatternArray patternArray = {PatternName};
PatternArray patternArray = {
    LED_fill_solid, LED_fill_gradient, LED_accel_rainbow,       POV_smiley,
    POV_skull,      POV_red_among_us,  POV_red_among_us_ribbon, POV_dna,
};

///////////////////////////////////////////////////////////////////////
////////////////  UTILITY FUNCTIONS  /////////////////////////////////
/////////////////////////////////////////////////////////////////////

void LED_Peripheral_setup() {
  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(25)>(
      leds, NUM_LEDS); // BGR
  set_max_power_in_milliwatts(2000);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.clear(true);
  FastLED.show();
}
// END OF LED_Peripheral_setup()
///////////////////////////////////////////////////

void LED_clear() {
  FastLED.clear(true);
  FastLED.show();
}
// END OF LED_clear()
////////////////////////////////////////////////////

void LED_show() { FastLED.show(); }
// END OF LED_show()
///////////////////////////////////////////////////

void LED_startup_animation() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(i * (255 / NUM_LEDS), 255, 255);
    FastLED.show();
    delay(10);
  }
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(500);
  for (int i = NUM_LEDS; i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(10);
  }
}
// END OF LED_startup_animation()
////////////////////////////////////////////////////

void LED_cycleBrightness() {
  // Cycles through NUM_BRIGHTNESS_LEVELS settings of brigthness
  // maxBrightness set by MAX_BRIGHTNESS macro at top of header
  // default brightness_level is max
  static byte brightness_level = NUM_BRIGHTNESS_LEVELS;
  // Roll over brightness_level to 1 once NUM_BRIGHTNESS_LEVELS is reached
  brightness_level = (brightness_level % (NUM_BRIGHTNESS_LEVELS)) + 1;
  byte brightness_value =
      map(brightness_level, 1, NUM_BRIGHTNESS_LEVELS, 3, MAX_BRIGHTNESS);
  FastLED.setBrightness(brightness_value);
}
// END OF LED_cyclebrightness()
///////////////////////////////////////////////////

void LED_nextPattern() {
  FastLED.clear();
  currentPatternNum = (currentPatternNum + 1) %
                      (sizeof(patternArray) / sizeof(patternArray[0]));
}
// END OF LED_nextPattern()
///////////////////////////////////////////////////

void LED_POV(POV_Pattern &pattern) {
  static uint32_t column{0};
  for (int i = 0; i < pattern._height; ++i) {
    uint32_t offset = 3 * (i + column * pattern._height);
    leds[i].blue = pattern._img[offset];
    leds[i].green = pattern._img[offset + 1];
    leds[i].red = pattern._img[offset + 2];
    // Serial.print("B");
    // Serial.print(pattern._img[offset]);
    // Serial.print(" G");
    // Serial.print(pattern._img[offset + 1]);
    // Serial.print(" R");
    // Serial.println(pattern._img[offset + 2]);
    // Serial.print(" ");
  }
  column = (column + 1) % pattern._width;
  FastLED.show();
}
// END OF LED_POV()
///////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
////////////////  LED PATTERN FUNCTIONS  /////////////////////////////
/////////////////////////////////////////////////////////////////////

void LED_fill_solid() {
  fill_solid(leds, NUM_LEDS, CRGB::Aqua);
  FastLED.show();
}
// END OF LED_fillsolid()
////////////////////////////////////////////////////

void LED_fill_gradient() {
  fill_gradient(leds, NUM_LEDS, CHSV(46, 255, 255), CHSV(180, 255, 255),
                FORWARD_HUES);
}
// END OF LED_fill_gradient()
///////////////////////////////////////////////////

void LED_accel_rainbow() {
  static NoBlockTimer t1;
  static float lpf{0};
  if (t1.timer(20)) {
    const byte filter_weight = 20;
    lpf = (filter_weight * lpf + mpu_fetch_a_y()) / (filter_weight + 1);
  }
  uint8_t map_val = map(lpf, -12.0, 12.0, 0, 255);
  uint8_t deltaHue = (255 / uint8_t(NUM_LEDS));
  fill_rainbow(leds, NUM_LEDS, map_val, deltaHue);
}
// END OF LED_accel_rainbow()
///////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
////////////////  POV PATTERN FUNCTIONS  /////////////////////////////
/////////////////////////////////////////////////////////////////////

void POV_smiley() {
  static POV_Pattern *smiley = new POV_Pattern("/spiffs/smiley.bmp");
  static NoBlockTimer t;
  if (t.timer(4)) {
    smiley->Run();
  }
}
// END OF POV_smiley()
///////////////////////////////////////////////////

void POV_skull() {
  static POV_Pattern *skull = new POV_Pattern("/spiffs/my_skull.bmp");
  static NoBlockTimer t;
  if (t.timer(4)) {
    skull->Run();
  }
}
// END OF POV_skull()
///////////////////////////////////////////////////

void POV_red_among_us() {
  static POV_Pattern *red_among_us =
      new POV_Pattern("/spiffs/red_among_us.bmp");
  static NoBlockTimer t;
  if (t.timer(4)) {
    red_among_us->Run();
  }
}
// END OF POV_red_among_us()
///////////////////////////////////////////////////

void POV_red_among_us_ribbon() {
  static POV_Pattern *red_among_us_ribbon =
      new POV_Pattern("/spiffs/red_among_us_ribbon.bmp");
  static NoBlockTimer t;
  if (t.timer(4)) {
    red_among_us_ribbon->Run();
  }
}
// END OF POV_red_among_us_ribbon()
///////////////////////////////////////////////////

void POV_dna() {
  static POV_Pattern *dna = new POV_Pattern("/spiffs/dna.bmp");
  static NoBlockTimer t;
  if (t.timer(4)) {
    dna->Run();
  }
}
// END OF POV_dna()
///////////////////////////////////////////////////