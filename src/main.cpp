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
#include "LED_Peripheral.h"

#include "Accelerometer_Functions.h"
#include "Button.h"
#include "NoBlockTimer.h"
#include "POV_pattern.h"
#include "PowerManagement.h"
#include "Sleep.h"
#include <Arduino.h>
#include <vector>

#include "FS.h"
#include <SPIFFS.h>

#define FORMAT_SPIFFS_IF_FAILED true

std::vector<int> testVector;

void setup() {
  Serial.begin(115200);

  sleep_setup();
  powerManagement_setup();
  LED_Peripheral_setup();
  button_setup();

  LED_cycleBrightness();
  LED_startup_animation();

  mpu_setup(8, 500, 44);

  // /////////////////SPIFFS SETUP /////////////////
  // if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
  //   Serial.println("SPIFFS Mount Failed");
  //   return;
  // }
  // /////////////////SPIFFS SETUP /////////////////

  // // POV_Pattern *test4;
  // // test4 = new POV_Pattern("/smiley.bmp");
  // // test4->print_img_info();

  // // while (1) {
  // //   test4->show();
  // // }
}

void loop() {

  btn.tick();

  patternArray[currentPatternNum]();
  LED_show();
}