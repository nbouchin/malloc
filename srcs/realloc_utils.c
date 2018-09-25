/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:05:22 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 14:43:52 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

int		exists(const t_block *p, void *ptr)
{
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

int		ret_psize(int i)
{
	int psize;

	psize = 0;
	psize = (i == 0) ? N * getpagesize() : M * getpagesize();
	(i == 2) ? psize = 4096 : 0;
	return (psize);
}

int		search_block(void *ptr)
{
	int				i;
	int				ps;
	const t_page	*page;
	const t_block	*block;

	i = 0;
	ps = 0;
	block = NULL;
	while (i <= 2)
	{
		ps = ret_psize(i);
		page = g_zone[i].page;
		while (page)
		{
			if ((char*)ptr >= (char*)(page) && (char*)ptr <= (char*)(page) + ps)
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
