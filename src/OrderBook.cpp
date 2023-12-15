#include "OrderBook.h"

#include <iostream>

OrderBook::OrderBook() {}

void OrderBook::addOrder(Order entry)
{

    if (entry.side == 1)
    {
        
    }
    else
    {
    }
    std::string orderId = "ord" + std::to_string(orderCounter++);
    std::vector<std::string> orderRow = {orderId, std::to_string(qty), std::to_string(price)};
    buyOrder.push_back(orderRow);
}

void OrderBook::displayOrders() const
{
    std::cout << "Order ID\tQty\tPrice\n";
    for (const auto &order : buyOrder)
    {
        for (const auto &value : order)
        {
            std::cout << value << '\t';
        }
        std::cout << '\n';
    }
}