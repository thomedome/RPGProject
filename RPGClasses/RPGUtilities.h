//
// Created by win11 on 29/10/2025.
//

#ifndef C_BASICS_RPGUTILITIES_H
#define C_BASICS_RPGUTILITIES_H
#pragma once

#include <chrono>
#include <thread>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

// Use for all random numbers instead of doing the full thing every time
class Random {
    public:
        static int Int(int min, int max) {
            static std::mt19937 gen(std::random_device{}()); // Only seeded once due to static tag
            std::uniform_int_distribution<int> dist(min, max);
            return dist(gen);
        }

        static float Float(float min, float max) {
            static std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<float> dist(min, max);
            return dist(gen);
        }

};

// Sleep function - I don't want to write ts constantly
inline void sleep(const int time) {
    std::this_thread::sleep_for(std::chrono::seconds(time));
}

inline bool searchVector(const std::vector<std::string>& vect, const std::string& search) {
    if (std::find(vect.begin(), vect.end(), search) != vect.end()) {
        return true;
    } else {
        return false;
    }
}

inline void cls() {
    std::system("cls");
}

inline int calculateDamageIncArmor(const int damage, const int armor) {
    return ceil(damage / (1 + (armor / 100)));
}

inline int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value)
            return value; // success
        else {
            std::cin.clear(); // clear the fail flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            // std::cout << "Invalid input, try again.\n";
        }
    }
}

inline void waitForEnter() {
    std::cin.clear(); // clear any fail state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush buffer
    std::cout << "\nPress ENTER to continue...";
    std::cin.get(); // now actually wait for ENTER
}

#endif //C_BASICS_RPGUTILITIES_H