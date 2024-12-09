#include<iostream>
#include <limits>
#include<string>
#include<vector>
#include <iomanip>
#include<algorithm>
#include "MerkleMain.h"
#include "CSVReader.h"
#include "OrderBook.h"

// Reason to have a separate constructor and init function
// To separate the concerns - a constructor function creates the object & the init function commences the operation based using the obj created.

MerkleMain::MerkleMain()
{

}

void MerkleMain::init()
{
    int i = 0;
    currentTime = orderbook.getEarliestTime();
    previousTime = orderbook.getEarliestTime();
    while (i < 9)  
    {
        // Printing the menu
        printMenu();
        // Fetching user input
        int userOption;
        userOption = getUserOption();
        // Acting on the user input
        handleUseroption(userOption);
        // Restricting looping to 6 times
        ++i;
    }
}


void MerkleMain::printMenu(void)
{
    /* Options to be mentioned in the menu*/
    std::cout << "###########################################" << std::endl;
    std::cout << "Welcome to your very own Merkle Exchange..." << std::endl;
    std::cout << "###########################################" << std::endl;
    // 1 print help
    std::cout << "1. Print help" << std::endl;
    // 2 print exchange stats
    std::cout << "2. Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3. Place an ask" << std::endl;
    // 4 make a bid
    std::cout << "4. Place a bid" << std::endl;
    // 5 print wallet
    std::cout << "5. Print wallet" << std::endl;
    // 6 continue 
    std::cout << "6. Continue" << std::endl;
    // 7. Avg Price per product - Current Timeframe
    std::cout << "7. Avg Price per product - Current Timeframe" << std::endl;
    // 8. Avg Price Change per Product - Over Previous Timeframe
    std::cout << "8. Avg Price Change per Product - Over Previous Timeframe" << std::endl;
    // Demarcator
    std::cout << "====================" << std::endl;
    std::cout << "Current Time is: " << currentTime << std::endl;
    std::cout << "====================" << std::endl;
}

int MerkleMain::getUserOption(void){
    int userOption;
    while (true)
    {
        std::cout << "Select option from 1 - 8" << std::endl;
        std::cin >> userOption;
        if (std::cin.fail())
        {
            /* with the help of CS50.ai to handle non-numeric inputs*/
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice! Choose from 1 - 6." << std::endl;
            std::cout << "====================" << std::endl;
            continue;
        } else if (userOption > 0 && userOption < 9)
        {
            std::cout << "Valid choice! You chose the option: " << userOption << std::endl;  //ignores the rest of the input line, up to the newline character. This effectively discards the invalid input.
            std::cout << "====================" << std::endl;
            break;
        } else
        {
            std::cout << "Invalid choice! Choose from 1 - 8." << std::endl;
            std::cout << "====================" << std::endl;
        }
        
    }
    return userOption;
}

void MerkleMain::printHelp(void){
    std::cout << "Help - Choose options from the menu" << std::endl;
    std::cout << "and follow the onscreen instructions." << std::endl;
}
void MerkleMain::printExchangeStats(void){
    // std::cout << "Exchange stats - Loading data ..." << std::endl;
    // std::cout << "Analyse the transaction data from Exchange to make money!!" << std::endl;
    // std::cout << "Order book currently contains " << orderbook.orders.size() <<" entries."<< std::endl;
    // std::cout << "Featuring entries for following products:" << std::endl;
    std::cout << "Exchange stats - For the Timestamp: " << currentTime << std::endl;
    std::cout << "#########################" << std::endl;
    for (std::string const& p : orderbook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::cout << "--------------------" << std::endl;
        std::vector<OrderBookEntry> askEntries = orderbook.getOrders(OrderBookType::ask,
                                                                            p,
                                                                            currentTime);
        std::cout << "Ask Entry Count = " << askEntries.size() << std::endl;
        std::cout << "Max Ask Price = " << orderbook.getHighPrice(askEntries) << std::endl;
        std::cout << "Min Ask Price = " << orderbook.getLowPrice(askEntries) << std::endl;
        std::cout << "     _-_-_-_-_-_-_     " << std::endl;
        std::vector<OrderBookEntry> bidEntries = orderbook.getOrders(OrderBookType::bid,
                                                                            p,
                                                                            currentTime);
        std::cout << "And Bid Entry Count = " << bidEntries.size() << std::endl;
        std::cout << "Max Bid Price = " << orderbook.getHighPrice(bidEntries) << std::endl;
        std::cout << "Min Bid Price = " << orderbook.getLowPrice(bidEntries) << std::endl;
        std::cout << "====================" << std::endl;

    }
    
    // AVOIDING PRINTING THIS NOW: Printing out the entries stored inside the vector Using the iterator method
    // std::cout << "Further details of the Order entries stored:" << std::endl;
    // std::cout << "#############################################" << std::endl;
    unsigned int bidCount = 0;
    unsigned int askCount = 0;
    unsigned int ETH_BTC_Count = 0;
    unsigned int DOGE_BTC_Count = 0;
    unsigned int BTC_USDT_Count = 0;
    unsigned int ETH_USDT_Count = 0;
    unsigned int DOGE_USDT_Count = 0;
    for (const OrderBookEntry &order : orderbook.orders)
    {
        // std::cout << "Price: " << order.price << std::endl;
        // std::cout << "Amount: " << order.amount << std::endl;
        // std::cout << "Timestamp: " << order.timestamp << std::endl;
        // std::cout << "Product: " << order.product << std::endl;
        // std::cout << "Order Type: " << toString(order.orderType) << std::endl;
        // std::cout << "----------------------------------------" << std::endl;
        
        // rather than printing out order book entries - capturing the order type count ( )
        if (order.product == "ETH/BTC")
        {
            ++ETH_BTC_Count;
        } else if (order.product == "DOGE/BTC")
        {
            ++DOGE_BTC_Count;
        } else if (order.product == "BTC/USDT")
        {
            ++BTC_USDT_Count;
        } else if (order.product == "ETH/USDT")
        {
            ++ETH_USDT_Count;
        } else if (order.product == "DOGE/USDT")
        {
            ++DOGE_USDT_Count;
        } 

        if (order.orderType == OrderBookType::ask )
        {
            ++askCount;
        } else if (order.orderType == OrderBookType::bid )
        {
            ++bidCount;
        }

    }

    // Avoiding the below placeholder stats previously used for testing
    // Fetching & displaying few basic insights from the limited data stored
    std::cout << std::fixed << std::setprecision(10);
    double averagePrice = computeAveragePrice(orderbook.orders);
    double lowPrice = computeLowPrice(orderbook.orders);
    double highPrice = computeHighPrice(orderbook.orders);
    double bidPriceSpread = computePriceSpread(orderbook.orders);

    // A basic commentary on the order entries stored
    // std::cout << "Based on the above mentioned order details:" << std::endl;
    // std::cout << "Entries in order book:  " << orderbook.orders.size() << std::endl;
    // std::cout << "Entries for ETH/BTC:    " << ETH_BTC_Count << std::endl;
    // std::cout << "Entries for DOGE/BTC:   " << DOGE_BTC_Count << std::endl;
    // std::cout << "Entries for BTC/USDT:   " << BTC_USDT_Count << std::endl;
    // std::cout << "Entries for ETH/USDT:   " << ETH_USDT_Count << std::endl;
    // std::cout << "Entries for DOGE/USDT:  " << DOGE_USDT_Count << std::endl;
    // std::cout << "Total bid orders:       " << bidCount << std::endl;
    // std::cout << "Total ask orders:       " << askCount << std::endl;
    // std::cout << "Average Order price:    $" << averagePrice << std::endl;
    // std::cout << "Minimum Order price:    $" << lowPrice << std::endl;
    // std::cout << "Maximum Order price:    $" << highPrice << std::endl;
    // std::cout << "Spread in Order price:  $" << bidPriceSpread << std::endl;
}
void MerkleMain::placeAsk(void){
    std::cout << "Place an ask using the format: product,price,amount" << std::endl;
    std::cout << "For example: BTC/USDT,5394.8,0.5" << std::endl;
    std::string askUserInput;
    /* One of the challenges of using getline is that it reads from the cin buffer as well.
    We are using cin for capturing the user input for menu option selected which contains a number & \n (from the enter key). Number is passed on to the program & 
    The new line character \n sits in buffer & if not cleared will be picked up by the getline command in this menu option of placeAsk.
    So we need to clear the buffer prior to using getline using the code below*/
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Code from stackoverflow
    std::getline(std::cin, askUserInput);
    // Let's use the tokenise function from CSVReader (ensure the same is public) to split user comma separated input taken for ask
    std::vector<std::string> tokens = CSVReader::tokenise(askUserInput, ',');
    // Adding a check on the product string entered to ensure that it is part of our existing product types (from the csv loaded)
    std::vector<std::string> acceptedProducts = orderbook.getKnownProducts(); // Using the function to get all known products.
    auto it = std::find(acceptedProducts.begin(), acceptedProducts.end(), tokens[0]); // As the token[0] holds product entered by user.
    if (tokens.size() != 3 || it == acceptedProducts.end())
    {
        std::cout << "Error Message from: MerkleMain::placeAsk function:" << std::endl;
        std::cout << "Bad Input! You typed: " << askUserInput << std::endl;
        if (it == acceptedProducts.end())
        {
            std::cout << "NOTE: Your Order type \"" << tokens[0] << "\" is not supported!" << std::endl;
            std::cout << "Following are the Order Types accepted for trading on our exchange:" << std::endl;
            for (const std::string& s : acceptedProducts)
            {
                std::cout << s << std::endl;
            }
        }
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                    tokens[2],
                                                    currentTime,
                                                    tokens[0],
                                                    OrderBookType::ask);
        std::cout << "Your Input: " << askUserInput << " is valid! Entry accepted for further processing." << std::endl;
        orderbook.insertOrder(obe);
        }
        catch(const std::exception& e)
        {
            std::cout << "Error Message from: MerkleMain::placeAsk function:" << std::endl;
            std::cout << "Bad Floating point values entered: " << tokens[1] << " or " << tokens[2] << std::endl;
        }
        
    }
}
void MerkleMain::placeBid(void){
    // std::cout << "Place a bid - How much are you willing to pay?" << std::endl;
    // std::cout << "Use the Exchange stats to get the best price." << std::endl;
    std::cout << "Place a bid using the format: product,price,amount" << std::endl;
    std::cout << "For example: BTC/USDT,5394.8,0.5" << std::endl;
    std::string bidUserInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Code from stackoverflow
    std::getline(std::cin, bidUserInput);
    std::vector<std::string> tokens = CSVReader::tokenise(bidUserInput, ',');
    std::vector<std::string> acceptedProducts = orderbook.getKnownProducts(); 
    auto it = std::find(acceptedProducts.begin(), acceptedProducts.end(), tokens[0]);
    if (tokens.size() != 3 || it == acceptedProducts.end())
    {
        std::cout << "Error Message from: MerkleMain::placeBid function:" << std::endl;
        std::cout << "Bad Input! You typed: " << bidUserInput << std::endl;
        if (it == acceptedProducts.end())
        {
            std::cout << "NOTE: Your Order type \"" << tokens[0] << "\" is not supported!" << std::endl;
            std::cout << "Following are the Order Types accepted for trading on our exchange:" << std::endl;
            for (const std::string& s : acceptedProducts)
            {
                std::cout << s << std::endl;
            }
        }
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                    tokens[2],
                                                    currentTime,
                                                    tokens[0],
                                                    OrderBookType::bid);
        std::cout << "Your Input: " << bidUserInput << " is valid! Entry accepted for further processing." << std::endl;
        orderbook.insertOrder(obe);
        }
        catch(const std::exception& e)
        {
            std::cout << "Error Message from: MerkleMain::placeAsk function:" << std::endl;
            std::cout << "Bad Floating point values entered: " << tokens[1] << " or " << tokens[2] << std::endl;
        }
        
    }

}
void MerkleMain::printWallet(void){
    std::cout << "Print wallet - Your wallet is currently empty!" << std::endl;
    std::cout << "Don't worry, just keep at it!!" << std::endl;
}
void MerkleMain::optionContinue(void){
    // std::cout << "Continue - Going through a transaction" << std::endl;
    // std::cout << "You have reached the other side!!" << std::endl;
    std::cout << "Continue - Going to the NEXT timeframe" << std::endl;
    previousTime = currentTime;
    currentTime = orderbook.getNextTime(currentTime);
    std::cout << "Updated current time is: " << currentTime << std::endl;

}

/** Prints out the average prices for both Ask & Bid Entries for the current timeframe */
void MerkleMain::currentAvgPrices(void)
{
    std::cout << "For the Timestamp: " << currentTime << std::endl;
    for (std::string const& p : orderbook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::cout << "--------------------" << std::endl;
        std::vector<OrderBookEntry> askEntries = orderbook.getOrders(OrderBookType::ask,
                                                                            p,
                                                                            currentTime);
        std::cout << "Ask Entry Count = " << askEntries.size() << std::endl;
        std::cout << "Average Ask Price = " << orderbook.getAvgPrice(askEntries) << std::endl;
        std::cout << "     _-_-_-_-_-_-_     " << std::endl;
        std::vector<OrderBookEntry> bidEntries = orderbook.getOrders(OrderBookType::bid,
                                                                            p,
                                                                            currentTime);
        std::cout << "And Bid Entry Count = " << bidEntries.size() << std::endl;
        std::cout << "Average Bid Price = " << orderbook.getAvgPrice(bidEntries) << std::endl;
        std::cout << "====================" << std::endl;

    }
}

/** Prints out the change in average prices for both Ask & Bid Entries */
void MerkleMain::avgPriceChange(void)
{
    std::cout << "For the Timestamp: " << currentTime << std::endl;
    if ( currentTime != previousTime)
    {
        for (std::string const& p : orderbook.getKnownProducts())
        {
            std::cout << "Product: " << p << std::endl;
            std::cout << "--------------------" << std::endl;
            std::vector<OrderBookEntry> askEntriesCurrent = orderbook.getOrders(OrderBookType::ask,
                                                                                p,
                                                                                currentTime);
            std::vector<OrderBookEntry> askEntriesPrevious = orderbook.getOrders(OrderBookType::ask,
                                                                                p,
                                                                                previousTime);
            double currentAvgAskPrice = orderbook.getAvgPrice(askEntriesCurrent);
            double previousAvgAskPrice = orderbook.getAvgPrice(askEntriesPrevious);
            std::cout << "Current Average Ask Price = " << currentAvgAskPrice << std::endl;
            std::cout << "Previous Average Ask Price = " << previousAvgAskPrice << std::endl;
            std::cout << "Delta = " << currentAvgAskPrice - previousAvgAskPrice  << std::endl;
            if (previousAvgAskPrice != 0) 
            {
                double deltaAsk = ((currentAvgAskPrice / previousAvgAskPrice) - 1) * 100;
                // std::cout << std::fixed << std::setprecision(2);
                std::cout << "Delta-% = " << deltaAsk << "%" << std::endl;
            } 
            else 
            {
                std::cout << "Previous average ask price is zero, cannot calculate delta percentage." << std::endl;
            }
            std::cout << "     _-_-_-_-_-_-_     " << std::endl;
            std::vector<OrderBookEntry> bidEntriesCurrent = orderbook.getOrders(OrderBookType::bid,
                                                                                p,
                                                                                currentTime);
            std::vector<OrderBookEntry> bidEntriesPrevious = orderbook.getOrders(OrderBookType::bid,
                                                                                p,
                                                                                previousTime);
            double currentAvgBidPrice = orderbook.getAvgPrice(bidEntriesCurrent);
            double previousAvgBidPrice = orderbook.getAvgPrice(bidEntriesPrevious);
            std::cout << "Current Average Bid Price = " << currentAvgBidPrice << std::endl;
            std::cout << "Previous Average Bid Price = " << previousAvgBidPrice << std::endl;
            std::cout << "Delta = " << currentAvgBidPrice - previousAvgBidPrice  << std::endl;
            if (previousAvgBidPrice != 0) 
            {
                double deltaBid = ((currentAvgBidPrice / previousAvgBidPrice) - 1) * 100;
                // std::cout << std::fixed << std::setprecision(2);
                std::cout << "Delta-% = " << deltaBid << "%" << std::endl;
            } 
            else 
            {
                std::cout << "Previous average ask price is zero, cannot calculate delta percentage." << std::endl;
            }
            std::cout << "====================" << std::endl;

        }
    }
    else
    {
        std::cout << "First use Option-6 to progress timeframe & then use the option to check change in a single timeframe!" << std::endl;
    }
}

void MerkleMain::handleUseroption(int userOption){
    switch (userOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printExchangeStats();
        break;
    case 3:
        placeAsk();
        break;
    case 4:
        placeBid();
        break;
    case 5:
        printWallet();
        break;
    case 6:
        optionContinue();
        break;
    case 7:
        currentAvgPrices();
        break;
    case 8:
        avgPriceChange();
        break;
    default:
        std::cout << "Invalid Choice! Try again" << std::endl;
        break;
    }
    std::cout << "====================" << std::endl;
}

std::string MerkleMain::toString(OrderBookType type) {
    switch (type) {
        case OrderBookType::bid: return "bid";
        case OrderBookType::ask: return "ask";
        default: return "unknown";
    }
}