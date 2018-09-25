/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 08:31:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 12:29:29 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

/*
**	Large allocation free runtime.
*/

void	large_free(void *ptr)
{
	t_block		*p;
	t_page		*page;
	t_page		*prev;

	page = NULL;
	prev = NULL;
	p = NULL;
	page = g_zone[2].page;
	while (page)
	{
		if (((t_block *)(page + 1) + 1) == ptr)
		{
			p = (t_block *)(page + 1);
			delete_page(p, &page, &prev, 2);
			return ;
		}
		prev = page;
		page = page->nxt;
	}
}

/*
**	Tiny and small allocation free runtime.
*/

void	tiny_small_free(void *ptr, int i)
{
	t_block		*p;
	t_page		*page;
	t_page		*prev;

	p = NULL;
	prev = NULL;
	page = g_zone[i].page;
	while (page)
	{
		if ((char*)ptr >= (char*)(page)
		&& (char*)ptr <= (char*)(page) + ret_nbr(i, 0))
		{
			p = (t_block *)((page) + 1);
			if (defrag(&p, ptr, ret_nbr(i, 1)))
				delete_page(p, &page, &prev, i);
			return ;
		}
		prev = (page);
		page = page->nxt;
	}
}

void	ft_free(void *ptr)
{
	int		i;

	i = get_page_type(ptr);
	if (ptr == 0)
		return ;
	if (i < 2)
		tiny_small_free(ptr, i);
	else
		large_free(ptr);
	return ;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
