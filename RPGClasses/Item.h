//
// Created by win11 on 31/10/2025.
//

#ifndef RPGPROJECT_ITEM_H
#define RPGPROJECT_ITEM_H

#include <unordered_map>
#include "common.h"

struct Item {
    std::string name;
    int price;
    int damageIncrease; // Flat
    int lifesteal; // %
    int defenseIncrease;
    bool applyWounds;
    std::string description;
    int uID;
};

const std::vector<Item> shopItems{
    {
        "Spear of Shojin", 250, 15, 0, 0, false,
        "A mystical spear from the Shojin Monastery in Ionia. Grants +15 Damage.", 1
    },
    {
        "Bloodluster", 350, 20, 10, 0, false,
        "The weapon used to bring down the Hand of Noxus. Grants +20 Damage and 10% Lifesteal.", 2
    },
    {
        "Kraken Slayer", 500, 35, 15, 0, false,
        "A great harpoon, imbued with magic by the mages of Shurima. Grants +35 Damage and 15% Lifesteal.", 3
    },
    {
        "Thornmail", 650, 0, 0, 25, true,
        "Armor taken from the Kame Clan. Gives 25 Defense and reduces enemy healing by 25% (Grievous Wounds.)", 4
    }
};

const std::unordered_map<int, Item> itemDB{
    // uID, Item
    {
        1, {
            "Spear of Shojin", 250, 15, 0, 0, false,
            "A mystical spear from the Shojin Monastery in Ionia. Grants +15 Damage.", 1
        }
    },
    {
        2, {
            "Bloodluster", 350, 20, 10, 0, false,
            "The weapon used to bring down the Hand of Noxus. Grants +20 Damage and 10% Lifesteal.", 2
        }
    },
    {
        3, {
            "Kraken Slayer", 500, 35, 15, 0, false,
            "A great harpoon, imbued with magic by the mages of Shurima. Grants +35 Damage and 15% Lifesteal.", 3
        }
    },
    {
        4, {
            "Thornmail", 650, 0, 0, 25, true,
            "Armor taken from the Kame Clan. Gives 25 Defense and reduces enemy healing by 25% (Grievous Wounds.)", 4
        }
    }
};

#endif //RPGPROJECT_ITEM_H
