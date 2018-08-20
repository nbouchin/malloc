#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone g_zone[3] = {{0, NULL, NULL},
					{0, NULL, NULL},
					{0, NULL, NULL}};

/*
**	Fill a block informations and set his status.
*/

void		fill_block(t_block *p, t_block *next, size_t block_size, int state)
{
	p->size = block_size;
	p->nxt = next;
	p->is_free = state;
}

/*
**	Create a new generic page and init the first free node.
*/

t_page		*new_page(size_t page_size)
{
	t_block	*p;
	t_page	*page;

	page = mmap(NULL, page_size, PROT_WRITE | PROT_READ
				, MAP_ANON | MAP_PRIVATE, -1, 0);
	page->size = page_size - sizeof(t_page);
	page->nxt = NULL;
	p = (t_block *)(page + 1);
	fill_block(p, NULL, page->size - sizeof(t_block), 1);
	page->fblock = p;
	return (page);
}

/*
**	Create a new memory zone according to the asked zone type.
*/

void	new_zone(size_t zone_size, int zone_type)
{
	if (!g_zone[zone_type].page)
	{
		if (zone_type == 0)
			g_zone[zone_type].page = new_page(N);
		else if (zone_type == 1)
			g_zone[zone_type].page = new_page(M);
		else if (zone_type == 2)
			g_zone[zone_type].page = new_page(zone_size);
		g_zone[zone_type].total_size = zone_size;
		g_zone[zone_type].last = g_zone[zone_type].page;
	}
}

/*
**	Run through pages block to get a free block.
*/

t_block	*search_free_block(t_page *page, size_t alloc_size)
{
	while (page)
	{
		while (page->fblock)
		{
			if (alloc_size <= page->fblock->size)
				return (page->fblock);
			page->fblock = page->fblock->nxt;
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

void	update_flist(t_block *to_del, t_block *to_keep, t_page *page, int state)
{
	t_block	*prev;
	t_block	*block;

	prev = NULL;
	block = page->fblock;
	while (block)
	{
		if (block == to_del)
		{
			if (state == 0)
			{
				if (prev)
					prev->nxt = block->nxt;
				else
					block = block->nxt;
			}
			else if (state == 1)
			{
				if (prev)
					prev->nxt = to_keep;
				else
					block = to_keep;
			}
		}
		prev = block;
		block = block->nxt;
	}
}

/*
**	Relink a new non-free block, with the old free block and the old free block next block.
*/

t_block	*relink_block(t_block *block, size_t alloc_size, size_t offset)
{
	t_block *backup;
	size_t	old_size;

	backup = NULL;
	old_size = 0;
	if (block->nxt)
	{
		old_size = block->size;
		backup = block->nxt;
		if (backup->size > alloc_size)
		{
			fill_block(block, block + get_offset(block->size, offset), alloc_size, 0);
			fill_block(block->nxt, backup, get_offset(old_size, offset)
		   - get_offset(block->size, offset), 1);
			update_flist(block, backup, page, 1);
		}
		else
		{
			update_flist(block, block->nxt, page, 0);
			fill_block(block, backup, alloc_size, 0);
		}
	}
	else
	{
		old_size = block->size;
		fill_block(block, block + get_offset(alloc_size, offset), alloc_size, 0);
		fill_block(block->nxt, NULL, get_offset(old_size, offset)
				   - get_offset(block->size, offset), 1);
		update_flist(block, block->nxt, page, 1);
	}
	return (block);
}

/*
**	Tiny allocation general runtime.
*/

void	*tiny_small_allocation(size_t alloc_size, int page_type, int alloc_type)
{
	t_block	*block;
	t_page	*page;
	t_page	*npage;

	page = NULL;
	npage = NULL;
	new_zone(alloc_size, page_type);
	block = search_free_block(g_zone[page_type].page, alloc_size);
	if (block)
		block = relink_block(block, alloc_size, alloc_type);
	else
	{
		if (alloc_type == TINY)
			page = new_page(N);
		else
			page = new_page(M);
		block = ((t_block *)page) + 1;
	}
	return (block);
}

/*
**	Run allocation runtime according the allocation size request.
*/

void	*ft_malloc(size_t alloc_size)
{
	ft_putendl("MALLOC_CALL");
	if (alloc_size <= TINY)
		return (tiny_small_allocation(alloc_size, 0, TINY));
	else if (alloc_size <= SMALL)
		return (tiny_small_allocation(alloc_size, 1, SMALL));
	else if (alloc_size >= LARGE)
		return (0);
	else
		return (0);
}
