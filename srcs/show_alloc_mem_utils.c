/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 10:22:25 by nbouchin          #+#    #+#             */
/*   Updated: 2018/09/25 10:29:11 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_malloc.h"
#include <stdio.h>

void		print_addr_fd(const void *addr, int fd)
{
	const char	*digits;
	size_t		nb;
	char		buffer[100];
	size_t		len;

	digits = "0123456789abcdef";
	len = 0;
	nb = (size_t)addr;
	ft_bzero(buffer, sizeof(buffer));
	ft_putstr_fd("0x", fd);
	if (nb == 0)
		ft_putchar_fd('0', fd);
	while (nb > 0)
	{
		buffer[len++] = digits[(size_t)nb % 16];
		nb /= 16;
	}
	ft_strrev(buffer);
	ft_putstr_fd(buffer, fd);
}

void		print_addr(const void *addr)
{
	print_addr_fd(addr, 1);
}

void		print_page(const t_page *page, int i)
{
	if (i == 0)
		ft_putstr("TINY : ");
	if (i == 1)
		ft_putstr("SMALL : ");
	if (i == 2)
		ft_putstr("LARGE : ");
	print_addr(page);
	ft_putendl("");
	dprintf(2, "PRINTF : %p\n", page);
}

void		print_octets(t_block *p)
{
	print_addr(p);
	ft_putstr(" - ");
	print_addr(p + p->size);
	ft_putstr(" : ");
	ft_putnbr(p->size);
	ft_putstr(" octets\n");
}

void		print_total(int total)
{
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl("");
}
