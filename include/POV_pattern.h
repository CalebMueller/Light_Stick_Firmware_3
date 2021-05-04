#ifndef POV_PATTERN_H
#define POV_PATTERN_H

#include "FS.h"
#include "SPIFFS.h"
#include <Arduino.h>
#include <vector>

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;

class POV_Pattern {
public:
  POV_Pattern(const char *fileName);

  ~POV_Pattern() { Serial.println("POV_Pattern destructor called"); };

  void print_img_info();
  void show();
  void ReadImage(const char *fileName, byte **pixels, int32 *width,
                 int32 *height, int32 *bytesPerPixel);
  friend void LED_POV(POV_Pattern &pattern);

private:
  uint32_t _width{0};
  uint32_t _height{0};
  std::vector<byte> _img; // Blue-Green-Red member sequence
};

#endif // POV_PATTERN_H