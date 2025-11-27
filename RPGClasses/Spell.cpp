//
// Created by 30264651 on 05/11/2025.
//

#include "Spell.h"
#include "RPGUtilities.h"
#include "Player.h"
#include "Enemy.h"

// May have overestimated what I can do... time for simple spells :')


/* Unused Spells

   {
        "Blazen Cross",
        "Your true soul emerges, letting loose and damaging everyone on the battlefield for a fixed 10HP, ticking across 3 rounds.",
        Offense,
    },
    {
        "Chancy's Blade",
        "Summoning the pixie lord Chancy, your next attack has a 50% chance to deal double damage.",
        Offense,
    },

    {
        "Freljord's Blessing", "Call upon the ice witch, gaining 30% bonus defense but losing 10% damage next turn.",
        Defense
    },
    {
        "Piltover Barrier",
        "Deploy a hextech barrier that nullifies the next spell effect cast upon you.",
        Defense
    },

    {
        "Singed's Works",
        "Stolen from a Zaun lab, you splash your enemy with a weakening liquid, making your enemy deal 20% less damage for the next 2 turns.",
        Debuff
    },

    {
        "Crowley's Torment",
        "Enter deep within your mind and cast out hellfire made of pure hatred. Make your opponent cower in fear and deal half damage for the next turn.",
        Debuff, 1
    },

    ####Utility Spells####

    {"Hextech Rewind",
    "Twist time, immediately taking another action after this one.",
    Utility
    },

    {
        "Lillia's Dream",
        "Cast a dream unto your enemy, giving them a well rested night, but forcing them to skip their next turn.",
        Utility
    },
    {
        "Living Shadow",
        "Conjure a shadow that dissipates after one round. The opponent has a 50% chance to strike this shadow instead of you, reflecting 25% of their damage back at them.",
        Utility
    },

    // Support Spells
    {
    "Bloom of Life",
    "Summon an enchanted flower that restores 10HP every turn for 2 turns.",
    Support
    },

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


 */

std::unordered_map<int, Spell> allSpells = {
    // Offensive Spells
    {1,
        {
            "Sharp Focus",
            "Channelling your inner focus, your next attack becomes empowered, dealing an extra 15% damage to your opponent.",
            Offense,
        }
    },

    // Defensive Spells
    {2,
        {
        "Demacian Pride",
        "You resolve your iron will. Gain 10% Defense for one round and heal 25HP.",
        Defense
    }},

    // Debuff Spells

    {3,
        {
        "Silence of the Isles", "Call upon the mists, silencing your opponent and skipping their turn.",
        Debuff
        }
    }

};

void Spell::CastSpell(Player &pObject, const Spell &spell) {
    pObject.activeEffects.push_back(spell.name); // Add to current spell effects - undo after every round
    if (spell.name == "Sharp Focus") {
        pObject.abilityPower = ceil(pObject.abilityPower * 1.15);
    } else if (spell.name == "Demacian Pride") {
        pObject.defense = ceil(pObject.defense * 1.1);
        pObject.currentHP += 25; // Keep HP
    } else if (spell.name == "Silence of the Isles") {
        pObject.currOpponent.flags.emplace_back("Silenced");
    }
}
