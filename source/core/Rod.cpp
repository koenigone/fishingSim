#include <string>
#include "Rod.h"

Rod::Rod() : name("Wooden Rod"), rarity("Common"), height(4), width(4), price(0) {
  size = height * width;
}

Rod::Rod(std::string rdName, std::string rdRarity, int rdHeight, int rdWidth, int rdPrice)
  : name(rdName), rarity(rdRarity), height(rdHeight), width(rdWidth), price(rdPrice) {
  size = height * width;
}