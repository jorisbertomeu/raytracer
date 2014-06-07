/*
** xopen.c for xopen in /home/martel_c/rendu/Piscine-C-lib/my/
**
** Made by martelliere
** Login   <martel_c@pc-martel_c>
**
** Started on  Wed Dec  5 04:36:08 2012 martelliere
** Last update Fri Jun  6 17:32:51 2014 Geoffrey Merran
*/

#include "parser.h"

int	xopen(const char *path, int flags, mode_t mode)
{
  int	ret;

  if ((ret = open(path, flags, mode)) == -1)
    {
      fprintf(stderr, "RT: %s can't be opened.\n", path);
      exit(EXIT_FAILURE);
    }
  return (ret);
}
