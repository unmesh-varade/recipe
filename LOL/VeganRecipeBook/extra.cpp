#include "FileHandler.h"
#include "User.h"
#include "VeganRecipeBook.h"
#include "NonVeganRecipeBook.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void displayChefMenu() {
    cout << "Chef Menu:\n";
    cout << "1. View Recipe\n";
    cout << "2. Create Shopping List\n";
    cout << "3. Add Vegan Recipe\n";
    cout << "4. Add Non-Vegan Recipe\n";
    cout << "5. Display All Vegan Recipes\n";
    cout << "6. Display All Non-Vegan Recipes\n";
    cout << "7. Update Vegan Recipe Ingredients\n";
    cout << "8. Update Non-Vegan Recipe Ingredients\n";
    cout << "9. Delete Vegan Recipe\n";
    cout << "10. Delete Non-Vegan Recipe\n";
    cout << "11. Save & Exit\n";
}



int main()
{
    FileHandler fileHandler;
    VeganRecipeBook veganRecipeBook;
    NonVeganRecipeBook nonVeganRecipeBook;

    vector<Recipe> veganRecipes = fileHandler.loadRecipes("recipeveg.txt");
    for (const auto &recipe : veganRecipes)
    {
        veganRecipeBook.addRecipe(recipe);
    }

    vector<Recipe> nonVeganRecipes = fileHandler.loadRecipes("recipenonveg.txt");
    for (const auto &recipe : nonVeganRecipes)
    {
        nonVeganRecipeBook.addRecipe(recipe);
    }

    User user("Chef AI");
    int choice;
    string recipe_name;

    while (true)
    {
        displayChefMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter recipe name: ";
            cin.ignore();
            getline(cin, recipe_name);
            if (Recipe *recipe = user.requestRecipe(veganRecipeBook, recipe_name))
            {
                cout << *recipe;
            }
            else if (Recipe *recipe = user.requestRecipe(nonVeganRecipeBook, recipe_name))
            {
                cout << *recipe;
            }
            else
            {
                cout << "Recipe not found!\n";
            }
            break;
        case 2:
        {
            vector<Recipe *> selected_recipes;
            cout << "Enter number of recipes: ";
            int num_recipes;
            cin >> num_recipes;
            for (int i = 0; i < num_recipes; ++i)
            {
                cout << "Enter recipe name: ";
                cin.ignore();
                getline(cin, recipe_name);
                if (Recipe *recipe = user.requestRecipe(veganRecipeBook, recipe_name))
                {
                    selected_recipes.push_back(recipe);
                }
                else if (Recipe *recipe = user.requestRecipe(nonVeganRecipeBook, recipe_name))
                {
                    selected_recipes.push_back(recipe);
                }
                else
                {
                    cout << "Recipe not found!\n";
                }
            }
            cout << "Enter factor to scale (e.g., 2 for double): ";
            double factor;
            cin >> factor;
            ShoppingList shoppingList = user.createShoppingList(selected_recipes, factor);
            shoppingList.display();
            fileHandler.saveShoppingList(shoppingList, "shopping_list.txt");
            break;
        }
        case 3:
        {
            string name, procedure, ingredient_str;
            cout << "Enter vegan recipe name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter procedure: ";
            getline(cin, procedure);
            cout << "Enter ingredients (name|quantity|unit, separated by commas): ";
            getline(cin, ingredient_str);
            vector<Ingredient> ingredients;
            stringstream ss(ingredient_str);
            string ing;
            while (getline(ss, ing, ','))
            {
                stringstream ss_detail(ing);
                string ing_name, quantity_str, unit;
                getline(ss_detail, ing_name, '|');
                getline(ss_detail >> ws, quantity_str, '|');
                getline(ss_detail >> ws, unit);
                double quantity = stod(quantity_str);
                ingredients.emplace_back(ing_name, quantity, unit);
            }
            Recipe newRecipe(name, ingredients, procedure);
            veganRecipeBook.addRecipe(newRecipe);
            cout << "Recipe added successfully!\n";
            break;
        }
        case 4:
        {
            string name, procedure, ingredient_str;
            cout << "Enter non-vegan recipe name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter procedure: ";
            getline(cin, procedure);
            cout << "Enter ingredients (name|quantity|unit, separated by commas): ";
            getline(cin, ingredient_str);
            vector<Ingredient> ingredients;
            stringstream ss(ingredient_str);
            string ing;
            while (getline(ss, ing, ','))
            {
                stringstream ss_detail(ing);
                string ing_name, quantity_str, unit;
                getline(ss_detail, ing_name, '|');
                getline(ss_detail >> ws, quantity_str, '|');
                getline(ss_detail >> ws, unit);
                double quantity = stod(quantity_str);
                ingredients.emplace_back(ing_name, quantity, unit);
            }
            Recipe newRecipe(name, ingredients, procedure);
            nonVeganRecipeBook.addRecipe(newRecipe);
            cout << "Recipe added successfully!\n";
            break;
        }
        case 5:
            veganRecipeBook.displayAllRecipes();
            break;
        case 6:
            nonVeganRecipeBook.displayAllRecipes();
            break;
        case 7:
            cout << "Enter vegan recipe name to update: ";
            cin.ignore();
            getline(cin, recipe_name);
            veganRecipeBook.updateRecipe(recipe_name);
            break;
        case 8:
            cout << "Enter non-vegan recipe name to update: ";
            cin.ignore();
            getline(cin, recipe_name);
            nonVeganRecipeBook.updateRecipe(recipe_name);
            break;
        case 9:
            cout << "Enter vegan recipe name to delete: ";
            cin.ignore();
            getline(cin, recipe_name);
            veganRecipeBook.deleteRecipe(recipe_name);
            break;
        case 10:
            cout << "Enter non-vegan recipe name to delete: ";
            cin.ignore();
            getline(cin, recipe_name);
            nonVeganRecipeBook.deleteRecipe(recipe_name);
            break;
        case 11:
            fileHandler.saveRecipes(veganRecipeBook, "recipeveg.txt");
            fileHandler.saveRecipes(nonVeganRecipeBook, "recipenonveg.txt");
            cout << "Recipes saved. Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice, try again!\n";
            break;
        }
    }
    return 0;
}
