/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */ /*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:30 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 11:09:06 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H
# define _GNU_SOURCE

# include <unistd.h>
# include <stdint.h>
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

# define TINY	992
# define SMALL	127000
# define LARGE	127000
# define N		488  * getpagesize()
# define M		3906 * getpagesize()

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

extern t_zone			g_zone[3];
extern pthread_mutex_t	g_mutex;

void				print_addr_fd(const void *addr, int fd);
void				print_addr(const void *addr);
void				print_page(const t_page *page, int i);
void				print_octets(t_block *p);
void				print_total(int total);
void				free(void *ptr);
void				ft_free(void *ptr);
void				*malloc(size_t size);
void				*ft_malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();
void				fill_block(t_block *p, t_block *next,
					size_t block_size, int state);
size_t				get_offset(size_t alloc_size, int offset);
void				relink_block(t_block *block, size_t alloc_size,
					size_t offset);
void				fill_block(t_block *p, t_block *next,
					size_t block_size, int state);
t_page				*new_page(size_t page_size);
void				new_zone(size_t zone_size, int zone_type);
t_block				*search_free_block(t_page **page, size_t alloc_size,
					int offset);
void				relink_block(t_block *block, size_t alloc_size,
					size_t offset);
size_t				get_offset(size_t alloc_size, int offset);
int					defrag(t_block **p, void *ptr, int offset);
void				delete_page(t_block *p, t_page **page, t_page **prev,
					int i);
int					ret_nbr(int i, int j);
int					get_page_type(void *ptr);
int					exists(const t_block *p, void *ptr);
int					ret_offset(int i);
int					ret_psize(int i);
int					search_block(void *ptr);
void				*ft_calloc(size_t count, size_t size);
void				*calloc(size_t count, size_t size);


#endif
