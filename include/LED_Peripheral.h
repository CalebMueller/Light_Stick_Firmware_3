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
void LED_Peripheral_setup();
void LED_clear();
void LED_show();
void LED_startup_animation();
void LED_cycleBrightness();
void LED_nextPattern();

// Patterns
void LED_fill_solid();
void LED_fill_gradient();
void LED_accel_rainbow();

void LED_POV(POV_Pattern &pattern);

typedef void (*PatternArray[])();
extern PatternArray patternArray;
extern int currentPatternNum;
extern struct CRGB leds[];

#endif // LED_PERIPHERAL_H