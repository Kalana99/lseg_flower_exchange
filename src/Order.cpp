#include "Order.h"

Order::Order(std::vector<std::string> row) {
    
    client_order_id = row[0];
    instrument = row[1];
    side = std::stoi(row[2]);
    quantity = std::stoi(row[3]);
    price = std::stod(row[4]);
}

Order::Order(std::string client_order_id, std::string instrument, int side, int quantity, double price) {
    
    this->client_order_id = client_order_id;
    this->instrument = instrument;
    this->side = side;
    this->quantity = quantity;
    this->price = price;
}
