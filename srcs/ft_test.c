#include "../includes/libft_malloc.h"
#include <stdio.h>

void		ft_test()
{
//	int		i;
//	t_page	*page;
//	t_block	*p;
//	size_t	total;
//
//	i = 0;
//	page = NULL;
//	p = NULL;
//	total = 0;
//	while (i <= 2)
//	{
//		page = g_zone[i].page;
//		while (page)
//		{
//			if (i == 0)
//				dprintf(1, "TINY : %p\n", page);
//			if (i == 1)
//				dprintf(1, "SMALL : %p\n", page);
//			if (i == 2)
//				dprintf(1, "LARGE : %p\n", page);
//			p = (t_block *)(page + 1);
//			while (p)
//			{
//				total += p->size;
//				if (p->is_free)
//					dprintf(1, "%p - %p : %lu free octets\n", p, p + p->size, p->size);
//				else
//					dprintf(1, "%p - %p : %lu nonfree octets\n", p, p + p->size, p->size);
//				p = p->nxt;	
//			}
//			page = page->nxt;
//		}
//		i++;
//	}
//	dprintf(1, "Total : %lu\n", total);
}
