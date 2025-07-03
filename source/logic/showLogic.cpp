#include <iostream>
#include "showLogic.h"
#include "core/Player.h"
#include "core/Rod.h"

void showInfo() {
  std::cout << "Welcome to the Fishing Game! In this game, players can fish, sell, and buy items.\n";
  std::cout << "You start by casting your rod into the sea using the 'fish' command.\n";
  std::cout << "Whatever lands on your hook is yours! whether it's a valuable fish or just junk.\n";
  std::cout << "Sell your catches to earn money and upgrade to better rods by typing 'buy rod'.\n";
  std::cout << "Start your fishing adventure by typing 'fish' below!";
}

void showStats(Player& p) {
  int currency = p.currency;
  std::string rodName = p.currentRod.name;
  int rodSize = p.currentRod.size;
  std::string rarity = p.currentRod.rarity;
  int fishCount = p.fishBasket.size();
  int junkCount = p.junkBasket.size();

  std::cout << "Currency: " << "$" << currency << "\n";
  std::cout << "Equipped Rod: " << rodName << " Size: " << rodSize << " Rarity: " << rarity << "\n";
  std::cout << "Fish owned: " << fishCount << "\n";
  std::cout << "Junk owned: " << junkCount;
}

// show a list of available commands
void showCommands(const std::unordered_map<std::string, std::function<void()>>& cmds) {
  std::cout << "Available commands: \n";
  for (const auto& [cm, _] : cmds) {
    std::cout << "- " << cm << "\n";
  }
}

void showInventory(Player& p) {
  if (p.ownedRods.size() > 0) {
    for (Rod& rod : p.ownedRods) { // show rods in the inventory
      std::cout << rod.name << " size: " << rod.size << " rarity: " << rod.rarity << "\n";
    }

    // change currently equipped rod
    std::cout << "Select Rod:" << "\n";
    int inventoryPick;
    std::cin >> inventoryPick;
    int inventoryIndex = inventoryPick -1;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (inventoryIndex >= 0 && inventoryIndex < p.ownedRods.size()) {
      p.currentRod = p.ownedRods[inventoryIndex];
      std::cout << "You equipped: " << p.ownedRods[inventoryIndex].name;
    } else {
      std::cout << "Invalid choice!";
    }
  } else {
    std::cout << "Inventory is Empty!";
  }
}