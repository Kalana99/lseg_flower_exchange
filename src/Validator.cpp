#include "Validator.h"
#include "Globals.h"

Validator::Validator() : reason("empty") {}

bool Validator:: validate(std::vector<std::string> row) {

    if (row[1].empty() || !validate_instrument(MyGlobals::INSTRUMENTS, row[1])) {
        reason = "Invalid instrument";
        return false;
    }

    if (row[2].empty() || !validate_side(std::stoi(row[2]))) {
        reason = "Invalid side";
        return false;
    }

    if (row[3].empty() || !validate_quantity(std::stoi(row[3]))) {
        reason = "Invalid quantity";
        return false;
    }

    if (row[4].empty() || !validate_price(std::stod(row[4]))) {
        reason = "Invalid price";
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

    if (side == static_cast<int>(MyGlobals::SIDES::BUY) || side == static_cast<int>(MyGlobals::SIDES::SELL)) {
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
