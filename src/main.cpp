#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "CSVHandler.h"
#include "Validator.h"
#include "Globals.h"
#include "Order.h"
#include "ReportEntry.h"

using namespace std;


int MyGlobals::ORDER_ID = 0;

int main() {

    // data read ###########################################################

    std::string filename = "orders2.csv";

    CSVHandler csvReader(filename);
    std::vector<std::vector<std::string>> data;

    if (csvReader.readCSV(data)) {

        std::cout << "Data read successfully" << std::endl;
    }

    // ####################################################################

    // validate and populate order list ####################################

    std::vector<ReportEntry> ex_report = {};
    std::vector<Order> order_lst = {};

    for (size_t i = 0; i < data.size(); ++i) {

        Validator validator(data[i]);
        bool is_valid = validator.validate(MyGlobals::INSTRUMENTS);

        if (!is_valid) {
            
            // add rejected row to report
            ex_report.push_back(ReportEntry(data[i][0], data[i][1], std::stoi(data[i][2]), std::stoi(data[i][3]), std::stod(data[i][4]), static_cast<int>(MyGlobals::STATUS::REJECTED), validator.reason));
            std::cout << "Order rejected" << std::endl;
        }
        else{

            // populate valid order list
            order_lst.push_back(Order(data[i]));
            std::cout << "Order added to valid order list" << std::endl;
        }

    }

    // ####################################################################

    return 0;
}
