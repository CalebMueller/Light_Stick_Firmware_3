#include "Sleep.h"

void sleep_setup() {

  Serial.println("Waking up...");
  // disabling pin holds placed in sleep function
  gpio_deep_sleep_hold_dis();
  gpio_hold_dis(led_rail.pin());
  gpio_hold_dis(mpu_rail.pin());

  // external wakeup on pin 15, wakeup when switch goes LOW
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 0);
}

void sleep() {
  Serial.println("Going to sleep");

  // clear out any of the colors
  LED_clear();

  // disable led_rail and hold the diabled state during sleep
  led_rail.disable();
  gpio_hold_en(led_rail.pin());
  // disable mpu_rail and hold the diabled state during sleep
  mpu_rail.disable();
  gpio_hold_en(mpu_rail.pin());

  // hold led and mpu enable pins to disable during sleep
  // This will be unnessessary with revisions to the hardware so that gate is
  // pulled high to vBatt using an appropriately sized voltage divider to
  // deliver ~3.5V while not being pulled low via GPIO
  gpio_deep_sleep_hold_en();

  // give time for user to remove finger from button
  delay(1000);
  esp_deep_sleep_start();
}