/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:30 by nbouchin          #+#    #+#             */
/*   Updated: 2017/11/14 17:09:03 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <unistd.h>
# include <pthread.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include "../srcs/libft/includes/libft.h"

/*
**	define malloc size
*/

# define	TINY		7936
# define	SMALL		1040384
# define	LARGE		1040384
# define	N			16777216
# define	M			134217728

typedef struct			s_struct
{
	size_t				start;
	size_t				end;
	struct s_struct		*next;
}						t_struct;

t_struct				*g_memory;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

#endif
