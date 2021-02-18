#include "02_shareData/ordering.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

void Ordering::naivePrintNumbers()
{
    // We start the threa that will print odd numbers
    std::thread oddPrint([]()->void
    {
        for(int i = 1; i < 1000; i += 2)
        {
            std::cout << i << ", ";
        }
    });

    // We start the threa that will print even numbers
    std::thread evenPrint([]()->void
    {
        for(int i = 0; i < 1000; i += 2)
        {
            std::cout << i << ", ";
        }
    });

    oddPrint.join();
    evenPrint.join();
    std::cout << std::endl;
}

void Ordering::syncPrintNumbers()
{
    // We create a condition_variable
    std::condition_variable switchCondition;
    std::mutex mutexSync;
    // This state will be used with the condition_variable
    int state = 0;

    // We start the threa that will print odd numbers
    std::thread oddPrint([&]()->void
    {
        for(int i = 1; i < 1000; i += 2)
        {
            // Lock the mutex
            std::unique_lock<std::mutex> lockSwitch(mutexSync);
            // Test the condition, if true we continue, if false
            // unlock the mutex and go to wainting state
            switchCondition.wait(lockSwitch, [&]()->bool{ return state == 1; });
            std::cout << i << ", ";
            state = 0;
            // Notify the other thread that he can test his condition again
            // to leave his waiting state
            switchCondition.notify_one();
        }
    });

    // We start the threa that will print even numbers
    std::thread evenPrint([&]()->void
    {
        for(int i = 0; i < 1000; i += 2)
        {
            // Lock the mutex
            std::unique_lock<std::mutex> lockSwitch(mutexSync);
            // Test the condition, if true we continue, if false
            // unlock the mutex and go to wainting state
            switchCondition.wait(lockSwitch, [&]()->bool{ return state == 0; });
            std::cout << i << ", ";
            state = 1;
            // Notify the other thread that he can test his condition again
            // to leave his waiting state
            switchCondition.notify_one();
        }
    });

    oddPrint.join();
    evenPrint.join();
    std::cout << std::endl;
}

void Ordering::ordering()
{
    std::cout << "Naive version :\n";
    naivePrintNumbers();
    std::cout << "Synchronized version :\n";
    syncPrintNumbers();
}
