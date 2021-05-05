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

std::vector<int> testVector;

void setup() {
  // Serial.begin(115200);

  sleep_setup();
  powerManagement_setup();
  LED_Peripheral_setup();
  button_setup();
  LED_cycleBrightness();
  LED_startup_animation();
  mpu_setup(8, 500, 44); // setup last because chip is slow to power on

  /////////////////////////////////////////////////////////////////////
  // debug development stuff

  // POV_Pattern *test4;
  // test4 = new POV_Pattern("/spiffs/my_skull.bmp");
  // test4->print_img_info();

  // for (int i = 0; i < 50; ++i) {
  //   delay(5000);
  //   test4->show();
  //   Serial.println();
  // }

  // while (1) {
  //   static NoBlockTimer t;
  //   if (t.timer(3)) {
  //     test4->show();
  //   }
  // }

  // sleep();
  // debug development stuff
  /////////////////////////////////////////////////////////////////////

} // END OF setup()

void loop() {

  btn.tick();

  patternArray[currentPatternNum]();
  LED_show();
}