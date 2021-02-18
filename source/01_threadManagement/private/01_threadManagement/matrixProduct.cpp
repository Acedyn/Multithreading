#include "01_threadManagement/matrixProduct.h"
#include <iostream>
#include <thread>
#include <chrono>

float** MatrixProduct::singleThreadProduct(const float (&m1)[4][4], const float (&m2)[4][4])
{
    float** product = nullptr;
    product = new float*[4];
    // Loop over all the row of the matrix
    for(int row = 0; row < 4; row++)
    {
        // Create an new array for that row
        product[row] = new float[4];

        // Loop over all the column of that row
        for(int column = 0; column < 4; column++)
        {
            // Compute the value of that [row][column]
            float value = 0.0f;
            for(int i = 0; i < 4; i++)
            {
                value += m1[row][i] * m2[i][column];
            }
            product[row][column] = value;
        }
    }

    return product;
}

float** MatrixProduct::multiThreadProduct(const float (&m1)[4][4], const float (&m2)[4][4])
{
    float** product = nullptr;
    product = new float*[4];
    // We create a array of threads
    std::thread threads[4];
    // Loop over all the row of the matrix
    for(int row = 0; row < 4; row++)
    {
        // We launch a thread for each row
        // We capture everything by reference
        threads[row] = std::thread([&]()->void
        {       
            // Create an new array for that row
            product[row] = new float[4];

            // Loop over all the column of that row
            for(int column = 0; column < 4; column++)
            {
                // Compute the value of that [row][column]
                float value = 0.0f;
                for(int i = 0; i < 4; i++)
                {
                    value += m1[row][i] * m2[i][column];
                }
                product[row][column] = value;
            }
        });
    }

    // We wail for all the threads to finish
    for(int threadId = 0; threadId < 4; threadId++)
    {
        threads[threadId].join();
    }

    return product;
}

void MatrixProduct::matrixProduct()
{
    auto time1 = std::chrono::high_resolution_clock::now();
    float** singleThreadMatrix = singleThreadProduct(matrix1, matrix2);
    auto time2 = std::chrono::high_resolution_clock::now();
    
    // Loop over all the elements of the matrix to print them
    std::cout << "Single threaded :\n";
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < 4; column++)
        {
            std::cout << singleThreadMatrix[row][column] << ", ";
        }
        std::cout << "\n";
    }
    std::cout << "Time elapsed : " << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
    std::cout << "\n\n";
    delete singleThreadMatrix;


    time1 = std::chrono::high_resolution_clock::now();
    float** multiThreadMatrix = multiThreadProduct(matrix1, matrix2);
    time2 = std::chrono::high_resolution_clock::now();
    
    // Loop over all the elements of the matrix to print them
    std::cout << "Multi threaded :\n";
    for(int row = 0; row < 4; row++)
    {
        for(int column = 0; column < 4; column++)
        {
            std::cout << multiThreadMatrix[row][column] << ", ";
        }
        std::cout << "\n";
    }
    std::cout << "Time elapsed : " << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
    std::cout << "\n\n";
    delete multiThreadMatrix;
}
