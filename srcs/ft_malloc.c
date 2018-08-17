/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:56:29 by nbouchin          #+#    #+#             */
/*   Updated: 2018/08/14 16:21:11 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone g_zone[3] = {{0, NULL, NULL},
	{0, NULL, NULL}, {0, NULL, NULL}};

/*
**	Check if a block can be allocated on a free block.
*/

int		is_place(t_block *p, size_t alloc_size)
{
//	dprintf(2, "%p, %lu, %d\n", p, p->size, p->is_free);
//	ft_putnbr(p->size);
//	ft_putstr(" - ");
//	ft_putnbr(alloc_size);
//	ft_putstr(" - ");
//	ft_putnbr(p->is_free);
//	ft_putendl("");
	if (p->size >= alloc_size && p->is_free)
	{
//		ft_putendl("FIND_FREE_BLOCK");
		return (1);
	}
	return (0);
}

/*
**	Create a zone.
*/

int		init_zone(int malloc_type, size_t zone_size)
{
	t_block	*p;

	p = NULL;
	if (!g_zone[malloc_type].total_size)
	{
		g_zone[malloc_type].page = mmap(NULL, zone_size, PROT_WRITE | PROT_READ
										, MAP_ANON | MAP_PRIVATE, -1, 0);
		//ft_bzero(g_zone[malloc_type].page, sizeof(t_page));
		g_zone[malloc_type].total_size = zone_size;
		g_zone[malloc_type].page->size = zone_size - sizeof(t_page *);
		g_zone[malloc_type].page->nxt = NULL;
		g_zone[malloc_type].last = g_zone[malloc_type].page;
		p = ((t_block *)g_zone[malloc_type].page) + 1;
		p->is_free = 1;
		p->nxt = NULL;
		p->size = g_zone[malloc_type].page->size - sizeof(t_block *);
		return (1);
	}
	return (0);
}

/*
**	Create free node on a given page.
**	The free node size equals to the actual block to the end of the zone.
*/

void	create_free_node(t_block **p, size_t alloc_size, size_t old_block_size)
{
	if ((*p)->nxt)
	{
		(*p)->nxt = (t_block *)((char *)((*p) + 1) + alloc_size);		
		(*p)->nxt->size = old_block_size - alloc_size;
		(*p)->nxt->is_free = 1;
	}
}

/*
**	Create a new page that whill be added at
**	the end of the current page type list.
*/

void	alloc_next_zone(t_page **page, size_t zone_size
		, t_block **p, int malloc_type)
{
	(*page)->nxt = mmap(NULL, zone_size, PROT_WRITE | PROT_READ,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	g_zone[malloc_type].total_size += zone_size;
	(*page)->nxt->size = zone_size - sizeof(t_page);
	(*page)->nxt->nxt = NULL;
	(*p) = (t_block *)((*page)->nxt) + 1;
	dprintf(2, "%p - %p\n", (*page)->nxt, (*p));
	(*p)->is_free = 1;
	(*p)->nxt = NULL;
	(*p)->size = g_zone[malloc_type].page->size - sizeof(t_block *);

}

/*
**	Browse blocks while it finds a free block.
*/

int		find_free_block(t_page **page, t_block **p, size_t alloc_size)
{
	t_page *pswap;

	pswap = NULL;
	while ((*page))
	{
		(*p) = (t_block *)((*page) + 1);
		while ((*p))
		{			
			if (is_place((*p), alloc_size))
				return (1);
			(*p) = (*p)->nxt;
		}
		pswap = (*page);
		(*page) = (*page)->nxt;
	}
	(*page) = pswap;
	return (0);
}

/*
**	get the block and page position. 
*/

int		get_position(size_t alloc_size, t_page **page
		, int malloc_type, t_block **p)
{
	if (alloc_size >= LARGE)
	{
		(*page) = g_zone[malloc_type].last;
		(*p) = (t_block *)(*page) + 1;
	}
	else
	{
		(*page) = g_zone[malloc_type].page;
		return (find_free_block(page, p, alloc_size));
	}
	return (0);
}

/*
**	Run malloc core.
*/

void	*malloc_core(size_t malloc_type, size_t alloc_size, size_t zone_size)
{
	t_block		*p;
	t_page		*page;
	int			fzone;
	int			is_free_block;
	size_t		old_block_size;

	p = NULL;
	old_block_size = 0;
	
	fzone = init_zone(malloc_type, zone_size);
	is_free_block = get_position(alloc_size, &page, malloc_type, &p);
	if (!is_free_block)
	{
//		ft_putendl("NEW_PAGE");
		alloc_next_zone(&page, zone_size, &p, malloc_type);
		if (malloc_type == 2 && !fzone)
			g_zone[malloc_type].last = page->nxt;
		else
			g_zone[malloc_type].last = page;
	}
	old_block_size = p->size;
	p->is_free = 0;
	p->size = alloc_size;
	(alloc_size < LARGE) ? create_free_node(&p, alloc_size, old_block_size) : 0;
	return (p + 1);
}

/*
**	Compute block new size according to the given offset.
*/

size_t	get_offset(size_t alloc_size, int offset)
{
	return (alloc_size = (alloc_size + (offset - 1)) & ~(offset - 1));
}

/*
**	Check allocation type according given size.
*/

void	*get_allocation_type(size_t alloc_size)
{
	if (alloc_size <= TINY)
		return (malloc_core(0, get_offset(alloc_size, 16), N));
	else if (alloc_size <= SMALL)
		return (malloc_core(1, get_offset(alloc_size, 512), M));
	else if (alloc_size >= LARGE)
		return (malloc_core(2, alloc_size,
		(alloc_size + sizeof(t_block) + sizeof(t_page))));
	else
		return (0);
}

void	*ft_malloc(size_t alloc_size)
{
//	ft_putendl("ALLOCATION_CALL");
	return (get_allocation_type(alloc_size));
}
