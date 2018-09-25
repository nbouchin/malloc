/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printitoabase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:10:30 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 11:10:41 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printitoabase(uintmax_t nb, char *str, int base)
{
	int	c;

	if (nb / base > 0)
		ft_printitoabase(nb / base, str, base);
	c = nb % base;
	write(1, &str[c], 1);
}
