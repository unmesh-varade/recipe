#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H

#include "Ingredient.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

class ShoppingList : public NamedEntity
{
private:
    unordered_map<string, Ingredient> ingredients;

public:
    void addIngredients(const Ingredient &ingredient)
    {
        if (ingredients.find(ingredient.name) != ingredients.end())
        {
            ingredients[ingredient.name].quantity += ingredient.quantity;
        }
        else
        {
            ingredients[ingredient.name] = ingredient;
        }
    }

    void addRecipeIngredients(const vector<Ingredient> &recipeIngredients)
    {
        for (const auto &ingredient : recipeIngredients)
        {
            addIngredients(ingredient);
        }
    }

    void display() const
    {
        cout << "Shopping List:\n";
        for (const auto &ing : ingredients)
        {
            cout << ing.second.name << " " << ing.second.quantity << " " << ing.second.unit << "\n";
        }
    }

    friend ostream &operator<<(ostream &os, const ShoppingList &shoppingList);
};

ostream &operator<<(ostream &os, const ShoppingList &shoppingList)
{
    os << "Shopping List:\n";
    for (const auto &ing : shoppingList.ingredients)
    {
        os << ing.second.name << " " << ing.second.quantity << " " << ing.second.unit << "\n";
    }
    return os;
}

#endif
