/*
** xfree.c for libmy in /home/martel_c/rendu/CPE_2014_corewar/my
**
** Made by martelliere
** Login   <martel_c@epitech.net>
**
** Started on  Fri Apr  4 14:11:56 2014 martelliere
** Last update Fri Jun  6 17:33:00 2014 Geoffrey Merran
*/

#include "parser.h"

void	xfree(char *s)
{
  if (s == NULL)
    {
      fprintf(stderr, "RT: %s doesn't exist. Can't free it.\n", s);
      return ;
    }
  free(s);
}
