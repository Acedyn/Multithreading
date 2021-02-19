#include "03-synchronizeOperations/meal.h"
#include <cstring>

ActorModel::Meal::Meal(const std::string _name, std::array<std::string, 3> _ingredients) :
    name(_name),
    ingredients(_ingredients),
    state(STATE::ORDERED) { }

ActorModel::Meal::Meal(const Meal& _other) :
    name(_other.name),
    ingredients(_other.ingredients),
    state(_other.state) { }

ActorModel::Meal::~Meal()
{

}

ActorModel::Meal& ActorModel::Meal::operator=(const Meal& _other)
{
    name = _other.name;
    ingredients = _other.ingredients;
    result = _other.result;

    return *this;
}
