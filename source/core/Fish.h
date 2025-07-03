#pragma once
#include <string>

class Fish {
public:
  std::string name;
  int size;
  int value;

  Fish();  // Constructor
  Fish(std::string fName, int fSize, int fValue);  // Constructor
};