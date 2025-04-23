#include "RPN.hpp"

int main(int argc, char **argv){

    //Check if number of arguments is correct
    if (argc != 2){
        std::cout << "Usage: ./RPN <Inverted Polish Mathematical Expression>" << std::endl;
        return 1;
    }

    try{
        std::cout << RPN(std::string(argv[1])).getResult() << std::endl;
    } catch (RPN::ExceptionWrongExpression &e){
        std::cerr << e.what() << std::endl;
    } catch (RPN::ExceptionIntOverflow &e){
        std::cerr << e.what() << std::endl;
    } catch (RPN::ExceptionDivisionByZero &e){
        std::cerr << e.what() << std::endl;
    }

}