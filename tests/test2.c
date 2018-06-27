#include <stdlib.h>
#include "../includes/libft_malloc.h"

int main()
{
	int i;
	char *addr;
	char *addr1;
	char *addr2;
	char *addr3;
	char *addr4;

	ft_putendl("TINY MALLOC TEST");
	i = 0;
	while (i < 5024)
	{
		addr = (char*)ft_malloc(10);
		addr[0] = 42;
		addr1 = (char*)ft_malloc(10);
		addr1[0] = 42;
		addr2 = (char*)ft_malloc(10);
		addr2[0] = 42;
		addr3 = (char*)ft_malloc(10);
		addr3[0] = 42;
		addr4 = (char*)ft_malloc(10);
		addr4[0] = 42;
		ft_free(addr2);
		ft_free(addr4);
		ft_free(addr3);
		ft_free(addr1);
		ft_free(addr);
		i++;
	}

	ft_test();
	return (0);
} 
