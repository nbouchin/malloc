/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:30 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/19 15:17:09 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H
# define _GNU_SOURCE

# include <unistd.h>
# include <pthread.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include "../srcs/libft/includes/libft.h"

/*
**	define malloc size
*/

/*
**	TINY
**
**	Allocation size 		: from 1 byte to 992 bytes;
**	Allocation resolution 	: 16 bytes;
**	Region size 			: 2MB
*/

/*
**	SMALL
**
**	Allocation size 		: from 993 bytes to 127KB;
**	Allocation resolution 	: 512 bytes;
**	Region size				: 16MB
*/

/*
**	LARGE
**
**	Allocation size 		: 127KB or greater;
**	Allocation resolution 	: 4KB
**	Region size				: N/A
*/

# define	TINY		992
# define	SMALL		127000
# define	LARGE		127000
# define	N			2000000
# define	M			16000000

typedef struct	s_block
{
	size_t		sze;
	struct s_block		*nxt;
	struct s_block		*nxt_free;
}				t_block;

typedef	struct	s_page
{
	size_t		sze;
	struct s_page		*nxt;
}				t_page;

typedef	struct	s_zone
{
	size_t		total_sze;
	t_block		*free_list;
	t_page		*page;
}				t_zone;

extern t_zone			g_zone[3];

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

#endif
