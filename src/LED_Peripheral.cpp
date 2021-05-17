#define FASTLED_ALL_PINS_HARDWARE_SPI
#include "fastLED.h"

#include "LED_Peripheral.h"

FASTLED_USING_NAMESPACE

CRGB leds[NUM_LEDS];

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
  FastLED.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(i * (255 / NUM_LEDS), 255, 255);
    FastLED.show();
    delay(7);
  }
  delay(250);
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(250);
  for (int i = NUM_LEDS; i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(7);
  }
}
// END OF LED_startup_animation()
////////////////////////////////////////////////////

void LED_indicateButtonHold() {
  // Indicates how long the button has been held to the user to make navigating
  // hold menu options easier

  // ticks increases as the button is held.  Used determine the color of the
  // leds corresponding to each of the hold options
  static int ticks;
  const int ticksWaitTime = 4;
  static bool y1st{false}; // first run from reset for yellow
  static bool r1st{false}; // first run from reset for red

  // Only trigger this function if it hasn't ran in a while
  static NoBlockTimer firstRunInAWhile;
  if (firstRunInAWhile.timer(3000)) {
    FastLED.clear();
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    ticks = 400; // Button Hold starts at 750ms
    y1st = true;
    r1st = true;
  }

  if (y1st && ticks >= 750 && ticks <= 1500) {
    y1st = false;
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  } else if (r1st && ticks > 1500) {
    r1st = false;
    fill_solid(leds, NUM_LEDS, CRGB::Red);
  }

  // only increment ticks and trigger fadeToBlack according to ticksWaitTime
  static NoBlockTimer ticksCoolDown;
  if (ticksCoolDown.timer(ticksWaitTime)) {
    fadeToBlackBy(leds, NUM_LEDS, 1);
    ticks += ticksWaitTime;
  }
  FastLED.show();
}
// END OF LED_confirmGreen()
////////////////////////////////////////////////////

void LED_showBatteryPercent(int reading) {
  // takes reading from get_battery_voltage and animates the battery percent
  // Start color is red, endColor goes up to green for fully charged depending
  // on battery voltage
  // Pulses brightness while showing for added effect
  const int showTime = 800;
  static int ledsToLight = LED_battVoltsToNUM_LEDS(reading);

  FastLED.clear();
  // end color is green (96) when max, and red (0) when min
  byte endColor = 96 * ledsToLight / NUM_LEDS;

  // fill_gradient(leds, ledsToLight, CHSV(0, 255, 255), CHSV(endColor, 255,
  // 255),
  //               FORWARD_HUES);
  // FastLED.show();

  NoBlockTimer pulseLoop;
  while (!pulseLoop.timer(showTime)) {
    byte sineBrightness = beatsin8(72, 255 / 2, 255, 0, 0);
    fill_gradient(leds, ledsToLight, CHSV(0, 255, sineBrightness),
                  CHSV(endColor, 255, sineBrightness), FORWARD_HUES);
    FastLED.show();
  }
  delay(showTime);
}

int LED_battVoltsToNUM_LEDS(int reading) {
  // takes reading and maps it to NUM_LEDS
  const int minReading = 3200;
  const int maxReading = 4200;
  const int minLeds = 1;
  const int maxLeds = NUM_LEDS;
  // map reading to the range of NUM_LEDS
  int numLedsToLight = map(reading, minReading, maxReading, minLeds, maxLeds);
  // handle cases that exceed intended range
  if (numLedsToLight > NUM_LEDS) {
    numLedsToLight = NUM_LEDS;
  } else if (numLedsToLight <= 0) {
    numLedsToLight = 1;
  }
  return numLedsToLight;
}

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
