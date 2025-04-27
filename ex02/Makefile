NAME = PmergeMe

CPP = c++

FLAGS = -Wall -Wextra -Werror -std=c++98 -g

FILES = PmergeMe.cpp main.cpp

HEADERS = PmergeMe.hpp

all: ${NAME}

${NAME}: ${FILES} ${HEADERS}
	${CPP} ${FLAGS} ${FILES} -o ${NAME}

clean:

fclean:
	rm ${NAME}

re:
	make fclean
	make