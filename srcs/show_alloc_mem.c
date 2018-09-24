#include "../includes/libft_malloc.h"
#include <stdio.h>

void				print_addr_fd(void *addr, int fd)
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

void				print_addr(void *addr)
{
	print_addr_fd(addr, 1);
}

void		print_page(t_page *page, int i)
{
	if (i == 0)
		ft_putstr("TINY : ");
	if (i == 1)
		ft_putstr("SMALL : ");
	if (i == 2)
		ft_putstr("LARGE : ");
	print_addr(page);
	ft_putendl("");
}

void		print_octets(t_block *p)
{
//	if (p->is_free)
//	{
	//	dprintf(1, "%p - %p : %lu free octets\n", p, p + p->size, p->size);
		print_addr(p);
		ft_putstr(" - ");
		print_addr(p + p->size);
		ft_putstr(" : ");
		ft_putnbr(p->size);
		ft_putstr(" octets\n");
//	}
//	else
//	{
//		dprintf(1, "%p - %p : %lu nonfree octets\n", p, p + p->size, p->size);
//	}
}

void		print_total(int total)
{
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl("");
}

void		show_alloc_mem()
{
	int		i;
	t_page	*page;
	t_block	*p;
	size_t	total;

	i = 0;
	page = NULL;
	p = NULL;
	total = 0;
	while (i <= 2)
	{
		page = g_zone[i].page;
		while (page)
		{
			print_page(page, i);
			p = (t_block *)(page + 1);
			while (p)
			{
				total += p->size;
				print_octets(p);
				p = p->nxt;	
			}
			page = page->nxt;
		}
		i++;
	}
	print_total(total);
}
