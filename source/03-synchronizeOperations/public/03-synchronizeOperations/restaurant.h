#pragma once

#include <vector>
#include <condition_variable>

#include "waiter.h"
#include "customer.h"

namespace ActorModel
{
    class Restaurant
    {
    public:
        Restaurant();

        void openRestaurant();

    private:
        bool isOpen = false;
        Waiter waiter;
        std::vector<Customer> pendingCustomers;
        std::vector<Customer> eatingCustomers;

        std::condition_variable customerCondition;
    };
}
