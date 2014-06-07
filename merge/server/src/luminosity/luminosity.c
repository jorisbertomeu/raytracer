/*
** luminosity.c for luminosity in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 23:18:21 2014 Geoffrey Merran
** Last update Mon May 19 23:21:32 2014 Geoffrey Merran
*/

#define _BSD_SOURCE
#include "core.h"

unsigned int	luminosity(t_spot spot, t_inter inter)
{
  t_vector	l;
  float		cos_a;
  float		norm;
  float		norm_d;

  l.x = inter.p.x - spot.pos.x;
  l.y = inter.p.y - spot.pos.y;
  l.z = inter.p.z - spot.pos.z;
  norm = sqrtf(pow(l.x, 2) + pow(l.y, 2) + pow(l.z, 2));
  norm_d = sqrtf(pow(inter.n.x, 2) + pow(inter.n.y, 2) + pow(inter.n.z, 2));
  cos_a = ((inter.n.x * l.x) + (inter.n.y * l.y)
	   + (inter.n.z * l.z)) / (norm * norm_d);
  if (cos_a < 0.0001)
    cos_a = 0;
  inter.rgb.r = ((float) inter.rgb.r * cos_a) * (spot.color.r / 255.0);
  inter.rgb.g = ((float) inter.rgb.g * cos_a) * (spot.color.g / 255.0);
  inter.rgb.b = ((float) inter.rgb.b * cos_a) * (spot.color.b / 255.0);
  return (change_rgb(inter.rgb.r, inter.rgb.g, inter.rgb.b));
}
