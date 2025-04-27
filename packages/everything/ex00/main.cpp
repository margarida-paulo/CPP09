#include <iostream>
#include <fstream>
#include <string>

#include "BitcoinExchange.hpp"

int main(int argc, char **argv){
    // Error checks of the program arguments
    if (argc != 2 || argv[1] == NULL){
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::string inputFileName(argv[1]); // Turn the file name into a string

    try {
        BitcoinExchange btc;
		btc.handleInputFile(inputFileName);
    } catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return 1;
    }



}
