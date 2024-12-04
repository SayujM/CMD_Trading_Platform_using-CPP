#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "OrderBookEntry.h"
#include "CSVReader.h"

class OrderBook
{
    public:
        /** Constructor to read in transactions from CSV file */
        OrderBook(std::string filename);
        /** Return a vector with details of all products in dataset */
        std::vector<std::string> getKnownProducts();
        /** Return a vector with Order details based on user input */
        std::vector<OrderBookEntry> getOrders(  OrderBookType type, 
                                                std::string product,
                                                std::string timestamp);
        std::vector<OrderBookEntry> orders;

};

#endif // ORDERBOOK_H