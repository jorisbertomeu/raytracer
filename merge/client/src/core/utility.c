/*
** items.c for items in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 01:54:50 2014 Geoffrey Merran
** Last update Fri Jun  6 17:25:10 2014 Geoffrey Merran
*/

#include "parser.h"

void	init_rgb(t_rgb *color, int r, int g, int b)
{
  color->r = r;
  color->g = g;
  color->b = b;
}
