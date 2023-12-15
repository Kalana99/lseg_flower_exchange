#pragma once

#include <vector>
#include <string>
#include <set>

class Validator {

public:

    std::vector<std::string> row;
    std::string reason;

    Validator(std::vector<std::string> row);
    bool validate(std::set<std::string> INSTRUMENTS);

private:

    bool validate_non_empty(std::vector<std::string> row);
    bool validate_instrument(std::set<std::string> INSTRUMENTS, const std::string& instrument);
    bool validate_side(int side);
    bool validate_quantity(int quantity);
    bool validate_price(double price);
};
