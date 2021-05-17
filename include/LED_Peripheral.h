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

// UTILITY FUNCTIONS
void LED_Peripheral_setup(); // Setup and configuration of fastled leds array
                             // and brightness settings

void LED_clear(); // Abstracted fastled function for use in other parts of code,
                  // overwrites current led buffer contents with NULL

void LED_show(); // Abstracted fastled function for use in other parts of code,
                 // wrapper function for the FastLED.show() method

void LED_startup_animation(); // display sequence played during device setup
                              // routine

void LED_indicateButtonHold(); // flashes green to confirm an action

void LED_showBatteryPercent(int reading); // takes an input from
                                          // get_battery_voltage and displays
                                          // the battery percent using leds
int LED_battVoltsToNUM_LEDS(int reading);

void LED_cycleBrightness(); // cycles through NUM_BRIGHTNESS_LEVELS of
                            // brightness settings, with MAX_BRIGHTNESS being
                            // the brightest allowable

void LED_POV(POV_Pattern &pattern); // used with POV patterns to display the
                                    // contents of _img, loads and shows the
                                    // next column each time the function is
                                    // called

// LED Pattern Functions
void LED_fill_solid();
void LED_fill_gradient();
void LED_accel_rainbow();

extern struct CRGB leds[];

#endif // LED_PERIPHERAL_H