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
  Serial.println("Constructor Called");

  _width = width;
  _height = height;

  for (int i = 0; i < (width * height * bytesPerPixel); i++) {
    _img.push_back(pixels[i]);
  }

  // free up malloc
  free(pixels);
}
// END OF POV_Pattern constructor
///////////////////////////////////////////////////////////

void POV_Pattern::print_img_info() {
  Serial.print("\n\n");

  Serial.printf("POV Pattern's height=%d, width=%d \n", _height, _width);
  for (int i = 0; i < _width; ++i) {
    for (int j = 0; j < _height; ++j) {
      Serial.print(_img[j * i]);
      Serial.print(", ");
    }
  }

  Serial.print("\n\n");
}
// END OF POV_Pattern::print_img()
///////////////////////////////////////////////////////////

// void POV_Pattern::show() {
//   static uint32_t column{0};
//   for (int i = 0; i < _height; ++i) {

//     uint32_t i_offset = 3 * (i + column * _height);

//     // Serial.print("B");
//     // Serial.print(_img[i_offset]);
//     // Serial.print(" G");
//     // Serial.print(_img[i_offset + 1]);
//     // Serial.print(" R");
//     // Serial.println(_img[i_offset + 2]);
//     // Serial.print(" ");
//   }
//   column = (column + 1) % _width;
// }
// END OF POV_Pattern::show()
///////////////////////////////////////////////////////////

// Defines relevant to ReadImage:
#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

void POV_Pattern::ReadImage(const char *fileName, byte **pixels, int32 *width,
                            int32 *height, int32 *bytesPerPixel) {
  File imageFile = SPIFFS.open(fileName, "r");

  int32 dataOffset;
  imageFile.seek(DATA_OFFSET_OFFSET, SeekSet);
  imageFile.readBytes((char *)&dataOffset, 4);
  imageFile.seek(WIDTH_OFFSET, SeekSet);
  imageFile.readBytes((char *)width, 4);
  imageFile.seek(HEIGHT_OFFSET, SeekSet);
  imageFile.readBytes((char *)height, 4);

  int16 bitsPerPixel;
  imageFile.seek(BITS_PER_PIXEL_OFFSET, SeekSet);
  imageFile.readBytes((char *)&bitsPerPixel, 2);
  *bytesPerPixel = ((int32)(bitsPerPixel) / 8);

  int paddedRowSize =
      (int)(4 * ceil((float)(*width) / 4.0f)) * (*bytesPerPixel);
  int unpaddedRowSize = (*width) * (*bytesPerPixel);
  int totalSize = unpaddedRowSize * (*height);
  *pixels = (byte *)malloc(totalSize);
  int i = 0;

  byte *currentRowPointer = *pixels + ((*height - 1) * unpaddedRowSize);

  for (i = 0; i < *height; i++) {
    imageFile.seek(dataOffset + (i * paddedRowSize), SeekSet);
    imageFile.readBytes((char *)currentRowPointer, unpaddedRowSize);
    currentRowPointer -= unpaddedRowSize;
  }
  imageFile.close();
}
// END OF POV_Pattern::ReadImage()
///////////////////////////////////////////////////////////
