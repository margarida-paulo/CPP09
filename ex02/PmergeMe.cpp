#include "PmergeMe.hpp"

//Containers FORBIDDEN: Map, Vector and Stack

PmergeMe::~PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe &other){
    (void) other;
    //TODO copy attributes if they exist
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other){
    (void) other;
    //TODO copy attributes if they exist
    return *this;
}

const char* PmergeMe::invalidInputException::what() const throw(){
    return "Invalid input";
}

int validateInput(std::string numberString){
    int integer;

    std::istringstream numberStream(numberString);
    if ((numberStream >> integer) && numberStream.eof())
        return integer;
    throw PmergeMe::invalidInputException();
}