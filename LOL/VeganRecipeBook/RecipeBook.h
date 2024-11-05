#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include "Recipe.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class RecipeBook
{
public:
    unordered_map<string, Recipe> recipes;

public:
    virtual void addRecipe(const Recipe &recipe)
    {
        recipes[recipe.name] = recipe;
    }

    Recipe *searchRecipe(const string &name)
    {
        if (recipes.find(name) != recipes.end())
        {
            return &recipes[name];
        }
        return nullptr;
    }

    void displayAllRecipes() const
    {
        cout << left << setw(20) << "Recipe Name" << "Ingredients\n";
        cout << "---------------------------------------\n";
        for (const auto &pair : recipes)
        {
            cout << left << setw(20) << pair.first << pair.second.ingredients.size() << " items\n";
        }
    }

    virtual void updateRecipe(const string &name)
    {
        cout << "Update functionality not implemented.\n";
    }

    virtual bool deleteRecipe(const string &name)
    {
        return recipes.erase(name) > 0;
    }

    unordered_map<string, Recipe> getRecipes() const
    {
        return recipes;
    }
};

#endif
