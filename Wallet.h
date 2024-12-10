#ifndef WALLET_H
#define WALLET_H

#include<string>
#include<map>

class Wallet
{
    public:
        Wallet();
        /** Insert Currency into the wallet */
        void insertCurrency(std::string type, double amount);
        /** Check if the wallet contains the given amount or more of the currency mentioned */
        bool containsCurrency(std::string type, double amount);
        /** Generate a string representation of the object from Wallet class */
        std::string walletToString();
    private:
        std::map<std::string, double> currencyBalance;
};

#endif // WALLET_H