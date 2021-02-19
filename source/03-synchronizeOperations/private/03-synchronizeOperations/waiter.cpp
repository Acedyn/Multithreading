#include <array>
#include <iostream>
#include <string>

#include "03-synchronizeOperations/waiter.h"
#include "03-synchronizeOperations/restaurant.h"

ActorModel::Waiter::Waiter(
        Restaurant* _restaurant, 
        std::condition_variable* _workCondition, 
        std::mutex* _lockInputQuery):
    isWorking(false),
    jobLeft(0),
    restaurant(_restaurant),
    workCondition(_workCondition),
    lockInputQuery(_lockInputQuery) { }

void ActorModel::Waiter::work()
{
    while(isWorking)
    {
        // Lock the state of the waiter to read it
        std::unique_lock<std::mutex> autoLock(lockState);
        // Wait for any jobs to do
        workCondition->wait(autoLock, [=]()->bool{ return jobLeft > 0; });
        // Unlock manualy the mutex
        autoLock.unlock();

        // If there is some customer that just came in
        Customer* _comingCustomer = restaurant->getCommingCustomers();
        if(_comingCustomer != nullptr)
        {
            takeOrder(_comingCustomer);
            continue;
        }
    }
}

void ActorModel::Waiter::startWorking()
{
    if(isWorking) { return; }
    std::lock_guard<std::mutex> autoLock(lockState);
    isWorking = true;
    waiterThread = std::thread([&]()->void{ work(); });
}

void ActorModel::Waiter::stopWorking()
{
    if(!isWorking) { return; }
    std::lock_guard<std::mutex> autoLock(lockState);
    isWorking = false;
    waiterThread.join();
}

void ActorModel::Waiter::addJob()
{
    std::lock_guard<std::mutex> autoLock(lockState);
    jobLeft++;
}

void ActorModel::Waiter::removeJob()
{
    std::lock_guard<std::mutex> autoLock(lockState);
    jobLeft--;
}

void ActorModel::Waiter::takeOrder(Customer* _comingCustomer)
{
    // Initialize the name of the meal
    std::string _mealName;
    // Initialize the array of ingredients
    std::array<std::string, 3> _ingredients;
    // Lock the inputQuery mutex to make sure we ask questions one by one
    lockInputQuery->lock();
    std::cout 
        << "Waiter : Hello "
        << _comingCustomer->name
        << " What meal do you want ?\n";
    std::getline(std::cin, _mealName);
    std::cout << "Waiter : Good, what will be the first ingredient ?\n";
    std::getline(std::cin, _ingredients[0]);
    std::cout << "Waiter : Alright, what will be the second ingredient ?\n";
    std::getline(std::cin, _ingredients[1]);
    std::cout << "Waiter : Okay, and what will be the last ingredient ?\n";
    std::getline(std::cin, _ingredients[2]);
    std::cout << "Waiter : Very good choice ! I will send this to the kitchen\n\n";

    // Unlock the inputQuery mutex
    lockInputQuery->unlock();
    
    // Set the orderedMeal to the customer data
    _comingCustomer->setOrderedMeal({ _mealName, _ingredients });
    // Add a job for the cooker
    restaurant->cooker.addJob();
    // Notify the cooker that there is new job to do
    restaurant->cookerCondition.notify_one();
    removeJob();
}
