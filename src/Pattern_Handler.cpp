#include "Pattern_Handler.h"

// Extern instantiation
Pattern_Handler patterns;

#define FILE_DIR "/spiffs/"

Pattern_Handler::Pattern_Handler() {}

void Pattern_Handler::BuildList() {
  // fills _patternList with constructed patterns

  // Iterate over contents of FILE_DIR
  for (auto fileName : get_dir_content(FILE_DIR)) {

    // Handle POV_image cases //
    // if fileName is an image (ends in bmp),
    // construct a POV_Pattern for the file and add it to _patternList
    if (fileName.substr(fileName.length() - 3, fileName.length()) == "bmp") {
      std::string filePath = FILE_DIR + fileName;
      _patternList.emplace_back(new POV_Pattern(filePath.c_str()));
    }
  }
} // end of Pattern_Handler::BuildList()

void Pattern_Handler::PrintListInfo() {
  for (auto pattern : _patternList) {
    pattern->PrintImgInfo(false);
  }
} // end of Pattern_Handler::PrintListInfo()

void Pattern_Handler::NextPattern() {
  _currentPattern = (_currentPattern + 1) % _patternList.size();
  Serial.println(_patternList[_currentPattern]->GetName().c_str());
} // end of Pattern_Handler::NextPattern()

void Pattern_Handler::Run() {
  // if autoplay is turned on
  if (_isAutoPlay) {
    // go to next pattern every N seconds
    static NoBlockTimer hasWaited;
    if (hasWaited.timer(_autoPlaySeconds * 1000)) {
      NextPattern();
    }
  }
  _patternList[_currentPattern]->Run();
} // end of Pattern_Handler::Run()

void Pattern_Handler::ToggleAutoPlay() {
  Serial.print("Auto Play toggled ");
  if (_isAutoPlay) {
    _isAutoPlay = false;
    Serial.println("off");
  } else if (!_isAutoPlay) {
    _isAutoPlay = true;
    Serial.println("on");
  }
}