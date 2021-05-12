#ifndef PATTERNS_LIST_H
#define PATTERNS_LIST_H

#include "POV_pattern.h"
#include <vector>

const std::string path = "/spiffs/pov";

std::vector<Pattern *> patterns;

void buildList() {
  for (auto file : get_dir_content(path.c_str())) {
    std::string sp = "/spiffs/pov/" + file;
    Serial.println(sp.c_str());
    patterns.push_back(new POV_Pattern(sp.c_str()));
  }

  for (auto pattern : patterns) {
    pattern->PrintImgInfo(false);
  }
}

#endif