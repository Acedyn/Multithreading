#include <iostream>
#include <03-synchronizeOperations/restaurant.h>

int main(int argc, char** argv)
{
    std::cout << "########################################\n";
    std::cout << "Exercice : Actor - Model\n";
    std::cout << "########################################\n\n";

    ActorModel::Restaurant restaurant;
    restaurant.openRestaurant();

    std::cout << "\n\n";

    std::cin.get();
}


