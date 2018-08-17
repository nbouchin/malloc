#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone g_zone[3] = {{0, NULL, NULL},
					{0, NULL, NULL},
					{0, NULL, NULL}};

/*
**	Create a new generic page and init the first free node.
*/

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

/*
**	Fill a block informations and set his status.
*/

void		fill_block(t_block **p, t_block *next, size_t block_size, int status)
{
	(*p)->size = block_size;
	(*p)->is_free = status;
	(*p)->nxt = next;
}

/*
**	Create a new memory zone according to the asked zone type.
*/

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

/*
**	Run through pages block to get a free block.
*/

t_block	*search_free_block(t_page *page, size_t alloc_size)
{
	t_block *p;

	p = NULL;
	while (page)
	{
		p = (t_block *)(page + 1);
		while (p)
		{
			if (p->is_free && alloc_size <= p->size)
				return (p);
			p = p->nxt;
		}
		page = page->nxt;
	}
	return (NULL);
}

/*
**	Compute the allocation offset and return new allocation size.
*/

size_t	get_offset(size_t alloc_size, int offset)
{
	return (alloc_size = (alloc_size + (offset - 1)) & ~(offset - 1));
}

/*
**	Relink a new non-free block, with the old free block and the old free block next block.
*/

t_block	*relink_block(t_block *block, size_t alloc_size, size_t offset)
{
	t_block *backup;
	size_t	old_size;

	if (block->nxt)
	{
		old_size = block->size;
		backup = block->nxt;
		fill_block(&block, block + get_offset(block->size, offset), alloc_size, 0);
		fill_block(&block->nxt, backup, get_offset(old_size, offset)
		- get_offset(block->size, offset), 1);
		return (block);
	}
	else
	{
		old_size = block->size;
		fill_block(&block, block + get_offset(block->size, offset), alloc_size, 0);
		fill_block(&block->nxt, NULL, get_offset(old_size, offset) - get_offset(block->size, offset), 1);
		return (block);
	}
}

/*
**	Tiny allocation general runtime.
*/

void	*tiny_allocation(alloc_size)
{
	t_block	*block;
	t_page	*page;

	page = NULL;
	new_zone(alloc_size, 0);
	block = search_free_block(g_zone[0].page, alloc_size);
	if (block)
		block = relink_block(block, alloc_size, 16);
	else
	{
		page = new_page(TINY);
		block = ((t_block *)page) + 1;
	}
	return (block);
}

/*
**	Run allocation runtime according the allocation size request.
*/

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
