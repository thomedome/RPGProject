//
// Created by win11 on 31/10/2025.
//

#ifndef RPGPROJECT_PLAYER_H
#define RPGPROJECT_PLAYER_H

#include "Item.h"
#include "Enemy.h"
#include <fstream>
#include <string>

#include "Spell.h"

// test
class Player {
public:
    std::string name;
    mutable int maxHP = 100;
    mutable int currentHP = 100;
    mutable int defense = 15;
    mutable int abilityPower = 10;
    mutable int level = 1;
    mutable int xp = 0;
    mutable int xpReq = 280;
    mutable int gold = 0;
    mutable int lifesteal = 0;
    mutable bool applyWounds {false};
    mutable std::vector<Item> playerInventory{};
    mutable std::vector< Spell> activeEffects; // player spells
    mutable std::vector<std::string> flags{}; // Dodging flag
    mutable std::vector<std::string> dynamicVariables{};

    void attack(const Enemy &eObject) const;

    void displayStats() const;

    void takeDamage(int damage) const;

    void heal() const;

    void cast(const Player &pObject, const Enemy *eObject) const;

    void levelUp() const;

    static int getXPCap(int xpReq);

    void addDodgeFlag() const;

    bool attemptShopPurchase(const Item& itemPurchasing) const;

    void dealDamage(const Enemy& eObject) const;

    void saveGame() const;

    bool loadGame();

    // Casting - WIP

};

#endif //RPGPROJECT_PLAYER_H