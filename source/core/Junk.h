#pragma once
#include <string>

class Junk {
  public:
  std::string name;
  int size;
  int value;

  Junk();
  Junk(std::string jName, int jSize, int jValue);
};