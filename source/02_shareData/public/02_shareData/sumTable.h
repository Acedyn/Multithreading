#pragma once

namespace SumTable
{
    const float elements[8] = {2.4f, 477.3f, 14.2f, 0.4f, 0.07f, 788.01f, 1.0f, 98.4f};

    float singleThreadSum(const float* const elements, const int elementCount);
    float multiThreadSum(const float* const elements, const int elementCount);


    void sumTable();
}
