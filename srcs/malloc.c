/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/19 15:17:43 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

t_block	new_block(size_t sze, t_block *nxt, t_block *nxt_free)
{
	t_block	new_block;

	new_block.sze = sze;
	new_block.nxt = nxt;
	new_block.nxt_free = nxt_free;
	return (new_block);
}

int		is_new_zone(int index)
{
	if (!g_zone[index].page)
		return (1);
	else
		return (0);
}

void	new_zone(size_t index, size_t sze)
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

void	update_free_list(int index, size_t sze)
{
	t_block *swap;
	t_block nblock;

	swap = g_zone[index].free_list;
	while (g_zone[index].free_list)
		g_zone[index].free_list = g_zone[index].free_list->nxt;
	nblock = new_block(sze, NULL, NULL);
	g_zone[index].free_list = ft_memcpy(g_zone[index].free_list, &nblock, sze);
	g_zone[index].free_list = swap;

}

void	check_zone(int sze)
{
	if (sze <= TINY && is_new_zone(0))
		new_zone(0, sze);
	else if (sze > TINY && sze <= SMALL && is_new_zone(1))
		new_zone(1, sze);
	else if (sze > SMALL)
		new_zone(3, sze);
	else if (sze <= TINY)
		update_free_list(0, sze);
	else if (sze > TINY && sze <= SMALL)
		update_free_list(1, sze);
}

void	*malloc(size_t sze)
{
	check_zone(sze);
	return (NULL);
}
