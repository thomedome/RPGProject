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

enum class TargetType {
    Self,
    Enemy,
    Both
};

enum class ModifyType {
    Heal,
    Damage
};

struct Spell {
    std::string name;
    std::string description;
    SpellType type;
    TargetType target;
    ModifyType modType; // Heal or Damage
    int remainingRounds;
    std::unordered_map<std::string, int> spellModifiers; // Iterate and affect
};

extern std::vector<Spell> allSpells;

void applySpellToCurrCast(const Spell& spellToApply, const Player& pObject); // Add spells to pObject.currCasts vector.
void spellChecks(const Player& pObject, const Enemy& eObject); // Do all spell checks in this function - use spell lambdas, and iterate through after each round.
Spell getSpellByName(const std::string& name, std::vector<Spell>& spellList);

#endif //RPGPROJECT_SPELL_H