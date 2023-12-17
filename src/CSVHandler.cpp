#include "CSVHandler.h"


CSVHandler::CSVHandler(const std::string& filename) : filename(filename) {}

bool CSVHandler::readCSV(std::vector<std::vector<std::string>>& data) {

    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int line_count = 0;

    while (std::getline(file, line)) {

        if (line_count == 0)
        {
            line_count++;
            continue;
        }

        std::vector<std::string> row;
        size_t pos = 0;
        std::string token;
        
        while ((pos = line.find(',')) != std::string::npos) {

            token = line.substr(0, pos);
            row.push_back(token);
            line.erase(0, pos + 1);
        }
        
        row.push_back(line);
        data.push_back(row);
    }

    file.close();
    return true;
}

bool CSVHandler::writeCSV(const std::vector<ReportEntry>& data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return false;
    }

    file << "client_order_id,order_id,instrument,side,quantity,price,status,reason\n";

    for (const auto& entry : data) {
        file << entry.client_order_id << ","
             << entry.order_id << ","
             << entry.instrument << ","
             << entry.side << ","
             << entry.quantity << ","
             << entry.price << ","
             << entry.status << ","
             << entry.reason << "\n";
    }

    file.close();
    return true;
}
