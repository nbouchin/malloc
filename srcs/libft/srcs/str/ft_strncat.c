/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:08:58 by nbouchin          #+#    #+#             */
/*   Updated: 2016/11/10 15:29:51 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	if (n == 0)
		return (s1);
	if (n)
	{
		while (s1[j] != '\0')
			j++;
		while (i < n && s2[i] != '\0')
		{
			s1[j] = s2[i];
			i++;
			j++;
		}
	}
	s1[j] = '\0';
	return (s1);
}
