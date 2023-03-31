# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 13:21:38 by zwong             #+#    #+#              #
#    Updated: 2022/08/16 13:31:23 by zwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= gcc
FLAGS		= -Wall -Wextra -Werror

SRCS		= ft_printf.c ft_putchar.c ft_puthex.c ft_putnbr.c ft_putptr.c ft_putstr.c ft_putunsigned.c
OBJS_DIR	= objects/
OBJS		= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all:		${NAME}

$(NAME):	${OBJS}
	@ar rcs ${NAME} ${OBJS}

$(OBJS_DIR)%.o:	%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@${CC} ${FLAGS} -I. -c $< -o $@

clean:
	@rm -rf ${OBJS_DIR}

fclean:		clean
	@rm -rf ${NAME}

re:			fclean all