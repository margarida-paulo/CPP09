#pragma once

#include <string>
#include <sstream>
#include <iostream>

//Containers FORBIDDEN: Map, Vector and Stack
//Let's use Array and List.
//Vector because looking for a specific element is faster, so looking for the placement of the binary insertion will be faster.
//List because insertions in the middle of a list are faster, so the binary insertion will be faster.


class PmergeMe{
    private:
        PmergeMe();
        
    
    public:
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        class invalidInputException: public std::exception{
            public:
                virtual const char* what() const throw();
        };
};

int validateInput(std::string number);