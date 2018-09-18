#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone g_zone[3] = {{0, NULL, NULL}, {0, NULL, NULL}, {0, NULL, NULL}};

/*
 **	Fill a block informations and set his status.
 */


void				print_addr_fd(void *addr, int fd)
{
	const char	*digits = "0123456789abcdef";
	size_t		nb;
	char		buffer[100];
	size_t		len;

	len = 0;
	nb = (size_t)addr;
	ft_bzero(buffer, sizeof(buffer));
	ft_putstr_fd("0x", fd);
	if (nb == 0)
		ft_putchar_fd('0', fd);
	while (nb > 0)
	{
		buffer[len++] = digits[(size_t)nb % 16];
		nb /= 16;
	}
	ft_strrev(buffer);
	ft_putstr_fd(buffer, fd);
}

void				print_addr(void *addr)
{
	print_addr_fd(addr, 1);
}


void fill_block(t_block *p, t_block *next, size_t block_size, int state)
{
	p->size = block_size;
	p->nxt = next;
	p->is_free = state;
}

/*
**	Create a new generic page and init the first free node.
*/

t_page *new_page(size_t page_size)
{
	t_block	*p;
	t_page	*page;

	p = NULL;
	page = NULL;
	p = NULL;
	page = NULL;
	page = mmap(NULL, page_size, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	page->size = page_size - sizeof(t_page);
	page->nxt = NULL;
	p = (t_block *)(page + 1);
	fill_block(p, NULL, page->size - sizeof(t_block), 1);
	return (page);
}

/*
 **	Create a new memory zone according to the asked zone type.
 */

void new_zone(size_t zone_size, int zone_type)
{
	if (!g_zone[zone_type].page)
	{
		if (zone_type == 0)
			g_zone[zone_type].page = new_page(N);
		else if (zone_type == 1)
			g_zone[zone_type].page = new_page(M);
		else if (zone_type == 2)
			g_zone[zone_type].page = new_page(zone_size);
		g_zone[zone_type].total_size = g_zone[zone_type].page->size + sizeof(t_page);
		g_zone[zone_type].last = g_zone[zone_type].page;
	}
}

/*
 **	Run through pages block to get a free block.
 */

t_block *search_free_block(t_page **page, size_t alloc_size, int offset)
{
	t_block	*block;
	t_page	*prev;

	block = NULL;
	prev = NULL;
	while (*page)
	{
		prev = *page;
		block = (t_block *)((*page) + 1);
		while (block)
		{
			if ((block->is_free && block->size >= alloc_size + sizeof(t_block) + offset) || (block->is_free && block->size == alloc_size))
				return (block);
			block = block->nxt;
		}
		*page = (*page)->nxt;
	}
	*page = prev;
	return (NULL);
}

/*
 **	Compute the allocation offset and return new allocation size.
 */

size_t get_offset(size_t alloc_size, int offset)
{
	return (alloc_size = (alloc_size + (offset - 1)) & ~(offset - 1));
}

/*
 **	Relink a new non-free block, with the old free block and the old free block next block.
 */

void relink_block(t_block *block, size_t alloc_size, size_t offset)
{
	t_block	*backup;
	size_t	old_size;

	backup = NULL;
	old_size = 0;
	old_size = block->size;
	if (block->nxt)
	{
		backup = block->nxt;
		if (block->size > get_offset(alloc_size, offset))
		{
			fill_block(block, (t_block *)((char *)(block + 1) + get_offset(alloc_size, offset)), alloc_size, 0);
			fill_block(block->nxt, backup, old_size - (get_offset(block->size, offset)), 1);
		}
		else if (block->size == get_offset(alloc_size, offset))
			block->is_free = 0;
	}
	else
	{
		if (block->size > get_offset(alloc_size, offset))
		{
			fill_block(block, (t_block *)((char *)(block + 1) + get_offset(alloc_size, offset)), alloc_size, 0);
			fill_block(block->nxt, NULL, old_size - (get_offset(block->size, offset) + sizeof(t_block)), 1);
		}
		else if (block->size == get_offset(alloc_size, offset))
			block->is_free = 0;
	}
}

/*
 **	Tiny allocation general runtime.
 */

void *tiny_small_allocation(size_t alloc_size, int page_type, int alloc_type)
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
		if (alloc_type == TINY)
			page->nxt = new_page(N);
		else
			page->nxt = new_page(M);
		block = search_free_block(&page->nxt, get_offset(alloc_size, offset), offset);
		relink_block(block, alloc_size, offset);
	}
	return (block + 1);
}

void new_big_block(size_t zone_size, int zone_type)
{
	g_zone[zone_type].last->nxt = new_page(zone_size);
	g_zone[zone_type].total_size = zone_size;
	g_zone[zone_type].last = g_zone[zone_type].last->nxt;
}

/*
 **	Large allocation general runtime.
 */

void *large_allocation(size_t alloc_size)
{
	t_block	*block;
	t_page	**page;

	block = NULL;
	page = NULL;
	if (!(g_zone[2].page))
		new_zone(alloc_size, 2);
	else
		new_big_block(alloc_size, 2);
	page = &(g_zone[2].last);
	block = (t_block *) ((*page) + 1);
	return (block + 1);
}

/*
 **	Run allocation runtime according the allocation size request.
 */

void *ft_malloc(size_t alloc_size)
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
