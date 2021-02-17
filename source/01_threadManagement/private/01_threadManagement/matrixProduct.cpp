#include "01_threadManagement/matrixProduct.h"
#include <iostream>
#include <thread>
#include <chrono>

float** MatrixProduct::singleThreadProduct(const float (&m1)[4][4], const float (&m2)[4][4])
{
    float** product = nullptr;
    product = new float*[4];
    for(int row = 0; row < 4; row++)
    {
        product[row] = new float[4];

        for(int column = 0; column < 4; column++)
        {
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
    std::thread threads[4];
    for(int row = 0; row < 4; row++)
    {
        threads[row] = std::thread([&]()->void
        {       
            product[row] = new float[4];

            for(int column = 0; column < 4; column++)
            {
                float value = 0.0f;
                for(int i = 0; i < 4; i++)
                {
                    value += m1[row][i] * m2[i][column];
                }
                product[row][column] = value;
            }
        });
    }

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
