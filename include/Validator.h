#pragma once

#include <vector>
#include <string>
#include <set>

class Validator {

public:

    std::string reason;

    Validator();
    bool validate(std::vector<std::string> row);

private:

    bool validate_instrument(std::set<std::string> INSTRUMENTS, const std::string& instrument);
    bool validate_side(int side);
    bool validate_quantity(int quantity);
    bool validate_price(double price);
};
