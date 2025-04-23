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
        std::map<std::string, float> exchangeRates;


    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);


        class FileOpeningException: public std::exception{
            virtual const char* what() const throw();
        };

        class DatabaseFileOpeningException: public std::exception{
            virtual const char* what() const throw();
        };

        class WrongFormatFileException: public std::exception{
			private:
				std::string errorInFile;
			public:
				WrongFormatFileException(const std::string &error);
            	virtual const char* what() const throw();
				virtual ~WrongFormatFileException() throw();
        };


		void handleInputFile(std::string inputFileName);
};

std::vector<std::string> split(std::string &str, std::string &delimiter);
bool validDate(std::string &date);
bool validFloat(std::string &numberString);