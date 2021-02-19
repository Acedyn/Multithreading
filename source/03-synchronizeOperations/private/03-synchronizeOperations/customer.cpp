#include "03-synchronizeOperations/customer.h"

ActorModel::Customer::Customer(const char* _name) :
    name(_name),
    orderedMeal(Meal()),
    state(STATE::COMMING) { }

ActorModel::Customer::Customer(const Customer& _other) :
    name(_other.name),
    orderedMeal(_other.orderedMeal),
    state(_other.state) { }

ActorModel::Customer::~Customer() { }

void ActorModel::Customer::setOrderedMeal(Meal _orderedMeal)
{
    std::lock_guard<std::mutex> autoLock(lockState);
    orderedMeal = _orderedMeal;
    state = STATE::WAITING;
}
