SRCS = *.cpp
OBJS = *.o
INCLUDE = ./includes/*.hpp
CC = c++
CFLAGS = -Wall -Wextra -Werror
NAME = computor

all: ${NAME}

${NAME}: ${SRCS} ${INCLUDE}
	${CC} ${CFLAGS} -c ${SRCS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
clean:
	rm -f ${OBJS}
fclean: clean
	rm -f ${NAME}
run: all clean
	clear && ./${NAME}
re : fclean all