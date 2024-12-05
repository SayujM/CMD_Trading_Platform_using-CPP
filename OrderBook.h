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
        /** Returns a string with the earliest timestamp */
        std::string getEarliestTime();
        /** Return the max price for the Orders shared */                                        
        static double getHighPrice(std::vector<OrderBookEntry>& sharedOrders); // Function is static as it is not required to initialise the Class for using it 
        /** Return the min price for the Orders shared */                                        
        static double getLowPrice(std::vector<OrderBookEntry>& sharedOrders);  // As both these functions operate on the order details shared while calling the function. 
        std::vector<OrderBookEntry> orders;

};

#endif // ORDERBOOK_H