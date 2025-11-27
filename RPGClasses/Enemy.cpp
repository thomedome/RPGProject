//
// Created by win11 on 31/10/2025.
//

#include "common.h"
#include "Enemy.h"
#include "Player.h"

void Enemy::defensiveTurn() const {
    int random = Random::Int(1, 100); // 2nd Random Number (for 75 / 25 split on Defensive State)
    if (random <= 75) {
        heal();
    } else {
        addDodgeFlag();
    }
}

void Enemy::heal() const {
    {
        std::cout << name << " decides to heal." << '\n';
        // Create Random number for health regen - 15 LB, 45 UB - this is a % of max hp.
        int random = Random::Int(15, 45);
        int hpToAdd = ceil(currentHP * (random * 0.01));

        // Check if HP goes over - if so, change to number needed to go max hp.
        if (currentHP + hpToAdd > maxHP) {
            hpToAdd = ceil(currentHP * ((maxHP - currentHP) * 0.01));
        }

        currentHP += hpToAdd;

        std::cout << name << " healed for " << hpToAdd << "% of their HP!" << '\n';
    }
}

void Enemy::addDodgeFlag() const {
    std::cout << name << " decided to attempt a dodge." << '\n';
    flags.emplace_back("Dodging");
}

void Enemy::takeTurn(const Player &pObject) const {

    if (searchVector(flags, "Silenced")) {
        std::cout << name << " is Silenced. Skipping turn!" << std::endl;
        flags.erase(std::ranges::find(flags, "Silenced"));
        return;
    }

    // Decision-Making
    int randomNum{Random::Int(1, 100)};
    if (randomNum <= 33) {
        // 33% Chance for a random thing
        state = Random;
    } else {
        // Normal Reasoning from here... XD
        if (currentHP >= (maxHP * .65)) {
            // If 65% HP or more
            state = Aggressive;
        } else if (currentHP >= (maxHP * .25)) {
            // If Over 25% HP
            state = Dodging;
        } else {
            state = Defensive;
        }
    }

    // Processing the above logic
    switch (state) {
        case Random: {
            const int random{Random::Int(1, 100)}; // Decides what to do on the Random State
            if (random <= 33) {
                attack(pObject);
            } else if (random <= 66) {
                defensiveTurn();
            } else {
                addDodgeFlag();
            }
            break;
        }

        case Aggressive: {
            attack(pObject);
            break;
        }
        case Defensive: {
            defensiveTurn();
            break;
        }
        case Dodging: {
            addDodgeFlag();
            break;
        }
    }
}

void Enemy::takeDamage(const int damage) const {
    currentHP -= damage;
}

void Enemy::displayStats() const {
    std::cout << "<-- " << name << "'s stats --> " << "\n";
    std::cout << "HP: " << currentHP << "/" << maxHP << '\n';
    std::cout << "Ability Power: " << abilityPower << '\n';
    std::cout << "Defense: " << defense << '\n';
    std::cout << "Level: " << level << '\n';
    sleep(3);
    // waitForEnter();
    // cls();
}

void Enemy::attack(const Player &pObject) const {
    std::cout << name << " chose to attack." << '\n';
    int damageIncArmor = calculateDamageIncArmor(abilityPower, pObject.defense);

    if (searchVector(pObject.flags, std::string{"Dodging"})) {
        // Search the enemy flags vector for dodging
        pObject.flags.erase(std::vector<std::string>::const_iterator(0));
        // Just for now, dodging will always be element 0.
        int random = Random::Int(1, 100);
        if (random <= 35) {
            std::cout << "You dodged the attack!" << '\n';
            return;
        }
        std::cout << "You tried to dodge but failed." << '\n';
        std::cout << name << " dealt " << damageIncArmor << " damage to you..." << std::endl;
        pObject.takeDamage(damageIncArmor);
        return;
    }

    pObject.takeDamage(damageIncArmor);
    std::cout << name << " dealt " << damageIncArmor << " damage to you..." << std::endl;
}
