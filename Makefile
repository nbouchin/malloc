# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/06/19 15:47:20 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME    = 	libft_malloc_$(HOSTTYPE).so
CC      = 	clang
HEADER  = 	includes/
FLAGS   = 	-Wall -Wextra -Werror
SRCDIR  = 	srcs/
OBJDIR  = 	objs/
SRC		=	free.c		\
			malloc.c	\
			realloc.c

DEPS        = libft_malloc.h

%.o: %.c $(DEPS)
	$(CC) -fPIC -c -o $@ $< $(FLAGS) -I libft/includes

all: $(NAME)

$(NAME): $(SOURCES:.c=.o)
	make -C srcs/libft/
	$(CC) -fPIC -shared -o $(NAME) $(SOURCES:.c=.o) -L srcs/libft -lft
	ln -F -f -s $(NAME) libft_malloc.so

clean:
	rm -rf objs
	make -C srcs/libft/ clean

fclean: clean
	rm -f libft_malloc.so $(NAME)
	make -C srcs/libft/ fclean

re: fclean all

.PHONY: all clean fclean re
