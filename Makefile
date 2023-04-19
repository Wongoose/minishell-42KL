NAME		= minishell

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I/usr/local/opt/readline/include
FSANS		= -fsanitize=address -g3
READLINE	= -lreadline -L/usr/local/opt/readline/lib

DSRCS		= src			\
			  src/execution	\
			  src/functions	\
			  src/shared	\
			  src/utils		\
			  src/tokenization	\
			  src/parsing

DOBJS		= objs/

FILES		=	print_start				\
				signal					\
				trim					\
				func_cd					\
				func_echo				\
				func_exit				\
				func_env				\
				func_pwd				\
				func_export				\
				func_export_unset_utils	\
				func_unset				\
				shared_envp				\
				token_main				\
				token_utils				\
				token_tree				\
				parse_main				\
				parse_utils				\
				split_keep_quotes		\
				start					\
				heredoc_handler			\
				wildcard_handler		\
				piping_child			\
				piping_utils			\
				execution				\
				execution_utils			\
				free

FOBJS		= $(addprefix $(DOBJS), $(addsuffix .o, $(FILES:.c=.o)))

vpath %.c $(DSRCS)

# ODIRS		= ${subst ${DSRCS}, ${DOBJS}, $(shell find src -type d)}

# FSRCS		= $(addprefix $(DSRCS), ${addsuffix .c, ${FILES}})
# FOBJS		= ${subst ${DSRCS}, ${DOBJS}, $(FSRCS:.c=.o)}
# FOBJS		= $(addprefix $(DOBJS), ${addsuffix .o, ${FILES}})

LIBD		= libft
LIBA		= libft.a

PRINTFD		= ft_printf
PRINTFA		= libftprintf.a

all:		$(NAME)

$(DOBJS)%.o: %.c
	@mkdir -p objs/
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I. -c $< -o $@

${NAME}:	src/main.c ${LIBD}/${LIBA} ${PRINTFD}/${PRINTFA} ${FOBJS}
	@echo "Compiling: src/main.c"
	@${CC} ${CFLAGS} -I. src/main.c ${FOBJS} ${LIBD}/${LIBA} ${PRINTFD}/${PRINTFA} -o ${NAME} ${READLINE}

${LIBD}/${LIBA}:
	@make -C ${LIBD}

${PRINTFD}/${PRINTFA}:
	@make -C ${PRINTFD}

clean: ${OBJ}
	@make clean -C ${LIBD}
	@make clean -C ${PRINTFD}
	@rm -rf ${DOBJS}

fclean: clean
	@make fclean -C ${LIBD}
	@make fclean -C ${PRINTFD}
	@rm -rf ${NAME}

re: fclean all

.PHONY:	all clean fclean re