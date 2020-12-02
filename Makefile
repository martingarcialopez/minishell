NAME	= minishell

FILED	= fnct_names/functions_david.txt
FILEM	= fnct_names/functions_martin.txt

F_DAVID	= $(shell cat ${FILED})
F_MARTIN = $(shell cat ${FILEM})

SRCS	= $(F_DAVID) $(F_MARTIN)

OBJS	= ${SRCS:.c=.o}

CC	= clang

CFLAGS	= -Wall -Wextra -Werror

DEBUG_FLAGS =  -g -g3 -fsanitize=address

MACOS_MACRO = -D SYNTAX_ERROR=2 -D EXIT_ERROR=255

LINUX_MACRO = -D SYNTAX_ERROR=1 -D EXIT_ERROR=2

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	CFLAGS += $(MACOS_MACRO)
endif
ifeq ($(UNAME),Linux)
	CFLAGS += $(LINUX_MACRO)
endif

.c.o:
	gcc ${DEBUG_FLAGS} ${CFLAGS} -c -I includes $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	make -C libft
	gcc ${DEBUG_FLAGS} ${CFLAGS} ${OBJS} libft/libft.a -o ${NAME}
	

all:	${NAME}

clean:
	make clean -C libft
	rm -f ${OBJS}

fclean:	clean
	make fclean -C libft
	rm -f ${NAME}

re: 	fclean all
