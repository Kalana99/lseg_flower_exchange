#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "Order.h"

class OrderBook
{
private:
    std::vector<std::vector<std::string>> buyOrder;
    std::vector<std::vector<std::string>> sellOrder;
    int orderCounter;

public:
    OrderBook() {}
    void addOrder(Order entry);
    void displayOrders() const;
};

#endif