#include <iostream>

#include "03-synchronizeOperations/cooker.h"
#include "03-synchronizeOperations/restaurant.h"

ActorModel::Cooker::Cooker(Restaurant* _restaurant, std::condition_variable* _workCondition) :
    isWorking(false),
    jobLeft(0),
    restaurant(_restaurant),
    workCondition(_workCondition) { }


void ActorModel::Cooker::work()
{
    while(isWorking)
    {
        // Lock the state of the waiter to read it
        std::unique_lock<std::mutex> autoLock(lockState);
        // Wait for any jobs to do
        workCondition->wait(autoLock, [=]()->bool{ return jobLeft > 0; });
        // Unlock manualy the mutex
        autoLock.unlock();

        // If there is some customer that are waiting
        Customer* _comingCustomer = restaurant->getWaitingCustomers();
        if(_comingCustomer != nullptr)
        {
            cookOrder(_comingCustomer);
            continue;
        }
    }
}

void ActorModel::Cooker::startWorking()
{
    if(isWorking) { return; }
    std::lock_guard<std::mutex> autoLock(lockState);
    isWorking = true;
    cookerThread = std::thread([&]()->void{ work(); });
}

void ActorModel::Cooker::stopWorking()
{
    if(!isWorking) { return; }
    std::lock_guard<std::mutex> autoLock(lockState);
    isWorking = false;
    cookerThread.join();
}

void ActorModel::Cooker::addJob()
{
    std::lock_guard<std::mutex> autoLock(lockState);
    jobLeft++;
}

void ActorModel::Cooker::removeJob()
{
    std::lock_guard<std::mutex> autoLock(lockState);
    jobLeft--;
}

void ActorModel::Cooker::cookOrder(Customer* _waitingCustomer)
{
    // Inform the user that a new meal is being cooked
    std::cout 
        << "Cooker : Hello "
        << _waitingCustomer->name
        << " I am starting to cook your meal : "
        << _waitingCustomer->getOrderedMeal().getName() << "\n";
    
    // Wait a bit to pretend we are working
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // Inform the user that a meal is done cooking
    std::cout 
        << "Cooker : Alright "
        << _waitingCustomer->name
        << " Your meal : "
        << _waitingCustomer->getOrderedMeal().getName()
        << " is done cooking, i will send it to the chief\n";

    removeJob();
}
