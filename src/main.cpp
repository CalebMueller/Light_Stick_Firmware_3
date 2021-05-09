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

#define FILEPATH "/spiffs"

void setup() {
  Serial.begin(115200);

  sleep_setup();
  powerManagement_setup();
  LED_Peripheral_setup();
  button_setup();
  LED_cycleBrightness();
  LED_startup_animation();
  mpu_setup(8, 500, 44); // setup last because mpu chip is slow to power on

  esp_spiffs_enable();
  show_dir_content(FILEPATH);

} // END OF setup()

void loop() {

  btn.tick();

  patternArray[currentPatternNum]();
  LED_show();
}