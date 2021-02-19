#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>

namespace ActorModel
{
    class Restaurant;
    class Customer;

    class Cooker
    {
    public:
        Cooker(
            Restaurant* _restaurant, 
            std::condition_variable* _workCondition);
        
        void startWorking();
        void stopWorking();
        void addJob();
        void removeJob();
        
    private:
        void work();
        void cookOrder(Customer* _waitingCustomer);

        bool isWorking;
        int jobLeft;
        Restaurant* restaurant;
        std::condition_variable* workCondition;
        std::thread cookerThread;
        std::mutex lockState;
    };
}
