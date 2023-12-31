#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "ReportEntry.h"
#include "Globals.h"

// ReportEntry::ReportEntry(std::vector<std::string> row) {
    
//     client_order_id = row[0];
//     instrument = row[1];
//     side = std::stoi(row[2]);
//     quantity = std::stoi(row[3]);
//     price = std::stod(row[4]);
//     status = std::stoi(row[5]);
//     reason = (row.size() == 8) ? row[6] : "";
//     set_order_id();
//     set_transaction_time();
// }

ReportEntry::ReportEntry(std::string client_order_id, std::string order_id, std::string instrument, std::string side, std::string quantity, std::string price, std::string status) {
    
    this->client_order_id = client_order_id;
    this->order_id = order_id;
    this->instrument = instrument;
    this->side = side;
    this->quantity = quantity;
    this->price = price;
    this->status = status;
    this->reason = "";
    set_transaction_time();
}

ReportEntry::ReportEntry(std::string client_order_id, std::string order_id, std::string instrument, std::string side, std::string quantity, std::string price, std::string status, std::string reason="") {
    
    this->client_order_id = client_order_id;
    this->order_id = order_id;
    this->instrument = instrument;
    this->side = side;
    this->quantity = quantity;
    this->price = price;
    this->status = status;
    this->reason = reason;
    set_transaction_time();
}

// void ReportEntry::set_order_id() {
    
//     order_id = "ord" + std::to_string(MyGlobals::ORDER_ID);
//     MyGlobals::ORDER_ID++;
// }

void ReportEntry::set_transaction_time() {
    
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
    std::tm* localTime = std::localtime(&currentTime_t);

    auto duration = currentTime.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;

    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y%m%d-%H%M%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();

    transaction_time = oss.str();
}
