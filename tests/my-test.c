#include <stdlib.h>
#include "../includes/libft_malloc.h"

int main()
{
	char *addr;
	char *addr1;
	char *addr2;
	char *addr3;
	char *addr4;
	char *addr5;
	char *addr6;
	char *addr7;
	char *addr8;
	char *addr9;
	int	i;

	i = 0;

	ft_putendl("TINY MALLOC TEST");
	while (i < 2000)
	{
		addr = (char*)ft_malloc(32);
		addr[0] = 42;
		ft_free(addr);
		addr1 = (char*)ft_malloc(32);
		addr1[0] = 42;
		ft_free(addr1);
		addr2 = (char*)ft_malloc(32);
		addr2[0] = 42;
		ft_free(addr2);
		addr3 = (char*)ft_malloc(32);
		addr3[0] = 42;
		ft_free(addr3);
		addr4 = (char*)ft_malloc(32);
		addr4[0] = 42;
		ft_free(addr4);
		addr5 = (char*)ft_malloc(32);
		addr5[0] = 42;
		ft_free(addr5);
		addr6 = (char*)ft_malloc(32);
		addr6[0] = 42;
		ft_free(addr6);
		addr7 = (char*)ft_malloc(32);
		addr7[0] = 42;
		ft_free(addr7);
		addr8 = (char*)ft_malloc(32);
		addr8[0] = 42;
		ft_free(addr8);
		addr9 = (char*)ft_malloc(32);
		addr9[0] = 42;
		ft_free(addr9);
		i++;
	}
//	ft_putendl("SMALL MALLOC TEST");
//	i = 0;
//	while (i < 20)
//	{
//		addr = (char*)ft_malloc(1200);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(1200);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(1200);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(1200);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(1200);
//		addr4[0] = 42;
//		ft_free(addr);
//		ft_free(addr1);
//		ft_free(addr2);
//		ft_free(addr3);
//		ft_free(addr4);
//		i++;
//	}
//	ft_putendl("LARGE MALLOC TEST");
//	i = 0;
//	while (i < 1)
//	{
//		addr = (char*)ft_malloc(127450);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(127450);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(127450);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(127450);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(127450);
//		addr4[0] = 42;
//
//		ft_free(addr);
//		ft_free(addr1);
//		ft_free(addr2);
//		ft_free(addr3);
//		ft_free(addr4);
//		i++;
//	}
//	ft_putendl("TINY MALLOC TEST");
//	i = 0;
//	while (i < 5000)
//	{
//		addr = (char*)ft_malloc(450);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(450);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(450);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(450);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(450);
//		addr4[0] = 42;
//		ft_free(addr2);
//		ft_free(addr4);
//		ft_free(addr3);
//		ft_free(addr1);
//		ft_free(addr);
//		i++;
//	}
//	ft_putendl("SMALL MALLOC TEST");
//	i = 0;
//	while (i < 5000)
//	{
//		addr = (char*)ft_malloc(1200);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(1200);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(1200);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(1200);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(1200);
//		addr4[0] = 42;
//		ft_free(addr2);
//		ft_free(addr4);
//		ft_free(addr3);
//		ft_free(addr1);
//		ft_free(addr);
//		i++;
//	}
//	ft_putendl("LARGE MALLOC TEST");
//	i = 0;
//	while (i < 5000)
//	{
//		addr = (char*)ft_malloc(127450);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(127450);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(127450);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(127450);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(127450);
//		addr4[0] = 42;
//		ft_free(addr2);
//		ft_free(addr4);
//		ft_free(addr3);
//		ft_free(addr1);
//		ft_free(addr);
//		i++;
//	}
//	ft_putendl("TINY MALLOC TEST");
//	i = 0;
//	while (i < 5000)
//	{
//		addr = (char*)ft_malloc(450);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(450);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(450);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(450);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(450);
//		addr4[0] = 42;
//		ft_free(addr);
//		ft_free(addr1);
//		ft_free(addr2);
//		ft_free(addr3);
//		ft_free(addr4);
//		i++;
//	}
//	ft_putendl("SMALL MALLOC TEST");
//	i = 0;
//	while (i < 5000)
//	{
//		addr = (char*)ft_malloc(1200);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(1200);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(1200);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(1200);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(1200);
//		addr4[0] = 42;
//		ft_free(addr);
//		ft_free(addr1);
//		ft_free(addr2);
//		ft_free(addr3);
//		ft_free(addr4);
//		i++;
//	}
//	ft_putendl("LARGE MALLOC TEST");
//	i = 0;
//	while (i < 200)
//	{
//		addr = (char*)ft_malloc(127450);
//		addr[0] = 42;
//		addr1 = (char*)ft_malloc(127450);
//		addr1[0] = 42;
//		addr2 = (char*)ft_malloc(127450);
//		addr2[0] = 42;
//		addr3 = (char*)ft_malloc(127450);
//		addr3[0] = 42;
//		addr4 = (char*)ft_malloc(127450);
//		addr4[0] = 42;
//	ft_free(addr4);
//	ft_free(addr);
//	ft_free(addr3);
//	ft_free(addr2);
//	ft_free(addr1);
//		i++;
//	}
	ft_test();
	return (0);
} 
