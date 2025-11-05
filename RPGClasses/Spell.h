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
    Utility,
    Support
};

struct Spell {
    std::string name;
    std::string description;
    SpellType type;
};

const std::vector<Spell> spells = {
    // Offensive Spells
    {"Sharp Focus", "Channelling your inner focus, your next attack becomes empowered, dealing an extra 15% damage to your opponent.", Offense},
    {"Blazen Cross", "Your true soul emerges, letting loose and damaging everyone on the battlefield for a fixed 10HP, ticking across 3 rounds.", Offense},
    {"Chancy's Blade", "Summoning the pixie lord Chancy, your next attack has a 50% chance to deal double damage.", Offense},

    // Defensive Spells
    {"Demacian Pride", "You resolve your iron will. Gain 10% Defense and 25HP for one round.", Defense},
    {"Freljord's Blessing", "Call upon the ice witch, gaining 30% bonus defense but losing 10% damage next turn.", Defense},
    {"Piltover Barrier", "Deploy a hextech barrier that nullifies the next spell effect cast upon you.", Defense},

    // Debuff Spells
    {"Singed's Works", "Stolen from a Zaun lab, you splash your enemy with a weakening liquid, making your enemy deal 20% less damage for the next 2 turns.", Debuff},
    {"Silence of the Isles", "Call upon the mists, preventing your opponent from healing or dodging for one round.", Debuff},
    {"Crowley's Torment", "Enter deep within your mind and cast out hellfire made of pure hatred. Make your opponent cower in fear and deal half damage for the next turn.", Debuff},

    // Utility Spells
    {"Hextech Rewind", "Twist time, immediately taking another action after this one.", Utility},
    {"Lillia's Dream", "Cast a dream unto your enemy, giving them a well rested night, but forcing them to skip their next turn.", Utility},
    {"Living Shadow", "Conjure a shadow. The opponent has a 50% chance to strike this shadow instead of you, reflecting 25% of their damage back at them.", Utility},

    // Support Spells
    {"Bloom of Life", "Summon an enchanted flower that restores 10HP every turn for 2 turns.", Support},
    {"Runic Harmony", "Balance your energies. Gain 10% defense if your HP is higher than the enemy’s, or 10% damage if it’s lower.", Support},
    {"Axiom Arcana", "Summon the arcane. Steal 10% of your opponents stats for the rest of the fight. After this, you cannot cast any more spells.", Support}
};

void applySpellToCurrCast(const Spell& spellToApply, const Player& pObject);

#endif //RPGPROJECT_SPELL_H