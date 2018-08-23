#include "../includes/libft_malloc.h"
#include <stdio.h>
struct test
{
	struct test *next;
};

int	main(int argc, char **argv)
{
	struct test *head;
	struct test **curs;

	head = calloc(1, sizeof(struct test));
	curs = &head;
	while (*curs)
	{
		curs = &(*curs)->next;
	}
	*curs = calloc(1, sizeof(struct test));
	dprintf(2, "%p -> %p\n", head, head->next);
}
