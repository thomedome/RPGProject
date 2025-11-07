//
// Created by 30264651 on 05/11/2025.
//

#ifndef RPGPROJECT_SPELL_H
#define RPGPROJECT_SPELL_H
#pragma once

#include <functional>
#include <string>
#include "RPGUtilities.h"

class Player;
class Enemy;

enum SpellType { // Spell types
    Offense,
    Defense,
    Debuff,
    Utility,
    Support
};

struct Spell {
    std::string name;
    std::string description;
    SpellType type;
    // Spell Effect Controls
    int remainingRounds;
    std::function<void(Player&, Enemy*)> apply;
    std::function<void(Player&, Enemy*)> remove;

    void applySpellToCurrCast(const Spell &spellToApply, const Player &pObject);

    void spellChecks(Player &pObject, Enemy &eObject);

    Spell *getSpellByName(const std::string &name, std::vector<Spell> &spellList);
};

extern std::vector<Spell> allSpells;

// [](const Player& pObject){};

void applySpellToCurrCast(const Spell& spellToApply, const Player& pObject); // Add spells to pObject.currCasts vector.
void spellChecks(const Player& pObject, const Enemy& eObject); // Do all spell checks in this function - use spell lambdas, and iterate through after each round.
Spell* getSpellByName(const std::string& name, std::vector<Spell>& spellList);

#endif //RPGPROJECT_SPELL_H