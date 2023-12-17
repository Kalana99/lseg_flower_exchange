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
#include "OrderBook.h"
#include "ExchangeApp.h"

using namespace std;


int MyGlobals::ORDER_ID = 1;

int main() {

    // data read ###########################################################

    std::string filename = "samples/orders0.csv";

    CSVHandler csvReader(filename);
    std::vector<std::vector<std::string>> data;

    if (csvReader.readCSV(data)) {

        std::cout << "Data read successfully" << std::endl;

        // for(size_t i = 0; i < data.size(); ++i){
        //     for(size_t j = 0; j < data[i].size(); ++j){
        //         std::cout << data[i][j] << ", ";
        //     }
        //     std::cout << std::endl;
        // }
    }

    // ####################################################################

    // validate and populate order list ####################################

    ExchangeApp myApp = ExchangeApp();

    for (size_t i = 0; i < data.size(); ++i) {

        bool is_valid = myApp.validator.validate(data[i]);

        if (!is_valid) {
            
            // add rejected row to report
            myApp.ex_report.push_back(ReportEntry(
                data[i][0], 
                "ord" + std::to_string(MyGlobals::ORDER_ID++), 
                data[i][1], 
                data[i][2], 
                data[i][3], 
                data[i][4], 
                std::to_string(static_cast<int>(MyGlobals::STATUS::REJECTED)), 
                myApp.validator.reason
            ));
            std::cout << "Order rejected" << std::endl;
        }
        else{

            // populate valid order list
            myApp.order_lst.push_back(Order(data[i]));
            std::cout << "Order added to valid order list" << std::endl;
        }

    }

    myApp.execute();
    
    // for(size_t i = 0; i < myApp.order_lst.size(); ++i){
    //     std::cout << myApp.order_lst[i].client_order_id << " " << myApp.order_lst[i].instrument << " "  << myApp.order_lst[i].price << " "  << myApp.order_lst[i].quantity << " "  << myApp.order_lst[i].side << " "  << std::endl;
    // }

    for(size_t i = 0; i < myApp.ex_report.size(); ++i){
        std::cout << myApp.ex_report[i].order_id << " " << myApp.ex_report[i].client_order_id << " "  << myApp.ex_report[i].instrument << " "  << myApp.ex_report[i].side << " "  << myApp.ex_report[i].status << " "  << myApp.ex_report[i].quantity << " "  << myApp.ex_report[i].price << " " << myApp.ex_report[i].reason << " "  << myApp.ex_report[i].transaction_time << " "    << std::endl;
    }

    // std::cout << myApp.ex_report.size() << std::endl;

    // ####################################################################

    return 0;
}
