# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2018/09/25 11:07:26 by nbouchin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME    = 	libft_malloc_$(HOSTTYPE).so
CC      = 	clang
HEADER  = 	includes/
FLAGS   = 	-Wall -Wextra -Werror -g
SRCDIR  = 	srcs/
OBJDIR  = 	objs/
SRC	=	calloc.c	\
		free.c		\
		free_utils.c	\
		malloc.c	\
		malloc_utils.c	\
		show_alloc_mem.c \
		show_alloc_mem_utils.c \
		realloc.c \
		realloc_utils.c \
		general_utils.c

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(SRC:.c=.o))


$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft_malloc.h
	$(CC) -fPIC -o $@ -c $< $(FLAGS) -I $(HEADER)

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	make -C srcs/libft/ all
	$(CC) -shared -fPIC -o $(NAME) $(OBJS) -L srcs/libft -lft 
	ln -sF $(NAME) libft_malloc.so

$(OBJDIR):
	mkdir -p objs objs/srcs

clean:
	rm -rf objs
	make -C srcs/libft/ clean

run: 
	gcc  $(FLAGS) -o my-test tests/my-test.c ./objs/*.o -I ./includes -L ./srcs/libft -lft
	./my-test

fclean: clean
	rm -f libft_malloc.so $(NAME)
	make -C srcs/libft/ fclean

re: fclean all

.PHONY: all clean fclean re
