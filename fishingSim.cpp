#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iomanip>
#include <limits>

class Fish {
  public:
  std::string name;
  int size;
  int value;

  Fish() : name(""), size(0), value(0) {}
  Fish(std::string fName, int fSize, int fValue) {
    name = fName;
    size = fSize;
    value = fValue;
  }
};

class Junk {
  public:
  std::string name;
  int size;
  int value;

  Junk() : name(""), size(0), value(0) {}
  Junk(std::string jName, int jSize, int jValue) {
    name = jName;
    size = jSize;
    value = jValue;
  }
};

class Rod {
  public:
  std::string name;
  std::string rarity;
  int height;
  int width;
  int size;
  int price = 0;

  Rod() : name("Wooden Rod"), rarity("Common"), height(2), width(2), price(0) {
    size = height * width;
  }
  Rod(std::string rdName, std::string rdRarity, int rdHeight, int rdWidth, int rdPrice)
    : name(rdName), rarity(rdRarity), height(rdHeight), width(rdWidth), price(rdPrice) {
    size = height * width;
  }
};

class Player {
  public:
  int currency = 1000000;
  std::vector<Fish> fishBasket;
  std::vector<Junk> junkBasket;
  Rod currentRod;
  std::vector<Rod> ownedRods;
};

void drawSea(int seaY, int seaX, int fishY, int fishX, int junkY, int junkX, int hookY, int hookX, int hookHeight, int hookWidth) {
  for (int y = 0; y < seaY; y++) {
    for (int x = 0; x < seaX; x++) {
      if (y == fishY && x == fishX) {
        std::cout << "F"; // fish
      } else if (y == junkY && x == junkX) {
        std::cout << "J"; // junk
      } else if (y >= hookY && y < hookY + hookHeight &&
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
  seedRandom();
  int random = rand() % (300 - 3 + 1) + 3;
  return random;
};

int randomJunkSize() { // generate random size
  seedRandom();
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

void catchFish(Player& player, Fish& fish, Junk& junk) {
  seedRandom();
  int seaY = 30;
  int seaX = 90;

  int rodHeight = player.currentRod.height;
  int rodWidth = player.currentRod.width;
  int fishY = rand() % seaY;
  int fishX = rand() % seaX;
  int junkY = rand() % seaY;
  int junkX = rand() % seaX;
  int hookY = rand() % (seaY - rodHeight + 1);
  int hookX = rand() % (seaX - rodWidth + 1);

  std::cout << "Your hook landed from (" << hookX << ", " << hookY << ") to ("
            << (hookX + rodWidth - 1) << ", " << (hookY + rodHeight - 1) << ")!\n";

  drawSea(seaY, seaX, fishY, fishX, junkY, junkX, hookY, hookX, rodHeight, rodWidth);

  bool caughtFish = false;
  bool caughtJunk = false;

  if (fishX >= hookX && fishX < hookX + rodWidth &&
    fishY >= hookY && fishY < hookY + rodHeight) {
    player.fishBasket.push_back(fish); // add fish to basket
    caughtFish = true;
  } 

  if (junkX >= hookX && junkX < hookX + rodWidth &&
      junkY >= hookY && junkY < hookY + rodHeight) {
    player.junkBasket.push_back(junk);
    caughtJunk = true;
  }
  
  if (caughtFish) {
    std::cout << "Fish caught" << "\n";
    std::cout << fish.name << " size: " << fish.size << " value: " << fish.value << "\n";
  }

  if (caughtJunk) {
    std::cout << "Junk caught" << "\n";
    std::cout << junk.name << " size: " << junk.size << " value: " << junk.value << "\n";
  }

  if (!caughtFish && !caughtJunk) {
    std::cout << "Nothing was caught...\n";
  }
}

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

void showStats(Player& p) {
  int currency = p.currency;
  std::string rodName = p.currentRod.name;
  int rodSize = p.currentRod.size;
  std::string rarity = p.currentRod.rarity;

  std::cout << "Currency: " << currency << "\n";
  std::cout << "Equipped Rod: " << rodName << " Size: " << rodSize << " Rarity: " << rarity;
}

// show a list of available commands
void showCommands(const std::unordered_map<std::string, std::function<void()>>& cmds) {
  std::cout << "Available commands: \n";
  for (const auto& [cm, _] : cmds) {
    std::cout << "- " << cm << "\n";
  }
}

int main() {
  Player player;

  std::vector<Rod*> rods;
  // Common
  rods.push_back(new Rod("Rod of Emberwake", "Common", 3, 3, 500));
  rods.push_back(new Rod("Rod of Verdant Bloom", "Common", 4, 3, 650));
  rods.push_back(new Rod("Rod of Silent Tempests", "Common", 4, 4, 1000));
  rods.push_back(new Rod("Rod of Whispering Stones", "Common", 4, 4, 1000));

  // Rare
  rods.push_back(new Rod("Rod of the Drowned Spire", "Rare", 15, 4, 1000));
  rods.push_back(new Rod("Rod of the Tidesong", "Rare", 3, 2, 200));
  rods.push_back(new Rod("Rod of Eternal Dusk", "Rare" ,5, 4, 1000));

  // Ultra Rare
  rods.push_back(new Rod("Rod of the Forgotten Depths", "Ultra Rare", 20, 30, 2500));
  rods.push_back(new Rod("Rod of the Moonlit Hollow", "Ultra Rare", 20, 30, 1000));
  
  // Legendary
  rods.push_back(new Rod("Rod of Shattered Skies", "Legendary", 28, 50, 1000));
  rods.push_back(new Rod("Rod of Twilight's Reach", "Legendary", 25, 54, 9200));

  std::unordered_map<std::string, std::function<void()>> commands;
  bool startGame = true;

  while (startGame) {
    // generate fish stats
    std::string fishName = randomName(fishNames);
    int fishSize = randomFishSize();
    int fishValue = calculateFishValue(fishSize);
    Fish fish(fishName, fishSize, fishValue); // fish object

    // generate junk stats
    std::string junkName = randomName(junkNames);
    int junkSize = randomJunkSize();
    int junkValue = calculateJunkValue(junkSize);
    Junk junk(junkName, junkSize, junkValue); // fish object

    std::string command;
    std::cout << "\nenter your command: ";
    std::getline(std::cin, command); // read user's full line

    commands["fish"] = [&]() { // captures everything by reference, can read/write external variables
      catchFish(player, fish, junk);
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