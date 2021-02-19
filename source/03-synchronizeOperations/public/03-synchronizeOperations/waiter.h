#pragma once

#include <mutex>
#include <thread>
#include <condition_variable>

namespace ActorModel
{
    class Restaurant;
    class Customer;

    class Waiter
    {
    public:
        Waiter(
            Restaurant* _restaurant, 
            std::condition_variable* _workCondition, 
            std::mutex* _lockInputQuery);
        
        void startWorking();
        void stopWorking();
        void addJob();
        void removeJob();
        
    private:
        void work();
        void takeOrder(Customer* _comingCustomer);

        bool isWorking;
        int jobLeft;
        Restaurant* restaurant;
        std::condition_variable* workCondition;
        std::mutex* lockInputQuery;
        std::mutex lockState;
        std::thread waiterThread;
    };
}
