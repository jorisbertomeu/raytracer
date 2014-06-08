/*
** reflexion.c for reflexion in /home/merran_g/work/c_igraph/raytracer
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Fri Jun  6 03:23:23 2014 Geoffrey Merran
** Last update Sun Jun  8 16:06:24 2014 Geoffrey Merran
*/

#define _BSD_SOURCE
#include "core.h"

t_rgb		put_reflexion(t_inter inter, t_scene *scene, t_vector pos_3d)
{
  t_cam		save;
  t_vector	r;
  t_inter      	color;

  save.pos = scene->eye->pos;
  save.angle = scene->eye->pos;
  init_vec(&scene->eye->pos, inter.p.x, inter.p.y, inter.p.z);
  init_vec(&scene->eye->angle, 0, 0, 0);
  init_rgb(&color.rgb, 0, 0, 0);
  normalize_vec(&inter.n);
  normalize_vec(&pos_3d);
  r.x = ((-2.0 * inter.n.x) * (pos_3d.x * inter.n.x)) + pos_3d.x;
  r.y = ((-2.0 * inter.n.y) * (pos_3d.y * inter.n.y)) + pos_3d.y;
  r.z = ((-2.0 * inter.n.z) * (pos_3d.z * inter.n.z)) + pos_3d.z;
  color = get_pixel_color(r, scene);
  scene->eye->pos = save.pos;
  scene->eye->pos = save.angle;
  return (color.rgb);
}
