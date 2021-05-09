#ifndef PATTERN_H
#define PATTERN_H

#include <string>

class Pattern {
protected:
  std::string _name;

public:
  void run();
  std::string getName() { return _name; }
};

#endif // PATTERN_H