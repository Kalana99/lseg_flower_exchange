#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class CSVHandler {
    
public:
    CSVHandler(const std::string& filename);

    bool readCSV(std::vector<std::vector<std::string>>& data);
    bool writeCSV(const std::vector<std::vector<std::string>>& data);

private:
    std::string filename;
};
