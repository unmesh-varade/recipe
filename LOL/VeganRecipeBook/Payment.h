#ifndef PAYMENT_H
#define PAYMENT_H

#include "Recipe.h"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Payment {
private:
    vector<Recipe> orderedItems; // List of ordered recipes

public:
    Payment(const vector<Recipe> &items) : orderedItems(items) {}

    double calculateTotal() const {
        double total = 0.0;
        for (const auto &item : orderedItems) {
            total += item.getPrice(); // Sum up the prices of ordered items
        }
        return total;
    }

    void displayOrderSummary() const {
        cout << "Ordered Items:\n";
        for (const auto &item : orderedItems) {
            cout << item.name << " - $" << fixed << setprecision(2) << item.getPrice() << "\n"; // Display each item with price
        }
        cout << "Total Amount: $" << fixed << setprecision(2) << calculateTotal() << "\n";
    }

    void confirmPayment() {
        char choice;
        cout << "Confirm payment? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "Payment confirmed. Thank you for your order!\n";
            // Proceed with payment processing logic here
        } else {
            cout << "Payment cancelled.\n";
        }
    }
};

#endif
