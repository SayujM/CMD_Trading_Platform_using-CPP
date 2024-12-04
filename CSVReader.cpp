#include "CSVReader.h"
#include<fstream>

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFileName};
    std::string line;

    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch(const std::exception& e)
            {
                std::cout << "Cout from function CSVReader::readCSV: Bad Data received - Omitting line! " << std::endl;
            }
            
        } // end of while loop
        csvFile.close();
    }
    std::cout << "Cout from function CSVReader::readCSV: entries read: " << entries.size() << std::endl;
    return entries;

}

// The following function is copied in directly from test.cpp ( refer to the program for the comments on the function)
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string token;

    unsigned int start, end;
    start = csvLine.find_first_not_of(separator, 0);

    do
    {
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end)
            break;

        if (end >= 0)
        {
            token = csvLine.substr(start, end - start);
        }
        else
        {
            token = csvLine.substr(start, csvLine.length() - start); //
        }
        
        tokens.push_back(token);
        start = end + 1;

    } while (end != std::string::npos);

    return tokens;

}

// Note that in the belo function we are using "throw" to raise exceptions. Intention here is: 
// Catching the exception to make it clear that something went wrong, 
// then throwing the exception to the calling function so it can decide what to do as it knows better the context.

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    if (tokens.size() != 5) // Implies that we have an entry that doesn't follow the standard format
        {
            std::cout << "Bad Line. Omitting it." << std::endl;
            throw std::exception{};   // Crash out of program if we don't have proper input tokens vector
        }
        // We have 5 tokens now
        try
        {
            price = std::stod(tokens[3]); // Utilising the standard string to double function to convert str to double
            amount = std::stod(tokens[4]);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << std::endl;
            std::cout << "Bad Floating point values received in file!" << std::endl;
            std::cout << "Received Floats: " << tokens[3] << " | " << tokens[4] << std::endl;
            throw;    // Crash out of program if we don't have proper numerical inputs
        }

    OrderBookEntry obe{ price,
                        amount,
                        tokens[0],
                        tokens[1],
                        OrderBookEntry::strToOrderBookType(tokens[2])};

    return obe;

}