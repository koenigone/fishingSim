#include <iostream>
#include "shopLogic.h"
#include "core/Fish.h"
#include "core/Junk.h"

void showFishBasket(Player& p) { // show current fish basket
  if (p.fishBasket.size() > 0) {
    for (Fish& fish : p.fishBasket) {
      std::cout << "Name: " << fish.name
                << " Size: " << fish.size
                << " Value: " << fish.value << "\n";
    }
  } else {
    std::cout << "Your fish basket is empty!";
  }
}

void showJunkBasket(Player& p) { // show current junk basket
  if (p.junkBasket.size() > 0) {
    for (Junk& junk : p.junkBasket) {
      std::cout << "Name: " << junk.name
                << " Size: " << junk.size
                << " Value: " << junk.value << "\n";
    }
  } else {
    std::cout << "Your junk basket is empty!";
  }
}

void sellAllFish(Player& p) { // sell FISH
  if (p.fishBasket.size() > 0) {
    int totalEarned = 0;
    
    for (const Fish& fish : p.fishBasket) {
      totalEarned += fish.value;
    }
    
    p.currency += totalEarned;
    p.fishBasket.clear();
    
    std::cout << "You sold all your fish for: " << totalEarned << " currency!\n";
    std::cout << "Your new balance: " << p.currency << " currency.\n";
  } else {
    std::cout << "Your fish basket is empty!\n";
  }
}

void sellAllJunk(Player& p) { // sell JUNK
  if (p.junkBasket.size() > 0) {
    int totalEarned = 0;
    
    for (const Junk& junk : p.junkBasket) {
      totalEarned += junk.value;
    }
    
    p.currency += totalEarned;
    p.junkBasket.clear();
    
    std::cout << "You sold all your junk for: " << totalEarned << " currency!\n";
    std::cout << "Your new balance: " << p.currency << " currency.\n";
  } else {
    std::cout << "Your junk basket is empty!\n";
  }
}

void rodShop(Player& player, std::vector<Rod*> rods) {
  std::cout << "Available Rods:" << "\n";

  int rodIndex = 1;
  for (Rod* rod : rods) {
    std::cout << rodIndex++ << "-" << rod->name << " size: " << rod->size << " price: " << rod->price << "$" << "\n";
  }

  int rodChoice;
  std::cin >> rodChoice;
  int choiceIndex = rodChoice -1; // fix the index
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the extra space added '\n'

  if (choiceIndex >= 0 && choiceIndex < rods.size()) {
    std::cout << "You chose: " << rods[choiceIndex]->name << "\n";
    if (player.currency >= rods[choiceIndex]->price) {
      std::cout << "Rod purchased '" << rods[choiceIndex]->name << "' successfully!";
      player.currency -= rods[choiceIndex]->price; // cut rod's price from currency
      player.currentRod = *rods[choiceIndex];      // equipd newly purchased rod
      player.ownedRods.push_back(*rods[choiceIndex]);
    } else {
      std::cout << "Not enough currency!";
    }

  } else {
    std::cout << "Invalid choice!";
  }
}