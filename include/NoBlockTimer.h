#ifndef NOBLOCKTIMER_H
#define NOBLOCKTIMER_H

#include <Arduino.h>

class NoBlockTimer {
public:
  // Non blocking delay function
  bool timer(uint16_t tToPass);

private:
  unsigned long tSinceChange{0};
};

#endif // NOBLOCKTIMER_H