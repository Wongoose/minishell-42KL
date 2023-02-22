NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
READLINE	= -lreadline

DSRCS		= src/
DOBJS		= objs/

ODIRS		= ${subst ${DSRCS}, ${DOBJS}, $(shell find src -type d)}

FILES		= main utils/signal
FSRCS		= $(addprefix $(DSRCS), ${addsuffix .c, ${FILES}})
FOBJS		= ${subst ${DSRCS}, ${DOBJS}, $(FSRCS:.c=.o)}
# FOBJS		= $(addprefix $(DOBJS), ${addsuffix .o, ${FILES}})

LIBD		= libft
LIBA		= libft.a

all:
	@mkdir -p ${ODIRS}
	@make ${NAME}

$(DOBJS)%.o: ${DSRCS}%.c
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${LIBD}/${LIBA} ${FOBJS}
	@${CC} ${CFLAGS} ${FOBJS} ${LIBD}/${LIBA} ${READLINE} -o ${NAME}

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