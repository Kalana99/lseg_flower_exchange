#include "OrderBook.h"

#include <iostream>

// quty being equal is a separate case
// always assign the price of the one in the order book

OrderBook::OrderBook() {}

void OrderBook::addOrder(Order entry, std::vector<ReportEntry>& ex_report, int priority_num)
{
    
    std::vector<std::string> orderRow;

    if (static_cast<int>(entry.side) == static_cast<int>(MyGlobals::SIDES::SELL)) // sell order
    {
        if (this->buyOrder.size() > 0 && entry.price <= std::stoi(this->buyOrder[0][2]))
        {
            if (entry.quantity < std::stoi(this->buyOrder[0][1]))
            {
                // no orderbook record - add both entries to report (fill and pfill)

                //order book update on the buy column
                
                ex_report.push_back(ReportEntry(
                    entry.client_order_id, 
                    get_order_id(), 
                    entry.instrument, 
                    std::to_string(entry.side), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                ));

                ex_report.push_back(ReportEntry(
                    this->buyOrder[0].back(), 
                    this->buyOrder[0][0], 
                    entry.instrument, 
                    std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))
                ));
            }
            else if(entry.quantity == std::stoi(this->buyOrder[0][1]))
            {
                // remove orderbook record and add both entries to report (fill)

                ex_report.push_back(ReportEntry(
                    entry.client_order_id, 
                    get_order_id(), 
                    entry.instrument, 
                    std::to_string(entry.side), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                ));

                ex_report.push_back(ReportEntry(
                    this->buyOrder[0].back(), 
                    this->buyOrder[0][0], 
                    entry.instrument, 
                    std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                ));

                this->buyOrder.erase(this->buyOrder.begin());
            }
            else
            {
                // order book entry and both report entry (fill and pfill)

                // int tempQty = entry.quantity - std::stoi(this->buyOrder[0][1]);
                // entry.quantity = tempQty;

                int temp_qty = entry.quantity;
                int index = 0;

                while (temp_qty > 0 || buyOrder.size() > 0)
                {
                    if (entry.price <= std::stoi(buyOrder[index][2]))
                    {
                        if (std::stoi(buyOrder[index][1]) <= temp_qty)
                        {
                            // buy order book entry remove
                            // buy report entry fill
                            // sell report entry pfill
                            // update temp qty

                            ex_report.push_back(ReportEntry(
                                entry.client_order_id, 
                                get_order_id(), 
                                entry.instrument, 
                                std::to_string(entry.side), 
                                std::to_string(entry.quantity),
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))
                            ));

                            ex_report.push_back(ReportEntry(
                                this->buyOrder[0].back(), 
                                this->buyOrder[0][0], 
                                entry.instrument, 
                                std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)), 
                                std::to_string(entry.quantity),
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                            ));

                            temp_qty -= std::stoi(buyOrder[0][1]);
                            this->buyOrder.erase(this->buyOrder.begin());
                        }
                        else
                        {
                            // buy order book entry update
                            // buy report entry pfill
                            // sell report entry fill
                            // temp qty = 0

                            ex_report.push_back(ReportEntry(
                                entry.client_order_id, 
                                get_order_id(), 
                                entry.instrument, 
                                std::to_string(entry.side), 
                                buyOrder[0][1], 
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                            ));

                            ex_report.push_back(ReportEntry(
                                this->buyOrder[0].back(), 
                                this->buyOrder[0][0], 
                                entry.instrument, 
                                std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)), 
                                buyOrder[0][1], 
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))
                            ));

                            this->buyOrder[0][1] = std::to_string(std::stoi(buyOrder[0][1]) - temp_qty);
                            temp_qty = 0;
                        }
                        
                    }
                    else
                    {
                        break;
                    }
                }
                
                // temp qty > 0 add sell order book entry
                orderRow = {
                    get_order_id(), 
                    std::to_string(temp_qty), 
                    std::to_string(entry.price), 
                    std::to_string(priority_num),  
                    entry.client_order_id
                };
                sellCompare(orderRow);
            }
        }
        else
        {
            // new report entry

            ex_report.push_back(ReportEntry(
                entry.client_order_id, 
                get_order_id(), 
                entry.instrument, 
                std::to_string(entry.side), 
                std::to_string(entry.quantity), 
                std::to_string(entry.price), 
                std::to_string(static_cast<int>(MyGlobals::STATUS::NEW))
            ));

            orderRow = {
                get_order_id(), 
                std::to_string(entry.quantity), 
                std::to_string(entry.price), 
                std::to_string(priority_num),  
                entry.client_order_id
            };
            sellCompare(orderRow);
        }
    }
    else if (static_cast<int>(entry.side) == static_cast<int>(MyGlobals::SIDES::BUY)) // buy order - add to buy order book
    {
        if (this->sellOrder.size() > 0 && entry.price >= std::stoi(this->sellOrder[0][2]))
        {
            if (entry.quantity < std::stoi(this->sellOrder[0][1]))
            {
                ex_report.push_back(ReportEntry(
                    entry.client_order_id, 
                    get_order_id(), 
                    entry.instrument, 
                    std::to_string(entry.side), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                ));

                ex_report.push_back(ReportEntry(
                    this->sellOrder[0].back(), 
                    this->sellOrder[0][0], 
                    entry.instrument, 
                    std::to_string(static_cast<int>(MyGlobals::SIDES::SELL)), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))
                ));
            }
            else if (entry.quantity = std::stoi(this->sellOrder[0][1]))
            {
                ex_report.push_back(ReportEntry(
                    entry.client_order_id, 
                    get_order_id(), 
                    entry.instrument, 
                    std::to_string(entry.side), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                ));

                ex_report.push_back(ReportEntry(
                    this->sellOrder[0].back(), 
                    this->sellOrder[0][0], 
                    entry.instrument, 
                    std::to_string(static_cast<int>(MyGlobals::SIDES::SELL)), 
                    std::to_string(entry.quantity), 
                    std::to_string(entry.price), 
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                ));

                this->sellOrder.erase(this->sellOrder.begin());
            }
            else
            {
                //int tempQty = entry.quantity - std::stoi(this->sellOrder[0][1]);
                int temp_qty = entry.quantity;
                int index = 0;

                while (temp_qty > 0 || sellOrder.size() > 0)
                {
                    if (entry.price >= std::stoi(sellOrder[0][2]))
                    {
                        if (std::stoi(sellOrder[index][1]) <= temp_qty)
                        {
                            // buy order book entry remove
                            // buy report entry fill
                            // sell report entry pfill
                            // update temp qty

                            ex_report.push_back(ReportEntry(
                                entry.client_order_id, 
                                get_order_id(), 
                                entry.instrument, 
                                std::to_string(entry.side), 
                                std::to_string(entry.quantity),
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))
                            ));

                            ex_report.push_back(ReportEntry(
                                this->buyOrder[0].back(), 
                                this->buyOrder[0][0], 
                                entry.instrument, 
                                std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)), 
                                std::to_string(entry.quantity),
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                            ));

                            temp_qty -= std::stoi(buyOrder[0][1]);
                            this->buyOrder.erase(this->buyOrder.begin());
                        }
                        else
                        {
                            // buy order book entry update
                            // buy report entry pfill
                            // sell report entry fill
                            // temp qty = 0

                            ex_report.push_back(ReportEntry(
                                entry.client_order_id, 
                                get_order_id(), 
                                entry.instrument, 
                                std::to_string(entry.side), 
                                buyOrder[0][1], 
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))
                            ));

                            ex_report.push_back(ReportEntry(
                                this->buyOrder[0].back(), 
                                this->buyOrder[0][0], 
                                entry.instrument, 
                                std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)), 
                                buyOrder[0][1], 
                                std::to_string(entry.price), 
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))
                            ));

                            this->buyOrder[0][1] = std::to_string(std::stoi(buyOrder[0][1]) - temp_qty);
                            temp_qty = 0;
                        }
                        
                    }
                    else
                    {
                        break;
                    }
                }

            }
        }

        buyCompare(orderRow);
    }
}

void OrderBook::buyCompare(std::vector<std::string> orderRow)
{
    int count = 0;
    for (const auto &orderRowVec : this->buyOrder)
    {
        if (orderRow[2] > orderRowVec[2])
        {
            auto position = buyOrder.begin() + count;
            buyOrder.insert(position, orderRow);
            break;
        }

        count++;
    }
}

void OrderBook::sellCompare(std::vector<std::string> orderRow)
{
    int count = 0;
    for (const auto &orderRowVec : this->sellOrder)
    {
        if (orderRow[2] < orderRowVec[2])
        {
            auto position = buyOrder.begin() + count;
            buyOrder.insert(position, orderRow);
            break;
        }

        count++;
    }
}

void OrderBook::displayOrders() const
{
    std::cout << "Order ID\tQty\tPrice\n";
    for (const auto &order : buyOrder)
    {
        for (const auto &value : order)
        {
            std::cout << value << '\t';
        }
        std::cout << '\n';
    }
}

std::string OrderBook::get_order_id(){

    std::string orderId = "ord" + std::to_string(MyGlobals::ORDER_ID++);
    return orderId;
}
