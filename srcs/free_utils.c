/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 10:56:55 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 10:57:23 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

/*
**	Memory free and defragmentation.
*/

int		defrag(t_block **p, void *ptr, int offset)
{
	t_block		*prev;

	prev = NULL;
	while ((*p))
	{
		if ((t_block*)((*p)) == (t_block*)ptr - 1)
		{
			(*p)->is_free = 1;
			(*p)->size = get_offset((*p)->size, offset);
			if ((*p)->nxt && (*p)->nxt->is_free)
			{
				(*p)->size += (*p)->nxt->size + sizeof(t_block);
				(*p)->nxt = (*p)->nxt->nxt;
			}
			if (prev && prev->is_free)
			{
				prev->size += (*p)->size + sizeof(t_block);
				prev->nxt = (*p)->nxt;
			}
			return (1);
		}
		prev = (*p);
		(*p) = (*p)->nxt;
	}
	return (0);
}

/*
**	Delete a page if this one is free and rechain linked list.
*/

void	delete_page(t_block *p, t_page **page, t_page **prev, int i)
{
	if (p->size == (*page)->size - sizeof(t_block))
	{
		if (!(*prev) && (*page)->nxt)
			g_zone[i].page = (*page)->nxt;
		else if ((*prev) && (*page)->nxt)
			(*prev)->nxt = (*page)->nxt;
		else if ((*prev) && !(*page)->nxt && (*prev)->nxt)
		{
			(*prev)->nxt = NULL;
			g_zone[i].last = (*prev);
		}
		else
		{
			g_zone[i].last = NULL;
			if (i == 2)
			{
				g_zone[2].page = NULL;
				munmap((*page), (*page)->size + sizeof(t_page));
			}
			return ;
		}
		munmap((*page), (*page)->size + sizeof(t_page));
	}
}

int		ret_nbr(int i, int j)
{
	if (i == 0 && j == 0)
		return (N);
	else if (i == 0 && j == 1)
		return (16);
	else if (i == 1 && j == 0)
		return (M);
	else
		return (512);
}

int		get_page_type(void *ptr)
{
	int			i;
	t_block		*p;
	t_page		*page;
	t_page		*prev;

	i = 0;
	p = NULL;
	page = NULL;
	prev = NULL;
	while (i <= 1)
	{
		page = g_zone[i].page;
		while (page)
		{
			if ((char*)ptr >= (char*)(page)
			&& (char*)ptr <= (char*)(page) + ret_nbr(i, 0))
				return (i);
			prev = (page);
			page = page->nxt;
		}
		i++;
	}
	return (2);
}
