/*
** luminosity.c for luminosity in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 23:18:21 2014 Geoffrey Merran
** Last update Fri Jun  6 02:59:40 2014 Geoffrey Merran
*/

#define _BSD_SOURCE
#include "core.h"

void		get_correct_color(int *c)
{
  if (*c < 0)
    *c = 0;
  if (*c > 255)
    *c = 255;
}

void		get_lumi_color(t_inter *inter, float cos_a, t_spot spot)
{
  inter->rgb.r = ((float) inter->item.color.r * cos_a) *
    ((float) spot.color.r / 255.0);
  inter->rgb.g = ((float) inter->item.color.g * cos_a) *
    ((float) spot.color.g / 255.0);
  inter->rgb.b = ((float) inter->item.color.b * cos_a) *
    ((float) spot.color.b / 255.0);
  inter->rgb.r = ((float) inter->rgb.r +
		  (inter->item.brillance * (float) spot.color.r * cos_a));
  inter->rgb.g = ((float) inter->rgb.g +
		  (inter->item.brillance * (float) spot.color.g * cos_a));
  inter->rgb.b = ((float) inter->rgb.b +
		  (inter->item.brillance * (float) spot.color.b * cos_a));
  get_correct_color(&inter->rgb.r);
  get_correct_color(&inter->rgb.g);
  get_correct_color(&inter->rgb.b);
}

t_rgb		luminosity(t_spot spot, t_inter inter)
{
  t_vector	l;
  float		cos_a;
  float		norm;
  float		norm_d;

  l.x = spot.pos.x - inter.p.x - inter.item.pos.x;
  l.y = spot.pos.y - inter.p.y - inter.item.pos.y;
  l.z = spot.pos.z - inter.p.z - inter.item.pos.z;
  norm = sqrtf(pow(l.x, 2) + pow(l.y, 2) + pow(l.z, 2));
  norm_d = sqrtf(pow(inter.n.x, 2) + pow(inter.n.y, 2) + pow(inter.n.z, 2));
  cos_a = ((inter.n.x * l.x) + (inter.n.y * l.y)
	   + (inter.n.z * l.z)) / (norm * norm_d);
  if (cos_a < 0.0001)
    cos_a = 0;
  get_lumi_color(&inter, cos_a, spot);
  return (inter.rgb);
}

