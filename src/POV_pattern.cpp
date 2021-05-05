#include "POV_Pattern.h"

POV_Pattern::POV_Pattern(const char *fileName) {
  // Constructor reads image data from fileName, assigns it to pixels, and
  // parses in pixels' elements into _img class member vector
  // example function call: POV_Pattern test("test.bmp");

  // temporary container variables for ReadImage
  byte *pixels; // data in BGR pixel order
  int32 width;
  int32 height;
  int32 bytesPerPixel;

  ReadImage(fileName, &pixels, &width, &height, &bytesPerPixel);
  Serial.println("\nConstructor Called");

  _width = width;
  _height = height;

  for (int i = 0; i < (width * height * bytesPerPixel); i++) {
    _img.push_back(pixels[i]);
    // Serial.print(pixels[i]);
    // Serial.print(", ");
  }

  // free up malloc
  free(pixels);
}
// END OF POV_Pattern constructor
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::print_img_info() {
  Serial.print("\n\n");

  Serial.printf("POV Pattern's height=%d, width=%d \n", _height, _width);
  for (int i = 0; i < _img.size(); ++i) {
    Serial.print(_img[i]);
    Serial.print(", ");
  }
  Serial.print("\n\n");
}

// END OF POV_Pattern::print_img()
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::run() { LED_POV(*this); }
// END OF POV_Pattern::show()
///////////////////////////////////////////////////////////////////////////
