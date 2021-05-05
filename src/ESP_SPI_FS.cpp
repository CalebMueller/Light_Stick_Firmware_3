#include "ESP_SPI_FS.h"

void esp_spiffs_enable() {
  Serial.println("Initializing SPIFFS");
  esp_vfs_spiffs_conf_t conf = {.base_path = "/spiffs",
                                .partition_label = NULL,
                                .max_files = 5,
                                .format_if_mount_failed = true};
  // Use settings defined above to initialize and mount SPIFFS filesystem.
  // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
  esp_err_t ret = esp_vfs_spiffs_register(&conf);
  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      Serial.println("Failed to mount or format filesystem");
    } else if (ret == ESP_ERR_NOT_FOUND) {
      Serial.println("Failed to find SPIFFS partition");
    } else {
      Serial.println("Failed to initialize SPIFFS");
    }
    return;
  }
  size_t total = 0, used = 0;
  ret = esp_spiffs_info(NULL, &total, &used);
  Serial.printf("Partition size: total: %d, used: %d", total, used);
} // end of esp_spiffs_enable()
///////////////////////////////////////////////////////////////////////////

void esp_spiffs_disable() {
  // All done, unmount partition and disable SPIFFS
  esp_vfs_spiffs_unregister(NULL);
  ESP_LOGI(TAG, "SPIFFS unmounted");
} // end of esp_spiffs_disable()
///////////////////////////////////////////////////////////////////////////

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
void ReadImage(const char *fileName, byte **pixels, int32 *width, int32 *height,
               int32 *bytesPerPixel) {

  esp_spiffs_enable();

  FILE *imageFile = fopen(fileName, "rb");
  int32 dataOffset;
  fseek(imageFile, DATA_OFFSET_OFFSET, SEEK_SET);
  fread(&dataOffset, 4, 1, imageFile);
  fseek(imageFile, WIDTH_OFFSET, SEEK_SET);
  fread(width, 4, 1, imageFile);
  fseek(imageFile, HEIGHT_OFFSET, SEEK_SET);
  fread(height, 4, 1, imageFile);
  int16 bitsPerPixel;
  fseek(imageFile, BITS_PER_PIXEL_OFFSET, SEEK_SET);
  fread(&bitsPerPixel, 2, 1, imageFile);
  *bytesPerPixel = ((int32)bitsPerPixel) / 8;

  int paddedRowSize =
      (int)(4 * ceil((float)(*width) / 4.0f)) * (*bytesPerPixel);
  int unpaddedRowSize = (*width) * (*bytesPerPixel);
  int totalSize = unpaddedRowSize * (*height);
  *pixels = (byte *)malloc(totalSize);
  int i = 0;
  byte *currentRowPointer = *pixels + ((*height - 1) * unpaddedRowSize);
  for (i = 0; i < *height; i++) {
    fseek(imageFile, dataOffset + (i * paddedRowSize), SEEK_SET);
    fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
    currentRowPointer -= unpaddedRowSize;
  }

  esp_spiffs_disable();
  fclose(imageFile);
} // end of ReadImage()