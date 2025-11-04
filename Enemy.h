//
// Created by win11 on 31/10/2025.
//

#ifndef RPGPROJECT_ENEMY_H
#define RPGPROJECT_ENEMY_H

#pragma once
#include "common.h"

class Player;

enum enemyBehaviourState {
    Aggressive, // Attack
    Defensive, // Heal / Dodge - 75 / 25 chance
    Dodging, // Guaranteed Dodge
    Random // Random Chance for everything, just for less readability. 33% Chance
};

enum enemyDifficulty {
    // Used for reward calculation in combination with levels.
    Easy,
    Medium,
    Hard,
    Extreme
};

class Enemy {
public:
    std::string name;
    mutable int maxHP{};
    mutable int currentHP{};
    mutable int defense{};
    mutable int abilityPower{};
    mutable int level{};
    mutable enemyDifficulty difficulty{};
    mutable enemyBehaviourState state{Random};
    mutable std::vector<std::string> flags{}; // Dodging flags

    void attack(const Player &pObject) const; // Declare now - change later so I can reference the player object

    void defensiveTurn() const;

    void heal() const;

    void addDodgeFlag() const;

    void takeTurn(const Player &pObject) const;

    void takeDamage(int damage) const;

    void displayStats() const;

};

// Vector for random enemy names
inline std::vector<std::string> enemyNames{"Goblin", "Golem", "Vex", "Pillager", "Ruination Wraith", "Yordle", "Fiend"};

#endif //RPGPROJECT_ENEMY_H