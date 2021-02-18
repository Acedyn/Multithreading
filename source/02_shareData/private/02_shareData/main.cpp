#include <iostream>
#include "02_shareData/sumTable.h"
#include "02_shareData/ordering.h"

int main(int argc, char** argv)
{
    std::cout << "########################################\n";
    std::cout << "Exercice : Sum of a table\n";
    std::cout << "########################################\n\n";

    SumTable::sumTable();
    std::cout << "\n\n";

    std::cout << "########################################\n";
    std::cout << "Exercice : Ordering with a mutex\n";
    std::cout << "########################################\n\n";

    Ordering::ordering();
    std::cout << "\n\n";

    std::cin.get();
}

