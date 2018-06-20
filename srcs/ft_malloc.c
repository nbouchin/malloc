/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/20 17:59:32 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

t_zone g_zone[3] = {{0, NULL},
	{0, NULL},
	{0, NULL}};

void	*new_zone(size_t index, size_t alloc_size, size_t zone_size)
{
	t_block		*p;

	if (!g_zone[index].total_size)
	{
		ft_putstr("page_size[");// debug
		ft_putnbr(zone_size);// debug
		ft_putstr("]\n");// debug
		g_zone[index].page = mmap(NULL, zone_size, PROT_WRITE | PROT_READ,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_bzero(g_zone[index].page, sizeof(t_page));
		g_zone[index].total_size = N;
		g_zone[index].page->size = N;
	}
	p = (t_block *)(g_zone[index].page + 1);
	p->size = alloc_size;
	p->nxt = (t_block *)((char *)(p + 1) + alloc_size);
	return (p + 1);
}

void	*check_zone(int alloc_size)
{
	if (alloc_size >= 1 && alloc_size <= TINY)
		return (new_zone(0, alloc_size, N));
	else if (alloc_size >= TINY + 1 && alloc_size <= SMALL)
		return (new_zone(1, alloc_size, M));
	else if (alloc_size >= LARGE)
		return (new_zone(2, alloc_size, alloc_size));
	return(0);
}

void	*ft_malloc(size_t alloc_size)
{
	return (check_zone(alloc_size));
}
