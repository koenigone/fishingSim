#pragma once
#include <vector>
#include "core/Player.h"
#include "core/Rod.h"

void showFishBasket(Player& p);

void showJunkBasket(Player& p);

void sellAllFish(Player& p);

void sellAllJunk(Player& p);

void rodShop(Player& player, std::vector<Rod*> rods);