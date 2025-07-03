#pragma once
#include <string>

class Rod {
  public:
  std::string name;
  std::string rarity;
  int height;
  int width;
  int size;
  int price = 0;

  Rod();
  Rod(std::string rdName, std::string rdRarity, int rdHeight, int rdWidth, int rdPrice);
};