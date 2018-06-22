#include "../includes/libft_malloc.h"

int      main()
{
   int   i;
   char  *addr;

   i = 0;
   while (i < 15000)
   {
      addr = (char*)ft_malloc(512);
      addr[0] = 42;
      i++;
   }
   return (0);
}
