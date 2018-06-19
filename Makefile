# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/06/19 17:12:48 by nbouchin         ###   ########.fr        #
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

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(SRC:.c=.o))


$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft_malloc.h
	$(CC) -o $@ -c $< $(FLAGS) -I $(HEADER)

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	make -C srcs/libft/ all
	$(CC) -shared -fPIC -o $(NAME) $(SRCS) -L srcs/libft -lft 
	ln -s $(NAME) libft_malloc.so

$(OBJDIR):
	mkdir -p objs objs/srcs


clean:
	rm -rf objs
	make -C srcs/libft/ clean

fclean: clean
	rm -f libft_malloc.so $(NAME)
	make -C srcs/libft/ fclean

re: fclean all

.PHONY: all clean fclean re
