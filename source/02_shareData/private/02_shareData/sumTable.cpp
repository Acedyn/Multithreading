#include "02_shareData/sumTable.h"
#include <iostream>
#include <mutex>
#include <thread>

float SumTable::singleThreadSum(const float* const elements, const int elementCount)
{
    float result = 0.0f;

    // Just loop over all the element and add they value to the result
    for(int i = 0; i < elementCount; i++)
    {
        result += elements[i];
    }

    return result;
}

float SumTable::multiThreadSum(const float* const elements, const int elementCount)
{
    float result = 0.0f;
    // We create a mutex that will be used as a common variable to lock the data
    std::mutex mutexSum;
    
    // We create a array of threads
    std::thread threads[elementCount];

    for(int i = 0; i < elementCount; i++)
    {
        // We launch a thread for each elements
        // We capture every parameters by reference exept i wich i copied
        threads[i] = std::thread([&result, &mutexSum, &elements, i]()->void
        {
            // We lock the mutex to ensure no one is using it a the same time
            std::lock_guard<std::mutex> lockSum(mutexSum);
            result += elements[i];
        });
    }

    // We wail for all the threads to finish
    for(int i = 0; i < elementCount; i++)
    {
        threads[i].join();
    }

    return result;
}


void SumTable::sumTable()
{
    std::cout << "Single threaded :\n";
    std::cout << singleThreadSum(elements, sizeof(elements) / sizeof(float)) << std::endl;
    std::cout << "Multi threaded :\n";
    std::cout << multiThreadSum(elements, sizeof(elements) / sizeof(float)) << std::endl;
}
