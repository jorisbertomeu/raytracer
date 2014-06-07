/*
** parser.h for parser in /home/merran_g/work/c_elem/raytracer/includes
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Mon May 19 23:05:46 2014 Geoffrey Merran
** Last update Sat Jun  7 21:18:18 2014 Joris Bertomeu
*/

#ifndef PARSER_
# define PARSER_
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include "my.h"

typedef		struct s_list
{
  char		*data;
  struct s_list *next;
  struct s_list *prev;
}		t_list;

#endif /* PARSER_ */
