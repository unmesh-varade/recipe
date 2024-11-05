#include "RecipeBook.h"
#include <sstream>

void RecipeBook::updateRecipe(const string &name)
{
    if (recipes.find(name) != recipes.end())
    {
        string ingredient_str;
        cout << "Enter new ingredients (name|quantity|unit, separated by commas): ";
        cin.ignore();
        getline(cin, ingredient_str);
        vector<Ingredient> ingredients;
        stringstream ss_ing(ingredient_str);
        string ing;
        while (getline(ss_ing, ing, ','))
        {
            stringstream ss_detail(ing);
            string ing_name, quantity_str, unit;
            getline(ss_detail, ing_name, '|');
            getline(ss_detail >> ws, quantity_str, '|');
            getline(ss_detail >> ws, unit);
            double quantity = stod(quantity_str);
            ingredients.emplace_back(ing_name, quantity, unit);
        }
        recipes[name].ingredients = ingredients;
        cout << "Ingredients updated successfully!\n";
    }
    else
    {
        cout << "Recipe not found!\n";
    }
}

bool RecipeBook::deleteRecipe(const string &name)
{
    if (recipes.erase(name))
    {
        cout << "Recipe deleted successfully!\n";
    }
    else
    {
        cout << "Recipe not found!\n";
    }
}
