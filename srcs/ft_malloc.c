/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/20 10:50:07 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

t_zone g_zone[3] = {{0, NULL},
	{0, NULL},
	{0, NULL}};


int		is_new_zone(int index)
{
	if (!g_zone[index].page)
		return (1);
	else
		return (0);
}

void	*new_zone(size_t index, size_t alloc_size)
{
	int			zone_size;
	t_block		*p;

	zone_size = 0;
	if (index == 0)
		zone_size = TINY;
	else if (index == 1)
		zone_size = SMALL;
	g_zone[index].page = mmap(NULL, zone_size * getpagesize(), PROT_WRITE | PROT_READ,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	ft_bzero(g_zone[index].page, sizeof(t_page));
	g_zone[index].total_size = zone_size;
	p = (t_block *)((t_page*)g_zone[index].page + 1);
	p->size = alloc_size;
	p->nxt = (t_block *)((char *)p + alloc_size);
	ft_bzero(p->nxt, sizeof(t_page));
	return (p + 1);
}

void	*check_zone(int alloc_size)
{
//	else if (alloc_size > TINY && alloc_size <= SMALL && is_new_zone(1))
//		new_zone(1, alloc_size);
//	else if (alloc_size > SMALL)
//		new_zone(3, alloc_size);
//if (alloc_size <= TINY && is_new_zone(0))
		return (new_zone(0, alloc_size));
}

void	*ft_malloc(size_t alloc_size)
{
	return (check_zone(alloc_size));
}
