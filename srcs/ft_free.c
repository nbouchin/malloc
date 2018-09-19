#include "../includes/libft_malloc.h"
#include <stdio.h>

/*
**	Memory free and defragmentation.
*/

void		defrag(t_block **p, void *ptr, int offset)
{
	t_block		*prev;

	prev = NULL;
	while ((*p))
	{
		if ((t_block*)((*p)) == (t_block*)ptr - 1)
		{
			(void)offset;
			(*p)->is_free = 1;
			(*p)->size = get_offset((*p)->size, offset);
//			if ((*p)->nxt && (*p)->nxt->is_free)
//			{
//				(*p)->size += (*p)->nxt->size + sizeof(t_block);
//				(*p)->nxt = (*p)->nxt->nxt;
//			}
//			if (prev && prev->is_free)
//			{
//				prev->size += (*p)->size + sizeof(t_block);
//				prev->nxt = (*p)->nxt;
//			}
			return ;
		}
		prev = (*p);
		(*p) = (*p)->nxt;
	}
}

/*
**	Delete a page if this one is free and rechain linked list.
*/

void		delete_page(t_block *p, t_page **page, t_page **prev, int i)
{
	if ((p->size == (*page)->size - sizeof(t_block)) && i == 2)
	{
		if (!(*prev) && (*page)->nxt)
			g_zone[2].page = (*page)->nxt;
		else if ((*prev) && (*page)->nxt)
			(*prev)->nxt = (*page)->nxt;
		else
		{
			g_zone[2].total_size = 0; 
			g_zone[2].last = NULL;
			g_zone[2].page = NULL;
		}
		munmap((*page), (*page)->size + sizeof(t_page));
	}
	else if (p->size == (*page)->size - sizeof(t_block))
	{
		if (!(*prev) && (*page)->nxt)	
			g_zone[i].page = (*page)->nxt;			
		else if ((*prev) && (*page)->nxt)
			(*prev)->nxt = (*page)->nxt;
		else
		{
			g_zone[i].total_size = 0; 
			g_zone[i].last = NULL;
			g_zone[i].page = NULL;
			return ;
		}
		munmap((*page), (*page)->size + sizeof(t_page));
	}
}

/*
**	Large allocation free runtime.
*/

void		large_free(void *ptr)
{
	t_block		*p;
	t_page		*page;
	t_page		*prev;

	page = NULL;
	prev = NULL;
	p = NULL; 
	page = g_zone[2].page;
	while (page)
	{
		if (((t_block *)(page + 1) + 1) == ptr)
		{
			p = (t_block *)(page + 1);
			delete_page(p, &page, &prev, 2);
			return ;
		}
		prev = page;
		page = page->nxt;
	}
}

/*
**	Tiny and small allocation free runtime.
*/

void		tiny_small_free(void *ptr)
{
	int			i;
	t_block		*p;
	t_page		*page;
	t_page		*prev;

	i = 0;
	p = NULL;
	page = NULL;
	prev = NULL;
	while (i <= 1)
	{
		page = g_zone[i].page;
		while (page)
		{
			if (i == 0)
			{
				if ((char*)ptr >= (char*)(page) && (char*)ptr <= (char*)(page) + N)
				{
					p = (t_block *)((page) + 1);
					defrag(&p, ptr, 16);
					delete_page(p, &page, &prev, i);
					return ;
				}
			}
			else if (i == 1)
			{
				if ((char*)ptr >= (char*)(page) && (char*)ptr <= (char*)(page) + M)
				{
					p = (t_block *)((page) + 1);
					defrag(&p, ptr, 512);
					delete_page(p, &page, &prev, i);
					return ;
				}
			}
			prev = (page);
			page = page->nxt;
		}
		i++;
	}
}

void		ft_free(void *ptr)
{
	if (ptr == 0)
		return ;
	tiny_small_free(ptr);
	large_free(ptr);
	(void)ptr;
	return ;
}

