/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/15 17:34:44 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void	free_list_itter(t_block *free_list, void (*f)(t_block *elem))
{
	while (free_list)
	{
		f(free_list);
		free_list = free_list->nxt;
	}
}

void		init_zone(size_t index, size_t sze)
{
	g_zone[index].page = mmap(NULL, sze, PROT_WRITE | PROT_READ,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	g_zone[index].free_list = ft_memcpy(g_zone[index].free_list,
			g_zone[index].page, sze);
	g_zone[index].free_list->nxt_free = NULL;
	g_zone[index].free_list->sze = sze;
	g_zone[index].free_list->nxt = NULL;
	g_zone[index].total_sze = sze;
	g_zone[index].page->sze = sze;
	g_zone[index].page->nxt = NULL;
}

void		get_alloc_sze(int sze)
{
	if (sze <= TINY)
		init_zone(N, 0);
	else if (sze > TINY && sze <= SMALL)
		init_zone(M, 1);
	else if (sze > SMALL)
		init_zone(sze, 2);
}

void		*malloc(size_t sze)
{
	get_alloc_sze(sze);
}
