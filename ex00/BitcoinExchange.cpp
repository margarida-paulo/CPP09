#include "BitcoinExchange.hpp"


bool validDate(std::string &date) {
    std::vector<std::string> yearMonthDay = split(date, '-');
    if (yearMonthDay.size() != 3)
        return false;

    int year;
    int month;
    int day;

    std::istringstream yearStream(yearMonthDay[0]);
    std::istringstream monthStream(yearMonthDay[1]);
    std::istringstream dayStream(yearMonthDay[2]);

    if (!(yearStream >> year && yearStream.eof()) ||
        !(monthStream >> month && monthStream.eof()) ||
        !(dayStream >> day && dayStream.eof())) {
        return false;
    }

    // Validação dos meses com 30 dias (abril, junho, setembro, novembro)
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day >= 1 && day <= 30) {
            return true;
        }
    }
    // Validação para o mês de fevereiro
    else if (month == 2) {
        if ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
            if (day >= 1 && day <= 29) {
                return true;  // Ano bissexto: fevereiro tem 29 dias
            }
        } else {
            if (day >= 1 && day <= 28) {
                return true;  // Ano não bissexto: fevereiro tem 28 dias
            }
        }
    }
    // Validação dos meses com 31 dias
    else if (month >= 1 && month <= 12) {
        if (day >= 1 && day <= 31) {
            return true;
        }
    }

    return false;
}

bool validDouble(std::string &numberString){
    double numberDouble;
    std::istringstream numberStream(numberString);

    if (!(numberStream >> numberDouble && numberStream.eof()))
        return false;
    return true;
}


BitcoinExchange::BitcoinExchange(): dataFileOpen(false), dataFile("data.csv"){
    // Check if ifstream of data file
    if (!dataFile.good()){
        std::cout << "Error in opening the file" << std::endl;
        throw FileOpeningException();
    }
    dataFileOpen = true; // Boolean that tells if the file is open
    int firstLine = true; // Boolean that teels that we're in the first line of the file

    std::string nextLineInFile; // String that stores the next line in the file
    while(std::getline(dataFile, nextLineInFile)){
        if (firstLine && nextLineInFile != "date,exchange_rate"){
            throw WrongFormatFileException();
        }
        if (!firstLine){
            std::vector<std::string> dateAndNumber = split(nextLineInFile, ',');
            if (dateAndNumber.size() != 2 || !(validDate(dateAndNumber[0])) || !(validDouble(dateAndNumber[1])))
                throw WrongFormatFileException();
            double rateDouble;
            std::istringstream rateDoubleStream(dateAndNumber[1]);
            rateDoubleStream >> rateDouble;
            exchangeRates.insert(std::pair<std::string, double>(dateAndNumber[0], rateDouble));
            //DEBUG std::cout << "Date: " << dateAndNumber[0] << " | Number: " << dateAndNumber[1] << std::endl;              
        }
        firstLine = false;
    }

    std::map<std::string, double>::iterator it = exchangeRates.begin();
    while (it != exchangeRates.end()){
        std::cout << "Date: " << it->first << " | Number: " << it->second << std::endl;
        it++;
    }

}

BitcoinExchange::~BitcoinExchange(){
    if (dataFileOpen)
        dataFile.close();
    exchangeRates.clear();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    (void)other; //TODO when there are attributes, fix this!
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other){
    (void)other; //TODO when there are attributes, fix this!
    return *this;}

const char* BitcoinExchange::FileOpeningException::what() const throw(){
    return "Error: File stream couldn't be opened properly.";
}

const char* BitcoinExchange::WrongFormatFileException::what() const throw(){
    return "Error: File is in the wrong format.";
}

std::vector<std::string> split(std::string &str, char delimiter){
    std::vector<std::string> finalStrings;
    std::string stringVersion = str;

    size_t begin = 0;
    size_t end = stringVersion.find(delimiter);
    while (end != std::string::npos) {
        finalStrings.push_back(stringVersion.substr(begin, end - begin));
        begin = end + 1;
        end = stringVersion.find(delimiter, begin);
    }
    finalStrings.push_back(stringVersion.substr(begin, stringVersion.size()));
    return finalStrings;
}