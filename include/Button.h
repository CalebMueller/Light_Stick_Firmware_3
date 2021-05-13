#ifndef BUTTON_H
#define BUTTON_H

#include "LED_Peripheral.h"
#include "Pattern_Handler.h"
#include "Sleep.h"
#include <Arduino.h>
#include <OneButton.h>

#define BUTTON_PIN 15

void button_setup();
void singleClick();
void doubleClick();
void duringLongPress();
void longPress();

///////////////////////////////////////
// Press Event Function Definitions
//////////////////////////////////////
void singleClick();
void doubleClick();
void duringLongPress();
void longPress();

extern OneButton btn;

#endif // BUTTON_H