#ifndef PATTERN_HANDLER_H
#define PATTERN_HANDLER_H

#include "ESP_SPI_FS.h"
#include "LED_Peripheral.h"
#include "POV_pattern.h"
#include <vector>

class Pattern_Handler {
public:
  Pattern_Handler();
  ~Pattern_Handler(){};

  void BuildList(); // constructs patternList using imageFiles located in the
                    // directory
  void PrintListInfo(); // Serial.prints pattern info of patternList contents
  void NextPattern(); // Advances _currentPattern by one, wraps to start at end
  void Run(); // calls the _patternList[_currentPattern]->Run() object member
  void ToggleAutoPlay();

private:
  int _autoPlaySeconds{2};
  bool _isAutoPlay{false};
  uint16_t _currentPattern{0};
  std::vector<Pattern *> _patternList;
};

extern Pattern_Handler patterns;

// std::vector<Pattern *> patterns;

#endif // PATTERN_HANDLER_H