#include "OrderBook.h"


OrderBook::OrderBook(std::string filename)
{

}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, 
                                                std::string product, 
                                                std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    return orders_sub;
}