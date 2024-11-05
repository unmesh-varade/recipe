#ifndef USER_H
#define USER_H

#include "RecipeBook.h"
#include "ShoppingList.h"
#include <string>
using namespace std;

class User
{
public:
    string name;

    User(string n) : name(n) {}

    Recipe *requestRecipe(RecipeBook &recipeBook, const string &recipe_name)
    {
        return recipeBook.searchRecipe(recipe_name);
    }

    ShoppingList createShoppingList(const vector<Recipe *> &recipes, double factor)
    {
        ShoppingList shoppingList;
        for (const auto &recipe : recipes)
        {
            shoppingList.addRecipeIngredients(recipe->scaleIngredients(factor));
        }
        return shoppingList;
    }
};

#endif
