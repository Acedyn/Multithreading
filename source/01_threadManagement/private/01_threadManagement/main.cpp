#include <iostream>
#include "01_threadManagement/doubleHello.h"

int main(int argc, char** argv)
{
    std::cout << "########################################\n";
    std::cout << "Exercice : Double Hello\n";
    std::cout << "########################################\n\n";

    DoubleHello::doubleHello();
    std::cout << "\n\n";

    std::cout << "########################################\n";
    std::cout << "Exercice : Matrix Product\n";
    std::cout << "########################################\n\n";

    std::cin.get();
}

