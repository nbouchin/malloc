#!/bin/bash

cd ./check
sed -n '15,15p' ft_isalnum.c
sed -n '15,15p' ft_isalpha.c
sed -n '15,15p' ft_isascii.c
sed -n '15,15p' ft_isdigit.c
sed -n '15,15p' ft_islower.c
sed -n '15,15p' ft_isprint.c
sed -n '15,15p' ft_isspace.c
sed -n '15,15p' ft_isupper.c
cd ..

cd ./conv
sed -n '15,15p' convert_to_list.c
sed -n '15,15p' ft_atoi.c
sed -n '15,15p' ft_itoa.c
sed -n '15,15p' ft_printitoabase.c
sed -n '15,15p' ft_tolower.c
sed -n '15,15p' ft_toupper.c
cd ..

cd ./get_next_line
sed -n '15,15p' get_next_line.c
cd ..

cd ./lst
sed -n '15,15p' ft_delete_node.c
sed -n '15,15p' ft_lstadd.c
sed -n '15,15p' ft_lstaddend.c
sed -n '15,15p' ft_lstdel.c
sed -n '15,15p' ft_lstdelone.c
sed -n '15,15p' ft_lstiter.c
sed -n '15,15p' ft_lstmap.c
sed -n '15,15p' ft_lstnew.c
cd ..

cd ./mem
sed -n '15,15p' ft_memalloc.c
sed -n '15,15p' ft_memccpy.c
sed -n '15,15p' ft_memchr.c
sed -n '15,15p' ft_memcmp.c
sed -n '15,15p' ft_memcpy.c
sed -n '15,15p' ft_memdel.c
sed -n '15,15p' ft_memmove.c
sed -n '15,15p' ft_memset.c
sed -n '15,15p' ft_realloc.c
cd ..

cd ./num
sed -n '15,15p' ft_bzero.c
sed -n '15,15p' ft_nblen.c
sed -n '15,15p' ft_power.c
cd ..

cd ./put
sed -n '15,15p' ft_putchar.c
sed -n '15,15p' ft_putchar_fd.c
sed -n '15,15p' ft_putendl.c
sed -n '15,15p' ft_putendl_fd.c
sed -n '15,15p' ft_putnbr.c
sed -n '15,15p' ft_putnbr_fd.c
sed -n '15,15p' ft_putstr.c
sed -n '15,15p' ft_putstr_fd.c
cd ..

cd ./str
sed -n '15,15p' ft_charjoin.c
sed -n '15,15p' ft_queuestr.c
sed -n '15,15p' ft_strcat.c
sed -n '15,15p' ft_strchr.c
sed -n '15,15p' ft_strclr.c
sed -n '15,15p' ft_strcmp.c
sed -n '15,15p' ft_strcpy.c
sed -n '15,15p' ft_strdel.c
sed -n '15,15p' ft_strdup.c
sed -n '15,15p' ft_strequ.c
sed -n '15,15p' ft_striter.c
sed -n '15,15p' ft_striteri.c
sed -n '15,15p' ft_strjoin.c
sed -n '15,15p' ft_strlcat.c
sed -n '15,15p' ft_strlen.c
sed -n '15,15p' ft_strmap.c
sed -n '15,15p' ft_strmapi.c
sed -n '15,15p' ft_strncat.c
sed -n '15,15p' ft_strncmp.c
sed -n '15,15p' ft_strncpy.c
sed -n '15,15p' ft_strnequ.c
sed -n '15,15p' ft_strnew.c
sed -n '15,15p' ft_strnstr.c
sed -n '15,15p' ft_strrchr.c
sed -n '15,15p' ft_strrev.c
sed -n '15,15p' ft_strsplit.c
sed -n '15,15p' ft_strstr.c
sed -n '15,15p' ft_strsub.c
sed -n '15,15p' ft_strtrim.c
cd ..

cd ./tab
sed -n '15,15p' ft_sort_params.c
sed -n '15,15p' ft_tabcpy.c
cd ..
