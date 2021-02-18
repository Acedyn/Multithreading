#include "03-synchronizeOperations/meal.h"
#include <vcruntime_string.h>
#include <cstring>

ActorModel::Meal::Meal(const char* _name, std::array<char*, 3> _ingredients):
    name(_name),
    ingredients(_ingredients),
    state(STATE::ORDERED) { }


