//
// Created by 30264651 on 05/11/2025.
//

#ifndef RPGPROJECT_SPELL_H
#define RPGPROJECT_SPELL_H
#include <string>
#include "Player.h"

enum SpellType { // type
    Offense,
    Defense,
    Debuff,
    Utility
};

struct Spell {
    std::string name;
    std::string description;
    SpellType type;
};

void applySpellToCurrCast(const Spell& spellToApply, const Player& pObject);

#endif //RPGPROJECT_SPELL_H