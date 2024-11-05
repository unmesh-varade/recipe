#ifndef ORDER_H
#define ORDER_H

#include "Recipe.h"
#include <vector>
#include <string>
#include <iostream>

class Order
{
private:
    vector<Recipe> dishes; // Dishes ordered
    double totalPrice;     // Total price of the order

public:
    Order(const vector<Recipe> &dishes) : dishes(dishes), totalPrice(0) {}

    // Function to calculate the total price of the order
    void calculateTotalPrice()
    {
        totalPrice = 0;
        for (const auto &dish : dishes)
        {
            // Assuming each recipe has a price attribute
            totalPrice += dish.getPrice(); // You need to implement getPrice() in the Recipe class
        }
    }

    // Function to display order details
    void displayOrder() const
    {
        std::cout << "Order Details:\n";
        for (const auto &dish : dishes)
        {
            std::cout << dish.name << " - " << dish.getPrice() << "\n";
        }
        std::cout << "Total Price: " << totalPrice << "\n";
    }

    double getTotalPrice() const
    {
        return totalPrice;
    }
};

#endif
