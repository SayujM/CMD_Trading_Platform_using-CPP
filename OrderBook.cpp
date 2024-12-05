#include "OrderBook.h"
#include "CSVReader.h"
#include<map>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    // Following map function is used to map a string to a bool and is being used to identify the unique product named in the orderbook.
    // Note that existing order type doesn't get another entry but is overwritten though.
    // We can imagine it as creating a python dictionary type data structure to hold product name as key & true as the value
    std::map<std::string, bool> prodMap;  // we can map the string to anything but bool is the smallest logical item & hence preferred for memory opt

    // Now to loop through the orderbook
    for (OrderBookEntry& e: orders)
    {
        prodMap[e.product] = true;
    }
    // Now that we have the dictionary type variable, we need to extract the keys
    // In the words of our prof: we have to flatten the map into a vector of strings
    // Note that the auto keyword lets the compiler to assign variable type
    for (auto const& e: prodMap)
    {
        products.push_back(e.first);  // similar to .keys operation in python dictionary
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, 
                                                std::string product, 
                                                std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp)
            {
                orders_sub.push_back(e);
            }
    }
    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& sharedOrders)
{
    double max = sharedOrders[0].price;
    for (OrderBookEntry& e: sharedOrders)
    {
        if (e.price > max)
        {
            max = e.price;
        }
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& sharedOrders)
{
    double min = sharedOrders[0].price;
    for (OrderBookEntry& e: sharedOrders)
    {
        if (e.price < min)
        {
            min = e.price;
        }
    }
    return min;
}

double OrderBook::getAvgPrice(std::vector<OrderBookEntry>& sharedOrders)
{
    double sum = 0.0f;
    double count = sharedOrders.size();
    for (OrderBookEntry& e: sharedOrders)
    {
        sum += e.price;
    }

    if (count == 0)
    {
        return 0.0f;
    }

    return sum/count;
}


std::string OrderBook::getEarliestTime()
{
    // Assuming the transaction data are sorted wrt timestamp
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    // Assuming the transaction data are sorted wrt timestamp
    // Next Time stamp is the first timestamp greater than the function input timestamp
    std::string nextTimeStamp = "";
    for (OrderBookEntry& e: orders)
    {
        if (e.timestamp > timestamp)
        {
            nextTimeStamp = e.timestamp;
            break;
        }
    }
    if (nextTimeStamp == "") // That is we couldn't find a timestamp larger than the given timestamp
    {
        nextTimeStamp = orders[0].timestamp; // We wrap back the timestamp to start again from the top!
    }
    return nextTimeStamp;
}