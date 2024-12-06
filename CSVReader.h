#ifndef CSVREADER_H
#define CSVREADER_H

#include<iostream>
#include<string>
#include<vector>
#include "OrderBookEntry.h"


class CSVReader
{
    public:
      CSVReader();
      static std::vector<OrderBookEntry> readCSV(std::string csvFile);
      static std::vector<std::string> tokenise(std::string csvLine, char separator);
      // Using the feature of function overloading ( i.e repeating same function name but with different calling parameters)
      // Compiler differentiates amongst these functions based on the way the function is called.
      static OrderBookEntry stringsToOBE(std::string price,
                                        std::string amount,
                                        std::string timestamp,
                                        std::string product,
                                        OrderBookType orderType);
    private:
      static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};

#endif // CSVREADER_H


// NOTE: We can call static functions without needing to create an instance of the class to which it belongs!