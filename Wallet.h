#ifndef WALLET_H
#define WALLET_H

#include "OrderBookEntry.h"
#include<string>
#include<map>

class Wallet
{
    public:
        Wallet();
        /** Insert Currency into the wallet */
        void insertCurrency(std::string type, double amount);
        /** Remove Currency from the wallet */
        bool removeCurrency(std::string type, double amount);
        /** Check if the wallet contains the given amount or more of the currency mentioned */
        bool containsCurrency(std::string type, double amount);
        /** Generate a string representation of the object from Wallet class */
        /** Validate an Order based on the current Wallet status */
        bool canFulfillOrder(OrderBookEntry order);
        std::string walletToString();
        /** Operator Overloading for Wallet class */
        friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);
        /** Update user Wallet based on Matched Orders details from Sale Entry */
        void processSale(OrderBookEntry& sale);
    private:
        std::map<std::string, double> currencyBalance;
};

#endif // WALLET_H