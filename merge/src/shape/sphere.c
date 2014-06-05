/*
** sphere.c for sphere in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 03:44:36 2014 Geoffrey Merran
** Last update Tue Jun  3 23:37:56 2014 Geoffrey Merran
*/

#include "core.h"

float	get_k_from_delta(float delta, float a, float b)
{
  float	k1;
  float	k2;

  if (delta >= 0)
    {
      k1 = (-b + sqrt(delta)) / (2 * a);
      k2 = (-b - sqrt(delta)) / (2 * a);
      if (k2 > 0.000001)
      	return (k2);
      if (k1 > 0.000001)
	return (k1);
      return (0);
    }
  else
    return (0);
  return (0);
}

t_rinter	inter_sphere(t_cam eye, t_vector pos_3d, t_item sphere)
{
  float		a;
  float		b;
  float		c;
  float		delta;
  t_rinter	rinter;

  get_simple_pos(&eye, sphere, &pos_3d);
  a = pow(pos_3d.x, 2) + pow(pos_3d.y, 2) + pow(pos_3d.z, 2);
  b = 2.000 * ((eye.pos.x * pos_3d.x) +
	       (eye.pos.y * pos_3d.y) + (eye.pos.z * pos_3d.z));
  c = pow(eye.pos.x, 2) +
    pow(eye.pos.y, 2) + pow(eye.pos.z, 2) - pow(sphere.rayon, 2);
  delta = pow(b, 2) - (4 * a * c);
  rinter.k = get_k_from_delta(delta, a, b);
  rinter.p = get_eq_param(eye.pos, rinter.k, pos_3d);
  return (rinter);
}
