#ifndef PATTERN_H
#define PATTERN_H

#include <string>

class Pattern {
protected:
  std::string _name;

public:
  virtual void Run(){};
  virtual void PrintImgInfo(bool verbose){};
  std::string GetName() { return _name; }
};

#endif // PATTERN_H