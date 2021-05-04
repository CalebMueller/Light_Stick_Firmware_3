#include "PowerManagement.h"

#define LED_EN_PIN GPIO_NUM_14
#define MPU_EN_PIN GPIO_NUM_33

// PowerRail instantiations
PowerRail led_rail(LED_EN_PIN, false);
PowerRail mpu_rail(MPU_EN_PIN, false);

//////////////////////////////////////////////
// FUNCTION DEFINITIONS

void PowerRail::setup() {
  pinMode(_enPin, OUTPUT);
  if (Serial) {
    Serial.print(_enPin);
    Serial.print(" set to ");
  }
  this->enable();
}

void PowerRail::enable() {
  // enables the power rail
  if (_activeLow) {
    digitalWrite(_enPin, HIGH);
  } else {
    digitalWrite(_enPin, LOW);
  }
  Serial.println("Enabling");
  isEnabled = true;
}

void PowerRail::disable() {
  // disables the power rail
  if (_activeLow) {
    digitalWrite(_enPin, LOW);
  } else {
    digitalWrite(_enPin, HIGH);
  }
  Serial.println("Disabling");
  isEnabled = false;
}

void PowerRail::toggle() {
  // changes enable/disable state to opposite of what it is currently
  if (isEnabled) {
    this->disable();
  } else {
    this->enable();
  }
}

void powerManagement_setup() {
  // Setup function calls relevant to powermanagement
  led_rail.setup();
  mpu_rail.setup();
}
// end of powerManagement_setup()
/////////////////////////////////////////////////////

int poll_battery() {
  // polls battery voltage divider analog pin and returns an average of
  // the reading over n_times (defined const within function)
  int batt_reading{0};
  const byte n_times{10};
  for (int i = 0; i < n_times; i++) {
    batt_reading = batt_reading + analogRead(BATT_CHARGE_ADC_PIN);
  }
  return (batt_reading / n_times);
}
// END OF poll_battery()
//////////////////////////////////////////////////////
