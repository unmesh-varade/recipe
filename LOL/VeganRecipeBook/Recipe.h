#ifndef RECIPE_H
#define RECIPE_H

#include "Ingredient.h"
#include <vector>
#include <iostream>
using namespace std;

class Recipe : public NamedEntity
{
public:
    vector<Ingredient> ingredients;
    string procedure;
    double price; // Price of the recipe/dish

    Recipe() : NamedEntity(), procedure(""), price(0.0) {}
    Recipe(string n, vector<Ingredient> ing, string proc, double p) : NamedEntity(n), ingredients(ing), procedure(proc), price(p) {}

    vector<Ingredient> scaleIngredients(double factor) const
    {
        vector<Ingredient> scaledIngredients;
        for (const auto &ing : ingredients)
        {
            scaledIngredients.push_back(ing.multiply(factor));
        }
        return scaledIngredients;
    }

    double getPrice() const {
        return price; // Returns the price of the recipe
    }

    friend ostream &operator<<(ostream &os, const Recipe &recipe);
};

ostream &operator<<(ostream &os, const Recipe &recipe)
{
    os << "Recipe: " << recipe.name << "\nIngredients: ";
    for (const auto &ing : recipe.ingredients)
    {
        os << ing.name << " " << ing.quantity << " " << ing.unit << ", ";
    }
    os << "\nProcedure: " << recipe.procedure << "\n";
    os << "Price: $" << recipe.price << "\n"; // Display price
    return os;
}

#endif
