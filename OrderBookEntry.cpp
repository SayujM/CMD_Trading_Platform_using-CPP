#include "OrderBookEntry.h"

// Implementation for the class constructor
OrderBookEntry::OrderBookEntry( double _price,
                                double _amount,
                                std::string _timestamp,
                                std::string _product,
                                OrderBookType _orderType,
                                std::string _username)
:    //Constructor initialisation list
    price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    orderType(_orderType),
    username(_username)
{
    // Doesn't require further code to initialse data members of the class
}

// Implementation for the function to convert a string to enum class OrderBookType entry
OrderBookType OrderBookEntry::strToOrderBookType(std::string token)
{
    if (token == "ask")
    {
        return OrderBookType::ask;
    }
    else if (token == "bid")
    {
        return OrderBookType::bid;
    }
    else if (token == "askSale")
    {
        return OrderBookType::askSale;
    }
    else if (token == "bidSale")
    {
        return OrderBookType::bidSale;
    }
    else
    {
        return OrderBookType::unknown;
    }

}


// Implementation for printing out enum class object
std::string toString(OrderBookType type)
{
    switch (type)
    {
    case OrderBookType::bid:
        return "bid";
    case OrderBookType::ask:
        return "ask";
    case OrderBookType::askSale:
        return "askSale";
    case OrderBookType::bidSale:
        return "bidSale";
    default:
        return "unknown";
    }
}

// Implementation for findind the average price
double computeAveragePrice(std::vector<OrderBookEntry> &entries)
{
    /* Returns the average bid price from the order entries*/
    double sum = 0.0;
    int count = 0;
    for (unsigned int i = 0; i < entries.size(); ++i)
    {
        sum += entries[i].price;
        count++;
    }

    double averagePrice = sum / count;
    return averagePrice;
}

// Implementation for findind the lowest price
double computeLowPrice(std::vector<OrderBookEntry> &entries)
{
    /* Returns the lowest bid price from the order entries*/
    double low = 0.0;
    
    for (unsigned int i = 0; i < entries.size(); ++i)
    {
        if (low == 0.0 || entries[i].price < low)
        {
            low = entries[i].price;
        }
    }
    return low;
}

// Implementation for findind the highest price
double computeHighPrice(std::vector<OrderBookEntry> &entries)
{
    /* Returns the lowest bid price from the order entries*/
    double high = 0.0;

    for (unsigned int i = 0; i < entries.size(); ++i)
    {
        if (high == 0.0 || entries[i].price > high)
        {
            high = entries[i].price;
        }
    }
    return high;
}

// Implementation for findind the bid price spread
double computePriceSpread(std::vector<OrderBookEntry> &entries)
{
    /* Ideally a price spread is the is the amount by which the ask price exceeds the bid price for an asset in the market.
    In simpler terms, price spread = maximum Bid Price - minimum Asking Price.
    The bid-ask spread is essentially the difference between the highest price that a buyer is willing to pay for an asset 
    and the lowest price that a seller is willing to accept. Hence a narrow bid/ask spread typically indicates good liquidity.
    */
   // However, in the given function I am computing the spread in the bid price alone
    double high = computeHighPrice(entries);
    double low  = computeLowPrice(entries);
    double bidPriceSpread = high - low;
    return bidPriceSpread;
}