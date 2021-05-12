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
  Serial.printf("Partition size: total: %d, used: %d \n", total, used);
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

void ReadImage(const char *fileName, byte **pixels, int32 *width, int32 *height,
               int32 *bytesPerPixel) {

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

  int paddedRowSize = (((*width) * (*bytesPerPixel) + 3) / 4) * 4;
  int unpaddedRowSize = (*width) * (*bytesPerPixel);
  int totalSize = unpaddedRowSize * (*height);

  *pixels = (byte *)malloc(totalSize);
  byte *currentRowPointer = *pixels + ((*height - 1) * unpaddedRowSize);

  for (int i = 0; i <= *height; ++i) {
    fseek(imageFile, dataOffset + (i * paddedRowSize), SEEK_SET);
    fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
    currentRowPointer -= unpaddedRowSize;
  }
  fclose(imageFile);
}
// end of ReadImage()
/////////////////////////////////////////////////////////////////////////////////

void show_dir_content(char *path) {
  // recursive function to print the content of a given folder
  DIR *d = opendir(path); // open the path
  if (d == NULL)
    return;           // if was not able return
  struct dirent *dir; // for the directory entries
  while ((dir = readdir(d)) !=
         NULL) // if we were able to read somehting from the directory
  {
    if (dir->d_type !=
        DT_DIR) // if the type is not directory print it to serial monitor
      Serial.println(dir->d_name);
    else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
             strcmp(dir->d_name, "..") != 0) // if it is a directory
    {
      char d_path[255]; // here I am using sprintf which is safer than strcat
      sprintf(d_path, "%s/%s", path, dir->d_name);
      show_dir_content(d_path); // recall with the new path
    }
  }
  closedir(d); // finally close the directory
}
// end of show_dir_contents()
//////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> get_dir_content(const char *path) {
  // returns a string vector containing the contents of the directory

  std::vector<std::string> contents;

  DIR *d = opendir(path); // open the path
  if (d == NULL)
    return contents; // if was not able return

  struct dirent *dir; // for the directory entries
  while ((dir = readdir(d)) !=
         NULL) // if we were able to read somehting from the directory
  {
    if (dir->d_type != DT_DIR) {
      std::string entry(dir->d_name);
      contents.emplace_back(entry);
    } // if the type is not directory print it to serial monitor
  }
  closedir(d); // finally close the directory
  return contents;
}
// end of get_dir_contents()
//////////////////////////////////////////////////////////////////////////////////
