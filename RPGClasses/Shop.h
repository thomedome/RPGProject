//
// Created by win11 on 01/11/2025.
//

#ifndef RPGPROJECT_SHOP_H
#define RPGPROJECT_SHOP_H

#include "Item.h"
#include "Player.h"

class Shop {

public:
    void openShop(const Player& player) const;
    void listItems() const;
    void openItem(const Item& selectedItem) const;
    void decideToPurchase(std::string yesNo, const Player& player, const Item& selectedItem) const;
};


#endif //RPGPROJECT_SHOP_H