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
    private:
      static std::vector<std::string> tokenise(std::string csvLine, char separator);
      static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};

#endif // CSVREADER_H


// NOTE: We can call static functions without needing to create an instance of the class to which it belongs!