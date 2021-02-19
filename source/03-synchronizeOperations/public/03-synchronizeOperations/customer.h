#pragma once

#include <mutex>

#include "meal.h"

namespace ActorModel
{
    class Customer
    {
    public:
        enum class STATE
        {
            COMMING = 0,
            WAITING = 1,
            EATING = 2,
            LEAVING = 3
        };

    public:
        Customer(const char* _name);
        Customer(const Customer& _other);
        ~Customer();

        STATE getState() const { return state; }
        void setOrderedMeal(Meal _orderedMeal);
        Meal getOrderedMeal() const { return orderedMeal; }

        const char* name;

    private:
        Meal orderedMeal;
        STATE state;
        std::mutex lockState;
    };
}

