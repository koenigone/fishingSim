#include <iostream>
#include "fishingLogic.h"
#include <iomanip>
#include <limits>

void drawSea(int seaY, int seaX,
             const std::vector<std::pair<int, int>>& fishPositions,
             const std::vector<std::pair<int, int>>& junkPositions,
             int hookY, int hookX,
             int hookHeight, int hookWidth) {
  for (int y = 0; y < seaY; y++) {
    for (int x = 0; x < seaX; x++) {

      bool isFish = false;
      bool isJunk = false;

      for (const auto& fish : fishPositions) {
        if (y == fish.first && x == fish.second) {
          std::cout << "F"; // fish
          isFish = true;
          break;
        }
      }

      if (isFish) continue;

      for (const auto& junk : junkPositions) {
        if (y == junk.first && x == junk.second) {
          std::cout << "J";
          isJunk = true;
          break;
        }
      }

      if (isJunk) continue;
      
      if (y >= hookY && y < hookY + hookHeight &&
                 x >= hookX && x < hookX + hookWidth) {
        std::cout << "#"; // hook
      } else {
        std::cout << "~";
      }
    }
    std::cout << "\n";
  }
}

void seedRandom() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
};

std::string randomName(const std::vector<std::string>& names) {
  int randomIndex = rand() % names.size();
  return names[randomIndex];
};

int randomFishSize() { // generate random size
  int random = rand() % (300 - 3 + 1) + 3;
  return random;
};

int randomJunkSize() { // generate random size
  int random = rand() % (150 - 3 + 1) + 3;
  return random;
};

int calculateFishValue(int size) { // decide fish price based on size
  if (size <= 30) return 12;
  if (size <= 80) return 20;
  if (size <= 120) return 28;
  if (size <= 150) return 35;
  if (size <= 200) return 46;
  if (size <= 250) return 66;
  if (size <= 299) return 78;
  return 0;
}

int calculateJunkValue(int size) { // decide fish price based on size
  if (size <= 30) return 4;
  if (size <= 80) return 8;
  if (size <= 120) return 15;
  if (size <= 150) return 26;
  return 0;
}

std::vector<std::string> fishNames = { // fish types
  "Goldfish", "Salmon", "Tuna", "Clownfish", "Cod", "Anglerfish", "Swordfish", "Shark", "Mackerel",
  "Carp", "Eel", "Catfish", "Piranha", "Trout", "Herring", "Barracuda", "Halibut", "Flounder", "Snapper",
  "Grouper", "Marlin", "Stingray", "Lionfish", "Seahorse", "Blue Tang", "Anchovy", "Sardine", "Dory",
};

std::vector<std::string> junkNames = { // junk items
  "Rusty Anchor", "Broken Compass", "Seaweed-Clogged Boot", "Barnacle-Crusted Can", "Tattered Fishing Net",
  "Waterlogged Treasure Map", "Soggy Pirate Hat", "Broken Spyglass", "Driftwood with Nails",
  "Mysterious Glass Bottle", "Old Ship Wheel Fragment", "Dented Oil Drum", "Salt-Corroded Pocket Watch",
};

void catchFish(Player& player) {
  int seaY = 30;
  int seaX = 90;
  int spawnRandomFishes = (rand() % 4) + 1;
  int spawnRandomJunk = (rand() % 15) + 1;

  std::vector<std::pair<int, int>> fishPositions;
  std::vector<std::pair<int, int>> junkPositions;
  std::vector<Fish> generatedFishes;
  std::vector<Junk> generatedJunk;
  std::vector<Fish> caughtFish;
  std::vector<Junk> caughtJunk;

  int rodHeight = player.currentRod.height;
  int rodWidth = player.currentRod.width;
  int hookY = rand() % (seaY - rodHeight + 1);
  int hookX = rand() % (seaX - rodWidth + 1);

  for (int f = 0; f < spawnRandomFishes; f++) {
    // generate fish stats
    std::string fishName = randomName(fishNames);
    int fishSize = randomFishSize();
    int fishValue = calculateFishValue(fishSize);
    Fish fish(fishName, fishSize, fishValue); // fish object

    int fishY = rand() % seaY;
    int fishX = rand() % seaX;
      
    fishPositions.emplace_back(fishY, fishX);
    generatedFishes.push_back(fish);
  }

  for (int j = 0; j < spawnRandomJunk; j++) {
    // generate junk stats
    std::string junkName = randomName(junkNames);
    int junkSize = randomJunkSize();
    int junkValue = calculateJunkValue(junkSize);
    Junk junk(junkName, junkSize, junkValue); // junk object

    int junkY = rand() % seaY;
    int junkX = rand() % seaX;
    junkPositions.emplace_back(junkY, junkX);
    generatedJunk.push_back(junk);
  }

  std::cout << "Your hook landed from (" << hookX << ", " << hookY << ") to ("
            << (hookX + rodWidth - 1) << ", " << (hookY + rodHeight - 1) << ")!\n";

  drawSea(seaY, seaX, fishPositions, junkPositions, hookY, hookX, rodHeight, rodWidth);

  bool isCaughtFish = false;
  bool isCaughtJunk = false;

  for (int f = 0; f < fishPositions.size(); ++f) {
    int fishY = fishPositions[f].first;
    int fishX = fishPositions[f].second;

    if (fishX >= hookX && fishX < hookX + rodWidth &&
      fishY >= hookY && fishY < hookY + rodHeight) {
      player.fishBasket.push_back(generatedFishes[f]); // only add caught fish
      caughtFish.push_back(generatedFishes[f]);
      isCaughtFish = true;
    }
  }

  if (isCaughtFish) { // display resault
    std::cout << "\nFish caught:" << "\n";
    for (const Fish fish : caughtFish) {
      std::cout << fish.name 
                << " size: " << fish.size 
                << " value: " << "$" <<fish.value <<"\n";
    }
  }

  for (int j = 0; j < junkPositions.size(); j++) {
    int junkY = junkPositions[j].first;
    int junkX = junkPositions[j].second;

    if (junkX >= hookX && junkX < hookX + rodWidth &&
      junkY >= hookY && junkY < hookY + rodHeight) {
      player.junkBasket.push_back(generatedJunk[j]);
      caughtJunk.push_back(generatedJunk[j]);
      isCaughtJunk = true;
    }
  }

  if (isCaughtJunk) { // display resault
    std::cout << "\nJunk caught:" << "\n";
    for (const Junk junk : caughtJunk) {
      std::cout << junk.name 
                << " size: " << junk.size 
                << " value: " << "$" << junk.value << "\n";
    }      
  }

  if (!isCaughtFish && !isCaughtJunk) {
    std::cout << "Nothing was caught...\n";
  }
}