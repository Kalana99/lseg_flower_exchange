#pragma once

#include <vector>
#include <string>
#include <set>

class ReportEntry {

public:

    std::string client_order_id;
    std::string order_id;
    std::string instrument;
    std::string side;
    std::string quantity;
    std::string price;
    std::string status;
    std::string reason;
    std::string transaction_time;

    // ReportEntry(std::vector<std::string> row);
    ReportEntry(std::string client_order_id, std::string order_id, std::string instrument, std::string side, std::string quantity, std::string price, std::string status, std::string reason="");

private:

    // void set_order_id();
    void set_transaction_time();

};
