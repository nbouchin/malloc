# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/27 13:56:26 by nbouchin          #+#    #+#              #
#    Updated: 2017/11/13 16:24:10 by nbouchin         ###   ########.fr        #
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

all: $(OBJDIR) $(NAME)
	@Make -C srcs/libft/ all

INDEX = 0

$(NAME): $(OBJS)
	@$(CC) -shared -o $(NAME) $(SRCS)
	@ln -s $(NANE) libft_malloc.so
	@echo "\nCompilation done for libft_malloc.so\n"

$(OBJDIR):
	@mkdir -p objs objs/srcs

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)libft_malloc.h
	@$(CC) -o $@ -c $< $(FLAGS) -I $(HEADER)
	$(eval INDEX=$(shell printf "%d" $$(($(INDEX)+1))))
	@printf "[%02d/03] Compiling (C) %s...\n" $(INDEX) $@

clean:
	@rm -rf objs
	@echo "Cleaning objects..."
	@make -C srcs/libft/ clean

fclean: clean
	@rm -f libft_malloc.so $(NAME)
	@echo "Cleaning binaries..."
	@make -C srcs/libft/ fclean

re: fclean all

.PHONY: all clean fclean re
