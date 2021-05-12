#ifndef POV_PATTERN_H
#define POV_PATTERN_H

#include "ESP_SPI_FS.h"
#include <stdio.h>

#include "Pattern.h"
#include <Arduino.h>
#include <vector>

class POV_Pattern : public Pattern {
public:
  // Constructors and Destructor
  POV_Pattern(const char *fileName);
  ~POV_Pattern() { Serial.println("POV_Pattern destructor called"); };

  // Virtual function overrides
  void Run() override;
  void PrintImgInfo(bool verbose) override;

  // Getters
  uint32_t get_width() { return _width; }
  uint32_t get_height() { return _height; }
  std::string get_name() { return _name; }

  friend void LED_POV(POV_Pattern &pattern);

private:
  void SetName(const char *fileName); // parses pattern name from fileName

  std::string _name{"empty"};
  uint32_t _width{0};
  uint32_t _height{0};
  std::vector<byte> _img; // Blue-Green-Red member sequence
};

#endif // POV_PATTERN_H