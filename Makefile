NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I/usr/local/opt/readline/include
READLINE	= -lreadline -L/usr/local/opt/readline/lib

DSRCS		= src/
DOBJS		= objs/

ODIRS		= ${subst ${DSRCS}, ${DOBJS}, $(shell find src -type d)}

FILES		= main utils/signal functions/func_cd functions/func_echo helper/helper_envp
FSRCS		= $(addprefix $(DSRCS), ${addsuffix .c, ${FILES}})
FOBJS		= ${subst ${DSRCS}, ${DOBJS}, $(FSRCS:.c=.o)}
# FOBJS		= $(addprefix $(DOBJS), ${addsuffix .o, ${FILES}})

LIBD		= libft
LIBA		= libft.a

PRINTFD		= ft_printf
PRINTFA		= libftprintf.a

all:
	@mkdir -p ${ODIRS}
	@make ${NAME}

$(DOBJS)%.o: ${DSRCS}%.c
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${LIBD}/${LIBA} ${PRINTFD}/${PRINTFA} ${FOBJS}
	@${CC} ${CFLAGS} ${FOBJS} ${LIBD}/${LIBA} ${PRINTFD}/${PRINTFA} -o ${NAME} ${READLINE}

${LIBD}/${LIBA}:
	@make -C ${LIBD}

${PRINTFD}/${PRINTFA}:
	@make -C ${PRINTFD}

clean: ${OBJ}
	@make clean -C ${LIBD}
	@make clean -C ${PRINTFD}
	rm -rf ${DOBJS}

fclean: clean
	@make fclean -C ${LIBD}
	@make fclean -C ${PRINTFD}
	rm -rf ${NAME}

re: fclean all

.PHONY:	all clean fclean re