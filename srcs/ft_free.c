/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:13:59 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/25 15:29:43 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>


int		defrag(t_block **p, void *ptr)
{
	t_block		*prev;
	t_block		*free;

	while ((*p)->nxt)
	{
		if ((char *)(t_block *)((*p) + 1) == (char *)ptr)
		{
			free = (t_block *)ptr - 1;
			if (prev && prev->is_free)
			{
				prev->size += (*p)->size + 16;
				prev->nxt = (*p)->nxt;
				(*p) = prev;
			}
			if ((*p)->nxt->is_free)
			{
				free->size += (*p)->nxt->size + 16;
				free->nxt = (*p)->nxt->nxt;
			}
			free->is_free = 1;
			return (1);
		}
		prev = (*p);
		(*p) = (*p)->nxt;
	}
	return (0);
}

void		ft_free(void *ptr)
{
	t_block		*p;
	t_page		*page;
	int			i;

	i = 0;
	p = NULL;
	while (i <= 1)
	{
		page = g_zone[i].page;
		while (page)
		{
			if ((char*)ptr >= (char*)page &&
					(char*)ptr <= (char*)(page) + (i == 0) ? N : M)
			{
				p = (t_block *)(page + 1);
				if (defrag(&p, ptr))
					return ;
			}
			page = page->nxt;
		}
		i++;
	}
}
