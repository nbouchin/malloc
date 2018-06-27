#include "../includes/libft_malloc.h"
#include <stdio.h>

void		ft_test()
{
	int		i;
	t_page	*page;
	t_block	*p;

	i = 0;
	while (i <= 2)
	{
		page = g_zone[i].page;
		if (i == 0)
			dprintf(1, "TINY\n");
		if (i == 1)
			dprintf(1, "SMALL\n");
		if (i == 2)
			dprintf(1, "lARGE\n");
		while (page)
		{
			dprintf(1, "page : %p\n", page);
			p = (t_block *)(page + 1);
			while (p->nxt)
			{
				dprintf(1, "block address: %p block size : %lu\n", p, p->size);
				p = p->nxt;	
			}
			page = page->nxt;
		}
		i++;
	}
}
