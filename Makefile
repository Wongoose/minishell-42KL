NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
READLINE	= -lreadline
DSRCS		= src/

FILES		= main utils/signal
FSRCS		= $(addprefix $(DSRCS), ${addsuffix .c, ${FILES}})
DOBJS		= objs/
FOBJS		= $(addprefix $(DOBJS), ${addsuffix .o, ${FILES}})

LIBD		= libft
LIBA		= libft.a

all:
	@mkdir -p ${DOBJS}
	@make ${NAME}

$(DOBJS)%.o: ${DSRCS}%.c
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${LIBD}/${LIBA} ${FOBJS}
	@${CC} ${CFLAGS} ${FOBJS} ${READLINE} -L${LIBD} -lft -o ${NAME}

${LIBD}/${LIBA}:
	@make -C ${LIBD}

clean: ${OBJ}
	@make clean -C ${LIBD}
	rm -rf ${DOBJS}

fclean: clean
	@make fclean -C ${LIBD}
	rm -rf ${NAME}

re: fclean all

.PHONY:	all clean fclean re