#include "OrderBook.h"

#include <iostream>

OrderBook::OrderBook() {}

void OrderBook::addOrder(Order entry, int priority_num)
{

    std::string orderId = "ord" + std::to_string(orderCounter++);
    std::vector<std::string> orderRow = {orderId, std::to_string(entry.quantity), std::to_string(entry.price), std::to_string(priority_num)};

    if (entry.side == 2) // sell order
    {
        sellCompare(orderRow);
        sellOrder.push_back(orderRow);
    }
    else if (entry.side == 1) // buy order
    {
        buyCompare(orderRow);
        buyOrder.push_back(orderRow);
    }
}

void OrderBook::buyCompare(std::vector<std::string> orderRow)
{
    int count = 0;
    for (const auto &orderRowVec : this->buyOrder)
    {
        if (orderRow[2] > orderRowVec[2])
        {
            auto position = buyOrder.begin() + count;
            buyOrder.insert(position, orderRow);
            break;
        }

        count++;
    }
}

void OrderBook::sellCompare(std::vector<std::string> orderRow)
{
    int count = 0;
    for (const auto &orderRowVec : this->sellOrder)
    {
        if (orderRow[2] < orderRowVec[2])
        {
            auto position = buyOrder.begin() + count;
            buyOrder.insert(position, orderRow);
            break;
        }

        count++;
    }
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