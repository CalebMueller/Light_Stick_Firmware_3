#ifndef POV_PATTERN_H
#define POV_PATTERN_H

#include "ESP_SPI_FS.h"
#include <stdio.h>

#include "Pattern.h"
#include <Arduino.h>
#include <vector>

class POV_Pattern : public Pattern {
public:
  POV_Pattern(const char *fileName);
  POV_Pattern(const byte *fileName[]);
  ~POV_Pattern() { Serial.println("POV_Pattern destructor called"); };

  void SetName(const char *fileName); // parses pattern name from fileName
  void PrintImgInfo();
  void PrintImgInfo(bool verbose);
  void Run();

  friend void LED_POV(POV_Pattern &pattern);

private:
  std::string _name{"empty"};
  uint32_t _width{0};
  uint32_t _height{0};
  std::vector<byte> _img; // Blue-Green-Red member sequence
};

#endif // POV_PATTERN_H