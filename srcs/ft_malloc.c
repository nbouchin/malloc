/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/22 15:01:13 by nbouchin         ###   ########.fr       */
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
		g_zone[index].page = mmap(NULL, zone_size, PROT_WRITE | PROT_READ,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_bzero(g_zone[index].page, sizeof(t_page));
		g_zone[index].total_size = zone_size;
		g_zone[index].page->size = zone_size;
	}
	while (g_zone[index].page->nxt)
	{
		ft_putstr("SALUT");
		g_zone[index].page = g_zone[index].page->nxt;
	}
	p = (t_block *)(g_zone[index].page + 1);
	while (p->nxt)
		p = p->nxt;
	if ((char*)(p + 1) + alloc_size > (char*)(g_zone[index].page + 1) + zone_size)
	{
		g_zone[index].page->nxt = mmap(NULL, zone_size, PROT_WRITE | PROT_READ,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_bzero(g_zone[index].page->nxt, sizeof(t_page));
		g_zone[index].total_size += zone_size;
		g_zone[index].page->nxt->size = zone_size;
		p = (t_block *)(g_zone[index].page->nxt + 1);
	}
	p->size = alloc_size;
	p->nxt = (t_block *)((char *)(p + 1) + alloc_size);
	return (p + 1);
}

size_t	get_offset(size_t alloc_size, int offset)
{
	return (alloc_size = (alloc_size + (offset - 1)) & ~(offset - 1));
}

void	*check_zone(size_t alloc_size)
{
	if (alloc_size >= 1 && alloc_size <= TINY)
		return (new_zone(0, get_offset(alloc_size, 16), N));
	else if (alloc_size >= TINY + 1 && alloc_size <= SMALL)
		return (new_zone(1, get_offset(alloc_size, 512), M));
	else if (alloc_size >= LARGE)
		return (new_zone(2, alloc_size, alloc_size));
	return(0);
}

void	*ft_malloc(size_t alloc_size)
{
	return (check_zone(alloc_size));
}
