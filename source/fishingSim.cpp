#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

// .h files
#include "core/Fish.h"
#include "core/Junk.h"
#include "core/Rod.h"
#include "core/Player.h"
#include "logic/fishingLogic.h"
#include "logic/shopLogic.h"
#include "logic/showLogic.h"

std::map<std::string, int> loadConfig(const std::string& filename) {
  std::map<std::string, int> config;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string key;
    if (std::getline(iss, key, '=')) {
      std::string valueStr;
      if (std::getline(iss, valueStr)) {
        int value = std::stoi(valueStr);
        config[key] = value;
      }
    }
  }

  return config;
}

int main() {
  seedRandom(); // random number generator
  Player player;

  std::map<std::string, int> config = loadConfig("settings.ini");

  player.currency = config["currency"];
  player.currentRod.height = config["rod_height"];
  player.currentRod.width = config["rod_width"];
  player.currentRod.size = player.currentRod.height * player.currentRod.width;

  std::vector<Rod*> rods;
  // Common
  rods.push_back(new Rod("Rod of Emberwake", "Common", 5, 5, 500));
  rods.push_back(new Rod("Rod of Verdant Bloom", "Common", 6, 6, 650));
  rods.push_back(new Rod("Rod of Silent Tempests", "Common", 7, 6, 1000));
  rods.push_back(new Rod("Rod of Whispering Stones", "Common", 7, 7, 1200));

  // Rare
  rods.push_back(new Rod("Rod of the Drowned Spire", "Rare", 8, 9, 1600));
  rods.push_back(new Rod("Rod of the Tidesong", "Rare", 9, 9, 1900));
  rods.push_back(new Rod("Rod of Eternal Dusk", "Rare", 10, 10, 2200));

  // Ultra Rare
  rods.push_back(new Rod("Rod of the Forgotten Depths", "Ultra Rare", 12, 12, 2500));
  rods.push_back(new Rod("Rod of the Moonlit Hollow", "Ultra Rare", 15, 15, 3000));
  
  // Legendary
  rods.push_back(new Rod("Rod of Twilight's Reach", "Legendary", 25, 55, 9200));
  rods.push_back(new Rod("Rod of Shattered Skies", "Legendary", 30, 50, 10000));

  std::unordered_map<std::string, std::function<void()>> commands;
  bool startGame = true;

  while (startGame) {
    std::string command;
    std::cout << "\nenter your command: ";
    std::getline(std::cin, command); // read user's full line

    commands["fish"] = [&]() { // captures everything by reference, can read/write external variables
      catchFish(player);
    };

    commands["stats"] = [&]() {
      showStats(player);
    };

    commands["basket fish"] = [&]() {
      showFishBasket(player);
    };

    commands["basket junk"] = [&]() {
      showJunkBasket(player);
    };

    commands["buy rod"] = [&]() {
      rodShop(player, rods);
    };

    commands["inventory"] = [&]() {
      showInventory(player);
    };

    commands["sell fish"] = [&]() {
      sellAllFish(player);
    };

    commands["sell junk"] = [&]() {
      sellAllJunk(player);
    };

    commands["info"] = [&]() {
      showInfo();
    };

    commands["end"] = [&]() {
      startGame = false;
    };

    commands["commands"] = [&]() {
      showCommands(commands);
    };

    if (commands.find(command) != commands.end()) {
      commands[command]();
    } else {
      std::cout << "Invlid command! type 'commands' to see a list of available commands";
    }
  }
}