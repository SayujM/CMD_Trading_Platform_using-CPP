#include<iostream>
#include <limits>
#include<string>
#include<vector>
#include <iomanip>
#include "OrderBookEntry.h"
#include "MerkleMain.h"
#include "CSVReader.h"

int main()
{   
    // Printing the in line interaction menu
    MerkleMain app{};
    std::cout << "Program Menu Details:" << std::endl;
    std::cout << "====================" << std::endl;
    app.init();
    return 0;
}

