#include "RPN.hpp"

//Containers used: Stack

// Operations to handle: + - / *

RPN::RPN(std::string expression){
    bool previousWasSpace = true;
    if (expression.empty())
        throw ExceptionWrongExpression();
    for (size_t i = 0; i < expression.size(); i++){
        if (expression[i] == ' '){
            previousWasSpace = true;
            continue;
        }
        if (!previousWasSpace && expression[i] != ' ')
            throw ExceptionWrongExpression();
        if (isdigit(expression[i])){
            previousWasSpace = false;
            operands.push(expression[i] - '0');
            continue;
        }
        if (operands.size() < 2)
            throw ExceptionWrongExpression();
        int b = operands.top();
            operands.pop();
        int a = operands.top(); 
            operands.pop();
        switch(expression[i]){
            case '+':
                if ((double)a+(double)b > std::numeric_limits<int>::max())
                    throw ExceptionIntOverflow();
                operands.push(a+b);
                break;
            case '-':
                if ((double)a-(double)b < std::numeric_limits<int>::min())
                    throw ExceptionIntOverflow();
                operands.push(a-b);
                break;
            case '*':
                if ((double)a*(double)b > std::numeric_limits<int>::max())
                    throw ExceptionIntOverflow();
                operands.push(a*b);
                break;
            case '/':
                if (b == 0)
                    throw ExceptionDivisionByZero();
                operands.push(a/b);
                break;
            default:
                throw ExceptionWrongExpression();
        }
    }
    if (operands.size() > 1)
        throw ExceptionWrongExpression();
    result = operands.top();
}

RPN::~RPN(){
    while (!(operands.empty()))
        operands.pop();
}

RPN::RPN(const RPN &other): operands(other.operands), result(other.result){}

RPN &RPN::operator=(const RPN &other){
    if (&other != this){
        operands = other.operands;
        result = other.result;
    }
    return *this;
}

int RPN::getResult() const {return result;}

const char* RPN::ExceptionWrongExpression::what() const throw(){
    return "Error";
}

const char* RPN::ExceptionIntOverflow::what() const throw(){
    return "Error: Integer overflow, calculator can only support numbers between –2147483648 and 2147483647 (INT_MIN and INT_MAX)";
}

const char* RPN::ExceptionDivisionByZero::what() const throw(){
    return "Error: Division by zero is mathematically impossible in the set of integers";
}