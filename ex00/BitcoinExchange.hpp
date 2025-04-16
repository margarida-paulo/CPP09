#pragma once

#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

class BitcoinExchange{
    private:

        //Attributes
        bool dataFileOpen;
        std::ifstream dataFile;
        std::map<std::string, double> exchangeRates;


    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);


        class FileOpeningException: public std::exception{
            virtual const char* what() const throw();
        };

        class WrongFormatFileException: public std::exception{
            virtual const char* what() const throw();
        };
};

std::vector<std::string> split(std::string &str, char delimiter);
bool validDate(std::string &date);
bool validDouble(std::string &numberString);