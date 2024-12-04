#ifndef MERKLEMAIN_H
#define MERKLEMAIN_H


#include<string>
#include<vector>
#include "OrderBookEntry.h"

class MerkleMain
{

    public:
        MerkleMain(/* args */);
        /** Call this function to start the simulation */
        void init();
    private: // Limiting the methods that can be used outside the class namespace.    
        void printMenu(void);
        int getUserOption(void);
        void handleUseroption(int userOption);
        void printHelp(void);
        void loadOrderBook(void);
        void printExchangeStats(void);
        void placeAsk(void);
        void placeBid(void);
        void printWallet(void);
        void optionContinue(void);
        std::string toString(OrderBookType type);
        std::vector<OrderBookEntry> orders;
};

#endif // MERKLEMAIN_H
