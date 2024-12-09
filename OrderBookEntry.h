#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H
/* The above 2 lines of code with the last #endif are guards put in place to tell the compiler to refer only
to this header file while checking for the definitions of specifications mentioned below.
when header files are included multiple times, the compile throws error as it cannot decide where to look for the right details*/

#include<string>
#include<vector>

// Putting a constraint on the entries for Order types
enum class OrderBookType
{
    bid,
    ask,
    unknown,
    sale
};

// Creating a class for holding Order Book entries
class OrderBookEntry
{
    public:
        // Prototype for constructor
        /** Create a new Order Book Entry*/
        OrderBookEntry( double _price,
                        double _amount,
                        std::string _timestamp,
                        std::string _product,
                        OrderBookType _orderType);
        static OrderBookType strToOrderBookType(std::string token);
        static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.timestamp < e2.timestamp;
        }
        static bool compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
        static bool compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }
        // Declaring the class data members
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
};

// Prototypes for the functions
std::string toString(OrderBookType type);
double computeAveragePrice(std::vector<OrderBookEntry> &entries);
double computeLowPrice(std::vector<OrderBookEntry> &entries);
double computeHighPrice(std::vector<OrderBookEntry> &entries);
double computePriceSpread(std::vector<OrderBookEntry> &entries);

#endif // ORDERBOOKENTRY_H