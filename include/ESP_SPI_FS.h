#ifndef ESP_SPI_FS_H
#define ESP_SPI_FS_H

#include "esp_spiffs.h"
#include <Arduino.h>

// Might not need these, keeping around just in case
//**originally from esp_spiffs example file
//#include <sys/unistd.h>
//#include "esp_err.h"
//#include "esp_log.h"
//#include <sys/stat.h>

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;

void esp_spiffs_enable();

void esp_spiffs_disable();

void ReadImage(const char *fileName, byte **pixels, int32 *width, int32 *height,
               int32 *bytesPerPixel);

#endif // ESP_SPI_FS_H
