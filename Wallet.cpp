#include "Wallet.h"
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