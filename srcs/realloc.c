#include "../includes/libft_malloc.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	bzero(p, count * size);
	return (p);
}

int	exists(t_block *p, void *ptr)
{
	t_block		*prev;

	prev = NULL;
	while (p)
	{
		if ((t_block*)(p) == (t_block*)ptr - 1)
			return (1);
		p = p->nxt;
	}
	return (0);
}

int	search_block(void *ptr)
{
	int i;
	int psize;
	t_page *page;
	t_block *block;

	i = 0;
	psize = 0;
	page = NULL;
	block = NULL;
	while (i <= 2)
	{
		psize = (i == 0) ? N : M;
		if (i == 2)
			psize = 4096;
		page = g_zone[i].page;
		while (page)
		{
			if ((char*)ptr >= (char*)(page) && (char*)ptr <= (char*)(page) + psize)
			{
				block = (t_block*)((page) + 1);
				if (exists(block, ptr))
					return (1);
			}
			page = page->nxt;
		}
		i++;
	}
	return (0);
}


int		get_value(t_block *block)
{
	int i;
	int psize;
	int	offset;
	t_page *page;

	i = 0;
	psize = 0;
	offset = 0;
	page = NULL;
	while (i <= 1)
	{
		psize = (i == 0) ? N : M;
		page = g_zone[i].page;
		while (page)
		{
			if ((char*)block >= (char*)(page) && (char*)block <= (char*)(page) + psize)
			{
				offset = (i == 0) ? 16 : 512;	
				if (i == 2)
					offset = 4096;
				return (offset);
			}
			page = page->nxt;
		}
		i++;
	}
	return (-1);
}

void	*realloc_runtime(void *ptr, t_block *newp, size_t new_size)
{
	size_t	total;
	int		offset;
	t_block	*backup;
	t_block	*block;

	total = 0;
	block = (t_block *)ptr - 1;
	backup = block->nxt;
	offset = get_value(block);
	if (block->nxt && block->nxt->is_free)
	{
		block->size = get_offset(block->size, offset) + sizeof(t_block) + block->nxt->size;
		block->nxt = block->nxt->nxt;
		backup = block->nxt;
		total = block->size;
	}
	if ((get_offset(new_size, offset) + sizeof(t_block) + offset) >= block->size)
		relink_block(block, new_size, offset);
	else if (get_offset(new_size, offset) == block->size)
		return (ptr);
	ft_bzero(newp, new_size);
	ft_memcpy(newp, ptr, block->size);
	return (newp);
}

void    *ft_realloc(void *ptr, size_t size)
{
	t_block    *old;
	void    *newp;
	
	newp = malloc(size);
	old = (t_block *)ptr - 1;
	if (!ptr)
		return (malloc(size));
	if (!search_block(ptr) || newp == 0)
		return (0);
	if (old->size >= size)
		return (ptr);
	return (realloc_runtime(ptr, newp, size));
}

void	*calloc(size_t count, size_t size)
{
	void	*temp;

	temp = ft_calloc(count, size);
	return (temp);
}

void    *realloc(void *ptr, size_t size)
{
	void	*temp;

	//	pthread_mutex_lock(&g_mutex);
	temp = ft_realloc(ptr, size);
	//	pthread_mutex_unlock(&g_mutex);
	return (temp);
}
