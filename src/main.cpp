////////////////////////////////////////////////////////////////////
//                                                                //
//             Light stick prototype board firmware               //
//             Written 27 April, 2021 by Caleb Mueller            //
//                                                                //
////////////////////////////////////////////////////////////////////

/*
Pin	        Net
15	      button
23	      led_dat
18	      led_clk
21	      mpu_dat
22	      mpu_clk
14	      led_en
33	      mpu_en
*/

#include "Accelerometer_Functions.h"
#include "Button.h"
#include "LED_Peripheral.h"
#include "NoBlockTimer.h"
#include "PowerManagement.h"
#include "Sleep.h"
#include <Arduino.h>

#include "Pattern_Handler.h"

void setup() {
  Serial.begin(115200);

  powerManagement_setup();
  sleep_setup();
  LED_Peripheral_setup();
  button_setup();

  LED_cycleBrightness();
  check_for_low_battery();
  LED_startup_animation();
  LED_showBatteryPercent(get_battery_voltage());

  mpu_setup(8, 500, 44); // setup last because mpu chip is slow to power on
  esp_spiffs_enable();

  patterns.BuildList();
  // patterns.PrintListInfo();

} // end of setup()

void loop() {

  btn.tick();

  static NoBlockTimer t;
  if (t.timer(4) && !btn.isLongPressed()) {
    patterns.Run();
  }

  static NoBlockTimer low_batt_check;
  if (low_batt_check.timer(10000)) {
    check_for_low_battery();
  }

} // end of loop()