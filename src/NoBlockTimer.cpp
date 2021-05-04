#include "NoBlockTimer.h"

bool NoBlockTimer::timer(uint16_t tToPass) {
  if (millis() - tSinceChange >= tToPass) {
    tSinceChange = millis();
    return true;
  } else {
    return false;
  }
}