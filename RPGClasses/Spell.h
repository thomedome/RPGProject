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
    Debuff
};

struct Spell {
    std::string name;
    std::string description;
    SpellType type;
    void CastSpell(Player& pObject, const Spell& spell);
};

extern std::unordered_map<int, Spell> allSpells;
bool cleanseSpells(Player& pObject);

#endif //RPGPROJECT_SPELL_H