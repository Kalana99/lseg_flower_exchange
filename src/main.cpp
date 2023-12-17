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

int main()
{
    std::string filename = "samples/orders5.csv";

    CSVHandler csvReader(filename);
    std::vector<std::vector<std::string>> data;

    if (csvReader.readCSV(data))
    {

        std::cout << "Data read successfully" << std::endl;
    }

    ExchangeApp myApp = ExchangeApp();

    for (size_t i = 0; i < data.size(); ++i)
    {

        bool is_valid = myApp.validator.validate(data[i]);

        if (!is_valid)
        {

            // add rejected row to report
            myApp.ex_report.push_back(ReportEntry(
                data[i][0],
                "ord" + std::to_string(MyGlobals::ORDER_ID++),
                data[i][1],
                data[i][2],
                data[i][3],
                data[i][4],
                std::to_string(static_cast<int>(MyGlobals::STATUS::REJECTED)),
                myApp.validator.reason));
            std::cout << "Order rejected" << std::endl;
        }
        else
        {
            myApp.order_lst.push_back(Order(data[i]));
            std::cout << "Order added to valid order list" << std::endl;
        }
    }

    myApp.execute();

    std::vector<std::vector<std::string>> ex_report_data;
    for (const auto &entry : myApp.ex_report)
    {
        std::vector<std::string> entry_data = {
            entry.client_order_id,
            entry.order_id,
            entry.instrument,
            entry.side,
            entry.quantity,
            entry.price,
            entry.status,
            entry.reason};
        ex_report_data.push_back(entry_data);
    }

    CSVHandler csvHandler("output.csv");
    csvHandler.writeCSV(myApp.ex_report);

    return 0;
}
