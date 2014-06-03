/*
** get_normal.c for get_normal in /home/merran_g/work/c_igraph/raytracer/src/inter
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Mon Jun  2 16:10:25 2014 Geoffrey Merran
** Last update Mon Jun  2 17:58:04 2014 Geoffrey Merran
*/

#include "core.h"

t_vector	get_normal(t_inter inter)
{
  t_vector	n;

  if (inter.type == SPHERE)
    {
      n.x = inter.p.x;
      n.y = inter.p.y;
      n.z = inter.p.z;
    }
  else if (inter.type == PLANE)
    {
      n.x = -100.0;
      n.y = 0.0;
      n.z = 0.0;
    }
  else if (inter.type == CONE)
    {
      n.x = inter.p.x;
      n.y = inter.p.y;
      n.z = 0;
    }
  return (n);
}
