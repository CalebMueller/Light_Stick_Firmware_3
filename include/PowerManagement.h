#ifndef POWERMANAGEMENT_H
#define POWERMANAGEMENT_H

// included LED_Peripheral for display_battry_level() function
#include "LED_Peripheral.h"

// includes for reading adc to determine battery_level
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <Arduino.h>

#include "Sleep.h"

#define LED_EN_PIN GPIO_NUM_14
#define MPU_EN_PIN GPIO_NUM_33

#define BATT_CHARGE_ADC_PIN 35

///////////////////////////////////////////////////////
// Declaration and in-line definition of PowerRail class
class PowerRail {
public:
  PowerRail(gpio_num_t enPin, bool activeLow)
      : _enPin{enPin}, _activeLow{activeLow} {}

  void setup(); // Serialprints a confirmation, and enables
  void enable();
  void disable();
  void toggle(); // toggle enable state of the powerRail
  gpio_num_t pin() { return _enPin; }

private:
  gpio_num_t _enPin;
  bool _activeLow;
  bool isEnabled;
};

extern PowerRail led_rail;
extern PowerRail mpu_rail;

void powerManagement_setup(); // Setup function calls relevant to
                              // powermanagement
int get_battery_voltage();    // Returns an approximate current battery voltage,
                              // scaled by 100
void check_for_low_battery(); // Puts device to sleep if voltage is below
                              // over-discharge threshold

#endif // POWERMANAGEMENT_H