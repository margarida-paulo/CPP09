NAME = btc

CPP = c++

FLAGS = -Wall -Wextra -Werror -std=c++98 -g

FILES = BitcoinExchange.cpp main.cpp

HEADERS = BitcoinExchange.hpp

all: ${NAME}

${NAME}: ${FILES} ${HEADERS}
	${CPP} ${FLAGS} ${FILES} -o ${NAME}

clean:

fclean:
	rm ${NAME}

re:
	make fclean
	make