#include<iostream>
#include <limits>
#include<string>
#include<vector>
#include <iomanip>
#include "OrderBookEntry.h"
#include "MerkleMain.h"
#include "CSVReader.h"
#include "Wallet.h"

int main()
{   
    // Printing the in line interaction menu
    // MerkleMain app{};
    // std::cout << "====================" << std::endl;
    // std::cout << "Program Menu Details:" << std::endl;
    // std::cout << "====================" << std::endl;
    // app.init();
    Wallet wallet;
    wallet.insertCurrency("BTC", 15);
    wallet.insertCurrency("ETH", 25);
    wallet.insertCurrency("USDT", 100);
    wallet.insertCurrency("DOGE", 1000);
    std::cout << "Does my wallet contain 10 USDT? (1:YES | 0:NO): " << wallet.containsCurrency("USDT", 10) << std::endl;
    std::cout << "Printing wallet - Current contents of my wallet:" << std::endl;
    std::cout << wallet.walletToString() << std::endl;
    wallet.removeCurrency("DOGE", 115);
    std::cout << wallet.walletToString() << std::endl;
    return 0;
}

