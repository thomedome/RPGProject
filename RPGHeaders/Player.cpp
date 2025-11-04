//
// Created by win11 on 31/10/2025.
//

#include "RPGUtilities.h"
#include "common.h"
#include "Player.h"

#include <filesystem>

#include "Item.h"
#include "Enemy.h"

void Player::dealDamage(const Enemy& eObject) const {
    int damageIncArmor = calculateDamageIncArmor(abilityPower, eObject.defense); // Calculate Attack + Armor

    if (lifesteal > 0) {
        const int lifestealAmount {static_cast<int>(std::ceil(damageIncArmor * (lifesteal * 0.01)))}; // Force from float to int
        currentHP += lifestealAmount;
        std::cout << "You regained " <<  lifestealAmount << "HP from your lifesteal!" << std::endl;
    }

    std::cout << "You dealt " << damageIncArmor << " damage to " << eObject.name << '!' << '\n';
    eObject.takeDamage(damageIncArmor);
}

void Player::attack(const Enemy &eObject) const {\
    std::cout << "You choose to attack." << '\n';

    if (searchVector(eObject.flags, std::string{"Dodging"})) {
        // Search the enemy flags vector for dodging
        eObject.flags.erase(std::remove(eObject.flags.begin(), eObject.flags.end(), "Dodging"), eObject.flags.end());

        // Remove all "Dodging" flags - may be multiple in case of whoopsies duplicates.
        const int random = Random::Int(1, 100);
        if (random <= 35) {
            std::cout << eObject.name << " dodged your attack!" << '\n';
            return;
        }
        std::cout << eObject.name << " tried to dodge but failed." << '\n';
        dealDamage(eObject);

        return;
    }

    dealDamage(eObject);
}

void Player::displayStats() const {
    std::cout << "<-- " << name << "'s stats --> " << "\n";
    std::cout << "HP: " << currentHP << "/" << maxHP << '\n';
    std::cout << "Ability Power: " << abilityPower << '\n';
    std::cout << "Defense: " << defense << '\n';
    std::cout << "Lifesteal: " << lifesteal << '\n';
    std::cout << "Level: " << level << '\n';
    std::cout << "XP: " << xp << '/' << xpReq << '\n';
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "Inventory: " << '\n';
    for (int i {0}; i < playerInventory.size(); i++) {
        std::cout << "- " << playerInventory[i].name << '\n';
    }
    sleep(3);
}

void Player::takeDamage(const int damage) const {
    currentHP -= damage;
}

//heal
void Player::heal() const {
    std::cout << "You decide to heal." << '\n';
    // Create Random number for health regen - 15 LB, 45 UB - this is a % of max hp.
    int random = Random::Int(15, 45);
    int hpToAdd = ceil(currentHP * (random * 0.01));

    // Check if HP goes over - if so, change to number needed to go max hp.
    if (currentHP + hpToAdd > maxHP) {
        hpToAdd = ceil(currentHP * ((maxHP - currentHP) * 0.01));
    }

    currentHP += hpToAdd;

    std::cout << "You healed for " << hpToAdd << "% of your HP!" << '\n';
}

void Player::levelUp() const {
    const int leftOver {xp - xpReq}; // If there's any XP left over from the player levelling up
    xpReq = getXPCap(xpReq);
    level += 1;
    xp = leftOver;
    gold += (15 * level); // Scaling gold reward. 15, 30, 45, 60...
    std::cout << "You have levelled up! You are now level " << level << "! \n";
    std::cout << "You gained " << (15 * level) << "gold as a reward!" << std::endl;
}

int Player::getXPCap(const int xpReq) {
    return xpReq + 100;
}

void Player::cast() const {
    // Work on this after I've finished everything else - probably going to be complicated
}

void Player::addDodgeFlag() const {
    std::cout << name << " decided to attempt a dodge." << std::endl;
    flags.emplace_back("Dodging");
}

bool Player::attemptShopPurchase(const Item& itemPurchasing) const {
    if (gold >= itemPurchasing.price) { // Success

        gold -= itemPurchasing.price;
        playerInventory.emplace_back(itemPurchasing); // Add to Inv vector

        // Add Stats to player.
        abilityPower += itemPurchasing.damageIncrease;
        lifesteal += itemPurchasing.lifesteal;
        defense += itemPurchasing.defenseIncrease;

        if (!applyWounds) {
            if (itemPurchasing.applyWounds) {
                applyWounds = true;
            }
        }

        return true; // notify that transaction was successful
    }

    return false; // Homeboy too poor XDD
}

void Player::saveGame() const {
    std::filesystem::create_directory("gameSaves");
    const std::string fileName {"gameSaves/" + name + ".txt"};
    std::ofstream file;

    file.open(fileName); // Rewrites all data - only one save per name1

    std::cout << fileName << std::endl;

    if (!file) {
        std::cout << "Failed to open save file." << '\n';
        return;
    }

    file << name << '\n';
    file << currentHP << '\n';
    file << maxHP << '\n';
    file << abilityPower << '\n';
    file << defense << '\n';
    file << lifesteal << '\n';
    file << level << '\n';
    file << xp << '\n';
    file << xpReq << '\n';
    file << gold << '\n';

    for (size_t i = 0; i < playerInventory.size(); i++) {
        file << playerInventory[i].uID << '\n';
    }

    file << "--EOI--" << "\n\n\n";

    std::cout << "Saved game file!" << '\n';

    file.close();
}

bool Player::loadGame() {

    int pChoice {};

    std::cout << "Enter the number that your save file corresponds to:" << std::endl;

    int counter {0};
    std::unordered_map<int, std::string> savesTranslatorDB {}; // So I can get the correct save from the list

    for (const auto& entry : std::filesystem::directory_iterator("gameSaves")) { // Loop through the game saves dir
        if (entry.is_regular_file()) { // if is a normal file
            counter++; // increase counter
            std::cout << counter << ") " << entry.path().filename().string() << '\n'; // list to player
            savesTranslatorDB.insert({counter, entry.path().filename().string()}); // add to unordered map
        }
    }

    std::cin >> pChoice; // give the player choice on what save to use

    std::string fName {savesTranslatorDB.find(pChoice)->second}; // pull the name from the map
    std::ifstream file;

    std::cout << fName << '\n';

    file.open("gameSaves/" + fName);

    if (!file.is_open()) {
        std::cout << "Failed to open save file." << '\n';
        return false;
    }

    std::getline(file, name);
    file >> currentHP;
    file >> maxHP;
    file >> abilityPower;
    file >> defense;
    file >> lifesteal;
    file >> level;
    file >> xp;
    file >> xpReq;
    file >> gold;

    int a;
    while (file >> a) {
        auto it = itemDB.find(a);
        if (it != itemDB.end()) {
            playerInventory.push_back(it->second);
        }
    }

    file.close();

    std::cout << "Save loaded!" << std::endl;

    return true;
}