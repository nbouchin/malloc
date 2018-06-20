#include "../includes/libft_malloc.h"

int      main()
{
   int   i;
   char  *addr;

   i = 0;
   while (i < 10)
   {
      addr = (char*)ft_malloc(993);
      addr[0] = 42;
      i++;
   }
   return (0);
}
