#ifndef PATTERN_H
#define PATTERN_H

#include <string>

class Pattern {
public:
  virtual void run();
  std::string getName() { return _name; }

private:
  std::string _name;
};

#endif // PATTERN_H