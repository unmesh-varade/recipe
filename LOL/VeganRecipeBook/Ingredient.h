#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "NamedEntity.h"
#include <string>
using namespace std;

class Ingredient : public NamedEntity
{
public:
    double quantity;
    string unit;

    Ingredient() : NamedEntity(), quantity(0), unit("") {}
    Ingredient(string n, double q, string u) : NamedEntity(n), quantity(q), unit(u) {}

    Ingredient multiply(double factor) const
    {
        return Ingredient(name, quantity * factor, unit);
    }
};

#endif
