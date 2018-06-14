/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 09:03:40 by nbouchin          #+#    #+#             */
/*   Updated: 2018/06/14 13:38:26 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

void		*update_free_list(void	**address)
{
}

void		*init_new_block(t_page	**page)
{
}

void		*init_new_page(int	page_type)
{
}

int			check_size(size_t size)
{
	if (size <= TINY)
	{

	}
	else if (size > TINY && size <= SMALL)
	{

	}
	else if (size > SMALL)
	{

	}
	
}

void		*malloc(size_t size)
{
	check_size();
	init_new_page();
	init_new_block();
	update_free_list();
}
