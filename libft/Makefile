# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 16:26:04 by zwong             #+#    #+#              #
#    Updated: 2022/06/09 16:26:05 by zwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

INCLUDE	= libft.h
SRCS	= ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strcmp.c	\
			ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_swap.c \
			ft_memchr.c ft_memcmp.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_isquote.c

OBJS_DIR= objects/
OBJS	= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS)
	@ar rcs	$(NAME) $(OBJS)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)

fclean:		clean
	@rm -rf $(NAME)

re:			fclean all
