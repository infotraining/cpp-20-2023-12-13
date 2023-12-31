module;

#include <iostream>
#include <vector>

module EShop;

void print(const Order& order)
{
    std::cout << "Order{count: " << order.count 
              << ", name: " << order.name
              << ", price: " << order.price << "$}\n";
}

void Customer::print() const
{
    std::cout << name_ << ":\n";

    for(const auto& order : orders_)
    {
        std::cout << order.count
            << " - " << order.name
            << " - " << order.price << "$\n";
    }

    std::cout << "------------------------\n"; 
    std::cout << "Total price: " << total_price() << "\n";
}

