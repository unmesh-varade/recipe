#include "Recipe.h"

ostream &operator<<(ostream &os, const Recipe &recipe)
{
    os << "Recipe: " << recipe.name << "\nIngredients: ";
    for (const auto &ing : recipe.ingredients)
    {
        os << ing.name << " " << ing.quantity << " " << ing.unit << ", ";
    }
    os << "\nProcedure: " << recipe.procedure << "\n";
    return os;
}
