#pragma once

//Containers used: Stack

#include <iostream>
#include <stack>
#include <exception>
#include <string>
#include <limits>

class RPN{
    private:
        RPN();
        std::stack<int> operands;
        int result;

    public:
        ~RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        RPN(std::string expression);

        class ExceptionWrongExpression : public std::exception{
            public:
                virtual const char* what() const throw();
        };

        class ExceptionIntOverflow : public std::exception{
            public:
                virtual const char* what() const throw();
        };

        class ExceptionDivisionByZero : public std::exception{
            public:
                virtual const char* what() const throw();
        };

        int getResult() const;
};