NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -lreadline

SRC		= src/main.c src/signal.c
OBJ		= ${SRC:.c=.o}

LIBFT_DIR	= libft
LIBFT_LIB	= libft.a

${LIBFT_LIB}:
	@make bonus -C ${LIBFT_DIR}

all: ${NAME}

${NAME}:	${LIBFT_LIB} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${LIBFT_DIR}/${LIBFT_LIB} -o ${NAME}

clean: ${OBJ}
	@make clean -C ${LIBFT_DIR}
	rm -rf ${OBJ}

fclean: clean
	@make fclean -C ${LIBFT_DIR}
	rm -rf ${NAME}

re: fclean all