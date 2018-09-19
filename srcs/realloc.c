/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:14:12 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/19 12:32:40 by nbouchin         ###   ########.fr       */
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
	t_page *page;
	t_block *block;

	i = 0;
	page = NULL;
	block = NULL;
	while (i <= 1)
	{
		page = g_zone[i].page;
		while (page)
		{
			if (i == 0)
			{
				if ((char*)ptr >= (char*)(page) && (char*)ptr <= (char*)(page) + N)
				{
					block = (t_block*)((page) + 1);
					if (exists(block, ptr))
						return (1);
				}
			}
			else if (i == 1)
			{
				if ((char*)ptr >= (char*)(page) && (char*)ptr <= (char*)(page) + M)
				{
					block = (t_block*)((page) + 1);
					if (exists(block, ptr))
						return (1);
				}
			}
			page = page->nxt;
		}
		i++;
	}
	return (0);
}

void    *ft_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return (malloc(size));
	if (!search_block(ptr))
		return (0);

    t_block    *old = (t_block *)ptr - 1;
    if (old->size >= size)
        return (ptr);

    void    *newp = malloc(size);

    if (newp == 0)
        return (0);
    ft_bzero(newp, size);
    ft_memcpy(newp, ptr, old->size);
    return (newp);
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
