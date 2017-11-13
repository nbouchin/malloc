/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 08:55:31 by nbouchin          #+#    #+#             */
/*   Updated: 2017/11/13 15:22:24 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"

int	main(int ac, char **av)
{
	int		i;
	int		nb;
	char	*str;

	i = 0;
	nb = atoi(av[1]);
	if (ac < 2)
		return (0);
	str = malloc(nb);
	while (i < nb)
	{
		str[i] = av[2][0];
		i++;
	}
	str[i] = '\0';
	printf("%s\n", str);
}
