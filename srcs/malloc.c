/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2017/11/13 15:31:12 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void		tiny_malloc(size_t size, void **ptr)
{
	(void)size;
	*ptr = mmap(NULL, N, (PROT_WRITE | PROT_READ),
	(MAP_ANON | MAP_PRIVATE), -1, 0);
}

void		small_malloc(size_t size, void **ptr)
{
	(void)size;
	*ptr = mmap(NULL, M, (PROT_WRITE | PROT_READ),
	(MAP_ANON | MAP_PRIVATE), -1, 0);
}

void		*malloc(size_t size)
{
	void	*ptr;

	if (size <= TINY)
		tiny_malloc(size, &ptr);
	else if (size > TINY && size <= SMALL)
		small_malloc(size, &ptr);
	else
		ptr = mmap(NULL, size, (PROT_WRITE | PROT_READ),
		(MAP_ANON | MAP_PRIVATE), -1, 0);
	return (ptr);
}
