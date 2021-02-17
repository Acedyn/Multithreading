#pragma once

namespace MatrixProduct
{
    const float matrix1[4][4] = { 
       { 0.87f, 0.42f, 0.22f, 0.0f }, 
       { -0.35f, 0.88f, -0.29f, 0.0f }, 
       { -0.32f, 0.18f, 0.92f, 0.0f }, 
       {-0.55f, 0.52f, 0.28f, 1.0f } };
    const float matrix2[4][4] = {
       { 0.33f, 0.88f, -0.33f, 0.0f },
       { -0.04f, -0.33f, -0.93f, 0.0f },
       { -0.94f, 0.32f, -0.07f, 0.0f },
       { 1.53f, -0.28f, -1.26f, 1.0f }};

    float** singleThreadProduct(const float (&m1)[4][4], const float (&m2)[4][4]);
    float** multiThreadProduct(const float (&m1)[4][4], const float (&m2)[4][4]);

    void matrixProduct();
}
