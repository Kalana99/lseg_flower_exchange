#ifndef REPORTENTRY_H
#define REPORTENTRY_H

#include <vector>
#include <string>
#include <set>

class ReportEntry {

public:

    std::string client_order_id;
    std::string order_id;
    std::string instrument;
    int side;
    int quantity;
    double price;
    std::string reason;

    ReportEntry(std::vector<std::string> row);
    // ReportEntry(std::string client_order_id, std::string instrument, int side, int quantity, double price, std::string reason);

};

#endif