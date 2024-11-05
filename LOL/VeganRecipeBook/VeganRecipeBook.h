#ifndef VEGANRECIPEBOOK_H
#define VEGANRECIPEBOOK_H

#include "RecipeBook.h"
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class VeganRecipeBook : public RecipeBook
{
public:
    void addRecipe(const Recipe &recipe) override
    {
        for (const auto &ingredient : recipe.ingredients)
        {
            if (!isVegan(ingredient))
            {
                cout << "Recipe \"" << recipe.name << "\" is not vegan and cannot be added to the Vegan Recipe Book.\n";
                return;
            }
        }
        RecipeBook::addRecipe(recipe);
        cout << "Recipe \"" << recipe.name << "\" added to the Vegan Recipe Book.\n";
    }

    void updateRecipe(const string &name) override
    {
        auto it = recipes.find(name);
        if (it != recipes.end())
        {
            Recipe updatedRecipe = it->second;
            for (const auto &ingredient : updatedRecipe.ingredients)
            {
                if (!isVegan(ingredient))
                {
                    cout << "Updated recipe \"" << name << "\" contains non-vegan ingredients and cannot be updated.\n";
                    return;
                }
            }
            recipes[name] = updatedRecipe;
            cout << "Recipe \"" << name << "\" updated successfully.\n";
        }
        else
        {
            cout << "Recipe \"" << name << "\" not found!\n";
        }
    }

    bool deleteRecipe(const string &name) override
    {
        if (recipes.erase(name) > 0)
        {
            cout << "Recipe \"" << name << "\" deleted from the Vegan Recipe Book.\n";
            return true;
        }
        else
        {
            cout << "Recipe \"" << name << "\" not found!\n";
            return false;
        }
    }

private:
    bool isVegan(const Ingredient &ingredient) const
    {
        return true;
    }
};

#endif
