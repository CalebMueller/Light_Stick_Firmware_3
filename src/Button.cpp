#include "Button.h"
#include "LED_Peripheral.h"
#include "Sleep.h"

OneButton btn = OneButton(BUTTON_PIN, // Input pin for the button
                          true,       // Button is active LOW
                          true        // Enable internal pull-up resistor
                          );

void button_setup() {
  btn.setDebounceTicks(7); // debounce trigger threshold
  btn.setClickTicks(300);  // double click trigger threshold
  btn.setPressTicks(750);  // duration to trigger a long press

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
  Serial.println("singleClick");
  LED_nextPattern();
}

void doubleClick() {
  Serial.println("doubleClick");
  LED_cycleBrightness();
}

void duringLongPress() {
  if (btn.getPressedTicks() >= 2250) {
    sleep();
  }
}

void longPress() {
  if ((btn.getPressedTicks() >= 750) && (btn.getPressedTicks() < 1500)) {
    Serial.println("shortHold");
  }
  if ((btn.getPressedTicks() >= 1500) && (btn.getPressedTicks() < 1800)) {
    Serial.println("mediumHold");
  }
  /*
  if (btn.getPressedTicks() >= 3000) {
    Serial.println("longHold");
  }
  */
}