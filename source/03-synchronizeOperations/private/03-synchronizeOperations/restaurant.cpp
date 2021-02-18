#include <iostream>
#include <thread>
#include <chrono>

#include "03-synchronizeOperations/restaurant.h"

ActorModel::Restaurant::Restaurant():
    waiter(this),
    isOpen(false) { }

void ActorModel::Restaurant::openRestaurant()
{
    std::thread{waiter};

    isOpen = true;

    while(isOpen)
    {
        char* _customerName;
        std::cin.get(_customerName, 256);

        pendingCustomers.emplace_back(Customer(_customerName));

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
