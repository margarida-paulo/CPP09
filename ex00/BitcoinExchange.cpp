#include "BitcoinExchange.hpp"


bool validDate(std::string &date) {
	std::string delimiter("-");
    std::vector<std::string> yearMonthDay = split(date, delimiter);
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

bool validFloat(std::string &numberString){
    float numberFloat;
    std::istringstream numberStream(numberString);

    if (!(numberStream >> numberFloat && numberStream.eof()))
        return false;
    return true;
}


BitcoinExchange::BitcoinExchange(): dataFileOpen(false), dataFile("data.csv"){
    // Check if ifstream of data file
    if (!dataFile.good()){
        throw DatabaseFileOpeningException();
    }
    dataFileOpen = true; // Boolean that tells if the file is open
    size_t line = 1; // Size_t that tells the current line being analyzed

    std::string nextLineInFile; // String that stores the next line in the file
	std::string delimiter(",");
    while(std::getline(dataFile, nextLineInFile)){
        if (line == 1 && nextLineInFile != "date,exchange_rate"){
            throw WrongFormatFileException(std::string("First line of csv database should be \"date, exchange rate\"."));
        }
        if (line != 1){
            std::vector<std::string> dateAndNumber = split(nextLineInFile, delimiter);
            if (dateAndNumber.size() != 2 || !(validDate(dateAndNumber[0])) || !(validFloat(dateAndNumber[1]))){
				std::stringstream message;
				message << "Line " << line << " is not correctly formatted";
                throw WrongFormatFileException(message.str());
			}
            double rateFloat;
            std::istringstream rateFloatStream(dateAndNumber[1]);
            rateFloatStream >> rateFloat;
            exchangeRates.insert(std::pair<std::string, double>(dateAndNumber[0], rateFloat));
            //DEBUG std::cout << "Date: " << dateAndNumber[0] << " | Number: " << dateAndNumber[1] << std::endl;
        }
        line++;
    }

	//DEBUG
    //std::map<std::string, double>::iterator it = exchangeRates.begin();
    //while (it != exchangeRates.end()){
    //    std::cout << "Date: " << it->first << " | Number: " << it->second << std::endl;
    //    it++;
    //}

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
    return "Error: could not open file.";
}

const char* BitcoinExchange::DatabaseFileOpeningException::what() const throw(){
    return "Error: could not open database file.";
}

BitcoinExchange::WrongFormatFileException::WrongFormatFileException(const std::string &error){
	errorInFile = "Error: File is in the wrong format: " + error;
}

BitcoinExchange::WrongFormatFileException::~WrongFormatFileException() throw(){}

const char* BitcoinExchange::WrongFormatFileException::what() const throw(){
    return errorInFile.c_str();
}

std::vector<std::string> split(std::string &str, std::string &delimiter){
    std::vector<std::string> finalStrings;
    std::string stringVersion = str;

    size_t begin = 0;
    size_t end = stringVersion.find(delimiter);
    while (end != std::string::npos) {
        finalStrings.push_back(stringVersion.substr(begin, end - begin));
        begin = end + delimiter.size();
        end = stringVersion.find(delimiter, begin);
    }
    finalStrings.push_back(stringVersion.substr(begin, stringVersion.size()));
    return finalStrings;
}


void BitcoinExchange::handleInputFile(std::string inputFileName){
    // Check if ifstream of data file
	std::ifstream inputFileStream(inputFileName.c_str());
	std::string delimiter(" | ");

    if (!inputFileStream.good()){
        throw FileOpeningException();
    }
    size_t line = 1; // Size_t that tells the current line being analyzed

    std::string nextLineInFile; // String that stores the next line in the file
    while(std::getline(inputFileStream, nextLineInFile)){
        if (line == 1 && nextLineInFile != "date | value"){
            throw WrongFormatFileException(std::string("First line of csv database should be \"date | value\"."));
        }
        if (line != 1){
            std::vector<std::string> dateAndNumber = split(nextLineInFile, delimiter);
            if (dateAndNumber.size() != 2 || !(validDate(dateAndNumber[0])) || !(validFloat(dateAndNumber[1]))){
				std::cout << "Error: bad input => " << nextLineInFile << std::endl;
				continue;
			}
            float rateFloat;
            std::istringstream rateFloatStream(dateAndNumber[1]);
            rateFloatStream >> rateFloat;
			if (rateFloat < 0){
				std::cout << "Error: not a positive number." << std::endl;
				continue;
			} else if (rateFloat > 1000){
				std::cout << "Error: too large a number." << std::endl;
				continue;
			}
			// Check for the date in the map or the one imediately before
			std::map<std::string, float>::iterator foundDateIterator = exchangeRates.lower_bound(dateAndNumber[0]);
            //DEBUG std::cout << "Date: " << dateAndNumber[0] << " | Number: " << dateAndNumber[1] << std::endl;
			if (foundDateIterator->first == dateAndNumber[0]){
				// Date was found, use it
				std::cout << dateAndNumber[0] << " => " << dateAndNumber[1] << " = " << rateFloat * (foundDateIterator->second) << std::endl;
			} else{
				if (foundDateIterator == exchangeRates.begin()){
					// Date was not found and there is no date below that one in the document
					std::cout << "Error: date not found and no date exists below it." << std::endl;
				} else{
					// Date was not found, it points to the one above, so we have to use it--
					foundDateIterator--;
					std::cout << dateAndNumber[0] << " => " << dateAndNumber[1] << " = " << rateFloat * (foundDateIterator->second) << std::endl;
				}
			}
		}
        line++;
    }
	inputFileStream.close();
}
