#ifndef SLEEP_H
#define SLEEP_H

#include "LED_Peripheral.h"
#include "PowerManagement.h"
#include <Arduino.h>

// includes for keeping enable pin pulled high to disable pchannel FET during
// deepsleep
#include "driver/rtc_io.h"
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"

void sleep_setup();
void sleep();

#endif // SLEEP_H