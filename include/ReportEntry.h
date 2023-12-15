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
    int status;
    std::string reason;
    std::string transaction_time;

    ReportEntry(std::vector<std::string> row);
    ReportEntry(std::string client_order_id, std::string instrument, int side, int quantity, double price, int status, std::string reason);

private:

    void set_order_id();
    void set_transaction_time();

};

#endif