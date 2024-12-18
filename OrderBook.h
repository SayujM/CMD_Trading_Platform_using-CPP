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
        /** Returns the next timestamp given the current time 
         *  In case there isn't a greater timestamp, we wrap
         *  back to the earliest timestamp.
        */
        std::string getNextTime(std::string timestamp);
        /** Return the max price for the Orders shared */                                        
        static double getHighPrice(std::vector<OrderBookEntry>& sharedOrders); // Function is static as it is not required to initialise the Class for using it 
        /** Return the min price for the Orders shared */                                        
        static double getLowPrice(std::vector<OrderBookEntry>& sharedOrders);  // As both these functions operate on the order details shared while calling the function. 
        /** Return the average price for the Orders shared */ 
        static double getAvgPrice(std::vector<OrderBookEntry>& sharedOrders);
        /** Insert User Provided Order Book Entry to Transaction Database */
        void insertOrder(OrderBookEntry& userOrderEntry); // Note that this function can't be static as it needs orders from the class instance to work.
        /** Match the orders based on the bid an ask prices for a given product & timestamp  */
        std::vector<OrderBookEntry> matchAsksToBids(const std::string product, const std::string timestamp);
        std::vector<OrderBookEntry> orders;

};

#endif // ORDERBOOK_H