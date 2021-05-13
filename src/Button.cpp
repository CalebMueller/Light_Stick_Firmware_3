#include "Button.h"

#define DEBOUNCE_TIME 7
#define DOUBLECLICK_TIME 300
#define LONGPRESS_TIME 400

#define REGISTER_TOGGLE_AUTOPLAY 750

OneButton btn = OneButton(BUTTON_PIN, // Input pin for the button
                          true,       // Button is active LOW
                          true        // Enable internal pull-up resistor
                          );

void button_setup() {
  btn.setDebounceTicks(DEBOUNCE_TIME); // debounce trigger threshold
  btn.setClickTicks(DOUBLECLICK_TIME); // double click trigger threshold
  btn.setPressTicks(LONGPRESS_TIME);   // duration to trigger a long press

  // Event attachment
  btn.attachClick(singleClick);
  btn.attachDoubleClick(doubleClick);
  btn.attachDuringLongPress(duringLongPress);
  btn.attachLongPressStop(longPress);
}
// END OF button_setup()
///////////////////////////////////////////////////////////

////////////////////////////
// Press Event Function Definitions
////////////////////////////

void singleClick() {
  // Serial.println("singleClick");
  // LED_nextPattern();
  patterns.NextPattern();
}

void doubleClick() {
  // Serial.println("doubleClick");
  LED_cycleBrightness();
}

void duringLongPress() {
  if (btn.getPressedTicks() >= LONGPRESS_TIME) {
    LED_indicateButtonHold();
  }
  if (btn.getPressedTicks() >= 2250) {
    sleep();
  }
}

void longPress() {
  if ((btn.getPressedTicks() >= REGISTER_TOGGLE_AUTOPLAY) &&
      (btn.getPressedTicks() < 1500)) {
    patterns.ToggleAutoPlay();
    // Serial.println("shortHold");
  }
  if ((btn.getPressedTicks() >= 1500) && (btn.getPressedTicks() < 1800)) {
    // Serial.println("mediumHold");
  }
  /*
  if (btn.getPressedTicks() >= 3000) {
    Serial.println("longHold");
  }
  */
}