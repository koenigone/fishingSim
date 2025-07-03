#include "Fish.h"

Fish::Fish() : name(""), size(0), value(0) {}

Fish::Fish(std::string fName, int fSize, int fValue)
    : name(fName), size(fSize), value(fValue) {}