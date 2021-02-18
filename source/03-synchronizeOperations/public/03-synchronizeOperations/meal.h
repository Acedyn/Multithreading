#pragma once

#include <array>

namespace ActorModel
{
    class Meal
    {
        enum STATE
        {
            ORDERED = 0,
            PREPARED = 1,
            COOKED = 2,
            SERVED = 3,
            EATED = 4,
        };

    public:
        Meal(const char* _name, std::array<char*, 3> _ingredients);
        ~Meal();

    private:
        const char* name;
        std::array<char*, 3> ingredients;
        char* result;
        STATE state;
    };
}
