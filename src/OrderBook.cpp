#include "OrderBook.h"

#include <iostream>

// quty being equal is a separate case
// always assign the price of the one in the order book

OrderBook::OrderBook() {}

void OrderBook::addOrder(Order entry, std::vector<ReportEntry> &ex_report, int priority_num)
{

    std::vector<std::string> orderRow;
    std::string orderId = get_order_id();

    if (static_cast<int>(entry.side) == static_cast<int>(MyGlobals::SIDES::SELL)) // sell order
    {
        if (this->buyOrder.size() > 0 && entry.price <= std::stoi(this->buyOrder[0][2]))
        {
            if (entry.quantity < std::stoi(this->buyOrder[0][1]))
            {
                // no orderbook record - add both entries to report (fill and pfill)
                ex_report.push_back(ReportEntry(
                    entry.client_order_id,
                    orderId,
                    entry.instrument,
                    std::to_string(entry.side),
                    std::to_string(entry.quantity),
                    this->buyOrder[0][2],
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                ex_report.push_back(ReportEntry(
                    this->buyOrder[0].back(),
                    orderId,
                    entry.instrument,
                    std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)),
                    std::to_string(entry.quantity),
                    this->buyOrder[0][2],
                    std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))));

                this->buyOrder[0][1] = std::to_string(std::stoi(this->buyOrder[0][1]) -  entry.quantity);
            }
            else if (entry.quantity == std::stoi(this->buyOrder[0][1]))
            {
                // remove orderbook record and add both entries to report (fill)

                ex_report.push_back(ReportEntry(
                    entry.client_order_id,
                    orderId,
                    entry.instrument,
                    std::to_string(entry.side),
                    std::to_string(entry.quantity),
                    this->buyOrder[0][2],
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                ex_report.push_back(ReportEntry(
                    this->buyOrder[0].back(),
                    orderId,
                    entry.instrument,
                    std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)),
                    std::to_string(entry.quantity),
                    this->buyOrder[0][2],
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                this->buyOrder.erase(this->buyOrder.begin());
            }
            else
            {   
                // order book entry and both report entry (fill and pfill)

                // int tempQty = entry.quantity - std::stoi(this->buyOrder[0][1]);
                // entry.quantity = tempQty;

                int temp_qty = entry.quantity;
                int index = 0;

                while (temp_qty > 0 && buyOrder.size() > 0)
                {   
                    if (entry.price <= std::stoi(buyOrder[0][2]))
                    {
                        if (std::stoi(buyOrder[0][1]) <= temp_qty)
                        {
                            // buy order book entry remove
                            // buy report entry fill
                            // sell report entry pfill
                            // update temp qty

                            ex_report.push_back(ReportEntry(
                                entry.client_order_id,
                                orderId,
                                entry.instrument,
                                std::to_string(entry.side),
                                this->buyOrder[0][1],
                                this->buyOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))));

                            ex_report.push_back(ReportEntry(
                                this->buyOrder[0].back(),
                                orderId,
                                entry.instrument,
                                std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)),
                                this->buyOrder[0][1],
                                this->buyOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

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
                                orderId,
                                entry.instrument,
                                std::to_string(entry.side),
                                std::to_string(temp_qty),
                                this->buyOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                            ex_report.push_back(ReportEntry(
                                this->buyOrder[0].back(),
                                orderId,
                                entry.instrument,
                                std::to_string(static_cast<int>(MyGlobals::SIDES::BUY)),
                                std::to_string(temp_qty),
                                this->buyOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))));

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
                    orderId,
                    std::to_string(temp_qty),
                    std::to_string(entry.price),
                    std::to_string(priority_num),
                    entry.client_order_id};
                sellCompare(orderRow);
            }
        }
        else
        {
            // new report entry

            ex_report.push_back(ReportEntry(
                entry.client_order_id,
                orderId,
                entry.instrument,
                std::to_string(entry.side),
                std::to_string(entry.quantity),
                std::to_string(entry.price),
                std::to_string(static_cast<int>(MyGlobals::STATUS::NEW))));

            orderRow = {
                orderId,
                std::to_string(entry.quantity),
                std::to_string(entry.price),
                std::to_string(priority_num),
                entry.client_order_id};

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
                    orderId,
                    entry.instrument,
                    std::to_string(entry.side),
                    std::to_string(entry.quantity),
                    std::to_string(entry.price),
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                ex_report.push_back(ReportEntry(
                    this->sellOrder[0].back(),
                    orderId,
                    entry.instrument,
                    std::to_string(static_cast<int>(MyGlobals::SIDES::SELL)),
                    std::to_string(entry.quantity),
                    std::to_string(entry.price),
                    std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))));
            }
            else if (entry.quantity == std::stoi(this->sellOrder[0][1]))
            {   
                ex_report.push_back(ReportEntry(
                    entry.client_order_id,
                    orderId,
                    entry.instrument,
                    std::to_string(entry.side),
                    std::to_string(entry.quantity),
                    this->sellOrder[0][2],
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                ex_report.push_back(ReportEntry(
                    this->sellOrder[0].back(),
                    orderId,
                    entry.instrument,
                    std::to_string(static_cast<int>(MyGlobals::SIDES::SELL)),
                    std::to_string(entry.quantity),
                    this->sellOrder[0][2],
                    std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                this->sellOrder.erase(this->sellOrder.begin());
            }
            else
            {   
                // int tempQty = entry.quantity - std::stoi(this->sellOrder[0][1]);
                int temp_qty = entry.quantity;
                int index = 0;
                
                while (temp_qty > 0 && sellOrder.size() > 0)
                {
                    if (entry.price >= std::stoi(sellOrder[0][2]))
                    {
                        if (std::stoi(sellOrder[0][1]) <= temp_qty)
                        {
                            // buy order book entry remove
                            // buy report entry fill
                            // sell report entry pfill
                            // update temp qty

                            ex_report.push_back(ReportEntry(
                                entry.client_order_id,
                                orderId,
                                entry.instrument,
                                std::to_string(entry.side),
                                this->sellOrder[0][1],
                                this->sellOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))));

                            ex_report.push_back(ReportEntry(
                                this->sellOrder[0].back(),
                                orderId,
                                entry.instrument,
                                std::to_string(static_cast<int>(MyGlobals::SIDES::SELL)),
                                this->sellOrder[0][1],
                                this->sellOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                            temp_qty -= std::stoi(sellOrder[0][1]);
                            this->sellOrder.erase(this->sellOrder.begin());
                        }
                        else
                        {
                            // buy order book entry update
                            // buy report entry pfill
                            // sell report entry fill
                            // temp qty = 0

                            ex_report.push_back(ReportEntry(
                                entry.client_order_id,
                                orderId,
                                entry.instrument,
                                std::to_string(entry.side),
                                std::to_string(temp_qty),
                                this->sellOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::FILL))));

                            ex_report.push_back(ReportEntry(
                                this->sellOrder[0].back(),
                                orderId,
                                entry.instrument,
                                std::to_string(static_cast<int>(MyGlobals::SIDES::SELL)),
                                std::to_string(temp_qty),
                                this->sellOrder[0][2],
                                std::to_string(static_cast<int>(MyGlobals::STATUS::PFILL))));

                            this->sellOrder[0][1] = std::to_string(std::stoi(sellOrder[0][1]) - temp_qty);
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
                    orderId,
                    std::to_string(temp_qty),
                    this->sellOrder[0][2],
                    std::to_string(priority_num),
                    entry.client_order_id};
                buyCompare(orderRow);
            }
        }
        else
        {
            ex_report.push_back(ReportEntry(
                entry.client_order_id,
                orderId,
                entry.instrument,
                std::to_string(entry.side),
                std::to_string(entry.quantity),
                std::to_string(entry.price),
                std::to_string(static_cast<int>(MyGlobals::STATUS::NEW))));

            orderRow = {
                orderId,
                std::to_string(entry.quantity),
                std::to_string(entry.price),
                std::to_string(priority_num),
                entry.client_order_id};
            buyCompare(orderRow);
        }
    }
}

void OrderBook::buyCompare(std::vector<std::string> orderRow)
{   
    if(this->buyOrder.size() == 0){
        this->buyOrder.push_back(orderRow);
        return;
    }

    int count = 0;
    for (const auto &orderRowVec : this->buyOrder)
    {
        if (std::stod(orderRow[2]) > std::stod(orderRowVec[2]))
        {
            auto position = buyOrder.begin() + count;
            buyOrder.insert(position, orderRow);
            return;
        }

        count++;
    }

    this->buyOrder.push_back(orderRow);
}

void OrderBook::sellCompare(std::vector<std::string> orderRow)
{
    if(this->sellOrder.size() == 0){
        this->sellOrder.push_back(orderRow);
        return;
    }

    int count = 0;
    for (const auto &orderRowVec : this->sellOrder)
    {
        if (std::stod(orderRow[2]) < std::stod(orderRowVec[2]))
        {
            auto position = sellOrder.begin() + count;
            sellOrder.insert(position, orderRow);
            return;
        }

        count++;
    }

    this->sellOrder.push_back(orderRow);
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

std::string OrderBook::get_order_id()
{

    std::string orderId = "ord" + std::to_string(MyGlobals::ORDER_ID++);
    return orderId;
}
