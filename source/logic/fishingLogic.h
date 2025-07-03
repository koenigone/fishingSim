#pragma once
#include <string>
#include <vector>
#include "../core/Player.h"
#include "../core/Fish.h"
#include "../core/Junk.h"

void drawSea(int seaY, int seaX,
             const std::vector<std::pair<int, int>>& fishPositions,
             const std::vector<std::pair<int, int>>& junkPositions,
             int hookY, int hookX,
             int hookHeight, int hookWidth);

void seedRandom();

std::string randomName(const std::vector<std::string>& names);

int randomFishSize();

int randomJunkSize();

int calculateFishValue(int size);

int calculateJunkValue(int size);

void catchFish(Player& player);