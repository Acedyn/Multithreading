#pragma once

#include <array>
#include <string>

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
        Meal() { }
        Meal(const std::string _name, std::array<std::string, 3> _ingredients);
        Meal(const Meal& _other);
        ~Meal();

        Meal& operator=(const Meal& _other);
        std::string getName() const { return name; }
        std::array<std::string, 3> getIngredients() const { return ingredients; }

    private:
        std::string name;
        std::array<std::string, 3> ingredients;
        char* result;
        STATE state;
    };
}
