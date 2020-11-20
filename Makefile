NAME	= minishell

FILED	= fnct_names/functions_david.txt
FILEM	= fnct_names/functions_martin.txt

F_DAVID	= $(shell cat ${FILED})
F_MARTIN = $(shell cat ${FILEM})

SRCS	= $(F_DAVID) $(F_MARTIN)

OBJS	= ${SRCS:.c=.o}

CC	= clang

CFLAGS	= -Wall -Wextra -Werror

DEBUG_FLAGS = -g -g3 -fsanitize=address

.c.o:
	${CC} ${CFLAGS} -c -I includes $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} libft/libft.a -o ${NAME}
	

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
