#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Order.h"
#include "ReportEntry.h"
#include "Globals.h"

class OrderBook
{

private:

    std::vector<std::vector<std::string>> buyOrder;
    std::vector<std::vector<std::string>> sellOrder;
    // int orderCounter;

public:

    OrderBook();
    void addOrder(Order entry, std::vector<ReportEntry>& ex_report, int priority_num);
    void displayOrders() const;
    void sellCompare(std::vector<std::string> orderRow);
    void buyCompare(std::vector<std::string> orderRow);
    std::string get_order_id();
};
