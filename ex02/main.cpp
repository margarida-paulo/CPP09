#include "PmergeMe.hpp"

int main(int argc, char **argv){
    if (argc <= 1){
        std::cerr << "Usage: ./PmergeMe <list> <of> <integers> <...>" << std::endl;
        return 1;
    }
    for (int i = 1; i < argc; i++){
        try{
            validateInput(std::string(argv[i]));
        } catch (PmergeMe::invalidInputException &e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}