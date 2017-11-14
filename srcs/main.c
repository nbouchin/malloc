/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:31 by nbouchin          #+#    #+#             */
/*   Updated: 2017/11/14 16:39:56 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void		*get_page(size_t size)
{
	void	*page;

	if (size <= TINY)
		page = mmap(NULL, N, PROT_WRITE | PROT_READ,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (size > TINY && size <= SMALL)
		page = mmap(NULL, M, PROT_WRITE | PROT_READ,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	else if (size > SMALL)
		page = mmap(NULL, size, PROT_WRITE | PROT_READ,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	return (page);
}

t_struct	*init_node(t_struct *node, size_t prev_start, size_t prev_end)
{
	node = (t_struct*)mmap(NULL, sizeof(t_struct),
	PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
	node->start = prev_start;
	node->end = prev_end;
	node->next = NULL;
	return (node);
}
void		*malloc(size_t size)
{
	static void	*page;
	t_struct *node;

	page = NULL;
	node = g_memory;
	if (size > SMALL)
		return (get_page(size));
	if (!g_memory)
	{
		page = get_page(size);
		node = init_node(node, 0, size);
		g_memory = node;
	}
	else
	{
		while (node->next)
			node = node->next;
		node = init_node(node->next, node->end + 1, node->end + size);
	}
	page = mmap(page + node->start, size, PROT_WRITE | PROT_READ,
	MAP_ANON | MAP_PRIVATE, -1, 0);
	return (page + node->start);
}

int			main()
{
	int		i;
	char	*str;

	i = 0;
	while (i < 2115)
	{
		str = malloc(7936);
		i++;
	}
}
