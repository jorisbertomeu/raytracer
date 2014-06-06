/*
** get_normal.c for get_normal in /home/merran_g/work/c_igraph/raytracer/src/inter
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Mon Jun  2 16:10:25 2014 Geoffrey Merran
** Last update Fri Jun  6 19:29:54 2014 Geoffrey Merran
*/

#include "core.h"

t_vector	get_normal(t_inter inter)
{
  t_vector	n;

  if (inter.item.type == SPHERE)
    {
      n.x = inter.p.x;
      n.y = inter.p.y;
      n.z = inter.p.z;
    }
  else if (inter.item.type == PLANE)
    {
      n.x = 0.0;
      n.y = 0.0;
      n.z = 100.0;
    }
  else if (inter.item.type == CYLINDER)
    {
      n.x = inter.p.x;
      n.y = inter.p.y;
      n.z = 0;
    }
  else if (inter.item.type == CONE)
    {
      n.x = inter.p.x;
      n.y = inter.p.y;
      n.z = (-(conv_radian(inter.item.rayon))) * inter.p.z;
    }
  return (n);
}
