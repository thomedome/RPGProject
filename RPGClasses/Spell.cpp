//
// Created by 30264651 on 05/11/2025.
//

#include "Spell.h"

void applySpellToCurrCast(const Spell &spellToApply, const Player &pObject) {
    pObject.playerCasts.push_back(spellToApply);
}
