/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:03:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/12 11:25:31 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_false_realloc(char *buff, int size)
{
	char	*swap;

	swap = ft_strnew(ft_strlen(buff));
	ft_strcpy(swap, buff);
	ft_strdel(&buff);
	buff = ft_strnew(ft_strlen(swap) + size);
	ft_strcpy(buff, swap);
	ft_strdel(&swap);
	return (buff);
}
