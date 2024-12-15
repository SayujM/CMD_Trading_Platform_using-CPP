#include "Wallet.h"
#include "CSVReader.h"
#include<iostream>

Wallet::Wallet()
{

}

void Wallet::insertCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        throw std::exception{};
    }
    
    if (currencyBalance.count(type) == 0)   // Implies we don't have the currency yet
    {
        currencyBalance[type] = amount;
    }
    else
    {
        currencyBalance[type] += amount;
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencyBalance.count(type) == 0)
    {
        return false;
    }
    else
    {
        return currencyBalance[type] >= amount;
    }
}

std::string Wallet::walletToString()
{
    std::string s = "";
    for (std::pair<std::string, double> pair: currencyBalance)
    {
        std::string currencyName = pair.first;
        double currencyAmount = pair.second;
        s += currencyName + " : " + std::to_string(currencyAmount) + "\n";
    }
    return s;
}


bool Wallet::removeCurrency(std::string type, double amount)
{
   if (amount < 0)
    {
        throw std::exception{};
    }
    
    if (currencyBalance.count(type) == 0)   
    {
        std::cout << "Currency " << type << " unavailable in the wallet. Check your wallet!!" << std::endl;
        return false;
    }
    else
    {
        if (currencyBalance[type] >= amount)
        {
            currencyBalance[type] -= amount;
            return true;
        }
        else
        {
            std::cout << "Insufficient Amount. Current balance of currency  \"" << type << "\" : " << currencyBalance[type] << std::endl;
            return false;
        }
    } 
}

bool Wallet::canFulfillOrder(const OrderBookEntry order)
{
    std::vector<std::string> currencies = CSVReader::tokenise(order.product, '/');
    // Validating Ask Order
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string sellingCurrency = currencies[0];
        return containsCurrency(sellingCurrency, amount);
    }
    // Validating Bid Order
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.price * order.amount;
        std::string purchasingCurrency = currencies[1];
        return containsCurrency(purchasingCurrency, amount);
    }
    // Else - Non-Standard order type received  
    return false;
}

std::ostream& operator<<(std::ostream& os, Wallet& wallet)
{
os << wallet.walletToString();
return os;
}

void Wallet::processSale(OrderBookEntry& sale)
{
    if (sale.username == "simUser")
    {
        std::vector<std::string> currencies = CSVReader::tokenise(sale.product, '/');
        // Handling Ask sale for the user
        if (sale.orderType == OrderBookType::askSale)
        {
            double outgoingAmount = sale.amount;
            std::string outgoingCurrency = currencies[0];
            double incomingAmount = sale.price * sale.amount;
            std::string incomingCurrency = currencies[1];
            // Now update the wallet (map data-structure)
            currencyBalance[incomingCurrency] += incomingAmount;
            currencyBalance[outgoingCurrency] -= outgoingAmount;
        }
        // Handling Bid sale for the user
        if (sale.orderType == OrderBookType::bidSale)
        {
            double outgoingAmount = sale.price * sale.amount;
            std::string outgoingCurrency = currencies[1];
            double incomingAmount = sale.amount;
            std::string incomingCurrency = currencies[0];
            // Now update the wallet (map data-structure)
            currencyBalance[incomingCurrency] += incomingAmount;
            currencyBalance[outgoingCurrency] -= outgoingAmount;
        }
        // Handling intra Account sale for the user
        // No Action to take as the matching logic shall place the revised price & amount for the balance Bid or Ask order.
    }
}