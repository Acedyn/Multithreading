#include <iostream>
#include <string>
#include <chrono>

#include "03-synchronizeOperations/restaurant.h"

ActorModel::Restaurant::Restaurant():
    isOpen(false),
    waiter(this, &waiterCondition, &lockInputQuery),
    cooker(this, &cookerCondition) { }

ActorModel::Restaurant::~Restaurant()
{
    // Stop the waiter thread
    waiter.stopWorking();
    // Stop the cooker thread
    cooker.stopWorking();
}

void ActorModel::Restaurant::openRestaurant()
{
    // Start the waiter thread
    waiter.startWorking();
    // Start the cooker thread
    cooker.startWorking();

    // Open the restaurant
    isOpen = true;

    // Until someone close the restaurant
    while(isOpen)
    {
        // Lock the inputQuery mutex to make sure we ask questions one by one
        lockInputQuery.lock();
        // Welcome the user and ask for his name
        std::cout 
            << "Restaurant : Welcome to our restaurant !\n"
            << "Restaurant : What is your name ?" << std::endl;
        std::string _customerName;
        std::getline(std::cin, _customerName);
        std::cout << "Restaurant : Alright, someone will take care of you\n" << std::endl;
        // Add the customer to the list of customers
        addCustomer(_customerName);
        // Add a job for the waiter
        waiter.addJob();
        // Notify the waiter that there new jobs to do
        waiterCondition.notify_one();
        // Unlock the inputQuery mutex
        lockInputQuery.unlock();

        // Wait a bit to prevent 100% cpu usage
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void ActorModel::Restaurant::addCustomer(std::string _customerName)
{
    std::lock_guard<std::mutex> autoLock(lockState);
    customers.emplace_back(Customer(_customerName));
}

ActorModel::Customer* ActorModel::Restaurant::getCommingCustomers()
{
    // Loop over all the customers and find one that is in comming state
    for(Customer& _customer : customers)
    {
        if(_customer.getState() == ActorModel::Customer::STATE::COMMING)
        {
            return &_customer;
        }
    }

    // If no matching customers has been found return null
    return nullptr;
}

ActorModel::Customer* ActorModel::Restaurant::getWaitingCustomers()
{
    // Loop over all the customers and find one that is in waiting state
    for(Customer& _customer : customers)
    {
        if(_customer.getState() == ActorModel::Customer::STATE::WAITING)
        {
            return &_customer;
        }
    }

    // If no matching customers has been found return null
    return nullptr;
}
