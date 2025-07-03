#pragma once
#include <functional>
#include <unordered_map>
#include "core/Player.h"

void showInfo();

void showStats(Player& p);

void showCommands(const std::unordered_map<std::string, std::function<void()>>& cmds);

void showInventory(Player& p);