#ifndef ESP_SPI_FS_H
#define ESP_SPI_FS_H

#include "esp_spiffs.h"
#include <Arduino.h>

#include <dirent.h>
#include <stdio.h>
#include <string.h>

//#include <string>
#include <vector>

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;

void esp_spiffs_enable();

void esp_spiffs_disable();

void ReadImage(const char *fileName, byte **pixels, int32 *width, int32 *height,
               int32 *bytesPerPixel);

void show_dir_content(char *path);
std::vector<std::string> get_dir_content(const char *path);

#endif // ESP_SPI_FS_H
