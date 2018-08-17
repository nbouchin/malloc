#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone g_zone[3] = {{0, NULL, NULL},
					{0, NULL, NULL},
					{0, NULL, NULL}};


t_page		*new_page(size_t page_size)
{
	t_block	*p;
	t_page	*page;

	page = mmap(NULL, page_size, PROT_WRITE | PROT_READ
				, MAP_ANON | MAP_PRIVATE, -1, 0);
	page->size = page_size - sizeof(t_page *);
	page->nxt = NULL;
	p = ((t_block *)page) + 1;
	p->is_free = 1;
	p->nxt = NULL;
	p->size = page->size - sizeof(t_block *);
	return (page);
}

//t_block		*new_block(size_t block_size, int status)
//{
//	t_block	*p;
//
//	p = NULL;
//	p->size = block_size;
//	p->is_free = status;
//	return (p);
//}

void	new_zone(size_t zone_size, int zone_type)
{
	if (!g_zone[zone_type].page)
	{
		if (zone_type == 0)
			g_zone[zone_type].page = new_page(TINY);
		else if (zone_type == 1)
			g_zone[zone_type].page = new_page(SMALL);
		else if (zone_type == 2)
			g_zone[zone_type].page = new_page(LARGE);
		g_zone[zone_type].total_size = zone_size;
		g_zone[zone_type].last = g_zone[zone_type].page;
	}
}

t_block	*place_cursor(t_page *page)
{
	t_block *p;

	p = NULL;
	while (page)
	{
		p = (t_block *)(page + 1);
		while (p)
		{
			if (p->is_free)
				return (p);
			p = p->nxt;
		}
		page = page->nxt;
	}
	return (NULL);
}

size_t	get_offset(size_t alloc_size, int offset)
{
	return (alloc_size = (alloc_size + (offset - 1)) & ~(offset - 1));
}

void	*tiny_allocation(alloc_size)
{
	t_block	*cursor;

	new_zone(alloc_size, 0);
	cursor = place_cursor(g_zone[0].page);
	if (cursor)
	{
		cursor->size = alloc_size;
		cursor->is_free = 0;
		cursor->nxt = (t_block *)(char *)((cursor) + 1) + get_offset(alloc_size, 16);
		cursor->nxt->is_free = 1;
	}
	else
	{
		
	}
		
	return (cursor);
}

void	*ft_malloc(size_t alloc_size)
{
	if (alloc_size <= TINY)
		return (tiny_allocation(alloc_size));
	else if (alloc_size <= SMALL)
		return (0);
	else if (alloc_size >= LARGE)
		return (0);
	else
		return (0);
}
