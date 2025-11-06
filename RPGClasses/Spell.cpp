//
// Created by 30264651 on 05/11/2025.
//

#include "Spell.h"
#include "RPGUtilities.h"
#include "Player.h"
#include "Enemy.h"

// Anytime im accessing Enemy, i need to use -> instead of . because it's a pointer. pointer stands for (piece of shit)ointer

void Spell::applySpellToCurrCast(const Spell &spellToApply, const Player &pObject) {
    pObject.activeEffects.push_back(spellToApply);
}

void Spell::spellChecks(const Player& pObject, const Enemy& eObject) {
    for (auto spell = pObject.activeEffects.begin(); spell != pObject.activeEffects.end();) {
        spell->remainingRounds--; // Remove Turn
        if (spell->remainingRounds == 0) { // If EOL of spell
            spell->remove(pObject, &eObject); // Remove the spell effects
            pObject.activeEffects.erase(spell); // Remove from activeEffects uMap
        } else {
            ++spell;
        }
    }
}

Spell* Spell::getSpellByName(const std::string& name, std::vector<Spell>& spellList) {
    auto it = std::find_if(spellList.begin(), spellList.end(),
        [&](const Spell& s) { return s.name == name; });

    if (it != spellList.end())
        return &(*it); // return pointer to spell
    else
        return nullptr; // not found
}