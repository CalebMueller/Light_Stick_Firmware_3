#include "POV_Pattern.h"

POV_Pattern::POV_Pattern(const char *fileName) {
  // Constructor reads image data from fileName, assigns it to pixels, and
  // parses pixels into class member vector _img
  // example constructor call: POV_Pattern test("/spiffs/example.bmp");

  // temporary container variables for ReadImage
  byte *pixels; // data in BGR pixel order
  int32 width;
  int32 height;
  int32 bytesPerPixel;

  ReadImage(fileName, &pixels, &width, &height, &bytesPerPixel);

  SetName(fileName);
  _width = width;
  _height = height;
  _img = std::vector<byte>(_height * _width * bytesPerPixel);

  for (int i = 0; i < _width; ++i) {
    for (int j = 0; j < (_height - 1); j++) {

      uint16_t a = bytesPerPixel * (i + j * _height);
      uint16_t b = bytesPerPixel * (j + i * _width);

      _img[a] = pixels[b];
      _img[a + 1] = pixels[b + 1];
      _img[a + 2] = pixels[b + 2];

      // _img.push_back(pixels[3 * (i + j)]);
      // _img.push_back(pixels[3 * (i + j) + 1]);
      // _img.push_back(pixels[3 * (i + j) + 2]);
    }
  }

  // free up malloc
  free(pixels);
}
// END OF POV_Pattern constructor
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::PrintImgInfo() {
  Serial.print("\n");
  Serial.printf("%s's img info: width: %dheight: %d\n", _name.c_str(), _width,
                _height);
} // end default PrintImgInfo()
void POV_Pattern::PrintImgInfo(bool verbose) {
  Serial.print("\n");
  Serial.printf("%s's img info: width: %dheight: %d\n", _name.c_str(), _width,
                _height);
  if (verbose) {
    Serial.printf("POV Pattern's height=%d, width=%d \n", _height, _width);
    for (int i = 0; i < _img.size(); ++i) {
      Serial.print(_img[i]);
      Serial.print(", ");
    }
    Serial.print("\n\n");
  }
} // end overloaded PrintImgInfo(bool)
// END OF POV_Pattern::print_img() and print_image(bool verbose)
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::Run() { LED_POV(*this); }
// END OF POV_Pattern::show()
///////////////////////////////////////////////////////////////////////////

void POV_Pattern::SetName(const char *fileName) {
  // parses pattern name from fileName and assigns to member _name
  std::string str(fileName);
  std::size_t s_pos = str.find("/spiffs/") + size_t(8);
  // truncate ".bmp"
  std::size_t span = str.length() - s_pos - 4;
  _name = str.substr(s_pos, span);
}
