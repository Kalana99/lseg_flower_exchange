#include "Validator.h"

Validator::Validator(std::vector<std::string> row) : row(row), reason("empty") {}

bool Validator:: validate(std::set<std::string> INSTRUMENTS) {

    if (!validate_non_empty(row)) {
        reason = "One or more fields are empty";
        return false;
    }

    if (!validate_instrument(INSTRUMENTS, row[1])) {
        reason = "Invalid instrument";
        return false;
    }

    if (!validate_side(std::stoi(row[2]))) {
        reason = "Invalid side";
        return false;
    }

    if (!validate_quantity(std::stoi(row[3]))) {
        reason = "Invalid quantity";
        return false;
    }

    if (!validate_price(std::stod(row[4]))) {
        reason = "Invalid price";
        return false;
    }

    return true;
}

// validate non empty function
bool Validator:: validate_non_empty(std::vector<std::string> row) {

    if (row.size() != 5) {
        return false;
    }
    return true;
}

// validate instrument function
bool Validator:: validate_instrument(std::set<std::string> INSTRUMENTS, const std::string& instrument) {

    if (INSTRUMENTS.count(instrument) > 0) {
        return true;
    }
    return false;
}  

// validate side function
bool Validator:: validate_side(int side) {

    if (side == 1 || side == 2) {
        return true;
    }
    return false;
}

// validate quantity function
bool Validator:: validate_quantity(int quantity) {

    if (quantity < 10 || quantity > 1000 || quantity % 10 != 0) {
        return false;
    }
    return true;
}

// validate price function
bool Validator:: validate_price(double price) {

    if (price > 0) {
        return true;
    }
    return false;
}
