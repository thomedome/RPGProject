    // This is a Turn-based CLI RPG created by thomedome :)
// Core Game Loop:
// -- Round starts
// -- Player chooses between Attack, Heal, Dodge and Cast
// -- Option Subtypes:
// -- -- Attack: Self Explanatory
// -- -- Heal: Also Self Explanatory - works off of random max hp%
// -- -- Dodge: You get the gist... X% chance depending on level
// -- -- Cast: Use a spell. Only one per battle though.
// -- After the player chooses, the enemy (AI) will do the same.
// -- After this round, the player will get some rewards (gold, xp etc.) in which they can
// -- increase their level and buy new items to get better stats.
#include "RPGClasses/common.h"
#include "RPGClasses/Player.h"
#include "RPGClasses/Enemy.h"
#include "RPGClasses/Item.h"
#include "RPGClasses/Shop.h"
#include "RPGClasses/Spell.h"

int round(Player &pObject, const Enemy &eObject) {
    constexpr bool roundOngoing {true};

    while (roundOngoing) {
        // Give player choice
        std::cout << "What would you like to do, " << pObject.name << "? \n";
        sleep(2);
        std::cout << "1) Attack" << '\n' << "2) Heal" << '\n' << "3) Dodge" << '\n' << "4) Cast" << '\n' << "5) View Stats"
                << '\n';
        std::cout << "p.s - type the number of action that you want to do, not the name." << '\n';

        // Allocate response variable + gather user input + Handle player choice
        switch (const int response = getIntInput("")) {
            case 1: {
                // Attack
                pObject.attack(eObject);
                break;
            }

            case 2: {
                // Heal
                pObject.heal();
                break;
            }

            case 3: {
                // Dodge
                pObject.addDodgeFlag();
                break;
            }

            case 4: {
                // Cast
                pObject.cast(pObject);
                break;
            }

            case 5: {
                // View Stats
                int viewChoice{};
                while (true) {
                    std::cout << "Would you like to view your stats or the enemies?" << '\n' << "1) Yours" << '\n' << "2) Enemy" << '\n' << "3) Exit Menu" << '\n';
                    std::cin >> viewChoice;
                    if (viewChoice == 1) {
                        // Player Stats
                        pObject.displayStats();
                        continue;
                    }

                    if (viewChoice == 2) {
                        // Enemy Stats
                        eObject.displayStats();
                        continue;
                    }

                    if (viewChoice == 3) { // Exit Menu
                        break;
                    }

                    std::cout << "Not an option." << '\n';
                }
                continue;
            }

            default: {
                std::cout << response << '\n';
                std::cout << "This isn't an option - try again." << '\n';
                continue;
            }
        }
            // Check that the round can still continue - enemy dead?
        if (eObject.currentHP <= 0) {
            std::cout << "You have slain " << eObject.name << '!' << '\n';
            return 1;
        }

        eObject.takeTurn(pObject);

        // Final check - check if player died to enemy turn.
        if (pObject.currentHP <= 0) {
            return 0;
        }
    }
}

int main() {
    std::cout << "Welcome to thomedome's RPG Game!" << '\n';
    std::cout << "1) New Game" << '\n';
    std::cout << "2) Load a Save" << '\n';

    Player player;

    // Get New / Load choice
    int NoL;
    bool loadedSave {false};
    std::cin >> NoL;

    if (NoL == 2) {
         loadedSave = player.loadGame();
    }

    std::cin.ignore();

    if (!loadedSave) { // If player doesn't load a save - either not choosing to or failure to open file
        std::cout << "What would you like to call your adventurer?" << '\n';

        // Get player name
        std::getline(std::cin, player.name);

        std::cout << "Thank you for playing," << player.name << "!\n";
    } else { // Player loaded a save
        std::cout << "Welcome back, " << player.name << "!\n";
    }

    while (true) {
        while (true) { // Start Menu / Shop Entry
                int pChoice {};
                std::cout << "Would you like to:" << '\n' << "1) View the shop" << '\n' << "2) New Round" << '\n' << "3) Save and Quit" << '\n';
                std::cin >> pChoice;

                if (pChoice == 1) { // View Shop

                    constexpr bool browsingShop {true};
                    while (browsingShop) {
                        Shop newShop;

                        newShop.openShop(player);

                        int shopChoice {};
                        std::cin >> shopChoice;

                        if (shopChoice == 1) { // View Items
                            constexpr bool browsingItems {true};
                            while (browsingItems) {

                                newShop.listItems();

                                int itemChoice {};
                                std::cin >> itemChoice;

                                if (itemChoice > 1) { // Select Item
                                    const Item& selectedItem {shopItems.at(itemChoice - 2)}; // -1 because indexing starts at 0... :')

                                    newShop.openItem(selectedItem); // List Item Name, Desc and Gold

                                    char yesNo {};
                                    std::cin >> yesNo;

                                    newShop.decideToPurchase(&yesNo, player, selectedItem); // Attempt to get purchase + logic
                                    continue;

                                } if (itemChoice == 1) { // Exit Menu
                                    break;
                                }
                            }
                        } if (shopChoice == 2) {
                            break;
                        } else {
                            std::cout << "Please enter a valid option!\n";
                        }
                    }

                } else if (pChoice == 2) { // Play Again
                    break;
                } else if (pChoice == 3) { // Save and Quit
                    player.saveGame();
                    return 0;
                }
            }
        // Create enemy object + give random stats
        Enemy enemy;
        enemy.name = enemyNames[Random::Int(0, enemyNames.size())];

        player.currOpponent = enemy;

        // Difficulty shall be random: Easy - 50%, Medium - 25%, Hard - 15%, Extreme - 10%
        const int random = Random::Int(1, 100);
        if (random <= 50) {
            enemy.difficulty = Easy;
        } else if (random <= 75) {
            enemy.difficulty = Medium;
        } else if (random <= 90) {
            enemy.difficulty = Hard;
        } else {
            enemy.difficulty = Extreme;
        }

        switch (enemy.difficulty) {
            // Assign rest of values based on level
            case Easy: {
                enemy.level = Random::Int(1, 4);
                enemy.maxHP = ceil(15 * enemy.level);
                enemy.currentHP = enemy.maxHP;
                enemy.abilityPower = Random::Int(1, 5);
                enemy.defense = Random::Int(1, 3);
                break;
            }

            case Medium: {
                enemy.level = Random::Int(5, 9);
                enemy.maxHP = ceil(17.5 * enemy.level);
                enemy.currentHP = enemy.maxHP;
                enemy.abilityPower = (Random::Int(5, 10));
                enemy.defense = Random::Int(3, 7);
                break;
            }

            case Hard: {
                enemy.level = Random::Int(10, 14);
                enemy.maxHP = ceil(21 * enemy.level);
                enemy.currentHP = enemy.maxHP;
                enemy.abilityPower = (Random::Int(13, 17));
                enemy.defense = Random::Int(7, 10);
                break;
            }

            case Extreme: {
                enemy.level = Random::Int(15, 18);
                enemy.maxHP = ceil(25 * enemy.level);
                enemy.currentHP = enemy.maxHP;
                enemy.abilityPower = (Random::Int(20, 30));
                enemy.defense = Random::Int(10, 15);

                // Max eHP is 518
                break;
            }
        }

        // Return an int to check if player won
        int survived = round(player, enemy);

        // If they survived, grant rewards + go to next turn
        if (survived == 1) {
            std::cout << "Congratulations! You have been rewarded:" << '\n';
            // Calculate and give rewards here
            int xpReward{};
            int goldReward{};
            switch (enemy.difficulty) {
                case Easy: {
                    xpReward = Random::Int(55, 85);
                    goldReward = Random::Int(65, 85);
                    break;
                }

                case Medium: {
                    xpReward = Random::Int(125, 175);
                    goldReward = Random::Int(100, 150);
                    break;
                }

                case Hard: {
                    xpReward = Random::Int(200, 250);
                    goldReward = Random::Int(150, 200);
                    break;
                }

                case Extreme: {
                    xpReward = Random::Int(300, 450);
                    goldReward = Random::Int(250, 300);
                    break;
                }
            }

            player.gold += goldReward;
            player.xp += xpReward;

            std::cout << " - " << xpReward << "XP" << '\n';
            std::cout << " - " << goldReward << "Gold" << std::endl;

            if (player.xp >= player.xpReq) {
                player.levelUp();
            }

            sleep(3);

        } else { // Any input that isn't 1 (1 is the player surviving)
            break;
        }
    }
    // Player dies
    std::cout << '\n' << "You died..." << '\n';
    std::cout << "RIP " << player.name << '\n';
    std::cout << "Thank you for playing!";
    return 0;
}