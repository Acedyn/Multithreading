#pragma once

#include <vector>
#include <condition_variable>
#include <mutex>

#include "waiter.h"
#include "customer.h"

namespace ActorModel
{
    class Restaurant
    {
    public:
        Restaurant();
        ~Restaurant();

        // Start a thread for each worker and wait for input
        void openRestaurant();
        void addCustomer(const char* _customerName);
        Customer* getCommingCustomers();

    private:
        bool isOpen = false;
        std::vector<Customer> customers;
        std::mutex lockState;
        std::mutex lockInputQuery;
        
        // Workers
        Waiter waiter;
        std::condition_variable waiterCondition;
    };
}
