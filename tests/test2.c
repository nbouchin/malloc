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

	i = 0;
//while (i < 1024)
//{
		addr = (char*)ft_malloc(1024);
		addr[0] = 42;
		addr1 = (char*)ft_malloc(1024);
		addr1[0] = 42;
		addr2 = (char*)ft_malloc(1024);
		addr2[0] = 42;
		addr3 = (char*)ft_malloc(1024);
		addr3[0] = 42;
		addr4 = (char*)ft_malloc(1024);
		addr4[0] = 42;
		ft_free(addr2);
		ft_free(addr4);
		ft_free(addr3);
		i++;
//}
	return (0);
} 
