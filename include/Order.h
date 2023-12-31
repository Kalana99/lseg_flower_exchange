#pragma once

#include <vector>
#include <string>
#include <set>

class Order {

public:

    std::string client_order_id;
    std::string instrument;
    int side;
    int quantity;
    double price;

    Order(std::vector<std::string> row);
    Order(std::string client_order_id, std::string instrument, int side, int quantity, double price);

};
