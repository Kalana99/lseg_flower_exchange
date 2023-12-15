#include "ReportEntry.h"

ReportEntry::ReportEntry(std::vector<std::string> row) {
    
    client_order_id = row[0];
    order_id = row[1];
    instrument = row[2];
    side = std::stoi(row[3]);
    quantity = std::stoi(row[4]);
    price = std::stod(row[5]);
    reason = row[6];
}

ReportEntry::ReportEntry(std::string client_order_id, std::string instrument, int side, int quantity, double price, std::string reason) {
    
    this->client_order_id = client_order_id;
    this->instrument = instrument;
    this->side = side;
    this->quantity = quantity;
    this->price = price;
    this->reason = reason;
}