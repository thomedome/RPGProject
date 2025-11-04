//
// Created by win11 on 01/11/2025.
//

#include "Shop.h"
#include "Player.h"

void Shop::openShop(const Player& player) const {
    std::cout << "<-- Welcome to the Wandering Boutique! -->" << '\n';
    sleep(2);
    std::cout << "You have " << player.gold << " Gold." << '\n';
    sleep(2);
    std::cout << "1) View Items" << '\n' << "2) Leave Shop";
}


void Shop::listItems() const {
    std::cout << "<--=[ITEMS]=-->" << '\n';
    std::cout << "1) Go Back" << std::endl;
    for (int i = 0; i <= (shopItems.size() - 1); i++) { // List all Items
        std::cout << (i + 2) << ") " << shopItems.at(i).name << " - " << shopItems.at(i).price << " Gold" << '\n';
        sleep(1);
    }
}

void Shop::openItem(const Item& selectedItem) const {
    std::cout << "<--== " <<  selectedItem.name << " ==-->" << std::endl;
    std::cout << "- Price: " << selectedItem.price << " Gold" << '\n';
    std::cout << "- Description: " << selectedItem.description << std::endl;
    sleep(1);
    std::cout << "Would you like to buy this item? Y/N" << '\n';
}

void Shop::decideToPurchase(char yesNo, const Player& player, const Item& selectedItem) const {
    if (yesNo == 'Y' || yesNo == 'y') { // Attempt Purchase
        const bool succeededPurchase {player.attemptShopPurchase(selectedItem)}; // Get Result
        if (succeededPurchase) { // Yes
            std::cout << "Congrats! You purchased " << selectedItem.name << '.' << std::endl;
            return;
        }

        // No
        std::cout << "Sorry, you don't have enough gold to purchase this." << std::endl;
        return;

    } if (yesNo == 'N' || yesNo == 'n') { // Go back to Items
        return;
    }

    std::cout << "Type Y/N to choose." << std::endl;
}
