#include "CSVReader.h"
#include<fstream>
#include <algorithm>
#include <cctype>

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFileName};
    std::string line;
    if (!csvFile.is_open())
    {
        std::cerr << "Error: Could not open file " << csvFileName << std::endl;
        return entries;
    }
    std::cout << "File opened successfully: " << csvFileName << std::endl;
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

// // The following function is copied in directly from test.cpp ( refer to the program for the comments on the function)
// std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
// {
//     std::vector<std::string> tokens;
//     std::string token;

//     unsigned int start, end;
//     start = csvLine.find_first_not_of(separator, 0);
//     end = csvLine.find_first_of(separator, start);
//     // std::cout << "Initial Start: " << start << ", Initial End: " << end << std::endl;
//     do
//     {
//         if (start == std::string::npos) 
//         {
//             break;
//         }
//         end = csvLine.find_first_of(separator, start);
//         // std::cout << "Start: " << start << ", End: " << end << std::endl; // Debugging line

//         if (start == csvLine.length() || start == end)
//             break;

//         if (end != std::string::npos)
//         {
//             token = csvLine.substr(start, end - start);
//         }
//         else
//         {
//             token = csvLine.substr(start, csvLine.length() - start); //
//         }
        
//         tokens.push_back(token);
//         // std::cout << "Token: " << token << std::endl; // Add this line for debugging
//         // start = end + 1;
//          if (end != std::string::npos)
//         {
//             start = end + 1;
//             // std::cout << "New Start: " << start << std::endl;
//         }
//         else
//         {
//             break;
//         }
//         // std::cout << "End of Loop - Start: " << start << ", End: " << end << std::endl; // Debugging line

//     } while (end != std::string::npos);

//     return tokens;

// }
std::string trim(const std::string& str) {
    auto it1 = std::find_if_not(str.begin(), str.end(), [](unsigned char ch) {
        return std::isspace(ch);
    });
    auto it2 = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch) {
        return std::isspace(ch);
    }).base();
    return std::string(it1, it2);
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string token;

    unsigned int start = 0;
    unsigned int end = 0;
    std::string text = trim(csvLine);
    start = text.find_first_not_of(separator, 0);
    while (start < text.length() && end < text.length())
    {
        end = text.find(separator, start);
        if (end >= 0)
        {
            token = text.substr(start, end - start);
        }
        else
        {
            token = text.substr(start, text.length() - start); //
        }
        
        tokens.push_back(token);
        start = end + 1;
    }

    return tokens;

}

// Note that in the below function we are using "throw" to raise exceptions. Intention here is: 
// Catching the exception to make it clear that something went wrong, 
// then throwing the exception to the calling function so it can decide what to do as it knows better the context.

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    if (tokens.size() != 5) // Implies that we have an entry that doesn't follow the standard format
        {
            std::cout << "Error Message From: CSVReader::stringsToOBE Function" << std::endl;
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
            std::cout << "Error Message From: CSVReader::stringsToOBE Function" << std::endl;
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

OrderBookEntry CSVReader::stringsToOBE(std::string _price,
                                        std::string _amount,
                                        std::string timestamp,
                                        std::string product,
                                        OrderBookType orderType)
{
    double price, amount;
    try
    {
        price = std::stod(_price); // Utilising the standard string to double function to convert str to double
        amount = std::stod(_amount);
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << std::endl;
        std::cout << "Error Message From: CSVReader::stringsToOBE Function" << std::endl;
        std::cout << "Bad Floating point values received in file!" << std::endl;
        std::cout << "Received Floats: " << _price << " | " << _amount << std::endl;
        throw;    // Crash out of program if we don't have proper numerical inputs
    }
        

    OrderBookEntry obe{ price,
                        amount,
                        timestamp,
                        product,
                        orderType};

    return obe;
}