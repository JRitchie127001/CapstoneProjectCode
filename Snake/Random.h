#pragma once
#include <random>

namespace Random {
    inline std::random_device SEEDER;
    inline std::mt19937 ENGINE{ SEEDER() };

    inline int Int(int Min, int Max) {
        std::uniform_int_distribution Get{ Min, Max };
        return Get(ENGINE);
    }
}