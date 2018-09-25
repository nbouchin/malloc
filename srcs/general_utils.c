/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 10:46:59 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 10:47:11 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

/*
**	Compute the allocation offset and return new allocation size.
*/

size_t	get_offset(size_t alloc_size, int offset)
{
	return (alloc_size = (alloc_size + (offset - 1)) & ~(offset - 1));
}
