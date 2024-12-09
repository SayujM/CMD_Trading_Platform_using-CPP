#include "OrderBook.h"
#include "CSVReader.h"
#include<map>
#include<algorithm>

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


void OrderBook::insertOrder(OrderBookEntry& userOrderEntry)
{
    orders.push_back(userOrderEntry); // Add the user shared order entry to the end of the transaction data
    std::sort(orders.begin(), orders.end(),OrderBookEntry::compareByTimestamp); // Std sort function takes start, end & logic (function) for sorting criteria

}


/* Key characteristics of the matching algorithm implemented below:
• The lowest ask is processed first.
• The highest bid that matches an ask is given priority over lower, matching bids.
• The lowest price is paid - so if a bid is offering to pay more than an ask, the bidder will only pay as much as the asker wants.
• Partial sales are allowed - if an ask and a bid match but the amounts do not match, the largest possible amount is sold
• Partially matched bids or asks can be re-processed and matched against further bids or asks*/
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(const std::string product, const std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(),OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(),OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry& ask : asks)
    {
        for (OrderBookEntry& bid : bids )
        {
            if ((ask.amount > 0) && (bid.amount > 0) && (bid.price >= ask.price))
            {
                // There is a valid match: Let's create and update sale order book entr
                OrderBookEntry sale{ask.price,
                                    0,
                                    timestamp,
                                    product,
                                    OrderBookType::sale};
                // We need to capture the right amount to be updated for the sale:
                // Scenario-1: Bid Amount equals amount from ask
                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    // Sale Entry is now complete - let's add it to the sales vector
                    sales.push_back(sale);
                    // Re-set the bid: So that it is not considered again
                    bid.amount = 0;
                    // We have exhausted the ask entry so we can break out of this loop & proceed to next ask
                    ask.amount = 0;
                    break;
                }
                // Scenario-2: Bid Amount greater than amount from ask
                if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    // Sale Entry is now complete - let's add it to the sales vector
                    sales.push_back(sale);
                    // Adjust the bid amount so that it is considered for the next ask order
                    bid.amount -= ask.amount;
                    // We have exhausted the ask entry so we can break out of this loop & proceed to next ask
                    ask.amount = 0;
                    break;
                }
                // Scenario-3: Bid Amount lower than amount from ask
                if (bid.amount < ask.amount)
                {
                    sale.amount = bid.amount;
                    // Sale Entry is now complete - let's add it to the sales vector
                    sales.push_back(sale);
                    // Re-set the bid: So that it is not considered again
                    bid.amount = 0;
                    // We have not exhausted the ask order:
                    ask.amount -= bid.amount;
                    continue;
                }
            }
        }
    }
    return sales;
}