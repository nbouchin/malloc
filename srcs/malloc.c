/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/15 17:17:14 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void		*update_free_list()
{
}

void		init_new_block()
{

}

void	print_size(t_block *elem)
{
	printf("%lu", elem->size);
}

void	free_list_itter(t_block *free_list, void (*f)(t_block *elem))
{
	while (free_list)
	{
		f(free_list);
		free_list = free_list->nxt;
	}
}

void		*new_block(size_t size, t_block *nxt, t_block *nxt_free)
{
	t_block	*new_block;

	new_block->size = size;
	new_block->nxt = nxt;
	new_block->nxt_free = nxt_free;
	return (new_block);
}

void		init_zone(size_t index, size_t size)
{
	g_zone[index].page = mmap(NULL, size, PROT_WRITE | PROT_READ,
	MAP_ANON | MAP_PRIVATE, -1, 0);
	g_zone[index].free_list = ft_memcpy(g_zone[index].free_list, g_zone[index].page, size);
	g_zone[index].total_size = size;
	g_zone[index].page->size = size;
	g_zone[index].page->nxt = NULL;
}

void		get_alloc_size(int size)
{
	if (size <= TINY)
		init_zone(N, 0);
	else if (size > TINY && size <= SMALL)
		init_zone(M, 1);
	else if (size > SMALL)
		init_zone(size, 2);
}

void		*malloc(size_t size)
{
	get_alloc_size(size);
	init_new_block();
	update_free_list();
}
