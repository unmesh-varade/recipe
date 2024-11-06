#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Order.h"
#include <vector>
#include <string>
#include <iostream>

class Customer : public User
{
public:
    Customer(string n) : User(n) {}
    int a;
    // Function to place an order
    Order placeOrder(const vector<Recipe> &dishes)
    {
        Order order(dishes);
        order.calculateTotalPrice();
        return order;
    }
};

#endif
