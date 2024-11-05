#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "RecipeBook.h"
#include "ShoppingList.h"
#include <fstream>
#include <sstream>
#include <iostream>

class FileHandler
{
public:
    static vector<Recipe> loadRecipes(const string &filename)
    {
        vector<Recipe> recipes;
        ifstream file(filename);
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, ingredients_str, procedure, price_str;

            getline(ss, name, ';');
            getline(ss, ingredients_str, ';');
            getline(ss, procedure, ';');
            getline(ss, price_str);

            vector<Ingredient> ingredients;
            stringstream ss_ing(ingredients_str);
            string ing;

            while (getline(ss_ing, ing, ','))
            {
                stringstream ss_detail(ing);
                string ing_name, quantity_str, unit;

                getline(ss_detail, ing_name, '|');
                getline(ss_detail >> ws, quantity_str, '|');
                getline(ss_detail >> ws, unit);

                try
                {
                    double quantity = stod(quantity_str);
                    ingredients.emplace_back(ing_name, quantity, unit);
                }
                catch (const std::invalid_argument &e)
                {
                    cerr << "Invalid quantity for ingredient: " << ing_name << " in recipe: " << name << endl;
                    continue;
                }
                catch (const std::out_of_range &e)
                {
                    cerr << "Quantity out of range for ingredient: " << ing_name << " in recipe: " << name << endl;
                    continue;
                }
            }

            // Convert price string to double
            double price = 0.0;
            try
            {
                price = stod(price_str);
            }
            catch (const std::invalid_argument &e)
            {
                cerr << "Invalid price for recipe: " << name << endl;
                continue;
            }
            catch (const std::out_of_range &e)
            {
                cerr << "Price out of range for recipe: " << name << endl;
                continue;
            }

            recipes.emplace_back(name, ingredients, procedure, price); // Include price
        }
        return recipes;
    }

    static void saveShoppingList(const ShoppingList &shoppingList, const string &filename)
    {
        ofstream file(filename);
        file << shoppingList;
    }

    static void saveRecipes(const RecipeBook &recipeBook, const string &filename)
    {
        ofstream file(filename);
        for (const auto &pair : recipeBook.getRecipes())
        {
            file << pair.first << ";";
            for (const auto &ing : pair.second.ingredients)
            {
                file << ing.name << "|" << ing.quantity << "|" << ing.unit << ",";
            }
            file << ";" << pair.second.procedure << ";" << fixed << setprecision(2) << pair.second.getPrice() << "\n"; // Write the price
        }
    }
};

#endif
