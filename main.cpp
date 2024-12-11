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
    MerkleMain app{};
    std::cout << "====================" << std::endl;
    std::cout << "Program Menu Details:" << std::endl;
    std::cout << "====================" << std::endl;
    app.init();
    return 0;
}


/* Note on the Order Book Entry:
For example meaning of the entry: 2020/03/17 17:01:24.884492,ETH/BTC,ask,0.02222991,0.5
- Type of Order : Ask ( Meaning I intend to sell something which I have)
- Valid Timeframe: 2020/03/17 17:01:24.884492 ( only in this particular timeframe can this order be matched with a valid Bid )
- Meaning of remaining field: User has 0.5 amounts of ETH, which he or she is willing to sell at a price of 0.02222991 BTC per unit ETH. 
- Therefor on a successful match with a bid, the user will sell upto 0.5 ETH receiving 0.5 * 0.02222991 BTC.
----------------------------------------------------------------------------------------------------------------------------------------------
For example meaning of the entry: 2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02161593,0.00636546
- Type of Order : Bid ( Meaning I intend to purchase something with the currency I have)
- Valid Timeframe: 2020/03/17 17:01:24.884492 ( only in this particular timeframe can this order be matched with a valid Ask )
- Meaning of remaining field: User is willing to buy upto 0.00636546 ETH and am willing ( and able ) to pay 0.02161593 BTC per unit ETH.
- Therefor on a successful match with an ask, the user will purchase upto 0.00636546 ETH by paying upto 0.02161593 * 0.00636546 BTC.
----------------------------------------------------------------------------------------------------------------------------------------------
NOTE: Word "upto" is used in the above explanation to communicate that partial fulfillment of Orders are allowed on the exchange.
*/