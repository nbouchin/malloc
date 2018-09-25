/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 08:34:11 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 11:08:49 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

int		get_value(t_block *block)
{
	int		i;
	int		psize;
	int		offset;
	t_page	*page;

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
	else if (new_size > TINY && new_size <= SMALL && offset == 512)
		return (1);
	else
		return (0);
}

void	*realloc_runtime(void *ptr, size_t new_size)
{
	int		off;
	t_block	*block;
	void	*newp;

	block = (t_block *)ptr - 1;
	off = get_value(block);
	pthread_mutex_unlock(&g_mutex);
	newp = malloc(new_size);
	pthread_mutex_lock(&g_mutex);
	if (check_correct_offset(new_size, off))
	{
		if (block->nxt && block->nxt->is_free)
			fill_block(block, block->nxt->nxt, get_offset(block->size, off)
			+ sizeof(t_block) + block->nxt->size - 1, 1);
		if (block->size > (get_offset(new_size, off) + sizeof(t_block) + off))
		{
			relink_block(block, new_size, off);
			return (block + 1);
		}
		if (get_offset(new_size, off) == block->size)
			return (ptr);
	}
	ft_bzero(newp, new_size);
	ft_memcpy(newp, ptr, block->size);
	return (newp);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_block		*old;

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

void	*realloc(void *ptr, size_t size)
{
	void	*temp;

	pthread_mutex_lock(&g_mutex);
	temp = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (temp);
}
