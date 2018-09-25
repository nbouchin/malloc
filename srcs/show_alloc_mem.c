/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 08:37:29 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 10:28:21 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

int			run_through_pages(int i)
{
	const t_page	*page;
	t_block			*p;
	size_t			total;

	total = 0;
	page = NULL;
	p = NULL;
	page = g_zone[i].page;
	while (page)
	{
		print_page(page, i);
		p = (t_block *)(page + 1);
		while (p)
		{
			total += p->size;
			print_octets(p);
			p = p->nxt;
		}
		page = page->nxt;
	}
	return (total);
}

void		show_alloc_mem(void)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i <= 2)
	{
		total += run_through_pages(i);
		i++;
	}
	print_total(total);
}
