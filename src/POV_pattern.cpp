#include "POV_Pattern.h"

POV_Pattern::POV_Pattern(const char *fileName) {
  // Constructor uses ReadImage to get image data from fileName, reorients it so
  // the data is vertically sequential in _img
  // example constructor call: POV_Pattern test("/spiffs/pov/example.bmp");

  // temporary container variables for ReadImage
  byte *pixels; // data in BGR pixel order
  int32 width;
  int32 height;
  int32 bytesPerPixel;

  ReadImage(fileName, &pixels, &width, &height, &bytesPerPixel);

  SetName(fileName);
  _width = width;
  _height = height;
  _img = std::vector<byte>(height * width * bytesPerPixel);

  for (int column = 0; column < width; ++column) {
    for (int row = 0; row < height; ++row) {
      uint32_t a = bytesPerPixel * (row + column * height);
      uint32_t b = bytesPerPixel * (column + row * width);
      _img[a] = pixels[b];
      _img[a + 1] = pixels[b + 1];
      _img[a + 2] = pixels[b + 2];
    }
  }

  // free up malloc
  free(pixels);
}
// END OF POV_Pattern constructor
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::PrintImgInfo(bool verbose) {
  Serial.printf("%s's _img info: width: %d height: %d\n", _name.c_str(), _width,
                _height);

  if (verbose) {
    // print out _img Data
    for (int row = 0; row < _height; ++row) {
      for (int column = 0; column < _width; ++column) {
        uint32_t offset = 3 * (_height * column + row);

        Serial.printf("(%d,%d,%d) ", _img[offset], _img[offset + 1],
                      _img[offset + 2]);
      }
      Serial.println();
    }
    Serial.print("\n\n");
  }
}
// END OF POV_Pattern::PrintImgInfo(bool)
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::Run() { LED_POV(*this); }
// END OF POV_Pattern::show()
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::SetName(const char *fileName) {
  // parses pattern name from fileName and assigns to member _name
  std::string str(fileName);
  std::size_t s_pos = str.find("/spiffs/pov/") + size_t(12);
  // truncate ".bmp"
  std::size_t span = str.length() - s_pos - 4;
  _name = str.substr(s_pos, span);
}
// END OF POV_Pattern::SetName()
///////////////////////////////////////////////////////////////////////////
