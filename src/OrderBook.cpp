#include "OrderBook.h"

#include <iostream>

OrderBook::OrderBook() {}

void OrderBook::addOrder(Order entry, int priority_num)
{

    std::string orderId = "ord" + std::to_string(orderCounter++);
    std::vector<std::string> orderRow = {orderId, std::to_string(entry.quantity), std::to_string(entry.price), std::to_string(priority_num)};

    if (static_cast<int>(entry.side) == static_cast<int>(MyGlobals::SIDES::SELL)) // sell order
    {
        if (entry.price <= std::stoi(this->buyOrder[0][2]))
        {
            if (entry.quantity <= std::stoi(this->buyOrder[0][1]))
            {
                return; // there' already a buyer for the selling product
            }
            else
            {
                int tempQty = entry.quantity - std::stoi(this->buyOrder[0][1]);
                entry.quantity = tempQty;
            }
        }
        sellCompare(orderRow);
    }
    else if (static_cast<int>(entry.side) == static_cast<int>(MyGlobals::SIDES::BUY)) // buy order
    {
        if (entry.price >= std::stoi(this->sellOrder[0][2]))
        {
            if (entry.quantity <= std::stoi(this->sellOrder[0][1]))
            {
                return; // there' already a seller for the buying product
            }
            else
            {
                int tempQty = entry.quantity - std::stoi(this->sellOrder[0][1]);
                entry.quantity = tempQty;
            }
        }
        buyCompare(orderRow);
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