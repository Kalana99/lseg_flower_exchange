#include "ExchangeApp.h"

ExchangeApp::ExchangeApp(){

    this->ex_report = {};
    this->order_lst = {};
    this->order_book_list = {
        {"Rose", OrderBook()},
        {"Lavender", OrderBook()},
        {"Lotus", OrderBook()},
        {"Tulip", OrderBook()},
        {"Orchid", OrderBook()},
    };
}

void ExchangeApp::execute(){

    for(size_t i = 0; i < order_lst.size(); ++i){

        order_book_list[order_lst[i].instrument].addOrder(order_lst[i], ex_report, i);
    }
}
