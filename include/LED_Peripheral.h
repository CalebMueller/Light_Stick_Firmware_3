#ifndef LED_PERIPHERAL_H
#define LED_PERIPHERAL_H

#include "Accelerometer_Functions.h"
#include "NoBlockTimer.h"
#include "POV_pattern.h"

#define DATA_PIN 23
#define CLOCK_PIN 18
#define NUM_LEDS 32
#define MAX_BRIGHTNESS 70       // 255 is maximum value
#define NUM_BRIGHTNESS_LEVELS 4 // Macro used in cycleBrightness()

// Utility Functions
void LED_Peripheral_setup(); // Setup and configuration of fastled leds array
                             // and brightness settings
void LED_clear(); // Abstracted fastled function for in other parts of code,
                  // clears current led buffer with NULL
void LED_show();  // Abstracted fastled function for use in other parts of code,
                  // wrapper function for the FastLED.show() method
void LED_startup_animation(); // display sequence played at start up
void LED_cycleBrightness();   // cycles through NUM_BRIGHTNESS_LEVELS of
                              // brightness settings, with MAX_BRIGHTNESS being
                              // the brightest allowable
void LED_nextPattern(); // cycles through patternArray, wrapping to beginning
                        // once the end is reached
void LED_POV(POV_Pattern &pattern); // used with POV patterns to display the
                                    // contents of _img, loads and shows the
                                    // next column each time the function is
                                    // called

// Pattern patterns vector functions
void BuildPatternList();

// LED Pattern Functions
void LED_fill_solid();
void LED_fill_gradient();
void LED_accel_rainbow();

// POV Pattern Functions
void POV_smiley();
void POV_skull();
void POV_red_among_us();
void POV_red_among_us_ribbon();
void POV_dna();

typedef void (*PatternArray[])();
extern PatternArray patternArray;
extern int currentPatternNum;
extern struct CRGB leds[];

#endif // LED_PERIPHERAL_H