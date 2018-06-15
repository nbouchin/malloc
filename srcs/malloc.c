/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/15 13:51:28 by nbouchin         ###   ########.fr       */
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

void		init_page(int size, int	index)
{
	if (!g_page[index].current)
		g_page[index].current = mmap(NULL, size, PROT_WRITE | PROT_READ,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	else
		free_list_itter(g_page[index].free_list, *print_size);
}

void		get_alloc_size(int size)
{
	if (size <= TINY)
		init_page(N, 0);
	else if (size > TINY && size <= SMALL)
		init_page(M, 1);
	else if (size > SMALL)
		init_page(size, 2);
}

void		*malloc(size_t size)
{
	get_alloc_size(size);
	init_new_block();
	update_free_list();
}
