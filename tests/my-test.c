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
		addr = (char*)malloc(50);
		ft_strcpy(addr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		free(addr);
		addr1 = (char*)malloc(50);
		addr1[0] = 42;
		free(addr1);
		addr2 = (char*)malloc(50);
		addr2[0] = 42;
		free(addr2);
		addr3 = (char*)malloc(50);
		addr3[0] = 42;
		free(addr3);
		addr4 = (char*)malloc(50);
		addr4[0] = 42;
		free(addr4);
		addr5 = (char*)malloc(50);
		addr5[0] = 42;
		free(addr5);
		addr6 = (char*)malloc(50);
		addr6[0] = 42;
		free(addr6);
		addr7 = (char*)malloc(50);
		addr7[0] = 42;
		free(addr7);
		addr8 = (char*)malloc(50);
		addr8[0] = 42;
		free(addr8);
		addr9 = (char*)malloc(50);
		addr9[0] = 42;
		free(addr9);
		i++;
	}
	ft_putendl("SMALL MALLOC TEST");
	i = 0;
	while (i < 20)
	{
		addr = (char*)malloc(1200);
		addr[0] = 42;
		addr1 = (char*)malloc(1200);
		addr1[0] = 42;
		addr2 = (char*)malloc(1200);
		addr2[0] = 42;
		addr3 = (char*)malloc(1200);
		addr3[0] = 42;
		addr4 = (char*)malloc(1200);
		addr4[0] = 42;
		free(addr1);
		free(addr);
		free(addr3);
		free(addr4);
		free(addr2);
		i++;
	}
	ft_putendl("LARGE MALLOC TEST");
	i = 0;
	while (i < 1)
	{
		addr = (char*)malloc(127450);
		addr[0] = 42;
		addr1 = (char*)malloc(127450);
		addr1[0] = 42;
		addr2 = (char*)malloc(127450);
		addr2[0] = 42;
		addr3 = (char*)malloc(127450);
		addr3[0] = 42;
		addr4 = (char*)malloc(127450);
		addr4[0] = 42;

		free(addr);
		free(addr1);
		free(addr2);
		free(addr3);
		free(addr4);
		i++;
	}
	ft_putendl("TINY MALLOC TEST");
	i = 0;
	while (i < 5000)
	{
		addr = (char*)malloc(450);
		addr[0] = 42;
		addr1 = (char*)malloc(450);
		addr1[0] = 42;
		addr2 = (char*)malloc(450);
		addr2[0] = 42;
		addr3 = (char*)malloc(450);
		addr3[0] = 42;
		addr4 = (char*)malloc(450);
		addr4[0] = 42;
		free(addr2);
		free(addr4);
		free(addr3);
		free(addr1);
		free(addr);
		i++;
	}
	ft_putendl("SMALL MALLOC TEST");
	i = 0;
	while (i < 5000)
	{
		addr = (char*)malloc(1200);
		addr[0] = 42;
		addr1 = (char*)malloc(1200);
		addr1[0] = 42;
		addr2 = (char*)malloc(1200);
		addr2[0] = 42;
		addr3 = (char*)malloc(1200);
		addr3[0] = 42;
		addr4 = (char*)malloc(1200);
		addr4[0] = 42;
		free(addr2);
		free(addr4);
		free(addr3);
		free(addr1);
		free(addr);
		i++;
	}
	ft_putendl("LARGE MALLOC TEST");
	i = 0;
	while (i < 5000)
	{
		addr = (char*)malloc(127450);
		addr[0] = 42;
		addr1 = (char*)malloc(127450);
		addr1[0] = 42;
		addr2 = (char*)malloc(127450);
		addr2[0] = 42;
		addr3 = (char*)malloc(127450);
		addr3[0] = 42;
		addr4 = (char*)malloc(127450);
		addr4[0] = 42;
		free(addr2);
		free(addr4);
		free(addr3);
		free(addr1);
		free(addr);
		i++;
	}
	ft_putendl("TINY MALLOC TEST");
	i = 0;
	while (i < 5000)
	{
		addr = (char*)malloc(450);
		addr[0] = 42;
		addr1 = (char*)malloc(450);
		addr1[0] = 42;
		addr2 = (char*)malloc(450);
		addr2[0] = 42;
		addr3 = (char*)malloc(450);
		addr3[0] = 42;
		addr4 = (char*)malloc(450);
		addr4[0] = 42;
		free(addr);
		free(addr1);
		free(addr2);
		free(addr3);
		free(addr4);
		i++;
	}
	ft_putendl("SMALL MALLOC TEST");
	i = 0;
	while (i < 5000)
	{
		addr = (char*)malloc(1200);
		addr[0] = 42;
		addr1 = (char*)malloc(1200);
		addr1[0] = 42;
		addr2 = (char*)malloc(1200);
		addr2[0] = 42;
		addr3 = (char*)malloc(1200);
		addr3[0] = 42;
		addr4 = (char*)malloc(1200);
		addr4[0] = 42;
		free(addr);
		free(addr1);
		free(addr2);
		free(addr3);
		free(addr4);
		i++;
	}
	ft_putendl("LARGE MALLOC TEST");
	i = 0;
	while (i < 200)
	{
		addr = (char*)malloc(127450);
		addr[0] = 42;
		addr1 = (char*)malloc(127450);
		addr1[0] = 42;
		addr2 = (char*)malloc(127450);
		addr2[0] = 42;
		addr3 = (char*)malloc(127450);
		addr3[0] = 42;
		addr4 = (char*)malloc(127450);
		addr4[0] = 42;
	free(addr4);
	free(addr);
	free(addr3);
	free(addr2);
	free(addr1);
		i++;
	}
	ft_test();
	return (0);
} 
