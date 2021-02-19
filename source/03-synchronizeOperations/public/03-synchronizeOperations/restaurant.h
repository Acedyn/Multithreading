#pragma once

#include <string>
#include <vector>
#include <condition_variable>
#include <mutex>

#include "waiter.h"
#include "cooker.h"
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
        void addCustomer(std::string _customerName);
        Customer* getCommingCustomers();
        Customer* getWaitingCustomers();

        // Workers
        Waiter waiter;
        std::condition_variable waiterCondition;
        Cooker cooker;
        std::condition_variable cookerCondition;

    private:
        bool isOpen = false;
        std::vector<Customer> customers;
        std::mutex lockState;
        std::mutex lockInputQuery;
    };
}
