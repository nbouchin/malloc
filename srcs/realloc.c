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
		if ((t_block*)(p + 1) == ptr)
			return (1);
		p = p->nxt;
	}
	return (0);
}

int		ret_offset(int i)
{
	int	offset;

	offset = 0;
	if (i == 0)
		offset = 16;
	else if (i == 1)
		offset = 512;
	else if (i == 2)
		offset = 4096;
	return (offset);
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
		(i == 2) ? psize = 4096 : 0;
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
			if ((char*)block >= (char*)(page) && (char*)block
			<= (char*)(page) + psize)
				return (ret_offset(i));
			page = page->nxt;
		}
		i++;
	}
	return (-1);
}

int		check_correct_offset(size_t new_size, int offset)
{
	if (new_size <= TINY && offset == 16)
		return (1);
	else if(new_size > TINY && new_size <= SMALL && offset == 512)
		return (1);
	else
		return (0);
}

void	*realloc_runtime(void *ptr, size_t new_size)
{
	int		offset;
	t_block	*block;
	void    *newp;

	newp = NULL;
	block = (t_block *)ptr - 1;
	offset = get_value(block);
	pthread_mutex_unlock(&g_mutex);
	newp = malloc(new_size);
	pthread_mutex_lock(&g_mutex);
	if (check_correct_offset(new_size, offset))
	{
		if (block->nxt && block->nxt->is_free)
			fill_block(block, block->nxt->nxt, get_offset(block->size, offset)
			+ sizeof(t_block) + block->nxt->size - 1, 1);
		if (block->size > (get_offset(new_size, offset)
		+ sizeof(t_block) + offset))
		{
			relink_block(block, new_size, offset);
			return (block + 1);
		}
		if (get_offset(new_size, offset) == block->size)
			return (ptr);
	}
	ft_bzero(newp, new_size);
	ft_memcpy(newp, ptr, block->size);
	return (newp);
}

void    *ft_realloc(void *ptr, size_t size)
{
	t_block    *old;

	old = (t_block *)ptr - 1;
	if (!ptr)
	{
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	if (!search_block(ptr))
		return (0);
	if (old->size >= size)
	{
		old->size = size;
		return (ptr);
	}
	return (realloc_runtime(ptr, size));
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

	pthread_mutex_lock(&g_mutex);
	temp = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (temp);
}
