#include "Junk.h"

Junk::Junk() : name(""), size(0), value(0) {}
Junk::Junk(std::string jName, int jSize, int jValue) {
  name = jName;
  size = jSize;
  value = jValue;
}