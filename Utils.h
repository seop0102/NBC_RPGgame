#pragma once

#include <random>
#include <chrono>

namespace Utils {
    inline int getRandomInt(int min, int max) {
        static std::mt19937 rng(
            static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())
        );
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
    inline int rollDice() {
        return getRandomInt(1, 6);
    }

    inline bool checkChance(int percentage) {
        if (percentage < 0) return false;
        if (percentage >= 100) return true;
        return getRandomInt(1, 100) <= percentage;
    }
}