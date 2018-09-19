/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:14:12 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/19 17:37:20 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

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
	while (i <= 1)
	{
		psize = (i == 0) ? N : M;
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

//void    *ft_realloc(void *ptr, size_t size)
//{
//	t_block    *old;
//	void    *newp;
//	
//	newp = malloc(size);
//	old = (t_block *)ptr - 1;
//	if (!ptr)
//		return (malloc(size));
//	if (!search_block(ptr))
//		return (0);
//	if (old->size >= size)
//		return (ptr);
//	if (newp == 0)
//		return (0);
//	ft_bzero(newp, size);
//	ft_memcpy(newp, ptr, old->size);
//	return (newp);
//}

int		get_value(t_block *block)
{
	int i;
	int psize;
	t_page *page;

	i = 0;
	psize = 0;
	page = NULL;
	block = NULL;
	while (i <= 1)
	{
		psize = (i == 0) ? N : M;
		page = g_zone[i].page;
		while (page)
		{
			if ((char*)block>= (char*)(page) && (char*)block <= (char*)(page) + psize)
				return (i);
			page = page->nxt;
		}
		i++;
	}
	return (-1);
}

void	*realloc_runtime(t_block *block, size_t new_size)
{
	t_block	*backup;
	size_t	total;
	int		offset;

	total = 0;
	backup = NULL;
	offset = get_value(block);
	if (block->nxt && block->nxt->is_free)
	{
		backup = block->nxt->nxt;
		block->size = get_offset(block->size, offset) + sizeof(t_block) + block->nxt->size;
		block->nxt = block->nxt->nxt;
		total = block->size;
	}
	else
	{
		if (get_offset(block->size, offset) >= new_size)
		{
			block->size = new_size;
			return (block - 1);
		}
		else
		{
			backup = malloc(new_size);
			ft_bzero(backup, new_size);
			ft_memcpy(backup, block, block->size);
			return (backup);
		}
	}
	if (block->size == get_offset(new_size, offset))
	{
		fill_block(block, backup, get_offset(new_size, offset), 0);
		return (block - 1);
	}
	else if ((block->size - get_offset(new_size, offset)) >= sizeof(t_block) + offset)
	{
		fill_block(block, (t_block *)((char *)(block + 1) + get_offset(new_size, offset)), new_size, 0);
		fill_block(block->nxt, backup, total - get_offset(block->size, offset) + sizeof(t_block), 1);
		return (block - 1);
	}
	else
	{
		backup = malloc(new_size);
		ft_bzero(backup, new_size);
		ft_memcpy(backup, block, block->size);
		return (backup);
	}
}

void	*ft_realloc(void *ptr, size_t nsize)
{
	t_block		*newp;
	t_block		*block;

	newp = malloc(nsize);
	block = (t_block *)ptr - 1;
	if (!ptr)
		return (malloc(nsize));
	if (!search_block(ptr) || newp == 0)
		return (0);
	if (block->size >= nsize)
		return (ptr);
	return (realloc_runtime(ptr + 1, nsize));
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
