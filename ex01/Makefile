NAME = RPN

CPP = c++

FLAGS = -Wall -Wextra -Werror -std=c++98 -g

FILES = RPN.cpp main.cpp

HEADERS = RPN.hpp

all: ${NAME}

${NAME}: ${FILES} ${HEADERS}
	${CPP} ${FLAGS} ${FILES} -o ${NAME}

clean:

fclean:
	rm ${NAME}

re:
	make fclean
	make