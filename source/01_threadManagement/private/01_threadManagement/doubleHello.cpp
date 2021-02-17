#include <iostream>
#include <thread>
#include "01_threadManagement/doubleHello.h"

void DoubleHello::helloFunction()
{
    std::cout << "Hello world from a function !\n";
}

void DoubleHello::HelloClass::operator()() const
{
    std::cout << "Hello world from a class !\n";
}


void DoubleHello::doubleHello()
{
    // Start thread with a function pointer
    std::thread t1(helloFunction);
    // Start thread with a lambda
    std::thread t2([]()->void{ std::cout << "Hello world from a lambda !\n"; });
    // Start thread with the () operator of a class 
    // (here we dont use parenthese to avoid function interpretation but logicaly it would world with parentheses too)
    std::thread t3{ HelloClass() };

    // std::thread.join will wait for the given thread to finish its job
    t1.join();
    t2.join();
    t3.join();
}
