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

void Spell::spellChecks(Player &pObject, Enemy &eObject) {
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

Spell* Spell::getSpellByName(const std::string& iname, std::vector<Spell>& spellList) {
    auto it = std::find_if(spellList.begin(), spellList.end(),
        [&](const Spell& s) { return s.name == iname; });

    if (it != spellList.end())
        return &(*it); // return pointer to spell
    else
        return nullptr; // not found
}

std::vector<Spell> allSpells = {
    // Offensive Spells
    {
        "Sharp Focus",
        "Channelling your inner focus, your next attack becomes empowered, dealing an extra 15% damage to your opponent.",
        Offense,
        1,
        [](Player &pObject, Enemy *eObject) {
            std::cout << "Test";
            pObject.abilityPower = static_cast<int>(pObject.abilityPower * 1.15);
        },
        [](Player &pObject, Enemy *eObject) {
            pObject.abilityPower = static_cast<int>(pObject.abilityPower / 1.15);
        }
    },
    {
        "Blazen Cross",
        "Your true soul emerges, letting loose and damaging everyone on the battlefield for a fixed 10HP, ticking across 3 rounds.",
        Offense,
        3,
        [](Player &pObject, Enemy *eObject) {
            pObject.currentHP -= 10;
            eObject->currentHP -= 10;
        },
        [](Player &pObject, Enemy *eObject) {
        } // Empty as I don't need to revert anything
    },
    {
        "Chancy's Blade", "Summoning the pixie lord Chancy, your next attack has a 50% chance to deal double damage.",
        Offense,
        1,
        [](Player &pObject, Enemy *eObject) {
            if (Random::Int(1, 100) >= 50) {
                pObject.abilityPower = static_cast<int>(pObject.abilityPower * 1.5);
                pObject.dynamicVariables.emplace_back("ChancyEmpowered");
            }
        },
        [](Player &pObject, Enemy *eObject) {
            if (searchVector(pObject.dynamicVariables, "ChancyEmpowered")) {
                pObject.abilityPower = static_cast<int>(pObject.abilityPower / 1.5);
                std::erase(pObject.dynamicVariables, "ChancyEmpowered");
            }
        }
    },

    // Defensive Spells
    {"Demacian Pride", "You resolve your iron will. Gain 10% Defense and 25HP for one round.", Defense, 1},
    {
        "Freljord's Blessing", "Call upon the ice witch, gaining 30% bonus defense but losing 10% damage next turn.",
        Defense, 1
    },
    {"Piltover Barrier", "Deploy a hextech barrier that nullifies the next spell effect cast upon you.", Defense, 1},

    // Debuff Spells
    {
        "Singed's Works",
        "Stolen from a Zaun lab, you splash your enemy with a weakening liquid, making your enemy deal 20% less damage for the next 2 turns.",
        Debuff, 2
    },
    {
        "Silence of the Isles", "Call upon the mists, preventing your opponent from healing or dodging for one round.",
        Debuff, 1
    },
    {
        "Crowley's Torment",
        "Enter deep within your mind and cast out hellfire made of pure hatred. Make your opponent cower in fear and deal half damage for the next turn.",
        Debuff, 1
    },

    // Utility Spells
    {"Hextech Rewind", "Twist time, immediately taking another action after this one.", Utility, 1},
    {
        "Lillia's Dream",
        "Cast a dream unto your enemy, giving them a well rested night, but forcing them to skip their next turn.",
        Utility, 1
    },
    {
        "Living Shadow",
        "Conjure a shadow that dissipates after one round. The opponent has a 50% chance to strike this shadow instead of you, reflecting 25% of their damage back at them.",
        Utility, 1
    },

    // Support Spells
    {"Bloom of Life", "Summon an enchanted flower that restores 10HP every turn for 2 turns.", Support, 2},
    {
        "Runic Harmony",
        "Balance your energies. Gain 10% defense if your HP is higher than the enemy’s, or 10% damage if it’s lower.",
        Support, 1
    },
    {
        "Axiom Arcana",
        "Summon the arcane. Steal 10% of your opponents stats for the rest of the fight. After this, you cannot cast any more spells.",
        Support, 1
    }
};