#pragma once
#include <string>
#include "Fish.h"
#include "Junk.h"
#include "Rod.h"

class Player {
  public:
  int currency = 20;
  std::vector<Fish> fishBasket;
  std::vector<Junk> junkBasket;
  Rod currentRod;
  std::vector<Rod> ownedRods;
};