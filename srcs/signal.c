#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define STDERR 1
void sig_int(int i)
{
   printf("\b\b  ");
   printf("\n");
   ft_putstr_fd(MINISHELL, 1);
   ms->errno = 130;
//   printf("\033[0;36m\033[1m:face_with_symbols_on_mouth: minishell ▸ \033[0m");
}

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
   ms->errno = 131;
   ft_memdel(nbr);
}
