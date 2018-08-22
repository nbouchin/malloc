/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:30 by nbouchin          #+#    #+#             */
/*   Updated: 2018/07/20 15:20:23 by nbouchin         ###   ########.fr       */
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
# define	N			488  * getpagesize()
# define	M			3906 * getpagesize()

typedef struct		s_block
{
	char			is_free;
	size_t			size;
	struct s_block	*nxt;
	int				pad;
}					t_block;

typedef	struct		s_page
{
	size_t			size;
	struct s_page	*nxt;
	int				pad[3];
}					t_page;

typedef	struct		s_zone
{
	size_t			total_size;
	t_page			*page;
	t_page			*last;
}					t_zone;

extern t_zone		g_zone[3];

void				ft_free(void *ptr);
void				*ft_malloc(size_t size);
void				ft_test();
//void				*ft_realloc(void *ptr, size_t size);

#endif
