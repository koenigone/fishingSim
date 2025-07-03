#pragma once
#include <string>

class Player {
  public:
  int currency = 20;
  std::vector<Fish> fishBasket;
  std::vector<Junk> junkBasket;
  Rod currentRod;
  std::vector<Rod> ownedRods;
};