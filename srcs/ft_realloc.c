/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:14:12 by nbouchin          #+#    #+#             */
/*   Updated: 2018/07/04 12:34:55 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void		*ft_realloc(void *ptr, size_t size)
{
	int		i;
	t_block	*p;
	t_page	*page;
	t_page	*prev;

	i = 0;
	p = NULL;
	page = NULL;
	prev = NULL;
	if (!ptr)
		ft_malloc(size);
	while (i <= 1)
		if ((char *)ptr >= (char *)page && (char *)ptr <= (char *)page + (i == 0) ? N : M)
		{
			p = (t_block *)(page + 1);
		}
	return (ptr);
}
