#include "03-synchronizeOperations/waiter.h"

ActorModel::Waiter::Waiter(Restaurant* _restaurant):
    isWorking(true),
    restaurant(_restaurant) { }

void ActorModel::Waiter::operator()()
{
    while(isWorking)
    {

    }
}

void ActorModel::Waiter::takeOrder()
{

}
