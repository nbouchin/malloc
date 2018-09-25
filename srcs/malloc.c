/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 08:28:00 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 12:10:14 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone			g_zone[3] = {{0, NULL, NULL}, {0, NULL, NULL}, {0, NULL, NULL}};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
**	Tiny allocation general runtime.
*/

void	*tiny_small_allocation(size_t alloc_size, int page_type, int alloc_type)
{
	t_block	*block;
	size_t	offset;
	t_page	*page;

	page = NULL;
	block = NULL;
	offset = 0;
	if (alloc_size < 16)
		alloc_size = 16;
	new_zone(alloc_size, page_type);
	page = g_zone[page_type].page;
	offset = (alloc_type == TINY) ? 16 : 512;
	block = search_free_block(&page, get_offset(alloc_size, offset), offset);
	if (block)
		relink_block(block, alloc_size, offset);
	else
	{
		page->nxt = (alloc_type == TINY) ? new_page(N) : new_page(M);
		block = search_free_block(&page->nxt,
		get_offset(alloc_size, offset), offset);
		relink_block(block, alloc_size, offset);
	}
	return (block + 1);
}

void	new_big_block(size_t zone_size, int zone_type)
{
	zone_size += sizeof(t_block) + sizeof(t_page);
	g_zone[zone_type].last->nxt = new_page(zone_size);
	g_zone[zone_type].total_size = get_offset(zone_size, 4096);
	g_zone[zone_type].last = g_zone[zone_type].last->nxt;
}

/*
**	Large allocation general runtime.
*/

void	*large_allocation(size_t alloc_size)
{
	t_block	*block;
	t_page	*page;

	block = NULL;
	page = NULL;
	if (!(g_zone[2].page))
		new_zone(alloc_size, 2);
	else
		new_big_block(alloc_size, 2);
	page = g_zone[2].last;
	block = (t_block *)(page + 1);
	return (block + 1);
}

/*
**	Run allocation runtime according the allocation size request.
*/

void	*ft_malloc(size_t alloc_size)
{
	if (alloc_size <= TINY)
		return (tiny_small_allocation(alloc_size, 0, TINY));
	else if (alloc_size <= SMALL)
		return (tiny_small_allocation(alloc_size, 1, SMALL));
	else if (alloc_size >= LARGE)
		return (large_allocation(alloc_size));
	else
		return (0);
}

void	*malloc(size_t alloc_size)
{
	void	*temp;

	pthread_mutex_lock(&g_mutex);
	temp = ft_malloc(alloc_size);
	pthread_mutex_unlock(&g_mutex);
	return (temp);
}
