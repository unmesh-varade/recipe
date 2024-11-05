#include "FileHandler.h"
#include "User.h"
#include "VeganRecipeBook.h"
#include "NonVeganRecipeBook.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

void displayChefMenu()
{
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

void displayCustomerMenu()
{
    cout << "Customer Menu:\n";
    cout << "1. View Menu\n";
    cout << "2. Place Order\n";
    cout << "3. View Order\n";
    cout << "4. Make Payment\n";
    cout << "5. Exit\n";
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

    User user("Chef");
    User customer("Customer");
    int chefChoice, customerChoice;
    string recipe_name;
    map<string, int> order; // to store dish names and their quantities
    while (true)
    {
        int choice;
        cout << "Are you a Chef(0) or Customer(1) ?\n";
        cin >> choice;
        if (choice == 0)
        {
            // Chef menu
            while (true)
            {
                displayChefMenu();
                cout << "Enter your choice: ";
                cin >> chefChoice;
                switch (chefChoice)
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
                    double price;
                    cout << "Enter vegan recipe name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter procedure: ";
                    getline(cin, procedure);
                    cout << "Enter price: ";
                    cin >> price;
                    cout << "Enter ingredients (name|quantity|unit, separated by commas): ";
                    cin.ignore(); // Clear the newline from input buffer
                    getline(cin, ingredient_str);
                    vector<Ingredient> ingredients;
                    Recipe newRecipe(name, ingredients, procedure, price); // Pass price to constructor
                    veganRecipeBook.addRecipe(newRecipe);
                    cout << "Recipe added successfully!\n";
                    break;
                }
                case 4:
                {
                    string name, procedure, ingredient_str;
                    double price;
                    cout << "Enter non-vegan recipe name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter procedure: ";
                    getline(cin, procedure);
                    cout << "Enter price: ";
                    cin >> price;
                    cout << "Enter ingredients (name|quantity|unit, separated by commas): ";
                    cin.ignore();
                    getline(cin, ingredient_str);
                    vector<Ingredient> ingredients;
                    Recipe newRecipe(name, ingredients, procedure, price);
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
                    return 0;
                }
            }
        }
        else if (choice == 1)
        {
            // Customer menu
            while (true)
            {
                displayCustomerMenu();
                cout << "Enter your choice: ";
                cin >> customerChoice;
                switch (customerChoice)
                {
                case 1:
                {
                    cout << "Vegan Recipes:\n";
                    veganRecipeBook.displayAllRecipes();
                    cout << "Non-Vegan Recipes:\n";
                    nonVeganRecipeBook.displayAllRecipes();
                    break;
                }
                case 2:
                {
                    cout << "Enter number of dishes to order: ";
                    int num_dishes;
                    cin >> num_dishes;
                    for (int i = 0; i < num_dishes; ++i)
                    {
                        cout << "Enter dish name: ";
                        cin.ignore();
                        getline(cin, recipe_name);
                        cout << "Enter quantity: ";
                        int quantity;
                        cin >> quantity;
                        order[recipe_name] += quantity; // Add quantity to the order
                    }
                    cout << "Order placed successfully!\n";
                    break;
                }
                case 3:
                {
                    cout << "Your Order:\n";
                    double totalAmount = 0.0;
                    for (const auto &item : order)
                    {
                        string dishName = item.first;
                        int quantity = item.second;

                        // Find the price of the dish
                        double price = 0.0;
                        if (Recipe *recipe = user.requestRecipe(veganRecipeBook, dishName))
                        {
                            price = recipe->getPrice();
                        }
                        else if (Recipe *recipe = user.requestRecipe(nonVeganRecipeBook, dishName))
                        {
                            price = recipe->getPrice();
                        }

                        if (price > 0)
                        {
                            cout << "Dish: " << dishName << ", Quantity: " << quantity << ", Price: " << price << ", Total: " << (price * quantity) << "\n";
                            totalAmount += (price * quantity);
                        }
                        else
                        {
                            cout << "Dish: " << dishName << " not found.\n";
                        }
                    }
                    cout << "Total Amount: " << totalAmount << "\n";
                    break;
                }
                case 4:
                {
                    double totalAmount = 0.0;
                    for (const auto &item : order)
                    {
                        string dishName = item.first;
                        int quantity = item.second;

                        // Find the price of the dish
                        double price = 0.0;
                        if (Recipe *recipe = user.requestRecipe(veganRecipeBook, dishName))
                        {
                            price = recipe->getPrice();
                        }
                        else if (Recipe *recipe = user.requestRecipe(nonVeganRecipeBook, dishName))
                        {
                            price = recipe->getPrice();
                        }

                        if (price > 0)
                        {
                            totalAmount += (price * quantity);
                        }
                    }

                    cout << "Total Bill Amount: " << totalAmount << "\n";
                    char confirm;
                    cout << "Do you want to confirm payment? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y')
                    {
                        cout << "Payment successful!\n";
                        order.clear(); // Clear the order after payment
                    }
                    else
                    {
                        cout << "Payment cancelled.\n";
                    }
                    break;
                }
                case 5:
                    cout << "Exiting...\n";
                    return 0;
                default:
                    cout << "Invalid choice, try again!\n";
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid choice.\n0.Chef\n1.Customer....";
        }
    }

    return 0;
}
