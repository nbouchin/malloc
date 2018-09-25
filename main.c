#include "includes/libft_malloc.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	do {
	void *test = malloc(10);
	void *test1 = malloc(10);
	void *test2 = malloc(10);

	show_alloc_mem();
	free(test1);

	show_alloc_mem();
	realloc(test, 17);

	show_alloc_mem();
	}while(0);
	return 0;
}
