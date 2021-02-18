#pragma once

#include "meal.h"

namespace ActorModel
{
    class Customer
    {
    public:
        Customer(const char* _name);
        ~Customer();

        void order();
    private:
        const char* name;
        Meal* orderedMeal;
    };
}

