/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:31 by nbouchin          #+#    #+#             */
/*   Updated: 2017/11/14 14:13:14 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void		*page_reclaim()
{
	void	*page;

	page = mmap(NULL, N, PROT_WRITE | PROT_READ,
	MAP_ANON | MAP_PRIVATE, -1, 0);
	return (page);
}

void		*malloc(size_t size)
{
	static void	*page;
	size_t	prev_end;
	t_struct *node;

	page = NULL;
	node = g_memory;
	if (!g_memory)
	{
		page = page_reclaim();
		g_memory = (t_struct*)mmap(NULL, sizeof(t_struct), PROT_WRITE | PROT_READ,
		MAP_ANON | MAP_PRIVATE, -1, 0);
		g_memory->start = 0;
		g_memory->end = size;
	}
	else
	{
		while (node->next)
			node = node->next;
		prev_end = node->end;
		node->next = (t_struct*)mmap(NULL, sizeof(t_struct), PROT_WRITE | PROT_READ,
		MAP_ANON | MAP_PRIVATE, -1, 0);
		node = node->next;
		node->start = prev_end + 1;
		node->end = prev_end + size;
		node->next = NULL;
	}
	node = g_memory;
	while (node->next)
		node = node->next;
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
	str = malloc(sizeof(char) * 50);
	str2 = malloc(sizeof(char) * 20);
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
	str3 = malloc(sizeof(char) * 20);
	while (i < 20)
	{
		str3[i] = 'C';
		i++;
	}
	str3[i] = '\0';
	printf("\n%s : [%p]\n", str3, str3);
}
