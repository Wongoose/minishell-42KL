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
FLAGS		= -c -Wall -Wextra -Werror
INCLUDES	= ./includes

SRCS		= ft_printf.c ft_putchar.c ft_puthex.c ft_putnbr.c ft_putptr.c ft_putstr.c ft_putunsigned.c
OBJS		= ${SRCS:.c=.o}

$(NAME):	${OBJS}
	${CC} ${FLAGS} -I${INCLUDES} ${SRCS}
	ar -rcs ${NAME} ${OBJS}

all:		${NAME}

clean:
	rm -rf ${OBJS}

fclean:		clean
	rm -rf ${NAME}

re:			fclean all