/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:31 by nbouchin          #+#    #+#             */
/*   Updated: 2017/11/14 16:21:46 by nbouchin         ###   ########.fr       */
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
	else
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
	char	*str2;
	char	*str3;

	i = 0;
	str = malloc(sizeof(char) * 800);
	while (i < 50)
	{
		str[i] = 'A';
		i++;
	}
	str[i] = '\0';
	printf("\n%s : [%p]\n", str, str);
	i = 0;
	str2 = malloc(sizeof(char) * 12);
	while (i < 12)
	{
		str2[i] = 'B';
		i++;
	}
	str2[i] = '\0';
	printf("\n%s : [%p]\n", str2, str2);
	i = 0;
	str3 = malloc(sizeof(char) * 800);
	while (i < 800)
	{
		str3[i] = 'C';
		i++;
	}
	str3[i] = '\0';
	printf("\n%s : [%p]\n", str3, str3);
}
