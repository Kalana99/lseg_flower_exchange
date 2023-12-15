#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Order.h"
#include "OrderBook.h"
#include "ReportEntry.h"

class ExchangeApp {

public:

    std::vector<ReportEntry> ex_report;
    std::vector<Order> order_lst;
    std::unordered_map<std::string, OrderBook> order_book_list;

    ExchangeApp();
    void execute();
};
