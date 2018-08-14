#include "libft.h"

void	ft_printitoabase(uintmax_t nb, char *str, int base)
{
	int	c;

	if (nb / base > 0)
		ft_printitoabase(nb / base, str, base);
	c = nb % base;
	write(1, &str[c], 1);
}

