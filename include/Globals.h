#pragma once

#include <string>
#include <set>
#include <unordered_map>

namespace MyGlobals {

    const std::set<std::string> INSTRUMENTS = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
    enum class SIDES : int {
        BUY = 1,
        SELL = 2
    };
    enum class STATUS : int {
        NEW = 0,
        REJECTED = 1,
        FILL = 2,
        PFILL = 3
    };
    // can add reasons here

    extern int ORDER_ID;
}
