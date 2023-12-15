#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

#include "CSVHandler.h"
#include "Validator.h"
#include "Constants.h"

using namespace MyConstants;
using namespace std;


int main() {

    // data read ###########################################################

    std::string filename = "orders2.csv";

    CSVHandler csvReader(filename);
    std::vector<std::vector<std::string>> data;

    if (csvReader.readCSV(data)) {

        std::cout << "Data read successfully" << std::endl;

        // for (size_t i = 0; i < data.size(); ++i) {
        //     for (size_t j = 0; j < data[i].size(); ++j) {
        //         std::cout << data[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
    }

    // ####################################################################

    // std::vector<std::vector<std::string>> ex_report;

    for (size_t i = 0; i < data.size(); ++i) {

        Validator validator(data[i]);
        bool is_valid = validator.validate(INSTRUMENTS);

        // std::vector<std::string> report_row = data[i];

        if (!is_valid) {
            
            // add rejected row to report
        }
        else{

            // create order book entry
        }

    }

    return 0;
}
