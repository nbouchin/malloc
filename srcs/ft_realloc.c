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

void	*calloc(size_t count, size_t size)
{
	void	*p;

	p = ft_malloc(count * size);
	bzero(p, count * size);
	return (p);
}

void	*malloc(size_t alloc_size)
{
	return (ft_malloc(alloc_size));
}

void	free(void *tofree)
{
	ft_free(tofree);
}

void    *ft_rerealloc(void *ptr, size_t size)
{
    if (!ptr)
        return (ft_malloc(size));

    t_block    *old = (t_block *)ptr - 1;

    if (old->size >= size)
        return (ptr);

    void    *newp = ft_malloc(size);

    if (newp == 0)
        return (0);
    ft_bzero(newp, size);
    ft_memcpy(newp, ptr, old->size);
    return (newp);
}

void	*realloc(void *ptr, size_t size)
{
	return(ft_rerealloc(ptr, size));
}
