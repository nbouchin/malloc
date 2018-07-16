/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/07/04 13:02:05 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone g_zone[3] = {{0, NULL, NULL},
	{0, NULL, NULL}, {0, NULL, NULL}};

int		no_place(t_block *p, size_t alloc_size)
{
	if (p->size >= alloc_size && p->is_free)
		return (0);
	return (1);
}

int		init_zone(int index, size_t zone_size)
{
	t_block	*p;

	p = NULL;
	if (!g_zone[index].total_size)
	{
		g_zone[index].page = mmap(NULL, zone_size, PROT_WRITE | PROT_READ,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_bzero(g_zone[index].page, sizeof(t_page));
		g_zone[index].total_size = zone_size;
		g_zone[index].page->size = zone_size - sizeof(t_page *);
		g_zone[index].page->nxt = NULL;
		g_zone[index].last = g_zone[index].page;
		p = ((t_block *)g_zone[index].page) + 1;
		p->is_free = 1;
		p->nxt = NULL;
		p->size = g_zone[index].page->size - sizeof(t_block *);
		return (1);
	}
	return (0);
}

void	create_free_node(t_block *p, t_page *page, size_t alloc_size)
{
	if (!p->nxt)
	{
		p->nxt = (t_block *)((char *)(p + 1) + alloc_size);
		p->nxt->size = ((char*)page + page->size) - (char *)(p->nxt + 1);
		p->nxt->is_free = 1;
	}
}

void	alloc_next(t_page **page, size_t zone_size, t_block **p, int index)
{
		(*page)->nxt = mmap(NULL, zone_size, PROT_WRITE | PROT_READ,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		g_zone[index].total_size += zone_size;
		(*page)->nxt->size = zone_size - sizeof(t_page);
		(*page)->nxt->nxt = NULL;
		(*p) = (t_block *)((*page)->nxt + 1);
}


void	find_place(t_page **page, t_block **p, size_t alloc_size)
{
	while ((*page))
	{
		(*p) = (t_block *)((*page) + 1);
		while (no_place((*p), alloc_size))
			(*p) = (*p)->nxt;
		if (!no_place((*p), alloc_size))
			break ;
		(*page) = (*page)->nxt;
	}
}

void	*new_zone(size_t index, size_t alloc_size, size_t zone_size)
{
	t_block		*p;
	t_page		*page;
	int			fzone;

	fzone = 1;
	p = NULL;
	fzone = init_zone(index, zone_size);
	if (alloc_size >= LARGE)
	{
		page = g_zone[index].last;
		p = (t_block *)page + 1;
	}
	else
	{
		page = g_zone[index].page;
		find_place(&page, &p, alloc_size);
	}
	if (((char *)(p + 1) + alloc_size + sizeof(t_block *) >= (char *)(page + 1)
		 + zone_size && index != 2) || (index == 2 && fzone == 0))
	{
		alloc_next(&page, zone_size, &p, index);
		if ((char *)(p + 1) + alloc_size
				+ sizeof(t_page) >= (char *)(page + 1) + zone_size && index != 2)
			g_zone[index].last = page;
		else if (index == 2 && fzone == 0)
			g_zone[index].last = page->nxt;
	}
	p->is_free = 0;
	p->size = alloc_size;
	(alloc_size < LARGE) ?  create_free_node(p, page, alloc_size) : 0;
	return (p + 1);
}

size_t	get_offset(size_t alloc_size, int offset)
{
	return (alloc_size = (alloc_size + (offset - 1)) & ~(offset - 1));
}

void	*check_zone(size_t alloc_size)
{
	if (alloc_size <= TINY)
		return (new_zone(0, get_offset(alloc_size, 16), N));
	else if (alloc_size >= TINY + 1 && alloc_size < SMALL)
		return (new_zone(1, get_offset(alloc_size, 512), M));
	else if (alloc_size >= LARGE)
		return (new_zone(2, alloc_size, alloc_size + sizeof(t_block) + sizeof(t_page)));
	return (0);
}

void	*ft_malloc(size_t alloc_size)
{
	return (check_zone(alloc_size));
}
