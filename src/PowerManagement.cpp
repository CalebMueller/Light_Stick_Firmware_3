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

int get_battery_voltage() {
  // Returns an approximate current battery voltage, scaled by 1000
  // IE 4.20V == 4200, 3.70V == 3700

  // poll battery voltage for an average reading over n_times
  int battReading{0};
  const byte n_times{30};
  for (int i = 0; i < n_times; i++) {
    battReading = battReading + analogRead(BATT_CHARGE_ADC_PIN);
  }
  battReading = battReading / n_times;

  // equation is from experimentally derived linear relationship
  // between battReading and actual battVoltage
  return ((battReading + 230) * 1000) / 353;
}
// END OF poll_battery()
//////////////////////////////////////////////////////

void check_for_low_battery() {
  // Puts device to sleep if voltage is below over-discharge threshold
  int battVoltage = get_battery_voltage();
  if (battVoltage < 3180) {
    LED_showBatteryPercent(battVoltage);
    sleep();
  }
}
// END OF check_battery()
//////////////////////////////////////////////////////
