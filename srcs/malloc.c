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

int			new_zone(int index)
{
	if (!g_zone[index].page)
		return (1);
	else
		return (0);
}

void	init_zone(size_t index, size_t sze)
{
	g_zone[index].page = mmap(NULL, sze, PROT_WRITE | PROT_READ,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	g_zone[index].free_list = ft_memcpy(g_zone[index].free_list,
			g_zone[index].page, sze);
	g_zone[index].free_list->sze = sze;
	g_zone[index].free_list->nxt = NULL;
	g_zone[index].free_list->nxt_free = NULL;
	g_zone[index].total_sze = sze;
	g_zone[index].page->sze = sze;
	g_zone[index].page->nxt = NULL;
}

void	init_big_zone(size_t index, size_t sze)
{
	g_zone[index].total_sze = sze;
	g_zone[index].free_list = NULL;
	g_zone[index].page = mmap(NULL, sze, PROT_WRITE | PROT_READ,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	g_zone[index].page->nxt = NULL;
	g_zone[index].page->sze = 0;
}

void	new_block(size_t index)
{
	t_block *swap;

	swap = g_zone[index].free_list;
	while (swap)
		swap = swap->nxt;
}

void		check_zone(int sze)
{
	if (sze <= TINY && new_zone(0))
		init_zone(0, N);
	else if (sze > TINY && sze <= SMALL && new_zone(1))
		init_zone(1, M);
	else if (sze > SMALL)
		init_big_zone(2, sze);
	else if (sze <= TINY)
		new_block(0);
	else if (sze > TINY && sze <= SMALL)
		new_block(1);
	else if (sze > SMALL)
		new_block(2);
}

void		*malloc(size_t sze)
{
	check_zone(sze);
}
