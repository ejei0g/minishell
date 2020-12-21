#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define STDERR 1

void   *ft_memdel(void *ptr)
{
   if (ptr)
   {
      free(ptr);
      ptr = NULL;
   }
   return (NULL);
}

void sig_quit(int i)
{
   char   *nbr;   nbr = ft_itoa(i);
   ms->err = 131;
   ft_memdel(nbr);
}
