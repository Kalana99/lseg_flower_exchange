#include "CSVHandler.h"

CSVHandler::CSVHandler(const std::string& filename) : filename(filename) {}

bool CSVHandler::readCSV(std::vector<std::vector<std::string>>& data) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
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

bool CSVHandler::writeCSV(const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return false;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
    return true;
}
